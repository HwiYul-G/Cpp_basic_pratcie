/*
	Complex operator+(const Complex& c);�� �����ϰ� ����
	a = a + "-1.1 + i3.923";�� a.operator+("-1.1 + i3.923")���� �������� �Ǿ ���������
	a = "-1.1 + i3.923" + a;�� ���� �׷��� �� �� ����.

	������ �����Ϸ��� ���� �����ڸ� 2���� ������� �ذ��Ѵ�.

	���� ��� @��� �����ڰ� �ִٰ� �ϸ�
	*a.operator@(b);
	*operator@(a,b);
	�����Ϸ��� �� �� ������ ���� ���ؼ� ó���ȴ�.

	a.operator@(b)������ operator@�� a�� Ŭ���� ����Լ��� ���Ǵ� ���̰�
	operator@(a,b)���� operator@�� Ŭ���� �ܺο� ���ǵǾ� �ִ� �Ϲ����� �Լ��� �ǹ��Ѵ�.
	
	================================================
	����� �̴� �Ϻ� �����ڵ鿡 ���ؼ� �ش� ���� �ʴµ�
	��ǥ������ [] ������(÷��), -> ������(��� ����), ���� ������(=), ()�Լ� ȣ�� �����ڵ��� ���
	��� �Լ��θ� ������ �� �ִ�.
	�� ���� ��� �Լ��� �ƴ� ���� �Լ��� �� �� ����.
	================================================
	
	Complex operator+(const Complex& a, const Complex& b) {
		// ...
	}
	�츮�� �� �ٸ� operator+�� 2 ���� const Complex& Ÿ���� ���� a, b�� �ް� �ȴ�.
	�����Ϸ��� ��Ȯ�� ��ġ ���� �ʴ� ���, ���� ����� ������ �����ε� �Ǵ� �Լ��� ã�� �ȴ�.
	��ħ �츮���� Complex(cosnt char*) Ÿ���� �����ڰ� �����Ƿ�
	"-1.1 + i3.923" + a; �� operator+(Complex("-1.1 + i3.923"), a);�� �Ǿ �� ���� �ȴ�.

	�׷��� ������ Complex operator+(const Complex& a, const Complex& b)�� ����� �۵��ϱ� ���ؼ�
	�� �Լ��� a�� b�� private member�� real�� img�� �����ؾ� �Ѵ�.
	=> friend�� �ذ�!
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

	// ������ �Լ��� ����

	void println() {
		std::cout << "( " << real << " , " << img << " ) " << std::endl;
	}

	// friend Ű���带 �ٿ��⿡ �� �Լ��� Complex�� private member�� ������ �� �ִ�.
	// ���������� Complex Ŭ���� �ܺ��� �Լ��̴�.
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

	// 'i'�� ������ �Ǽ��� ����
	if (pos_i == -1) {
		real = get_number(str, begin, end - 1);
		return;
	}

	// ���� 'i'�� ������ �Ǽ��� ����θ� ������ ó�� �ʿ�
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
	���� �����ϸ� ������ ����.
	�����Ϸ��� a.operator+(a)�� operator+(a, a) �� ���� ���� �� �ϳ��� ���µ�
	���� ��� �� ���°� ��� �����ؼ� � ���� ���� ���� ��Ÿ���� ������ ��Ÿ����.

	�̸� �ذ� �ϱ� ���ؼ� �� �Լ� �� �ϳ��� ���־� �Ѵ�.

	��������� �ڱ� �ڽ��� �������� �ʴ� ���� �����ڵ�,
	���� ��� ���� ���� +, -, *, /���� ��� �ܺ� �Լ��� �����ϴ� ���� ��Ģ�̴�.

	�ݴ�� �ڱ� �ڽ��� �����ϴ� ���� �����ڵ�
	���� ��� +=, -= ���� �ֵ��� ��� ��� �Լ��� �����ϴ� ���� ��Ģ�̴�.

	==> ���� ���� �ڵ带 �����ϸ� 3_binary_op.cpp
*/