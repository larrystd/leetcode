package main

import (
	"fmt"
	"time"
)

// golang的channel是天然的线程安全队列

func producer(ch chan<- int) {
	for i := 0; i < 5; i++ {
		ch <- i
		fmt.Printf("produce %d\n", i)
		time.Sleep(100 * time.Millisecond)
	}
	close(ch)
}

func consumer(ch <-chan int) {
	for num := range ch {
		fmt.Printf("consume %d\n", num)
		time.Sleep(200 * time.Millisecond)
	}
}

func main() {
	ch := make(chan int, 3)
	go producer(ch)
	consumer(ch)
}
