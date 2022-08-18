#include <iostream>

int main() {
	int lucky_number = 3;
	std::cout << "내 비밀 수를 맞춰 보세요~" << std::endl;

	int user_input;
	while (true)
	{
		std::cout << "입력 : ";
		std::cin >> user_input;
		if (lucky_number == user_input) {
			std::cout << "맞추셨습니다~~" << std::endl;
			/*
				cout은 앞에서 배운 것처럼 <<을 이용해 출력시킨다.

				그리고 cin은 사용자로부터 입력을 받아서 >>을 이용해 user_input에 넣는다.
				cin도 cout과 마찬가지로 std에 정의되어 있기 때문에 std::cin과 같이 사용해야 한다.

				c에선 scanf로 입력시 &를 붙여 주소값을 알려주었는데
				C++에선 편리하게 &연산자를 붙일 필요가 없다.
				심지어 scanf에서는 int 형태로 입력을 받을지 아니면 char 인자에 따라서 %d나 %c 등을 구분했는데
				여기선 변수를 보고 cin이 알아서 처리해주어서 매우 편리하다.

				아직 cin이나 cout이 무엇인지,
				shift연산자로 사용되었던 <<이나 >>은 뭔지 감이 오지 않는다.
				우선 사용하고 나중에 이 강좌를 들으면서 알게 될 것이다.!
			*/
			break;
		}
		else {
			std::cout << "다시 생각해보세요~" << std::endl;
		}
	}
	return 0;
}