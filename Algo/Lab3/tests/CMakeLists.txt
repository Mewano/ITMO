FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
if (WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif ()
FetchContent_MakeAvailable(googletest)

include(GoogleTest)


macro(add_google_test TEST_NAME TEST_ARGS)
    add_executable(${TEST_NAME} ${TEST_ARGS})
    target_link_libraries(${TEST_NAME} GTest::gtest_main lab3)
    gtest_discover_tests(${TEST_NAME})
endmacro()

add_google_test(quick_sort_test QuickSort.cpp)
add_google_test(insertion_sort_test InsertionSort.cpp)
add_google_test(sort_test Sort.cpp)
