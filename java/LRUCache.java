import java.util.LinkedHashMap;
import java.util.Map;


/*
LinkedHashMap
accessOrder 控制顺序, 默认为false。即
​遍历顺序与元素的插入顺序一致。
LinkedHashMap<String, Integer> map = new LinkedHashMap<>();
map.put("A", 1);
map.put("B", 2);
map.put("C", 3);
System.out.println(map.keySet()); // 输出 [A, B, C]

如果 accessOrder 为 true，则

​遍历顺序按元素被访问的先后排序，最近访问的排在末尾。即LRU
​触发访问的操作：
get(key)
put(key, value)（更新已存在的键）
 */
public class LRUCache<K, V> extends LinkedHashMap<K, V> {
    private final int maxCapacity;

    public LRUCache(int maxCapacity) {
        // 第三个参数为accessOrder：true表示按访问顺序排序，false表示按插入顺序
        super(maxCapacity, 0.75f, true);
        this.maxCapacity = maxCapacity;
    }

    @Override
    protected boolean removeEldestEntry(Map.Entry<K, V> eldest) {
        // 当元素数量超过容量时，移除最久未使用的元素
        return size() > maxCapacity;
    }

    public static void main(String[] args) {
        LRUCache<Integer, String> cache = new LRUCache<>(2);
        cache.put(1, "A");
        cache.put(2, "B");
        cache.get(1);       // 访问键1，使其成为最近使用的
        cache.put(3, "C");  // 插入新键3，触发淘汰键2
        System.out.println(cache); // 输出: {1=A, 3=C}
    }
}