#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>

template <typename T>
class ThreadSafeQueue {
public:
    explicit ThreadSafeQueue(size_t max_size = 0) 
        : max_size_(max_size), stop_(false) {}

    // 将数据推入队列（阻塞直到成功）
    bool push(T value) {
        std::unique_lock<std::mutex> lock(mutex_);
        // 等待队列非满或停止信号
        not_full_.wait(lock, [this]() { 
            return stop_ || (max_size_ == 0 || queue_.size() < max_size_); 
        });
        if (stop_) return false;
        queue_.push(std::move(value));
        not_empty_.notify_one();
        return true;
    }

    // 从队列取出数据（阻塞直到成功）
    bool pop(T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        // 等待队列非空或停止信号
        not_empty_.wait(lock, [this]() { 
            return stop_ || !queue_.empty(); 
        });
        if (stop_ && queue_.empty()) return false;
        value = std::move(queue_.front());
        queue_.pop();
        not_full_.notify_one();
        return true;
    }

    // 安全停止队列（唤醒所有等待线程）
    void stop() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            stop_ = true;
        }
        not_empty_.notify_all();
        not_full_.notify_all();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

private:
    mutable std::mutex mutex_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
    std::queue<T> queue_;
    size_t max_size_;  // 0表示无限制
    bool stop_;
};

// 生产数据函数
void producer(ThreadSafeQueue<int>& queue, int id, int count) {
    for (int i = 0; i < count; ++i) {
        if (!queue.push(id * 1000 + i)) {
            std::cout << "Producer " << id << " exiting\n";
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

// 消费数据函数
void consumer(ThreadSafeQueue<int>& queue, int id) {
    while (true) {
        int value;
        if (!queue.pop(value)) {
            std::cout << "Consumer " << id << " exiting\n";
            break;
        }
        std::cout << "Consumer " << id << " processed: " << value 
                  << " (qsize: " << queue.size() << ")\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    const int PRODUCERS = 3;
    const int CONSUMERS = 2;
    const int MAX_QUEUE_SIZE = 5;
    const int ITEMS_PER_PRODUCER = 10;

    ThreadSafeQueue<int> queue(MAX_QUEUE_SIZE);

    // 启动生产者线程
    std::vector<std::thread> producers;
    for (int i = 0; i < PRODUCERS; ++i) {
        producers.emplace_back(producer, std::ref(queue), i+1, ITEMS_PER_PRODUCER);
    }

    // 启动消费者线程
    std::vector<std::thread> consumers;
    for (int i = 0; i < CONSUMERS; ++i) {
        consumers.emplace_back(consumer, std::ref(queue), i+1);
    }

    // 等待生产者完成
    for (auto& t : producers) {
        t.join();
    }

    // 停止队列并唤醒所有消费者
    queue.stop();

    // 等待消费者退出
    for (auto& t : consumers) {
        t.join();
    }

    return 0;
}