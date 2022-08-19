#include <iostream>
#include <string.h>

class Marine {
	int hp;
	int coord_x, coord_y;
	int damage;
	bool is_dead;
	char* name;

public:
	Marine();
	Marine(int x, int y, const char* marine_name);
	Marine(int x, int y);
	~Marine();	// 소멸자!

	int attack();
	void be_attacked(int damage_earn);
	void move(int x, int y);
	void show_status();
};

Marine::Marine() {
	hp = 50;
	coord_x = coord_y = 0;
	damage = 5;
	is_dead = false;
	name = NULL;
}
Marine::Marine(int x, int y, const char* marine_name) {
	name = new char[strlen(marine_name) + 1]; // Null값 추가용 + 1
	strcpy(name, marine_name);
	/*
		이 부분에서 문제가 있다.
		name을 분명히 동적(new)를 통해 생성해서 문자열을 복사했다.
		그럼 이 동적으로 할당된 char 배열에 대한 delete는 언제 이루어지는가?

		안타깝게도 delete를 우리가 명확하게 지정하지 않는 한 자동으로 delete 되지 않는다.
		즉 동적 할당했던 name은 영원히 메모리 공간 속에서 둥둥 떠다니는 말이다.
	
		사실 몇 바이트 정도 밖에 되지 않을 것이지만 위와 같은 name들이 엄청나게 많아지게 되면
		메모리 누수(Memory leak)이라는 문제점이 생긴다.
		- 종종 몇 프로그램들이 비정상적으로 많은 메모리를 점유함 - 
	*/

	hp = 50;
	coord_x = x;
	coord_y = y;
	damage = 5;
	is_dead = false;
}
Marine::Marine(int x, int y) {
	coord_x = x;
	coord_y = y;
	hp = 50;
	damage = 5;
	is_dead = false;
	name = NULL;
}
void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}
int Marine::attack() { return damage; }
void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
}
void Marine::show_status() {
	std::cout << " *** Marine : " << name << " ***" << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
		<< std::endl;
	std::cout << " HP : " << hp << std::endl;
}
Marine::~Marine() {
	/*
		소멸자는 인자를 아무것도 가지지 않는다. 소멸하는 객체에 인자를 넘겨서 무슨 소용인가?
		즉 소멸자는 오버로딩도 되지 않는다.
	*/
	std::cout << name << " 의 소멸자 호출 ! " << std::endl;
	if (name != NULL) {
		delete[] name;	// name을 char 배열로 동적할당 했기에 delete 여깃 delete[]로 해야한다.
		// 이렇게 함으로 아까 leak이 날뻔한 name들에 문제가 없다.
	}
}

int main() {
	Marine* marines[100];

	marines[0] = new Marine(2, 3, "Marine 2");
	marines[1] = new Marine(1, 5, "Marine 1");

	marines[0]->show_status();
	marines[1]->show_status();

	std::cout << std::endl << "마린 1 이 마린 2 를 공격! " << std::endl;

	marines[0]->be_attacked(marines[1]->attack());

	marines[0]->show_status();
	marines[1]->show_status();

	delete marines[0];
	delete marines[1];
	/*
		만일 main 함수의 끝인 이곳에서 Marine이 delete될 때
		즉 우리가 생성했던 객체가 소멸될 때 자동으로 호출되는 함수
		- 마치 객체가 생성될 때 자동으로 호출되었던 생성자처럼 소멸될 때 자동으로 호출되는 함수가 있다면 어떨까?
		C++에선 이 기능을 지원하고 있다. 이것이 바로 소멸자(destructor)이다.

	*/
	return 0;
}