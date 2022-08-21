/*
	friend keyword
	: Ŭ���� ���ο��� �ٸ� Ŭ������ �Լ����� friend�� ������ �� �ִµ�,
	friend�� ���ǵ� Ŭ������ �Լ����� ���� Ŭ������ private�� ���ǵ� ������ �Լ��鿡 ������ �� �ִ�.
*/

class A {
private:
	void private_func() {}
	int private_num;

	friend class B; // class B is a friend of A

	friend void func(); // func is a friend of A(class)
};

class B {
public:
	void b() {
		A a;

		// ��� pirvate �Լ��� �ʵ�������� friend�̹Ƿ� ���� ����
		a.private_func();
		a.private_num = 2;
	}
};

void func() {
	A a;

	// ��� private �Լ��� �ʵ�������� friend�̹Ƿ� ���� ����
	a.private_func();
	a.private_num = 2;
}
/*
	class A �ȿ��� B�� friend�� �����߱� ������ B�� A�� ��� private�� �� �� �ִ�.
	������ B �ȿ��� A�� friend�� �������� �ʾұ� ������
	A�� B�� private ��ü�鿡 ������ �� ����.
*/

int main() {

	return 0;
}