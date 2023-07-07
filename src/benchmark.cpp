#include <algorithm>
#include <functional>
#include <numeric>
#include <random>
#include <vector>

#include <benchmark/benchmark.h>

static void BM_reduce(benchmark::State &state)
{
    std::minstd_rand generator;
    std::uniform_int_distribution<int> distribution(1, 10);
    auto dice = std::bind(distribution, generator);
    std::vector<int> v(state.range(0));
    std::generate(v.begin(), v.end(), dice);
    for (auto _ : state)
    {
        auto sum = std::reduce(v.begin(), v.end(), 0);
        benchmark::DoNotOptimize(sum);
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_reduce)->RangeMultiplier(2)->Range(1, 1 << 30)->Complexity();

BENCHMARK_MAIN();
