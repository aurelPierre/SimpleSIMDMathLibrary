include(CTest)

add_executable(test_matrix test_matrix.cpp)
target_link_libraries(test_matrix SSML)
target_link_libraries(test_matrix Toolbox)

add_test(NAME Runs_matrix COMMAND test_matrix)
