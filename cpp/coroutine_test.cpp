#include <future>
#include <coroutine>

struct task {
    struct promise_type {
        std::promise<int> result_;  // 用于存储协程结果
        
        // 创建并返回 task 对象
        task get_return_object() {
            return task{result_.get_future()}; // 将 future 与 promise 绑定
        }
        
        // 控制协程的挂起行为
        std::suspend_never initial_suspend() { return {}; }  // 不挂起，立即执行
        std::suspend_never final_suspend() noexcept { return {}; } // 执行完后不挂起
        
        // 处理协程返回值
        void return_value(int val) { 
            result_.set_value(val); // 将结果存入 promise
        }
        
        // 处理未捕获的异常（示例未实现）
        void unhandled_exception() { 
            /* 此处应处理异常，例如：result_.set_exception(std::current_exception()); */ 
        }
    };

    std::future<int> fut_; // 供外部获取结果的 future
};

task async_compute() {
    co_return 42; 
}

int main() {
    task t = async_compute(); // 协程立即执行
    int result = t.fut_.get(); // 获取结果
    printf ("result = %d\n", result);
    return 0;
}