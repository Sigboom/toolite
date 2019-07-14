cmake_minimum_required (VERSION 2.8)

project(power)

set (power_VERSION_MAJOR 1)
set (power_VERSION_MINOR 0)

#添加路径
set (CMAKE_INCLUDE_CURRENT_DIR ON)

#检查系统是否支持pow函数
include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
check_function_exists (pow HAVE_POW)

#添加配置头文件
configure_file (
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
	)
#设置默认选项为ON
option (USE_MYMATH
	"use provided math implementation" ON)

if (USE_MYMATH) 
	include_directories ("${PROJECT_SOURCE_DIR}/math")
	add_subdirectory(math)
	set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

aux_source_directory(. DIR_SRCS)
add_executable(power ${DIR_SRCS})

target_link_libraries(power MathFunctions)

install (TARGETS power DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)

enable_testing()

#测试程序是否能成功运行
add_test (test_run power 5 2)

add_test (test_usage power)
set_tests_properties(test_usage
	PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .* base exponent")

#add_test (test_5_2 power 5 2)
#set_tests_properties(test_5_2
#	PROPERTIES PASS_REGULAR_EXPRESSION "= 25")
#
#add_test (test_10_5 power 10 5)
#set_tests_properties(test_10_5
#	PROPERTIES PASS_REGULAR_EXPRESSION "= 100000")
#
#add_test (test_2_10 power 2 10)
#set_tests_properties(test_2_10
#	PROPERTIES PASS_REGULAR_EXPRESSION "= 1024")

# 定义宏来完成上面操作
macro (do_test arg1 arg2 result)
	add_test (test_${arg1}_${arg2} power ${arg1} ${arg2})
	set_tests_properties(test_${arg1}_${arg2}
		PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

do_test(5 2 "= 25")
do_test(10 5 "= 100000")
do_test(2 10 "= 1024")

#如果想支持gdb 在DEBUG 模式下使用-g
#set(CMAKE_BUILD_TYPE "DEBUG")
#set(CMAKE_CXX_FLAGS_DEBUG "ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
#set(CMAKE_CXX_FLAGS_RELEASE "ENV{CXXFLAGS} -O3 -Wall")

#构建一个 CPack 安装包
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENCE
	"${CMAKE_CURRENT_SOURCE_DIR}/Licence.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${power_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${power_VERSION_MINOR}")
include (CPack)
