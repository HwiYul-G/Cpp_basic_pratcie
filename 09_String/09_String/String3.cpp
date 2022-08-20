/*
	문자열 삽입하기 (insert)
	문자열 중간에 다른 문자열을 삽입하는 작업을 들 수 있다.
	
	MyString& insert(int loc, const MyString& str);
	MyString& insert(int loc, const char* str);
	MyString& insert(int loc, char c);

	loc을 어떻게 생각할 지 미리 기준을 정해야 한다.
	일반적으로 insert함수에서 loc(위치)를 받는 경우, 그 입력 위치 '앞'에 문자를 insert하는 경우가 많다.

	abc라는 문자열에 insert(1,"d")라고 하면 1의 위치에 있는 b 앞에 d가 삽입되어 "adbc"가 된다.
	
	MyString& insert(int loc, const MyString& str); 만 잘 작성하면 그 아래 함수는 이를 이용하면 된다.
	
	MyString& MyString::insert(int loc, const char* str) {
		MyString temp(str);
		return insert(loc, temp);
	}
	MyString& MyString::insert(int loc, char c) {
		MyString temp(c);
		return insert(loc, temp);
	}

*/
#include<iostream>
#include<string.h>

class MyString {
	char* string_content;	// 문자열 데이터를 가리키는 포인터
	int string_length;		// 문자열 길이
	int memory_capacity;	// 현재 할당된 용량

public:
	MyString(char c);
	MyString(const char* str);
	MyString(const MyString& str);

	~MyString();

	int length() const;
	int capacity() const;
	void reserve(int size);

	void print() const;
	void println() const;

	MyString& assign(const MyString& str);
	MyString& assign(const char* str);

	char at(int i) const;

	MyString& insert(int loc, const MyString& str);
	MyString& insert(int loc, const char* str);
	MyString& insert(int loc, char c);
};

MyString::MyString(char c) {
	string_content = new char[1];
	string_content[0] = c;
	memory_capacity = 1;
	string_length = 1;
}
MyString::MyString(const char* str) {
	string_length = strlen(str); // NULL값 제외
	memory_capacity = string_length;
	string_content = new char[string_length];

	for (int i = 0; i < string_length; i++)
		string_content[i] = str[i];
}
MyString::MyString(const MyString& str) {
	string_length = str.string_length;
	memory_capacity = str.string_length;
	string_content = new char[string_length];

	for (int i = 0; i != string_length; i++)
		string_content[i] = str.string_content[i];
}

MyString::~MyString() { delete[] string_content; }

int MyString::length() const { return string_length; }
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
}

void MyString::print() const {
	for (int i = 0; i != string_length; i++) {
		std::cout << string_content[i];
	}
}
void MyString::println() const {
	for (int i = 0; i != string_length; i++) {
		std::cout << string_content[i];
	}
	std::cout << std::endl;
}

MyString& MyString::assign(const MyString& str) {
	if (str.string_length < str.memory_capacity) {
		delete[] string_content;

		string_content = new char[str.string_length];
		memory_capacity = str.string_length;
	}
	for (int i = 0; i != str.string_length; i++)
		string_content[i] = str.string_content[i];
	
	// 그리고 굳이 str.string_length + 1 ~ string_length 부분은 초기화
	// 시킬 필요는 없다. 왜냐하면 거기 까지는 읽어들이지 않기 때문이다.
	string_length = str.string_length;

	return *this;
}
MyString& MyString::assign(const char* str) {
	int str_length = strlen(str);
	if (str_length > memory_capacity) {
		// 그러면 다시 할당을 해줘야만 한다.
		delete[] string_content;

		string_content = new char[str_length];
		memory_capacity = str_length;
	}
	for (int i = 0; i != str_length; i++) {
		string_content[i] = str[i];
	}

	string_length = str_length;

	return *this;
}

char MyString::at(int i) const {
	if (i >= string_length || i < 0)return 0;
	return string_content[i];
}

MyString& MyString::insert(int loc, const MyString& str) {
	// i의 위치의 바로 앞에 문자를 삽입한다.
	// 예를들어서 abc라는 문자열에 insert(1,"d")를 한다면 adbc라는 문자가 된다.

	// 범위를 벗어나는 입력에 대해선 삽입을 수행하지 않는다.
	if (loc<0 || loc>string_length) return *this;

	if (string_length + str.string_length > memory_capacity) {
		// 새롭게 동적으로 할당해야한다.
		memory_capacity = string_length + str.string_length;

		char* prev_string_content = string_content;
		string_content = new char[memory_capacity];

		int i;
		for (i = 0; i < loc; i++)
			string_content[i] = prev_string_content[i];

		for (int j = 0; j != str.string_length; j++)
			string_content[i + j] = str.string_content[j];

		for (; i < string_length; i++)
			string_content[str.string_length + i] = prev_string_content[i];

		delete[] prev_string_content;

		string_length += str.string_length;
		return *this;
	}

	// 만일 초과하지 않는 경우 굳이 동적 할당을 할 필요가 없다.
	// 효율적인 insert를 위해 밀리는 부분을 먼저 뒤로 민다.
	for (int i = string_length - 1; i >= loc; i--) {
		string_content[i + str.string_length] = string_content[i];
	}

	// insert 되는 문자 다시 집어넣기
	for (int i = 0; i < str.string_length; i++)
		string_content[i + loc] = str.string_content[i];

	string_length = string_length + str.string_length;
	return *this;		
}
MyString& MyString::insert(int loc, const char* str) {
	MyString temp(str);
	return insert(loc, temp);
}
MyString& MyString::insert(int loc, char c) {
	MyString temp(c);
	return insert(loc, temp);
}

int main() {
	MyString str1("very long string");
	MyString str2("<some string inserted between>");
	str1.reserve(30);

	std::cout << "Capacity : " << str1.capacity() << std::endl;
	std::cout << "String length : " << str1.length() << std::endl;
	str1.println();

	str1.insert(5, str2);
	str1.println();

	return 0;
}
/*
	큰 크기의 문자열을 한 번에 insert하는 작업보단 
	작은 크기의 문자열들을 여러번 insert하는 명령을 더 많이 수행한다.

	그런데 만일 이미 capacity 한계에 도달한 문자열 클래스에 
	문자 a를 계속 추가하는 아래와 같은 명령을 한다고 해보자.

	while(some_condition)
		str.insert(some_loc, 'a');
	
	이미 str가 capacity 한계에 도달했다고 가정햇으므로,
	매 insert마다 메모리를 해제하고 1 만큼 큰 메모리를 할당하는 작업을 반복하게 될 것이다.
	이는 str의 크기가 크다면 엄청난 작업의 낭비이다.

	짜잘하게 계속 insert하는 명령에서 메모리 할당과 해제를 반복하지 않도록 하려면
	통 크게 메모리를 미리 reserve 해놓는 것이 필요하다.
	물론, 무턱대고 미리 엄청난 크기의 메모리를 할당해 놓을 수도 없다.
	만일 10byte 밖에 사용하지 않는데
	이와 같이 짜잘하게 insert하는 문제를 피하기 위해 
	1000byte를 미리 할당해 놓는다면 소중한 자원의 낭비가 될 것이다.

	따라서 insert 작업에서의 잦은 할당/해제를 피하기 위해 미리 메모리를 할당해놓기와
	메모리를 할당해 놓데 많은 자원을 낭비하지 않는다.
	이 두 조건을 모두 만족하는 방법이 있을까?

	있다! 메모리를 미리 할당할 경우 현재 메모리 크기의 2배 정도를 할당해 놓는 것이다.
	
	MyString& MyString::insert(int loc, const MyString& str) {
		// 범위를 벗어나는 입력에 대해서는 삽입을 수행하지 않는다.
		if (loc < 0 || loc > string_length) return *this;

		if (string_length + str.string_length > memory_capacity) {
		// 이제 새롭게 동적으로 할당을 해야 한다.

		if (memory_capacity * 2 > string_length + str.string_length)
			memory_capacity *= 2;
		else
			memory_capacity = string_length + str.string_length;

		// 생략..
	}

	즉 새로 할당해야 할 메모리 크기(string_length + str.string_length)가 현재의 memory_capacity의 2배 이하라면
	아예  memory_capacity에 2배에 달하는 크기를 할당해 버리는 것이다.

	물론 insert되는 문자열의 크기가 엄청 커서 memory_capacity의 2배를 뛰어 넘어버린다면
	그냥 예약을 생각하지 않고 필요한 만큼 할당해 보리면 된다.

	이와 같은 방식으로 처리하면 빈번한 메모리의 할당/해제를 막을 수 있고
	또 많은 메모리 공간을 낭비하지 않을 수 있다.

	참고로 이러한 방법은 C++에서 동적으로 할당되는 메모리를 처리하는데 매우 빈번히 사용되는 기법 중 하나이다.A

	==> String4.cpp
*/