/*
	Marine의 수를 알아내기 위한 코드를 짜보자.
	1) 어떠한 배열에 Marine을 보관하고 생성된 Marine의 수를 모두 Count
	2) 어떠한 변수를 만들어서 Marine 생성시 1을 추가하고 소멸시 1을 뺌

	1)의 경우 vector라는 자료형을 이용하면 쉽게 할 수 있다.
	하지만 이용하지 않는다면 크기가 자유롭게 변할 수 있는 배열을 따로 만들어야하는 문제점이 있다.

	2)의 경우 만일 어떤 함수 내에서 이런 변수를 정의했다면 다른 함수에서도 그 값을 이용하기 위해
		계속 인자로 전달해줘야하는 번거로움이 있다.

	global 변수로 만드는 방법도 있지만 global variable의 경우 프로젝트의 크기가 커질 수록
	프로그래머의 실수로 서로 겹쳐서 오류가 날 가능성이 크기 때문에 반드시 필요한 경우가 아니면 사용하지 않는다.
	(실제로 필요한 경우 외엔 꼭! 사용하지 말자!)

	이러한 문제를 간단히 해결할 수 있는 방법으로
	전역변수 같지만 클래스 하나에만 종속된 변수인 static 멤버 변수를 이용할 수 있다.

	C에서도 어떤 함수의 static 변수가 지역변수들처럼 함수가 종료될 때 소멸된느 것이 아니라
	프로그램이 종료될 때 소멸되는 것처럼,
	어떤 class의 static member variable의 경우 멤버 변수들 처럼 객체가 소멸될 때 소멸되는 것이 아니라
	프로그램이 소멸될 때 소멸된다.

	이 static 멤버 변수의 경우 클래스의 모든 객체들이 '공유'하는 변수로써
	각 객체 별로 따로 존재하는 멤버변수들과 달리 모든 객체들이 '하나의' static 멤버 변수를 사용하게 된다.
*/
#include <iostream>

class Marine {
	/*
		marine의 수를 세기 위한 static 변수
		global and static var 은 정의와 동시에 값이 자동으로 0으로 초기화 된다.
		따라서 굳이 초기화 하지 않아도 된다.
		하지만 초기화 하고 싶다면
		class 외부에서 int Marine::total_marine_num = 0; 이라고 작성해주면 된다.

		class 내부에서 static int total_marine_num = 0; 자체로 초기화할 순 없다.
		멤버변수들을 이러한 방식으로 초기화 시킬 수 없는 것처럼 static 변수 역시 불가능하다.

		저것이 가능한 경우(class 내부에서 선언과 동시에 초기화)는
		유일하게 const static 변수인 경우이다.
		const static int x = 0; 이런 것은 가능하다.

	*/
	static int total_marine_num;

	int hp;
	int coord_x, coord_y;
	int is_dead;

	const int default_damage;

public:
	Marine();
	Marine(int x, int y);
	Marine(int x, int y, int default_damage);

	int attack();						// 데메지 리턴
	void be_attacked(int damage_earn);	// 입는 데미지
	void move(int x, int y);			// 새로운 위치

	void show_status();					// 상태 보여줌ㄴ

	~Marine() { total_marine_num--; }
};

Marine::Marine() :hp(50),coord_x(0),coord_y(0),default_damage(5),is_dead(false) {
	total_marine_num++;
}
Marine::Marine(int x, int y) :hp(50), coord_x(x), coord_y(y), default_damage(5), is_dead(false) {
	total_marine_num++;
}
Marine::Marine(int x, int y, int default_damage): hp(50), coord_x(x), coord_y(y), default_damage(default_damage), is_dead(false) {
	total_marine_num++;
}

int Marine::attack() { return default_damage; }
void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0)is_dead = true;
}
void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}
void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "<< std::endl;
	std::cout << " HP : " << hp << std::endl;
	std::cout << " 현재 총 마린 수 : " << total_marine_num << std::endl;
}

void create_marine() {
	Marine marine3(10, 10, 4);
	marine3.show_status();
}

int main() {
	Marine m1(2, 3, 5);
	m1.show_status();

	Marine m2(3, 5, 10);
	m2.show_status();

	create_marine();

	std::cout << std::endl << "마린1이 마린2를 공격!" << std::endl;
	m2.be_attacked(m1.attack());

	m1.show_status();
	m2.show_status();
	return 0;
}