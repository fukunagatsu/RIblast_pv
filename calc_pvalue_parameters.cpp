/*
 *  calc_pvalue_parameters.cpp
 *
 *  Created on: 2017/01/30
 *      Author: Tsukasa Fukunaga
 */

#include "calc_pvalue_parameters.h"
#include <getopt.h>
#include <stdlib.h>

void CalcPvalueParameters::SetParameters(int argc, char* argv[]) {
  int c;
  extern char *optarg;
  while ((c = getopt(argc, argv, "i:o:")) != -1) {
    switch (c) {
    case 'i':
      _input_filename = optarg;
      break;

    case 'o':
      _output_filename = optarg;
      break;

    default:
      cerr << "The argument is invalid command." << endl;
      exit(1);
    }
  }
}
