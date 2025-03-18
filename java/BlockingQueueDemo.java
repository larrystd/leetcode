import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

/*
 * java BlockingQueue 结构, 
 * 一个线程安全的队列接口，用于在多线程环境中实现生产者-消费者模式。
 * 支持在队列满或空时阻塞线程，直到条件满足。
 * 
 * 当队列满时，插入操作put()会阻塞；队列空时，取出操作take()会阻塞。
 * 
 * offer(e, timeout, unit)和poll(timeout, unit)方法， 相比put/take阻塞等待， offer和poll返回状态(成功或失败)
 * 
 * 
 * Runnable 接口, 只包含一个 run() 方法，没有返回值
 * Runnable 用来定义任务逻辑，Thread 负责执行任务。Runnable作为thread的参数
 * 
 * Thread对象, 传入Runnable 对象
 * start()	启动线程，进入 RUNNABLE 状态，由JVM调用 run()。
 * run()	线程实际执行的任务逻辑，直接调用不会启动新线程。
 * join() / join(ms)	等待该线程终止（或超时），常用于同步多个线程的执行顺序。
 * interrupt()	中断线程，设置中断标志，触发 InterruptedException（若在阻塞中）。
 * 
 * Thread 静态函数, 
 * sleep(long millis) 使当前线程进入休眠（TIMED_WAITING 状态），不释放锁。
 * yield() 提示线程调度器让出当前线程的CPU时间片，但无强制约束（实际是否让出由JVM决定）。
 * currentThread() 获取当前正在执行的线程对象。
 * interrupted() 检查当前线程是否被中断，并清除中断状态。
 * JAVA InterruptedException 是当线程在阻塞操作（如 sleep(), wait(), join()）中被中断时抛出的异常
 */
public class BlockingQueueDemo {
    public static void main(String[] args) {
        BlockingQueue<Integer> queue = new ArrayBlockingQueue<>(10); // 容量=10

        // 生产者
        Runnable producer = () -> {
            try {
                for (int i = 0; i < 20; i++) {
                    queue.put(i); // 队列满时自动阻塞
                    System.out.println("生产: " + i);
                    Thread.sleep(100);
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        };

        // 消费者
        Runnable consumer = () -> {
            try {
                while (true) {
                    Integer num = queue.take(); // 队列空时自动阻塞
                    System.out.println("消费: " + num);
                    Thread.sleep(200);
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        };

        // 启动线程
        new Thread(producer).start();
        new Thread(consumer).start();
    }
}