import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;
import java.util.ArrayList;
import java.util.List;

/*
 * java 锁
 * ReentrantLock, 可重入锁, 同一个线程可以多次获取同一个锁，而不会导致死锁。
 * ReentrantLock.newCondition(), 条件变量
 * 
 * 操作条件变量await()之前需要申请锁, 进入await时会释放锁，等待被唤醒
 * 
 * java lambda闭包捕获规则
 * ​值捕获：捕获变量的当前值（编译时生成副本）
 * ​对象引用：捕获引用地址（可以修改对象内容，但不能重新赋值）
 * 
 * golang闭包捕获规则
 * ​所有变量: 通过引用隐式捕获(无需声明)
 * ​可修改性：直接修改原始变量（无限制）
 * 
 * C++ lambda表示闭包捕获规则
 * [=], [var] 值捕获
 * [&], [&var] 引用捕获
 * 
 * Python, 
 * Python lambda ​不立即捕获变量值，而是记录变量名，在 ​调用时动态查找 当前作用域的变量值
 * lambda 表达式不能通过赋值语句修改外部变量
 */

public class RotatePrint {
    private static final ReentrantLock lock = new ReentrantLock();
    private static final Condition cond = lock.newCondition();
    private static int currentIdx = 0;

    public static void main(String[] args) {
        List<Thread> threads = new ArrayList<>();

        for (int i = 0; i < 4; i++) {
            final int idx = i;
            Thread t = new Thread(() -> {
                while (true) {
                    lock.lock();
                    try {
                        while (idx != currentIdx) {
                            cond.await();
                        }

                        System.out.printf("%d %d %d %d\n", idx % 4 + 1, (idx + 1) % 4 + 1, (idx + 2) % 4 + 1, (idx + 3) % 4 + 1);
                        currentIdx = (currentIdx + 1) % 4;
                        cond.signalAll();
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                        System.out.println("Thread interrupted");
                    } finally {
                        lock.unlock();
                    }
                }
            });
            threads.add(t);
        }

        for (Thread t : threads) {
            t.start();
        }

        // To prevent the main thread from exiting immediately, we can join the threads
        for (Thread t : threads) {
            try {
                t.join();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                System.out.println("Main thread interrupted");
            }
        }
    }
}
