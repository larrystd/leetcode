/**
 * Given an array of integers, return indices of the two numbers such that
 * they add up to a specific target.
 *
 * You may assume that each input would have exactly one solution, and
 * you may not use the same element twice.
 * 你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。
 * Example:
 * Given nums = [2, 7, 11, 15], target = 9,
 *
 * Because nums[0] + nums[1] = 2 + 7 = 9,
 * return [0, 1].
 */


import java.util.HashMap;
import java.util.Map;

/*
 * java Map的定义, Map<Integer, Integer> xx = new HashMap<>()
 * Map的常用函数, containsKey(x)判断key存在, get(x) 根据key获得value, put(x,y) 插入key,value对
 * <> 称为 ​**"钻石操作符"**, Diamond Operator，在泛型时可以简化类型声明
 * 
 * java 数组只存在堆内存，使用int[] nums定义类型, 使用new int[]{}创建对象
 * java 对象只以引用的形式存在, int[]数组具有length属性表示长度
 */

public class TwoSum1 {

    public int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> foundSet = new HashMap<>();

        int[] returns = new int[2];
        for (int i = 0; i < nums.length; i++) {
            Integer now = nums[i];
            Integer lookingfor = target - now;
            if (foundSet.containsKey(lookingfor)) {
                returns[0] = foundSet.get(lookingfor);
                returns[1] = i;
                return returns;
            } else {
                foundSet.put(now, i);
            }
        }
        return returns;
    }

    public static void main(String[] args) {
        TwoSum1 ts = new TwoSum1();
        int[] ret = ts.twoSum(new int[]{2, 7, 11, 15}, 9);
        for (int i = 0; i < ret.length; i++) {
            System.out.println(ret[i]);
        }
        ret = ts.twoSum(new int[]{1, 2, 3}, 5);
        for (int i = 0; i < ret.length; i++) {
            System.out.println(ret[i]);
        }
        
    }

}