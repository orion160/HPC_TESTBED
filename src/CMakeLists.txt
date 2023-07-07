add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark PRIVATE benchmark::benchmark benchmark::benchmark_main)