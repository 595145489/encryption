#include<iostream>
#include<malloc.h>
#include<vector>
#include"fstream"
#include<string>
#include<unordered_map>
#include<list>

using namespace std;

#define exclusive_or 0x48

void save_file();
struct Website
{
	string Webname;
	vector<string> account;
	vector<string> password;
};


unordered_map<string,Website*>* hashinfo;



void openaccountdb() {

	fstream db("account.db", std::fstream::in);
	if (!db.is_open())
	{
		cout << "Error opening file";
		exit(1);
	}

	hashinfo = new unordered_map<string, Website*>;
	hashinfo->clear();

	string line,cachewebname = "";
	int thislinenumber = 0;

	while (getline(db,line)) {
	
		string cache = "";
		Website* thisWWW = NULL;
		int size = line.size();

		for (int i = 0, postion =  0; i < size; i++) {
			//½âÃÜ
			line[i] = (line[i]);

			
			if (i == 0 && line[i] == ' ') {
				unordered_map<string, Website*>::iterator it = hashinfo->find(cachewebname);
				if (it == hashinfo->end()) {
					exit(1);
				}
				thisWWW = it->second;
				postion++;
				continue;
			}
			else if (i == 0) {
				thisWWW = new Website;
			}


			if(line[i] != ' ')
				cache += line[i];
			if (line[i] == ' '|| i == size - 1) {
				switch (postion)
				{
				case 0:
					thisWWW->Webname = cache;
					cachewebname = thisWWW->Webname;
					hashinfo->insert(make_pair(thisWWW->Webname, thisWWW));
					break;
				case 1:
					thisWWW->account.push_back(cache);
					break;
				case 2:
					thisWWW->password.push_back(cache);
					break;
				default:
					break;
				}
				postion++;
				cache = "";
			}
		}
		thislinenumber++;
	}
	db.close();
}


void initDB() {
	openaccountdb();
}


void showtotalweb() {
	unordered_map<string, Website*>::iterator it = hashinfo->begin();
	for (;it!= hashinfo->end();it++) {
		cout << it->first << endl;
	}
	return;
};


void getaccount() {

	string webname;
	cout << "Please input Webname" << endl;
	cin >> webname;
	unordered_map<string, Website*>::iterator it = hashinfo->find(webname);
	if (it == hashinfo->end()) {
		cout << "not found" << endl;
		return;
	}

	for (size_t i = 0; i < it->second->account.size() ; i++)
	{
		cout << "webname :: " << it->first << "  account :: " << it->second->account[i] << "  password :: " << it->second->password[i] << endl;
	}
	

};


void addweb() {

	Website* newwebsite;
	string webname,account,password,YandN,allstring = "";
	cout << "Please input Webname" << endl;
	cin >> webname;
	cout << "Please input account" << endl;
	cin >> account;
	cout << "Please input password" << endl;
	cin >> password;
	
	while (1) {
		cout << "would you please confirm that ? (Y/N)" << endl;
		cin >> YandN;
		if (YandN == "Y")
			break;
		else if (YandN == "N")
			return;
	}
	unordered_map<string, Website*>::iterator it = hashinfo->find(webname);
	if (it == hashinfo->end()) {

		newwebsite = new Website;
		newwebsite->Webname = webname;
		hashinfo->insert(make_pair(webname, newwebsite));
		allstring += webname;
	}
	else {
		newwebsite = it->second;
	}
	newwebsite->account.push_back(account);
	newwebsite->password.push_back(password);


	save_file();
	cout << "Add Web Success" << endl;
};







void save_file() {

	fstream db("account.db", ios::out );
	if (!db.is_open())
	{
		cout << "Error opening file";
		exit(1);
	}

	unordered_map<string, Website*>::iterator it = hashinfo->begin();
	string cachestring;
	for (; it != hashinfo->end(); it++) {
		for (size_t i = 0; i < it->second->account.size(); i++)
		{
			if (i > 0)
				cachestring =  ' ' + it->second->account[i] + ' ' + it->second->password[i] ;
			else
				cachestring = it->second->Webname + ' ' + it->second->account[i] + ' ' + it->second->password[i];

			//×Ö·û´®¼ÓÃÜS
			for (int size = 0; size < cachestring.size();size++) {


			}
			db << cachestring << "\n";
		}
	}
	db.close();
}



