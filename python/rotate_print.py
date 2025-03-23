import threading
import time

'''
python的Lock(), Condition() 都在threading库里

threading.Thread用于创建线程, 参数和C++的thread完全一致, func和args

with self.cond:  等价于std::unique_lock<std::mutex> lck; cond.wait(lck, ...)
mu.lock xxx cond.wait()
lock.lock() cond.await()


python lambda变量捕获, 延迟绑定
funcs = []
for i in range(3):
    funcs.append(lambda: print(i))  # 所有 lambda 捕获变量名 i
    #  funcs.append(lambda x=i: print(x))  # 更改为立即绑定

for f in funcs:
    f()  # 输出 2 2 2 （i 的最终值）
    
python允许读取全局变量，修改需用 global：
'''

class RotatePrint:
    def __init__(self):
        self.lock = threading.Lock()
        self.cond = threading.Condition(self.lock)
        self.current_idx = 0
        self.running = True

    def print_numbers(self, idx):
        while self.running:
            with self.cond:
                while idx != self.current_idx:
                    self.cond.wait()

                print(f"{idx % 4 + 1} {((idx + 1) % 4) + 1} {((idx + 2) % 4) + 1} {((idx + 3) % 4) + 1}")
                self.current_idx = (self.current_idx + 1) % 4
                self.cond.notify_all()

    def start_threads(self):
        threads = []
        for i in range(4):
            thread = threading.Thread(target=self.print_numbers, args=(i,))
            threads.append(thread)
            thread.start()

        # Let the threads run for a while
        time.sleep(5)

        # Signal threads to stop
        with self.lock:
            self.running = False
            self.cond.notify_all()

        # Wait for all threads to finish
        for thread in threads:
            thread.join()

if __name__ == "__main__":
    rotate_print = RotatePrint()
    rotate_print.start_threads()