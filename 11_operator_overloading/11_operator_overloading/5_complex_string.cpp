/*
	operator+�� �����ؼ� �� Complex ���� ���ϴ� ���� �ƴ϶�
	���ڿ��� ������ �� �� �ֵ��� operator+ �Լ��� ����� ����.
	���� ���, y = z + "3+i2"; �� ���� ������ ���������� ó���� �� �ְ� �ϴ� ���̴�.

	�̶� ���ڿ��� ���Ҽ��� ��� ǥ���ؾ� �� ���� ���� ����� �ʿ��ϴ�.
	�츮�� ��� (��ȣ) (�Ǽ���) (��ȣ) i (�����)�� ����ϵ��� ����.
	���� ��� "2+i3"�� Complex �� (2,3)�� ��Ÿ���� ���̶� �����ϰ�
	 "2-i3"�� (2, -3)�� ��Ÿ�� ���� �ȴ�.

	 ���� �Ǽ��γ� ������� ���� 0�̶�� ���� �Ƚ��־ �Ǵµ�
	 ���� �� �׳� "3"�� (3,0)�� ��Ÿ���� "-5i"��� (0, -5)�� ��Ÿ���� �ȴ�.

	 ����� �츮�� �Ǽ��ο� ����δ� double �����̹Ƿ� ���ڿ��� �Է¹��� ��
	 �ܼ��� ���� �κи� �޴� ���� �ƴ϶� �Ҽ��� �Ʒ� �κе� ó���� �־�߸� �Ѵ�.

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

	// C��� ǥ�� ���̺귯���� stdlib.h���� atof��� �Լ��� get_number�� ������ ���� �Ѵ�.
	double get_number(const char* str, int from, int to) const;

	void println() { std::cout << "( " << real << " , " << img << " ) " << std::endl; }

};

Complex Complex::operator+(const Complex& c) const {
	Complex temp(real + c.real, img + c.img);
	return temp;
}


// �̷��� �ϳ��ϳ� const char* str�� ���� +, -, ����� ������� ������.
// ���� const char* str�� ���� �����ڸ� �߰��ϴ� �͵� ������ ���� �� ����.
// �̸� �߰�����!
Complex Complex::operator+(const char* str) {
	// �Է¹��� ���ڿ��� �м��ؼ� real�κа� img�κ��� ã�ƾ� �Ѵ�.
	// ���ڿ��� ���� ������ ���� "[��ȣ](�Ǽ���)(��ȣ)i(�����)"
	// �� �� �� ���� ��ȥ�� ���������ϴ�. (������ + �� ����)
	int begin = 0, end = strlen(str);
	double str_img = 0.0, str_real = 0.0;

	// ���� ���� ������ �Ǵ� 'i'�� ��ġ�� ã�´�.
	int pos_i = -1;
	for (int i = 0; i != end; i++) {
		if (str[i] == 'i') {
			pos_i = i;
			break;
		}
	}

	// ���� 'i'�� ���ٸ� �Ǽ��� �ִ�.
	if (pos_i == -1) {
		str_real = get_number(str, begin, end - 1);

		Complex temp(str_real, str_img);
		return (*this) + temp;
	}

	// ���� 'i'�� �ִٸ�, �Ǽ��ο� ����θ� ������ ó��
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
	// �Է¹��� ���ڿ��� �м��ؼ� real�κа� img�κ��� ã�ƾ� �Ѵ�.
// ���ڿ��� ���� ������ ���� "[��ȣ](�Ǽ���)(��ȣ)i(�����)"
// �� �� �� ���� ��ȥ�� ���������ϴ�. (������ + �� ����)
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