add_library(micrograd_core INTERFACE)
target_include_directories(micrograd_core INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(micrograd src/main.cpp)
target_link_libraries(micrograd PRIVATE micrograd_core)

find_package(Catch2 3 REQUIRED)

add_executable(micrograd_test tests/test_main.cpp)
target_link_libraries(micrograd_test PRIVATE
	micrograd_core
	Catch2::Catch2WithMain)

include(CTest)
include(Catch)

catch_discover_tests(micrograd_test)