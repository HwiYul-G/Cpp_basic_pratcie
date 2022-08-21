#include <iostream>

class MyString {
	char* string_content; // ���ڿ� �����͸� ����Ű�� ������
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
	// String ��ü s�� ������ ���𰡸� �ϴ� �Լ�
	std::cout << "doSthWithStr function execute" << std::endl;
}

int main() {
	// ��������� ���ڸ� ���� -> ��ü�� �����ؼ� �̸� ���ڷ� ����
	DoSthWithStr(MyString("abc"));

	// �Ͻ���(implicit) ��ȯ
	DoSthWithStr("abc");
	/*
		"abc"�� MyString ��ü�� �ƴ����� 
		�����Ϸ��� cosnt char* str�� �ڵ����� MyString �����ڸ� �̿��ؼ�
		ó���Ѵ�.
	*/

	/*
		�̷��� �Ͻ��� ��ȯ�� �ſ� ��������, ����ġ ���� ��ȯ�� ���� �� �ִ�.
		DoSthWithStr(3);�� ��� ������ �����ϴµ�

		MyString(int capacity)�� �Ͻ��� ��ȯ�� �ȴ�.

		�̷��� ��ġ �ʴ� �Ͻ��� ��ȯ�� ���� ���ϵ���
		"explicit"Ű����� �����Ϸ����� ����� �� �ִ�.

		MyString Ŭ���� ���� explict MyString(int capacity); �� �ϸ� �ȴ�.

		explict Ű���带 �ϰ� ����
		DoSthWithStr(3); �� �����ϸ� ������ ������ ����.

		explict MyString(int capacity);��
		�����Ϸ����� �� MyString �����ڸ� ����� ���� ����� ��ȯ�� �����ϴٴ� ���̴�.

		�׸��� explict�� �ش� �����ڰ� ���� �������� ���·ε� ȣ��Ǵ� ���� ���´�.

		���� �� MyString s = "abc"; // MyString s("abc");
		Mystring s = 5; // MyString s(5)
		���� �� ��°�� explict Ű����� ���� �۵����� �ʰ� �ȴ�.

		MyString s(5); �� ����������� ���� �����ϴ�.

	*/
	return 0;
}