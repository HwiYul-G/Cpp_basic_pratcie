#include <iostream>
#include <string.h>

class MyString {
	char* string_content;	// 문자열 데이터를 가리키는 포인터
	int string_length;		// 문자열 길이
public:
	// 문자 하나로 생성
	MyString(char c);
	// 문자열로부터 생성
	MyString(const char* str);
	// 복사 생성자
	MyString(const MyString& str);
	
	int length() const;
	void print() const;
	void println() const;

	// assing 함수 : '='과 동일한 역할으 함.
	// str.assign("abc"); 을 하면 str에 원래 있던 문자열이 지워지고 abc가 들어간다.
	MyString& assign(const MyString& str);
	MyString& assign(const char* str);

	~MyString();
};

/*
	어떠한 방식으로 문자열을 저장할까?
	string_content에 C 형식의 문자열(null 종료 문자열)을 보관하는 것이 좋을까?
	아니면 필요 없는 정보들(null 종료 문자열)을 빼고 실제 '문자'만 해당하는 부분만 넣을까?

	C 형식의 문자열을 그대로 보관하면, 문자열의 끝 부분을 쉽게 체크할 수 있다는 장점이 있다.
	하지만 이 문제는 string_length라는 변술르 도입함으로 해결할 수 있게 되었다.

	따라서 Mystring class에선 실제 문자에만 해당하는 내용만(null 제외)을 string_content에 보관하겠다.
*/

MyString::MyString(char c) {
	string_content = new char[1];
	string_content[0] = c;
	string_length = 1;
}
MyString::MyString(const char* str) {
	string_length = strlen(str); // null을 제외한 문자 길이가 추출됨
	string_content = new char[string_length];

	for (int i = 0; i != string_length; i++)
		string_content[i] = str[i];
}
MyString::MyString(const MyString& str) {
	string_length = str.string_length;
	for (int i = 0; i != string_length; i++)
		string_content[i] = str.string_content[i];
}

int MyString::length() const { 
	return string_length; 
	/*
		length 함수 역시 string_length 값을 읽기만 하므로 상수함수로 정의

		이러한 방식으로 문자열의 길이를 구한다면, 
		문자열 조작시에 string_length의 값을 올바른 값으로 설정해야만 한다.

		예를 들어서 두 문자열을 서로 더해서 새로운 문자열을 만들 때 
		새로운 문자열의 string_length는 두 문자열의 string_length의 합이 된다.
		마찬가지로 부분 문자열을 추출하거나 문자 하나를 지우는 등 
		모든 작업시 string_length 값을 정확히 조절해야한다.
	*/
}
void MyString::print() const {
	for (int i = 0; i != string_length; i++)
		std::cout << string_content[i];
}
void MyString::println() const {
	for (int i = 0; i != string_length; i++) {
		std::cout << string_content[i];
	}
	std::cout << std::endl;
}

MyString& MyString::assign(const MyString& str) {
	if (str.string_length > string_length) {
		delete[] string_content;
		string_content = new char[str.string_length];
	}

	for (int i = 0; i != str.string_length; i++)
		string_content[i] = str.string_content[i];

	string_length = str.string_length;

	return *this;
}
MyString& MyString::assign(const char* str) {
	int str_length = strlen(str);
	if (str_length > string_length) {
		delete[] string_content;
		string_content = new char[str_length];
	}

	for (int i = 0; i != str_length; i++)
		string_content[i] = str[i];

	string_length = str_length;

	return *this;
}
/*
	MyString& MyString::assign(const MyString& str)과
	MyString& MyString::assign(const char* str)을
	효율을 위해 기존 글의 길이보다 짧은 것을 할당할 경우에는 따로 동적할당을 하지 않는다.
	그래서 그 경우엔 그냥 그대로 복사해서 사용한다.

	그런데 이 방식은 좀 문제가 있다.
	MyString str1("very very very long string");
	str1.assign("short string");
	str1.assign("very long string");

	이러한 방식으로 할당했을 때 문제를 볼 수 있다.
	예를 들어서 str1에 매우 긴 약 1000 byte의 문자열을 할당했다고 하자.
	그리고 str1에 다시 짧은 문자열을 할당했다고 하자

	우리가 만든 assign 함수에 따르면 이미 긴 문자열이 할당된 경우 다 짧은 문자열을 assign하면
	기존의 것을 지우고 동적할당하지 않고 string_length를 줄이고 앞부분을 짧은 문자열로 덮어 씌운다.

	그런데 문제는 이렇게 짧아진 str1에 다시 긴 문자열을 assign 할 때 발생하게 된다.
	비록 str1에는 이미 처음 할당했던 1000byte의 공간이 있음에도 현재 짧은 문자열이 있어서
	새롭게 긴 문자열 할당시 1000byte가 할당되어 있다는 사실을 알 수 없게 된다.

	따라서 assign 함수는 문자열에 짧은 문자열을 위한 작은 크기에 공간만이 할당되어 있다고 생각하여
	메모리를 해제하고 다시 많은 양의 메모리를 할당하는 매우 비효율적인 작업을 하게 된다.
	
	이러한 비효율을 막기 위해 얼마나 많은 공간이 할당되어 있는지 알 수 있는 정보를 따로 관리하는 것이 좋을 것이라 A생각됨
	이를 위해 memory_capacity라는 현재 할당된 메모리 공간의 크기를 나타내는 새로운 변수를 추가하자!
	==> String2.cpp
*/

MyString::~MyString() { 
	delete[] string_content; 
	/*
		string_content를 각 생성자에서 동적할당했기에 반드시 소멸자에서 이를 동적해제 해야한다.
		이것이 클래스의 큰 장점이다. C에서 구조체로 문자열을 구현하면 이를 일일히 해제하는 것도 처리해줘야 한다.
		말 그대로, 클래스를 사용하는 사람은 안에서 어떻게 돌아가는지 신경 안쓰고 사용할 수 있게 된다.
	*/
}

int main() {
	MyString str1("hello world!");
	MyString str2(str1);

	str1.println();
	str2.println();

	return 0;
}