/*
	Complex operator+(const Complex& c);로 정의하고 나서
	a = a + "-1.1 + i3.923";는 a.operator+("-1.1 + i3.923")으로 컴파일이 되어서 실행되지만
	a = "-1.1 + i3.923" + a;의 경우는 그렇게 할 수 없다.

	다행히 컴파일러는 이항 연산자를 2개의 방식으로 해결한다.

	예를 들어 @라는 연산자가 있다고 하면
	*a.operator@(b);
	*operator@(a,b);
	컴파일러는 둘 중 가능한 것을 택해서 처리된다.

	a.operator@(b)에서의 operator@는 a의 클래스 멤버함수로 사용되는 것이고
	operator@(a,b)에서 operator@는 클래스 외부에 정의되어 있는 일반적인 함수를 의미한다.
	
	================================================
	참고로 이는 일부 연산자들에 대해선 해당 되지 않는데
	대표적으로 [] 연산자(첨자), -> 연산자(멤버 접근), 대입 연산자(=), ()함수 호출 연산자들의 경우
	멤버 함수로만 존재할 수 있다.
	즉 따로 멤버 함수가 아닌 전역 함수로 뺄 수 없다.
	================================================
	
	Complex operator+(const Complex& a, const Complex& b) {
		// ...
	}
	우리의 또 다른 operator+는 2 개의 const Complex& 타입의 인자 a, b를 받게 된다.
	컴파일러는 정확히 일치 하지 않는 경우, 가장 가까운 가능한 오버로딩 되는 함수를 찾게 된다.
	마침 우리에게 Complex(cosnt char*) 타입의 생성자가 있으므로
	"-1.1 + i3.923" + a; 는 operator+(Complex("-1.1 + i3.923"), a);가 되어서 잘 실행 된다.

	그런데 문제는 Complex operator+(const Complex& a, const Complex& b)가 제대로 작동하기 위해선
	이 함수가 a와 b의 private member인 real과 img에 접근해야 한다.
	=> friend로 해결!
*/

#include <iostream>
#include <cstring>

class Complex {
private:
	double real, img;

	double get_number(const char* str, int from, int to) const;

public:
	Complex(double real, double img) : real(real), img(img) {}
	Complex(const Complex& c) { real = c.real, img = c.img; }
	Complex(const char* str);

	Complex operator+(const Complex& c);
	Complex& operator=(const Complex& c);

	// 나머지 함수들 생략

	void println() {
		std::cout << "( " << real << " , " << img << " ) " << std::endl;
	}

	// friend 키워드를 붙였기에 이 함수는 Complex의 private member에 접근할 수 있다.
	// 본질적으론 Complex 클래스 외부의 함수이다.
	friend Complex operator+(const Complex& a, const Complex& b);
};

Complex operator+(const Complex& a, const Complex& b) {
	Complex temp(a.real + b.real, a.img + b.img);
	return temp;
}

Complex::Complex(const char* str) {
	int begin = 0, end = strlen(str);
	img = 0.0;
	real = 0.0;

	int pos_i = -1;
	for (int i = 0; i != end; i++) {
		if (str[i] == 'i') {
			pos_i = i;
			break;
		}
	}

	// 'i'가 없으면 실수만 존재
	if (pos_i == -1) {
		real = get_number(str, begin, end - 1);
		return;
	}

	// 만일 'i'가 있으면 실수와 허수부를 나눠서 처리 필요
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
	for (int i = 0; i <= to; i++) {
		if (isdigit(str[i]) && integer_part) {
			num *= 10.0;
			num += (str[i] - '0');
		}
		else if (str[i] == '.') {
			decimal /= 10.0;
			num += ((str[i] - '0') * decimal);
		}
		else if (isdigit(str[i]) && !integer_part) {
		}
		else break;
	}
	
	if (minus) num *= -1.0;

	return num;
}

Complex Complex::operator+(const Complex& c) {
	Complex temp(real + c.real, img + c.img);
	return temp;
}
Complex& Complex::operator=(const Complex& c) {
	real = c.real;
	img = c.img;
	return *this;
}

int main() {
	Complex a(0, 0);
	a = "-1.1 + i3.923" + a;
	a.println();
	return 0;
}

/*
	위를 실행하면 오류가 난다.
	컴파일러는 a.operator+(a)와 operator+(a, a) 두 가지 형태 중 하나를 고르는데
	위의 경우 두 형태가 모두 가능해서 어떤 것을 고를지 몰라서 나타나는 오류가 나타난다.

	이를 해결 하기 위해선 두 함수 중 하나를 없애야 한다.

	통상적으로 자기 자신을 리턴하지 않는 이항 연산자들,
	예를 들어 위와 같은 +, -, *, /들은 모두 외부 함수로 선언하는 것이 원칙이다.

	반대로 자기 자신을 리턴하는 이항 연산자들
	예를 들어 +=, -= 같은 애들은 모두 멤버 함수로 선언하는 것이 원칙이다.

	==> 따라서 위의 코드를 수정하면 3_binary_op.cpp
*/