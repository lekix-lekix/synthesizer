#include <benchmark/benchmark.h>
#include "CircularBuffer.hpp"
#include "CircularBufferMutex.hpp"
#include <thread>

// --- single-threaded write ---

static void BM_Write(benchmark::State &state)
{
    CircularBuffer<int, 1024> buf;

    for (auto _ : state)
    {
        // refill when full (write returns false)
        int dummy = 0;
        if (!buf.write(42))
            buf.read(dummy); // drain one slot then retry
        benchmark::DoNotOptimize(buf);
    }
}
BENCHMARK(BM_Write);

// --- single-threaded read ---

static void BM_Read(benchmark::State &state)
{
    CircularBuffer<int, 1024> buf;
    for (int i = 0; i < 1023; ++i)
        buf.write(i); // pre-fill

    for (auto _ : state)
    {
        int value = 0;
        if (!buf.read(value))
            buf.write(0); // refill one slot then retry
        benchmark::DoNotOptimize(value);
    }
}
BENCHMARK(BM_Read);

// --- single-threaded write+read round trip ---

static void BM_WriteRead(benchmark::State &state)
{
    CircularBuffer<int, 1024> buf;

    for (auto _ : state)
    {
        int value = 0;
        buf.write(42);
        buf.read(value);
        benchmark::DoNotOptimize(value);
    }
}
BENCHMARK(BM_WriteRead);

// --- vary buffer size ---

static void BM_WriteRead_Sizes(benchmark::State &state)
{
    // state.range(0) is the number of ops per iteration
    CircularBuffer<int, 4096> buf;

    for (auto _ : state)
    {
        for (int i = 0; i < state.range(0); ++i)
            buf.write(i);
        int v = 0;
        for (int i = 0; i < state.range(0); ++i)
            buf.read(v);
        benchmark::DoNotOptimize(v);
    }
    state.SetItemsProcessed(state.iterations() * state.range(0));
}
BENCHMARK(BM_WriteRead_Sizes)->Arg(1)->Arg(16)->Arg(64)->Arg(256);

// --- multithreaded: one producer, one consumer ---

static void BM_ProducerConsumer(benchmark::State &state)
{
    CircularBuffer<int, 4096> buf;
    bool running = true;

    // consumer thread drains the buffer in the background
    std::thread consumer([&]()
                         {
        int v = 0;
        while (running || buf.read(v))
            buf.read(v); });

    for (auto _ : state)
    {
        while (!buf.write(42))
            ; // spin if full
        benchmark::DoNotOptimize(buf);
    }

    running = false;
    consumer.join();
}
BENCHMARK(BM_ProducerConsumer)->UseRealTime();

//////////////////////////////////////////

// --- single-threaded write ---

static void BM_WriteMutex(benchmark::State &state)
{
    CircularBufferMutex<int, 1024> buf;

    for (auto _ : state)
    {
        // refill when full (write returns false)
        int dummy = 0;
        if (!buf.write(42))
            buf.read(dummy); // drain one slot then retry
        benchmark::DoNotOptimize(buf);
    }
}
BENCHMARK(BM_WriteMutex);

// --- single-threaded read ---

static void BM_ReadMutex(benchmark::State &state)
{
    CircularBufferMutex<int, 1024> buf;
    for (int i = 0; i < 1023; ++i)
        buf.write(i); // pre-fill

    for (auto _ : state)
    {
        int value = 0;
        if (!buf.read(value))
            buf.write(0); // refill one slot then retry
        benchmark::DoNotOptimize(value);
    }
}
BENCHMARK(BM_ReadMutex);

// --- single-threaded write+read round trip ---

static void BM_WriteReadMutex(benchmark::State &state)
{
    CircularBufferMutex<int, 1024> buf;

    for (auto _ : state)
    {
        int value = 0;
        buf.write(42);
        buf.read(value);
        benchmark::DoNotOptimize(value);
    }
}
BENCHMARK(BM_WriteReadMutex);

// --- vary buffer size ---

static void BM_WriteRead_SizesMutex(benchmark::State &state)
{
    // state.range(0) is the number of ops per iteration
    CircularBufferMutex<int, 4096> buf;

    for (auto _ : state)
    {
        for (int i = 0; i < state.range(0); ++i)
            buf.write(i);
        int v = 0;
        for (int i = 0; i < state.range(0); ++i)
            buf.read(v);
        benchmark::DoNotOptimize(v);
    }
    state.SetItemsProcessed(state.iterations() * state.range(0));
}
BENCHMARK(BM_WriteRead_SizesMutex)->Arg(1)->Arg(16)->Arg(64)->Arg(256);

// --- multithreaded: one producer, one consumer ---

static void BM_ProducerConsumerMutex(benchmark::State &state)
{
    CircularBufferMutex<int, 4096> buf;
    bool running = true;

    // consumer thread drains the buffer in the background
    std::thread consumer([&]()
                         {
        int v = 0;
        while (running || buf.read(v))
            buf.read(v); });

    for (auto _ : state)
    {
        while (!buf.write(42))
            ; // spin if full
        benchmark::DoNotOptimize(buf);
    }

    running = false;
    consumer.join();
}
BENCHMARK(BM_ProducerConsumerMutex)->UseRealTime();

BENCHMARK_MAIN();