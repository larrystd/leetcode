import java.util.function.Function;


/*
 * java的java.util.function.Function 和Runnable
 * Runnable 表示一个无参数、无返回值的任务（void 类型）
 * 常用于定义异步任务（如线程池、Thread 类）
 * 
 * Function<T, R> 接口，表示一个接受一个输入参数（类型 T）并返回结果（类型 R）的函数
 * 通过@FunctionalInterface 自定义Function接口
 */
@FunctionalInterface
interface TriFunction<A, B, C, R> {
    R apply(A a, B b, C c);
}

public class ClosureTest {
    

    public static void main(String[] args) {
        int base = 10; // 必须为 effectively final
        Function<Integer, Integer> addBase = x -> x + base; // 捕获 base

        System.out.println(addBase.apply(5)); // 输出 15
        // base = 20; // 若取消注释，会导致编译错误（base 不再是 effectively final）
    
        TriFunction<String, Integer, Boolean, String> format = 
        (s, i, b) -> s + "-" + i + "-" + b;
    
        String output = format.apply("Data", 100, true); // "Data-100-true"
        System.out.println(output);
    }
}
