#include <iostream>

int change_val(int& p) {
	p = 3;

	return 0;
}
int main() {
	int number = 5;

	std::cout << number << std::endl;
	change_val(number);
	std::cout << number << std::endl;
}
/*
	pointer�� �̿��ؼ� ������� change_val �Լ��� �����ڸ� �̿��ؼ� �������.
	�׷��� �Ʊ� int& p ó�� ���� �ϴ� ���� �Ұ����ϴٰ� �ߴ�.
	������ function�� argument�� p�� ���ǵǴ� ������ change_val(number);�� ȣ���ϴ� �����̹Ƿ�
	int& p = number;�� ����ȴٰ� �����ϸ� �ȴ�.

	change_val(number);�� ������ 
	p���� "�ʴ� ������ number�� ���ο� �����̾�"��� �˷��ְ� �ȴ�.

	���⼭ �߿��� ���� �Լ��� ȣ���� �� �����Ͱ� ������ ���� �޸� &�� �տ� ���� �ʿ䰡 ���ٴ� ���̴�.

	�� �� change_val �Լ� �ȿ��� p = 3;�̶�� ���� main �Լ��� number�� number = 3;�� �� �Ͱ� ������ ������ �Ѵ�.
	�׷��� �����͸� ���ڷ� ������ ������ ������� ����ϰ� ����� �� �ִ�.
*/