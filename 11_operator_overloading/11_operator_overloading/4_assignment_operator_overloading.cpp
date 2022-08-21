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

	Complex& operator+=(const Complex& c);
	Complex& operator-=(const Complex& c);
	Complex& operator*=(const Complex& c);
	Complex& operator/=(const Complex& c);

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

int main() {
	Complex a(1.0, 2.0);
	Complex b(3.0, -2.0);
	a += b;
	a.println();
	b.println();
}
/*
	a값만 바뀌고 b의 값엔 영향 없이 잘 출력됨을 볼 수 있다.

	연산자 오버로딩을 하면 a += b와 a = a + b가 같다고 보장되지 않는 다는 점을 명심해야한다.
	컴파일러는 operator+와 operator=를 정의해 놓았다고 해서 
	a +=b를 자동으로 a = a + b로 바꿔주지 않는다.

	반드시 operator +=를 따로 만들어야 +=를 사용할 수 있게 된다.

	이와 같은 사실은 ++을 +=1;로 바꿔주지 않는다던지 --를 -=1로 바꿔주지 않는 다는 사실과 동일하다.

	즉 연산자 오버로딩을 하게 된다면 모든 연산자에 대한 개별적인 정의가 필요하다.
*/