#include <iostream>

int change_val(int& p) {
	p = 3;

	return 0;
}
int main() {
	int number = 5;

	std::cout << number << std::endl;
	change_val(number);
	std::cout << number << std::endl;
}
/*
	pointer를 이용해서 만들었던 change_val 함수를 참조자를 이용해서 만들었다.
	그런데 아까 int& p 처럼 선언만 하는 것은 불가능하다고 했다.
	하지만 function의 argument인 p가 정의되는 순간은 change_val(number);를 호출하는 순간이므로
	int& p = number;가 실행된다고 생각하면 된다.

	change_val(number);를 함으로 
	p에게 "너는 앞으로 number의 새로운 별명이야"라고 알려주게 된다.

	여기서 중요한 점은 함수를 호출할 때 포인터가 인자일 때와 달리 &를 앞에 붙일 필요가 없다는 점이다.

	그 후 change_val 함수 안에서 p = 3;이라는 것은 main 함수의 number에 number = 3;을 한 것과 동일한 수행을 한다.
	그래서 포인터를 인자로 전달할 때보다 여러모로 깔끔하게 사용할 수 있다.
*/