/*
	생성자의 초기화 리스트(initializer list)

*/
#include <iostream>

class Marine {
	int hp;
	int coord_x, coord_y;
	int damage;
	bool is_dead;
public:
	Marine();
	Marine(int x, int y);

	int attack();
	void be_attacked(int damage_earn);
	void move(int x, int y);

	void show_status();
};

// initialzier_list!!
Marine::Marine() : hp(50), coord_x(0), coord_y(0), damage(5), is_dead(false) {}
Marine::Marine(int x, int y) : coord_x(x), coord_y(y), hp(50), damage(5), is_dead(false) {}

int Marine::attack() { return damage; }
void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
}
void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
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
}
/*
	Marine::Marine() : hp(50), coord_x(0), coord_y(0), damage(5), is_dead(false) {}
	Marine::Marine(int x, int y) : coord_x(x), coord_y(y), hp(50), damage(5), is_dead(false) {}

	놀랍게도 함수 본체에는 기존과 달리 아무것도 없다.
	오직 위에 추가된 이상한 것들이 기존 생성자가 했던 일과 동일한 작업을 하고 있을 뿐이다.

	생성자 이름 옆에 있는 저것들이 '초기화 리스트(initializer list)'라고 부르고
	생성자 호출과 동시에 멤버 변수들을 초기화해주게 된다.

	멤버 초기화 리스트의 일반적인 꼴은 아래와 같다.
	(생성자 이름) : var1(arg1), var2(arg2) {}
	여기서 var는 클래스의 멤버 변수이고 arg는 그 멤버변수를 무엇으로 초기화할지를 지칭하는 역할이다.
	흥미로운 이름은 var1과 arg1의 이름이 동일해도 된다.

	coord_x(coord_x)에서 바깥쪽 coord_x는 무조건 멤버 변수를 지칭하게 된다.
	괄호 안의 coord_x는 원칙상 Marine이 인자로 받은 coord_x를 우선적으로 지칭하는 것이기 때문이다.


	=============================================================================================
	그렇다면 Marine::Marine(){hp = 50; .... }이랑 Marine::Marine():hp(50), .. {}의 차이는 무엇일까?

	초기화 리스트를 사용하는 경우 생성과 초기화를 동시에 한다.
	반면에 초기화 리스트를 사용하지 않으면 생성을 먼저 하고 그 다음에 대입을 수행하게 된다.
	쉽게 말해 초기화 리스트를 사용하는 것은 int a = 10; 이라 하는 것과 같고 
	그냥 예전 버전의 생성자를 사용하는 것은 int a; a = 10; 이라 하는 것과 동일하다.

	만약에 int가 대신에 클래스 였다면, 전자의 경우 복사 생성자가 호출되는데, 
	후자의 경우 디폴트 생성자가 호출된 뒤 대입이 수행된다.

	후자가 하는 작업이 많고 따라서 초기화 리스트를 사용하는 것이 조금 더 효율적인 작업이다.
	그 뿐만 아니라, 우리 경험상 반드시 '생성과 동시에 초기화 되어야 하는 것들'이 몇 가지 있다.
	대표적으로 래퍼런스와 상수가 그렇다.

	상수와 레퍼런스는 생성과 동시에 초기화 되지 않으면 컴파일 오류가 난다.
	따라서 만약에 클래스 내부에 레퍼런스 변수나 상수를 넣고 싶다면
	이들을 생성자에서 무조건 초기화 리스트를 사용해 초기화 시켜야 한다.
*/