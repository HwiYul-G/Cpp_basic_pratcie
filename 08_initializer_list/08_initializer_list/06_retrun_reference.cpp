#include <iostream>

class A {
	int x;
public:
	A(int c) : x(c) {}

	int& access_x() { return x; }
	int get_x() { return x; }
	void show_x() { std::cout << x << std::endl; }
};

int main() {
	A a(5);
	a.show_x();	// 5

	int& c = a.access_x();
	c = 4;
	a.show_x(); //4

	int d = a.access_x();
	d = 3;
	a.show_x();; // 4
	
	// This is error
	// int& e = a.get_x();
	// a.show_x();
	/*
		error C2440: 'initializing' : cannot convert from 'int' to 'int &'
		이러한 오류가 나타난다.

		그 이유는 레퍼런스가 아닌 타입을 리턴하는 경우 '값' 복사가 이루어지기 때문에
		임시 객체가 생성되는데, 임시 객체의 레퍼런스를 가질 수 없기 때문이다.
		(임시 객체는 문장이 끝나면 소멸된다.)
		이미 존재하지 않는 것에 대한 별명이 되므로 이 레퍼런스에 접근하는 것은 오류이다.
	*/

	int f = a.get_x();
	f = 1;
	a.show_x(); // 4
	/*
		get_x() 를 수행하며 임시 생성된 int형 변수가 f에 복사된다.
		역시 f =1;을 한 것이 실제 객체 a의 x에게 어떤 영향을 끼칠 수 없다.
	*/

	a.access_x() = 3; 
	a.show_x(); // a의 값이 3으로 바뀜
	/*
		access_x()는 reference를 리턴하는 함수이다.
		레퍼런스를 리턴하는 함순느 그 함수 부분을 리턴하는 원래 변수로 치환해도 된다.
		즉 위의 문장은 결국 a.x = 3; 과 동일하다.ㄴ

		반면 a.get_x() = 3;은 역시나 오류가 난다.
		왜냐하면 a.get_x()는 get_x()가 리턴하면서 생성되는 임시 객체로 치환되어 임시 객체에 대입하는
		모순적인 상황이 발생하기 때문이다.
	*/

	return 0;
}

/*
	int& access_x(){return x;}
	int get_x(){return x;}

	access_x는 x의 '레퍼런스'를 리턴하게 되고
	get_x는 x의 '값'을 리턴하게 된다.

	int& c = a.access_x();
	c = 4;
	a.show_x();
	이 부분에서 레퍼런스 c는 x의 레퍼런스, 즉 x의 별명을 받았다.
	따라서 c는 x의 별명으로 탄생하게 되는 것이다.
	레퍼런스를 리턴하는 함수는 그 함수 부분을 원래 변수로 치환했다고 생각해도 상관 없다.
	
	즉 int &c = x; // 여기서 x는 a의 x
	와 동일하다.
	따라서 c의 값을 바꾸는 것은 a의 x값을 바꾸는 것을 동일하다.
	c는 단순히 x에 다른 이름을 붙여준 것일 뿐이다.

	show_x를 실행해보면 x의 값이 5에서 4로 바뀐다.

	int d = a.access_x();
	d = 3;
	a.show_x();
	이번엔 int&가 아닌 그냥 int 변수에 x의 별명을 전달했다.
	만일 d가 int& 였다면 x의 별명을 받아서 d 역시 또다른 x의 별명이 되겠지만
	d가 그냥 int 변수이므로 '값복사'가 일어나 d에는 x의 값이 들어가게 된다.

	그리고 d는 x의 별명이 아닌 또다른 독립적인 변수라 d = 3;을 해도
	x의 값은 바뀌지 않은 채 그냥 4가 출력된다.


*/