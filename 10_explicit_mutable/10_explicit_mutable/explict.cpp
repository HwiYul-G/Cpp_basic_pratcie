#include <iostream>

class MyString {
	char* string_content; // 문자열 데이터를 가리키는 포인터
	int string_length;
	int memory_capacitiy;
public:
	explicit MyString(int capacity);
	MyString(const char* str);
	MyString(const MyString& str);

	~MyString();

	int length() const;
};

explicit MyString::MyString(int capacity) {
	string_content = new char[capacity];
	string_length = 0;
	memory_capacitiy = capacity;
	std::cout << "Capacitiy : " << capacity << std::endl;
}

MyString::MyString(const char* str) {
	string_length = 0;
	while (str[string_length++]) {}

	string_content = new char[string_length];
	memory_capacitiy = string_length;

	for (int i = 0; i != string_length; i++)
		string_content[i] = str[i];
}

MyString::MyString(const MyString& str) {
	string_length = str.string_length;
	string_content = new char[string_length];

	for (int i = 0; i != string_length; i++)
		string_content[i] = str.string_content[i];
}

MyString::~MyString() { delete[] string_content; }

int MyString::length() const { return string_length; }

void DoSthWithStr(MyString s) {
	// String 객체 s를 가지고 무언가를 하는 함수
	std::cout << "doSthWithStr function execute" << std::endl;
}

int main() {
	// 명시적으로 인자를 전달 -> 객체를 생성해서 이를 인자로 전달
	DoSthWithStr(MyString("abc"));

	// 암시적(implicit) 변환
	DoSthWithStr("abc");
	/*
		"abc"가 MyString 객체는 아니지만 
		컴파일러가 cosnt char* str로 자동으로 MyString 생성자를 이용해서
		처리한다.
	*/

	/*
		이러한 암시적 변환이 매우 편리하지만, 예상치 못한 변환이 생길 수 있다.
		DoSthWithStr(3);의 경우 오류를 내야하는데

		MyString(int capacity)로 암시적 변환이 된다.

		이러한 원치 않는 암시적 변환을 하지 못하도록
		"explicit"키워드로 컴파일러에게 명시할 수 있다.

		MyString 클래스 내에 explict MyString(int capacity); 를 하면 된다.

		explict 키워드를 하고 나서
		DoSthWithStr(3); 을 수행하면 컴파일 오류가 난다.

		explict MyString(int capacity);는
		컴파일러에서 이 MyString 생성자를 사용할 때는 명시적 변환만 가능하다느 것이다.

		그리고 explict는 해당 생성자가 복사 생성자의 형태로도 호출되는 것을 막는다.

		예를 들어서 MyString s = "abc"; // MyString s("abc");
		Mystring s = 5; // MyString s(5)
		에서 두 번째가 explict 키워드로 인해 작동하지 않게 된다.

		MyString s(5); 로 명시적으로할 때만 가능하다.

	*/
	return 0;
}