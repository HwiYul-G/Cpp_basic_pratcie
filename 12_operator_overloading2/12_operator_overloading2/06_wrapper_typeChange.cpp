/*
	Wrapper class
	기본 자료형들을 객체로 다루어야 할 때가 있다.
	이때 기본 자료형들을 객체로 사용하는 것을 Wrapper 클래스를 이용한다는 것이다.
*/
#include <iostream>

class Int {
	int data;

public:
	Int(int data) : data(data) {}
	Int(const Int& i) : data(i.data) {}

	operator int() { return data; }
};

int main() {
	Int x = 3; // Wrapper 객체
	// int a = x + 4; // 평범한 int형 변수 a
	// 프리미티브 타입(int)인 a와 Wrapper 클래스의 객체인 x는 더할 수 없다.
	
	/*
		int형 변수에 사용되는 모든 연산자에 Int에 대한 wrapper 클래스를 연산하도록
		연산자 오버로딩을 이용할 수도 있다.
		하지만 모든 연산자에 이를 추가하는 것은 귀찮은 일이다.

		그냥 이 Wrapper 클래스 객체를 마치 'int형 변수'라고 컴파일러가 생각수 있다.
		=> 타입 변환 연산자가 있기 때문이다.

		타입 변환 연산자는 아래와 같이 정의한다.
		operaotr (변환 하고자 하는 타입 ()
	*/
	Int y = 3;
	int a = y + 4;

	y = a * 2 + y + 4;
	std::cout << y << std::endl;
	// 타입 변환 연산자를 정의함으로 잘 되는 것을 볼 수 있다.
	return 0;
}