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
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;

	return *this;
	/*
		�� �Լ��� Marine& Ÿ���� �����ϰ� �ȴ�.
		�� ��� *this�� �����ϰ� �ȴ�.
		this�� ���� �� �Լ��� ȣ���� ��ü�� ����Ű�� �������̴�.
		���� *this�� �� ��ü �ڽ��̴�.

		main �Լ��� ����
		marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());
		�� ����.
	*/
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
	/*
		be_attacked �Լ��� ����Ÿ���� Marine&�̴�.
		m2.be_attacked(m1.attack())�� ���� ����ǰ� ���ϵǴ� Ÿ���� �ٽ� m2�̴�.
		�׷��� m2.be_attacked(m1.attack())�� ����ȴ�.

		���� be_attacked �Լ��� ���� Ÿ���� Marine&�� �ƴ϶� �׳� Marine�̶�� ����.
		�� ���� be_attacked �Լ��� �Ʒ��� ���ٰ� �����غ���.

		Marine Marine::be_attacked(int damage_earn) {
			this->hp -= damage_earn;
			if (this->hp <= 0) this->is_dead = true;
			return *this;
		}

		�̷��� �� ���·� 
		m2.be_attacked(m1.attack()).be_attacked(m1.attack());
		�� �Ǿ��ٰ� ��������.
		�̰��� ����Ǹ� m2�� ������ �� �� ������ �ƴ� 1�� �������� ������ hp�� ���δ�.
		�̴� ����Ÿ���� Marine�̹Ƿ� �ӽð�ü Marine�� �����ؼ� *this�� �������� ���簡 �ȴ�.
		�� Marine�� ���� �����ڰ� ȣ��ȴ�.
		�� �ӽ� ��ü�� ���� be_attacked �Լ��� ȣ��ȴ�.

		���� �� ��° be_attacked�� marine2�� �ƴ϶� ������ �ӽ� ��ü�� ���� ȣ��Ǵ� ���̶�
		m2�� m1�� ������ 1���� �ް� �ȴ�.
	*/

	m1.show_status();
	m2.show_status();
	return 0;
}