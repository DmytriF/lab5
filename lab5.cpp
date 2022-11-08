#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
//::Base 
using namespace std;
struct programmisti {
	string level;
	string spisok;
};
struct sis_a {
	string oborud;
};
struct person {
	string F;
	string I;
	string O;
	int salary;
	int t=3;
	programmisti d_prog;
	sis_a d_sis;
};

//Class Roditel 

class Employee {
public:
	void set(person &Per) {
		cout << "Введите ФИО сотрудника:\n";
		cout << "Фамилия:";
		cin >> Per.F;
		Per.F.append(" ");
		cout << "Имя:";
		cin >> Per.I;
		Per.I.append(" ");
		cout << "Отчество:";
		cin >> Per.O;
		Per.O.append(" ");
		do {
			cout << "Введите зарплату сотрудника:";
			cin >> Per.salary;
			if (Per.salary < 0) {
				cout << "Зарплата не может быть отрицательной\n";
			}
		} while (check()||Per.salary<0);
		return;
	}
	bool check() {
		bool flag = false;
		if (cin.fail()) {
			flag = true; cout << "Неверные входные данные\n";
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		}
		return flag;
	};
}; 
class sis_admin :virtual public Employee {
private:
	person sis_admin;
public:  
	vector <sis_a> oborud;
	person employ_sis() {
		set(sis_admin);
		cout << "Введите оборудование";
		cin >> sis_admin.d_sis.oborud;
		sis_admin.t = 1;
		return sis_admin;
	}
	void get_s(person fd) {
		cout << "Сис Админ:" << fd.F << fd.I << fd.O << "Зарплата:" << fd.salary;
			cout << "Список оборудования:" << fd.d_sis.oborud << "\n";
		}

};
class programmist :public sis_admin {
private:
	person proger;
public:
	person employ_proger() {
		int y;
		string s;
		set(proger);
		proger.t = 0;
		do {
			cout << "Уровень программиста 1)junior, 2)middle, 3)senior, 4)lead:";
			cin >> y;
			if (y <= 0 || y>4)cout << "Нет такого уровня\n";
		} while (check()||y<=0||y>4);
		switch (y) {
		case 1:proger.d_prog.level = "junior";
		case 2:proger.d_prog.level = "middle";
		case 3:proger.d_prog.level = "senior";
		case 4:proger.d_prog.level = "lead";
		}
		do {
			cout << "технологии:";
			cin >> s;
			proger.d_prog.spisok.append(s);
			proger.d_prog.spisok.append(" ");
			do {
				cout << "Ввести еще? 1-y/2-no\n";
				cin >> y;
			} while (y<1 ||y>2||check());
		} while (y==1);
		return proger;
	}
	void get_p(person dp) {
		cout << "Прогер:" << dp.F << dp.I << dp.O << "Зарплата:" << dp.salary;
			cout << " Уровень программиста: " << dp.d_prog.level << " Список технологий: "<<dp.d_prog.spisok<<"\n";
	}
};
class Boss :public programmist {
private:
	person b;
public:
	int sis=0;
	int progra = 0;
	int sec = 1;
public:
	vector <person> emp;
	
	Boss() {
		b.F = "Филиппов ";
		b.I = "Дмитрий ";
		b.O = "Сергеввич ";
		b.salary = 1000000;
		cout << "Директор:" << b.F << b.I << b.O << "Зарплата:" << b.salary << "\n";
	}
	void employ() {
		person per;
		int k;
		do {
			cout << "Кого нанять?\n1-Программист\n2-Сис., Админ\n3-секретарша\n4-выход\n";
			cin >> k;
			switch (k) {
			case 1:
				per = employ_proger();
				progra++;
				emp.push_back(per);
				break;
			case 2:
				per = employ_sis();
				sis++;
				emp.push_back(per);
				break;
			case 4:break;
			case 3:
				set(per);
				per.t = 3;
				sec++;
				emp.push_back(per);
				break;
			default:cout << "Нет такой команды\n"; cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n'); break;
			}

		} while (k != 4);
	}
	void fire() {
		int r = size(emp);
		char ch;
		for (int i = 0; i < r; i++) {
			get(emp[i]);
			do {
				cout << "Уволить? y/n:";
				cin >> ch;
			} while (ch != 'y' && ch != 'n');
			if (ch == 'y') {
				if (emp[i].t == 1) sis--;
				if (emp[i].t == 0) progra--;
				if (emp[i].t == 3) sec--;
				auto t1 = emp.cbegin();
				emp.erase(t1 + i, t1 + i + 1);
			}

		}
	}
	void change_b() {
		set(b);
	}
	void get_b() {
		cout << "Директор:" << b.F << b.I << b.O << "Зарплата:" << b.salary << "\n";
	}
	void get(person chel) {
		if (chel.t == 0)
			cout << "Программист:" << chel.F << chel.I << chel.O << "Зарплата:" << chel.salary << "\n";
		if (chel.t == 1)
			cout << "Сис Админ:" << chel.F << chel.I << chel.O << "Зарплата:" << chel.salary << "\n";
		if (chel.t == 3)
			cout << "Секретарь:" << chel.F << chel.I << chel.O << "Зарплата:" << chel.salary << "\n";

	};
};
class Secretery:public Boss{
private:
	person secr;
	bool flag = false;
public:
	Secretery() {
		secr.F = "Васильева ";
		secr.I = "Мария ";
		secr.O = "Дмитревна ";
		secr.salary = 89898;
		cout << "Секретарь:" << secr.F << secr.I << secr.O << "Зарплата:" << secr.salary << "\n";
		emp.push_back(secr);
	}
	void st_proger() {
		int y;
		programmisti gh;
		for (int i=0; i < size(emp); i++)
		{
			if (emp[i].t == 0)
				get_p(emp[i]);
		}
	}
	void sis_admins() {
		cout << "Cис Админы и их оборудования:\n";
		for (int i = 0; i < size(emp); i++)
		{
			if (emp[i].t == 1)
				get_s(emp[i]);
		}
	}
	void employeers() {
		if (size(emp) == 0)
			cout << "Сотрудников нет, босс всех УВОЛИЛ!!!!\n";
		else
			for (int i=0; i < size(emp); i++) {
				get(emp[i]);
			}
		}
};

class inicial {
public:
	string I, F, O;
	void set() {
		cout << "Введите фамилию:";
		cin >> F;
		F.append(" ");
		cout << "Введите имя:";
		cin >> I;
		I.append(" ");
		cout << "Введите отчество:";
		cin >> O;
		O.append(" ");
	}
};
class viplati {
public:
	int zap;
	void set_z() {
		bool flag;
		do {
			flag = false;
			cout << "Введите выплаты:\n";
			cin >> zap;
			if (cin.fail()||zap<0) {
				flag = true; cout << "Неверные входные данные\n";
				cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			}
		} while (flag);
	}
};
class stavka:public viplati,public inicial {
public:
	void data_emp() {
		int y;
		bool flag = true;
		do {
			cout << "Введите инициалы работника\n";
			set();
			set_z();
			cout << "=================================================================\n";
			cout << "Инициалы: " << F << I << O << "Зарплата: " << 30 * zap<<"\n";
			cout << "=================================================================\n";
			cout << "Продолжить? 1-y/2-y\n";
			cin >> y;
			if (y == 2)
				flag = false;
		} while (flag);
	}
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color F0");
	Secretery b;
	int j;
	int l;
	do {
		cout << "1-Босс\n2-Секретарь\n3-выход\n";
		cin >> j;
		switch (j) {
		case 1:
			do {
				cout << "==========================================================\n";
				b.get_b();
				cout << "1-Уволить\n2-Нанять\n3-изменить\n4-выход\n";
				cin >> l;
				switch (l) {
				case 1:
					b.fire();
					break;
				case 2:
					b.employ();
					break;
				case 3:
					b.change_b();
					break;
				case 4:break;
				default:
					cout << "Нет такой команды\n"; cin.clear(); cin.ignore((numeric_limits<streamsize>::max)(), '\n'); break;
				}
			} while (l != 4);
			break;
		case 2:
			if (b.sec == 0)
				cout << "А вы зачем секретаршу уволили???!!?!?! Чтобы использовать методы наймите секретаршу:))\n";
			else
			do {			
				cout << "==========================================================\n";
				cout << "Секретарь\n";
				cout << "1-Вывести список сотрудников\n2-Вывести список программистов\n3-вывестиz сис админов и их оборудование\n4-выход\n";
				cin >> l;
				switch (l) {
				case 1:
					cout << "==========================================================\n";
					b.employeers();
					break;
				case 2:
					if (b.progra!= 0) {
						cout << "==========================================================\n";
						b.st_proger();
					}
					else cout << "А программистов то нет, все уехали(((\n";
					break;
				case 3:
					cout << "==========================================================\n";
					if (b.sis != 0)
						b.sis_admins();
					else cout << "Сис админов нет, чините принтер сами )\n";
					break;
				case 4:
					break;
				default:cout << "Нет такой команды\n"; cin.clear(); cin.ignore((numeric_limits<streamsize>::max)(), '\n'); break;
				}
			} while (l!=4);
			break;
		case 3:break;
		default:cout << "WRONG!\n"; break;
		}
		cin.clear();
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
	} while (j != 3);
	cout << "Задание 5.2\n";
	stavka p;
	p.data_emp();
}