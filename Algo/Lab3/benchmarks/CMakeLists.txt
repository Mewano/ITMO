set(BENCHMARK_ENABLE_TESTING off)

FetchContent_Declare(
        google_benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.8.3
)
if (WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif ()
FetchContent_MakeAvailable(google_benchmark)


macro(add_google_benchmark TEST_NAME TEST_ARGS)
    add_executable(${TEST_NAME} ${TEST_ARGS})
    target_link_libraries(${TEST_NAME} benchmark::benchmark lab3)
endmacro()

add_google_benchmark(worst_case_benchmark WorstCase.cpp)
