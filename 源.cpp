//
//#系统主要功能 [Ver 1.0 保留了字符串菜单]
//
//一、管理员权限??
//? ? ? ? ? ? 1.对图书的增删查改
//? ? ? ? ? ? 2.对用户的增删查改
//????????????3.修改管理员的密码
//二、用户权限
//? ? ? ? ? ? 1.查询 
//  ? ? ? ? ? 2.借阅 
//????????????3.续借 
//????????????4.修改密码
//三、程序文件
//? ? ? ? ? ? book.txt 存放图书馆数据 【编号 书名 作者 出版日期】
//? ? ? ? ? ? user.txt 存放用户数据 【学号 姓名 密码】
//? ? ? ? ? ? userborrow.txt 存放用户借书数据【编号 书名 作者 出版日期】
//? ? ? ? ? ? library.txt 存放修改后的书籍数据 【编号 书名 作者 出版日期】
//四、数据示例
//    book ： 1 JavaScript 扎克伯格 2018 11
//????user ： 20176666 Leo 123456
//
//#各个功能实现方法原理
//????1.图书的增删查改 首先定义了book类，并重载输入运算符，在增加图书时，便于图书信息的整体输入，然后在管理员类里创建图书Vector和索引Map，
//????便于存放图书数据和查找图书。在查找时，有三种方式：书名查找、作者查找、出版日期查找。查找之前，把不同的类型作为键值，分别存放Map。
//????删除图书和修改图书之前，首先要找到图书，然后在操作。对用户的增删查改同理。
//????2.用户的查询和管理员同理。在借阅之前，先定位该书，然后从书库Vector压入用户借阅的Vector，每个用户只能续借一次，所以续借就是修改0为1，
//
//#程序设计心得体会见末尾
//
/*
? ? ? ? ? ? *Library Management System -By Leo
? ? ? ? ? ? *? ? Copyright ? 2018.5 - 2018.6
? ? ? ? ? ? *? ? ? ?Leo.All Rights Reserved.
? ? ? ? ? ? *? ? ? ? ? ? ? ?Ver 1.0
? ? ? ? ? ? */
			//主程序代码
#include<bits/stdc++.h>
#include <iostream>
#include<algorithm>

using namespace std;
class date//日期类
{
private:
	int year;//年
	int month;//月
public:
	//构造函数
	date() {
		year = 0;
		month = 0;
	}
	date(int x, int y) {
		year = x;
		month = y;
	}
	//get set 函数
	int getYear() { return year; }
	int getMonth() { return month; }
	void setYear(int x) { year = x; }
	void setMonth(int x) { month = x; }
	//显示日期函数
	void dispdate() {
		cout << year << "年" << month << "月";
	}
	//重载输入运算符
	friend istream& operator>>(istream?& in, date& x) {
		in >> x.year >> x.month;
		return in;
	}
	//重载输出运算符
	friend ostream& operator<<(ostream& output, const date& x)
	{
		output << x.year << " " << x.month;
		return output;
	}
};
class book//书籍类
{
private:
	int id;//图书编号
	string title;//书名
	string author;//作者
	date dat;//出版日期
	int num;//库存数量 副本为3
	int renewnum;//续借次数 最多一次
	string startdate;
	string enddate;
public:
	//构造函数
	book() {
		id = 0;
		title = "NULL";
		author = "NULL";
		dat;
		num = 3;
		renewnum = 0;
	}
	book(int x, string a, string b, date c) {
		id = x;
		title = a;
		author = b;
		dat = c;
		num = 3;
		renewnum = 0;
	}
	//Get函数
	int getId() { return id; }
	string getTitle() { return title; }
	string getAuthor() { return author; }
	date getDate() { return dat; }
	int getNum() { return num; }
	int getRenewnum() { return renewnum; }
	//Set函数
	void setId(int x) { id = x; }
	void setTitle(string x) { title = x; }
	void setAuthor(string x) { author = x; }
	void setDate(date x) { dat = x; }
	void setNum(int x) { num = x; }
	void setRenewnum(int x) { renewnum = x; }
	//获取系统时间作为借书时间
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
			cout << str[i];
		}
		cout << str[5] << x;//2018_08_08
		for (int i = 7; i <= 9; i++) {
			cout << str[i];
		}
	}
	//显示函数
	void dispbook(bool x) {
		if (x) {
			cout << setw(10) << "编号" << setw(10) << "书名" << setw(10) << "作者" << setw(10) << "出版日期" << setw(6) << " 库存 " << setw(6) << "续借" << setw(12) << "借阅时间" << setw(10) << "应还时间" << endl;
			cout << setw(10) << id << setw(10) << title << setw(10) << author << setw(6) << dat << setw(6) << num << setw(6) << renewnum << "? ? " << setw(6) << getTime() << "? "; dispdate(); cout << endl;
			cout << endl;
		}
		else {
			cout << setw(10) << "编号" << setw(10) << "书名" << setw(10) << "作者" << setw(10) << "出版日期" << setw(6) << " 库存 " << setw(6) << "续借次数" << endl;
			cout << setw(10) << id << setw(10) << title << setw(10) << author << setw(6) << dat << setw(6) << num << setw(6) << renewnum << endl;
			cout << endl;
		}
	}
	//重载输入运算符
	friend istream& operator>>(istream?& in, book& x) {
		in >> x.id >> x.title >> x.author >> x.dat;
		return in;
	}
	//重载输出运算符
	friend ostream& operator<<(ostream& output, const book& x)
	{
		output << x.id << " " << x.title << " " << x.author << " " << x.dat << " " << x.num << " " << x.renewnum;
		return output;
	}
	//重载赋值运算符
	void operator=(const book& x) {
		id = x.id;
		title = x.title;
		author = x.author;
		dat = x.dat;
		num = x.num;
		renewnum = x.renewnum;
	}
};
class user//用户类
{
private:
	long long int id;//学号
	string name;//姓名
	string password;//密码
	int booknum;//借阅数目
public:
	vector<book> b;//存放用户借的图书
	vector<book>::iterator b1;//用户借的图书 迭代器
	vector<book> b2;//文件读写容器 相当于图书馆
	vector<book>::iterator itb2;//文件读写迭代器
	multimap<string, int> m1;//根据书名查找 First->书名 Second->下标
	multimap<string, int>::iterator mit1;//根据书名查找 对应迭代器
	multimap<string, int> m2;//根据作者查找 First->作者 Second->下标
	multimap<string, int>::iterator mit2;//根据作者查找 对应迭代器
	multimap<int, int> m3;//根据出版日期查找 First->出版日期 Second->下标
	multimap<int, int>::iterator mit3;//根据出版日期查找 对应迭代器
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
	//Get函数
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
		if (password == x) return true;
		else return false;
	}
	//重载输入运算符
	friend istream& operator>>(istream?& in, user& x) {
		in >> x.id >> x.name >> x.password;
		return in;
	}
	//重载输出运算符
	friend ostream& operator<<(ostream& output, const user& x)
	{
		output << x.id << " " << x.name << " " << x.password;
		return output;
	}
	//显示函数
	void dispuser() {
		if (booknum) {//如果借阅数量不为0 则输出借阅图书
			cout << setw(10) << "学号" << setw(10) << "姓名" << setw(10) << "密码" << setw(10) << "借阅数量" << endl;
			cout << setw(10) << id << setw(10) << name << setw(10) << password << setw(10) << booknum << endl;
			for (b1 = b.begin(); b1 != b.end(); b1++) {
				b1->dispbook(1); // cout<<*b1<<endl;
			}
		}
		else {
			cout << setw(10) << "学号" << setw(10) << "姓名" << setw(10) << "密码" << setw(10) << "借阅数量" << endl;
			cout << setw(10) << id << setw(10) << name << setw(10) << password << setw(6) << booknum << endl;
		}
	}
	//显示book文件所有图书
	void dispallbook() {
		for (itb2 = b2.begin(); itb2 != b2.end(); itb2++) {
			itb2->dispbook(0); // cout<<*b1<<endl;
		}
	}
	//借阅图书
	void borrowbook(int x) {
		b.push_back(b2[x - 1]);//从文件书籍Vector b2 到用户书籍Vector b
		b[booknum].setId(booknum + 1);//重新设置下标
		booknum++;//借阅数量 +1
		int i = b2[x - 1].getId() - 1;//向量下标
		int j = b2[x - 1].getNum() - 1;//库存数量 -1
		b[i].setNum(j);//修改库存
	}
	//续借图书
	void reborrowbook() {
		dispuser();
		cout << "请输入你要续借的图书编号:" << endl;
		int x;
		cin >> x;
		b[x - 1].setRenewnum(1);
		b[x - 1].dispbook(1);
		//cout<<b[x-1];
		cout << endl;
		cout << "续借成功!" << endl;
	}
	//归还图书
	void returnbook(int x) {
		if (b.empty()) {//如果用户借阅图书为0
			cout << "该用户没有借阅任何书籍！\n";
		}
		else {
			b1 = b.begin() - 1 + x;
			b.erase(b1);//删除图书
			booknum--;//借阅数量 -1
			int i = b2[x - 1].getId() - 1;//向量下标
			int j = b2[x - 1].getNum() + 1;//库存数量 +1
			b[i].setNum(j);//修改库存
			save();
			cout << "成功归还图书！\n";
		}
	}
	//查询图书 [图书馆中的图书]
	//按书名查询
	string seaBytitle(string x) {
		mit1 = m1.find(x);//根据书名查找 返回迭代器
		int num = m1.count(x);// x 出现的次数
		if (mit1 == m1.end()) {//如果没找到 find() 会返回m2.end()
			cout << "? ? ?未找到该图书！请检查书名是否正确！\n";
		}
		else {
			cout << "您要查找的图书信息如下:\n\n";
			for (; num > 0; num--) {//输出所有结果
				int temp = mit1->second;//下标
				b2[temp - 1].dispbook(0);//显示图书信息
				mit1++;
			}
		}
	}
	//按作者查询
	string seaByauthor(string x) {
		mit2 = m2.find(x);//根据书名查找 返回迭代器
		int num = m2.count(x);// x 出现的次数
		if (mit2 == m2.end()) {//如果没找到 find() 会返回m2.end()
			cout << "? ? ?未找到该图书！请检查作者名是否正确！\n";
		}
		else {
			cout << "您要查找的图书信息如下:\n\n";
			for (; num > 0; num--) {//输出所有结果
				int temp = mit2->second;//下标
				b2[temp - 1].dispbook(0);//显示图书信息
				mit2++;
			}
		}
	}
	//按出版日期查询
	string seaBydate(int x) {
		mit3 = m3.find(x);//根据书名查找 返回迭代器
		int num = m3.count(x);
		if (mit3 == m3.end()) {//如果没找到 find() 会返回m3.end()
			cout << "? ? ?未找到该图书！请检查日期是否正确！\n";
		}
		else {
			cout << "您要查找的图书信息如下:\n\n";
			for (; num > 0; num--) {//输出所有结果
				int temp = mit3->second;//下标
				b2[temp - 1].dispbook(0);//显示图书信息
				mit3++;
			}
		}
	}
	//读取文件
	void read()
	{
		b.clear();
		b2.clear();
		m1.clear();
		m2.clear();
		m3.clear();
		ifstream infile;//只读模式打开book.txt
		infile.open("book.txt", ios::in);
		book temp;
		if (!infile) { cout << "Error!读取文件失败！\n"; }
		else {
			while (infile >> temp) {
				b2.push_back(temp);//压入图书馆
				m1.insert(make_pair(temp.getTitle(), temp.getId()));//书名
				m2.insert(make_pair(temp.getAuthor(), temp.getId()));//作者
				m3.insert(make_pair(temp.getDate().getYear(), temp.getId()));//出版日期
			}
		}
		infile.close();
	}
	//保存用户借阅图书文件
	void save()
	{
		ofstream outfile;
		outfile.open("userborrow.txt", ios::out);
		if (!outfile) { cout << "Error!保存文件失败！\n"; }
		else {
			for (b1 = b.begin(); b1 != b.end(); b1++) {
				outfile << *b1 << endl;
			}
		}
		outfile.close();
		b.clear();
		b2.clear();
		m1.clear();
		m2.clear();
		m3.clear();
	}
};
class admin//管理员类
{
public:
	date d;
	string password;//管理员密码
	vector<user> u;
	vector<user>::iterator u1;
	vector<book> b;
	vector<book>::iterator b1;
	//书籍map
	multimap<string, int> m1;//根据书名查找 First->书名 Second->下标
	multimap<string, int>::iterator mit1;//根据书名查找 对应迭代器
	multimap<string, int> m2;//根据作者查找 First->作者 Second->下标
	multimap<string, int>::iterator mit2;//根据作者查找 对应迭代器
	multimap<int, int> m3;//根据出版日期查找 First->出版日期 年 Second->下标
	multimap<int, int>::iterator mit3;//根据出版日期查找 对应迭代器
	//用户map
	map<long long int, string> m4;//根据学号查找 First->学号 Second->姓名
	map<long long int, string>::iterator mit4;//根据学号查找 对应迭代器
	map<string, long long int> m5;//根据姓名查找 First->姓名 Second->学号
	map<string, long long int>::iterator mit5;//根据姓名查找 对应迭代器
	//构造函数
	admin() {
		password = "123456";//默认密码
	}
	admin(string x) {
		password = x;
	}
	//修改密码
	void setPassword(string x) { password = x; }
	//读取user文件
	void readuser() {
		u.clear();
		m4.clear();
		m5.clear();
		ifstream infile;//只读模式打开user.txt
		infile.open("user.txt", ios::in);
		user temp;
		if (!infile) { cout << "Error!读取文件失败！\n"; }
		else {
			while (infile >> temp) {
				u.push_back(temp);//加入user vector
				m4.insert(make_pair(temp.getId(), temp.getName()));//根据学号查找
				m5.insert(make_pair(temp.getName(), temp.getId()));//根据姓名查找
			}
		}
		infile.close();
	}
	//保存user文件
	void saveuser() {
		ofstream outfile;
		user x;
		outfile.open("user.txt", ios::app);
		if (!outfile) { cout << "Error!保存文件失败！\n"; }
		else {
			for (u1 = u.begin(); u1 != u.end(); u1++) {
				outfile << u1->getId() << " " << u1->getName() << " " << u1->getPassword() << endl;
			}
		}
		outfile.close();
		u.clear();
		m4.clear();
		m5.clear();
	}
	//读取book文件
	void readbook()
	{
		b.clear();
		m1.clear();
		m2.clear();
		m3.clear();
		ifstream infile;//只读模式打开book.txt
		infile.open("book.txt", ios::in);
		book temp;
		if (!infile) { cout << "Error!读取文件失败！\n"; }
		else {
			while (infile >> temp) {
				b.push_back(temp);//加入图书馆书库
				m1.insert(make_pair(temp.getTitle(), temp.getId()));//书名
				m2.insert(make_pair(temp.getAuthor(), temp.getId()));//作者
				m3.insert(make_pair(temp.getDate().getYear(), temp.getId()));//出版日期
			}
		}
		infile.close();
	}
	//保存文件
	void savebook()
	{
		ofstream outfile;
		outfile.open("library.txt", ios::out);
		if (!outfile) { cout << "Error!读取文件失败！\n"; }
		else {
			for (b1 = b.begin(); b1 != b.end(); b1++) {
				outfile << b1->getId() << " " << b1->getTitle() << " " << b1->getAuthor() << " " << b1->getDate() << endl;
			}
		}
		outfile.close();
		b.clear();
		m1.clear();
		m2.clear();
		m3.clear();
	}
	//增加图书
	void addBook() {
		book tem;
		cout << "请依次输入书籍信息:? ?[编号 书名 作者 出版日期 xxxx年xx月]\n";
		cin >> tem;//重载输入运算符
		b.push_back(tem);
		cout << "\n书籍添加成功!\n";
	}
	//删除图书
	void delBook() {
		if (b.empty()) { cout << "? ? ? !!!Error!!!\n书籍容器为空！请先添加书籍！\n"; }
		else {
			for (b1 = b.begin(); b1 != b.end(); b1++) {//输出容器中所有图书
				b1->dispbook(0);
			}
			cout << endl;
			cout << "\n\n请输入要删除书籍的编号:\n";
			int x;
			cin >> x;//输入书籍编号
			b1 = b.begin() - 1 + x;
			cout << *b1 << endl;
			b.erase(b1);
			cout << "删除书籍成功！\n";
		}
	}
	//查找图书 这里暂时调用用户里的查找图书函数
	//查询图书 [图书馆中的图书]
	//按书名查询
	string seaBytitle(string x) {
		mit1 = m1.find(x);//根据书名查找 返回迭代器
		int num = m1.count(x);// x 出现的次数
		if (mit1 == m1.end()) {//如果没找到 find() 会返回m2.end()
			cout << "? ? ?未找到该图书！请检查书名是否正确！\n";
		}
		else {
			cout << "您要查找的图书信息如下:\n\n";
			for (; num > 0; num--) {//输出所有结果
				int temp = mit1->second;//下标
				b[temp - 1].dispbook(0);//显示图书信息
				mit1++;
			}
		}
	}
	//按作者查询
	string seaByauthor(string x) {
		mit2 = m2.find(x);//根据书名查找 返回迭代器
		int num = m2.count(x);// x 出现的次数
		if (mit2 == m2.end()) {//如果没找到 find() 会返回m2.end()
			cout << "? ? ?未找到该图书！请检查作者名是否正确！\n";
		}
		else {
			cout << "您要查找的图书信息如下:\n\n";
			for (; num > 0; num--) {//输出所有结果
				int temp = mit2->second;//下标
				b[temp - 1].dispbook(0);//显示图书信息
				mit2++;
			}
		}
	}
	//按出版日期查询
	string seaBydate(int x) {
		mit3 = m3.find(x);//根据书名查找 返回迭代器
		int num = m3.count(x);
		if (mit3 == m3.end()) {//如果没找到 find() 会返回m3.end()
			cout << "? ? ?未找到该图书！请检查日期是否正确！\n";
		}
		else {
			cout << "您要查找的图书信息如下:\n\n";
			for (; num > 0; num--) {//输出所有结果
				int temp = mit3->second;//下标
				b[temp - 1].dispbook(0);//显示图书信息
				mit3++;
			}
		}
	}
	//修改图书
	void setbook() {
		int number;
		book temp;
		for (b1 = b.begin(); b1 != b.end(); b1++) {//输出所有图书让用户选择编号
			cout << *b1 << endl << endl;
		}
		cout << "请输入要修改的图书编号:" << endl;
		cin >> number;
		system("cls");
		cout << "您要修改的图书信息:" << endl;
		cout << b[number - 1] << endl;//输出该图书信息 确认修改
		b.erase(b.begin() - 1 + number);//删除该图书
		cout << "请依次输入要添加的书籍信息:? ?[编号 书名 作者 出版日期 xxxx年xx月]\n";
		cin >> temp;//输入新图书信息
		b.insert((b.begin() - 1 + number), temp);
		system("cls");
		cout << "? ? \n修改图书信息成功!" << endl;
		savebook();//保存到文件
	}
	//创建用户 增加用户
	void adduser() {
		cout << "请输入要创建的用户信息:? ? ?[学号 姓名 密码]\n";
		user temp;
		cin >> temp;
		u.push_back(temp);//加入user vector
		m4.insert(make_pair(temp.getId(), temp.getName()));//根据学号查找
		m5.insert(make_pair(temp.getName(), temp.getId()));//根据姓名查找
		cout << "创建用户:? ? " << temp << "? ? 成功！\n";
	}
	//删除用户
	void deluser() {
		for (mit4 = m4.begin(); mit4 != m4.end(); mit4++) {//输出所有user
			cout << "? ?" << mit4->first << "? " << mit4->second << endl;
		}
		cout << "请输入要删除的用户学号:\n\n";
		long long int temp;
		cin >> temp;
		mit4 = m4.find(temp);//学号查找
		if (mit4 != m4.end()) {
			cout << "删除用户:? ?";
			cout << mit4->first << "? ? " << mit4->second;
			cout << "? ?成功！\n";
			m4.erase(mit4);
			m5.erase(mit4->second);
		}
		else cout << "\n未找到学号为 " << temp << " 的用户！\n";
	}
	//查询用户 学号
	void seaById() {
		cout << "请输入要查询的学号:\n";
		int id;
		cin >> id;
		mit4 = m4.find(id);//学号查找
		if (mit4 != m4.end()) {
			cout << "您要查找的用户:? ?\n";
			cout << "? ? ?" << mit4->first << "? ? " << mit4->second << endl;
		}
		else cout << "\n未找到学号为 " << id << " 的用户！\n";
	}
	//查询用户 姓名
	void seaByName() {
		cout << "请输入要查询的姓名:\n";
		string name;
		cin >> name;
		mit5 = m5.find(name);
		if (mit5 != m5.end()) {
			cout << "您要查找的用户:? ?\n";
			cout << "? ? ?" << mit5->second << "? ? " << mit5->first << endl;
		}
		else cout << "\n未找到姓名为 " << name << " 的用户！\n";
	}
	//修改用户
	void setuser() {
		for (mit4 = m4.begin(); mit4 != m4.end(); mit4++) {//输出所有user
			cout << "? ?" << mit4->first << "? " << mit4->second << endl;
		}
		cout << "请输入要修改的学号:\n";
		int id;
		cin >> id;
		mit4 = m4.find(id);//学号查找
		if (mit4 != m4.end()) {
			cout << "您要修改的用户:? ?\n";
			cout << "? ? ?" << mit4->first << "? ? " << mit4->second << endl;
			cout << "您输入修改后的 学号 姓名 密码:? ?\n";
			user temp;
			cin >> temp;
			m4.erase(mit4);//删除
			m5.erase(mit4->second);//删除
			m4.insert(make_pair(temp.getId(), temp.getName()));//学号
			m5.insert(make_pair(temp.getName(), temp.getId()));//姓名
			cout << "修改成功！\n";
		}
		else cout << "\n未找到学号为 " << id << " 的用户！\n";
	}
	//验证密码
	bool isPassword(string x) {
		if (password == x) return true;
		else return false;
	}
	//显示所有用户
	void dispalluser() {
		for (u1 = u.begin(); u1 != u.end(); u1++) {
			u1->dispuser();
		}
	}
};
class menu//菜单类
{
public:
	date d;
	book b;
	user u;
	admin a;
	void welcome() {//主欢迎菜单
		system("color 0B");
		cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";
		cout << "■? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?■\n";
		cout << "■? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?■\n";
		cout << "■? ? ? ? ? ? ?┏━━━━━━━━━━━━━━━━━━━━━━━┓? ? ? ? ? ? ? ? ? ? ? ? ? ?■\n";
		cout << "■? ? ? ? ? ? ?┃? ? ? ? ? ? ? ? ? ? ? ?┃? ? ? ? ? ? ? ? ? ? ? ? ? ?■\n";
		cout << "■? ? ? ? ? ? ?┃ 图书馆管理系统 Ver 1.0┃? ? ? ? ? ? ? ? ? ? ? ? ? ?■\n";
		cout << "■? ? ? ? ? ? ?┃? ? ? ? ? ? ? ? ? ? ? ?┃? ? ? ? ? ? ? ? ? ? ? ? ? ?■\n";
		cout << "■? ? ? ? ? ? ?┃? ? ? 山东农业大学? ? ?┃? ? ? ? ? ? ? ? ? ? ? ? ? ?■\n";
		cout << "■? ? ? ? ? ? ?┃? ? ? ? ? ? ? ? ? ? ? ?┃? ? ? ? ? ? ? ? ? ? ? ? ? ?■\n";
		cout << "■? ? ? ? ? ? ?┃? By? Leo? 2018.5? ? ? ┃? ? ? ? ? ? ? ? ? ? ? ? ? ?■\n";
		cout << "■? ? ? ? ? ? ?┃? ? ? ? ? ? ? ? ? ? ? ?┃? ? ? ? ? ? ? ? ? ? ? ? ? ?■\n";
		cout << "■? ? ? ? ? ? ?┗━━━━━━━━━━━━━━━━━━━━━━━┛? ? ? ? ? ? ? ? ? ? ? ? ? ?■\n";
		cout << "■? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?■\n";
		cout << "■? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?■\n";
		cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";
		cout << "\n? ? ? ? ? ? ? ? ? 按 任 意 键 清 屏? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? \n";
		//Sleep(2000);
		system("pause");
		system("cls");
		system("color 0F");
	}
	void selectmenu() {//选择菜单 管理员or用户
		cout << "? ? ? ? ? ? ? [0]? 退出系统\n";
		cout << "? ? ? ? ? ? ? [1]? 管理员界面\n";
		cout << "? ? ? ? ? ? ? [2]? 用户界面\n";
		cout << "请输入要进入的页面:\n";
		int command;
		cin >> command;
		switch (command) {
		case 0: {
			cout << "? ? ? ? ?-? ? ?感谢使用? -? 正在退出系统? ?-? ?\n";
			system("pause");
			system("cls");
			exit(0); //exit(1)是异常退出 exit(0)是正常退出
			break;
		}
		case 1: {
			cout << "请输入管理员初始密码:? ?[123456] \n";
			string pass;
		rcin: while (cin >> pass)
		{
			if (u.isPassword(pass)) { system("cls"); a.readbook(); a.readuser(); Administrator(); }
			else {
				cout << "密码输入错误！请重新输入:\n";
				goto rcin;
			}
		}
		break;
		}
		case 2: {
			cout << "请输入用户初始密码:? ?[123456] \n";
			string pass;
		recin: while (cin >> pass)
		{
			if (u.isPassword(pass)) {
				system("cls");
				int a; string b, c;
				cout << "请输入用户信息：[学号 姓名 密码]\n";
				cin >> a >> b >> c;
				u.setId(a); u.setName(b); u.setPassword(c);
				u.read();
				cout << "初始化用户完成！进入用户操作菜单！\n";
				useroperator();


			}
			else {
				cout << "密码输入错误！请重新输入:\n";
				goto recin;
			}
		}
		break;
		}
		default: {
			cout << "Command Error！请重新输入！" << endl;
			selectmenu();
		}
		}
	}
	void Administrator() {//管理员菜单
	amenu:cout << "■■■■■■■■■■■■管理员系统■■■■■■■■■■■■■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┏━━━━━━━━━━━━━━┓? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┃ [0] 退出系统 ┃? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┣━━━━━━━━━━━━━━┫? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┃ [1] 增加图书 ┃? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┣━━━━━━━━━━━━━━┫? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┃ [2] 删除图书 ┃? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┣━━━━━━━━━━━━━━┫? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┃ [3] 查找图书 ┃? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┣━━━━━━━━━━━━━━┫? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┃ [4] 修改图书 ┃? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┣━━━━━━━━━━━━━━┫? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┃ [5] 创建用户 ┃? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┣━━━━━━━━━━━━━━┫? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┃ [6] 删除用户 ┃? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┣━━━━━━━━━━━━━━┫? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┃ [7] 查询用户 ┃? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┣━━━━━━━━━━━━━━┫? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┃ [8] 修改用户 ┃? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┣━━━━━━━━━━━━━━┫? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┃ [9] 修改密码 ┃? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┗━━━━━━━━━━━━━━┛? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■■■■■■■■■■■[-1]返回上一层■■■■■■■■■■■■\n";
		cout << "输入要进行的操作：";
		int command;
	cincom: cin >> command;
		switch (command) {
		case -1: {
			system("cls");
			selectmenu();//返回上一层
		}
		case 0: {//退出系统
			a.savebook();
			a.saveuser();
			cout << "? ? ? ? ?-? ? ?感谢使用? -? 正在退出系统? ?-? ?\n";
			system("pause");
			system("cls");
			exit(0); //exit(1)是异常退出 exit(0)是正常退出
			break;
		}
		case 1: {//增加图书
			system("cls");
			a.addBook(); goto amenu;//返回主菜单
			break; }
		case 2: {//删除图书
			system("cls");
			a.delBook(); goto amenu;//返回主菜单
			break; }
		case 3: {//查找图书
			system("cls");
		chaxun:cout << "? ? ? ? ? ? ?[1]按书名查询\n";
			cout << "? ? ? ? ? ? ?[2]按作者查询\n";
			cout << "? ? ? ? ? ? ?[3]按出版日期查询\n";
			cout << "请输入查询方式:\n";
			int way;
			cin >> way;
			switch (way) {
			case 1: {
				cout << "请输入要查询的书名:\n";
				string title;
				cin >> title;
				//u.seaBytitle(title);
				a.seaBytitle(title);
				system("pause");
				system("cls");
				goto amenu;
			}
			case 2: {
				cout << "请输入要查询的作者:\n";
				string author;
				cin >> author;
				//u.seaByauthor(author);
				a.seaByauthor(author);
				system("pause");
				system("cls");
				goto amenu;
			}
			case 3: {
				cout << "请输入要查询的出版日期: [****年]\n";
				int year;
				cin >> year;
				//u.seaBydate(year);
				a.seaBydate(year);
				system("pause");
				system("cls");
				goto amenu;
			}
			default: {
				system("cls");
				cout << "? ? ? ?Command Error！请重新输入！" << endl;
				goto chaxun;
			}
			}
		}
		case 4: {//修改图书
			system("cls");
			a.setbook();
			goto amenu;
			break;
		}
		case 5: {//创建用户
			system("cls");
			a.adduser();
			system("pause");
			goto amenu;
			break;
		}
		case 6: {//删除用户
			system("cls");
			a.deluser();
			system("pause");
			goto amenu;
			break;
		}
		case 7: {//查询用户
			system("cls");
			cout << "? ? ? ? ? ? ?[1]按学号查询\n";
			cout << "? ? ? ? ? ? ?[2]按姓名查询\n";
			cout << "请输入查询方式:\n";
			int way;
			cin >> way;
			switch (way) {
			case 1:
				a.seaById();
				system("pause");
				system("cls");
				goto amenu;
				break;
			case 2:
				a.seaByName();
				system("pause");
				system("cls");
				goto amenu;
				break;
			}
		}
		case 8: {//修改用户
			system("cls");
			a.setuser();
			system("pause");
			system("cls");
			goto amenu;
			break;
		}
		case 9: {//修改密码
			system("cls");
			string pass;
			cout << "请输入原密码:\n";
			cin >> pass;
			cout << endl;
			if (a.isPassword(pass)) {
				cout << "请输入新密码:\n";
				cin >> pass;
				a.setPassword(pass);
				cout << endl;
				cout << "密码修改成功！\n";
			}
			else cout << "Error！ 密码输入错误！ 已返回主菜单！\n";
			goto amenu;//返回主菜单
			break; }
		default: {
			cout << "Command Error！请重新输入！" << endl;
			goto cincom; }
		}
	}
	void useroperator() {//用户菜单
	umenu:cout << "■■■■■■■■■■■■■用户系统■■■■■■■■■■■■■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┏━━━━━━━━━━━━━━┓? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┃ [0] 退出系统 ┃? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┣━━━━━━━━━━━━━━┫? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┃ [1] 借阅图书 ┃? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┣━━━━━━━━━━━━━━┫? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┃ [2] 续借图书 ┃? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┣━━━━━━━━━━━━━━┫? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┃ [3] 归还图书 ┃? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┣━━━━━━━━━━━━━━┫? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┃ [4] 查询图书 ┃? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┣━━━━━━━━━━━━━━┫? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┃ [5] 显示用户 ┃? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┣━━━━━━━━━━━━━━┫? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┃ [6] 修改密码 ┃? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■? ? ? ? ? ? ? ? ? ┗━━━━━━━━━━━━━━┛? ? ? ? ? ? ? ? ? ? ? ■\n";
		cout << "■■■■■■■■■■■[-1]返回上一层■■■■■■■■■■■■\n";
		cout << "输入要进行的操作：";
		int command;
		cin >> command;
		switch (command) {
		case -1: {
			system("cls");
			selectmenu();//返回上一层
		}
		case 0: {//退出系统
			u.save();
			cout << "? ? ? ? ?-? ? ?感谢使用? -? 正在退出系统? ?-? ?\n";
			system("pause");
			system("cls");
			exit(0); //exit(1)是异常退出 exit(0)是正常退出
			break;
		}
		case 1: {//借阅图书
			int x;
			if (u.b.size() >= 10) cout << "\n借阅数量已达10本上限!\n";
			else {
				u.dispallbook();//显示所有图书
				cout << "\n请输入借阅的图书编号:\n";
				cin >> x;
				u.borrowbook(x);
				cout << u.b2[x - 1] << endl;
				cout << "借阅成功！\n";
				system("pause");
				system("cls");
				goto umenu;
			}
			break;
		}
		case 2: {//续借图书
			u.reborrowbook();
			system("pause");
			system("cls");
			goto umenu;
			break;
		}
		case 3: {//归还图书
			if (u.b.empty()) {
				system("cls");
				cout << "\n该用户未借阅任何图书！" << endl;
				system("pause");
				goto umenu;
			}
			else {
				u.dispuser();//显示用户信息 包括借阅的图书信息
				int x;
				cout << "请输入要归还的图书编号:\n";
				cin >> x;
				u.returnbook(x);
				cout << endl;
				goto umenu;
			}
			break;
		}
		case 4: {//查询图书
			system("cls");
		chaxun:cout << "? ? ? ? ? ? ?[1]按书名查询\n";
			cout << "? ? ? ? ? ? ?[2]按作者查询\n";
			cout << "? ? ? ? ? ? ?[3]按出版日期查询\n";
			cout << "请输入查询方式:\n";
			int way;
			cin >> way;
			switch (way) {
			case 1: {
				cout << "请输入要查询的书名:\n";
				string title;
				cin >> title;
				u.seaBytitle(title);
				system("pause");
				system("cls");
				goto umenu;
			}
			case 2: {
				cout << "请输入要查询的作者:\n";
				string author;
				cin >> author;
				u.seaByauthor(author);
				system("pause");
				system("cls");
				goto umenu;
			}
			case 3: {
				cout << "请输入要查询的出版日期: [****年]\n";
				int year;
				cin >> year;
				u.seaBydate(year);
				system("pause");
				system("cls");
				goto umenu;
			}
			default: {
				system("cls");
				cout << "? ? ? ?Command Error！请重新输入！" << endl;
				goto chaxun;
			}
			}
			break;
		}
		case 5: {//显示用户
			u.dispuser();
			system("pause");
			system("cls");
			goto umenu;
			break;
		}
		case 6: {//修改密码
			system("cls");
			string pass;
			cout << "请输入原密码:\n";
			cin >> pass;
			cout << endl;
			if (u.isPassword(pass)) {
				cout << "请输入新密码:\n";
				cin >> pass;
				u.setPassword(pass);
				cout << endl;
				cout << "密码修改成功！\n";
			}
			else cout << "Error！ 密码输入错误！ 已返回主菜单！\n";
			goto umenu;//返回主菜单
			break;
		}
		default: {
			system("cls");
			cout << "? ? ? ?Error！? Error！? Error！\n";
			cout << "? ? ? ? 输入命令错误! 请重新输入! \n";
			cout << "? ? ? ?Error！? Error！? Error！\n";
			goto umenu;
		}
		}
	}
};
int main()
{
	menu m;//菜单类
	m.welcome();//欢迎菜单
	m.selectmenu();//选择 Administrator or useroperator 菜单
}