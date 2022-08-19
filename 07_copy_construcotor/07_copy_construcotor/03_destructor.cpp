#include <iostream>

class Test {
	char c;
public:
	Test(char _c) {
		c = _c;
		std::cout << "생성자 호출 " << c << std::endl;
	}
	~Test() { std::cout << "소멸자 호출 " << std::endl; }
};

void simple_function() { Test b('b'); }

int main() {
	Test a('a'); // 이렇게 하면 stack 영역에 객체를 할당한 것 (new 키워드 이용시만 heap에)
	simple_function();
	return 0;
}
/*
	소멸자가 하는 가장 흔한 역할은 객체가 동적으로 할당받은 메모리를 해제하는 일이다.
	그 외에도 쓰레드 사이에서 lock된 것을 푸는 역할 등 다양한 역할을 수행한다.

	생성자를 정의하지 않더라도 디폴트 생성자가 있던 것처럼,
	소멸자도 디폴트 소멸자가 있다.

	물론 디폴트 소멸자 내부에선 아무런 작업도 수행하지 않는다.
	만일 소멸자가 필요 없는 클래스라면 굳이 소멸자를 쓸 필욘 없다.
*/