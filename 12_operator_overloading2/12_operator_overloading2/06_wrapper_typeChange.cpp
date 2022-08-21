/*
	Wrapper class
	�⺻ �ڷ������� ��ü�� �ٷ��� �� ���� �ִ�.
	�̶� �⺻ �ڷ������� ��ü�� ����ϴ� ���� Wrapper Ŭ������ �̿��Ѵٴ� ���̴�.
*/
#include <iostream>

class Int {
	int data;

public:
	Int(int data) : data(data) {}
	Int(const Int& i) : data(i.data) {}

	operator int() { return data; }
};

int main() {
	Int x = 3; // Wrapper ��ü
	// int a = x + 4; // ����� int�� ���� a
	// ������Ƽ�� Ÿ��(int)�� a�� Wrapper Ŭ������ ��ü�� x�� ���� �� ����.
	
	/*
		int�� ������ ���Ǵ� ��� �����ڿ� Int�� ���� wrapper Ŭ������ �����ϵ���
		������ �����ε��� �̿��� ���� �ִ�.
		������ ��� �����ڿ� �̸� �߰��ϴ� ���� ������ ���̴�.

		�׳� �� Wrapper Ŭ���� ��ü�� ��ġ 'int�� ����'��� �����Ϸ��� ������ �ִ�.
		=> Ÿ�� ��ȯ �����ڰ� �ֱ� �����̴�.

		Ÿ�� ��ȯ �����ڴ� �Ʒ��� ���� �����Ѵ�.
		operaotr (��ȯ �ϰ��� �ϴ� Ÿ�� ()
	*/
	Int y = 3;
	int a = y + 4;

	y = a * 2 + y + 4;
	std::cout << y << std::endl;
	// Ÿ�� ��ȯ �����ڸ� ���������� �� �Ǵ� ���� �� �� �ִ�.
	return 0;
}