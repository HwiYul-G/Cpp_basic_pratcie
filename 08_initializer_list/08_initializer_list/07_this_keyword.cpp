// 자기 자신을 가리키는 포인터 this
#include <iostream>

class Marine {
	static int total_marine_num; // 자동으로 0으로 초기화
	const static int i = 0; // const static은 class 내에서 선언과 동시에 초기화 가능

	int hp;
	int coord_x, coord_y;
	bool is_dead;

	const int default_damage; // 기본 공격력

public:
	Marine();
	Marine(int x, int y);
	Marine(int x, int y, int default_damage);

	int attack();
	Marine& be_attacked(int damage_earn);
	void move(int x, int y);

	void show_status();
	static void show_total_marine();
	~Marine() { total_marine_num--; }
};

int Marine::total_marine_num = 0; // 자동으로 0으로 초기화 되지만 명세
void Marine::show_total_marine() {
	std::cout << "전체 마린 수 : " << total_marine_num << std::endl;
}

Marine::Marine()
	: hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
	total_marine_num++;
}

Marine::Marine(int x, int y)
	: coord_x(x),
	coord_y(y),
	hp(50),

	default_damage(5),
	is_dead(false) {
	total_marine_num++;
}

Marine::Marine(int x, int y, int default_damage)
	: coord_x(x),
	coord_y(y),
	hp(50),
	default_damage(default_damage),
	is_dead(false) {
	total_marine_num++;
}

void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}
int Marine::attack() { return default_damage; }

Marine& Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;

	return *this;
	/*
		이 함수는 Marine& 타입을 리턴하게 된다.
		위 경우 *this를 리턴하게 된다.
		this는 지금 이 함수를 호출한 객체를 가리키는 포인터이다.
		따라서 *this는 그 객체 자신이다.

		main 함수로 가서
		marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());
		을 보자.
	*/
}
void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
		<< std::endl;
	std::cout << " HP : " << hp << std::endl;
	std::cout << " 현재 총 마린 수 : " << total_marine_num << std::endl;
}

int main() {
	Marine m1(2, 3, 5);
	m1.show_status();

	Marine m2(3, 5, 10);
	m2.show_status();

	std::cout << std::endl << "마린1이 마린 2를 2번 공격" << std::endl;
	m2.be_attacked(m1.attack()).be_attacked(m1.attack());
	/*
		be_attacked 함수의 리턴타입이 Marine&이다.
		m2.be_attacked(m1.attack())가 먼저 실행되고 리턴되는 타입이 다시 m2이다.
		그래서 m2.be_attacked(m1.attack())이 실행된다.

		만일 be_attacked 함수의 리턴 타입이 Marine&이 아니라 그냥 Marine이라고 하자.
		즉 만일 be_attacked 함수가 아래와 같다고 생각해보자.

		Marine Marine::be_attacked(int damage_earn) {
			this->hp -= damage_earn;
			if (this->hp <= 0) this->is_dead = true;
			return *this;
		}

		이렇게 된 상태로 
		m2.be_attacked(m1.attack()).be_attacked(m1.attack());
		이 되었다고 생각하자.
		이것이 실행되면 m2는 실제로 두 번 공격이 아닌 1번 공격으로 감소한 hp만 보인다.
		이는 리턴타입이 Marine이므로 임시객체 Marine을 생성해서 *this의 내용으로 복사가 된다.
		즉 Marine의 복사 생성자가 호출된다.
		이 임시 객체에 대한 be_attacked 함수가 호출된다.

		따라서 두 번째 be_attacked는 marine2가 아니라 엉뚱한 임시 객체에 대한 호출되는 것이라
		m2는 m1의 공격을 1번만 받게 된다.
	*/

	m1.show_status();
	m2.show_status();
	return 0;
}