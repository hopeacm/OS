#include"Job_scheduling.h"
PCB_S *ready, *blocked, *running, *finished;
int accumulation = 0;

void PCB_S::init() {
	ready = (PCB_S*)malloc(sizeof(PCB_S));
	ready->next = NULL;
	running = (PCB_S*)malloc(sizeof(PCB_S));
	running->next = NULL;
	blocked = (PCB_S*)malloc(sizeof(PCB_S));
	blocked->next = NULL;
	finished = (PCB_S*)malloc(sizeof(PCB_S));
	finished->next = NULL;
}

PCB_S* PCB_S::creatPro() { //创建进程
	PCB_S *p;
	p = (PCB_S*)malloc(sizeof(PCB_S));
	p->next = NULL;
	cout << "Please input PCB_S's Name：";
	cin >> p->name;
	cout << "到达时间：";
	cin >> p->arrival_time;
	cout << "服务时间：";
	cin >> p->burst_time;
	return p;
}

void PCB_S::add(PCB_S *head, PCB_S *process) { //增加对应进程
	PCB_S *tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = process;
	process->next = NULL;
}

PCB_S* PCB_S::out(PCB_S *head) {//返回对应链表的第一个进程
	PCB_S *p;
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

void PCB_S::torun() {//运行进程
	PCB_S *p;
	p = out(ready);
	if (running->next != NULL && p != NULL)
		add(running, p);
}

void PCB_S::timeout() {//运行进程添加到就绪队列并运行就绪队列的第一个进程
	PCB_S *p;
	p = out(running);
	if (p != NULL)
		add(ready, p);
	p = out(ready);
	if (running->next == NULL && p != NULL)
		add(running, p);
}

void PCB_S::wakeup() {//觉醒进程
	PCB_S *p;
	p = out(blocked);
	if (p != NULL)
		add(ready, p);
}

void PCB_S::block() {//阻塞进程
	PCB_S *p;
	p = out(running);
	if (p != NULL)
		add(blocked, p);
	p = out(ready);
	if (running->next == NULL && p != NULL)
		add(running, p);
}

void PCB_S::ending() {//结束进程
	PCB_S *p;
	p = out(running);
	if (p != NULL)
		add(finished, p);
	p = out(ready);
	if (running->next == NULL && p != NULL)
		add(running, p);
}

void PCB_S::showPCB_S() {//显示进程
	PCB_S *p;
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


void PCB_S::printPro() {//显示就绪队列
	PCB_S *tmp;
	cout << setw(12) << "进程";
	tmp = ready->next;
	while (tmp != NULL) {
		cout << setw(5) << tmp->name;
		tmp = tmp->next;
	}
	cout << endl;
	cout << endl;

	cout << setw(12) << "到达时间";
	tmp = ready->next;
	while (tmp != NULL) {
		cout << setw(5) << tmp->arrival_time;
		tmp = tmp->next;
	}
	cout << endl;
	cout << endl;

	cout << setw(12) << "服务时间";
	tmp = ready->next;
	while (tmp != NULL) {
		cout << setw(5) << tmp->burst_time;
		tmp = tmp->next;
	}
	cout << endl;
	cout << endl;
}

void PCB_S::calculate_time() {
	PCB_S *tmp;
	tmp = finished->next;
	if (tmp != NULL) {
		if (tmp = finished->next) {
			tmp->runned_time = tmp->finished_time - tmp->arrival_time;
			tmp->Weighted_runned_time = (double)tmp->runned_time / tmp->burst_time;
			accumulation = tmp->finished_time;
		}
		tmp = tmp->next;
		while (tmp != NULL) {
			tmp->runned_time = tmp->finished_time - tmp->arrival_time;
			tmp->Weighted_runned_time = (double)tmp->runned_time / tmp->burst_time;
			accumulation = tmp->finished_time;
			tmp = tmp->next;
		}
	}

	cout << setw(12) << "进程";
	tmp = finished->next;
	while (tmp != NULL) {
		cout << setw(5) << tmp->name;
		tmp = tmp->next;
	}
	cout << endl;
	cout << endl;

	cout << setw(12) << "到达时间";
	tmp = finished->next;
	while (tmp != NULL) {
		cout << setw(5) << tmp->arrival_time;
		tmp = tmp->next;
	}
	cout << endl;
	cout << endl;

	cout << setw(12) << "服务时间";
	tmp = finished->next;
	while (tmp != NULL) {
		cout << setw(5) << tmp->burst_time;
		tmp = tmp->next;
	}
	cout << endl;
	cout << endl;

	cout << setw(12) << "完成时间";
	tmp = finished->next;
	while (tmp != NULL) {
		cout << setw(5) << tmp->finished_time;
		tmp = tmp->next;
	}
	cout << endl;
	cout << endl;

	cout << setw(12) << "周转时间";
	tmp = finished->next;
	while (tmp != NULL) {
		cout << setw(5) << tmp->runned_time;
		tmp = tmp->next;
	}
	cout << endl;
	cout << endl;

	cout << setw(12) << "带权周转时间";
	tmp = finished->next;
	while (tmp != NULL) {
		cout << setw(5) << setprecision(3) << tmp->Weighted_runned_time;
		tmp = tmp->next;
	}
	cout << endl;

}

void PCB_S::calculate_RR() {
	PCB_S *tmp;
	tmp = finished->next;
	if (tmp != NULL) {
		if (tmp = finished->next) {
			tmp->runned_time = tmp->finished_time - tmp->arrival_time;
			tmp->Weighted_runned_time = (double)tmp->runned_time / tmp->burst_time;
			accumulation = tmp->finished_time;
		}
		tmp = tmp->next;
		while (tmp != NULL) {
			if (accumulation < tmp->arrival_time) {
				accumulation = tmp->arrival_time;
			}
			tmp->runned_time = tmp->finished_time - tmp->arrival_time;
			tmp->Weighted_runned_time = (double)tmp->runned_time / tmp->burst_time;
			accumulation = tmp->finished_time;
			tmp = tmp->next;
		}
	}

	cout << setw(12) << "进程";
	tmp = finished->next;
	while (tmp != NULL) {
		cout << setw(5) << tmp->name;
		tmp = tmp->next;
	}
	cout << endl;
	cout << endl;

	cout << setw(12) << "到达时间";
	tmp = finished->next;
	while (tmp != NULL) {
		cout << setw(5) << tmp->arrival_time;
		tmp = tmp->next;
	}
	cout << endl;
	cout << endl;

	cout << setw(12) << "服务时间";
	tmp = finished->next;
	while (tmp != NULL) {
		cout << setw(5) << tmp->burst_time;
		tmp = tmp->next;
	}
	cout << endl;
	cout << endl;

	cout << setw(12) << "完成时间";
	tmp = finished->next;
	while (tmp != NULL) {
		cout << setw(5) << tmp->finished_time;
		tmp = tmp->next;
	}
	cout << endl;
	cout << endl;

	cout << setw(12) << "周转时间";
	tmp = finished->next;
	while (tmp != NULL) {
		cout << setw(5) << tmp->runned_time;
		tmp = tmp->next;
	}
	cout << endl;
	cout << endl;

	cout << setw(12) << "带权周转时间";
	tmp = finished->next;
	while (tmp != NULL) {
		cout << setw(5) << setprecision(3) << tmp->Weighted_runned_time;
		tmp = tmp->next;
	}
	cout << endl;

}

void PCB_S::help() {
	cout << "_____处理机调度算法_______" << endl;
	cout << "fcfs   --先来先服务调度算法" << endl;
	cout << "sjf    --短作业优先调度算法" << endl;
	cout << "rr     --时间片轮转调度算法" << endl;
	cout << "___________________________" << endl;
}

void PCB_S::help1() {
	cout << "                      HELP MENU" << endl;
	cout << " c——CREATE create a new process , and put to ready queuen" << endl;
	cout << " s——SHOW show the PCB_S all state" << endl;
	cout << " p——PRINT print Calculate_time" << endl;
	cout << " h——HELP print help menu" << endl;
	cout << " exit——Quit menu" << endl;
	cout << "___________________________________________________" << endl;

}

void PCB_S::FCFS() {
	PCB_S *r;
	char ch[6];
	char choice[2];
	cout << "__________________先来先服务调度算法_______________" << endl;
	help1();
	cout << "INPUT：";
	cin >> ch;
	while (strcmp(ch, "exit") != 0) {
		if (strcmp(ch, "c") == 0) {
			do {
				r = creatPro();
				PCB_S *smp, *tmp;

				smp = ready;
				tmp = ready->next;
				if (tmp != NULL) {
					while ((tmp->arrival_time < r->arrival_time) && tmp->next != NULL) {
						smp = tmp;
						tmp = tmp->next;
					}
					if (tmp->arrival_time >= r->arrival_time) {
						smp->next = r;
						r->next = tmp;
					}
					else {
						tmp->next = r;
					}
				}
				else {
					ready->next = r;
				}
				cout << "  是否继续创建进程(y/n)：";
				cin >> choice;
			} while (strcmp(choice, "y") == 0);

			if (strcmp(choice, "n") == 0) {
				showPCB_S();
				printPro();
				if (running->next == NULL) {
					PCB_S *tmp;
					tmp = out(ready);
					add(running, tmp);
					cout << "执行顺序 ： ";
					cout << tmp->name << ":";
					cout << tmp->burst_time << "  ";
					tmp->finished_time = tmp->arrival_time + tmp->burst_time;
					accumulation = tmp->finished_time;
					Sleep(tmp->burst_time * 1000);
					ending();
					while (running->next != NULL) {
						tmp = running->next;
						cout << tmp->name << ":";
						cout << tmp->burst_time << "  ";
						if (tmp->arrival_time < accumulation) {
							tmp->finished_time = accumulation + tmp->burst_time;
							accumulation = tmp->finished_time;
						}
						else {
							tmp->finished_time = tmp->arrival_time + tmp->burst_time;
							accumulation = tmp->finished_time;
						}
						Sleep(tmp->burst_time * 1000);
						ending();
					}
					cout << endl;
				}
			}
		}
		else if (strcmp(ch, "p") == 0) {
			calculate_time();
		}
		else if (strcmp(ch, "s") == 0) {
			showPCB_S();
		}
		else if (strcmp(ch, "h") == 0) {
			help1();
		}
		else {
			cout << "没有此命令或输入错误" << endl;
		}
		cout << "INPUT：";
		cin >> ch;
	}
	return;
}

void PCB_S::SJF() {
	PCB_S *r;
	char ch[6];
	char choice[2];
	cout << "__________________短作业优先调度算法_______________" << endl;
	help1();
	cout << "INPUT：";
	cin >> ch;
	while (strcmp(ch, "exit") != 0) {
		if (strcmp(ch, "c") == 0) {
			do {
				r = creatPro();
				PCB_S *smp, *tmp;
				smp = ready;
				tmp = ready->next;
				if (tmp != NULL) {
					while ((tmp->burst_time < r->burst_time) && tmp->next != NULL) {
						smp = tmp;
						tmp = tmp->next;
					}
					if (tmp->burst_time >= r->burst_time) {
						smp->next = r;
						r->next = tmp;
					}
					else {
						tmp->next = r;

					}
				}
				else {
					ready->next = r;
				}
				cout << "  是否继续创建进程(y/n)：";
				cin >> choice;
			} while (strcmp(choice, "y") == 0);

			if (strcmp(choice, "n") == 0) {
				PCB_S *x, *y, *u, *z;

				z = ready;
				u = ready;
				x = ready->next;
				y = ready->next;
				while (y != NULL) {

					if (y->arrival_time < x->arrival_time) {
						z = u;
						x = y;
					}
					u = u->next;
					y = y->next;
				}

				z->next = x->next;
				x->next = ready->next;
				ready->next = x;

				showPCB_S();
				printPro();
				if (running->next == NULL) {
					PCB_S *tmp;
					tmp = out(ready);
					add(running, tmp);
					cout << "执行顺序 ： ";
					cout << tmp->name << ":";
					cout << tmp->burst_time << "  ";
					tmp->finished_time = tmp->arrival_time + tmp->burst_time;
					accumulation = tmp->finished_time;
					Sleep(tmp->burst_time * 1000);
					ending();
					while (running->next != NULL) {
						tmp = running->next;
						cout << tmp->name << ":";
						cout << tmp->burst_time << "  ";

						if (tmp->arrival_time < accumulation) {
							tmp->finished_time = accumulation + tmp->burst_time;
							accumulation = tmp->finished_time;
						}
						else {
							tmp->finished_time = tmp->arrival_time + tmp->burst_time;
							accumulation = tmp->finished_time;
						}

						Sleep(tmp->burst_time * 1000);
						ending();
					}
					cout << endl;
				}
			}
		}
		else if (strcmp(ch, "p") == 0) {
			calculate_time();
		}
		else if (strcmp(ch, "s") == 0) {
			showPCB_S();
		}
		else if (strcmp(ch, "h") == 0) {
			help1();
		}
		else {
			cout << "没有此命令或输入错误" << endl;
		}
		cout << "INPUT：";
		cin >> ch;
	}
	return;
}

void PCB_S::RR() {
	PCB_S *r;
	char ch[6];
	char choice[2];
	int time;
	cout << "__________________时间片调度轮转算法_______________" << endl;
	help1();
	cout << "输入时间片q=";
	cin >> time;
	cout << "INPUT：";
	cin >> ch;
	while (strcmp(ch, "exit") != 0) {
		if (strcmp(ch, "c") == 0) {
			do {
				r = creatPro();
				r->reduce_burst_time = r->burst_time;

				PCB_S *smp, *tmp;

				smp = ready;
				tmp = ready->next;
				if (tmp != NULL) {
					while ((tmp->arrival_time < r->arrival_time) && tmp->next != NULL) {
						smp = tmp;
						tmp = tmp->next;
					}
					if (tmp->arrival_time >= r->arrival_time) {
						smp->next = r;
						r->next = tmp;
					}
					else {
						tmp->next = r;
					}
				}
				else {
					ready->next = r;
				}

				cout << "  是否继续创建进程(y/n)：";
				cin >> choice;
			} while (strcmp(choice, "y") == 0);

			if (strcmp(choice, "n") == 0) {
				printPro();
				PCB_S *t;
				t = out(ready);
				add(running, t);
				cout << "执行顺序 ： ";
				do {
					PCB_S *smp;
					smp = running->next;
					int n = smp->reduce_burst_time;
					if (time >= n && n != 0) {
						cout << smp->name << ":";
						cout << n << "  ";
						Sleep(n * 1000);
						if (accumulation < smp->arrival_time)
							accumulation = smp->arrival_time;
						accumulation = accumulation + n;
						smp->finished_time = accumulation;
						smp->reduce_burst_time = 0;
						ending();
					}
					else if (n == 0) {
						ending();
					}
					else {
						cout << smp->name << ":";
						cout << time << "  ";
						Sleep(time * 1000);
						if (accumulation < smp->arrival_time) {
							accumulation = smp->arrival_time;
						}
						accumulation = accumulation + time;
						smp->reduce_burst_time = n - time;
						smp->finished_time = accumulation;

						PCB_S *u, *v;
						u = running->next;
						running->next = u->next;
						v = ready;
						while (v->next != NULL) {
							v = v->next;
						}
						if (v->next == NULL) {
							v->next = u;
						}
						if (running->next == NULL) {
							u = out(ready);
							add(running, u);
						}
					}
				} while (running->next != NULL);
				cout << endl;
			}

		}

		else if (strcmp(ch, "p") == 0) {
			calculate_RR();
		}
		else if (strcmp(ch, "s") == 0) {
			showPCB_S();
		}
		else if (strcmp(ch, "h") == 0) {
			help1();
		}
		else {
			cout << "没有此命令或输入错误" << endl;
		}
		cout << "INPUT：";
		cin >> ch;

	}
}

void PCB_S::showJob() {
	char ch[6];
	init();
	while (strcmp(ch, "exit") != 0) {
		help();
		cout << "请选择算法：";
		cin >> ch;
		if (strcmp(ch, "fcfs") == 0) {
			FCFS();
		}
		else if (strcmp(ch, "sjf") == 0) {
			SJF();
		}
		else if (strcmp(ch, "rr") == 0) {
			RR();
		}
		else if (strcmp(ch, "exit") == 0) break;
		else {
			cout << "输入错误,重新输入："<<endl;
		}
		cout << endl;
	}
}
