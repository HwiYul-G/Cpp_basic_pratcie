#include <iostream>

int main() {
	int lucky_number = 3;
	std::cout << "�� ��� ���� ���� ������~" << std::endl;

	int user_input;
	while (true)
	{
		std::cout << "�Է� : ";
		std::cin >> user_input;
		if (lucky_number == user_input) {
			std::cout << "���߼̽��ϴ�~~" << std::endl;
			/*
				cout�� �տ��� ��� ��ó�� <<�� �̿��� ��½�Ų��.

				�׸��� cin�� ����ڷκ��� �Է��� �޾Ƽ� >>�� �̿��� user_input�� �ִ´�.
				cin�� cout�� ���������� std�� ���ǵǾ� �ֱ� ������ std::cin�� ���� ����ؾ� �Ѵ�.

				c���� scanf�� �Է½� &�� �ٿ� �ּҰ��� �˷��־��µ�
				C++���� ���ϰ� &�����ڸ� ���� �ʿ䰡 ����.
				������ scanf������ int ���·� �Է��� ������ �ƴϸ� char ���ڿ� ���� %d�� %c ���� �����ߴµ�
				���⼱ ������ ���� cin�� �˾Ƽ� ó�����־ �ſ� ���ϴ�.

				���� cin�̳� cout�� ��������,
				shift�����ڷ� ���Ǿ��� <<�̳� >>�� ���� ���� ���� �ʴ´�.
				�켱 ����ϰ� ���߿� �� ���¸� �����鼭 �˰� �� ���̴�.!
			*/
			break;
		}
		else {
			std::cout << "�ٽ� �����غ�����~" << std::endl;
		}
	}
	return 0;
}