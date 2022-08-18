#include <iostream>

int change_val(int* p) {
	*p = 3;
	return 0;
}

int main() {
	int number = 5;
	std::cout << number << std::endl;
	change_val(&number);
	/*
		change_val 함수의 인자 p에 number의 주소값을 전달해서
		*p를 통해 number를 참조하여 number의 값을 3으로 변경했다.
		
		C언어에선 어떠한 변수를 가리키고 싶을 땐 반드시 포인털르 사용해야만 했다.
		그런데 C++에선 다른 변수나 상수를 가리키는 방법으로 또 다른 방식을 제공한다.
		이를 바로 참조자(레퍼런스, reference)라고 부른다.
		=> 02_reference.cpp

	*/
	std::cout << number << std::endl;
	return 0;
}