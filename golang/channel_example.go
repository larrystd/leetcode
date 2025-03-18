package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	// 利用channel等待子routine执行完
	done := make(chan bool)
	go func() {
		done <- true
	}()
	<-done // 等待任务完成

	// 生产者消费者队列
	var wg sync.WaitGroup
	wg.Add(2)
	jobs := make(chan int, 100)
	// 生产者
	go func() {
		defer wg.Done()
		for i := 0; i < 10; i++ {
			jobs <- i
		}
		close(jobs)
	}()
	// 消费者
	go func() {
		defer wg.Done()
		for job := range jobs {
			fmt.Println(job)
		}
	}()
	wg.Wait()
	// 超时机制
	ch := make(chan bool)
	select {
	case res := <-ch:
		fmt.Println(res)
	case <-time.After(2 * time.Second):
		fmt.Println("超时")
	}
}
