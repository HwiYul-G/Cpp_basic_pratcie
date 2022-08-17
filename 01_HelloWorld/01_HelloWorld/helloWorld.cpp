#include <iostream>	// iostream이라는 header file을 include 하고 있다.
/*
	iosteram 헤더파일은 C++에서 표준 입출력에 필요한 것들을 포함하고 있다.
	예를 들면  std::cout이나 std::endl 같은 것이다.

	이는 C언어에서의 stdio.h와 비슷하다. (그러나 C++ 헤더파일은 .h가 붙지 않는다!)
*/

int main() {
	std::cout << "Hello, World!!!" << std::endl;
	/*
		printf와 다르게 사용된 것을 보니 std::cout은 함수 같지는 않다.
		하지만 이는 화면에 무언가 출력시켜주는 것 같다.

		그리고 화면에 출력된 것이 마지막에 enter가 들어가져 있는 것을 보면
		std::endl은 한 줄 엔터를 쳐서 나타내란 표시 같다.
	*/
	return 0;
}
/*
	[이름공간(namespace)]
	cout 앞에 붙어있는 std의 정체부터 알아보자.
	std는 C++ 표준 라이브러리의 모든 함수, 객체 등이 정의된 이름공간(namespace)이다.

	네임스페이스 = 이름공간은 말그대로 어떤 정의된 객체에 대해 어디 소속인지 지정해주는 것과 동일하다.
	코드의 크기가 늘어남에 따라, 혹은 다른 사람들이 쓴 코드를 가져다 쓰는 경우가 많아지면서
	중복된 이름을 가지는 함수들이 많아졌다.
	따라서 C++에선 이를 굽누하기 위해, 
	같은 이름이라도, 소속된 네임스페이스(이름공간)이 다르면 다른 것으로 취급하게 되었다.

	예를 들어서 서울에 사는 철수와 부산에 사는 철수와 짱구의 철수가 다른 것과 같다.

	std::cout 은 std라는 네임스페이스에 정의되어 있는 cout을 의미한다.
	만약 std:: 없이 그냥 cout만 한다면
	컴파일러가 cout을 찾지 못한다.
	왜냐하면 서울에 산느 철수인지, 부산에 사는 철수인지, 짱구 친구 철수인지 알 수 없기 때문이다.

	이름 공간을 정의하는 방법은 아래와 같다.
	예를 들어 두 헤더파일 header1.h와 header2.h를 생각해보자.

	namespace header1{
		int foo();
		void bar();
	}

	namespace header2{
		int foo();
		void bar();
	}

	위 코드에서 header1에 있는 foo는 header1이라는 네임스페이스에 살고 있는 foo이고
	header2에 있는 foo는 header2라는 네임스페이스에 살고 있는 foo가 된다.

	자기 자신이 포함되어 있는 네임스페이스 내에선 굳이 앞에 네임스페이스를 명시하지 않고 자유롭게 호출할 수 잇다.
	예를 들면 아래와 같다.
	#include "header1.h"
	namespace header1{
		int func(){ 
			foo(); // 알아서 header1::foo(); 가 실행됨
		}
	}

	그렇다고 header1이라는 네임스페이스에서 header2의 foo를 호출할 수 없는 것은 아니다.
	아래와 같이 할 수 있다.
	#include "header1.h"
	#include "header2.h"
	namespace header1 {
		int func() {
			foo();           // 알아서 header1::foo() 가 실행된다.
			header2::foo();  // header2::foo() 가 실행된다.
		}
	}  // namespace header1

	반면에 어떤 네임스페이스에도 소속되지 않는 경우라면 아래와 같이 명시적으로 네임스페이스를 지정해야 한다.
	#include "header1.h"
	#include "header2.h"

	int func() {
		header1::foo();  // header1 이란 이름 공간에 있는 foo 를 호출
	}
	
	그런데 위와 같이 foo를 여러번 반복적으로 호출하게 되는 경우 매번 header1::을 붙이기 상당히 귀찮다.
	그래서 '나는 앞으로 header1이란 이름 공간에 있는 foo만 쓸거다!'라고 선언할 수 있다.

	#include "header1.h"
	#include "header2.h"

	using header1::foo;
	int main() {
		foo();  // header1 에 있는 함수를 호출
	}
	뿐만 아니라 기본적으로 header1 네임스페이스 안에 정의된 모든 것들을 header1:: 없이 사용하고 싶으면 
	using namespace header1;을 하면 된다.

	#include "header1.h"
	#include "header2.h"

	using namespace header1;
	int main() {
		foo();  // header1 에 있는 함수를 호출
		bar();  // header1 에 있는 함수를 호출
	}
	이러한 경우라고 해서 header2의 함수를 사용할 수 없는 것은 아니다.
	header2를 사용하고 싶다면 명시적으로 header2::foo();로 사용하면 된다. 
	명시하지 않고 foo();를 하면 자동으로 header1에 있는 것을 사용하게 된다.

	그렇다면 helloworld2.cpp로 가보자!
*/