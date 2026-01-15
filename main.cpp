#include "ThreadPool.h"
#include <iostream>
#include <vector>
#include <chrono>

int main()
{
    ThreadPool pool(4); // Create a thread pool with 4 worker threads

    std::vector<std::future<int>> results;

    for (int i = 0; i < 8; ++i)
    {
        results.emplace_back(
            pool.enqueue([i]
                         {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return i * i; }));
    }

    for (auto &result : results)
    {
        std::cout << result.get() << " ";
    }
    std::cout << std::endl;

    return 0;
}