import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.CountDownLatch;

/*
 * java.util.concurrent 库
 * 
 * 原子类
 * java.util.concurrent.AtomicInteger
 * 
 * java.util.concurrent.ConcurrentHashMap
 * 并发安全map，分段锁技术
 * java.util.concurrent,BlockingQueue
 * 阻塞队列
 * 
 * 
 * java.util.concurrent.Future，接收异步任务结果
 * Future<Integer> future = executor.submit(() -> {
 *      Thread.sleep(1000);
 *      return 42;
 * });
 * Integer result = future.get(); // 阻塞获取结果
 * 
 */

public class WaitGroup {
    public static void main(String[] args) throws InterruptedException {
        List<Thread> threads = new ArrayList<>();
        
        // 创建并启动 3 个子线程
        for (int i = 0; i < 3; i++) {
            Thread t = new Thread(() -> {
                System.out.println(Thread.currentThread().getName() + " 开始执行");
                try {
                    Thread.sleep(2000); // 模拟耗时操作
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println(Thread.currentThread().getName() + " 执行完毕");
            });
            threads.add(t);
            t.start();
        }

        // 主线程等待所有子线程完成
        for (Thread t : threads) {
            t.join(); // 阻塞直到线程终止
        }
        
        System.out.println("所有子线程执行完毕，主线程继续");

        // 使用CountDownLatch工具
        final int THREAD_COUNT = 3;
        CountDownLatch latch = new CountDownLatch(THREAD_COUNT);

        for (int i = 0; i < THREAD_COUNT; i++) {
            new Thread(() -> {
                try {
                    System.out.println(Thread.currentThread().getName() + " 开始工作");
                    Thread.sleep(1500);
                    System.out.println(Thread.currentThread().getName() + " 完成工作");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                } finally {
                    latch.countDown(); // 计数器减1
                }
            }).start();
        }

        latch.await(); // 阻塞直到计数器归零
        System.out.println("所有子线程任务完成，主线程继续执行");
    }
}
