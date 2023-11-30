
//prioNum.h
//
typedef enum {R,E} PROC_STATE;

typedef struct _proc {/*进程结构体*/
 char name[32];/*进程名*/
 int run_time; /*要求运行总时间*/
 int alloc_time; /*已经运行时间*/
 int req_time;/*还需要的时间 */
 int pri;/*优先级：时间片调度中未使用*/
 PROC_STATE state;/*进程状态*/
 struct _proc *next;
}PROC;


