/*
	friend keyword
	: 클래스 내부에서 다른 클래스나 함수들을 friend로 정의할 수 있는데,
	friend로 정의된 클래스나 함수들은 원래 클래스의 private로 정의된 변수나 함수들에 접근할 수 있다.
*/

class A {
private:
	void private_func() {}
	int private_num;

	friend class B; // class B is a friend of A

	friend void func(); // func is a friend of A(class)
};

class B {
public:
	void b() {
		A a;

		// 비록 pirvate 함수의 필드들이지만 friend이므로 접근 가능
		a.private_func();
		a.private_num = 2;
	}
};

void func() {
	A a;

	// 비록 private 함수의 필드들이지만 friend이므로 접근 가능
	a.private_func();
	a.private_num = 2;
}
/*
	class A 안에서 B를 friend로 지정했기 때문에 B는 A의 모든 private를 볼 수 있다.
	하지만 B 안에서 A를 friend로 지정하지 않았기 때문에
	A는 B의 private 개체들에 접근할 수 없다.
*/

int main() {

	return 0;
}