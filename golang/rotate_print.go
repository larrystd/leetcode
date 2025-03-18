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

func main() {
	var (
		mu           sync.Mutex
		currentRound int
		currentStep  int
	)

	cond := sync.NewCond(&mu)

	// 创建4个协程，每个对应一个步骤
	for step := 0; step < 4; step++ {
		go func(s int) {
			for {
				mu.Lock()
				// 等待直到当前步骤匹配自己的步骤
				for currentStep != s {
					cond.Wait()
				}

				// 计算并打印当前数字
				num := (currentRound+currentStep)%4 + 1
				fmt.Printf("%d ", num)

				// 更新步骤和轮次
				currentStep++
				if currentStep >= 4 {
					currentStep = 0
					currentRound++
				}

				// 唤醒所有等待的协程
				cond.Broadcast()
				mu.Unlock()
			}
		}(step)
	}

	// 保持主协程运行
	select {}
}
