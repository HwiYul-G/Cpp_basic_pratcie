/*
	memory management is always important.
	the address values of all variables had to be fixed at compile time 
	in order to run program correctly.

	이를 위해선 많은 제약이 따르기 때문에
	프로그램 실행 시 자유롭게 할당하고 해제할 수 있는 heap이란 공간이 생겼다.

	하지만 이전에 컴파일러에 의해 어느정도 안정성이 보장되는 stack과 달리
	힙은 사용자가 스스로 제어해야하는 부분인 만큼 책임이 따른다.

	C에선 malloc과 free 함수를 지원해 힙 상에서 메모리의 할당을 지원했다.
	C++에도 malloc과 freee 함수를 이용할 수 있다.

	하지만 언어 차원에서 지원하는 것은 바로 new와 delete이다.
	new는 말 그대로 malloc과 대응되는 것으로 메모리를 할당하고 delete는 free에 대응되는 것으로 메모리르 해제한다.

	이 사용법을 보자.
*/
#include <iostream>
int main() {
	int* p = new int;	// int 크기의 공간을 할당해 그 주소값을 p에 집어넣음
	*p = 10;

	std::cout << *p << std::endl;

	delete p;	// p에 할당된 공간이 해제됨

	/*
		delete를 통해서는 사용자가 new를 통해 할당한 공간만 해제가 가능하다.
		만일 아래와 같이 지역변수를 무리하게 delete 하려고 하면
		#include <iostream>
		int main() {
		  int a = 5;
		  delete &a;
		  return 0;
		}
		Heap이 아닌 공간을 해제하려 했다는 경고 메시지가 나온다.

	*/
	return 0;
}