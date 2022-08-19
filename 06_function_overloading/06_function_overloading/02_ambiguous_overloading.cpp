// 모호한 오버로딩
#include <iostream>

void print(int x) { std::cout << "int : " << x << std::endl; }
void print(char x) { std::cout << "double : " << x << std::endl; }

int main() {
	int a = 1;
	char b = 'c';
	double c = 3.2f;

	print(a);
	print(b);
	print(c);

	return 0;
}
/*
	 error C2668: 'print' : ambiguous call to overloaded function could be 'void print(char)'
						or  'void print(int)' while trying to match the argument list '(double)'

	이러한 오류가 나올 것이다.
	문제가 되는 print(c); 부분을 보자.
	print(c)를 했을 때  자기 타입에 맞는 것이 없다(1) 그래서 2단계로 넘어간다
	double의 캐스팅에 관한 내용이 없어 일치하는 것이 없다. 따라서 3단계로 간다.
	임의의 숫자 타입이 임의의 숫자타입으로 변환되서 생각되므로 double은 char, int로 둘다 변환 될 수 있다.

	따라서 같은 단게에서 2개 이상 가능한 일치가 존재하므로 '모호한' 오류가 발생하게 된다.

	C++의 오버로딩 규칙을 숙지하는 일은 중요하다.
	왜냐하면 나중에 복잡한 함수를 오버로딩 할 때 여러 개가 중복되면서 나온다면 오류의 향연을 볼 수 있기 때문이다.
*/