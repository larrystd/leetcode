// 并发程序的关键是，
// 1. 明确每个线程要做什么
// 2. 明确线程安全数据结构怎样加锁保护
// 3. 明确怎么做线程之间的通信，包括启动、停止、数据交互

// 既然有协作，就会出现 线程可能相互等待，需要a做完b才能做。这个过程需要避免死锁

package main

import (
	"fmt"
	"sync"
)

/*
 * golang 的锁和条件变量都比较原始
 * mutex定义，mu sync.Mutex，mu.Lock, mu.Unlock
 * cond定义, 用锁的指针做参数, sync.NewCond(&mu), 结合for循环等待, for currentIdx != idx { cond.Wait() }
 * 等待时会阻塞释放锁，直到被唤醒
 * cond.Broadcast() 唤醒所有协程, cond.Broadcast()唤醒一个协程(往往唤醒一个协程是不够的)
 */
func main() {
	var (
		mu         sync.Mutex
		currentIdx int
	)
	cond := sync.NewCond(&mu)

	for i := 0; i < 4; i++ {
		go func(idx int) {
			for {
				mu.Lock()
				for currentIdx != idx {
					cond.Wait()
				}
				fmt.Printf("%d %d %d %d\n", idx%4+1, (idx+1)%4+1, (idx+2)%4+1, (idx+3)%4+1)
				currentIdx = (currentIdx + 1) % 4
				cond.Broadcast()
				mu.Unlock()
			}

		}(i)
	}
	select {}
}
