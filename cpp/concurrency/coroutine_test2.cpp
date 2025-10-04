#include <coroutine>
#include <iostream>
#include <thread>

// 1. 定义协程返回类型 Task
struct Task {
    // 协程的承诺类型（必须命名为 promise_type）
    struct promise_type {
        Task get_return_object() { 
            std::cout << "创建协程对象\n";
            return Task{std::coroutine_handle<promise_type>::from_promise(*this)}; 
        }
        
        // 初始挂起策略：协程创建后立即挂起
        std::suspend_always initial_suspend() { 
            std::cout << "初始化挂起\n";
            return {}; 
        }
        
        // 最终挂起策略：协程结束后保持挂起状态
        std::suspend_always final_suspend() noexcept { 
            std::cout << "最终挂起\n";
            return {}; 
        }
        
        void return_void() { 
            std::cout << "协程返回\n"; 
        }
        
        void unhandled_exception() { 
            std::terminate(); 
        }
    };

    // 协程句柄
    std::coroutine_handle<promise_type> handle;

    // 构造函数
    explicit Task(std::coroutine_handle<promise_type> h) : handle(h) {}

    // 析构时自动销毁协程
    ~Task() {
        if (handle) handle.destroy();
        std::cout << "销毁协程\n";
    }

    // 恢复协程执行
    void resume() {
        if (!handle.done()) {
            std::cout << "恢复协程执行\n";
            handle.resume();
        }
    }
};

// 2. 定义可等待对象（Awaiter）
struct AsyncOperation {
    bool await_ready() const { 
        std::cout << "检查是否就绪\n";
        return false; // 总是挂起
    }
    
    void await_suspend(std::coroutine_handle<> h) {
        std::cout << "开始异步操作...\n";
        // 模拟异步操作（例如网络请求）
        std::thread([h] {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "异步操作完成\n";
            h.resume(); // 完成后恢复协程
        }).detach();
    }
    
    void await_resume() {
        std::cout << "处理操作结果\n";
    }
};

// 3. 协程函数定义
Task my_coroutine() {
    std::cout << "协程开始执行\n";
    
    co_await AsyncOperation{}; // 等待异步操作
    
    std::cout << "继续执行协程体\n";
    
    co_await std::suspend_always{}; // 主动挂起
    
    std::cout << "协程最终阶段\n";
}

// 4. 主函数
int main() {
    std::cout << "===== 协程生命周期演示 =====\n";
    
    Task task = my_coroutine(); // 此时协程处于挂起状态
    std::cout << "\n首次恢复协程:\n";
    // task.resume();             // 第一次恢复
    sleep(5);
    std::cout << "\n二次恢复协程:\n";
    // task.resume();             // 第二次恢复
    
    std::cout << "\n程序结束\n";
    return 0;
}