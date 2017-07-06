CXXFLAGS = -O3

RIblast_pv: main.cpp calc_pvalue.cpp calc_pvalue_parameters.cpp

	$(CXX) $(CXXFLAGS) -o RIblast_pv main.cpp calc_pvalue.cpp calc_pvalue_parameters.cpp