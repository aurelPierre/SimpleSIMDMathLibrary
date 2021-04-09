enable_testing()
include(GoogleTest)

function(test name)
	add_executable(${name} ${name}.cpp)
	target_link_libraries(${name} ssml)
	target_link_libraries(${name} gtest_main)

	add_test(NAME Run_${name} COMMAND ${name})
endfunction()

test(test_matrix2)
test(test_matrix3)
test(test_matrix4)

