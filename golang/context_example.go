package main

import (
	"context"
	"fmt"
	"time"
)

func main() {
	// 父parentCtx作为参数传入多个子context,
	// 当 context ​未被取消时，<-ctx.Done() 会阻塞当前 goroutine
	// 父执行cancel，子routine的<-ctx.Done() 会解除阻塞
	parentCtx, parentCancel := context.WithCancel(context.Background())
	defer parentCancel()

	// 创建多个子Context
	childCtx1, _ := context.WithCancel(parentCtx)
	childCtx2, _ := context.WithCancel(parentCtx)

	go func() {
		<-childCtx1.Done()
		fmt.Println("子任务1终止")
	}()

	go func() {
		<-childCtx2.Done()
		fmt.Println("子任务2终止")
	}()

	// 父级取消触发所有子级取消
	parentCancel()
	time.Sleep(100 * time.Millisecond)
}
