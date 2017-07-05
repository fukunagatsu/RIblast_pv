CXXFLAGS = -O3

RIblast: main.cpp calc_pvalue.cpp calc_pvalue_parameters.cpp

	$(CXX) $(CXXFLAGS) -o RIblast main.cpp calc_pvalue.cpp calc_pvalue_parameters.cpp