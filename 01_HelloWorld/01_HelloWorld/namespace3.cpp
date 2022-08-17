#include <iostream>
/*
	C++에서는 네임스페이스에 굳이 이름을 설정하지 않아도 된다.

	이 경우 해당 네임스페이스에 정의된 것들은 해당 파일 '안'에서만 접근할 수 있게 된다.
	이 경우 마치 static을 이용한 것과 같은 효과를 낸다.
*/

namespace {
	// 이 함수는 이 파일 안에서만 사용할 수 있다.
	// 이는 마치 static int OnlyInThisfile() 과 동일하다.
	int OnlyInThisFile() {}

	// 이 변수 역시 static int x; 와 동일하다.
	int only_in_this_file = 0;
} // namespace

int main() {
	OnlyInThisFile();
	only_in_this_file = 3;
	return 0;
}