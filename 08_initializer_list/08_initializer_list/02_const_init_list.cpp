#include <iostream>

class Marine {
	int hp;
	int coord_x, coord_y;
	bool is_dead;

	const int default_damage; // 기본 공격령
	/*
		마린의 공격력이 이상하게 변하는 것을 막기 위해서
		기본 공격력이라는 상수 멤버를 도입해서 딱 고정시키고 편하게 할 수 있게 해야한다.
		=> 상수이므로 선언 및 초기화를 동시에 해야하므로 '초기화 리스트'를 이용해야한다.
		=> 그리고 그 값이 초기화 되고 나선 바귀지 않는다.
	*/

public:
	Marine();
	Marine(int x, int y); 
	Marine(int x, int y, int default_damage);


	int attack();
	void be_attacked(int damage_earn);
	void move(int x, int y);

	void show_status();
};

Marine::Marine()
	: hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {}

Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {}
Marine::Marine(int x, int y, int default_damage)
	: coord_x(x),
	coord_y(y),
	hp(50),
	default_damage(default_damage),
	is_dead(false) {}
/*
	default_damage에 초기화 리스트로 생성자에 어떤 값을 전달한 인자를 ㅂ다음 다음에 상수를 넣어졌다
	따라서 이는 const int default_damage = 인자인 default_damage; 를 실행한 것과 동일하다.
	const 변수는 생성과 동시에 초기화가 되어야하는데 잘 수행되고 있다!
*/

void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}
int Marine::attack() { return default_damage; }
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

	std::cout << std::endl << "마린 1이 마린 2를 공격 ! " << std::endl;
	marine2.be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();

	// ============================

	Marine marine1(2, 3, 10);
	Marine marine2(3, 5, 10);

	marine1.show_status();
	marine2.show_status();

	std::cout << std::endl << "마린 1 이 마린 2 를 공격! " << std::endl;
	marine2.be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();

	return 0;
}