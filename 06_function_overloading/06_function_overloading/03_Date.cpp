#include <iostream>

class Date {
	int year_;
	int month_;
	int day_;

public:
	void SetDate(int year, int month, int day);
	void AddDay(int inc);
	void AddMonth(int inc);
	void AddYear(int inc);

	int GetCurrentMonthTotaldays(int year, int month);

	void ShowDate();
};

void Date::SetDate(int year, int month, int day) {
	year_ = year;
	month_ = month;
	day_ = day;
}

int Date::GetCurrentMonthTotaldays(int year, int month) {
	static int month_day[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month != 2) {
		return month_day[month - 1];
	}
	else if (year % 4 == 0 && year % 100 != 0) {
		return 29; // 윤년
	}
	else return 28;
}

void Date::AddDay(int inc) {
	while (1) {
		// 현재 달의 총 일 수
		int current_month_total_days = GetCurrentMonthTotaldays(year_, month_);

		// 같은 달 안에 들어온다면
		if (day_ + inc <= current_month_total_days) {
			day_ += inc;
			return;
		}
		else {
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
	Date day;
	day.SetDate(2011, 3, 1);
	day.ShowDate();

	day.AddDay(30);
	day.ShowDate();

	day.AddDay(2000);
	day.ShowDate();

	day.SetDate(2012, 1, 31);  // 윤년
	day.AddDay(29);
	day.ShowDate();

	day.SetDate(2012, 8, 4);
	day.AddDay(2500);
	day.ShowDate();
	return 0;
}
/*
	class 내부에는 함수의 '정의'만 있고 함수의 정의는 
	class 외부에 "T 클래스명::함수명(인자){}" 와 같은 방식을 통해 작성된다.

	만약 클래스명::을 해주지 않고 void ShowDate()와 같은 식으로 작성했다면
	클래스의 멤버 함수가 아니라 그냥 일반적인 함수가 된다.

	보통 간단한 함수를 제외하면 대부분의 함수들은 클래스 외부에서 정의하게 된다.
	왜냐하면 클래스 내부에 써서 클래스의 크기가 길어지면 보기 좋지 않기 때문이다.

	main 함수를 보면 Date의 인스턴스를 생성해서 SetDate로 초기화 하고 ShowDate로 내용을 보여주고 한다.
	여기서 가장 중요한 부분은 SetDate이다. 
	만일 SetDate로 초기화를 하지 않으면 초기화 되지 않은 상태로 이후의 함수들이 진행되어 쓰레기 값이 출력된다.

	그런데 실수로 SetDate 함수를 작성하지 않는 경우가 있다.
	그래서 C++에서 이를 언어 차원에서 도와주는 장치가 있는데 그것이 바로 생성자(constructor)이다.
	= > 04_constructor.cpp
*/