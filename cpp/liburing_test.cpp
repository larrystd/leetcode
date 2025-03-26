#include <liburing.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_PATH "example.txt"
#define BUFFER_SIZE 4096

int main() {
    struct io_uring ring;
    struct io_uring_sqe *sqe;
    struct io_uring_cqe *cqe;
    char buffer[BUFFER_SIZE];
    int fd, ret;

    // 初始化 io_uring
    ret = io_uring_queue_init(8, &ring, 0);
    if (ret < 0) {
        fprintf(stderr, "io_uring_queue_init: %s\n", strerror(-ret));
        return 1;
    }

    // 打开文件
    fd = open(FILE_PATH, O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // 获取一个提交队列条目
    sqe = io_uring_get_sqe(&ring);
    if (!sqe) {
        fprintf(stderr, "io_uring_get_sqe: No SQE available\n");
        return 1;
    }

    // 写操作
    const char *write_buffer = "Hello, liburing!";
    size_t write_len = strlen(write_buffer);
    io_uring_prep_write(sqe, fd, write_buffer, write_len, 0);

    // 提交写操作
    io_uring_submit(&ring);

    // 等待写操作完成
    ret = io_uring_wait_cqe(&ring, &cqe);
    if (ret < 0) {
        fprintf(stderr, "io_uring_wait_cqe: %s\n", strerror(-ret));
        return 1;
    }

    // 检查写操作结果
    if (cqe->res < 0) {
        fprintf(stderr, "Async write failed: %s\n", strerror(-cqe->res));
        return 1;
    } else {
        printf("Wrote %d bytes\n", cqe->res);
    }

    // 清理写操作完成事件
    io_uring_cqe_seen(&ring, cqe);

    // 获取一个新的提交队列条目
    sqe = io_uring_get_sqe(&ring);
    if (!sqe) {
        fprintf(stderr, "io_uring_get_sqe: No SQE available\n");
        return 1;
    }

    // 准备读操作
    io_uring_prep_read(sqe, fd, buffer, BUFFER_SIZE, 0);

    // 提交读操作
    io_uring_submit(&ring);

    // 等待读操作完成
    ret = io_uring_wait_cqe(&ring, &cqe);
    if (ret < 0) {
        fprintf(stderr, "io_uring_wait_cqe: %s\n", strerror(-ret));
        return 1;
    }

    // 检查读操作结果
    if (cqe->res < 0) {
        fprintf(stderr, "Async read failed: %s\n", strerror(-cqe->res));
    } else {
        printf("Read %d bytes: %.*s\n", cqe->res, cqe->res, buffer);
    }

    // 清理读操作完成事件
    io_uring_cqe_seen(&ring, cqe);

    // 关闭文件
    close(fd);

    // 销毁 io_uring
    io_uring_queue_exit(&ring);

    return 0;
}