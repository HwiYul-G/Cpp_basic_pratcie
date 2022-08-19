/*
	디폴트 복사 생성자의 한계
*/
#include <string.h>
#include <iostream>

class Photon_Cannon {
	int hp, shield;
	int coord_x, coord_y;
	int damage;

	char* name;	// 추가함!!

public:
	Photon_Cannon(int x, int y);
	Photon_Cannon(int x, int y, const char* cannon_name);
	~Photon_Cannon();

	void show_status();
};

Photon_Cannon::Photon_Cannon(int x, int y) {
	hp = shield = 100;
	coord_x = x;
	coord_y = y;
	damage = 20;

	name = NULL;
}
Photon_Cannon::Photon_Cannon(int x, int y, const char* cannon_name) {
	hp = shield = 100;
	coord_x = x;
	coord_y = y;
	damage = 20;

	name = new char[strlen(cannon_name) + 1];
	strcpy(name, cannon_name);
}
Photon_Cannon::~Photon_Cannon() {
	// 0 이 아닌 값은 if 문에서 true 로 처리되므로
	// 0 인가 아닌가를 비교할 때 그냥 if(name) 하면
	// if(name != 0) 과 동일한 의미를 가질 수 있다.

	// 참고로 if 문 다음에 문장이 1 개만 온다면
	// 중괄호를 생략 가능하다.

	if (name) delete[] name;
}
void Photon_Cannon::show_status() {
	std::cout << "Photon Cannon :: " << name << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
		<< std::endl;
	std::cout << " HP : " << hp << std::endl;
}

int main() {
	Photon_Cannon pc1(3, 3, "Cannon");
	Photon_Cannon pc2 = pc1;

	pc1.show_status();
	pc2.show_status();
}
/*
	이를 실행하면 런타임 오류가 난다.
	분명히 디폴트 복사 생성자는 원소들 간의 정확한 복사를 1:1로 수행해 준다고 했다.

	그럼 여기서 우리의 디폹트 복사 생성자가 어떻게 생겼는 지 보자.
	아마 아래와 같은 복사 생성자가 만들어 졌을 것이다.
	Photon_Cannon::Photon_Cannon(const Photon_Cannon& pc){
		hp = pc.hp;
		shield = pc.shield;
		coord_x = pc.coord_x;
		coord_y = pc.coord_y;
		damage = pc.damage;
		name = pc.name;
	}
	그럼 위 복사 생성자를 홏루한 뒤에 pc1과 pc2가 어떻게 되었는 지 보자.
	hp, shield, ... , name까지 모두 같은 값을 갖게 된다.
	여기서 name이 같은 값- 즉 2개의 포인터가 같은 값을 가진다 -으로 같은 주소값을 가리킨다.

	즉, 우리는 pc1의 name이 동적으로 할당받아서 가리키고 있던 메모리("Cannon"이라는 문자열이 저장된 메모리)를 pc2의 name도 같이 가리키게 되나.

	물론 이 상태에서는 별 문제가 안된다.
	같은 메모리를 서로 다른 두 포인터가 가리켜도 되기 때문이다.

	하지만 문제는 소멸자에서 일어난다.
	main 함수가 종료되기 직전에 생성되었던 객체등른 파괴되면서 소멸자를 호출하게 된다.
	만일 pc1이 먼저 파괴 되었다면 pc1이 삭제되면서 name이 가리키고 있는 값(포인터)까지 delete하게 된다.
	그런데 pc2의 name이 이미(방금) 해제된 메모리를 가리키고 있다.

	Photon_Cannon::~Photon_Cannon() {
		if (name) delete[] name;
	}

	pc2에서 일단 name은 NULL이 아니므로 (가리키고 있던 주소값이 있다) delete [] name이 수행된다.
	그런데 이미 해제된 메모리에 다시 접근해서 다시 해제하려고 했기 때문에 (사실 접근한 것 자체만으로 오류)
	런 타임 오류가 발생하게 된다.

	그렇다면 이 문제를 막으려면 어케 해야할까? 답은 간단하다!
	복사 생성자에서 name을 그대로 복사하지 말고 따로 메모리에 동적할당을 해서 그 내용만 복사하면 된다.
	이렇게 메모리를 새로 할당해서 내용을 복사하는 것을 깊은 복사(deep copy)라고 부른다.

	아까처럼 단순히 대입만 해주는 것을 얕은 복사(shallow copy)라고 부른다.

	컴파일러가 생성하는 디폴트 복사 생성자의 경우 얕은 복사만 할 수 있어서 
	위와 같이 깊은 복사가 필요한 경우엔 사용자가 직접 복사 생성자를 만들어야한다.

	깊은 복사를 위해 복사생성자를 만드는 것을 06_deep_copy.cpp를 보자!
*/