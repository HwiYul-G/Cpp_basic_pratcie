/*
	class 내부에 static variable만 가능한 게 아니라
	static function도 가능하다.

	static 변수가 어떤 객체에 종속되는 것이 아니라,
	그냥 클래스 자체에 딱 1개 존재하는 것처럼 static 함수 역시 어떤 특정 객체에 종속되는 것이 아니라
	클래스 전체에 딱 1개 존재하는 함수이다.

	즉 static이 아닌 멤버 변수, 멤버 함수들의 경우 객체를 만들어야만 각 멤버 함수를 호출할 수 있지만
	static 함수의 경우 객체가 없어도 그냥 클래스 자체에서 호출할 수 있게 된다.
*/
// static 함수
#include <iostream>

class Marine {
    static int total_marine_num;
    const static int i = 0;

    int hp;                // 마린 체력
    int coord_x, coord_y;  // 마린 위치
    bool is_dead;

    const int default_damage;  // 기본 공격력

public:
    Marine();              // 기본 생성자
    Marine(int x, int y);  // x, y 좌표에 마린 생성
    Marine(int x, int y, int default_damage);

    int attack();                       // 데미지를 리턴한다.
    void be_attacked(int damage_earn);  // 입는 데미지
    void move(int x, int y);            // 새로운 위치

    void show_status();  // 상태를 보여준다.
    static void show_total_marine();            // class 내부의 static 함수
    ~Marine() { total_marine_num--; }
};
int Marine::total_marine_num = 0;   // class 내부의 static 변수 초기화
void Marine::show_total_marine() {
    std::cout << "전체 마린 수 : " << total_marine_num << std::endl;
}   // class 내부의 static 함수
Marine::Marine()
    : hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
    total_marine_num++;
}

Marine::Marine(int x, int y)
    : coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {
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
void Marine::be_attacked(int damage_earn) {
    hp -= damage_earn;
    if (hp <= 0) is_dead = true;
}
void Marine::show_status() {
    std::cout << " *** Marine *** " << std::endl;
    std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
        << std::endl;
    std::cout << " HP : " << hp << std::endl;
    std::cout << " 현재 총 마린 수 : " << total_marine_num << std::endl;
}

void create_marine() {
    Marine marine3(10, 10, 4);
    Marine::show_total_marine();
}
int main() {
    Marine marine1(2, 3, 5);
    /* 
        static 함수는 어떤 객체에 종속되는 것이 아니라
        클래스 자체에 종속되는 것이다.
        따라서 호출할 때 객체.멤버함수 가 아니라 클래스::static함수 형식으로 호출 가능하다.

        왜냐하면 어떤 객체도 이 함수를 소유하고 있지 않기 때문이다.

        그래서 static 함수 내에서는 클래스의 static 변수만을 이용할 수 있다.
        만일 static 함수 내에서 static이 아닌 일반 클래스 멤버 변ㅁ수들을 사용한다면
        그 멤버 변수들의 누구의(어떤 객체의) 멤버변수인지 알 수 없다.

    */
    Marine::show_total_marine();

    Marine marine2(3, 5, 10);
    Marine::show_total_marine();

    create_marine();

    std::cout << std::endl << "마린 1 이 마린 2 를 공격! " << std::endl;
    marine2.be_attacked(marine1.attack());

    marine1.show_status();
    marine2.show_status();
}