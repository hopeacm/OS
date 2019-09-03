#pragma once
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <windows.h>

using namespace std;
class PCB_S {
	char name[20];
	int size;
	int arrival_time;		//到达时间
	int burst_time;		//服务时间
	int finished_time;	//完成时间
	int runned_time;		//周转时间
	double Weighted_runned_time;   //带权周转时间
	int reduce_burst_time;	//剩余服务时间
	int *page_table;
	PCB_S * next;
public:
	void init(); //初始化
	void add(PCB_S *head, PCB_S *process);//添加head对应进程
	PCB_S * out(PCB_S *head); //返回对应链表的第一个进程
	PCB_S* creatPro();//创建进程
	void torun();//运行进程
	void timeout();//运行进程添加到就绪队列并运行就绪队列的第一个进程
	void wakeup();//觉醒进程
	void block();//阻塞进程
	void ending();//结束进程
	void showPCB_S(); //显示进程
	void printPro();//显示就绪队列
	void help();//显示帮助
	void help1();//显示帮助
	void calculate_time();//时间计算
	void calculate_RR(); //
	void FCFS();//先来先服务
	void SJF(); //短作业优先
	void RR(); //时间片轮法
	void showJob(); //作业调度入口
};
extern PCB_S *ready, *blocked, *running, *finished;
extern int accumulation;
