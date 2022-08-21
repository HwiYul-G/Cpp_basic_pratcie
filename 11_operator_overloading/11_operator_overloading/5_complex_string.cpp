/*
	operator+를 개량해서 꼭 Complex 수를 더하는 것이 아니라
	문자열로 덧셈을 할 수 있도록 operator+ 함수를 만들어 보자.
	예를 들면, y = z + "3+i2"; 와 같은 문장이 성공적으로 처리할 수 있게 하는 것이다.

	이때 문자열을 복소수로 어떻게 표현해야 할 지에 대한 약속이 필요하다.
	우리의 경우 (부호) (실수부) (부호) i (허수부)로 약속하도록 하자.
	예를 들어 "2+i3"은 Complex 수 (2,3)을 나타내는 것이라 생각하고
	 "2-i3"은 (2, -3)을 나타낸 것이 된다.

	 만일 실수부나 허수부의 값이 0이라면 굳이 안써주어도 되는데
	 예를 들어서 그냥 "3"은 (3,0)을 나타내고 "-5i"라면 (0, -5)를 나타내게 된다.

	 참고로 우리의 실수부와 허수부는 double 변수이므로 문자열로 입력받을 때
	 단순히 정수 부분만 받는 것이 아니라 소수점 아래 부분도 처리해 주어야만 한다.

*/
#include <iostream>
class Complex {
private:
	double real, img;
public:
	Complex(double real, double img) :real(real), img(img) {}
	Complex(const Complex& c) { real = c.real; img = c.img; }

	Complex operator+(const Complex& c) const;
	Complex operator+(const char* str);
	Complex operator-(const Complex& c) const;
	Complex operator*(const Complex& c) const;
	Complex operator/(const Complex& c) const;

	Complex& operator=(const Complex& c);

	Complex& operator+=(const Complex& c);
	Complex& operator-=(const Complex& c);
	Complex& operator*=(const Complex& c);
	Complex& operator/=(const Complex& c);

	// C언어 표준 라이브러리인 stdlib.h에서 atof라는 함수는 get_number와 동일한 일을 한다.
	double get_number(const char* str, int from, int to) const;

	void println() { std::cout << "( " << real << " , " << img << " ) " << std::endl; }

};

Complex Complex::operator+(const Complex& c) const {
	Complex temp(real + c.real, img + c.img);
	return temp;
}


// 이렇게 하나하나 const char* str에 대한 +, -, 등등을 만들려면 귀찮다.
// 따라서 const char* str에 대한 생성자를 추가하는 것도 나쁘지 않을 것 같다.
// 이를 추가하자!
Complex Complex::operator+(const char* str) {
	// 입력받은 문자열을 분석해서 real부분과 img부분을 찾아야 한다.
	// 문자열의 꼴은 다음과 같다 "[부호](실수부)(부호)i(허수부)"
	// 이 때 맨 앞의 부혼느 생략가능하다. (생략시 + 라 가정)
	int begin = 0, end = strlen(str);
	double str_img = 0.0, str_real = 0.0;

	// 가장 먼저 기준이 되는 'i'의 위치를 찾는다.
	int pos_i = -1;
	for (int i = 0; i != end; i++) {
		if (str[i] == 'i') {
			pos_i = i;
			break;
		}
	}

	// 만일 'i'가 없다면 실수만 있다.
	if (pos_i == -1) {
		str_real = get_number(str, begin, end - 1);

		Complex temp(str_real, str_img);
		return (*this) + temp;
	}

	// 만일 'i'가 있다면, 실수부와 허수부를 나눠서 처리
	str_real = get_number(str, begin, pos_i - 1);
	str_img = get_number(str, pos_i + 1, end - 1);

	if (pos_i >= 1 && str[pos_i - 1] == '-') str_img *= -1.0;

	Complex temp(str_real, str_img);
	return (*this) + temp;
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
Complex& Complex::operator=(const Complex& c) {
	real = c.real;
	img = c.img;
	return *this;
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

double Complex::get_number(const char* str, int from, int to) const {
	// 입력받은 문자열을 분석해서 real부분과 img부분을 찾아야 한다.
// 문자열의 꼴은 다음과 같다 "[부호](실수부)(부호)i(허수부)"
// 이 때 맨 앞의 부혼느 생략가능하다. (생략시 + 라 가정)
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
		else if (str[i] == '.') {
			integer_part = false; 
		}
		else if (isdigit(str[i]) && !integer_part) {
			decimal /= 10.0;
			num += ((str[i] - '0') * decimal);
		}
		else {
			break;
		}
	}

	if (minus)num *= -1.0;

	return num;
}