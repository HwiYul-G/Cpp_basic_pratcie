#include <iostream>

int main() {
	int a = 3;
	int& another_a = a;

	another_a = 5;
	std::cout << "a : " << a << std::endl;	// 5
	std::cout << "another_a : " << another_a << std::endl; // 5

	return 0;
}
/*
	int& another_a = a;
	another_a라는 이름의 'a'의 '참조자'를 정의함.
	이때 참조자를 저장하는 방법은 가리키고자 하는 타입 뒤에 &를 붙이면 된다.

	위 처럼 int형 변수의 참조자를 만들고 싶을 땐 int&를 double의 경우 doube&를 하면 된다.
	심지어 int*와 같은 포인터 타입의 참조자를 만들려면 int*&를 하면된다.

	아무튼 int& another_a = a;로 선언함으로써 우리는 another_a는 a의 참조자다!라고 공표했다.
	이 말은 즉 another_a는 a의 또다른 이름 이라고 컴파일러에게 알려주는 것이다.
	따라서 another_a에 어떠한 작업을 수행하든 이는 사실상 a에 그 작업을 하는 것과 마찬가지이다.

	따라서 another_a = 5;로 a의 참조자인 another_a에 5를 대입했음에도
	실제로 a의 값이 바뀌어있다.

	어떻게 보면 참조자와 포인터는 상당히 유사한 개념이다.
	포인터 역시 다른 변수의 주소값을 보관함으로써 해당 변수에 간접적으로 연산을 수행할 수 있기 때문이다.
	하지만 레퍼런스(참조자)와 포인터는 몇가지 중요한 차이점이 있다.

	1) 레퍼런스는 반드시 처음에 누구의 별명이 될 것인지 지정해야한다.
		- int& another_a; 와 같은 문장은 불가능 하다.
		- int* p; 는 가능하다.

	2) 레퍼런스가 한 번 별명이 되면 절대로 다른 이의 별명이 될 수 없다.
		int a = 10;
		int &another_a = a; // another_a는 이제 a의 참조자.

		int b= 3;
		another_a = b; // NO!!!!!!!!1

		another_a = b;라는 문장은 another_a보고 다른 변수인 b를 가리키라는 말이 아니다.
		이는 그냥 a에 b 값을 대입하라는 의미이다.
		int& another_a = a; 를 하고 나선 another_a에 하는 작업들은 모두 a에 무언가를 하는 것과 동일하다.
		따라서 another_a = b; 는 a = b;와 동일하다.

		참고로 &another_a = b; 는 &a = b;와 동일하므로 말이 안되는 문장이다.

		반면에 포인터의 경우
		int a = 10;
		int* p = &a; // p는 a를 가리킨다.
		int b = 3;
		p = &b; // 이제 p는 b를 가리킨다.
	
	3) 레퍼런스는 메모리 상에 존재하지 않을 수도 있다.
		int a = 10;
		int &another_a = a;
		another_a를 위해서 메모리 상에 공간을 차지할 필요가 사실 없다.
		왜냐하면 another_a의 자리는 모두 a로 바꿔치기 하면 되기 때문이다.
		따라서 이 경우 레퍼런스는 메모리 상에 존재하지 않게 된다.
		그렇다고 해서 항상 존재하지 않는 것은 아니다.
		=> 함수 인자로 레퍼런스를 받는 03_reference.cpp를 보자.
*/