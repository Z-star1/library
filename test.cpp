#include<iostream>
#include<algorithm>
#include<math.h>
#include<time.h>
#include <iomanip>
#include<vector>
#include<map>
using namespace std;


class date {
private:
	int year;
	int month;
public:
	date() {
		year = 0;
		month = 0;
	}
	date(int x, int y) {
		year = x;
		month = y;
	}
	int GetYear() { return year; }
	int GetMonth() { return month; }
	void SetYear(int x) { year = x; }
	void SetMonth(int y) { month = y; }
	void Displaydate() { cout << year << "年" << month << "月" << endl; }
	friend istream& operator>>(istream& in, date& x) {
		in >> x.year >> x.month;
		return in;
	}
	friend ostream& operator<<(ostream& output, const date& x) {
		output << x.year << "  " << x.month;
		return output;
	}
};


class book {
private:
	int id;
	string title;
	string author;
	int num;
	date dat;//出版日期
	int renewnum;//续借次数
	date startdate;
	date enddate;
public:
	book() {
		id = 0;
		title =" NULL";
		author = "NULL";
		num = 3;
		dat;
		renewnum = 0;
	}
	book(int x,string a,string b,date c) {
		id = x;
		title = a;
		author = b;
		num = 3;
		dat = c;
		renewnum = 0;
	}

	int Getid() { return id; }
	string Gettitle() { return title; }
	string Getauthor() { return author; }
	date Getdate() { return dat; }
	int Getnum() { return num; }
	int Getrenewnum() { return renewnum; }

	void Setid(int x) { id = x; }
	void Settitle(string a) { title = a; }
	void Setauthor(string a) { author = a; }
	void Setdate(date a) { dat = a; }
	void Setnum(int x) { num = x; }
	void Setrenewnum(int x) { renewnum = x; }
	//?????????????????????????
	string getTime() {
		time_t t = time(0);
		char tmp[11];
		strftime(tmp, sizeof(tmp), "%Y %m %d", localtime(&t));
		return tmp;
	}
	void dispdate() {
		string str = getTime();
		int x = (str[6] - 48) + 2;
		for (int i = 0; i <= 4; i++) {
			cout<<str[i];
		}
		cout << str[5] << x;//2018—08—08
		for(int i=7;i<=9;i++){
			cout << str[i];
		}
	}
	//显示函数
	void dispbook(bool x) {
		if (x) {
			cout << setw(10) << "编号" << setw(10) << "书名" << setw(10) << "作者" << setw(10) << "出版日期" << setw(6) << "库存" << setw(6) << "续借" << setw(12) << "借阅时间" << setw(10) << "应还时间" << endl;
			cout << setw(10) << id << setw(10) << title << setw(10) << author << setw(6) << dat << setw(6) << num << setw(6) << renewnum << "    " << setw(6) << getTime() << "  "; dispdate(); cout << endl;
			cout << endl;
		}
		else {
			cout << setw(10) << "编号" << setw(10) << "书名" << setw(10) << "作者" << setw(10) << "出版日期" << setw(6) << " 库存 " << setw(6) << "续借次数" << endl;
			cout << setw(10) << id << setw(10) << title << setw(10) << author << setw(6) << dat << setw(6) << num << setw(6) << renewnum << endl;
			cout << endl;
		}
	}
	friend istream& operator>>(istream& in, book& x) {
		in >> x.id >> x.title >> x.author >> x.dat;
		return in;
	}
	friend ostream& operator<<(ostream& output, const book& x) {
		output << x.id << " " << x.title << " " << x.author << " " << x.dat << " " << x.num << " " << x.renewnum;
		return output;
	}
	void operator=(const book& x) {
		id = x.id;
		title = x.title;
		author = x.author;
		dat = x.dat;
		num = x.num;
		renewnum = x.renewnum;
	}
};

class user {
private:
	long long int id;
	string name;
	string password;
	int booknum;
public:
	vector<book> b;//存放用户借的书
	vector<book>::iterator b1;//用户借的书  迭代器
	vector<book> b2;//文件读写容器
	vector<book>::iterator itb2;//文件读写迭代器
	multimap<string, int>m1;//根据书名查找下标 first->下标
	multimap<string, int>::iterator mit1;//根据书名查找
	multimap<string, int>m2;//根据作者查找
	multimap<string, int>::iterator mit2;//根据作者查找
	multimap<int, int>m3;//根据出版日期查找
	multimap<int, int>::iterator mit3;//根据出版日期查找  迭代器

	//构造函数
	user() {
		id = 0;
		name = "NULL";
		password = "123456";
		booknum = 0;
	}
	user(long long int a, string b, string c) {
		id = a;
		name = b;
		password = c;
		booknum = 0;
	}
	//成员函数
	long long int getId() { return id; }
	string getName() { return name; }
	string getPassword() { return password; }
	int getBooknum() { return booknum; }
	//Set函数
	void setId(long long int x) { id = x; }
	void setName(string x) { name = x; }
	void setPassword(string x) { password = x; }
	void setBooknum(int x) { booknum = x; }
	//验证密码
	bool isPassword(string x) {
		if (password == x)
			return 1;
		else
			return 0;
	}
	//重载
	friend istream& operator>>(istream& in, user& x) {
		in >> x.id >> x.name >> x.password;
		return in;
	}
	friend ostream& operator<<(ostream& output, user& x) {
		output << x.id << " " << x.name << " " << x.password;
		return output;
	}
	//显示函数
	void dispuser() {
		if (booknum) {
			cout << setw(10) << "学号" << setw(10) << "姓名" << setw(10) << "密码" << setw(10) << "借阅数量" << endl;
			cout << setw(10) << id << setw(10) << name << setw(10) << password << setw(10) << booknum << endl;
			for (b1 = b.begin(); b1 != b.end(); b1++) {
				b1->dispbook(1);

			}
		} 
		else
		{
			cout << setw(10) << "学号" << setw(10) << "姓名" << setw(10) << "密码" << setw(10) << "借阅数量" << endl;
			cout << setw(10) << id << setw(10) << name << setw(10) << password << setw(6) << booknum << endl;
		}
		//显示所有图书




	}



};