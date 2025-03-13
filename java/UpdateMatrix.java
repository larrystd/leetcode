import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;


/*
 * Arrays.fill 函数
 * java.util.Arrays 类提供了一系列静态方法用于操作数组
 * Arrays.toString([]) 转字符串
 * Arrays.sort(arr); // 升序排序
 * Arrays.binarySearch(arr, 5); 
 * Arrays.fill(arr, 10); // 所有元素填充为10
 * int[] copy1 = Arrays.copyOf(arr, 3); // 复制前3个元素 -> [1, 2, 3]
 * List<String> list = Arrays.asList(arr); // 数组转列表
 * 
 * Deque 容器
 * Deque（Double Ended Queue）是 Java 集合框架中的一个接口，继承自 Queue，支持在队列的 ​头部 和 ​尾部 高效插入、删除和查看元素。
 * ArrayDeque：基于数组实现，性能高（推荐大多数场景使用）
 * LinkedList：基于链表实现，支持快速插入删除，但内存开销更大。
 * 
 * offer(x) 队尾插入元素
 * poll() 队头拿元素
 * peek() 查看队头元素
 * 
 * offerFirst(E e)	头部插入元素
 * offerLast(E e)	尾部插入元素
 * 
 * pollFirst()	删除并返回头部元素
 * pollLast()	删除并返回尾部元素
 * 
 * peekFirst()	查看头部元素
 * peekLast()	查看尾部元素
 */

class UpdateMatrix {
    public int[][] updateMatrix(int[][] mat) {
        int m = mat.length, n = mat[0].length;
        int[][] ans = new int[m][n];
        for (int[] row : ans) {
            Arrays.fill(row, -1);
        }
        Deque<int[]> q = new ArrayDeque<>();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 0) {
                    q.offer(new int[] {i, j});
                    ans[i][j] = 0;
                }
            }
        }
        int[] dirs = {-1, 0, 1, 0, -1};
        while (!q.isEmpty()) {
            int[] p = q.poll();
            int i = p[0], j = p[1];
            for (int k = 0; k < 4; ++k) {
                int x = i + dirs[k], y = j + dirs[k + 1];
                if (x >= 0 && x < m && y >= 0 && y < n && ans[x][y] == -1) {
                    ans[x][y] = ans[i][j] + 1;
                    q.offer(new int[] {x, y});
                }
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        int[][] mat = {
            {0,0,0},
            {0,1,0},
            {1,1,1}
        };
        UpdateMatrix s = new UpdateMatrix();
        int[][] ans = s.updateMatrix(mat);
        for (int[] row : ans) {
            for (int x : row) {
                System.out.print(x + " ");
            }
            System.out.println();
        }
    }
}