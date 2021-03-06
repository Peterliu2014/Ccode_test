#!/bin/bash
rm *.out
g++ -std=c++11 test.cc algorithm_impls/binary_tree.cc \
               algorithm_impls/string_alg.cc \
               algorithm_impls/reverse_polish.cc \
               algorithm_impls/max_point_on_a_line.cc \
               algorithm_impls/listnode.cc \
               algorithm_impls/word_break.cc \
               algorithm_impls/single_number.cc \
               algorithm_impls/candy.cc \
               algorithm_impls/complete_circuit.cc \
               algorithm_impls/undirectGraphNode.cc \
               algorithm_impls/palindrome.cc \
               algorithm_impls/surrounding_region.cc \
               -g \
               -O1
./a.out
