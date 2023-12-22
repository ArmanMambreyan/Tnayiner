#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

class Number {
public:
    int x = 0;
};

std::mutex mtx;

void increaseWithMutex(Number* num) {
    for (int i = 0; i < 10000; ++i) {
       mtx.lock();
        num->x++;
        mtx.unlock();
    }
}

int main() {
    Number* num = new Number();
    num->x = 2;

    std::thread threads[20];

    auto startMutex = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 20; ++i) {
        threads[i] = std::thread(increaseWithMutex, num);
    }

    for (int i = 0; i < 20; ++i) {
        threads[i].join();
    }
    auto endMutex = std::chrono::high_resolution_clock::now();

    std::cout <<
              << std::chrono::duration_cast<std::chrono::milliseconds>(endMutex - startMutex).count()
              << "ms" << std::endl;

    std::cout << num->x << std::endl;
    delete num;

    return 0;
}
