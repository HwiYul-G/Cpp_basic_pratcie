/*
	const 멤버 함수는 그 내부에서 멤버 변수들의 값을 바꾸는 것이 불가능하다.
	cosnt 멤버 함수는 값을 read하기 위해 사용한다.

	하지만 만약에 멤버 변수를 mutable로 선언했다면
	const 함수에서도 이 값들을 바꿀 수 있다.
*/

#include <iostream>

class A {
	int data_;
	mutable int data2_;
public:
	A(int data) : data_(data) {}
	void DoSth(int x) const {
		data_ = x; // 불가능
		data2_ = x; // 가능
	}
	void PrintData() const { std::cout << "data: " << data_ << std::endl; }
};

int main() {
	A a(10);
	a.DoSomething(3);
	a.PrintData();
}
/*
	이렇게 사용할 때 mutable이 붙은 data2_ 멤버 변수는
	const 함수 내에서 그 값을 바꿀 수 있다.

	하지만 이럴 바에 const 함수에서 const를 제외하는 편이 낫지 않을까?
	왜 mutable 키워들르 만든 건가?

	클래스의 멤버 함수들은 이 객체가 할 수 있는 '일'을 의미한다.
	그리고 멤버 함수를 const로 선언하는 것의 의미는
	이 함수는 이 객체의 내부 상태에 영향을 주지 않는다를 표현하는 것이다.
	그 중 대표적인 작업이 '읽기'이다.

	대부분의 경우 의미상 상수 작업을 하는 경우 실제로도 상수 작업을 하게 된다.
	하지만 실제로 꼭 그렇지많은 않다.

	=> server.cpp 를 통해 서버 프로그램의 경우를 생각해보자.
*/