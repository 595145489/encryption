#include<iostream>
#include<malloc.h>
#include"Md5Encode.h"
#include<vector>
#include"fstream"
#include<string>

using namespace std;


#ifndef JUMP_EXIT0
#define JUMP_EXIT0 goto Exit0;
#endif 



char Invalid[] = { 'P','a','s','s','w','o','r','d',' ','i','s',' ','I','n','v','a','l','i','d' };
char Success[] = { 'P','a','s','s','w','o','r','d',' ','i','s',' ','S','u','c','c','e','s','s' };
char offset[] = { '/','@','0','*','%','x','1','9','0','^' };

vector<char>*  openfile() {

	fstream config("config.ini",std::fstream::in);
	if (!config.is_open())
	{
		cout << "Error opening file";
		exit(1);
	}

	vector<char>* password = new vector<char>;
	char input;
	while (input = config.get()) {
		if (input != 10 && input != EOF)
			password->push_back(input);
		else
			break;
	}

	if (password->size() <= 0) {
		config.close();
		exit(1);
	}
		

	return password;
}


vector<char>* GetInput() {

	cout << "Please input your password! " << endl;
	char input;
	string inputpassword = "";
	while ((input = getchar()) != 10)
		inputpassword += input;
	inputpassword += offset;

	Md5Encode Md5;
	string Md5Inputpassword = Md5.Encode(inputpassword);
	vector<char>* Md5password = new vector<char>;
	for (int i = 0;i<Md5Inputpassword.size();i++) {
		Md5password->push_back(Md5Inputpassword[i]);
	}
	return Md5password;

}

bool Getpassword() {

	vector<char>* password = openfile();
	vector<char>* inputpassword = GetInput();
	int size = 0 ;
	vector<char>::iterator it1 = password->begin();
	vector<char>::iterator it2 = inputpassword->begin();

	if ((size = password->size() )!= inputpassword->size()) {
		JUMP_EXIT0
	}
	for (int i = 0 ;i<size;it1++,it2++,i++) {
		if (*it1 != *it2) {
			JUMP_EXIT0
		}
	}

	cout << Success << endl;
	return true;
Exit0:
	cout << Invalid << endl;
	return false;
}

void setpassword() {

	string inputpassword;
	cin >> inputpassword;
	Md5Encode Md5;
	string Md5Inputpassword = Md5.Encode(inputpassword+offset);
	fstream config("config.ini", std::fstream::out);
	config.write(Md5Inputpassword.c_str(), Md5Inputpassword.size());
	cout << "Set " << Success << endl;

}


