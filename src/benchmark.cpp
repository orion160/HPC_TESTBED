#include <algorithm>
#include <execution>
#include <vector>

#include <benchmark/benchmark.h>

static void BM_reduce_seq(benchmark::State &state)
{
    const std::vector<double> v(state.range(0), 0.1);
    for (auto _ : state)
    {
        auto sum{std::reduce(v.begin(), v.end())};
        benchmark::DoNotOptimize(sum);
    }
}

BENCHMARK(BM_reduce_seq)->RangeMultiplier(2)->Range(1 << 20, 1 << 30)->Unit(benchmark::kMillisecond);

static void BM_reduce_par(benchmark::State &state)
{
    const std::vector<double> v(state.range(0), 0.1);
    for (auto _ : state)
    {
        auto sum{std::reduce(std::execution::par, v.begin(), v.end())};
        benchmark::DoNotOptimize(sum);
    }
}

BENCHMARK(BM_reduce_par)->RangeMultiplier(2)->Range(1 << 20, 1 << 30)->Unit(benchmark::kMillisecond)->UseRealTime();

static void BM_reduce_par_unseq(benchmark::State &state)
{
    const std::vector<double> v(state.range(0), 0.1);
    for (auto _ : state)
    {
        auto sum{std::reduce(std::execution::par_unseq, v.begin(), v.end())};
        benchmark::DoNotOptimize(sum);
    }
}

BENCHMARK(BM_reduce_par_unseq)
    ->RangeMultiplier(2)
    ->Range(1 << 20, 1 << 30)
    ->Unit(benchmark::kMillisecond)
    ->UseRealTime();

BENCHMARK_MAIN();
