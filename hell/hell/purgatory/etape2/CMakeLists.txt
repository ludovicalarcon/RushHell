cmake_minimum_required(VERSION 2.6)
project(rushhell_purgatory_etape2)

add_executable(
	test_fsa
	main.cpp
	Machine.cpp
	Machine.hpp
	)
set(EXECUTABLE_OUTPUT_PATH ..)