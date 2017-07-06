/*
 * main.cpp
 *
 *     Created on: 2016/11/21
 *  Last modified: 2017/07/05
 *         Author: Tsukasa Fukunaga
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include "calc_pvalue.h"
#include "calc_pvalue_parameters.h"

using namespace std;

int main(int argc, char* argv[]) {
  CalcPvalueParameters parameters;
  parameters.SetParameters(argc, argv);
  CalcPvalue calc_p_value;
  calc_p_value.Run(parameters);
  return(0);
}
