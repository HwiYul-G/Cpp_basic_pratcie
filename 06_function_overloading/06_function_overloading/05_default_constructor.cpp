#include <iostream>

class Date {
    int year_;
    int month_;  // 1 부터 12 까지.
    int day_;    // 1 부터 31 까지.

public:
    void SetDate(int year, int month, int date);
    void AddDay(int inc);
    void AddMonth(int inc);
    void AddYear(int inc);

    // 해당 월의 총 일 수를 구한다.
    int GetCurrentMonthTotalDays(int year, int month);

    void ShowDate();

    // default 생성자
    Date() {
        year_ = 2012;
        month_ = 7;
        day_ = 12;
    }

    Date(int year, int month, int day) {
        year_ = year;
        month_ = month;
        day_ = day;
    }
};

void Date::SetDate(int year, int month, int day) {
    year_ = year;
    month_ = month;
    day_ = day;
}

int Date::GetCurrentMonthTotalDays(int year, int month) {
    static int month_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month != 2) {
        return month_day[month - 1];
    }
    else if (year % 4 == 0 && year % 100 != 0) {
        return 29;  // 윤년
    }
    else {
        return 28;
    }
}

void Date::AddDay(int inc) {
    while (true) {
        // 현재 달의 총 일 수
        int current_month_total_days = GetCurrentMonthTotalDays(year_, month_);

        // 같은 달 안에 들어온다면;
        if (day_ + inc <= current_month_total_days) {
            day_ += inc;
            return;
        }
        else {
            // 다음달로 넘어가야 한다.
            inc -= (current_month_total_days - day_ + 1);
            day_ = 1;
            AddMonth(1);
        }
    }
}

void Date::AddMonth(int inc) {
    AddYear((inc + month_ - 1) / 12);
    month_ = month_ + inc % 12;
    month_ = (month_ == 12 ? 12 : month_ % 12);
}

void Date::AddYear(int inc) { year_ += inc; }

void Date::ShowDate() {
    std::cout << "오늘은 " << year_ << " 년 " << month_ << " 월 " << day_
        << " 일 입니다 " << std::endl;
}

int main() {
    /*
        맨 처음에 03_Date.cpp  에서 SetDate 함수를 이용해서 객체를 초기화 했을 때
        우리는 생성자를 명시하지 않았다.

        즉 처음에 생성자 정의를 하지 않은 채 SetDate 함수를 통해 초기화를 했었을 때를 생각해보면
        Date day; 로 Date의 인스턴스 day를 만들었다.
        이 경우에도 생성자가 호출된다.
        우리가 어떤 생성자도 작성하지 않았지만 '디폴트 생성자(default constructor)'가 생성된다.
        
        디폴트 생성자는 인자를 하나도 가지지 않는 생성자인데, 
        클래스에서 사용자가 어떤 생성자도 명시적으로 정의하지 않았을 경우 컴파일러가 자동으로 추가해주는 생성자이다.
        물론 디폴트 생성자를 다시 정의할 수도 있다.
        
    */
    Date day(2011, 3, 1);
    day.ShowDate();

    day.AddYear(10);
    day.ShowDate();

    Date day2 = Date();
    Date day3;

    day2.ShowDate();    // 기본 설정값인 2012, 7, 12가 나옴
    day3.ShowDate();    // 기본 설정값인 2012, 7, 12가 나옴

    /*
        인자가 있는 생성자에 적용한 것처럼
        Date day4(); 와 같이 하면 day4 객체를 디폴트 생성자를 이용해서 초기화 하는 것이 아니라
        리턴 값이 Date이고 인자가 없는 함수 day4()를 정의하게 된 것으로 인식한다.

        이는 암시적 표현이므로 객체를 선언할 때 반드시 주의해야 한다.

        절대로 인자가 없는 생성자를 A a()처럼 하면 안된다!!!
        그냥 A a;로 해야한다.
    */
    Date day4(); 

    return 0;
}
/*
    [명시적으로 디폴트 생성자 사용하기]
    C++ 11이전에는 디폴트 생성자를 사용하고 싶을 경우 그냥 생성자를 정의하지 않는 방법만 있다.
    하지만 이 때문에 그 코드를 읽는 사용자 입장에서 개발자가 깜빡 잊고 생성자 정의를 안한 것인지
    정말로 디폴트 생성자를 사용하고 싶어서 그런 것인지 알 수 없었다.

    다행히도 C++11부터 명시적으로 디폴트 생성자를 명시할 수 있다.

    class Test{
        public:
        Test() = default; // 디폴트 생성자를 정의해라
    };
    위와 같이 생성자 선언 바로 뒤에 = default를 붙여주면 
    해당 클래스으 디폴트 생성자를 정의하라고 컴파일러에게 명시적으로 알려줄 수 있다.
*/