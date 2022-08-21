#include <iostream>

class Complex {
private:
	double real, img;
public:
	Complex(double real, double img) :real(real), img(img) {}
	Complex(const Complex& c) { real = c.real; img = c.img; }

	Complex operator+(const Complex& c) const;
	Complex operator-(const Complex& c) const;
	Complex operator*(const Complex& c) const;
	Complex operator/(const Complex& c) const;

	Complex& operator=(const Complex& c);

	void println() { std::cout << "( " << real << " , " << img << " ) " << std::endl; }
};

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
Complex& Complex::operator=(const Complex& c) {
	real = c.real;
	img = c.img;
	return *this;
}

int main() {
	Complex a(1.0, 2.0);
	Complex b(3.0, -2.0);
	Complex c(0.0, 0.0);
	c = a * b + a / b + a + b;
	c.println();
}

/*
	오버로딩한 모든 연산자들이 잘 작동한다.

	하지만 한 가지 재미있는 사실은 operator= 를 만들지 않더라도, 위 소스를 컴파일하면 잘 작동한다.
	이 컴파일러 차원에서 디폴트 대입 연산자(default assignment operator)를 지원하고 있기 때문이다.
	이전에 복사 생성자를 다룰 때 디폴트 복사 생성자가 있던 것과 동일하다.

	디폴트 복사 생성자와 마찬가지로 디폴트 대입 연산자 역시 '얕은 복사'를 수행한다.
	따라서 깊은 복사가 필요한 클래스의 경우(ex, 클래스 내부적으로 동적 핟당하는 메모리를 관리하는 포인터가 있다 던지 등)
	대입 연산자를 꼭 만들어 주어야 할 필요가 있다.

	=============================================
	1) Some_Class a = b;
	2) Some_Class a;
		a = b;
	
	1)과 2)는 다르다
	1)의 경우 a의 복사 생성자가 호출되는 것이다. 
	2)의 경우는 a의 기본 생성자가 호출된 다음에 대입 연산자 함수가 실행된다.
	=============================================

	마찬 가지의 이유로 대입 사칙연산 함수들인 +=, -=, *=, /=를 구현할 수 있다.
	우선 =와 마찬가지로 Complex&를 리턴하고 내부 구현은 operator+, operator- 등을 이용해서 처리하면 된다.
	=> 4_assign_op_overloading.cpp
*/