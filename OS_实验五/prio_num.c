#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "prioNum.h"

// 


// 初始化队列
void initQueue(PROC** front, PROC** rear) {
    *front = NULL;
    *rear = NULL;
}

// 入队列
void enqueue(PROC** front, PROC** rear, PROC* process) {
    process->next = NULL;

    if (*rear == NULL) {
        *front = process;
        *rear = process;
    } else {
        // 寻找插入位置
        PROC* current = *front;
        PROC* prev = NULL;

        while (current != NULL && current->pri >= process->pri) {
            prev = current;
            current = current->next;
        }

        // 插入队列
        if (prev == NULL) {
            process->next = *front;
            *front = process;
        } else {
            prev->next = process;
            process->next = current;
            if (current == NULL) {
                *rear = process;  // 更新队尾指针
            }
        }
    }
}

// 创建进程
PROC* createProcess(char name[], int run_time, int alloc_time, int req_time, int pri, PROC_STATE state) {
    PROC* process = (PROC*)malloc(sizeof(PROC));
    strcpy(process->name, name);
    process->run_time = run_time;
    process->alloc_time = alloc_time;
    process->req_time = req_time;
    process->pri = pri;
    process->state = state;
    process->next = NULL;

    return process;
}

// 打印队列
void printQueue(PROC* front) {
    PROC* current = front;

    while (current != NULL) {
        printf("Process: %s Priority=%d run_time=%d alloc_time=%d req_time=%d State=%s\n", current->name, current->pri, current->run_time, current->alloc_time, current->req_time, (current->state == R) ? "R" : "E");
        current = current->next;
    }
}

void simulateProcess(PROC** front, PROC** rear) {
    int i=0;
    while (*front != NULL) {
        PROC* current = *front;
	//出队
	*front = current->next;
	if(*front == NULL){
	*rear = NULL;
	}
        // 模拟进程的一次运行
        current->pri -= 1;
        current->alloc_time += 1;
        current->req_time -= 1;

        // 输出运行的进程
        printf("Simulating process: %s\n" , current->name);

        // 判断是否需要重新加入队列或结束
        if (current->req_time > 0) {
            // 还需运行时间不为0，重新加入队列
            enqueue(front, rear, current);
            
        } else {
            // 运行结束，修改状态并出队列
            current->state = E;
            //*front = (*front)->next;
            if (*front == NULL) {
                *rear = NULL;  // 更新队尾指针
                printf("运行第%d次后结束!!!\n",i);
                return;
            }
            
            free(current);
        }
        printf("运行第%d次之后进程队列的变化:\n",i);
        printQueue(*front);
        i += 1;

    }
}

int main(){
    PROC* front;
    PROC* rear;

    // 初始化队列
    initQueue(&front, &rear);

    // 创建5个进程并加入队列
    PROC* processes[5];
    processes[0] = createProcess("P1", 2, 0, 2, 1, R);
    processes[1] = createProcess("P2", 3, 0, 3, 5, R);
    processes[2] = createProcess("P3", 1, 0, 1, 3, R);
    processes[3] = createProcess("P4", 2, 0, 2, 4, R);
    processes[4] = createProcess("P5", 4, 0, 4, 2, R);

    // 将进程按照优先数插入队列
    for (int i = 0; i < 5; i++) {
        enqueue(&front, &rear, processes[i]);
    }

    // 打印队列
    printf("初始进程信息: \n");
    printQueue(front);

    simulateProcess(&front, &rear);

 return 0;
}
