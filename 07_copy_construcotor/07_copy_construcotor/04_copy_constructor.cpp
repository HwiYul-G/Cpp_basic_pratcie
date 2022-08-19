#include <iostream>
#include <string.h>

class Photon_Cannon {
	int hp, shield;
	int coord_x, coord_y;
	int damage;
public:
	Photon_Cannon(int x, int y);
	Photon_Cannon(const Photon_Cannon& pc);

	void show_status();
};

Photon_Cannon::Photon_Cannon(int x, int y) {
	std::cout << "������ ȣ��!" << std::endl;
	hp = shield = 100;
	coord_x = x;
	coord_y = y;
	damage = 20;
}
Photon_Cannon::Photon_Cannon(const Photon_Cannon& pc) {
	std::cout << "���� ������ ȣ��!" << std::endl;
	hp = pc.hp;
	shield = pc.shield;
	coord_x = pc.coord_x;
	coord_y = pc.coord_y;
	damage = pc.damage;
	/*
		�츮�� ������ �� ��������ڴ� ǥ������ �����̴�.
		�� ��������ڴ� � Ŭ���� T�� �ִٸ�, T(const T& a); ��� ���ǵȴ�.
		�� �ٸ� T�� ��ü a�� ��� ���۷����� �޴´ٴ� ���̱��̴�.
		
		���⼭ a�� cosnt�̹Ƿ� �츮�� ���� ������ ���ο��� 
		a�� �����͸� ������ �� ���� 
		���� ���Ӱ� �ʱ�ȭ �Ǵ� �ν��Ͻ��鿡�� '����'�� �� �� �ִ�.

		!! �Լ� ���ο��� ���� ������ ���� ��ȭ��Ű�� ���� ���ٸ� �� cosnt�� ������!!
	*/
}
void Photon_Cannon::show_status() {
	std::cout << "Photon Cannon " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "<< std::endl;
	std::cout << " HP : " << hp << std::endl;
}

int main() {
	Photon_Cannon pc1(3, 3);
	Photon_Cannon pc2(pc1);
	Photon_Cannon pc3 = pc2;	// �� �ڵ� ���� ���� �����ڰ� ȣ��ȴ�. Photon_Cannon pc3(p2);�� �����ϰ� �ؼ���
	/*
		1) Photon_Cannon pc3 = pc2;
		2) Photon_Cannon pc3;
		   pc3 = pc2;
		1), 2)�� ������ �ٸ� �����̴�.
		1)�� �� �״�� ���� �����ڰ� 1�� ȣ��ȴ� ���̰�
		2)�� �׳� �����ڰ� �ѹ� ȣ��ǰ� pc3=pc2;��� ����� ����Ǵ� ���̴�.
		�ٽ� �� �� ����������, ���� �����ڴ� ���� '����'�ÿ� ȣ��ȴٴ� ���� ����ϸ� �ȴ�.

		�׷��� ��� ����Ʈ �����ڿ� ����Ʈ �Ҹ���ó��
		C++ �����Ϸ��� �̹� ����Ʈ ���� �����ڸ� �������ش�.
		�� �ڵ忡�� ���� �����ڸ� �������� �����ص� ������ ������ ����� ��Ÿ����.

		����Ʈ ���� ������ T(const T& a); �� ��� 
		������ ����Ʈ �����ڿ� �Ҹ��ڰ� �ϴ� ���� �ƹ� �͵� ������ �Ͱ� �޸� ������ '����'�� ���ش�.

		���� �� Photon_Cannon�� ����Ʈ ���� �������� ������ �����غ���
		Photon_Cannon::Photon_Cannon(const Photon_Cannon& pc) {
			hp = pc.hp;
			shield = pc.shield;
			coord_x = pc.coord_x;
			coord_y = pc.coord_y;
			damage = pc.damage;
		}
		�� ���� ������ ���̴�.

		�����Ǵ� ���ҵ��� �� �״�� 1:1 �������ְ� �ȴ�. 
		 
	*/
	pc1.show_status();
	pc2.show_status();

	return 0;
}
