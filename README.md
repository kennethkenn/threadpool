# ThreadPool Implementation

This project demonstrates a simple yet powerful implementation of a thread pool in C++.

## Features

- **Task Queue**: A thread-safe queue to hold pending tasks.
- **Worker Threads**: A fixed number of threads that consume tasks from the queue.
- **Synchronization Primitives**: Mutexes and condition variables for efficient coordination.
- **Future-based Results**: Retrieve results of tasks asynchronously using `std::future`.
- **Graceful Shutdown**: Ensures all tasks are completed before shutting down the thread pool.

## Code Structure

- `ThreadPool.h`: Contains the declaration of the `ThreadPool` class.
- `ThreadPool.cpp`: Contains the implementation of the `ThreadPool` class.
- `main.cpp`: Demonstrates the usage of the thread pool with an example.

## Example Usage

```cpp
#include "ThreadPool.h"
#include <iostream>
#include <vector>
#include <chrono>

int main() {
    ThreadPool pool(4); // Create a thread pool with 4 worker threads

    std::vector<std::future<int>> results;

    for (int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([i] {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return i * i;
            })
        );
    }

    for (auto& result : results) {
        std::cout << result.get() << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

## How to Build

1. Ensure you have a C++ compiler that supports C++17 or later (e.g., `g++` or `clang++`).
2. Compile the code using the following command:

   ```bash
   g++ *.cpp -o threadpool -std=c++17
   ```

3. Run the compiled executable:

   ```bash
   ./threadpool
   ```

## Output

The program calculates the squares of numbers from 0 to 7 using the thread pool. The output will look like this (order may vary due to concurrency):

```text
0 1 4 9 16 25 36 49
```

## Performance Considerations

- **Thread Count**: Use `std::thread::hardware_concurrency()` to determine the optimal number of threads for CPU-bound tasks.
- **Lock Contention**: Minimized by holding the mutex only while accessing the task queue.
- **Exception Safety**: Tasks are executed in a try-catch block to prevent unhandled exceptions.

## License

This project is open-source and available under the [MIT License](LICENSE)
