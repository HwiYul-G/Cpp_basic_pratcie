#include <iostream>
using namespace std; // std라는 네임스페이스의 것을 사용할 거야! 라고 함으로

int main() {
	cout << "Hello, World!!" << endl; // 귀찮게 std::을 명시하지 않아도 된다.
	return 0;
}
/*
	그런데 using namespace std;와 같이 어떤 이름 공간을 사용하겠다라고 선언하는 것은 권장되지 않는다.
	왜냐하면 std에 이름이 겹치는 함수를 만들게 된다면, 오류가 발생하기 때문이다.

	게다가 C++ 표준 라이브러리는 매우 거대하므로 정말 많은 수의 함수가 존재한다.
	자칫 잘못하다 이름을 겹치게 사용하면 고치느라 많은 시간을 잡아먹게 된다.
	게다가 std에는 매번 수 많은 함수들이 추가되고 있어서 C++ 버전이 바뀔 때마다 
	기존에 잘 동작하던 코드가 이름 충돌로 인해 동작하지 않게 되는 문제가 발생할 수 있다.

	따라서 권장하는 방식은 using namespace std; 같은 것을 사용하지 않고
	 std::을 직접 앞에 붙여서 std의 네임스페이스의 함수이다 라고 명시하는 것이 좋다.
	 또한 직접 작성한 코든느 자신의 네임스페이스에 넣어 혹시 모를 이름 충돌로부터 보호하는 것이 좋다.
*/

/*
	cout은 무엇일까?
	정확히 말하자면 ostream 클래스의 객체로 표준 출력(C언어의 stdout에 대응됨)을 담당한다.
	
	사용법은 아래와 같다.
	std::cout << 출력할것1 <<출력할것2<<출력할것3 << ..... << ....;
	
	endl은 화면에 출력해주는 '함수'이다.
	하지만 그냥 std::cout << std::endl; 이라 쓰면 화면에 엔터를 하나 출력ㅁ해준다.
	이정도로 기억하고  endl; 에 대해선 나중에다루자!

*/
