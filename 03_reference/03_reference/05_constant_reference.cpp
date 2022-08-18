#include <iostream>

int main() {
	int& ref = 4;	// error C2440: 'initializing' : cannot convert from 'int' to 'int &'
	/*
		상수 값 자체는 literal 이다. (literal : 소스 코드 상에서 고정된 값을 가지는 것)
		그런데 만일 int& ref = 4;로 레퍼런스로 참조한다면
		ref = 5;로 리터럴의 값을 바꾸는 말도 안되는 행위가 가능하게 된다.
		(int& ref = 4;로 ref는 4라는 literal의 별명이 되고 ref = 5;는 4 = 5;가 된다.)
		따라서 C++ 문법 상 상수 리터럴을 일반적인 레퍼런스가 참조하는 것은 불가능하게 되어 있다.

		대신에
		const int& ref = 4;로 '상수 참조자'로 선언한다면 리털러도 참조할 수 있다.
		int a = ref;는 a = 4;란 문장과 동일하게 처리 된다.
	*/
	const int& ref2 = 4; // 4라는 literal의 별명은 ref인데 cosnt로 고정값이다. (즉 ref2 = 5; 같은 행위를 할 수 없다.)
	int a = ref; // int a = 4;와 동일하다.

	std::cout << ref << std::endl;
}