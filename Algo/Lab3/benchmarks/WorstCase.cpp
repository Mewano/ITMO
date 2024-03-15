#include <benchmark/benchmark.h>
#include <Lab3/Sort.hpp>

#include <vector>
#include <string>
#include <ranges>
#include <chrono>

template<typename Sort>
void WorstCase(benchmark::State &state, Sort sort) {
    std::vector<std::string> vector;

    const auto size = state.range(0);
    vector.reserve(size);

    auto to_string = [](const auto value) { return std::to_string(value); };
    auto range = std::views::iota(0, size) | std::views::transform(to_string);
    auto fill_vector_from_range = [&range, &vector]() {
        std::ranges::copy(range.begin(), range.end(), std::back_inserter(vector));
        std::reverse(vector.begin(), vector.end());
    };

    fill_vector_from_range();
    for ([[maybe_unused]] auto _ : state) {
        auto start = std::chrono::high_resolution_clock::now();
        sort(vector.begin(), vector.end(), std::less());
        auto end = std::chrono::high_resolution_clock::now();

        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
        state.SetIterationTime(elapsed_seconds.count());

        benchmark::DoNotOptimize(vector);
        vector.clear();
        fill_vector_from_range();
    }
}

auto InsertionSort = [](auto first, auto last, auto comp) {
    lab3::insertion_sort(first, last, comp);
};
auto QuickSort = [](auto first, auto last, auto comp) {
    lab3::quick_sort(first, last, comp);
};
auto Sort = [](auto first, auto last, auto comp) {
    lab3::sort(first, last, comp);
};

BENCHMARK_CAPTURE(WorstCase, InsertionSort, InsertionSort)->DenseRange(0, 100)->UseManualTime();
BENCHMARK_CAPTURE(WorstCase, QuickSort, QuickSort)->DenseRange(0, 100)->UseManualTime();
BENCHMARK_CAPTURE(WorstCase, Sort, Sort)->DenseRange(0, 100)->UseManualTime();

BENCHMARK_MAIN();
