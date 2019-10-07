# CMake generated Testfile for 
# Source directory: /Users/daniel/Documents/Github/toolite/CMakeTool
# Build directory: /Users/daniel/Documents/Github/toolite/CMakeTool
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_run "power" "5" "2")
set_tests_properties(test_run PROPERTIES  _BACKTRACE_TRIPLES "/Users/daniel/Documents/Github/toolite/CMakeTool/CMakeLists.txt;41;add_test;/Users/daniel/Documents/Github/toolite/CMakeTool/CMakeLists.txt;0;")
add_test(test_usage "power")
set_tests_properties(test_usage PROPERTIES  PASS_REGULAR_EXPRESSION "Usage: .* base exponent" _BACKTRACE_TRIPLES "/Users/daniel/Documents/Github/toolite/CMakeTool/CMakeLists.txt;43;add_test;/Users/daniel/Documents/Github/toolite/CMakeTool/CMakeLists.txt;0;")
add_test(test_5_2 "power" "5" "2")
set_tests_properties(test_5_2 PROPERTIES  PASS_REGULAR_EXPRESSION "= 25" _BACKTRACE_TRIPLES "/Users/daniel/Documents/Github/toolite/CMakeTool/CMakeLists.txt;61;add_test;/Users/daniel/Documents/Github/toolite/CMakeTool/CMakeLists.txt;66;do_test;/Users/daniel/Documents/Github/toolite/CMakeTool/CMakeLists.txt;0;")
add_test(test_10_5 "power" "10" "5")
set_tests_properties(test_10_5 PROPERTIES  PASS_REGULAR_EXPRESSION "= 100000" _BACKTRACE_TRIPLES "/Users/daniel/Documents/Github/toolite/CMakeTool/CMakeLists.txt;61;add_test;/Users/daniel/Documents/Github/toolite/CMakeTool/CMakeLists.txt;67;do_test;/Users/daniel/Documents/Github/toolite/CMakeTool/CMakeLists.txt;0;")
add_test(test_2_10 "power" "2" "10")
set_tests_properties(test_2_10 PROPERTIES  PASS_REGULAR_EXPRESSION "= 1024" _BACKTRACE_TRIPLES "/Users/daniel/Documents/Github/toolite/CMakeTool/CMakeLists.txt;61;add_test;/Users/daniel/Documents/Github/toolite/CMakeTool/CMakeLists.txt;68;do_test;/Users/daniel/Documents/Github/toolite/CMakeTool/CMakeLists.txt;0;")
subdirs("math")
