/*
    크기 비교 함수 compare
    
    문자열 간의 크기를 비교하는 compare 함수.
    여기서 '크기'를 비교한다는 의미는 사전식으로 배열해서 
    어떤 문자열이 더 뒤에 오는지 판단하는 의미가 된다.
    
    이 함수를 이용해서 문자열 전체를 정렬하는 함수라던지, 
    기존의 C언어에서 strcmp 함수 등으로 지원했던 것을 그대로 사용할 수 있다.
*/

#include <iostream>
#include <string.h>

class MyString {
    char* string_content;  // 문자열 데이터를 가리키는 포인터
    int string_length;     // 문자열 길이
    int memory_capacity;   // 현재 할당된 용량

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

    MyString& erase(int loc, int num);

    int find(int find_from, MyString& str) const;
    int find(int find_from, const char* str) const;
    int find(int find_from, char c) const;

    int compare(const MyString& str) const;
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
        // 그러면 다시 할당을 해줘야만 한다.
        delete[] string_content;

        string_content = new char[str.string_length];
        memory_capacity = str.string_length;
    }
    for (int i = 0; i != str.string_length; i++) {
        string_content[i] = str.string_content[i];
    }

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
    if (i >= string_length || i < 0) {
        return 0;
    }
    else {
        return string_content[i];
    }
}
MyString& MyString::insert(int loc, const MyString& str) {
    // 이는 i 의 위치 바로 앞에 문자를 삽입하게 된다. 예를 들어서
    // abc 라는 문자열에 insert(1, "d") 를 하게 된다면 adbc 가 된다.

    // 범위를 벗어나는 입력에 대해서는 삽입을 수행하지 않는다.
    if (loc < 0 || loc > string_length) return *this;

    if (string_length + str.string_length > memory_capacity) {
        // 이제 새롭게 동적으로 할당을 해야 한다.

        if (memory_capacity * 2 > string_length + str.string_length)
            memory_capacity *= 2;
        else
            memory_capacity = string_length + str.string_length;

        char* prev_string_content = string_content;
        string_content = new char[memory_capacity];

        // 일단 insert 되는 부분 직전까지의 내용을 복사한다.
        int i;
        for (i = 0; i < loc; i++) {
            string_content[i] = prev_string_content[i];
        }

        // 그리고 새롭에 insert 되는 문자열을 넣는다.
        for (int j = 0; j != str.string_length; j++) {
            string_content[i + j] = str.string_content[j];
        }

        // 이제 다시 원 문자열의 나머지 뒷부분을 복사한다.
        for (; i < string_length; i++) {
            string_content[str.string_length + i] = prev_string_content[i];
        }

        delete[] prev_string_content;

        string_length = string_length + str.string_length;
        return *this;
    }

    // 만일 초과하지 않는 경우 굳이 동적할당을 할 필요가 없게 된다.
    // 효율적으로 insert 하기 위해, 밀리는 부분을 먼저 뒤로 밀어버린다.

    for (int i = string_length - 1; i >= loc; i--) {
        // 뒤로 밀기. 이 때 원래의 문자열 데이터가 사라지지 않게 함
        string_content[i + str.string_length] = string_content[i];
    }
    // 그리고 insert 되는 문자 다시 집어넣기
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

MyString& MyString::erase(int loc, int num) {
    // loc 의 앞 부터 시작해서 num 문자를 지운다.
    if (num < 0 || loc < 0 || loc > string_length) return *this;

    // 지운다는 것은 단순히 뒤의 문자들을 앞으로 끌고 온다고
    // 생각하면 됩니다.

    for (int i = loc + num; i < string_length; i++) {
        string_content[i - num] = string_content[i];
    }

    string_length -= num;
    return *this;
}

int MyString::find(int find_from, MyString& str) const {
    // find_from에서부터 시작해서 가장 첫 번째의 str의 위치를 리턴했다.
    // 그리고 str이 문자열에 포함되어 있지 않다면 -1을 리턴하게 되었다.s
    int i, j;
    if (str.string_length == 0) return -1;
    for (i = find_from; i <= string_length - str.string_length; i++) {
        for (j = 0; j < str.string_length; j++)
            if (string_content[i + j] != str.string_content[j]) break;

        if (j == str.string_length) return i;
    }
    return -1;
}
int MyString::find(int find_from, const char* str) const {
    MyString temp(str);
    return find(find_from, temp);
}
int MyString::find(int find_from, char c) const {
    MyString temp(c);
    return find(find_from, temp);
}

int MyString::compare(const MyString& str) const {
    // (*this) - (str) 을 수행해서 그 1, 0, -1 로 그 결과를 리턴한다
    // 1 은 (*this) 가 사전식으로 더 뒤에 온다는 의미. 0 은 두 문자열
    // 이 같다는 의미, -1 은 (*this) 가 사전식으로 더 앞에 온다는 의미이다.

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


int main() {
    MyString str1("abcdef");
    MyString str2("abcde");

    std::cout << "str1 and str2 compare : " << str1.compare(str2) << std::endl;
}

/*
    MyString 클래스를 만들었다고 볼 수 있다. 이 MyString 클래스는 아래와 같은 인터페이스를 제공한다.

    - 문자 c 혹은 C 형식 문자열 str 에서 생성할 수 있는 생성자와 복사 생성자
    - 문자열의 길이를 리턴하는 함수(length)
    - 문자열 대입 함수(assign)
    - 문자열 메모리 할당 함수(reserve) 및 현재 할당된 크기를 알아오는 함수(capacity)
    - 특정 위치의 문자를 리턴하는 함수(at)
    - 특정 위치에 특정 문자열을 삽입하는 함수(insert)
    - 특정 위치의 특정 개수의 문자를 지우는 함수(erase)
    - 특정 위치를 시작으로 특정 문자열을 검색하는 함수(find)
    - 두 문자열을 사전식 비교하는 함수(compare)
*/