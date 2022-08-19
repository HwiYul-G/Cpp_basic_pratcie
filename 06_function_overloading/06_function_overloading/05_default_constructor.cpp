#include <iostream>

class Date {
    int year_;
    int month_;  // 1 ���� 12 ����.
    int day_;    // 1 ���� 31 ����.

public:
    void SetDate(int year, int month, int date);
    void AddDay(int inc);
    void AddMonth(int inc);
    void AddYear(int inc);

    // �ش� ���� �� �� ���� ���Ѵ�.
    int GetCurrentMonthTotalDays(int year, int month);

    void ShowDate();

    // default ������
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
        return 29;  // ����
    }
    else {
        return 28;
    }
}

void Date::AddDay(int inc) {
    while (true) {
        // ���� ���� �� �� ��
        int current_month_total_days = GetCurrentMonthTotalDays(year_, month_);

        // ���� �� �ȿ� ���´ٸ�;
        if (day_ + inc <= current_month_total_days) {
            day_ += inc;
            return;
        }
        else {
            // �����޷� �Ѿ�� �Ѵ�.
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
    std::cout << "������ " << year_ << " �� " << month_ << " �� " << day_
        << " �� �Դϴ� " << std::endl;
}

int main() {
    /*
        �� ó���� 03_Date.cpp  ���� SetDate �Լ��� �̿��ؼ� ��ü�� �ʱ�ȭ ���� ��
        �츮�� �����ڸ� ������� �ʾҴ�.

        �� ó���� ������ ���Ǹ� ���� ���� ä SetDate �Լ��� ���� �ʱ�ȭ�� �߾��� ���� �����غ���
        Date day; �� Date�� �ν��Ͻ� day�� �������.
        �� ��쿡�� �����ڰ� ȣ��ȴ�.
        �츮�� � �����ڵ� �ۼ����� �ʾ����� '����Ʈ ������(default constructor)'�� �����ȴ�.
        
        ����Ʈ �����ڴ� ���ڸ� �ϳ��� ������ �ʴ� �������ε�, 
        Ŭ�������� ����ڰ� � �����ڵ� ��������� �������� �ʾ��� ��� �����Ϸ��� �ڵ����� �߰����ִ� �������̴�.
        ���� ����Ʈ �����ڸ� �ٽ� ������ ���� �ִ�.
        
    */
    Date day(2011, 3, 1);
    day.ShowDate();

    day.AddYear(10);
    day.ShowDate();

    Date day2 = Date();
    Date day3;

    day2.ShowDate();    // �⺻ �������� 2012, 7, 12�� ����
    day3.ShowDate();    // �⺻ �������� 2012, 7, 12�� ����

    /*
        ���ڰ� �ִ� �����ڿ� ������ ��ó��
        Date day4(); �� ���� �ϸ� day4 ��ü�� ����Ʈ �����ڸ� �̿��ؼ� �ʱ�ȭ �ϴ� ���� �ƴ϶�
        ���� ���� Date�̰� ���ڰ� ���� �Լ� day4()�� �����ϰ� �� ������ �ν��Ѵ�.

        �̴� �Ͻ��� ǥ���̹Ƿ� ��ü�� ������ �� �ݵ�� �����ؾ� �Ѵ�.

        ����� ���ڰ� ���� �����ڸ� A a()ó�� �ϸ� �ȵȴ�!!!
        �׳� A a;�� �ؾ��Ѵ�.
    */
    Date day4(); 

    return 0;
}
/*
    [��������� ����Ʈ ������ ����ϱ�]
    C++ 11�������� ����Ʈ �����ڸ� ����ϰ� ���� ��� �׳� �����ڸ� �������� �ʴ� ����� �ִ�.
    ������ �� ������ �� �ڵ带 �д� ����� ���忡�� �����ڰ� ���� �ذ� ������ ���Ǹ� ���� ������
    ������ ����Ʈ �����ڸ� ����ϰ� �; �׷� ������ �� �� ������.

    �������� C++11���� ��������� ����Ʈ �����ڸ� ����� �� �ִ�.

    class Test{
        public:
        Test() = default; // ����Ʈ �����ڸ� �����ض�
    };
    ���� ���� ������ ���� �ٷ� �ڿ� = default�� �ٿ��ָ� 
    �ش� Ŭ������ ����Ʈ �����ڸ� �����϶�� �����Ϸ����� ��������� �˷��� �� �ִ�.
*/