#include <iostream>
#include "threadsafequeue.h"

using namespace std;

int main()
{
    ThreadSafeQueue<size_t> queue;

    for (size_t i = 0; i < 100000; ++i)
        queue.push(i);

    std::thread fillingThread([&]() {
        for (unsigned int i = 0; i < 100000; i++) {
            queue.push(i);
        }
    });
    std::thread readingThread([&]() {
        while (!queue.empty()) {
            std::cout << queue.front() << ' '; queue.pop();
        }
    });

    if (fillingThread.joinable())
        fillingThread.join();

    if (readingThread.joinable())
        readingThread.join();

    std::cout << std::endl;

    return 0;
}
