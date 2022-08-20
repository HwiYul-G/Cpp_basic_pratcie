/*
	Marine�� ���� �˾Ƴ��� ���� �ڵ带 ¥����.
	1) ��� �迭�� Marine�� �����ϰ� ������ Marine�� ���� ��� Count
	2) ��� ������ ���� Marine ������ 1�� �߰��ϰ� �Ҹ�� 1�� ��

	1)�� ��� vector��� �ڷ����� �̿��ϸ� ���� �� �� �ִ�.
	������ �̿����� �ʴ´ٸ� ũ�Ⱑ �����Ӱ� ���� �� �ִ� �迭�� ���� �������ϴ� �������� �ִ�.

	2)�� ��� ���� � �Լ� ������ �̷� ������ �����ߴٸ� �ٸ� �Լ������� �� ���� �̿��ϱ� ����
		��� ���ڷ� ����������ϴ� ���ŷο��� �ִ�.

	global ������ ����� ����� ������ global variable�� ��� ������Ʈ�� ũ�Ⱑ Ŀ�� ����
	���α׷����� �Ǽ��� ���� ���ļ� ������ �� ���ɼ��� ũ�� ������ �ݵ�� �ʿ��� ��찡 �ƴϸ� ������� �ʴ´�.
	(������ �ʿ��� ��� �ܿ� ��! ������� ����!)

	�̷��� ������ ������ �ذ��� �� �ִ� �������
	�������� ������ Ŭ���� �ϳ����� ���ӵ� ������ static ��� ������ �̿��� �� �ִ�.

	C������ � �Լ��� static ������ ����������ó�� �Լ��� ����� �� �Ҹ�ȴ� ���� �ƴ϶�
	���α׷��� ����� �� �Ҹ�Ǵ� ��ó��,
	� class�� static member variable�� ��� ��� ������ ó�� ��ü�� �Ҹ�� �� �Ҹ�Ǵ� ���� �ƴ϶�
	���α׷��� �Ҹ�� �� �Ҹ�ȴ�.

	�� static ��� ������ ��� Ŭ������ ��� ��ü���� '����'�ϴ� �����ν�
	�� ��ü ���� ���� �����ϴ� ���������� �޸� ��� ��ü���� '�ϳ���' static ��� ������ ����ϰ� �ȴ�.
*/
#include <iostream>

class Marine {
	/*
		marine�� ���� ���� ���� static ����
		global and static var �� ���ǿ� ���ÿ� ���� �ڵ����� 0���� �ʱ�ȭ �ȴ�.
		���� ���� �ʱ�ȭ ���� �ʾƵ� �ȴ�.
		������ �ʱ�ȭ �ϰ� �ʹٸ�
		class �ܺο��� int Marine::total_marine_num = 0; �̶�� �ۼ����ָ� �ȴ�.

		class ���ο��� static int total_marine_num = 0; ��ü�� �ʱ�ȭ�� �� ����.
		����������� �̷��� ������� �ʱ�ȭ ��ų �� ���� ��ó�� static ���� ���� �Ұ����ϴ�.

		������ ������ ���(class ���ο��� ����� ���ÿ� �ʱ�ȭ)��
		�����ϰ� const static ������ ����̴�.
		const static int x = 0; �̷� ���� �����ϴ�.

	*/
	static int total_marine_num;

	int hp;
	int coord_x, coord_y;
	int is_dead;

	const int default_damage;

public:
	Marine();
	Marine(int x, int y);
	Marine(int x, int y, int default_damage);

	int attack();						// ������ ����
	void be_attacked(int damage_earn);	// �Դ� ������
	void move(int x, int y);			// ���ο� ��ġ

	void show_status();					// ���� �����ܤ�

	~Marine() { total_marine_num--; }
};

Marine::Marine() :hp(50),coord_x(0),coord_y(0),default_damage(5),is_dead(false) {
	total_marine_num++;
}
Marine::Marine(int x, int y) :hp(50), coord_x(x), coord_y(y), default_damage(5), is_dead(false) {
	total_marine_num++;
}
Marine::Marine(int x, int y, int default_damage): hp(50), coord_x(x), coord_y(y), default_damage(default_damage), is_dead(false) {
	total_marine_num++;
}

int Marine::attack() { return default_damage; }
void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0)is_dead = true;
}
void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}
void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "<< std::endl;
	std::cout << " HP : " << hp << std::endl;
	std::cout << " ���� �� ���� �� : " << total_marine_num << std::endl;
}

void create_marine() {
	Marine marine3(10, 10, 4);
	marine3.show_status();
}

int main() {
	Marine m1(2, 3, 5);
	m1.show_status();

	Marine m2(3, 5, 10);
	m2.show_status();

	create_marine();

	std::cout << std::endl << "����1�� ����2�� ����!" << std::endl;
	m2.be_attacked(m1.attack());

	m1.show_status();
	m2.show_status();
	return 0;
}