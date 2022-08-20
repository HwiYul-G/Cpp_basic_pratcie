// �ڱ� �ڽ��� ����Ű�� ������ this
#include <iostream>

class Marine {
	static int total_marine_num; // �ڵ����� 0���� �ʱ�ȭ
	const static int i = 0; // const static�� class ������ ����� ���ÿ� �ʱ�ȭ ����

	int hp;
	int coord_x, coord_y;
	bool is_dead;

	const int default_damage; // �⺻ ���ݷ�

public:
	Marine();
	Marine(int x, int y);
	Marine(int x, int y, int default_damage);

	int attack();
	Marine& be_attacked(int damage_earn);
	void move(int x, int y);

	void show_status();
	static void show_total_marine();
	~Marine() { total_marine_num--; }
};

int Marine::total_marine_num = 0; // �ڵ����� 0���� �ʱ�ȭ ������ ��
void Marine::show_total_marine() {
	std::cout << "��ü ���� �� : " << total_marine_num << std::endl;
}

Marine::Marine()
	: hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
	total_marine_num++;
}

Marine::Marine(int x, int y)
	: coord_x(x),
	coord_y(y),
	hp(50),

	default_damage(5),
	is_dead(false) {
	total_marine_num++;
}

Marine::Marine(int x, int y, int default_damage)
	: coord_x(x),
	coord_y(y),
	hp(50),
	default_damage(default_damage),
	is_dead(false) {
	total_marine_num++;
}

void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}
int Marine::attack() { return default_damage; }

Marine& Marine::be_attacked(int damage_earn) {
	/*
		this��� Ű����� C++ ��� �������� ���ǵǾ� �ִ� Ű�����̴�.
		�̴� ��ü �ڽ��� ����Ű�� ������ ������ �Ѵ�.

		�� �� ��� �Լ��� ȣ���ϴ� ��ü �ڽ��� ����Ų�ٴ� ���̴�.

		this->hp -= damage_earn;
		if (this->hp <= 0) this->is_dead = true;
		return *this;
		
		�� �Լ��� ���� ������ ���� ���� this ->�� �̿��ؼ� ����ص� �ȴ�.
	*/
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;

	return *this;
}
void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
		<< std::endl;
	std::cout << " HP : " << hp << std::endl;
	std::cout << " ���� �� ���� �� : " << total_marine_num << std::endl;
}

int main() {
	Marine m1(2, 3, 5);
	m1.show_status();

	Marine m2(3, 5, 10);
	m2.show_status();

	std::cout << std::endl << "����1�� ���� 2�� 2�� ����" << std::endl;
	m2.be_attacked(m1.attack()).be_attacked(m1.attack());

	m1.show_status();
	m2.show_status();
	return 0;
}
/*
	������ ��� ��� �Լ� �������� this Ű���尡 ���ǵǾ� ������
	Ŭ���� �ȿ� ���ǵ� �Լ� �߿��� this Ű���尡 ���� �Լ��� 
	�翬�� ��ü�� �ƴ� Ŭ������ ���ӵǾ� �ִ� static �Լ� ���̴�.

	�׷��� ���۷��� Ÿ���� �����Ѵٴ� ���� �����ϱ�?

	���۷����� � ������ �ٸ� ����(alias)�̴�.
	�׷��� ������ �����Ѵٴ� ���� ���� ���ϱ�?
	=> 06_return_reference.cpp
*/