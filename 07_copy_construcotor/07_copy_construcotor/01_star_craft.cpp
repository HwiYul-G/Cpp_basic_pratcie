/*
	�����ڸ� ���� ������ C ���α׷��� �� ���� �ʱ�ȭ�� ���� �ʾƼ� ����� �� ���� ������ ȿ�������� ���� �� �־���.

	�Ӹ� �ƴ϶� C++���� ���� ���Ե� �Լ� �����ε� ���п� �Լ� �̸��� ������ ���� �������� �ʴ���
	���������� ���ڵ��� Ÿ�Կ� �� ���ϴ� �Լ��鸸 ȣ���� �� �ְ� �Ǿ���.

	������ C��� ���ٸ� ������ Ÿ�Կ� ���� �Լ��� �̸��� �ܿ��� ������, C++���� �׷� �ʿ䰡 ���� ����.
*/

#include <iostream>

class Marine {
	int hp;
	int coord_x, coord_y;
	int damage;
	bool is_dead;
public:
	Marine() = default; // �⺻ ������
	Marine(int x, int y);	// x, y ��ǥ�� ���� ����

	int attack(); // �������� ����
	void be_attacked(int damage_earn); // �Դ� ������
	void move(int x, int y); // ���ο� ��ġ

	void show_status(); // ���¸� �����ش�.
};

Marine::Marine() {
	hp = 50;
	coord_x = coord_y = 0;
	damage = 5;
	is_dead = false;
}

Marine::Marine(int x, int y) {
	coord_x = x;
	coord_y = y;
	hp = 50;
	damage = 5;
	is_dead = false;
}

void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}

int Marine::attack() { return damage; }

void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
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

	std::cout << std::endl << "���� 1�� ���� 2�� ����! " << std::endl;
	marine2.be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();
	/*
		������ 2������ �ƴ϶� ��û���� �������ٸ�
		-> �迭�� ����!
	*/
	Marine* marines[100];

	/*
		new delete�� ���� ��� �� malloc���� �������� �ִٰ� �޴�.
		new�� malloc ��� �������� �Ҵ�������, new�� ��� 
		��ü�� �������� �����ϸ鼭 ���ÿ� �ڵ����� �����ڵ� ȣ�����شٴ� ���� �ٸ���.
	*/
	marines[0] = new Marine(2, 3);
	marines[1] = new Marine(3, 5);

	/*
		Marine���� '������'�� ����Ű�� �迭�̱� ������ �޼ҵ带 ȣ���� �� ->�� ����ؾ��Ѵ�.
	*/
	marines[0]->show_status();
	marines[1]->show_status();

	std::cout << std::endl << "���� 1 �� ���� 2 �� ����! " << std::endl;

	marines[0]->be_attacked(marines[1]->attack());

	marines[0]->show_status();
	marines[1]->show_status();

	// ���� �Ҵ� �Ŀ� �׻� ������ ������Ѵ�.
	delete marines[0];
	delete marines[1];



	return 0;
}