#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class CreatePDL {
	fstream *fin;
	fstream *fout;
public:
	CreatePDL(string filename, int mode);
	~CreatePDL();	
	void insertClass(string str_class);	//클래스 추가
	void insertVal(string className, string str_val);		//해당 클래스에 변수 추가
	void insertFunc(string className, string str_func);	//해당 클래스에 함수 추가		
	void insertSource(string className, string str_func, string content);	//해당 클래스에 생성자, 소멸자, 함수의 끝에 소스 추가
	void lastClassLoc(int len);
};
CreatePDL::CreatePDL(string filename, int mode = ios::out | ios::ate | ios::binary) {
	fin = new fstream;
	fout = new fstream;
	fin->open(filename, ios::in || ios::binary);
	fout->open(filename, mode);
	if (!fout ) {
		cout << "파일을 열수 없다.";
		return;
	}
	string default = "namespace PDL\n{\n}";
	*fout << default;	
}
CreatePDL::~CreatePDL() {	
	fin->close();
	fout->close();
	delete fin;
	delete fout;
}
void CreatePDL::insertClass(string className) {
	string str_class = "\n\tclass " + className + "\n\t{\n\tpublic:\n\t};\n\n";
	int len = str_class.length();	
	lastClassLoc(len);	
	*fout << str_class;
	
	fin->seekg(0, ios::beg);
	fout->seekp(0, ios::beg);
}
void CreatePDL::insertVal(string className, string str_val) {
	string arr;
	int c, cnt = 0;
	str_val = "\n\t\t" + str_val;
	while ((c=fin->get()) != EOF) {
		arr += c;
		cnt++;
		if (char(c) == '\n') {
			int pos = arr.find(className, 0);
			if (pos != string::npos) {
				string temp;
				int cur = cnt + 2; //삽입해야 할 위치				
				fin->seekg(cur, ios::beg);
				int c2;
				while ((c2 = fin->get()) != EOF) {
					temp += c2;
				}				
				fout->seekp(cur, ios::beg);
				*fout << str_val;
				*fout << temp;				
			}
			else
				arr = "";
		}
	}
	fin->clear();
	fout->clear();
	fin->seekg(0, ios::beg);
	fout->seekp(0, ios::beg);
	
}
void CreatePDL::insertFunc(string className, string str_func) {
	string arr;
	int c, cnt = 0;
	bool find = false;
	str_func = "\n\t\t" + str_func + "\n\t\t{\n\t\t}";
	while ((c = fin->get()) != EOF) {
		arr += c;
		cnt++;
		if (char(c) == '\n') {
			if (!find) {	//클래스 이름을 못찾았을 때
				int pos = arr.find(className, 0);
				if (pos != string::npos) {
					find = true;
				}
				else
					arr = "";
			}
			else {
				int pos = arr.find("};", 0);
				if (pos != string::npos) {
					string temp;
					int cur = cnt - 5; //삽입해야 할 위치				
					fin->seekg(cur, ios::beg);
					int c2;
					while ((c2 = fin->get()) != EOF) {
						temp += c2;
					}
					fout->seekp(cur, ios::beg);
					*fout << str_func;
					*fout << temp;
					break;
				}
				else
					arr = "";
			}
		}
	}
	fin->clear();
	fout->clear();
	fin->seekg(0, ios::beg);
	fout->seekp(0, ios::beg);
}
void CreatePDL::insertSource(string className, string str_func, string content) {
	
}
void CreatePDL::lastClassLoc(int len) {	
	fout->seekp(-2, ios::end);
	fin->seekg(-2, ios::end);
	string buf, space;
	for (int i = 0; i < len; i++)
		space += ' ';
	*fin >> buf;	
	buf = space + buf;
	*fout << buf;
	fout->seekp(-1-len, ios::end);
}

int main() {
	CreatePDL c("a.h");
	string s = "abc";
	c.insertClass(s);
	c.insertClass("PKT_REQUEST_ENTER_CHANNEL_WRITE");	
	c.insertVal("abc", "int a;");
	c.insertVal("abc", "int b;");
	c.insertVal("PKT_REQUEST_ENTER_CHANNEL_WRITE", "int c;");
	c.insertClass("PKT_REQUEST_ENTER_CHANNEL_READ");
	c.insertFunc("abc", "void getAbc()");
	c.insertFunc("PKT_REQUEST_ENTER_CHANNEL_WRITE", "void set_channel(int& x)");
	c.insertFunc("PKT_REQUEST_ENTER_CHANNEL_WRITE", "void get_channel()");
}