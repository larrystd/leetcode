from collections import OrderedDict


'''
collections.OrderedDict
OrderedDict会记录键值对的插入顺序, 迭代时按此顺序返回。

可通过方法将元素移动到开头或结尾，普通字典无法做到。
od.move_to_end('a')     # 将键'a'移到末尾
popitem(last=True) 弹出元素, last=True 弹出最后插入的键值对, last=False 弹出最先插入的键值对
'''
class LRUCache:
    def __init__(self, capacity: int):
        self.cache = OrderedDict()
        self.capacity = capacity

    def get(self, key: int) -> int:
        if key not in self.cache:
            return -1
        # 将访问的键移到字典末尾表示最近使用
        self.cache.move_to_end(key)
        return self.cache[key]

    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            # 更新已存在的键值并移到末尾
            self.cache.move_to_end(key)
        else:
            if len(self.cache) >= self.capacity:
                # 淘汰最久未使用的键（字典第一个键）
                self.cache.popitem(last=False)
        self.cache[key] = value

# 示例用法
cache = LRUCache(2)
cache.put(1, 1)
cache.put(2, 2)
print(cache.get(1))    # 输出 1
cache.put(3, 3)        # 淘汰键2
print(cache.get(2))    # 输出 -1