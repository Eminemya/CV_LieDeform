# The make file for BCSLib

# compiler configuration

ifndef CC
CC=gcc
endif

ifndef CXX
CXX=g++
endif


WARNING_FLAGS = -Wall -Wextra -Wconversion -Wformat -Wno-unused-parameter
BOOST_WARNING_FLAGS = -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter

ifeq ($(CXX), clang++)
	CFLAGS = -std=c++0x -stdlib=libc++ -pedantic -U__STRICT_ANSI__ $(WARNING_FLAGS) -I. 
else
	CFLAGS = -std=c++0x -fmax-errors=50 -pedantic $(WARNING_FLAGS) -I. 
endif

OFLAGS = -march=native -ffast-math -O3 


#------ Intel-specific part (begin) ----------

ifdef MACOSX_VERSION
ifeq ($(INTEL_TARGET_ARCH), ia32)
INTEL_LINKS=-lmkl_intel -lmkl_intel_thread -lmkl_core -lipps -liomp5 -lpthread
else
INTEL_LINKS=-lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -lipps -liomp5 -lpthread
endif
else
ifeq ($(INTEL_TARGET_ARCH), ia32)
INTEL_LINKS=-Wl,--start-group -lmkl_intel -lmkl_intel_thread -lmkl_core -Wl,--end-group -lipps -liomp5 -lpthread
else
INTEL_LINKS=-Wl,--start-group -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -Wl,--end-group -lipps -liomp5 -lpthread
endif
endif

ifdef MACOSX_VERSION
INTEL_PATHS=-I$(MKLROOT)/include -L$(MKLROOT)/lib -I$(IPPROOT)/include -L$(IPPROOT)/lib -L$(ICCROOT)/lib
else
INTEL_PATHS=-I$(MKLROOT)/include -I$(IPPROOT)/include
endif

INTEL_FLAGS=-DHAS_INTEL_MKL -DHAS_INTEL_IPP $(INTEL_PATHS) $(INTEL_LINKS)


#------ Intel-specific part (end) ----------

BASE_HEADERS = bcslib/base/config.h \
	bcslib/base/basic_defs.h \
	bcslib/base/arg_check.h \
	bcslib/base/mathfun.h \
	bcslib/base/basic_algorithms.h \
	bcslib/base/iterator_wrappers.h \
	bcslib/base/basic_mem.h \
	bcslib/base/monitored_allocator.h \
	bcslib/base/index_selectors.h \
	bcslib/base/sexpression.h

TEST_HEADERS = bcslib/test/test_assertion.h \
	bcslib/test/test_units.h \
	bcslib/test/execution_mon.h \
	bcslib/test/performance_timer.h
	
ARRAY_BASIC_HEADERS = bcslib/array/array_base.h \
	bcslib/array/array_index.h \
	bcslib/array/generic_array_functions.h \
	bcslib/array/generic_array_transpose.h \
	bcslib/array/array1d.h \
	bcslib/array/array2d.h 
	 	
VEC_COMP_HEADERS = bcslib/veccomp/veccalc.h \
	bcslib/veccomp/vecstat.h \
	bcslib/veccomp/logical_vecops.h \
	bcslib/veccomp/intel_calc.h

ARRAY_COMP_HEADERS = bcslib/array/generic_array_eval.h \
	bcslib/array/array_calc.h \
	bcslib/array/array_stat.h \
	bcslib/array/logical_array_ops.h
	
LINALG_HEADERS = bcslib/extern/blas_select.h \
	 bcslib/array/blas_base.h \
	 bcslib/array/generic_blas.h \
	 bcslib/array/mat_times.h


ARRAY_SPARSE_HEADERS = bcslib/array/sparse_vector.h bcslib/array/dynamic_sparse_vector.h

GRAPH_BASIC_HEADERS = bcslib/graph/graph_base.h bcslib/graph/gr_edgelist.h bcslib/graph/gr_adjlist.h bcslib/graph/bgl_port.h

GEOMETRY_BASIC_HEADERS = bcslib/geometry/geometry_base.h bcslib/geometry/poly_scan.h bcslib/geometry/triangle_mesh.h

IMAGE_BASIC_HEADERS = bcslib/image/image_base.h bcslib/image/image.h

PROB_BASIC_HEADERS = bcslib/prob/pdistribution.h bcslib/prob/sampling.h bcslib/prob/discrete_distr.h 

all: test_c0x_support test_basics test_array
others: test_geometry test_image test_graph test_prob

test_c0x_support: bin/test_c0x_support.out
bin/test_c0x_support.out: test/test_c0x_support.cpp
	$(CXX) $(CFLAGS) -c test/test_c0x_support.cpp -o bin/test_c0x_support.out

test_geometry : bin/test_geometry_basics
test_image: bin/test_image_basics
test_graph : bin/test_graph_basics
test_prob: bin/test_prob_basics bin/test_psampling


#------ Basic tests ----------

test_basics: bin/test_basics

BASICS_TESTS = test/test_basics.cpp \
	test/test_basic_algorithms.cpp \
	test/test_basic_memory.cpp \
	test/test_index_selection.cpp
	
bin/test_basics: $(BASE_HEADERS) $(TEST_HEADERS) $(BASICS_TESTS)
	$(CXX) $(CFLAGS) $(BASICS_TESTS) -o bin/test_basics 


#------ Array tests -----------

# test_array : bin/test_array_basics bin/test_array_comp bin/test_array_sparse  
test_array: bin/test_array_basics \
	bin/test_array_comp \
	bin/test_array_comp_intel \
	bin/test_access_performance \
	bin/test_calc_performance \
	bin/test_calc_performance_intel \
	bin/test_linalg_intel

ARRAY_TEST_HEADERS = $(TEST_HEADERS) bcslib/test/test_array_aux.h

ARRAY_BASIC_TESTS = test/test_array_basics.cpp \
	test/test_array1d.cpp \
	test/test_array2d.cpp \
	test/test_array_transpose.cpp

bin/test_array_basics: $(BASE_HEADERS) $(ARRAY_TEST_HEADERS) $(ARRAY_BASIC_HEADERS) $(ARRAY_BASIC_TESTS) 
	$(CXX) $(CFLAGS) $(ARRAY_BASIC_TESTS) -o bin/test_array_basics
	
bin/test_access_performance: $(BASE_HEADERS) $(ARRAY_BASIC_HEADERS) test/test_access_performance.cpp
	$(CXX) $(CFLAGS) $(OFLAGS) test/test_access_performance.cpp -o bin/test_access_performance	
		
ARRAY_COMP_TESTS = test/test_array_comp.cpp \
	test/test_array_calc.cpp \
	test/test_array_stat.cpp \
	test/test_logical_array_ops.cpp

bin/test_array_comp: $(BASE_HEADERS) $(ARRAY_TEST_HEADERS) $(ARRAY_BASIC_HEADERS) $(VEC_COMP_HEADERS) $(ARRAY_COMP_HEADERS) $(ARRAY_COMP_TESTS) 
	$(CXX) $(CFLAGS) $(ARRAY_COMP_TESTS) -o bin/test_array_comp
	
bin/test_array_comp_intel: $(BASE_HEADERS) $(ARRAY_TEST_HEADERS) $(ARRAY_BASIC_HEADERS) $(VEC_COMP_HEADERS) $(ARRAY_COMP_HEADERS) $(ARRAY_COMP_TESTS) 
	$(CXX) $(CFLAGS) $(INTEL_FLAGS) $(ARRAY_COMP_TESTS) -o bin/test_array_comp_intel

bin/test_calc_performance: $(BASE_HEADERS) $(ARRAY_BASIC_HEADERS) $(VEC_COMP_HEADERS) test/test_calc_performance.cpp
	$(CXX) $(CFLAGS) $(OFLAGS) test/test_calc_performance.cpp -o bin/test_calc_performance
	
bin/test_calc_performance_intel: $(BASE_HEADERS) $(ARRAY_BASIC_HEADERS) $(VEC_COMP_HEADERS) test/test_calc_performance.cpp
	$(CXX) $(CFLAGS) $(INTEL_FLAGS) $(OFLAGS) -limf test/test_calc_performance.cpp -o bin/test_calc_performance_intel	
	
LINALG_TESTS = test/test_linalg.cpp \
	test/test_array_blas.cpp

bin/test_linalg_intel: $(BASE_HEADERS) $(ARRAY_TEST_HEADERS) $(ARRAY_BASIC_HEADERS) $(LINALG_HEADERS) $(LINALG_TESTS)
	$(CXX) $(CFLAGS) $(INTEL_FLAGS) $(LINALG_TESTS) -o bin/test_linalg 



#--- Pending -------------

ARRAY_SPARSE_TESTS = test/test_array_sparse.cpp test/test_spvec.cpp test/test_dynamic_spvec.cpp
bin/test_array_sparse: $(BASE_HEADERS) $(ARRAY_TEST_HEADERS) $(ARRAY_BASIC_HEADERS) $(ARRAY_SPARSE_HEADERS) $(ARRAY_SPARSE_TESTS)
	$(CXX) $(CFLAGS) $(ARRAY_SPARSE_TESTS) -o bin/test_array_sparse	


GEOMETRY_BASIC_TESTS = test/test_geometry_basics.cpp test/test_geometry_primitives.cpp test/test_poly_scan.cpp
bin/test_geometry_basics: $(BASE_HEADERS) $(TEST_HEADERS) $(GEOMETRY_BASIC_HEADERS) $(GEOMETRY_BASIC_TESTS)
	$(CXX) $(CFLAGS) $(GEOMETRY_BASIC_TESTS) -o bin/test_geometry_basics

	
IMAGE_BASIC_TESTS = test/test_image_basics.cpp test/test_image_views.cpp
bin/test_image_basics: $(BASE_HEADERS) $(TEST_HEADERS) $(IMAGE_BASIC_HEADERS) $(IMAGE_BASIC_TESTS)
	$(CXX) $(CFLAGS) $(IMAGE_BASIC_TESTS) -o bin/test_image_basics
	 

GRAPH_BASIC_TESTS = test/test_graph_basics.cpp test/test_gr_edgelist.cpp test/test_gr_adjlist.cpp test/test_graph_basic_alg.cpp
bin/test_graph_basics: $(BASE_HEADERS) $(TEST_HEADERS) $(GRAPH_BASIC_HEADERS) $(GRAPH_BASIC_TESTS)
	$(CXX) $(BOOST_CFLAGS) $(GRAPH_BASIC_TESTS) -o bin/test_graph_basics	
	
		
PROB_BASIC_TESTS = test/test_prob_basics.cpp test/test_discrete_distr.cpp
bin/test_prob_basics: $(BASE_HEADERS) $(TEST_HEADERS) $(PROB_BASIC_HEADERS) $(PROB_BASIC_TESTS)
	$(CXX) $(BOOST_CFLAGS) $(PROB_BASIC_TESTS) -o bin/test_prob_basics
	
	
bin/test_psampling: $(BASE_HEADERS) $(TEST_HEADERS) $(PROB_BASIC_HEADERS) test/test_psampling.cpp
	$(CXX) $(BOOST_CFLAGS) -O3 test/test_psampling.cpp -o bin/test_psampling
	

clean:
	rm bin/*

