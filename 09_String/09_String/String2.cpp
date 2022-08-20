#include <iostream>

// string.h �� strlen ������ include �ߴµ�, ��� �������� ���� strlen
// �� ���� �Լ��� ���� �ᵵ �˴ϴ�.
#include <string.h>

class MyString {
    char* string_content;  // ���ڿ� �����͸� ����Ű�� ������
    int string_length;     // ���ڿ� ����
    int memory_capacity;   // ���� �Ҵ�� �뷮

public:
    // ���� �ϳ��� ����
    MyString(char c);

    // ���ڿ��� ���� ����
    MyString(const char* str);

    // ���� ������
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

    for (int i = 0; i != string_length; i++) {
        string_content[i] = str[i];
    }
}

MyString::MyString(const MyString& str) {
    string_length = str.string_length;
    memory_capacity = str.string_length;
    string_content = new char[string_length];

    for (int i = 0; i != string_length; i++) {
        string_content[i] = str.string_content[i];
    }
}

MyString::~MyString() { delete[] string_content; }
int MyString::length() const { return string_length; }

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
    if (str.string_length > memory_capacity) {
        // �׷��� �ٽ� �Ҵ��� ����߸� �Ѵ�.
        delete[] string_content;

        string_content = new char[str.string_length];
        memory_capacity = str.string_length;
    }
    for (int i = 0; i != str.string_length; i++) {
        string_content[i] = str.string_content[i];
    }

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
/*
    �Ҵ��� ���ڿ��� ũ�⸦ �̸� �����س��� reserve �Լ�
    ���� ���ڿ��� �Ҵ�� �޸� ũ�⸦ ��Ÿ���� capacity �Լ�
*/
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

    // ���� �����Ϸ��� size �� ���� capacity ���� �۴ٸ�
    // �ƹ��͵� ���ص� �ȴ�.
}

char MyString::at(int i) const {
    if (i >= string_length || i < 0)
        return NULL;
    return string_content[i];
}

int main() {
    MyString str1("very very very long string");
    str1.reserve(30);

    std::cout << "Capacity : " << str1.capacity() << std::endl;
    std::cout << "String length : " << str1.length() << std::endl;
    str1.println();

    return 0;
}