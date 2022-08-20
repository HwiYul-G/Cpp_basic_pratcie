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
	/*
		this라는 키워드는 C++ 언어 차원에서 정의되어 있는 키워드이다.
		이는 객체 자신을 가리키는 포인터 역할을 한다.

		즉 이 멤버 함수를 호출하는 객체 자신을 가리킨다는 말이다.

		this->hp -= damage_earn;
		if (this->hp <= 0) this->is_dead = true;
		return *this;
		
		이 함수의 기존 내용을 위와 같이 this ->를 이용해서 사용해도 된다.
	*/
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;

	return *this;
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

	m1.show_status();
	m2.show_status();
	return 0;
}
/*
	실제로 모든 멤버 함수 내에서는 this 키워드가 정의되어 있으며
	클래스 안에 정의된 함수 중에서 this 키워드가 없는 함수는 
	당연히 객체가 아닌 클래스에 종속되어 있는 static 함수 뿐이다.

	그러면 레퍼런스 타입을 리턴한다는 말은 무엇일까?

	레퍼런스는 어떤 변수의 다른 별명(alias)이다.
	그런데 별명을 리턴한다는 것은 무슨 말일까?
	=> 06_return_reference.cpp
*/