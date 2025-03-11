import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Map;
import java.util.HashMap;

/*
 * java Deque的定义, Deque<Integer> stk = new ArrayDeque<>()
 * Deque的常用函数, push(x), pop(), peek()
 * 
 * java Map的定义, Map<Integer, Integer> xx = new HashMap<>()
 * Map的常用函数, containsKey(x)判断key存在, get(x) 根据key获得value, put(x,y) 插入key,value对
 * getOrDefault(x, y) 如果key存在, 返回value, 否则返回y
 */

class NextGreaterElement {
    public int[] nextGreaterElement(int[] nums1, int[] nums2) {
        Deque<Integer> stk = new ArrayDeque<>();
        int m = nums1.length, n = nums2.length;
        Map<Integer, Integer> d = new HashMap<>(n);

        for (int i = n-1; i >= 0; --i) {
            int x = nums2[i];
            while (!stk.isEmpty() && stk.peek() < x) {
                stk.pop();
            }
            if (!stk.isEmpty()) {
                d.put(x, stk.peek());
            }
            stk.push(x);
        }

        int[] ans = new int[m];
        for (int i = 0; i < m; ++i) {
            ans[i] = d.getOrDefault(nums1[i], -1);
        }
        return ans;
    }

    public static void main(String[] args) {
        NextGreaterElement nge = new NextGreaterElement();
        int[] ret = nge.nextGreaterElement(new int[]{4,1,2}, new int[]{1,3,4,2});
        for (int i = 0; i < ret.length; i++) {
            System.out.println(ret[i]);
        }
    }
}