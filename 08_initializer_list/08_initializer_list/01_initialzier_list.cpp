/*
	�������� �ʱ�ȭ ����Ʈ(initializer list)

*/
#include <iostream>

class Marine {
	int hp;
	int coord_x, coord_y;
	int damage;
	bool is_dead;
public:
	Marine();
	Marine(int x, int y);

	int attack();
	void be_attacked(int damage_earn);
	void move(int x, int y);

	void show_status();
};

// initialzier_list!!
Marine::Marine() : hp(50), coord_x(0), coord_y(0), damage(5), is_dead(false) {}
Marine::Marine(int x, int y) : coord_x(x), coord_y(y), hp(50), damage(5), is_dead(false) {}

int Marine::attack() { return damage; }
void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
}
void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}

void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
		<< std::endl;
	std::cout << " HP : " << hp << std::endl;
}

int main() {
	Marine marine1(2, 3);
	Marine marine2(3, 5);

	marine1.show_status();
	marine2.show_status();
}
/*
	Marine::Marine() : hp(50), coord_x(0), coord_y(0), damage(5), is_dead(false) {}
	Marine::Marine(int x, int y) : coord_x(x), coord_y(y), hp(50), damage(5), is_dead(false) {}

	����Ե� �Լ� ��ü���� ������ �޸� �ƹ��͵� ����.
	���� ���� �߰��� �̻��� �͵��� ���� �����ڰ� �ߴ� �ϰ� ������ �۾��� �ϰ� ���� ���̴�.

	������ �̸� ���� �ִ� ���͵��� '�ʱ�ȭ ����Ʈ(initializer list)'��� �θ���
	������ ȣ��� ���ÿ� ��� �������� �ʱ�ȭ���ְ� �ȴ�.

	��� �ʱ�ȭ ����Ʈ�� �Ϲ����� ���� �Ʒ��� ����.
	(������ �̸�) : var1(arg1), var2(arg2) {}
	���⼭ var�� Ŭ������ ��� �����̰� arg�� �� ��������� �������� �ʱ�ȭ������ ��Ī�ϴ� �����̴�.
	��̷ο� �̸��� var1�� arg1�� �̸��� �����ص� �ȴ�.

	coord_x(coord_x)���� �ٱ��� coord_x�� ������ ��� ������ ��Ī�ϰ� �ȴ�.
	��ȣ ���� coord_x�� ��Ģ�� Marine�� ���ڷ� ���� coord_x�� �켱������ ��Ī�ϴ� ���̱� �����̴�.


	=============================================================================================
	�׷��ٸ� Marine::Marine(){hp = 50; .... }�̶� Marine::Marine():hp(50), .. {}�� ���̴� �����ϱ�?

	�ʱ�ȭ ����Ʈ�� ����ϴ� ��� ������ �ʱ�ȭ�� ���ÿ� �Ѵ�.
	�ݸ鿡 �ʱ�ȭ ����Ʈ�� ������� ������ ������ ���� �ϰ� �� ������ ������ �����ϰ� �ȴ�.
	���� ���� �ʱ�ȭ ����Ʈ�� ����ϴ� ���� int a = 10; �̶� �ϴ� �Ͱ� ���� 
	�׳� ���� ������ �����ڸ� ����ϴ� ���� int a; a = 10; �̶� �ϴ� �Ͱ� �����ϴ�.

	���࿡ int�� ��ſ� Ŭ���� ���ٸ�, ������ ��� ���� �����ڰ� ȣ��Ǵµ�, 
	������ ��� ����Ʈ �����ڰ� ȣ��� �� ������ ����ȴ�.

	���ڰ� �ϴ� �۾��� ���� ���� �ʱ�ȭ ����Ʈ�� ����ϴ� ���� ���� �� ȿ������ �۾��̴�.
	�� �Ӹ� �ƴ϶�, �츮 ����� �ݵ�� '������ ���ÿ� �ʱ�ȭ �Ǿ�� �ϴ� �͵�'�� �� ���� �ִ�.
	��ǥ������ ���۷����� ����� �׷���.

	����� ���۷����� ������ ���ÿ� �ʱ�ȭ ���� ������ ������ ������ ����.
	���� ���࿡ Ŭ���� ���ο� ���۷��� ������ ����� �ְ� �ʹٸ�
	�̵��� �����ڿ��� ������ �ʱ�ȭ ����Ʈ�� ����� �ʱ�ȭ ���Ѿ� �Ѵ�.
*/