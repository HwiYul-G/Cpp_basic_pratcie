#include <iostream>

int main() {
	int& ref = 4;	// error C2440: 'initializing' : cannot convert from 'int' to 'int &'
	/*
		��� �� ��ü�� literal �̴�. (literal : �ҽ� �ڵ� �󿡼� ������ ���� ������ ��)
		�׷��� ���� int& ref = 4;�� ���۷����� �����Ѵٸ�
		ref = 5;�� ���ͷ��� ���� �ٲٴ� ���� �ȵǴ� ������ �����ϰ� �ȴ�.
		(int& ref = 4;�� ref�� 4��� literal�� ������ �ǰ� ref = 5;�� 4 = 5;�� �ȴ�.)
		���� C++ ���� �� ��� ���ͷ��� �Ϲ����� ���۷����� �����ϴ� ���� �Ұ����ϰ� �Ǿ� �ִ�.

		��ſ�
		const int& ref = 4;�� '��� ������'�� �����Ѵٸ� ���з��� ������ �� �ִ�.
		int a = ref;�� a = 4;�� ����� �����ϰ� ó�� �ȴ�.
	*/
	const int& ref2 = 4; // 4��� literal�� ������ ref�ε� cosnt�� �������̴�. (�� ref2 = 5; ���� ������ �� �� ����.)
	int a = ref; // int a = 4;�� �����ϴ�.

	std::cout << ref << std::endl;
}