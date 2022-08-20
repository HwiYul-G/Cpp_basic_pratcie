// 상수 멤버 함수 (const function)
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

    // ================== const 함수!! ====================
    int attack() const;                    // 데미지를 리턴한다.
    Marine& be_attacked(int damage_earn);  // 입는 데미지
    void move(int x, int y);               // 새로운 위치

    void show_status();  // 상태를 보여준다.
    static void show_total_marine();
    ~Marine() { total_marine_num--; }
};
int Marine::total_marine_num = 0;
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
int Marine::attack() const { 
    return default_damage; 
    /*
        int attack() const; 로 정의하고
        int Marine::attack() const {return default_damage; }
        이렇게 하면 attack 함수는 '상수 멤버 함수'로 정의된 것이다.

        우리는 상수 함수로 이 함술르 정의함으로써, 이 함수는 다른 변수의 값을 바꾸지 않는 함수라고
        프로그래머에게 명시 싴틸 수 있다.

        당연하게도 상수 함수 내에서는 객체들의 '읽기'만 수행되어,
        상수 함수 내에서 호출할 수 있는 함수로는 다른 상수 함수밖에 없다.
    */
}
Marine& Marine::be_attacked(int damage_earn) {
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
    Marine marine1(2, 3, 5);
    marine1.show_status();

    Marine marine2(3, 5, 10);
    marine2.show_status();

    std::cout << std::endl << "마린 1 이 마린 2 를 두 번 공격! " << std::endl;
    marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());

    marine1.show_status();
    marine2.show_status();
}
/*
    많은 경우에 클래스를 설계할 때 멤버 변수들은 모두 private에 넣고
    이 변수들의 값에 접근하는 방법으로 get_x 함수 처럼 함수를 public 에 넣어 
    이 함수를 이용해 값을 리턴받는 형식을 많이 사용한다.

    이렇게 하면 멤버 변수들을 private에 넣음으로써 함수로 변수에 접근하는 것을 막고
    또 그 값은 자유롭게 구할 수 있게 된다.
*/