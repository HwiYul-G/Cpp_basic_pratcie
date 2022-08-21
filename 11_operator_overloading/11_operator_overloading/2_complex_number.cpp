// ������ ����� ��c++ ǥ�� ���̺귯���� std::complex�� ���ǵǾ� �־ ���� ���� ����� �ʿ� ����.
#include <iostream>
class Complex {
private:
	double real, img;
public:
	Complex(double real, double img) : real(real), img(img) {}

	/* 
		������ �����ε��� �𸥴� ���
		Complex plus(const Complex& c);
		Complex minus(const Complex& c);
		Complex times(const Complex& c);
		Complex divide(const Complex& c);

		�̷��� �Ǹ� ���� int �� �������� �� a + b / c + d;�� �����ϰ� �� ����
		a.plus(b.divide(c)).plus(d);�� ���� ������ �Լ����� �̿��ؼ� ǥ���ؾ� �Ѵ�.

		������ ������ �����ε��� �̿��ؼ� plus�� operator+�� divid�� operator/�� ���
		�ٲ��ָ� ������ �ϴ� ��ó�� +, - ���� �̿��ؼ� ���ϰ� ����� �� �ִ�.
	*/
	Complex operator+(const Complex& c) const;
	Complex operator-(const Complex& c) const;
	Complex operator*(const Complex& c) const;
	Complex operator/(const Complex& c) const;
	/*
		���⼭ �߿��ϰ� �����ϴ� ���� ��Ģ���� ������ �Լ����� ����Ÿ���̴�.
		���� Complex�� �ƴ϶� Complex&�� �����ϸ� ��� �ɱ�?

		Complex& operator+(const Complex& c) {
			real += c.real;
			img += c.img;
			return *this;
		}
		�׷� ���� ���� ���� �ۼ��ϰ� �� ���̴�.
		�̷��� ���۷����� ������ ���� ������ �ִ�. Complex�� �����ϴ� ��� �����簡 �Ͼ�� �ӵ� ���ϰ� �߻��Ѵ�.
		������ ���۷���(Complex&)�� �����ϴ� ��� ���۷����� �����ϴ� ���̹Ƿ� ū �ӵ����ϰ� ��Ÿ���� �ʴ´�.

		������ �̷� ���۷����� ��ȯ�ϴ� �����ڸ� �����ϰ� �Ʒ��� ���� ������ �����ϸ� ��� �ɱ�?
		Complex a = b + c + d;
		�� ������ �� ���� a = 2*b + c;�� �ǵ����� ���̴�.

		������ ������ ó���Ǵ� ���� ���� (b.plus(c)).plus(b)�� �ȴ�.
		b.plus(c)�� �ϸ鼭 b���� b+c�� ���� �ű⿡ �ٽ� plus(b)�� �ϰ� �ȴٸ�
		�� ��ü�� ���� (b+c) + (b+c)�� �Ǿ (�ֳ��ϸ� ���� b���� b+c�� �� �����Ƿ�)
		a = 2*b + 2*c�� �ȴ�.

		�̷��� ����� ���� ���ؼ� �ݵ�� �� ���� �����ؾ��Ѵ�.

		���� �Լ� ���ο��� 'read'�� ����ǰ� ���� �ٲ��� �ʴ� ���ڵ鿡 ���ؼ� const Ű���带 �ٿ��ش�.
		operator+�� ���, c�� ���� ������ ���� c�� ���� ��� ��ȭ�� ���� �����Ƿ�
		cosnt Complex* Ÿ������ ���ڸ� �޾Ҵ�.

		!! ������ ���� �Լ� ���ο��� �ٲ��� �ʴ´ٰ� Ȯ���� ���� const Ű���带 �� �ٿ��� ������ �Ǽ��� ���� !!
		���� �� ������ operator+�� ��� ��ü ������ ���� �������� �ʱ� ������ ���ο� ��� �Լ��� ����!
	*/

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

int main() {
	Complex a(1.0, 2.0);
	Complex b(3.0, -2.0);

	Complex c = a * b;

	c.println();
}