/*
	prefix increment operation
	operator++();
	operator--();
	
	postfix increment operation
	operator++(int x);
	operator--(int x);

	후위 증감 연산자의 인자 int x는 단지 후위 증감 연산자임을 표시하기 위한 것이다.

	- 전위 증감 연산 : 값이 바뀐 자신을 리턴
	- 후위 증감 연산 : 값이 바뀌기 이전의 객체 리턴

	int x = 1;
	func(++x); // x는 2가 전달됨

	int x= 1;
	func(x++); // x는 1이 전달되고 나중에 2가 됨

	A& operator++(){ 
		// A++ 연산 수행
		return *this;
	}
	A operator++(int x){
		A temp(A);
		// A++을 수행한다.
		return temp;
	}

	후위 증감 연산의 경우 ++을 하기 전에 객체를 반환해야해서 
	temp 객체를 만들어서 이전 상태를 기록한 후
	++을 수행한 뒤에 temp 객체를 반환하게 된다.

	따라서 후위 증감 연산의 경우 추가적으로 복사 생성자를 호출함으로 전위 증감 연산보다 더 느리다.
*/

#include <iostream>

class Test {
	int x;
public:
	Test(int x) :x(x) {}
	Test(const Test& t) : x(t.x) {}

	Test& operator++() {
		x++;
		std::cout << "전위 증감 연산자" << std::endl;
		return *this;
	}
	Test operator++(int x) {
		Test temp(*this);
		x++;
		std::cout << "후위 증감 연산자" << std::endl;
		return temp;
	}
	
	int get_x() const { return x; }
};

void func(const Test& t) {
	std::cout << "x : " << t.get_x() << std::endl;
}

int main() {
	Test t(3);

	func(++t); // 4
	func(t++); // 4가 출력됨 (그리고나서 5로 바뀜)

	std::cout << "x : " << t.get_x() << std::endl;
	return 0;
}

/*
	연산자 오버로딩에 대한 요점 정리
	- 2 개의 동등한 객체 사이에서 이항 연산자는 멤버 함수가 아닌 외부 함수로 오버로딩하는 것이 좋다.
	- 두 개의 객체 사이의 이항 연산자이지만 한 객체만 값이 바뀐다던지 등의 동등하지 않은 이항 연산자는 멤버 함수로 오버로딩
	- 단항 연산자는 멤버 함수로 오버로딩하는 것이 좋다. (ex. operator++ )
	- 일부 연산자들은 반드시 멤버 함수로만 오버로딩 해야한다. (객체 자신을 리턴하는 경우)
*/