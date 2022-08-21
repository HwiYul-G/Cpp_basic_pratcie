/*
	prefix increment operation
	operator++();
	operator--();
	
	postfix increment operation
	operator++(int x);
	operator--(int x);

	���� ���� �������� ���� int x�� ���� ���� ���� ���������� ǥ���ϱ� ���� ���̴�.

	- ���� ���� ���� : ���� �ٲ� �ڽ��� ����
	- ���� ���� ���� : ���� �ٲ�� ������ ��ü ����

	int x = 1;
	func(++x); // x�� 2�� ���޵�

	int x= 1;
	func(x++); // x�� 1�� ���޵ǰ� ���߿� 2�� ��

	A& operator++(){ 
		// A++ ���� ����
		return *this;
	}
	A operator++(int x){
		A temp(A);
		// A++�� �����Ѵ�.
		return temp;
	}

	���� ���� ������ ��� ++�� �ϱ� ���� ��ü�� ��ȯ�ؾ��ؼ� 
	temp ��ü�� ���� ���� ���¸� ����� ��
	++�� ������ �ڿ� temp ��ü�� ��ȯ�ϰ� �ȴ�.

	���� ���� ���� ������ ��� �߰������� ���� �����ڸ� ȣ�������� ���� ���� ���꺸�� �� ������.
*/

#include <iostream>

class Test {
	int x;
public:
	Test(int x) :x(x) {}
	Test(const Test& t) : x(t.x) {}

	Test& operator++() {
		x++;
		std::cout << "���� ���� ������" << std::endl;
		return *this;
	}
	Test operator++(int x) {
		Test temp(*this);
		x++;
		std::cout << "���� ���� ������" << std::endl;
		return temp;
	}
	
	int get_x() const { return x; }
};

void func(const Test& t) {
	std::cout << "x : " << t.get_x() << std::endl;
}

int main() {
	Test t(3);

	func(++t); // 4
	func(t++); // 4�� ��µ� (�׸����� 5�� �ٲ�)

	std::cout << "x : " << t.get_x() << std::endl;
	return 0;
}

/*
	������ �����ε��� ���� ���� ����
	- 2 ���� ������ ��ü ���̿��� ���� �����ڴ� ��� �Լ��� �ƴ� �ܺ� �Լ��� �����ε��ϴ� ���� ����.
	- �� ���� ��ü ������ ���� ������������ �� ��ü�� ���� �ٲ�ٴ��� ���� �������� ���� ���� �����ڴ� ��� �Լ��� �����ε�
	- ���� �����ڴ� ��� �Լ��� �����ε��ϴ� ���� ����. (ex. operator++ )
	- �Ϻ� �����ڵ��� �ݵ�� ��� �Լ��θ� �����ε� �ؾ��Ѵ�. (��ü �ڽ��� �����ϴ� ���)
*/