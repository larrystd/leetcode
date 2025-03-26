package main

import (
	"container/list"
	"fmt"
)

/*
container/list
创建链表list.New()
l.PushFront(1) 头部插入
l.PushBack(1) 尾部插入
l.MoveToFront(e4) 元素移动到头部
l.MoveAfter(e2, e4) // 将e2移到e4后
l.Len() 返回链表长度

*list.Element 链表元素
e.Next(), Prev() 获得下一个/上一个元素
e.Value() 链表元素值
for e := l.Front(); e != nil; e = e.Next() { 遍历链表

map
m1 := make(map[string]int)
增删改查
m["apple"] = 5
if value, ok := m["banana"]; ok
delete(m, "apple")

遍历
for key, value := range m

接口interface
接口断言, 类型转换any.(type), （Type Assertion）检查接口值的底层具体类型或将其转换为其他接口
entry := elem.Value.(*entry)
value := i.(Type)          // 直接断言，失败会panic
value, ok := i.(Type)      // 安全断言，ok为bool结果
*/
type LRUCache struct {
	capacity int                      // 最大容量
	list     *list.List               // 双向链表维护访问顺序
	cache    map[string]*list.Element // 哈希表快速查找节点
}

// entry 存储键值对的结构
type entry struct {
	key   string
	value interface{}
}

func NewLRUCache(capacity int) *LRUCache {
	return &LRUCache{
		capacity: capacity,
		list:     list.New(),
		cache:    make(map[string]*list.Element),
	}
}

func (lru *LRUCache) Get(key string) (interface{}, bool) {
	if elem, ok := lru.cache[key]; ok {
		lru.list.MoveToFront(elem) // 移动到链表头部
		return elem.Value.(*entry).value, true
	}
	return nil, false
}

// 添加缓存值
func (lru *LRUCache) Put(key string, value interface{}) {
	// 如果键已存在，更新值并移动到头部
	if elem, ok := lru.cache[key]; ok {
		lru.list.MoveToFront(elem)
		elem.Value.(*entry).value = value
		return
	}

	// 如果容量已满，淘汰最久未使用的元素（链表尾部）
	if lru.list.Len() >= lru.capacity {
		tail := lru.list.Back()
		if tail != nil {
			delete(lru.cache, tail.Value.(*entry).key)
			lru.list.Remove(tail)
		}
	}

	// 添加新元素到链表头部并记录到哈希表
	elem := lru.list.PushFront(&entry{key, value})
	lru.cache[key] = elem
}

// 打印缓存内容（测试用）
func (lru *LRUCache) Print() {
	fmt.Print("Cache [")
	for elem := lru.list.Front(); elem != nil; elem = elem.Next() {
		entry := elem.Value.(*entry)
		fmt.Printf(" %s:%v", entry.key, entry.value)
	}
	fmt.Println(" ]")
}

// 使用示例
func main() {
	cache := NewLRUCache(3)

	cache.Put("a", 1)
	cache.Put("b", 2)
	cache.Put("c", 3)
	cache.Print() // 输出: Cache [ c:3 b:2 a:1 ]

	val, _ := cache.Get("b")
	fmt.Println("Get b:", val) // 输出: Get b: 2

	cache.Put("d", 4) // 触发淘汰，淘汰 a
	cache.Print()     // 输出: Cache [ d:4 b:2 c:3 ]

	cache.Put("c", 100) // 更新已有值
	cache.Print()       // 输出: Cache [ c:100 d:4 b:2 ]
}
