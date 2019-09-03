#include"File_management.h"

char cmd[10];
char url[20];
int fat[64];
FCB *root, *c, *d, *e, *f;
FCB* FCB::present = root;
FCB* FCB::predir = root;

void FCB::setfat(int row) { //设置fat值
	for (int i = 0; i < row; i++) {
		fat[i] = 0x0000;
	}
}

int FCB::getfat(int count) { //获取fat
	for (int i = 0; i < count; i++) {
		if (fat[i] == 0x0000) {
			return i;
		}
	}
	return 0;
}

void FCB::printfat(int count) { //输出fat
	for (int i = 0; i < count; i++) {
		cout << hex << setw(5) << fat[i];
		if (i % 16 == 15) {
			cout << endl;
		}
	}
}


void FCB::init() { //初始化
	root = (FCB*)malloc(L);	//初始化四个盘
	c = (FCB*)malloc(L);
	d = (FCB*)malloc(L);
	e = (FCB*)malloc(L);
	f = (FCB*)malloc(L);
	//-----------------------------------------
	GetSystemTime(&(root->createtime));
	strcpy(root->filename, "root");
	strcpy(root->type, "DIR");
	root->rightbrother = NULL;
	root->child = c;
	root->father = NULL;
	//------------------------------------------
	c->rightbrother = d;
	d->rightbrother = e;
	e->rightbrother = f;
	f->rightbrother = NULL;
	c->father = root;
	d->father = root;
	e->father = root;
	f->father = root;
	//------------------------------------------
	GetSystemTime(&(c->createtime));
	c->child = NULL;
	strcpy(c->filename, "C");
	strcpy(c->type, "DIR");
	c->size = 775646412;

	c->first_block = getfat(16);
	fat[c->first_block] = 0xffff;
	//------------------------------------------
	GetSystemTime(&(d->createtime));
	d->child = NULL;
	strcpy(d->filename, "D");
	strcpy(d->type, "DIR");
	d->size = 1853685720;

	d->first_block = getfat(16);
	fat[d->first_block] = 0xffff;
	//------------------------------------------
	GetSystemTime(&(e->createtime));
	e->child = NULL;
	strcpy(e->filename, "E");
	strcpy(e->type, "DIR");
	e->size = 1719427072;

	e->first_block = getfat(16);
	fat[e->first_block] = 0xffff;
	//------------------------------------------
	GetSystemTime(&(f->createtime));
	f->child = NULL;
	strcpy(f->filename, "F");
	strcpy(f->type, "DIR");
	f->size = 1276334080;

	f->first_block = getfat(16);
	fat[f->first_block] = 0xffff;
	//------------------------------------------
	present = c;
	predir = c;
	strcpy(url, "C:\\");
}


void FCB::help() {
	cout << "md     创建子目录" << endl;
	cout << "cd     定位目录" << endl;
	cout << "rd     删除空子目录" << endl;
	cout << "dir    列出当前目录对象" << endl;
	cout << "tree   显示树形目录" << endl;
	cout << "mk     创建文件" << endl;
	cout << "del    删除文件" << endl;
	cout << "fat    查看FAT表" << endl;
	cout << "help   提供命令帮助信息" << endl;
	cout << "exit   退出CMD.EXE程序(命令解释程序)" << endl;
}

void FCB::md() { //创建子目录
	FCB *p;
	p = (FCB*)malloc(L);
	cout << "input name: ";
	cin >> p->filename;
	GetSystemTime(&(p->createtime));
	strcpy(p->type, "DIR");

	p->first_block = getfat(16);//第一块盘号
	fat[p->first_block] = 0xffff;

	p->father = present;
	p->child = NULL;
	p->rightbrother = NULL;
	if (present->child == NULL) {
		present->child = p;
	}
	else {
		FCB *tmp;
		tmp = present->child;
		while (tmp->rightbrother != NULL) {
			tmp = tmp->rightbrother;
		}
		if (tmp->rightbrother == NULL) {
			tmp->rightbrother = p;
		}
	}

}

void FCB::cd() { //定位目录
	char ch[10];
	cout << "input cd: ";
	cin >> ch;
	FCB *tmp;
	tmp = present->child;
	if (tmp != NULL) {
		if (strstr(ch, "\\") != NULL) {
			char *cd1 = strtok(ch, "\\");
			while (cd1 != NULL) {
				while (strcmp(cd1, tmp->filename) != 0 && tmp->rightbrother != NULL) {
					tmp = tmp->rightbrother;
				}
				if (strcmp(cd1, tmp->filename) == 0) {
					tmp = tmp->child;
					cd1 = strtok(NULL, "\\");
				}
				else {
					cout << "系统找不到指定路径1" << endl;
					break;
				}
			}
			if (cd1 == NULL) {
				strcat(url, ch);
				strcat(url, "\\");
				present = tmp;
			}
		}
		else if (strcmp(ch, ".") == 0) {
			present = present;
		}
		else if (strcmp(ch, "..") == 0) {
			char ch1[10];
			strcpy(ch1, present->filename);
			char *s = strtok(url, strcat(ch1, "\\"));
			strcpy(url, s);
			strcat(url, "\\");

			present = predir;
			predir = predir->father;
		}
		else {
			while (strcmp(tmp->filename, ch) != 0 && tmp->rightbrother != NULL) {
				tmp = tmp->rightbrother;
			}
			if (strcmp(tmp->filename, ch) == 0) {
				strcat(url, ch);
				strcat(url, "\\");
				predir = present;
				present = tmp;
			}
			else {
				cout << "系统找不到指定路径2" << endl;
			}
		}
	}
	else if (strcmp(ch, "..") == 0) {
		char ch1[10];
		strcpy(ch1, present->filename);
		char *s = strtok(url, strcat(ch1, "\\"));
		strcpy(url, s);
		strcat(url, "\\");
		present = predir;
		predir = predir->father;
	}
	else
		cout << "系统找不到指定路径3" << endl;
}

void FCB::rd() { //删除空目录
	char ch[10];
	cout << "input rdname: ";
	cin >> ch;
	FCB *tmp, *ump;
	ump = present->child;
	tmp = present->child;
	if (tmp != NULL) {
		while (strcmp(tmp->filename, ch) != 0 && tmp->rightbrother != NULL) {
			ump = tmp;
			tmp = tmp->rightbrother;
		}
		if (strcmp(tmp->filename, ch) == 0 && tmp->child != NULL) {
			cout << "该目录不为空，无法删除" << endl;
		}
		else if (strcmp(tmp->filename, ch) == 0 && tmp->child == NULL) {
			tmp->father = NULL;
			strcpy(tmp->type, "DEL");

			fat[tmp->first_block] = 0x0000;//fat块回收置0

			if (present->child == tmp) {
				present->child = tmp->rightbrother;
			}
			else {
				ump->rightbrother = tmp->rightbrother;
			}
			tmp->rightbrother = NULL;
		}
		else
			cout << "系统找不到指定目录" << endl;
	}

	else
		cout << "系统找不到指定目录" << endl;
}

void FCB::mk() { //创建文件
	FCB *p;
	p = (FCB*)malloc(L);
	cout << "input name and size: ";
	cin >> p->filename;
	cin >> p->size;
	GetSystemTime(&(p->createtime));
	strcpy(p->type, "FILE");


	int a = p->size / 1024; //分配第一块磁盘号
	if (p->size % 1024 > 0) {
		a++;
	}
	if (a == 1) {
		p->first_block = getfat(64);
		fat[p->first_block] = 0xffff;
	}
	if (a > 1) {
		p->first_block = getfat(64);
		fat[p->first_block] = 1;
		fat[p->first_block] = getfat(64);
		int m = getfat(64);
		a--;
		while (a > 1) {
			fat[m] = 1;
			fat[m] = getfat(64);
			m = getfat(64);
			a--;
		}
		if (a == 1) {
			fat[getfat(64)] = 0xffff;
		}
	}

	p->father = present;
	p->child = NULL;
	p->rightbrother = NULL;
	if (present->child == NULL) {
		present->child = p;
	}
	else {
		FCB *tmp;
		tmp = present->child;
		while (tmp->rightbrother != NULL) {
			tmp = tmp->rightbrother;
		}
		if (tmp->rightbrother == NULL) {
			tmp->rightbrother = p;
		}
	}

}

void FCB::del() { //删除文件
	char ch[10];
	cout << "input mkname: ";
	cin >> ch;
	FCB *tmp, *ump;
	ump = present->child;
	tmp = present->child;
	if (tmp != NULL) {
		while (strcmp(tmp->filename, ch) != 0 && tmp->rightbrother != NULL) {
			ump = tmp;
			tmp = tmp->rightbrother;
		}
		if (strcmp(tmp->filename, ch) == 0) {
			tmp->father = NULL;
			strcpy(tmp->type, "DEL");

			int a = tmp->size / 1024;//文件占用的空间回收
			if (tmp->size % 1024 > 0) {
				a++;
			}
			int m, n;
			m = tmp->first_block;

			while (a > 0) {
				n = fat[m];
				fat[m] = 0x0000;
				m = n;
				a--;
			}

			if (present->child == tmp) {
				present->child = tmp->rightbrother;
			}
			else {
				ump->rightbrother = tmp->rightbrother;
			}
			tmp->rightbrother = NULL;
		}
		else
			cout << "系统找不到指定目录" << endl;
	}
	else
		cout << "系统找不到指定目录" << endl;
}



void FCB::dir() { //列出当前目录对象
	FCB *tmp;
	int a = 0, b = 0;//统计文件和目录的个数
	tmp = present->child;

	cout << url << "中的目录" << endl;
	cout << dec << present->createtime.wYear << "-" << present->createtime.wMonth << "-" << present->createtime.wDay << " " << present->createtime.wHour << ":" << present->createtime.wMinute << ":" << present->createtime.wSecond;
	cout << setw(4) << "<" << present->type << ">  " << setw(4) << "." << endl;
	cout << present->father->createtime.wYear << "-" << present->father->createtime.wMonth << "-" << present->father->createtime.wDay << " " << present->father->createtime.wHour << ":" << present->father->createtime.wMinute << ":" << present->father->createtime.wSecond;
	cout << setw(4) << "<" << present->father->type << ">  " << setw(4) << ".." << endl;
	while (tmp != NULL) {
		cout << tmp->createtime.wYear << "-" << tmp->createtime.wMonth << "-" << tmp->createtime.wDay << " " << tmp->createtime.wHour << ":" << tmp->createtime.wMinute << ":" << tmp->createtime.wSecond;
		cout << setw(4) << "<" << tmp->type << ">  " << setw(4) << tmp->filename;//类型 文件名
		cout << setw(4) << tmp->first_block;
		if (strcmp(tmp->type, "FILE") == 0) {
			a++;
			cout << setw(8) << tmp->size;
		}
		else
			b++;
		cout << endl;
		tmp = tmp->rightbrother;
	}
	cout << a << "个文件" << endl;
	cout << b << "个目录" << endl;
}

void FCB::tree() {//文件最多显示四级目录
	FCB *mp;
	mp = present;
	cout << present->filename << endl;
	if (mp->child != NULL) {
		FCB *tmp;
		tmp = c->child;
		while (tmp != NULL) {
			if (strcmp(tmp->type, "DIR") == 0) {
				cout << "|--" << tmp->filename << endl;
				FCB *amp;
				amp = tmp->child;
				while (amp != NULL) {
					if (strcmp(amp->type, "DIR") == 0) {
						cout << "    |--" << amp->filename << endl;
						FCB *bmp;
						bmp = amp->child;
						while (bmp != NULL) {
							if (strcmp(bmp->type, "DIR") == 0) {
								cout << "        |--" << bmp->filename << endl;
							}
							bmp = bmp->rightbrother;
						}
					}
					amp = amp->rightbrother;
				}
			}
			tmp = tmp->rightbrother;
		}
	}
}

void FCB::showFile() {//文件管理入口
	setfat(64);
	init();

	cout << url << ">";
	cout << "可查看帮助help()" << endl;
	cin >> cmd;
	while (1) {
		if (strcmp(cmd, "c:") == 0) {
			present = c;
			predir = c;
			strcpy(url, "C:\\");
		}
		else if (strcmp(cmd, "d:") == 0) {
			present = d;
			predir = d;
			strcpy(url, "D:\\");
		}
		else if (strcmp(cmd, "e:") == 0) {
			present = e;
			predir = e;
			strcpy(url, "E:\\");
		}
		else if (strcmp(cmd, "f:") == 0) {
			present = f;
			predir = f;
			strcpy(url, "F:\\");
		}
		else if (strcmp(cmd, "md") == 0) {
			md();
		}
		else if (strcmp(cmd, "cd") == 0) {
			cd();
		}
		else if (strcmp(cmd, "rd") == 0) {
			rd();
		}
		else if (strcmp(cmd, "dir") == 0) {
			dir();
		}
		else if (strcmp(cmd, "tree") == 0) {
			tree();
		}
		else if (strcmp(cmd, "mk") == 0) {
			mk();
		}
		else if (strcmp(cmd, "del") == 0) {
			del();
		}
		else if (strcmp(cmd, "help") == 0) {
			help();
			cout << endl;
		}
		else if (strcmp(cmd, "fat") == 0) {
			cout << "FAT:" << endl;
			printfat(64);
		}
		else if (strcmp(cmd, "exit") == 0) {
			exit(0);
			cout << "Thanks for using" << endl;
			break;
		}
		else {
			cout << "“" << cmd << "”" << "不是内部或外部命令，也不是可运行程序或批处理文件" << endl;
		}
		cout << endl;
		cout << url << ">";
		cin >> cmd;
	}
} 
