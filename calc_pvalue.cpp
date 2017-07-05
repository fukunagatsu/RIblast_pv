/*
 * calc_pvalue.cpp
 *
 *     Created on: 2016/01/30
 *         Author: Tsukasa Fukunaga
 */

#include "calc_pvalue.h"
#include <vector>
#include <math.h>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdlib.h>

void CalcPvalue::Run(const CalcPvalueParameters parameters){
  int maximal_span = 0;
  double final_threshold = 0.0;
  
  ifstream fp;
  string buffer;
  fp.open(parameters.GetInputFilename().c_str(),ios::in);
  if (!fp){
    cout << "Error: can't open input_file:"+parameters.GetInputFilename()+"." <<endl;
    exit(1);
  }
  getline(fp,buffer);
  getline(fp,buffer);
  string token;
  {
    istringstream iss(buffer);
    for(int i = 0; i <4;i++){
      getline(iss, token, ',');
    }
    maximal_span = atoi(token.substr(12).c_str());
  }
  {
     istringstream iss(buffer);
     for(int i = 0; i <5;i++){
       getline(iss, token, ',');
     }
     final_threshold = atof(token.substr(15).c_str());
  }
  getline(fp,buffer);
  vector<double> min_energy_array; min_energy_array.reserve(1000);
  vector<string> q_name_array; q_name_array.reserve(1000);
  vector<string> db_name_array; db_name_array.reserve(1000);
  vector<int> q_length_array; q_length_array.reserve(1000);
  vector<int> db_length_array; db_length_array.reserve(1000);

  string q_name = "";
  string db_name = "";
  int q_length = 0;
  int db_length = 0;
  double min_energy = 0.0;
  while(getline(fp,buffer)){
    istringstream iss(buffer);
    getline(iss, token, ',');
    getline(iss, token, ',');
    string temp_qname = token;
    getline(iss, token, ',');
    int temp_qlength = atoi(token.c_str());
    getline(iss, token, ',');
    string temp_dbname = token;
    getline(iss, token, ',');
    int  temp_dblength = atoi(token.c_str());
    getline(iss, token, ',');
    double temp_energy = atof(token.c_str());
    if(q_name.size()!= 0 && (q_name!=temp_qname || db_name!=temp_dbname)){
      min_energy_array.push_back(min_energy);
      q_name_array.push_back(q_name);
      db_name_array.push_back(db_name);
      q_length_array.push_back(q_length);
      db_length_array.push_back(db_length);
      min_energy = 0.0;
    }
    q_name = temp_qname;
    q_length = temp_qlength;
    db_name = temp_dbname;
    db_length = temp_dblength;
    min_energy = min_energy < temp_energy ? min_energy : temp_energy;
  }
  if(q_name.size()!= 0){
    min_energy_array.push_back(min_energy);
    q_name_array.push_back(q_name);
    db_name_array.push_back(db_name);
    q_length_array.push_back(q_length);
    db_length_array.push_back(db_length);
  }
  
  CalcDistributionParameter(maximal_span);
  ofstream ofs;
  ofs.open(parameters.GetOutputFilename().c_str(),ios::out);
  for(int i= 0; i <min_energy_array.size();i++){
    double min_value = CalcMinPvalue(q_length_array[i],db_length_array[i],min_energy_array[i]);
    ofs << "Query:" << q_name_array[i] <<",target:" << db_name_array[i] << ",min_energy:" << min_energy_array[i] << ",p_value(min_energy):" << min_value <<  endl;
  }
  ofs.close();
}

double CalcPvalue::CalcMinPvalue(int q_length, int db_length, double energy){
  double estimated_mu = _gumbel_mu_coefficient_a*log(q_length*db_length)+_gumbel_mu_coefficient_b;  
  double estimated_eta = _gumbel_eta_coefficient_a*sqrt(q_length)*sqrt(db_length)+_gumbel_eta_coefficient_b;
  return(1-exp(-exp(-(-energy-estimated_mu)/estimated_eta)));
}

void CalcPvalue::CalcDistributionParameter(double w){
  vector<double> gumbel_mu; gumbel_mu.reserve(10);
  vector<double> gumbel_eta; gumbel_eta.reserve(10);
  if(w>=300){
    for(int j = 1;j <TEST_LENGTH_SIZE; j++){
      gumbel_mu.push_back(gumbel_mu_array[j][TEST_W_SIZE-1]);
      gumbel_eta.push_back(gumbel_eta_array[j][TEST_W_SIZE-1]);
    }
  }else{
    for(int i = 0; i< TEST_W_SIZE-1;i++){
      if(w >= w_array[i] && w < w_array[i+1]){
	int diff_w = w_array[i+1] - w_array[i];
	for(int j = 0;j <TEST_LENGTH_SIZE; j++){
	  double diff_mu = gumbel_mu_array[j][i+1] - gumbel_mu_array[j][i];
	  double diff_eta = gumbel_eta_array[j][i+1] - gumbel_eta_array[j][i];
	  gumbel_mu.push_back(gumbel_mu_array[j][i] + diff_mu * ((double)(w - w_array[i])/(double)diff_w));
	  gumbel_eta.push_back(gumbel_eta_array[j][i] + diff_eta * ((double)(w - w_array[i])/(double)diff_w));
	}
	break;
      }
    }
  }
  double sum_lnMN = 0.0;
  double sum_gumbel_mu = 0.0;
  double sum_lnMN_gumbel_mu = 0.0;
  double squared_sum_lnMN = 0.0;  
  
  for(int i = 0; i<TEST_LENGTH_SIZE;i++){
    sum_lnMN += lnMN_array[i];    
    sum_gumbel_mu += gumbel_mu[i];
    sum_lnMN_gumbel_mu += lnMN_array[i]*gumbel_mu[i];
    squared_sum_lnMN += lnMN_array[i]*lnMN_array[i];
  }

  double lnMN_denominator = TEST_LENGTH_SIZE*squared_sum_lnMN - sum_lnMN*sum_lnMN;  
  _gumbel_mu_coefficient_a = (TEST_LENGTH_SIZE*sum_lnMN_gumbel_mu - sum_lnMN*sum_gumbel_mu)/lnMN_denominator;
  _gumbel_mu_coefficient_b = (squared_sum_lnMN*sum_gumbel_mu - sum_lnMN*sum_lnMN_gumbel_mu)/lnMN_denominator;

  double sum_MN = 0.0;
  double sum_gumbel_eta = 0.0;
  double sum_MN_gumbel_eta = 0.0;
  double squared_sum_MN = 0.0;

  for(int i = 0; i<TEST_LENGTH_SIZE;i++){
    sum_MN += MN_array[i];
    sum_gumbel_eta += gumbel_eta[i];
    sum_MN_gumbel_eta += MN_array[i]*gumbel_eta[i];
    squared_sum_MN += MN_array[i]*MN_array[i];
  }

  double MN_denominator = TEST_LENGTH_SIZE*squared_sum_MN - sum_MN*sum_MN;
  _gumbel_eta_coefficient_a = (TEST_LENGTH_SIZE*sum_MN_gumbel_eta - sum_MN*sum_gumbel_eta)/MN_denominator;
  _gumbel_eta_coefficient_b = (squared_sum_MN*sum_gumbel_eta - sum_MN*sum_MN_gumbel_eta)/MN_denominator;
};
