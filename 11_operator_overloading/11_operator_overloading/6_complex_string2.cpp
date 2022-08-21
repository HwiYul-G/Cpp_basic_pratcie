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

    Complex operator+(const Complex& c) const;
    Complex operator-(const Complex& c) const;
    Complex operator*(const Complex& c) const;
    Complex operator/(const Complex& c) const;

    Complex operator+(const char* str) const;
    Complex operator-(const char* str) const;
    Complex operator*(const char* str) const;
    Complex operator/(const char* str) const;

    Complex& operator+=(const Complex& c);
    Complex& operator-=(const Complex& c);
    Complex& operator*=(const Complex& c);
    Complex& operator/=(const Complex& c);

    Complex& operator=(const Complex& c);

    void println() {
        std::cout << "( " << real << " , " << img << " ) " << std::endl;
    }
};
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
Complex Complex::operator+(const Complex& c) const {
    Complex temp(real + c.real, img + c.img);
    return temp;
}
Complex Complex::operator-(const Complex& c) const {
    Complex temp(real - c.real, img - c.img);
    return temp;
}
Complex Complex::operator*(const Complex& c) const {
    Complex temp(real * c.real - img * c.img, real * c.img + img * c.real);
    return temp;
}
Complex Complex::operator/(const Complex& c) const {
    Complex temp(
        (real * c.real + img * c.img) / (c.real * c.real + c.img * c.img),
        (img * c.real - real * c.img) / (c.real * c.real + c.img * c.img));
    return temp;
}
Complex Complex::operator+(const char* str) const {
    Complex temp(str);
    return (*this) + temp;
}
Complex Complex::operator-(const char* str) const {
    Complex temp(str);
    return (*this) - temp;
}
Complex Complex::operator*(const char* str) const {
    Complex temp(str);
    return (*this) * temp;
}
Complex Complex::operator/(const char* str) const {
    Complex temp(str);
    return (*this) / temp;
}
Complex& Complex::operator+=(const Complex& c) {
    (*this) = (*this) + c;
    return *this;
}
Complex& Complex::operator-=(const Complex& c) {
    (*this) = (*this) - c;
    return *this;
}
Complex& Complex::operator*=(const Complex& c) {
    (*this) = (*this) * c;
    return *this;
}
Complex& Complex::operator/=(const Complex& c) {
    (*this) = (*this) / c;
    return *this;
}
Complex& Complex::operator=(const Complex& c) {
    real = c.real;
    img = c.img;
    return *this;
}

int main() {
    Complex a(0, 0);
    a = a + "-1.1 + i3.923";
    a.println();
    a = a - "1.2 -i1.823";
    a.println();
    a = a * "2.3+i22";
    a.println();
    a = a / "-12+i55";
    a.println();
}

/*
    이때 Complex(const char* str) 생성자만 남겨놓고
    operator+(const char* str) 계열들을 모두 지워보고 컴파일해보라.

    그래도 성공적으로 동일한 결과가 나온다.
    그럼 고생해서 const char* str을 만든 operator+,-,*,/을 만든 것이 허망하다.
    Complex operator+(const char *str) const;
    Complex operator-(const char *str) const;
    Complex operator*(const char *str) const;
    Complex operator/(const char *str) const;

    이것이 없어도 가능한 이유는 컴파일러가 똑똑하기 때문이다.
    만일 a = a + "-1.1 + i3.923";와 같은 문장을 사용했을 때 컴파일러는 아래와 같이 바꿔준다.
    a = a.operator+("-1.1 + i3.923");

    하지만 우리에겐 operator+(const char* str)이 없고 operator+(const Complex& c)밖에 없어서
    직접적으로 오버로딩 되지는 않는다.
    그렇지만 컴파일러는 매우 똑똑해서 다음 순위로 오버로딩될 수 있는 함수들이 있는 지 없는 지 확인해 본다.

    const char*에서 Complex를 생성할 수 있는 생성자
    Complex(const char* str);이 있으므로 컴파일러는 문자열 literal로부터 cosnt Complex 타입 객체를 새롭게 생성한다.

    즉 a = a.operator+("-1.1 + i3.923");라는 문장은 아래와 같이 변경된다
    a = a.operator+(Complex("-1.1 + i3.923"));
    따라서 const Complex에 인자를 전달할 수 있게 되어 프로그램이 올바르게 작동하게 된다.

    여기서 중요한 점은 operator+ 함수의 인자가 const Complex& c가 아니라 
    Complex& c로 받도록 했다면 위와 같은 변환이 똑똑하게 일어나지 않는다.

    왜냐하면 -1.1 + i3.923 자체가 'string literal'이기 때문에
    이를 바탕을 생성된 객체 역시 상수 여야 하기 때문이다.
    따라서 여러 모로 함수의 인자 값을 변형하지 않는다는 확신이 들면 무조건 const 인자로 받도록 하는 것이 좋다.

    그렇다면 +의 순서를 바꾼 아래와 같은 것은 수행이 될까?
    a = a + "-1.1 + i3.923";이 아니라 a = "-1.1 + i3.923" + a;하는 것은 작동할까?

    + 연산자는 교환 법칙이 성립하는 연산자 이므로 성립해야 하지만
    a = "-1.1 + i3.923" + a;의 경우 성공적으로 컴파일 되지 않는다.
    왜냐하면 a = a + "-1.1 + i3.923";는 a.operator+("-1.1+i3.923")으로 변환되어서 정확히 수행될 수 있지만
    a = "-1.1 + i3.923" + a;의 경우 이 변환이 불가능하기 때문이다.

    => 이에 대해선 어떻게 해결할 수 있을까?? 
        이는 다음 프로젝트에서!
    
    
*/