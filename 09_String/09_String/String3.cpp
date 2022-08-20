/*
	���ڿ� �����ϱ� (insert)
	���ڿ� �߰��� �ٸ� ���ڿ��� �����ϴ� �۾��� �� �� �ִ�.
	
	MyString& insert(int loc, const MyString& str);
	MyString& insert(int loc, const char* str);
	MyString& insert(int loc, char c);

	loc�� ��� ������ �� �̸� ������ ���ؾ� �Ѵ�.
	�Ϲ������� insert�Լ����� loc(��ġ)�� �޴� ���, �� �Է� ��ġ '��'�� ���ڸ� insert�ϴ� ��찡 ����.

	abc��� ���ڿ��� insert(1,"d")��� �ϸ� 1�� ��ġ�� �ִ� b �տ� d�� ���ԵǾ� "adbc"�� �ȴ�.
	
	MyString& insert(int loc, const MyString& str); �� �� �ۼ��ϸ� �� �Ʒ� �Լ��� �̸� �̿��ϸ� �ȴ�.
	
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
	char* string_content;	// ���ڿ� �����͸� ����Ű�� ������
	int string_length;		// ���ڿ� ����
	int memory_capacity;	// ���� �Ҵ�� �뷮

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
	string_length = strlen(str); // NULL�� ����
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
	
	// �׸��� ���� str.string_length + 1 ~ string_length �κ��� �ʱ�ȭ
	// ��ų �ʿ�� ����. �ֳ��ϸ� �ű� ������ �о������ �ʱ� �����̴�.
	string_length = str.string_length;

	return *this;
}
MyString& MyString::assign(const char* str) {
	int str_length = strlen(str);
	if (str_length > memory_capacity) {
		// �׷��� �ٽ� �Ҵ��� ����߸� �Ѵ�.
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
	// i�� ��ġ�� �ٷ� �տ� ���ڸ� �����Ѵ�.
	// ������ abc��� ���ڿ��� insert(1,"d")�� �Ѵٸ� adbc��� ���ڰ� �ȴ�.

	// ������ ����� �Է¿� ���ؼ� ������ �������� �ʴ´�.
	if (loc<0 || loc>string_length) return *this;

	if (string_length + str.string_length > memory_capacity) {
		// ���Ӱ� �������� �Ҵ��ؾ��Ѵ�.
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

	// ���� �ʰ����� �ʴ� ��� ���� ���� �Ҵ��� �� �ʿ䰡 ����.
	// ȿ������ insert�� ���� �и��� �κ��� ���� �ڷ� �δ�.
	for (int i = string_length - 1; i >= loc; i--) {
		string_content[i + str.string_length] = string_content[i];
	}

	// insert �Ǵ� ���� �ٽ� ����ֱ�
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
	ū ũ���� ���ڿ��� �� ���� insert�ϴ� �۾����� 
	���� ũ���� ���ڿ����� ������ insert�ϴ� ����� �� ���� �����Ѵ�.

	�׷��� ���� �̹� capacity �Ѱ迡 ������ ���ڿ� Ŭ������ 
	���� a�� ��� �߰��ϴ� �Ʒ��� ���� ����� �Ѵٰ� �غ���.

	while(some_condition)
		str.insert(some_loc, 'a');
	
	�̹� str�� capacity �Ѱ迡 �����ߴٰ� ���������Ƿ�,
	�� insert���� �޸𸮸� �����ϰ� 1 ��ŭ ū �޸𸮸� �Ҵ��ϴ� �۾��� �ݺ��ϰ� �� ���̴�.
	�̴� str�� ũ�Ⱑ ũ�ٸ� ��û�� �۾��� �����̴�.

	¥���ϰ� ��� insert�ϴ� ��ɿ��� �޸� �Ҵ�� ������ �ݺ����� �ʵ��� �Ϸ���
	�� ũ�� �޸𸮸� �̸� reserve �س��� ���� �ʿ��ϴ�.
	����, ���δ�� �̸� ��û�� ũ���� �޸𸮸� �Ҵ��� ���� ���� ����.
	���� 10byte �ۿ� ������� �ʴµ�
	�̿� ���� ¥���ϰ� insert�ϴ� ������ ���ϱ� ���� 
	1000byte�� �̸� �Ҵ��� ���´ٸ� ������ �ڿ��� ���� �� ���̴�.

	���� insert �۾������� ���� �Ҵ�/������ ���ϱ� ���� �̸� �޸𸮸� �Ҵ��س����
	�޸𸮸� �Ҵ��� ���� ���� �ڿ��� �������� �ʴ´�.
	�� �� ������ ��� �����ϴ� ����� ������?

	�ִ�! �޸𸮸� �̸� �Ҵ��� ��� ���� �޸� ũ���� 2�� ������ �Ҵ��� ���� ���̴�.
	
	MyString& MyString::insert(int loc, const MyString& str) {
		// ������ ����� �Է¿� ���ؼ��� ������ �������� �ʴ´�.
		if (loc < 0 || loc > string_length) return *this;

		if (string_length + str.string_length > memory_capacity) {
		// ���� ���Ӱ� �������� �Ҵ��� �ؾ� �Ѵ�.

		if (memory_capacity * 2 > string_length + str.string_length)
			memory_capacity *= 2;
		else
			memory_capacity = string_length + str.string_length;

		// ����..
	}

	�� ���� �Ҵ��ؾ� �� �޸� ũ��(string_length + str.string_length)�� ������ memory_capacity�� 2�� ���϶��
	�ƿ�  memory_capacity�� 2�迡 ���ϴ� ũ�⸦ �Ҵ��� ������ ���̴�.

	���� insert�Ǵ� ���ڿ��� ũ�Ⱑ ��û Ŀ�� memory_capacity�� 2�踦 �پ� �Ѿ�����ٸ�
	�׳� ������ �������� �ʰ� �ʿ��� ��ŭ �Ҵ��� ������ �ȴ�.

	�̿� ���� ������� ó���ϸ� ����� �޸��� �Ҵ�/������ ���� �� �ְ�
	�� ���� �޸� ������ �������� ���� �� �ִ�.

	����� �̷��� ����� C++���� �������� �Ҵ�Ǵ� �޸𸮸� ó���ϴµ� �ſ� ����� ���Ǵ� ��� �� �ϳ��̴�.A

	==> String4.cpp
*/