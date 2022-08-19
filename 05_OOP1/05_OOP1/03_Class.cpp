/*
    그렇다면 객체는 C++ 상에서 어떻게 만들어 낼까 ?
    이를 위해 C++에선 객체를 만들 수 있는 장치를 준비했다. 쉽게 말하면 객체의 설계도이다.
    이것이 바로 '클래스(class)' 이다.

    객체는 앞서 말했던 것처럼 하나의 원이 있는데 그 내부엔 변수들이 선언되어 있고
    외부 둘레쪽으론 Methods가 있는 것이다.

    이러한 객체를 만들어내는 설계도(클래스)는 그 Object의 내용이 들어있지 않은 빈 껍질이라 생각할 수 잇다.
    그리고 이 빈껍질인 객체 설계도를 통해 실제 객체를 만들게 된다.
    C++에선 이와 같이 클래스(객체 설계도)를 이용해서 만들어진 객체를 인스턴스라고 부른다.
    그래서 앞서 객체의 변수와 메소드를 인스턴스 변수와 인스턴스 메소드라고 한 이유이다.
*/
#include <iostream>
class Animal {
// private되어 있는 변수들 -> 멤버 변수 (실체화=객체화 되기 전 클래스 상의 변수)
// 인스턴스로 실체화 되고 나선 인슽너스 변수, 인스턴수 함수로 부른다.
// 즉 멤버 변수와 멤버 함수는 설계도상에 있는 것일 분 실제로 존재하진 않는다.
 private:   // 접근지시자가 private이다. 
 /*
    private 키워드는 아래에 쓰여진 것들은 모두 객체 내에서 보호되고 있다는 뜻이다.
    즉 객체 안에서만 접근할 수 있고 외부에선 접근할 수 없다.
 */
  int food;
  int weight;
 public:
 // public되어 있는 함수들 -> 멤버 함수(실체화=객체화 되기 전 클래스 상의 함수들)
  void set_animal(int _food, int _weight) {
    food = _food;
    weight = _weight;
  }
  void increase_food(int inc) {
    food += inc;
    weight += (inc / 3);
  }
  void view_stat() {
    std::cout << "이 동물의 food   : " << food << std::endl;
    std::cout << "이 동물의 weight : " << weight << std::endl;
  }
};  // 세미콜론 잊지 말자!

int main() {
    // Animal 클래스의 instance 생성
    // 구조체에서 구조체 변수를 생성할 때와 달리 struct를 명시하지 않아도 된다.
    Animal animal;
    animal.set_animal(100, 50);
    animal.increase_food(30);

    animal.view_stat();
    return 0;
}