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

//�ı�����
int main() {


	bool result = Getpassword();

	if (!result)
		return 0;
	
	string command;
	initDB();
	cout << help << endl;
	cout << "command:sp(��������),sw(��ʾ������վ),gc(��ȡ��վ�µ������˺�����),aw(�����˺�),out(�˳�)" << endl;
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

