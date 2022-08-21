/*
	std::cout<< a;
	=> std::cout.operator<<(a)와 동일한 명령

	즉 std::cout이라는 객체에 멤버 함수 operator<<가 정의되어 있어서
	a를 호출하게 하는 것이다.

	그런데 std::cout이라는 것 하나로 int, double, char 등 다양한 타입의 변수를 출력한다.
	이 이유는 operator<< 함수들이 오버로딩되어 있기 때문이다.

	include 하는 iostream(istream + ostream)의 헤더파일 내용을 살펴보면
	ostream 클래스에 아래와 같은 많은 operator<<들이 정의되어 있다.
	
	ostream& operator<<(bool val);
	ostream& operator<<(short val);
	ostream& operator<<(unsigned short val);
	ostream& operator<<(int val);
	ostream& operator<<(unsigned int val);
	ostream& operator<<(long val);
	ostream& operator<<(unsigned long val);
	ostream& operator<<(float val);
	ostream& operator<<(double val);
	ostream& operator<<(long double val);
	ostream& operator<<(void* val);

	Complex 클래스에서 ostream 클래스의 연산자 operaotr<<를 자유롭게 사용할 수 있게 해보자.
	Complex c;
	std::cout<< c;
	를 하면 c.println();을 한 것과 같은 효과를 내도록
    ======


    ostream 클래스에 operator<< 멤버함수를 새롭게 추가하는 것은 불가능 (표준 헤더파일을 수정해야 하므로)
    따라서 ostream 클래스에 Complex 객체를 오버로딩하는 operator<< 연산자 함수를 추가할 수는 없다.

    클래스 연산자 함수를 추가하는 방법으로 멤버 함수를 사용하는 것 말고도 더 있다
    ostream 클래스 객체와 Complex 객체 2개를 인자로 받는 전역 operator<< 함수를 정의하면 된다.
*/
#include <cstring>
#include <iostream>

class Complex {
private:
    double real, img;

    double get_number(const char* str, int from, int to) const;

public:
    Complex(double real, double img) : real(real), img(img) {}
    Complex(const Complex& c) { real = c.real, img = c.img; }
    Complex(const char* str);

    Complex& operator+=(const Complex& c);
    Complex& operator=(const Complex& c);

    // 나머지 연산자 함수들은 생략 :)

    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
    friend Complex operator+(const Complex& a, const Complex& b);
};

Complex operator+(const Complex& a, const Complex& b) {
    Complex temp(a.real + b.real, a.img + b.img);
    return temp;
}
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "( " << c.real << " , " << c.img << " ) ";
    return os;
}

Complex::Complex(const char* str) {
    // 입력 받은 문자열을 분석하여 real 부분과 img 부분을 찾아야 한다.
    // 문자열의 꼴은 다음과 같습니다 "[부호](실수부)(부호)i(허수부)"
    // 이 때 맨 앞의 부호는 생략 가능합니다. (생략시 + 라 가정)

    int begin = 0, end = strlen(str);
    img = 0.0;
    real = 0.0;

    // 먼저 가장 기준이 되는 'i' 의 위치를 찾는다.
    int pos_i = -1;
    for (int i = 0; i != end; i++) {
        if (str[i] == 'i') {
            pos_i = i;
            break;
        }
    }

    // 만일 'i' 가 없다면 이 수는 실수 뿐이다.
    if (pos_i == -1) {
        real = get_number(str, begin, end - 1);
        return;
    }

    // 만일 'i' 가 있다면,  실수부와 허수부를 나누어서 처리하면 된다.
    real = get_number(str, begin, pos_i - 1);
    img = get_number(str, pos_i + 1, end - 1);

    if (pos_i >= 1 && str[pos_i - 1] == '-') img *= -1.0;
}
double Complex::get_number(const char* str, int from, int to) const {
    bool minus = false;
    if (from > to) return 0;

    if (str[from] == '-') minus = true;
    if (str[from] == '-' || str[from] == '+') from++;

    double num = 0.0;
    double decimal = 1.0;

    bool integer_part = true;
    for (int i = from; i <= to; i++) {
        if (isdigit(str[i]) && integer_part) {
            num *= 10.0;
            num += (str[i] - '0');
        }
        else if (str[i] == '.')
            integer_part = false;
        else if (isdigit(str[i]) && !integer_part) {
            decimal /= 10.0;
            num += ((str[i] - '0') * decimal);
        }
        else
            break;  // 그 이외의 이상한 문자들이 올 경우
    }

    if (minus) num *= -1.0;

    return num;
}

Complex& Complex::operator+=(const Complex& c) {
    (*this) = *this + c;
    return (*this);
}
Complex& Complex::operator=(const Complex& c) {
    real = c.real;
    img = c.img;
    return *this;
}

int main() {
    Complex a(0, 0);
    a = "-1.1 + i3.923" + a;
    std::cout << "a 의 값은 : " << a << " 이다. " << std::endl;
}