// 실제로 사용할 때c++ 표준 라이브러리에 std::complex가 정의되어 있어서 굳이 만들어서 사용할 필욘 없다.
#include <iostream>
class Complex {
private:
	double real, img;
public:
	Complex(double real, double img) : real(real), img(img) {}

	/* 
		연산자 오버로딩을 모른느 경우
		Complex plus(const Complex& c);
		Complex minus(const Complex& c);
		Complex times(const Complex& c);
		Complex divide(const Complex& c);

		이렇게 되면 만일 int 형 변수였을 때 a + b / c + d;로 간단하게 할 것을
		a.plus(b.divide(c)).plus(d);와 같이 복잡한 함수식을 이용해서 표현해야 한다.

		하지만 연산자 오버로딩을 이용해서 plus를 operator+로 divid를 operator/로 등등
		바꿔주면 기존에 하던 것처럼 +, - 등을 이용해서 편리하게 사용할 수 있다.
	*/
	Complex operator+(const Complex& c) const;
	Complex operator-(const Complex& c) const;
	Complex operator*(const Complex& c) const;
	Complex operator/(const Complex& c) const;
	/*
		여기서 중요하게 봐야하는 것이 사칙연산 연산자 함수들의 리턴타입이다.
		만약 Complex가 아니라 Complex&를 리턴하면 어떻게 될까?

		Complex& operator+(const Complex& c) {
			real += c.real;
			img += c.img;
			return *this;
		}
		그럼 위와 같은 경우로 작성하게 될 것이다.
		이렇게 레퍼런스를 리턴할 때의 장점도 있다. Complex를 리턴하는 경우 값복사가 일어나서 속도 저하가 발생한다.
		하지만 레퍼런스(Complex&)를 리턴하는 경우 레퍼런스만 복사하는 것이므로 큰 속도저하가 나타나지 않는다.

		하지만 이런 레퍼런스를 반환하는 연산자를 정의하고 아래와 같은 문장을 수행하면 어떻게 될까?
		Complex a = b + c + d;
		위 문장을 쓴 것은 a = 2*b + c;를 의도했을 것이다.

		하지만 실제로 처리되는 것을 보면 (b.plus(c)).plus(b)가 된다.
		b.plus(c)를 하면서 b에는 b+c가 들어가고 거기에 다시 plus(b)를 하게 된다면
		값 자체만 보면 (b+c) + (b+c)가 되어서 (왜냐하면 현재 b에는 b+c가 들어가 있으므로)
		a = 2*b + 2*c가 된다.

		이러한 결과를 막기 위해서 반드시 각 값을 리턴해야한다.

		또한 함수 내부에서 'read'만 수행되고 값이 바꾸지 않는 인자들에 대해선 const 키워드를 붙여준다.
		operator+의 경우, c의 값을 읽지만 하지 c의 값에 어떠한 변화도 주지 않으므로
		cosnt Complex* 타입으로 인자를 받았다.

		!! 인자의 값이 함수 내부에서 바뀌지 않는다고 확신할 때는 const 키워드를 꼭 붙여서 추후의 실수를 막자 !!
		또한 이 버전의 operator+의 경우 객체 내부의 값을 변경하지 않기 때문에 새로운 상수 함수로 선언!
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