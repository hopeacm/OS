#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "conio.h"
using namespace std;
/*定义结构体*/

extern int bitmap[8][8];

typedef struct PCB {
	char name[20];  //名称
	int size;   //大小
	int *page_table; //进程页面
	struct PCB * next; 
}PCB;
extern PCB *ready, *blocked, *running, *finished;

class Node {
	char name[10];				//名称
	struct PCB *process;			//占用该节点的进程
	struct PCB *waitinglist;		//等待该节点的进程队列
	Node *next;			//下一个节点
	Node *parent;	    //父节点
	static Node *CHCT; //通道队列头节点
	static Node *COCT; //控制器队列头节点
	static Node *DCT; //设备头节点
public:
	void initFacility();  //初始化设备
	void addCHCT(); //添加通道
	void addCOCT(); //添加控制器
	void addDCT(); //添加设备

	void deleteCHCT();//删除通道
	void deleteCOCT();//删除控制器
	void deleteDCT();//删除设备

	void allotFacility(); //分配设备
	void releaseFacility();//释放设备
	void printFacility();//显示设备


	void setmap(int *bitmap, int row, int rank); //初始化bitmap
	void printmap(int *bitmap, int row, int rank); //输出bitmap
	int getbit(int *bitmap, int row, int rank); //获取空闲区域
	void address_translate(); //地址映射
	void exitmap(int *bitmap); //地址分配
	void printpage_table(); //页面显示

	PCB * out(PCB *head); //返回对应链表的第一个进程
	void add(PCB *head, PCB *process);//添加head对应进程
	void create();//创建进程
	void torun();//运行进程
	void timeout();//运行进程添加到就绪队列并运行就绪队列的第一个进程
	void wakeup();//觉醒进程
	void block();//阻塞进程
	void ending();//结束进程
	void showPCB(); //显示进程
	void help();//显示帮助
	void help2_1();
	void help2_2();
	void init(); //初始化
	void showEquip(); //设备管理入口
};
