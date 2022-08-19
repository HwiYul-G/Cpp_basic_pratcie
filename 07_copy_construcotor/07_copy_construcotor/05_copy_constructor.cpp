/*
	����Ʈ ���� �������� �Ѱ�
*/
#include <string.h>
#include <iostream>

class Photon_Cannon {
	int hp, shield;
	int coord_x, coord_y;
	int damage;

	char* name;	// �߰���!!

public:
	Photon_Cannon(int x, int y);
	Photon_Cannon(int x, int y, const char* cannon_name);
	~Photon_Cannon();

	void show_status();
};

Photon_Cannon::Photon_Cannon(int x, int y) {
	hp = shield = 100;
	coord_x = x;
	coord_y = y;
	damage = 20;

	name = NULL;
}
Photon_Cannon::Photon_Cannon(int x, int y, const char* cannon_name) {
	hp = shield = 100;
	coord_x = x;
	coord_y = y;
	damage = 20;

	name = new char[strlen(cannon_name) + 1];
	strcpy(name, cannon_name);
}
Photon_Cannon::~Photon_Cannon() {
	// 0 �� �ƴ� ���� if ������ true �� ó���ǹǷ�
	// 0 �ΰ� �ƴѰ��� ���� �� �׳� if(name) �ϸ�
	// if(name != 0) �� ������ �ǹ̸� ���� �� �ִ�.

	// ����� if �� ������ ������ 1 ���� �´ٸ�
	// �߰�ȣ�� ���� �����ϴ�.

	if (name) delete[] name;
}
void Photon_Cannon::show_status() {
	std::cout << "Photon Cannon :: " << name << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
		<< std::endl;
	std::cout << " HP : " << hp << std::endl;
}

int main() {
	Photon_Cannon pc1(3, 3, "Cannon");
	Photon_Cannon pc2 = pc1;

	pc1.show_status();
	pc2.show_status();
}
/*
	�̸� �����ϸ� ��Ÿ�� ������ ����.
	�и��� ����Ʈ ���� �����ڴ� ���ҵ� ���� ��Ȯ�� ���縦 1:1�� ������ �شٰ� �ߴ�.

	�׷� ���⼭ �츮�� ��bƮ ���� �����ڰ� ��� ����� �� ����.
	�Ƹ� �Ʒ��� ���� ���� �����ڰ� ����� ���� ���̴�.
	Photon_Cannon::Photon_Cannon(const Photon_Cannon& pc){
		hp = pc.hp;
		shield = pc.shield;
		coord_x = pc.coord_x;
		coord_y = pc.coord_y;
		damage = pc.damage;
		name = pc.name;
	}
	�׷� �� ���� �����ڸ� �M���� �ڿ� pc1�� pc2�� ��� �Ǿ��� �� ����.
	hp, shield, ... , name���� ��� ���� ���� ���� �ȴ�.
	���⼭ name�� ���� ��- �� 2���� �����Ͱ� ���� ���� ������ -���� ���� �ּҰ��� ����Ų��.

	��, �츮�� pc1�� name�� �������� �Ҵ�޾Ƽ� ����Ű�� �ִ� �޸�("Cannon"�̶�� ���ڿ��� ����� �޸�)�� pc2�� name�� ���� ����Ű�� �ǳ�.

	���� �� ���¿����� �� ������ �ȵȴ�.
	���� �޸𸮸� ���� �ٸ� �� �����Ͱ� �����ѵ� �Ǳ� �����̴�.

	������ ������ �Ҹ��ڿ��� �Ͼ��.
	main �Լ��� ����Ǳ� ������ �����Ǿ��� ��ü� �ı��Ǹ鼭 �Ҹ��ڸ� ȣ���ϰ� �ȴ�.
	���� pc1�� ���� �ı� �Ǿ��ٸ� pc1�� �����Ǹ鼭 name�� ����Ű�� �ִ� ��(������)���� delete�ϰ� �ȴ�.
	�׷��� pc2�� name�� �̹�(���) ������ �޸𸮸� ����Ű�� �ִ�.

	Photon_Cannon::~Photon_Cannon() {
		if (name) delete[] name;
	}

	pc2���� �ϴ� name�� NULL�� �ƴϹǷ� (����Ű�� �ִ� �ּҰ��� �ִ�) delete [] name�� ����ȴ�.
	�׷��� �̹� ������ �޸𸮿� �ٽ� �����ؼ� �ٽ� �����Ϸ��� �߱� ������ (��� ������ �� ��ü������ ����)
	�� Ÿ�� ������ �߻��ϰ� �ȴ�.

	�׷��ٸ� �� ������ �������� ���� �ؾ��ұ�? ���� �����ϴ�!
	���� �����ڿ��� name�� �״�� �������� ���� ���� �޸𸮿� �����Ҵ��� �ؼ� �� ���븸 �����ϸ� �ȴ�.
	�̷��� �޸𸮸� ���� �Ҵ��ؼ� ������ �����ϴ� ���� ���� ����(deep copy)��� �θ���.

	�Ʊ�ó�� �ܼ��� ���Ը� ���ִ� ���� ���� ����(shallow copy)��� �θ���.

	�����Ϸ��� �����ϴ� ����Ʈ ���� �������� ��� ���� ���縸 �� �� �־ 
	���� ���� ���� ���簡 �ʿ��� ��쿣 ����ڰ� ���� ���� �����ڸ� �������Ѵ�.

	���� ���縦 ���� ��������ڸ� ����� ���� 06_deep_copy.cpp�� ����!
*/