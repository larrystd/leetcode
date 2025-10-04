#include <cstdio>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>

int main() {
    std::mutex mtx;
    std::condition_variable cond;
    int currentIdx = 0;
    std::vector<std::thread> threads;

    for (int i = 0; i < 4; i++) {
        std::thread t([&](int i) -> void {
            while (true) {
                std::unique_lock<std::mutex> lck(mtx);
                cond.wait(lck, [&](){
                    return i == currentIdx;
                });

                printf("%d %d %d %d\n", i%4+1, (i+1)%4+1, (i+2)%4+1, (i+3)%4+1);
                currentIdx = (currentIdx+1) % 4;
                cond.notify_all();
                lck.unlock();
            }
        }, i);
        threads.emplace_back(std::move(t));
    }
    for (auto& t : threads) {
        t.join();
    }
    return 0;
}