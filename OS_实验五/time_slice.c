#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "prioNum.h"

// 
PROC *flag;  // 标志单元
PROC *front;
PROC *rear;


// 创建进程
PROC* createProcess(char name[], int run_time, int alloc_time,PROC_STATE state) {
    PROC* process = (PROC*)malloc(sizeof(PROC));
    strcpy(process->name, name);
    process->run_time = run_time;
    process->alloc_time = alloc_time;
    process->state = state;
    process->next = NULL;
    return process;
}
// 初始化循环队列
void initCircularQueue(PROC **front, PROC **rear, PROC *processes[], int size) {
    *front = processes[0];
    *rear = processes[size - 1];
    processes[size - 1]->next = processes[0];
    for (int i = 0; i < size - 1; ++i) {
        processes[i]->next = processes[i + 1];
    }
    flag = *front;  // 初始时标志单元指向队头
}
// 打印队列
void printQueue(PROC *front) {
    PROC *current = front;

    do {
        printf("Process: %s run_time=%d alloc_time=%d State=%s\n", current->name, current->run_time, current->alloc_time, (current->state == R) ? "R" : "E");
        current = current->next;
    } while (current != front);
}

// 处理器调度
void scheduler() {
    printf("Running process: %s\n", flag->name);

    // 模拟进程运行
    flag->alloc_time++;
    
    PROC *prev = flag;
    // 判断进程是否执行结束
    if (flag->alloc_time == flag->run_time) {
        flag->state = E;
        printf("Process %s finished.\n", flag->name);

        // 修改指针值，使其指向下一个进程
        
        flag = flag->next;
        
        if (flag == prev) {
            front = NULL;
            rear = NULL;
        } else {
            front = flag;
            rear->next = front;
        }
        free(prev);  // 释放已完成的进程的内存
       
    } else {
        // 进程状态为R时，指向下一个进程
        rear->next=flag;
        rear = flag;
        flag = flag->next;
        front = flag;
    }


    if(front == NULL){
    printf("运行结束!!\n");
    }
    else{
      printf("运行之后的信息:\n");
      printQueue(front);
    }
  
}


int main(){
    

    // 创建5个进程并加入队列
    PROC* processes[5];
    processes[0] = createProcess("Q1", 2, 0,  R);
    processes[1] = createProcess("Q2", 3, 0,  R);
    processes[2] = createProcess("Q3", 1, 0,  R);
    processes[3] = createProcess("Q4", 2, 0,  R);
    processes[4] = createProcess("Q5", 4, 0,  R);
    // 初始化循环队列

    initCircularQueue(&front, &rear, processes, 5);
 

    // 打印队列
    printf("初始进程信息: \n");
    printQueue(front);
    
    // 模拟处理器调度
    while (front != NULL) {
        scheduler();
    }
    

  

 return 0;
}
