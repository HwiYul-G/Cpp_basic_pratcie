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
	�����ε��� ��� �����ڵ��� �� �۵��Ѵ�.

	������ �� ���� ����ִ� ����� operator= �� ������ �ʴ���, �� �ҽ��� �������ϸ� �� �۵��Ѵ�.
	�� �����Ϸ� �������� ����Ʈ ���� ������(default assignment operator)�� �����ϰ� �ֱ� �����̴�.
	������ ���� �����ڸ� �ٷ� �� ����Ʈ ���� �����ڰ� �ִ� �Ͱ� �����ϴ�.

	����Ʈ ���� �����ڿ� ���������� ����Ʈ ���� ������ ���� '���� ����'�� �����Ѵ�.
	���� ���� ���簡 �ʿ��� Ŭ������ ���(ex, Ŭ���� ���������� ���� �����ϴ� �޸𸮸� �����ϴ� �����Ͱ� �ִ� ���� ��)
	���� �����ڸ� �� ����� �־�� �� �ʿ䰡 �ִ�.

	=============================================
	1) Some_Class a = b;
	2) Some_Class a;
		a = b;
	
	1)�� 2)�� �ٸ���
	1)�� ��� a�� ���� �����ڰ� ȣ��Ǵ� ���̴�. 
	2)�� ���� a�� �⺻ �����ڰ� ȣ��� ������ ���� ������ �Լ��� ����ȴ�.
	=============================================

	���� ������ ������ ���� ��Ģ���� �Լ����� +=, -=, *=, /=�� ������ �� �ִ�.
	�켱 =�� ���������� Complex&�� �����ϰ� ���� ������ operator+, operator- ���� �̿��ؼ� ó���ϸ� �ȴ�.
	=> 4_assign_op_overloading.cpp
*/