// ��ȣ�� �����ε�
#include <iostream>

void print(int x) { std::cout << "int : " << x << std::endl; }
void print(char x) { std::cout << "double : " << x << std::endl; }

int main() {
	int a = 1;
	char b = 'c';
	double c = 3.2f;

	print(a);
	print(b);
	print(c);

	return 0;
}
/*
	 error C2668: 'print' : ambiguous call to overloaded function could be 'void print(char)'
						or  'void print(int)' while trying to match the argument list '(double)'

	�̷��� ������ ���� ���̴�.
	������ �Ǵ� print(c); �κ��� ����.
	print(c)�� ���� ��  �ڱ� Ÿ�Կ� �´� ���� ����(1) �׷��� 2�ܰ�� �Ѿ��
	double�� ĳ���ÿ� ���� ������ ���� ��ġ�ϴ� ���� ����. ���� 3�ܰ�� ����.
	������ ���� Ÿ���� ������ ����Ÿ������ ��ȯ�Ǽ� �����ǹǷ� double�� char, int�� �Ѵ� ��ȯ �� �� �ִ�.

	���� ���� �ܰԿ��� 2�� �̻� ������ ��ġ�� �����ϹǷ� '��ȣ��' ������ �߻��ϰ� �ȴ�.

	C++�� �����ε� ��Ģ�� �����ϴ� ���� �߿��ϴ�.
	�ֳ��ϸ� ���߿� ������ �Լ��� �����ε� �� �� ���� ���� �ߺ��Ǹ鼭 ���´ٸ� ������ �⿬�� �� �� �ֱ� �����̴�.
*/