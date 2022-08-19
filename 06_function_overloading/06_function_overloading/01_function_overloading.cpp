/*
	overload
	1) 과적하다
	2) sb (with sth) 너무 많이 주다(부과하다)
	3) (컴퓨터, 전기 시스템에) 과부하가 걸리게 하다.

	그렇다면 함수 오버로딩이라는 것은 함수에 과부하를 주는 것인가? -> 맞다.
	사실 C언어에서는 하나의 이름을 가지는 함수는 딱 1개만 존재할 수 밖에 없어서
	과부하라는 말 자체가 성립되지 않는다.

	하지만 C++에선 같은 이름을 가진 함수가 여러 개 존재해도 된다.
	즉 함수의 이름에 과부하가 걸려도 된다.

	그렇다면 C++에선 어떻게 같은 이름의 함수를 호출 했을 때 구분을 할까?
	=> 인자를 보고 한다.
*/
#include <iostream>

void print(int x) { std::cout << "int : " << x << std::endl; }
void print(char x) { std::cout << "char : " << x << std::endl; }
void print(double x) { std::cout << "double : " << x << std::endl; }

int main() {
	int a = 1;
	char b = 'c';
	double c = 3.2f;

	/*
		c에서는 int, char, double type에 따라서 함수의 이름을 각각 다르게 만들어서 호출해 주어야 했다면
		C++에선 컴파일러가 알아서 적합한 인자를 가지는 함수를 찾아서 호출해 준다.

		만일 void print(char x); 를 없앤다면 
		char 타입인 b를 인자로 넣어준 printf함수는 void print(int x)가 작동한다.
		=> char의 경우 자기와 정확히 일치하는 인자를 가진 함수가 없어서 '자신과 최대로 근접한 함수'를 찾게 됨
	*/
	print(a);
	print(b);
	print(c);

	return 0;
}
/*
	C++ 컴파일러에서 함수를 오버로딩 하는 과정
	1) 자신과 타입이 정확히 일치하는 함수를 찾음
	2) 정확히 일치하는 타입이 ㅇ벗는 경우 아래와 같은 형변환을 통해 일치하는 함수를 찾음
		- char, unsigned char, short 는 int로
		- unsigned short는 int의 크기에 따라 int 혹은 unsigned int로
		- float은 double로
		- Enum은 int로
	3) 위와 같이 변환해도 일치하는 것이 엇다면 좀 더 포괄적인 형변환을 통해 일치하는 함수를 찾는다.
		- 임의의 숫자 타입은 다른 숫자 타입으로 변환된다. (float -> int)
		- Enum도 임의의 숫자 타입으로 변환된다. (Enum -> double)
		- 0은 포인터 타입이나 숫자 타입으로 변환된 0은 포인터 타입이나 숫자 타입으로 변환된다.
		- 포인터는 void 포인터로 변환된다.
	4) 유저 정의된 타입 변환으로 일치하는 것을 찾는다.

	만약 컴파일러가 위 과정을 통해도 함수를 찾을 수 없거나 같은 단게에서 2개 이상이 일치하는 경우에
	모호하다(ambiguous)라고 판단해서 오류를 발생시킨다.

	void print(int x)와 void print(double x)만 있던 상황에서
	print(b)로 char 타입인 b를 인자로 넘기면 2단계로 넘어가서 
	char를 int로 변환되게해서 void print(int x) 함수가 호출된다.

	=> 02_ambiguous_overloading.cpp 를 보자.
*/