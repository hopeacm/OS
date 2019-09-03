#include"Equipment_management.h"

int bitmap[8][8];
PCB *ready, *blocked, *running, *finished;
Node* Node::CHCT = (Node*)malloc(sizeof(Node));
Node* Node::COCT = (Node*)malloc(sizeof(Node));
Node* Node::DCT = (Node*)malloc(sizeof(Node));

void Node::initFacility() {	//初始化设备
	Node *a, *b, *d, *e, *f, *j, *k, *l, *m; //a,b两个通道； d,e,f三个控制器；j,k,l,m四个设备 
	a = (Node*)malloc(sizeof(Node));
	b = (Node*)malloc(sizeof(Node));
	strcpy(a->name, "CHCT1");
	a->parent = NULL;
	a->process = NULL;
	a->waitinglist = NULL;

	strcpy(b->name, "CHCT2");
	b->parent = NULL;
	b->process = NULL;
	b->waitinglist = NULL;

	a->next = b;
	b->next = NULL;
	CHCT->next = a;

	d = (Node*)malloc(sizeof(Node));
	e = (Node*)malloc(sizeof(Node));
	f = (Node*)malloc(sizeof(Node));
	strcpy(d->name, "COCT1");
	d->parent = a;
	d->process = NULL;
	d->waitinglist = NULL;

	strcpy(e->name, "COCT2");
	e->parent = a;
	e->process = NULL;
	e->waitinglist = NULL;

	strcpy(f->name, "COCT3");
	f->parent = b;
	f->process = NULL;
	f->waitinglist = NULL;
	d->next = e;
	e->next = f;
	f->next = NULL;
	COCT->next = d;

	j = (Node*)malloc(sizeof(Node));
	k = (Node*)malloc(sizeof(Node));
	l = (Node*)malloc(sizeof(Node));
	m = (Node*)malloc(sizeof(Node));

	strcpy(j->name, "1");
	j->parent = d;
	j->process = NULL;
	j->waitinglist = NULL;

	strcpy(k->name, "2");
	k->parent = d;
	k->process = NULL;
	k->waitinglist = NULL;

	strcpy(l->name, "3");
	l->parent = e;
	l->process = NULL;
	l->waitinglist = NULL;

	strcpy(m->name, "4");
	m->parent = f;
	m->process = NULL;
	m->waitinglist = NULL;

	DCT->next = j;
	j->next = k;
	k->next = l;
	l->next = m;
	m->next = NULL;
}


void Node::printFacility() {   //显示设备表

	Node *r, *s, *t;
	r = CHCT->next;
	s = COCT->next;
	t = DCT->next;

	while (r) {
		cout << setw(6) << r->name;
		if (r->process) {
			cout << " P:";
			cout << "—" << r->process->name;
		}
		if (r->waitinglist) {
			PCB *p;
			p = r->waitinglist;
			cout << " W:";
			while (p != NULL) {
				cout << "—" << p->name;
				p = p->next;
			}
		}
		cout << endl;
		if (s != NULL) {
			while (s->parent == r) {
				cout << setw(22) << s->name;
				if (s->process) {
					cout << " P:";
					cout << "—" << s->process->name;
				}
				if (s->waitinglist) {
					PCB *q;
					q = s->waitinglist;
					cout << " W:";
					while (q != NULL) {
						cout << "—" << q->name;
						q = q->next;
					}
				}
				cout << endl;
				if (t) {
					while (t->parent == s) {
						cout << setw(38) << t->name;
						if (t->process) {
							cout << " P:";
							cout << "—" << t->process->name;
						}
						if (t->waitinglist) {
							PCB *o;
							o = t->waitinglist;
							cout << " W:";
							while (o != NULL) {
								cout << "—" << o->name;
								o = o->next;
							}
						}
						cout << endl;
						t = t->next;
						if (t == NULL)
							break;

					}
				}

				s = s->next;
				if (s == NULL)
					break;
			}
		}
		cout << "————————————————————" << endl;
		r = r->next;
	}
}

void Node::addCHCT() {    //添加通道
	Node *p, *q;
	q = CHCT;
	p = (Node*)malloc(sizeof(Node));
	cout << "请输入通道名称：";
	cin >> p->name;
	p->next = NULL;
	p->parent = NULL;
	p->process = NULL;
	p->waitinglist = NULL;
	while (q->next)
		q = q->next;
	q->next = p;
	p->next = NULL;
}

void Node::addCOCT() {      //添加控制器
	Node *o, *p, *q;  //o, 设备； p, 待添加节点；q, 控制器
	char ch[20];
	o = COCT->next;
	q = CHCT->next;
	p = (Node*)malloc(sizeof(Node));

	cout << "请输入控制器名称：";
	cin >> p->name;
	cout << "请输入父节点名称：";
	cin >> ch;

	while (strcmp(q->name, ch) != 0) {
		q = q->next;
		if (q == NULL) {
			break;
		}
	}
	if (q) {
		while (o != NULL) {
			if (strcmp(o->parent->name, ch) == 0 && o->next == NULL) {
				p->next = NULL;
				o->next = p;
				p->parent = q;
				p->process = NULL;
				p->waitinglist = NULL;
				break;

			}
			if (strcmp(o->parent->name, ch) == 0 && strcmp(o->next->parent->name, ch) != 0) {
				p->next = o->next;
				o->next = p;
				p->parent = q;
				p->process = NULL;
				p->waitinglist = NULL;
				break;
			}
			o = o->next;
		}
		if (o == NULL) {
			o = COCT->next;
			while (o->next != NULL) {
				o = o->next;
			}
			o->next = p;
			p->next = NULL;
			p->parent = q;
			p->process = NULL;
			p->waitinglist = NULL;
		}

	}
	else
		cout << "没有这个通道" << endl;
}

void Node::addDCT() {    //添加设备
	Node *o, *p, *q; //o,设备； p,添加的节点；q,控制器
	char ch[20];
	o = DCT->next;
	q = COCT->next;
	p = (Node*)malloc(sizeof(Node));

	cout << "请输入设备名称：";
	cin >> p->name;
	cout << "请输入父节点名称：";
	cin >> ch;

	while (strcmp(q->name, ch) != 0) {
		q = q->next;
		if (q == NULL) {
			break;
		}
	}
	if (q) {
		while (o != NULL) {
			if (strcmp(o->parent->name, ch) == 0 && o->next == NULL) {
				p->next = NULL;
				o->next = p;
				p->parent = q;
				p->process = NULL;
				p->waitinglist = NULL;
				break;

			}
			if (strcmp(o->parent->name, ch) == 0 && strcmp(o->next->parent->name, ch) != 0) {
				p->next = o->next;
				o->next = p;
				p->parent = q;
				p->process = NULL;
				p->waitinglist = NULL;
				break;
			}
			o = o->next;
		}
		if (o == NULL) {
			o = DCT->next;
			while (o->next != NULL) {
				o = o->next;
			}
			o->next = p;
			p->next = NULL;
			p->parent = q;
			p->process = NULL;
			p->waitinglist = NULL;
		}

	}
	else
		cout << "没有这个控制器" << endl;
}

void Node::deleteCHCT() {  //删除通道
	Node *p, *pr, *q;
	char ch[10];

	pr = CHCT;
	p = CHCT->next;
	q = COCT->next;
	cout << "输入要删除的通道名称：";
	cin >> ch;
	while (strcmp(p->name, ch) != 0 && p->next != NULL) {
		pr = p;
		p = p->next;
	}
	if (strcmp(p->name, ch) == 0) {
		while (strcmp(p->name, q->parent->name) != 0 && q->next != NULL) {
			q = q->next;
		}
		if (strcmp(p->name, q->parent->name) != 0 && p->process == NULL && p->waitinglist == NULL) {
			pr->next = p->next;
			p->next = NULL;
			free(p);
		}
		else
			cout << "无法删除这个通道" << endl;
	}
	else
		cout << "没有这个通道" << endl;
}

void Node::deleteCOCT() {   //删除控制器
	Node *p, *pr, *q;
	char ch[10];

	pr = COCT;
	p = COCT->next;
	q = DCT->next;
	cout << "输入要删除的控制器名称：";
	cin >> ch;
	while (strcmp(p->name, ch) != 0 && p->next != NULL) {
		pr = p;
		p = p->next;
	}
	if (strcmp(p->name, ch) == 0) {
		while (strcmp(p->name, q->parent->name) != 0 && q->next != NULL) {
			q = q->next;
		}
		if (strcmp(p->name, q->parent->name) != 0 && p->process == NULL && p->waitinglist == NULL) {
			pr->next = p->next;
			p->next = NULL;
			free(p);
		}
		else
			cout << "无法删除这个控制器" << endl;
	}
	else
		cout << "没有这个控制器" << endl;
}

void Node::deleteDCT() {   //删除设备
	Node *p, *pr;
	char ch[10];

	pr = DCT;
	p = DCT->next;
	cout << "输入要删除的设备名称：";
	cin >> ch;
	while (strcmp(p->name, ch) != 0 && p->next != NULL) {
		pr = p;
		p = p->next;
	}
	if (strcmp(p->name, ch) == 0) {

		if (p->process == NULL && p->waitinglist == NULL) {
			pr->next = p->next;
			p->next = NULL;
			free(p);
		}
		else
			cout << "无法删除这个设备" << endl;
	}
	else
		cout << "没有这个设备" << endl;
}

void Node::allotFacility() {     //分配设备
	char ch[10];
	PCB *progess, *t;
	progess = out(running);
	Node *p, *q, *r;
	p = CHCT->next;
	q = COCT->next;
	r = DCT->next;
	cout << "输入进程要用的设备名：";
	cin >> ch;
	while (strcmp(r->name, ch) != 0 && r->next != NULL) {
		r = r->next;
	}

	if (strcmp(r->name, ch) == 0) {
		PCB *tmp;
		tmp = (PCB*)malloc(sizeof(PCB));
		strcpy(tmp->name, progess->name);
		tmp->page_table = progess->page_table;
		tmp->next = NULL;
		tmp->size = progess->size;

		if (r->process == NULL) {
			r->process = tmp;
			PCB *a;
			a = (PCB*)malloc(sizeof(PCB));
			strcpy(a->name, progess->name);
			a->page_table = progess->page_table;
			a->next = NULL;
			a->size = progess->size;
			if (r->parent->process == NULL) {
				r->parent->process = a;
				PCB *b;
				b = (PCB*)malloc(sizeof(PCB));
				strcpy(b->name, progess->name);
				b->page_table = progess->page_table;
				b->next = NULL;
				b->size = progess->size;
				if (r->parent->parent->process == NULL) {
					r->parent->parent->process = b;
				}
				else if (r->parent->parent->waitinglist == NULL) {
					r->parent->parent->waitinglist = b;
				}
				else {
					PCB *t;
					t = r->parent->waitinglist;
					while (t->next != NULL) {
						t = t->next;
					}
					t->next = tmp;
				}
			}
			else if (r->parent->waitinglist == NULL) {
				r->parent->waitinglist = a;
			}
			else {
				PCB *t;
				t = r->parent->waitinglist;
				while (t->next != NULL) {
					t = t->next;
				}
				t->next = tmp;
			}
		}
		else if (r->waitinglist == NULL) {
			r->waitinglist = tmp;
		}
		else {
			PCB *t;
			t = r->waitinglist;
			while (t->next != NULL) {
				t = t->next;
			}
			t->next = tmp;
		}
		add(blocked, progess);
		t = out(ready);
		if (running->next == NULL && t != NULL)
			add(running, t);
	}
	else
		cout << "没有这个设备" << endl;
}

void Node::releaseFacility() {     //释放设备
	Node *r;
	r = DCT->next;
	char ch[10];
	cout << "请输入要释放的设备名称：";
	cin >> ch;
	while (strcmp(r->name, ch) != 0 && r->next != NULL) {
		r = r->next;
	}
	if (strcmp(r->name, ch) == 0) {
		if (r->process) {
			PCB *pr;
			pr = r->process;
			r->process = NULL;
			pr->next = NULL;
			if (r->waitinglist) {
				PCB *qr;
				qr = r->waitinglist;
				r->waitinglist = r->waitinglist->next;
				qr->next = NULL;
				r->process = qr;

				PCB *a, *b;
				a = (PCB*)malloc(sizeof(PCB));
				strcpy(a->name, qr->name);
				a->next = NULL;
				b = r->parent->waitinglist;
				if (b == NULL) {
					b = a;
				}
				else {
					while (b->next != NULL)
						b = b->next;
					if (b) {
						b->next = a;
					}
				}
			}
			if (strcmp(pr->name, r->parent->process->name) == 0) {
				PCB *ar;
				ar = r->parent->process;
				r->parent->process = NULL;
				ar->next = NULL;
				if (r->parent->waitinglist) {
					PCB *br;
					br = r->parent->waitinglist;
					r->parent->waitinglist = r->parent->waitinglist->next;
					br->next = NULL;
					r->parent->process = br;
				}

				if (strcmp(ar->name, r->parent->parent->process->name) == 0) {
					PCB *mr;
					mr = r->parent->parent->process;
					r->parent->parent->process = NULL;
					mr->next = NULL;
					if (r->parent->parent->waitinglist) {
						PCB *nr;
						nr = r->parent->parent->waitinglist;
						r->parent->parent->waitinglist = r->parent->parent->waitinglist->next;
						nr->next = NULL;
						r->parent->parent->process = nr;

						PCB *c, *d;
						c = (PCB*)malloc(sizeof(PCB));
						strcpy(c->name, nr->name);
						c->next = NULL;
						d = r->parent->parent->waitinglist;
						if (d == NULL) {
							d = c;
						}
						else {
							while (d->next != NULL)
								d = d->next;
							if (d) {
								d->next = c;
							}
						}
					}

					PCB *v, *u, *f;
					v = blocked;
					u = blocked->next;
					while (strcmp(mr->name, u->name) != 0 && u->next != NULL) {
						v = u;
						u = u->next;
					}
					if (strcmp(mr->name, u->name) == 0) {
						v->next = u->next;
						u->next = NULL;
						add(ready, u);
						if (running->next == NULL) {
							f = out(ready);
							add(running, f);
						}
					}
				}

			}
		}
		else
			cout << "这个设备没被占用" << endl;

	}
	else
		cout << "这个设备不存在；";

	if (r->parent->parent->process == NULL && r->parent->process != NULL) {
		PCB *a;
		a = (PCB*)malloc(sizeof(PCB));
		strcpy(a->name, r->parent->process->name);
		a->next = NULL;
		r->parent->parent->process = a;
	}
	if (r->parent->parent->process == NULL && r->parent->process == NULL && r->process != NULL) {
		PCB *a;
		a = (PCB*)malloc(sizeof(PCB));
		strcpy(a->name, r->process->name);
		a->next = NULL;
		r->parent->parent->process = a;
		PCB *b;
		b = (PCB*)malloc(sizeof(PCB));
		strcpy(b->name, r->process->name);
		b->next = NULL;
		r->parent->process = b;
	}

}


void Node::setmap(int *bitmap, int row, int rank){ //初始化bitmap
	for (int i = 0; i < row; i++)
		for (int j = 0; j < rank; j++)
			bitmap[i * 8 + j] = rand() % 2;
}

void Node::printmap(int *bitmap, int row, int rank) { //输出bitmap
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < rank; j++)
			cout << bitmap[i * 8 + j];
		cout << "  ";
	}
}

int Node::getbit(int *bitmap, int row, int rank) { //获取空闲区域

	for (int i = 0; i < row; i++)
		for (int j = 0; j < rank; j++)
			if (bitmap[i * 8 + j] == 0) {
				bitmap[i * 8 + j] = 1;
				return i * 8 + j;
			}
	return 0;
}

void Node::address_translate() { //地址映射
	int addr;
	cout << "Please enter the Logic Address: ";
	cin >> addr;
	int vritual = addr / 1024;
	int offset = addr % 1024;
	int real = *(running->next->page_table + vritual);
	cout << "逻辑页号 = " << vritual << "  偏移量 = " << offset << endl;
	//cout << "物理块号 = "<< endl;
	cout << "物理地址 = " << real * 1024 + offset << endl;
}

void Node::exitmap(int *bitmap) {  //地址分配
	for (int i = 0; i <= finished->next->size / 1024; i++) {
		int	real = *(finished->next->page_table + i);
		int a = real / 8;
		int b = real % 8;
		bitmap[real] = 0;

	}
}

void Node::printpage_table() { //页面显示

	int i = running->next->size / 1024 + 1;
	for (int j = 0; j < i; j++) {
		cout << j << " ";
		cout << *(running->next->page_table + j) << endl;
	}

}

void Node::add(PCB *head, PCB *process) { //添加head对应进程
	PCB *tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = process;
	process->next = NULL;
}

PCB* Node::out(PCB *head) { //返回对应链表的第一个进程
	PCB *p;
	p = head;
	if (p->next == NULL)
		return NULL;
	else
	{
		p = p->next;
		head->next = p->next;
		p->next = NULL;
		return p;
	}
}


void Node::create() { //创建进程
	PCB *p;

	p = (PCB*)malloc(sizeof(PCB));
	p->next = NULL;
	cout << "Please input PCB's Name：";
	cin >> p->name;

	cout << "Please input PCB's Size:(Unit: Byte) ";
	cin >> p->size;
	int i = (int)(p->size) / 1024 + 1;
	p->page_table = (int*)malloc(sizeof(int)*i);
	for (int j = 0; j < i; j++)
		*(p->page_table + j) = getbit(*bitmap, 8, 8);

	add(ready, p);
	if (running->next == NULL && p != NULL) {
		p = out(ready);
		add(running, p);
	}
}

void Node::torun() { //运行进程
	PCB *p;
	p = out(ready);
	if (running->next != NULL && p != NULL)
		add(running, p);
}

void Node::timeout() { //运行进程添加到就绪队列并运行就绪队列的第一个进程
	PCB *p;
	p = out(running);
	if (p != NULL)
		add(ready, p);
	p = out(ready);
	if (running->next == NULL && p != NULL)
		add(running, p);
}

void Node::wakeup() { //觉醒进程
	PCB *p;
	p = out(blocked);
	if (p != NULL)
		add(ready, p);
}

void Node::block() {//阻塞进程
	PCB *p;
	p = out(running);
	if (p != NULL)
		add(blocked, p);
	p = out(ready);
	if (running->next == NULL && p != NULL)
		add(running, p);
}

void Node::ending() { //结束进程
	PCB *p;
	p = out(running);
	if (p != NULL)
		add(finished, p);
	p = out(ready);
	if (running->next == NULL && p != NULL)
		add(running, p);
	exitmap(*bitmap);
}



void Node::showPCB() { //显示
	PCB *p;
	p = ready->next;
	cout << "ready: ";
	while (p != NULL) {
		cout << p->name << " ";
		p = p->next;
	}
	cout << endl;

	p = running->next;
	cout << "running: ";
	while (p != NULL) {
		cout << p->name << " ";
		p = p->next;
	}
	cout << endl;

	p = blocked->next;
	cout << "blocked: ";
	while (p != NULL) {
		cout << p->name << " ";
		p = p->next;
	}
	cout << endl;

	p = finished->next;
	cout << "finished: ";
	while (p != NULL) {
		cout << p->name << " ";
		p = p->next;
	}
	cout << endl;
}

void Node::help() {
	cout << "_____________________HELP MENU_____________________" << endl;
	cout << " h——HELP show help optionn" << endl;
	cout << " c——CREATE create a new process , and put to ready queuen" << endl;
	cout << " b——BLOCK block a process in excute queuen" << endl;
	cout << " w——WAKEUP a process in wait queuen" << endl;
	cout << " r——RUN run excute a process in ready queuen" << endl;
	cout << " s——SHOW show the PCB all state" << endl;
	cout << " e——ENDING end a procee in running" << endl;
	cout << " t——TIMEOUT let a process to run" << endl;
	cout << " 1——display Bitmap" << endl;
	cout << " 2——display Page_table" << endl;
	cout << " 3——Address display" << endl;
	cout << " 4——添加设备" << endl;
	cout << " 5——删除设备" << endl;
	cout << " 6——分配设备" << endl;
	cout << " 7——释放设备" << endl;
	cout << " 8——显示设备图" << endl;
	cout << " q——QUIT quit the PCB" << endl;
	cout << "_____________________________________________________" << endl;
}

void Node::help2_1() {
	cout << " 1——添加通道" << endl;
	cout << " 2——添加控制器" << endl;
	cout << " 3——添加设备" << endl;
	cout << " 0——返回上一层" << endl;
}
void Node::help2_2() {
	cout << " 1——删除通道" << endl;
	cout << " 2——删除控制器" << endl;
	cout << " 3——删除设备" << endl;
	cout << " 0——返回上一层" << endl;
}

void Node::init() {
	ready = (PCB*)malloc(sizeof(PCB));
	ready->next = NULL;
	running = (PCB*)malloc(sizeof(PCB));
	running->next = NULL;
	blocked = (PCB*)malloc(sizeof(PCB));
	blocked->next = NULL;
	finished = (PCB*)malloc(sizeof(PCB));
	finished->next = NULL;
}

void Node::showEquip() {//设备管理入口
	char ch, a;
	init();
	initFacility();
	help();
	cout << endl;
	setmap(*bitmap, 8, 8);
	cout << "Bit Map:" << endl;
	printmap(*bitmap, 8, 8);
	cout << endl;
	cout << " Please input: ";
	cin >> ch;
	while (ch != 'q') {
		switch (ch) {
		case 'h':
		case 'H': help(); break;
		case 'c':
		case 'C': create(); showPCB(); break;
		case 'b':
		case 'B': block(); showPCB(); break;
		case 'W':
		case 'w': wakeup(); showPCB(); break;
		case 'R':
		case 'r': torun(); showPCB(); break;
		case 'S':
		case 's': showPCB(); break;
		case 'E':
		case 'e': ending(); showPCB(); break;
		case 'T':
		case 't': timeout(); showPCB (); break;

		case '1': printmap(*bitmap, 8, 8); break;
		case '2': printpage_table(); break;
		case '3': address_translate(); break;
		case '4': help2_1();
			cout << "选择：";
			cin >> a;
			while (a != '0') {
				switch (a) {
				case '1': addCHCT(); printFacility(); break;
				case '2': addCOCT(); printFacility(); break;
				case '3': addDCT(); printFacility(); break;
				}
				cout << endl;
				help2_1();
				cout << "选择：";
				cin >> a;
			}
			break;
		case '5':help2_2();
			cout << "选择：";
			cin >> a;
			while (a != '0') {
				switch (a) {
				case '1': deleteCHCT(); printFacility(); break;
				case '2': deleteCOCT(); printFacility(); break;
				case '3': deleteDCT(); printFacility(); break;
				}
				cout << endl;
				help2_2();
				cout << "选择：";
				cin >> a;
			}
			break;
		case '6':allotFacility(); printFacility(); break;
		case '7':releaseFacility(); printFacility(); break;
		case '8':printFacility(); break;
		case 'Q':
		case 'q': cout << "Quit the PCB" << endl; break;
		default:cout << " Input error " << endl;
		}
		cout << endl;
		cout << " Please input: ";
		cin >> ch;
	}
} 
