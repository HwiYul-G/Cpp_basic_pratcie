#include <iostream>
#include <string.h>

class Photon_Cannon {
	int hp, shield;
	int coord_x, coord_y;
	int damage;
public:
	Photon_Cannon(int x, int y);
	Photon_Cannon(const Photon_Cannon& pc);

	void show_status();
};

Photon_Cannon::Photon_Cannon(int x, int y) {
	std::cout << "생성자 호출!" << std::endl;
	hp = shield = 100;
	coord_x = x;
	coord_y = y;
	damage = 20;
}
Photon_Cannon::Photon_Cannon(const Photon_Cannon& pc) {
	std::cout << "복사 생성자 호출!" << std::endl;
	hp = pc.hp;
	shield = pc.shield;
	coord_x = pc.coord_x;
	coord_y = pc.coord_y;
	damage = pc.damage;
	/*
		우리가 정의한 이 복사생성자는 표준적인 정의이다.
		즉 복사생성자는 어떤 클래스 T가 있다면, T(const T& a); 라고 정의된다.
		즉 다른 T의 객체 a를 상수 레퍼런스로 받는다는 이이기이댜.
		
		여기서 a가 cosnt이므로 우리는 복사 생성자 내부에서 
		a의 데이터를 변경할 수 없고 
		오직 새롭게 초기화 되는 인스턴스들에게 '복사'만 할 수 있다.

		!! 함수 내부에서 받은 인자의 값을 변화시키는 일이 없다면 꼭 cosnt를 붙이자!!
	*/
}
void Photon_Cannon::show_status() {
	std::cout << "Photon Cannon " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "<< std::endl;
	std::cout << " HP : " << hp << std::endl;
}

int main() {
	Photon_Cannon pc1(3, 3);
	Photon_Cannon pc2(pc1);
	Photon_Cannon pc3 = pc2;	// 이 코드 역시 복사 생성자가 호출된다. Photon_Cannon pc3(p2);와 동일하게 해석함
	/*
		1) Photon_Cannon pc3 = pc2;
		2) Photon_Cannon pc3;
		   pc3 = pc2;
		1), 2)는 엄연히 다른 문장이다.
		1)은 말 그대로 복사 생성자가 1번 호출된느 것이고
		2)는 그냥 생성자가 한번 호출되고 pc3=pc2;라는 명령이 실행되는 것이다.
		다시 한 번 강조하지만, 복사 생성자는 오직 '생성'시에 호출된다는 것을 명심하면 된다.

		그런데 사실 디폴트 생성자와 디폴트 소멸자처럼
		C++ 컴파일러는 이미 디폴트 복사 생성자를 지원해준다.
		위 코드에서 복사 생성자를 지워보고 실행해도 이전과 동일한 결과가 나타난다.

		디폴트 복사 생성자 T(const T& a); 의 경우 
		기존의 디폴트 생성자와 소멸자가 하는 일이 아무 것도 없었던 것과 달리 실제로 '복사'를 해준다.

		만일 위 Photon_Cannon의 디폴트 복사 생성자의 내용을 추정해보면
		Photon_Cannon::Photon_Cannon(const Photon_Cannon& pc) {
			hp = pc.hp;
			shield = pc.shield;
			coord_x = pc.coord_x;
			coord_y = pc.coord_y;
			damage = pc.damage;
		}
		와 같이 생겼을 것이다.

		대응되는 원소들을 말 그대로 1:1 복사해주게 된다. 
		 
	*/
	pc1.show_status();
	pc2.show_status();

	return 0;
}
