#include <iostream>

int change_val(int* p) {
	*p = 3;
	return 0;
}

int main() {
	int number = 5;
	std::cout << number << std::endl;
	change_val(&number);
	/*
		change_val �Լ��� ���� p�� number�� �ּҰ��� �����ؼ�
		*p�� ���� number�� �����Ͽ� number�� ���� 3���� �����ߴ�.
		
		C���� ��� ������ ����Ű�� ���� �� �ݵ�� �����и� ����ؾ߸� �ߴ�.
		�׷��� C++���� �ٸ� ������ ����� ����Ű�� ������� �� �ٸ� ����� �����Ѵ�.
		�̸� �ٷ� ������(���۷���, reference)��� �θ���.
		=> 02_reference.cpp

	*/
	std::cout << number << std::endl;
	return 0;
}