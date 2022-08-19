/*
    동일한 이름의 함수에 인자를 다르게 해서 함수 오버로딩을 하는 것처럼
    생성자 역시 가능하다.
    생성자 역시 함수 이기 때문에 함수의 오버로딩이 적용될 수 있다.

    즉 해당 클래스의 객체를 여러 가지 방식으로 생성할 수 있다.
*/
#include <iostream>

class Date {
    int year_;
    int month_;  // 1 부터 12 까지.
    int day_;    // 1 부터 31 까지.

public:
    void ShowDate();

    Date() {
        std::cout << "기본 생성자 호출!" << std::endl;
        year_ = 2012;
        month_ = 7;
        day_ = 12;
    }

    Date(int year, int month, int day) {
        std::cout << "인자 3 개인 생성자 호출!" << std::endl;
        year_ = year;
        month_ = month;
        day_ = day;
    }
};

void Date::ShowDate() {
    std::cout << "오늘은 " << year_ << " 년 " << month_ << " 월 " << day_
        << " 일 입니다 " << std::endl;
}
int main() {
    Date day = Date();
    Date day2(2012, 10, 31);

    day.ShowDate();
    day2.ShowDate();

    return 0;
}