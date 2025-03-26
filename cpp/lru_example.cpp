#include <list>
#include <unordered_map>
#include <iostream>

/*
std::list 双向链表
.front() .back() 头尾部元素
.push_front() .push_back() .pop_front() .pop_back()
.emplace_front() .emplace_back()
.erase(pos) 删除指定位置的元素, .remove(val) 删除指定值的元素

查找
auto iter = xx.find(key); if iter != xx.end() {}

移动位置
std::list::splice
void splice(const_iterator pos, list& other, const_iterator it);
将 other 链表中迭代器 it 指向的单个元素移动到当前链表的 pos 位置前。

std::pair<R, U> .first .second
使用迭代器描述指针
std::pair<int, int>>::iterator


unordered_map
operator[](const Key&) 通过键访问值（若键不存在则插入默认值）
at(const Key&) 通过键访问值（键不存在时抛出异常）

empty() .size()

insert(const value_type&) 插入键值对
template<class... Args> emplace(Args&&...)

size_t erase(const Key&) 删除指定健的元素
void clear() 清空

count(const Key&) 统计key出现的次数（判断key是否存在

迭代器失效
插入元素：可能导致rehash，所有迭代器失效
​删除元素：仅被删元素的迭代器失效

为了避免迭代器失效, 插入元素后可以重新开始从map::begin()处遍历，不使用前面的迭代器

    std::unordered_map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};

    // 使用迭代器遍历
    for (auto it = myMap.begin(); it != myMap.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    // 插入新元素，可能导致 rehash
    myMap[4] = "four";

    // 重新获取迭代器并继续遍历
    for (auto it = myMap.begin(); it != myMap.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }
*/

class LRUCache {
private:
    int capacity;
    std::list<std::pair<int, int>> cache; // 双向链表存储键值对，头部为最近访问
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> keyMap; // 哈希表映射键到链表节点

public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        auto it = keyMap.find(key);
        if (it == keyMap.end()) return -1; // 键不存在
        
        // 将访问的节点移动到链表头部
        cache.splice(cache.begin(), cache, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = keyMap.find(key);
        if (it != keyMap.end()) { // 键已存在
            it->second->second = value; // 更新值
            cache.splice(cache.begin(), cache, it->second); // 移动至头部
            return;
        }
        
        if (keyMap.size() >= capacity) { // 容量已满，淘汰尾部
            int lruKey = cache.back().first;
            keyMap.erase(lruKey);
            cache.pop_back();
        }
        
        // 插入新键值对到头部并更新哈希表
        cache.emplace_front(key, value);
        keyMap[key] = cache.begin();
    }
};

int main() {
    LRUCache cache(2);
    
    cache.put(1, 1);          // 缓存: {1=1}
    cache.put(2, 2);          // 缓存: {2=2, 1=1}
    std::cout << cache.get(1) << std::endl; // 输出 1，缓存: {1=1, 2=2}
    
    cache.put(3, 3);          // 淘汰键2，缓存: {3=3, 1=1}
    std::cout << cache.get(2) << std::endl; // 输出 -1（未找到）
    
    cache.put(4, 4);          // 淘汰键1，缓存: {4=4, 3=3}
    std::cout << cache.get(1) << std::endl; // 输出 -1
    std::cout << cache.get(3) << std::endl; // 输出 3
    std::cout << cache.get(4) << std::endl; // 输出 4
}