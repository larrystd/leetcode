
/*
 * synchronized 有锁对象的概念
 * public synchronized void withdraw(int amount) 锁对象为this，同一实例的多个线程调用 函数 会互斥，不同实例不会
 * 
 * public static synchronized void staticMethod() 锁对象为class, 所以调用该类函数的多个线程会互斥
 * 
 * private final Object lock = new Object(); // 锁对象
 * synchronized (lock)（锁对象 = 显式指定对象）, 使用相同锁对象的不同线程会互斥
 */

public class SyncTest {
    private int balance = 100;

    // 同步实例方法（锁对象为当前实例 this）
    public synchronized void withdraw(int amount) {
        if (balance >= amount) {
            System.out.println(Thread.currentThread().getName() + " 取款 " + amount);
            balance -= amount;
        }
    }

    // 同步静态方法（锁对象为类对象 SyncMethodDemo.class）
    public static synchronized void staticMethod() {
        System.out.println("静态方法同步");
    }

    public static void main(String[] args) {
        SyncTest account = new SyncTest();

        // 创建两个线程并发取款
        new Thread(() -> account.withdraw(50)).start();
        new Thread(() -> account.withdraw(60)).start();

        Object lockA = new Object();
        Object lockB = new Object();

        // 线程1：使用 lockA
        new Thread(() -> {
            synchronized (lockA) {
                System.out.println("Thread1 进入 lockA");
                try { Thread.sleep(2000); } catch (InterruptedException e) {}
            }
        }).start();

        // 线程2：使用 lockA（会阻塞）
        new Thread(() -> {
            synchronized (lockA) {
                System.out.println("Thread2 进入 lockA");
            }
        }).start();

        // 线程3：使用 lockB（不会阻塞）
        new Thread(() -> {
            synchronized (lockB) {
                System.out.println("Thread3 进入 lockB");
            }
        }).start();
    }
}