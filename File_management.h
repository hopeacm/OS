#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;
#define DIR 2
#define file 1
#define deleted 0

class FCB {
	char filename[10];//目录名
	int size;//大小
	SYSTEMTIME createtime; //日期时间
	char type[5];//类型
	int first_block;//第一块磁盘号
	FCB *child;	//子目录
	FCB *father; //父目录
	FCB *rightbrother;//右目录
	static FCB *present;//当前所处的目录
	static FCB *predir;//上一级目录
public:
	FCB() {}
	void setfat(int row); //设置fat值
	int getfat(int count); //获取fat
	void printfat(int count); //输出fat表
	void init(); //初始化
	void help();//显示帮助
	void md(); //md     创建子目录
	void cd();//cd     定位目录
	void rd(); //rd     删除空子目录
	void mk(); //md    创建文件
	void del();//del    删除文件
	void dir();// dir    列出当前目录对象
	void tree();//tree   显示树形目录
	void showFile(); //文件管理入口
};
#define L sizeof(FCB)

