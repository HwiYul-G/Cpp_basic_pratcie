/*
	string class 만들어보기!
*/
#include <iostream>
#include <string.h>

class string {
	char* str;
	int len;
public:
	string(char c, int n);	// 문자 c가 n개 있는 문자열로 정의
	string(const char* s);
	string(const string& s);
	~string();

	void add_string(const string& s);	// str 뒤에 s를 붙인다.
	void copy_string(const string& s);	// str에 s를 복사한다.
	int strlen();	// 문자열 길이 리턴
	void print_string()	// 출력
};

string::string(char c, int n) {
	len = n;
	str = new char[len + 1];
	for (int i = 0; i < len; i++) {
		str[i] = c;
	}
	str[len] = (char)'\0';
}
string::string(const char* s) {
	len = 0;
	while (*s) {
		len++;
		s++;
	}
	str = new char[len + 1];
	s -= len;
	for (int i = 0; i < len; i++, s++) {
		str[i] = *s;
	}
	str[len] = '\0';
}
string::string(const string& s) {
	// 복사생성자
	len = s.len;
	str = new char[len + 1]; // 깊은 복사!
	char* c = s.str;
	for (int i = 0; i < len; i++) {
		str[i] = *c;
	}
	str[len] = NULL;
}
string::~string() {
	if (str) {
		delete[] str;
	}
}

void string::add_string(const string& s) {
	len += s.len;
	char* new_str = new char[len+1];
	char* original = str;
	char* add = s.str;
	
	int i = 0;
	while (*original) {
		new_str[i++] = *original;
		original++;
	}
	while (*add) {
		new_str[i++] = *add;
		add++;
	}
	new_str[len] = '\0';

	if (str) {
		delete[] str;
	}
	str = new char[len + 1];
	char* temp = new_str;

	i = 0;
	while (*temp) {
		str[i++] = *temp;
		temp++;
	}
	str[i] = '\0';
}
void string::copy_string(const string& s) {
	if (str) delete[] str;
	len = s.len;
	str = new char[len + 1];

	char* c = s.str;
	for (int i = 0; i < len; i++, c++) {
		str[i] = *c;
	}
	str[len] = NULL;
}
int string::strlen() { return len; }
void string::print_string() {
	;
	std::cout << "내용: " << str << std::endl;
}