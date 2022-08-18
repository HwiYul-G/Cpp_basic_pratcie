#include <iostream>

int function() {
	int a = 2;
	return a;
}

int& function2() {
	int a = 2;
	return a;
}

int& function3(int& a) {
	a = 5;
	return a;
}

int function4() {
	int a = 5;
	return a;
}

int main() {
	int b = function();
	/*
		int b = function(); 에서 function 안에 정의된 a라는 변수의 값(2)이 b에 copy 되었다.
		여기서 주목할 점은 copy 되었다는 점이다.
		function이 종료되고 나면 a는 메모리에서 사라진다.
		따라서 더이상 main 안에서는 a를 만날 일이 없다.
	*/
	int c = function2();
	/*
		위의 int c= function2();를 컴파일하면 경고가 나온다. (오류는 아님)
		In function2 'int& function2()' :
		reference to local variable 'a' returned;

		실제로 실행해보면 segmentation fault (core dumped) 같은 런타임 오류가 발생한다.

		무엇이 문제 였을까?
		function2의 return 타입은 int&이다. 따라서 참조자를 리턴하게 된다. 
		그런데 문제는 리턴하는 function2 안에 정의된 a는 함수의 리턴과 함께 사라지는 local var이다.

		위의 문제는
		int& ref = a;
		int b = ref; // 근데 a가 사라짐
		이것과 같은 의미이다.
		function2가 레퍼런스를 리턴하면서 원래 참조하고 있던 변수가 이미 사라졌으므로 오류가 발생하게 된다.
		쉽게 말해 본체는 이미 사라졌지만 별명만 남아있다.

		이와 같이 레퍼런스는 있느데 원래 참조하던 것이 사라진 레퍼런스를
		댕글린 레퍼런스(Dangling reference)라고 부른다.

		따라서 위의 경우처럼 '레퍼런스를 리턴한느 함수에서 지역 변수의 레퍼런스를 리턴하지 않도록 주의' 해야한다.

		[그렇다면 function3()의 경우는 어떨까?]
	*/
	int d1 = 2;
	int d2 = function3(d1);
	/*
		int& function3(int& a){return a;}
		fuction3 역시 레퍼런스를 리턴하고 있다. 하지만 인자로 받은 레퍼런스를 그대로 리턴하고 있다.
		fuction3(d1)을 실행한 시점에서 function의 지역변수인 a는 main의 d1을 참조하고 있다.
		따라서 function3이 리턴한 참조자는 아직 살아있는 변수인 d1을 계속 참조하고 있다.

		결국 int d2 = function3(d1); 이란 문장은  d2에 d1을 대입하는 거랑 동일하다.

		그렇다면 이렇게 참조자 리턴을 하는 경우 장점이 무엇일까?
		C에서 엄청나게 큰 구조체가 있을 때 해당 구조체 변수를 그냥 리턴하면 전체 복사가 발생해서 시간이 오래 걸린다.
		하지만 해당 구조체를 가리키는 포인터를 리턴하면 그냥 포인터 주소 한번 복사로 빠르게 끝난다.

		레퍼런스도 마찬가지이다.
		레퍼런스를 리턴하게 된다면 레퍼런스가 참조하는 타입의 크기와 상관 없이 딱 한 번의 주소값 복사로 전달이 끝난다.
		따라서 매우 효율적이다.
	*/

	int& e = function4();
	/*
		위의 문장은 참조자가 아닌 값을 리턴하는 함수를 참조자로 받는 것이다.
		즉 함수는 값을 리턴하는데 reference로 받은 경우이다.

		이를 컴파일하면 오류가 발생한다.
		error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’

		e는 function4()의 리턴값은 문장이 끝난 후 바로 사라지는 값이기 때문에 리턴값을 참조할 수 없다.
		따라서 참조자를 만든 즉시 댕글링 레퍼런스가 된다.
		
		만약 
		int& c = function4();
		c = 2;
		와 같은 작업을 하면 런타임 오류를 보게 된다.

		하지만 C++에서 중요한 예외 규칙이 있다.
		=> 08_return_reference2.cpp
	*/
	return 0;
}