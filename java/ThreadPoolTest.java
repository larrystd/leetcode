import java.util.concurrent.*;

/*
 * ThreadPoolExecutor 对象参数，
 * corePoolSize 核心线程数（永不会回收）
 * maxPoolSize 最大线程数量
 * keepAliveTime，非核心线程空闲存活时间。下一个参数是存活时间单位
 * LinkedBlockingQueue<>(queueCapacity) 任务队列
 * 拒绝策略：当线程池和队列均满时，处理新提交任务的方式（如抛出异常、丢弃任务等）。
 * 
 * executor.execute() 提交 ​无返回值 的任务（Runnable 类型）
 * submit() 方法则用于提交 ​有返回值 的任务
 * 
 * 
 * catch (InterruptedException e) 的作用
 * 
 * 中断状态是线程的一个标志，调用 interrupt() 会设置中断标志。设置中断标志可以让线程安全终止（而非强制shutdown)
 * 线程处于阻塞状态，如Thread.sleep、wait、IO阻塞等情况时，调用interrupt方法后，sleep等方法将会抛出一个InterruptedException：
 * 抛出异常后会清除中断状态。若不恢复状态，上层代码无法检测到中断请求，可能导致线程无法正确停止。
 * 
 * 因此处理InterruptedException异常时，调用thread.interrupt() 恢复中断状态
 */

public class ThreadPoolTest {

    public static void main(String[] args) throws InterruptedException {
        // 自定义线程池配置
        int corePoolSize = 2;      // 核心线程数
        int maxPoolSize = 4;       // 最大线程数
        int queueCapacity = 2;     // 队列容量
        long keepAliveTime = 30;    // 非核心线程空闲存活时间（秒）

        // 创建线程池（手动配置参数）
        ThreadPoolExecutor executor = new ThreadPoolExecutor(
                corePoolSize,
                maxPoolSize,
                keepAliveTime,
                TimeUnit.SECONDS,
                new LinkedBlockingQueue<>(queueCapacity),  // 有界队列
                new ThreadPoolExecutor.CallerRunsPolicy()  // 拒绝策略：由提交任务的线程执行
        );

        // 提交 10 个任务（超出队列容量，触发拒绝策略）
        for (int i = 1; i <= 10; i++) {
            final int taskId = i;
            try {
                executor.execute(() -> {
                    try {
                        System.out.printf("[%s] 执行任务 %d (活动线程数: %d, 队列大小: %d)%n",
                                Thread.currentThread().getName(),
                                taskId,
                                executor.getActiveCount(),
                                executor.getQueue().size());
                        Thread.sleep(2000);  // 模拟任务耗时
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                });
            } catch (RejectedExecutionException e) {
                System.err.println("任务 " + taskId + " 被拒绝!");
            }
        }

        // 监控线程池状态（非必须，仅用于观察）
        ScheduledExecutorService monitor = Executors.newScheduledThreadPool(1);
        monitor.scheduleAtFixedRate(() -> {
            System.out.printf("[监控] 活动线程数: %d, 已完成任务: %d, 队列大小: %d%n",
                    executor.getActiveCount(),
                    executor.getCompletedTaskCount(),
                    executor.getQueue().size());
        }, 0, 1, TimeUnit.SECONDS);

        // 平缓关闭线程池
        executor.shutdown();
        if (!executor.awaitTermination(30, TimeUnit.SECONDS)) {
            executor.shutdownNow();  // 强制终止
        }
        monitor.shutdown();  // 关闭监控
    }
}