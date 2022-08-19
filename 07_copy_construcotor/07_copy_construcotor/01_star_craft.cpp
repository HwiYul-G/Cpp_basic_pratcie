/*
	생성자를 통해 이전에 C 프로그래밍 시 변수 초기화를 하지 않아서 생겼던 수 많은 오류를 효과적으로 없앨 수 있었다.

	뿐만 아니라 C++에서 새로 도입된 함수 오버로딩 덕분에 함수 이름을 일일이 따로 지정하지 않더라도
	성공적으로 인자들의 타입에 딸 원하는 함수들만 호출할 수 있게 되었다.

	실제로 C언어 였다면 인자의 타입에 따라서 함수의 이름을 외워야 했지만, C++에선 그럴 필요가 전혀 없다.
*/

#include <iostream>

class Marine {
	int hp;
	int coord_x, coord_y;
	int damage;
	bool is_dead;
public:
	Marine() = default; // 기본 생성자
	Marine(int x, int y);	// x, y 좌표에 마린 생성

	int attack(); // 데미지를 리턴
	void be_attacked(int damage_earn); // 입는 데미지
	void move(int x, int y); // 새로운 위치

	void show_status(); // 상태를 보여준다.
};

Marine::Marine() {
	hp = 50;
	coord_x = coord_y = 0;
	damage = 5;
	is_dead = false;
}

Marine::Marine(int x, int y) {
	coord_x = x;
	coord_y = y;
	hp = 50;
	damage = 5;
	is_dead = false;
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
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
		<< std::endl;
	std::cout << " HP : " << hp << std::endl;
}

int main() {
	Marine marine1(2, 3);
	Marine marine2(3, 5);

	marine1.show_status();
	marine2.show_status();

	std::cout << std::endl << "마린 1이 마린 2를 공격! " << std::endl;
	marine2.be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();
	/*
		마린이 2마리가 아니라 엄청나게 많아진다면
		-> 배열로 관리!
	*/
	Marine* marines[100];

	/*
		new delete에 대해 배울 때 malloc과의 차이점이 있다고 햇다.
		new와 malloc 모두 동적으로 할당하지만, new의 경우 
		객체를 동적으로 생성하면서 동시에 자동으로 생성자도 호출해준다는 점이 다르다.
	*/
	marines[0] = new Marine(2, 3);
	marines[1] = new Marine(3, 5);

	/*
		Marine들의 '포인터'를 가리키는 배열이기 때문에 메소드를 호출할 때 ->을 사용해야한다.
	*/
	marines[0]->show_status();
	marines[1]->show_status();

	std::cout << std::endl << "마린 1 이 마린 2 를 공격! " << std::endl;

	marines[0]->be_attacked(marines[1]->attack());

	marines[0]->show_status();
	marines[1]->show_status();

	// 동적 할당 후엔 항상 해제를 해줘야한다.
	delete marines[0];
	delete marines[1];



	return 0;
}