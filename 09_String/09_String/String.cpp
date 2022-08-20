#include <iostream>
#include <string.h>

class MyString {
	char* string_content;	// ���ڿ� �����͸� ����Ű�� ������
	int string_length;		// ���ڿ� ����
public:
	// ���� �ϳ��� ����
	MyString(char c);
	// ���ڿ��κ��� ����
	MyString(const char* str);
	// ���� ������
	MyString(const MyString& str);
	
	int length() const;
	void print() const;
	void println() const;

	// assing �Լ� : '='�� ������ ������ ��.
	// str.assign("abc"); �� �ϸ� str�� ���� �ִ� ���ڿ��� �������� abc�� ����.
	MyString& assign(const MyString& str);
	MyString& assign(const char* str);

	~MyString();
};

/*
	��� ������� ���ڿ��� �����ұ�?
	string_content�� C ������ ���ڿ�(null ���� ���ڿ�)�� �����ϴ� ���� ������?
	�ƴϸ� �ʿ� ���� ������(null ���� ���ڿ�)�� ���� ���� '����'�� �ش��ϴ� �κи� ������?

	C ������ ���ڿ��� �״�� �����ϸ�, ���ڿ��� �� �κ��� ���� üũ�� �� �ִٴ� ������ �ִ�.
	������ �� ������ string_length��� ������ ���������� �ذ��� �� �ְ� �Ǿ���.

	���� Mystring class���� ���� ���ڿ��� �ش��ϴ� ���븸(null ����)�� string_content�� �����ϰڴ�.
*/

MyString::MyString(char c) {
	string_content = new char[1];
	string_content[0] = c;
	string_length = 1;
}
MyString::MyString(const char* str) {
	string_length = strlen(str); // null�� ������ ���� ���̰� �����
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
		length �Լ� ���� string_length ���� �б⸸ �ϹǷ� ����Լ��� ����

		�̷��� ������� ���ڿ��� ���̸� ���Ѵٸ�, 
		���ڿ� ���۽ÿ� string_length�� ���� �ùٸ� ������ �����ؾ߸� �Ѵ�.

		���� �� �� ���ڿ��� ���� ���ؼ� ���ο� ���ڿ��� ���� �� 
		���ο� ���ڿ��� string_length�� �� ���ڿ��� string_length�� ���� �ȴ�.
		���������� �κ� ���ڿ��� �����ϰų� ���� �ϳ��� ����� �� 
		��� �۾��� string_length ���� ��Ȯ�� �����ؾ��Ѵ�.
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
	MyString& MyString::assign(const MyString& str)��
	MyString& MyString::assign(const char* str)��
	ȿ���� ���� ���� ���� ���̺��� ª�� ���� �Ҵ��� ��쿡�� ���� �����Ҵ��� ���� �ʴ´�.
	�׷��� �� ��쿣 �׳� �״�� �����ؼ� ����Ѵ�.

	�׷��� �� ����� �� ������ �ִ�.
	MyString str1("very very very long string");
	str1.assign("short string");
	str1.assign("very long string");

	�̷��� ������� �Ҵ����� �� ������ �� �� �ִ�.
	���� �� str1�� �ſ� �� �� 1000 byte�� ���ڿ��� �Ҵ��ߴٰ� ����.
	�׸��� str1�� �ٽ� ª�� ���ڿ��� �Ҵ��ߴٰ� ����

	�츮�� ���� assign �Լ��� ������ �̹� �� ���ڿ��� �Ҵ�� ��� �� ª�� ���ڿ��� assign�ϸ�
	������ ���� ����� �����Ҵ����� �ʰ� string_length�� ���̰� �պκ��� ª�� ���ڿ��� ���� �����.

	�׷��� ������ �̷��� ª���� str1�� �ٽ� �� ���ڿ��� assign �� �� �߻��ϰ� �ȴ�.
	��� str1���� �̹� ó�� �Ҵ��ߴ� 1000byte�� ������ �������� ���� ª�� ���ڿ��� �־
	���Ӱ� �� ���ڿ� �Ҵ�� 1000byte�� �Ҵ�Ǿ� �ִٴ� ����� �� �� ���� �ȴ�.

	���� assign �Լ��� ���ڿ��� ª�� ���ڿ��� ���� ���� ũ�⿡ �������� �Ҵ�Ǿ� �ִٰ� �����Ͽ�
	�޸𸮸� �����ϰ� �ٽ� ���� ���� �޸𸮸� �Ҵ��ϴ� �ſ� ��ȿ������ �۾��� �ϰ� �ȴ�.
	
	�̷��� ��ȿ���� ���� ���� �󸶳� ���� ������ �Ҵ�Ǿ� �ִ��� �� �� �ִ� ������ ���� �����ϴ� ���� ���� ���̶� A������
	�̸� ���� memory_capacity��� ���� �Ҵ�� �޸� ������ ũ�⸦ ��Ÿ���� ���ο� ������ �߰�����!
	==> String2.cpp
*/

MyString::~MyString() { 
	delete[] string_content; 
	/*
		string_content�� �� �����ڿ��� �����Ҵ��߱⿡ �ݵ�� �Ҹ��ڿ��� �̸� �������� �ؾ��Ѵ�.
		�̰��� Ŭ������ ū �����̴�. C���� ����ü�� ���ڿ��� �����ϸ� �̸� ������ �����ϴ� �͵� ó������� �Ѵ�.
		�� �״��, Ŭ������ ����ϴ� ����� �ȿ��� ��� ���ư����� �Ű� �Ⱦ��� ����� �� �ְ� �ȴ�.
	*/
}

int main() {
	MyString str1("hello world!");
	MyString str2(str1);

	str1.println();
	str2.println();

	return 0;
}