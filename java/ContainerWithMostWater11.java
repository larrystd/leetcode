/**
 * Given n non-negative integers a1, a2, ..., an, where each represents a point
 * at coordinate (i, ai). n vertical lines are drawn such that the two endpoints
 * of line i is at (i, ai) and (i, 0). Find two lines, which together with
 * x-axis forms a container, such that the container contains the most water.
 * 
 * 
 * Note: You may not slant the container and n is at least 2.
 */

/* java Math库, 所有方法均为静态方法
 * 常用, Math.abs(a), Math.max(a, b), Math.min(a, b), Math.sqrt(a), Math.pow(a, b)
 */
public class ContainerWithMostWater11 {
    public int maxArea(int[] height) {
        int res = 0;
        int n = height.length;
        int left = 0;
        int right = n-1;
        while (left < right) {
            res = Math.max(res, Math.min(height[left], height[right]) * (right - left));
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return res;
    }

    public static void main(String[] args) {
        int[] arr = new int[]{1,8,6,2,5,4,8,3,7};
        ContainerWithMostWater11 l1 = new ContainerWithMostWater11();
        int res = l1.maxArea(arr);
        System.out.println(res);
    }

}