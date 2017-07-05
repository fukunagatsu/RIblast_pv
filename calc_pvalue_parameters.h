/*
 * calc_p_value_parameters.h
 *
 *  Created on: 2017/01/30
 *      Author: Tsukasa Fukunaga
 */

#ifndef CALC_PVALUE_PARAMETERS_H
#define CALC_PVALUE_PARAMETERS_H

#include <string>
#include <cstdio>
#include <iostream>
using namespace std;

class CalcPvalueParameters{
 private:
  string _input_filename;
  string _output_filename;
  
 public:
  CalcPvalueParameters(){
    _input_filename = "";
    _output_filename = "";
  }
  void SetParameters(int argc, char* argv[]);

  string GetInputFilename() const {
    return _input_filename;
  }

  string GetOutputFilename() const {
    return _output_filename;
  }
};

#endif
