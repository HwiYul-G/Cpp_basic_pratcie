/*
	std::cout<< a;
	=> std::cout.operator<<(a)�� ������ ����

	�� std::cout�̶�� ��ü�� ��� �Լ� operator<<�� ���ǵǾ� �־
	a�� ȣ���ϰ� �ϴ� ���̴�.

	�׷��� std::cout�̶�� �� �ϳ��� int, double, char �� �پ��� Ÿ���� ������ ����Ѵ�.
	�� ������ operator<< �Լ����� �����ε��Ǿ� �ֱ� �����̴�.

	include �ϴ� iostream(istream + ostream)�� ������� ������ ���캸��
	ostream Ŭ������ �Ʒ��� ���� ���� operator<<���� ���ǵǾ� �ִ�.
	
	ostream& operator<<(bool val);
	ostream& operator<<(short val);
	ostream& operator<<(unsigned short val);
	ostream& operator<<(int val);
	ostream& operator<<(unsigned int val);
	ostream& operator<<(long val);
	ostream& operator<<(unsigned long val);
	ostream& operator<<(float val);
	ostream& operator<<(double val);
	ostream& operator<<(long double val);
	ostream& operator<<(void* val);

	Complex Ŭ�������� ostream Ŭ������ ������ operaotr<<�� �����Ӱ� ����� �� �ְ� �غ���.
	Complex c;
	std::cout<< c;
	�� �ϸ� c.println();�� �� �Ͱ� ���� ȿ���� ������
    ======


    ostream Ŭ������ operator<< ����Լ��� ���Ӱ� �߰��ϴ� ���� �Ұ��� (ǥ�� ��������� �����ؾ� �ϹǷ�)
    ���� ostream Ŭ������ Complex ��ü�� �����ε��ϴ� operator<< ������ �Լ��� �߰��� ���� ����.

    Ŭ���� ������ �Լ��� �߰��ϴ� ������� ��� �Լ��� ����ϴ� �� ������ �� �ִ�
    ostream Ŭ���� ��ü�� Complex ��ü 2���� ���ڷ� �޴� ���� operator<< �Լ��� �����ϸ� �ȴ�.
*/
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

    Complex& operator+=(const Complex& c);
    Complex& operator=(const Complex& c);

    // ������ ������ �Լ����� ���� :)

    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
    friend Complex operator+(const Complex& a, const Complex& b);
};

Complex operator+(const Complex& a, const Complex& b) {
    Complex temp(a.real + b.real, a.img + b.img);
    return temp;
}
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "( " << c.real << " , " << c.img << " ) ";
    return os;
}

Complex::Complex(const char* str) {
    // �Է� ���� ���ڿ��� �м��Ͽ� real �κа� img �κ��� ã�ƾ� �Ѵ�.
    // ���ڿ��� ���� ������ �����ϴ� "[��ȣ](�Ǽ���)(��ȣ)i(�����)"
    // �� �� �� ���� ��ȣ�� ���� �����մϴ�. (������ + �� ����)

    int begin = 0, end = strlen(str);
    img = 0.0;
    real = 0.0;

    // ���� ���� ������ �Ǵ� 'i' �� ��ġ�� ã�´�.
    int pos_i = -1;
    for (int i = 0; i != end; i++) {
        if (str[i] == 'i') {
            pos_i = i;
            break;
        }
    }

    // ���� 'i' �� ���ٸ� �� ���� �Ǽ� ���̴�.
    if (pos_i == -1) {
        real = get_number(str, begin, end - 1);
        return;
    }

    // ���� 'i' �� �ִٸ�,  �Ǽ��ο� ����θ� ����� ó���ϸ� �ȴ�.
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
            break;  // �� �̿��� �̻��� ���ڵ��� �� ���
    }

    if (minus) num *= -1.0;

    return num;
}

Complex& Complex::operator+=(const Complex& c) {
    (*this) = *this + c;
    return (*this);
}
Complex& Complex::operator=(const Complex& c) {
    real = c.real;
    img = c.img;
    return *this;
}

int main() {
    Complex a(0, 0);
    a = "-1.1 + i3.923" + a;
    std::cout << "a �� ���� : " << a << " �̴�. " << std::endl;
}