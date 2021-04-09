add_executable(ssml_bench)

file(GLOB_RECURSE SSML_BENCH_SOURCES *)
target_sources(ssml_bench PUBLIC ${SSML_BENCH_SOURCES})

target_link_libraries(ssml_bench PUBLIC glm)
target_link_libraries(ssml_bench PUBLIC ssml)
target_link_libraries(ssml_bench PUBLIC benchmark)

