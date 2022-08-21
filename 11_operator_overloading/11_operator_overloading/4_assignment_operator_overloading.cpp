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
	a���� �ٲ�� b�� ���� ���� ���� �� ��µ��� �� �� �ִ�.

	������ �����ε��� �ϸ� a += b�� a = a + b�� ���ٰ� ������� �ʴ� �ٴ� ���� ����ؾ��Ѵ�.
	�����Ϸ��� operator+�� operator=�� ������ ���Ҵٰ� �ؼ� 
	a +=b�� �ڵ����� a = a + b�� �ٲ����� �ʴ´�.

	�ݵ�� operator +=�� ���� ������ +=�� ����� �� �ְ� �ȴ�.

	�̿� ���� ����� ++�� +=1;�� �ٲ����� �ʴ´ٴ��� --�� -=1�� �ٲ����� �ʴ� �ٴ� ��ǰ� �����ϴ�.

	�� ������ �����ε��� �ϰ� �ȴٸ� ��� �����ڿ� ���� �������� ���ǰ� �ʿ��ϴ�.
*/