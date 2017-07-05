/*
 * calc_pvalue.h
 *
 *     Created on: 2016/01/30
 *         Author: Tsukasa Fukunaga
 */

#ifndef CALC_PVALUE_H
#define CALC_PVALUE_H

#define TEST_W_SIZE 13
#define TEST_LENGTH_SIZE 6
#include "calc_pvalue_parameters.h"
#include <vector>

class CalcPvalue{
 public:
  CalcPvalue(){
    _gumbel_eta_coefficient_a = 0.0;
    _gumbel_eta_coefficient_b = 0.0;
    _gumbel_mu_coefficient_a = 0.0;
    _gumbel_mu_coefficient_b = 0.0;
  }
  void Run(const CalcPvalueParameters parameters);

 private:
  double CalcMinPvalue(int q_length, int db_length, double energy);
  void CalcDistributionParameter(double w);
  double _gumbel_eta_coefficient_a;
  double _gumbel_eta_coefficient_b;
  double _gumbel_mu_coefficient_a;
  double _gumbel_mu_coefficient_b;
};
#endif

static int w_array[TEST_W_SIZE] = {20,30,40,50,60,70,80,90,100,150,200,250,300};
static double gumbel_eta_array[TEST_LENGTH_SIZE][TEST_W_SIZE] = {{1.534, 1.307, 1.206, 1.142, 1.109, 1.081, 1.068, 1.046, 1.041, 1.029, 1.032, 1.031, 1.030},//length=100 
								 {1.796, 1.443, 1.281, 1.207, 1.158, 1.117, 1.099, 1.085, 1.073, 1.039, 0.998, 1.001, 0.996}, //length=200
								 {1.834, 1.477, 1.335, 1.251, 1.184, 1.145, 1.127, 1.113, 1.090, 1.048, 0.997, 0.987, 0.998}, //length=300
								 {2.008, 1.619, 1.413, 1.334, 1.274, 1.201, 1.172, 1.142, 1.122, 1.061, 1.035, 1.009, 0.998}, //length=400 
								 {2.150, 1.759, 1.532, 1.418, 1.328, 1.286, 1.254, 1.221, 1.191, 1.153, 1.093, 1.073, 1.060}, //length=600
                                          			 {2.235, 1.798, 1.600, 1.456, 1.364, 1.330, 1.272, 1.244, 1.238, 1.170, 1.136, 1.106, 1.081}}; //length=800
   
static double gumbel_mu_array[TEST_LENGTH_SIZE][TEST_W_SIZE] = {{ 6.68,  5.89,  5.53, 5.29, 5.16, 5.06, 4.99, 4.94, 4.88, 4.83, 4.81, 4.79, 4.79}, //length=100
								{ 8.62,  7.48,  6.95, 6.64, 6.43, 6.28, 6.18, 6.13, 6.06, 5.92, 5.85, 5.82, 5.80}, //length=200
								{ 9.86,  8.45,  7.81, 7.44, 7.20, 7.02, 6.89, 6.82, 6.77, 6.61, 6.52, 6.48, 6.44}, //length=300
								{10.80,  9.20,  8.46, 8.02, 7.76, 7.57, 7.44, 7.36, 7.30, 7.05, 6.95, 6.90, 6.86}, //length=400
								{12.21, 10.31,  9.41, 8.89, 8.58, 8.36, 8.21, 8.10, 8.02, 7.79, 7.66, 7.58, 7.54}, //length=600
								{13.11, 11.10, 10.12, 9.55, 9.20, 8.96, 8.80, 8.67, 8.57, 8.30, 8.17, 8.10, 8.03}}; //length=800
static double lnMN_array[TEST_LENGTH_SIZE] = {9.21,10.59,11.40,11.98,12.79,13.37};
static double MN_array[TEST_LENGTH_SIZE] = {100,200,300,400,600,800};
