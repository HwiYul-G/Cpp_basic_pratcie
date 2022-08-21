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

    Complex operator+(const Complex& c) const;
    Complex operator-(const Complex& c) const;
    Complex operator*(const Complex& c) const;
    Complex operator/(const Complex& c) const;

    Complex operator+(const char* str) const;
    Complex operator-(const char* str) const;
    Complex operator*(const char* str) const;
    Complex operator/(const char* str) const;

    Complex& operator+=(const Complex& c);
    Complex& operator-=(const Complex& c);
    Complex& operator*=(const Complex& c);
    Complex& operator/=(const Complex& c);

    Complex& operator=(const Complex& c);

    void println() {
        std::cout << "( " << real << " , " << img << " ) " << std::endl;
    }
};
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
Complex Complex::operator+(const char* str) const {
    Complex temp(str);
    return (*this) + temp;
}
Complex Complex::operator-(const char* str) const {
    Complex temp(str);
    return (*this) - temp;
}
Complex Complex::operator*(const char* str) const {
    Complex temp(str);
    return (*this) * temp;
}
Complex Complex::operator/(const char* str) const {
    Complex temp(str);
    return (*this) / temp;
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
Complex& Complex::operator=(const Complex& c) {
    real = c.real;
    img = c.img;
    return *this;
}

int main() {
    Complex a(0, 0);
    a = a + "-1.1 + i3.923";
    a.println();
    a = a - "1.2 -i1.823";
    a.println();
    a = a * "2.3+i22";
    a.println();
    a = a / "-12+i55";
    a.println();
}

/*
    �̶� Complex(const char* str) �����ڸ� ���ܳ���
    operator+(const char* str) �迭���� ��� �������� �������غ���.

    �׷��� ���������� ������ ����� ���´�.
    �׷� �����ؼ� const char* str�� ���� operator+,-,*,/�� ���� ���� ����ϴ�.
    Complex operator+(const char *str) const;
    Complex operator-(const char *str) const;
    Complex operator*(const char *str) const;
    Complex operator/(const char *str) const;

    �̰��� ��� ������ ������ �����Ϸ��� �ȶ��ϱ� �����̴�.
    ���� a = a + "-1.1 + i3.923";�� ���� ������ ������� �� �����Ϸ��� �Ʒ��� ���� �ٲ��ش�.
    a = a.operator+("-1.1 + i3.923");

    ������ �츮���� operator+(const char* str)�� ���� operator+(const Complex& c)�ۿ� ���
    ���������� �����ε� ������ �ʴ´�.
    �׷����� �����Ϸ��� �ſ� �ȶ��ؼ� ���� ������ �����ε��� �� �ִ� �Լ����� �ִ� �� ���� �� Ȯ���� ����.

    const char*���� Complex�� ������ �� �ִ� ������
    Complex(const char* str);�� �����Ƿ� �����Ϸ��� ���ڿ� literal�κ��� cosnt Complex Ÿ�� ��ü�� ���Ӱ� �����Ѵ�.

    �� a = a.operator+("-1.1 + i3.923");��� ������ �Ʒ��� ���� ����ȴ�
    a = a.operator+(Complex("-1.1 + i3.923"));
    ���� const Complex�� ���ڸ� ������ �� �ְ� �Ǿ� ���α׷��� �ùٸ��� �۵��ϰ� �ȴ�.

    ���⼭ �߿��� ���� operator+ �Լ��� ���ڰ� const Complex& c�� �ƴ϶� 
    Complex& c�� �޵��� �ߴٸ� ���� ���� ��ȯ�� �ȶ��ϰ� �Ͼ�� �ʴ´�.

    �ֳ��ϸ� -1.1 + i3.923 ��ü�� 'string literal'�̱� ������
    �̸� ������ ������ ��ü ���� ��� ���� �ϱ� �����̴�.
    ���� ���� ��� �Լ��� ���� ���� �������� �ʴ´ٴ� Ȯ���� ��� ������ const ���ڷ� �޵��� �ϴ� ���� ����.

    �׷��ٸ� +�� ������ �ٲ� �Ʒ��� ���� ���� ������ �ɱ�?
    a = a + "-1.1 + i3.923";�� �ƴ϶� a = "-1.1 + i3.923" + a;�ϴ� ���� �۵��ұ�?

    + �����ڴ� ��ȯ ��Ģ�� �����ϴ� ������ �̹Ƿ� �����ؾ� ������
    a = "-1.1 + i3.923" + a;�� ��� ���������� ������ ���� �ʴ´�.
    �ֳ��ϸ� a = a + "-1.1 + i3.923";�� a.operator+("-1.1+i3.923")���� ��ȯ�Ǿ ��Ȯ�� ����� �� ������
    a = "-1.1 + i3.923" + a;�� ��� �� ��ȯ�� �Ұ����ϱ� �����̴�.

    => �̿� ���ؼ� ��� �ذ��� �� ������?? 
        �̴� ���� ������Ʈ����!
    
    
*/