/*
	(리턴 타입) operator(연산자) (연산자가 받는 인자)

	위 방법 외에는 함수 이름으로 연산자를 절대 넣을 수 없다.
	예를 들어서 ==을 오버로딩 하고 싶다면
		== 연산자는 언제나 결과값이 bool이고
		== 로 비교하는 것 하나만 받게 된다.

	따라서 MyString 클래스에서 == 연산자를 오버로딩한다면
	bool operator== (MyString& str); 이다.

	이렇게 정의하고 나서 str1 == str2;라는 명령을 수행한다면
	이는 str1.operator==(str2)로 내부적으로 변환되어 처리된다.

	그리고 그 결과값을 리턴하게 된다. 사실 operator==를 만드는 것 자체는 별로 어려운 일은 아니다.
	왜냐하면 이미 MyString 클래스에서 compare라는 좋은 함수를 제공하고 있기 때문이다.

	그래서 간단하게 만들어 보면 아래와 같다.
	bool operator==(MyString& str){
		return !compare(str); // str1과 같으면 compare에서 0을 리턴한다. 0은  false
	}
*/
#include <string.h>
#include <iostream>

class MyString {
	char* string_content;  // 문자열 데이터를 가리키는 포인터
	int string_length;     // 문자열 길이

	int memory_capacity;  // 현재 할당된 용량

public:
	// 문자 하나로 생성
	MyString(char c);

	// 문자열로 부터 생성
	MyString(const char* str);

	// 복사 생성자
	MyString(const MyString& str);

	~MyString();

	int length() const;
	int capacity() const;
	void reserve(int size);

	void print() const;
	void println() const;

	char at(int i) const;

	int compare(MyString& str);
	bool operator==(MyString& str);
};

MyString::MyString(char c) {
	string_content = new char[1];
	string_content[0] = c;
	memory_capacity = 1;
	string_length = 1;
}
MyString::MyString(const char* str) {
	string_length = strlen(str);
	memory_capacity = string_length;
	string_content = new char[string_length];

	for (int i = 0; i != string_length; i++) string_content[i] = str[i];
}
MyString::MyString(const MyString& str) {
	string_length = str.string_length;
	string_content = new char[string_length];

	for (int i = 0; i != string_length; i++)
		string_content[i] = str.string_content[i];
}
MyString::~MyString() { delete[] string_content; }
int MyString::length() const { return string_length; }
void MyString::print() const {
	for (int i = 0; i != string_length; i++) std::cout << string_content[i];
}
void MyString::println() const {
	for (int i = 0; i != string_length; i++) std::cout << string_content[i];

	std::cout << std::endl;
}
int MyString::capacity() const { return memory_capacity; }
void MyString::reserve(int size) {
	if (size > memory_capacity) {
		char* prev_string_content = string_content;

		string_content = new char[size];
		memory_capacity = size;

		for (int i = 0; i != string_length; i++)
			string_content[i] = prev_string_content[i];

		delete[] prev_string_content;
	}

	// 만일 예약하려는 size 가 현재 capacity 보다 작다면
	// 아무것도 안해도 된다.
}
char MyString::at(int i) const {
	if (i >= string_length || i < 0)
		return 0;
	else
		return string_content[i];
}
int MyString::compare(MyString& str) {
	// (*this) - (str) 을 수행해서 그 1, 0, -1 로 그 결과를 리턴한다
	// 1 은 (*this) 가 사전식으로 더 뒤에 온다는 의미. 0 은 두 문자열
	// 이 같다는 의미, -1 은 (*this) 사 사전식으러 더 앞에 온다는 의미이다.

	for (int i = 0; i < std::min(string_length, str.string_length); i++) {
		if (string_content[i] > str.string_content[i])
			return 1;

		else if (string_content[i] < str.string_content[i])
			return -1;
	}

	// 여기 까지 했는데 끝나지 않았다면 앞 부분 까지 모두 똑같은 것이 된다.
	// 만일 문자열 길이가 같다면 두 문자열은 아예 같은 문자열이 된다.

	if (string_length == str.string_length) return 0;

	// 참고로 abc 와 abcd 의 크기 비교는 abcd 가 더 뒤에 오게 된다.
	else if (string_length > str.string_length)
		return 1;

	return -1;
}
bool MyString::operator==(MyString& str) {
	return !compare(str);  // str 과 같으면 compare 에서 0 을 리턴한다.
}

int main() {
	MyString str1("a word");
	MyString str2("sentence");
	MyString str3("sentence");

	if (str1 == str2)
		std::cout << "str1 와 str2 같다." << std::endl;
	else
		std::cout << "st1 와 str2 는 다르다." << std::endl;

	if (str2 == str3)
		std::cout << "str2 와 str3 는 같다." << std::endl;
	else
		std::cout << "st2 와 str3 는 다르다" << std::endl;
}