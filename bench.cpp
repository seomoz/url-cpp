#include <iostream>
#include <chrono>
#include <ctime>

#include "url.h"

/**
 * Run func() `count` times in each of `runs` experiments, where `name` provides a
 * meaningful description of the task being benchmarked. Prints out the time for each
 * run, the average time, and rate.
 */
template<typename Functor>
void bench(const std::string& name, size_t count, size_t runs, Functor func)
{
    std::cout << "Benchmarking " << name << " with " << count << " per run:" << std::endl;
    double total(0);
    for (size_t run = 0; run < runs; ++run)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (size_t it = 0; it < count; ++it)
        {
            func();
        }
        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double, std::milli>(end - start).count();
        total += duration;
        std::cout << "    Run " << run << ": " << duration << " ms" << std::endl;
    }
    std::cout << "  Average: " << (total / runs) << " ms" << std::endl;
    std::cout << "     Rate: " << ((count * runs) / total) << " k-iter / s" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "bench <base> <relative>" << std::endl;
        std::cerr << "  Benchmark various transforms of base + relative." << std::endl;
        return 1;
    }

    std::string base(argv[1]);
    std::string relative(argv[2]);

    size_t count = 1000000;
    size_t runs = 5;

    Url::Url base_url(base);
    std::string full = Url::Url(relative).relative_to(base_url).str();

    bench("parse", count, runs, [full]() {
        Url::Url parsed(full);
    });

    bench("relative", count, runs, [base_url, relative]() {
        Url::Url(relative).relative_to(base_url);
    });

    bench("parse + escape", count, runs, [full]() {
        Url::Url(full).escape();
    });

    bench("parse + abspath", count, runs, [full]() {
        Url::Url(full).abspath();
    });

    bench("parse + punycode", count, runs, [full]() {
        Url::Url(full).punycode();
    });
}
