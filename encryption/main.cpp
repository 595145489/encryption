#include<iostream>
#include<string>
#include<unordered_map>
#define JUMP_EXIT0 goto Exit0;

using namespace std;

bool Getpassword();
void setpassword();
void initDB();
void showtotalweb();
void getaccount();
void addweb();

char help[26] = { 'P','l','e','a','s','e',' ','i','n','p','u','t',' ','y','o','u','r',' ','c','o','m','m','a','n','d' };

//文本加密
int main() {


	bool result = Getpassword();

	if (!result)
		return 0;
	
	string command;
	initDB();
	cout << help << endl;
	cout << "command:sp(设置密码),sw(显示所有网站),gc(获取网站下的所有账号密码),aw(新增账号),out(退出)" << endl;
	while (true)
	{
		cin >> command;
		if (command == "sp") {
			setpassword();
		}
		else if (command == "out") {
			break;
		}
		else if (command == "sw") {
			showtotalweb();
		}
		else if (command == "gc") {
			getaccount();
		}
		else if (command == "aw") {
			addweb();
		}
		else {
			cout << "not found command" << endl;
		}
	}
	return 0;
}

