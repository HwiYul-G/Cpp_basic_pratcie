/*
	��ü�������� class�� �������� 
	C���� struct�� �̿��� ������� ���� ���� ���α׷��� �ٽ� ����.
*/
#include <iostream>

typedef struct Animal {
	char name[30];
	int age;

	int health;
	int food;
	int clean;
} Animal;

void create_animal(Animal* animal) {
	std::cout << "������ �̸�? ";
	std::cin >> animal->name;

	std::cout << "������ ����? ";
	std::cin >> animal->age;

	animal->health = 100;
	animal->food = 100;
	animal->clean = 100;
}
void play(Animal* animal) {
	animal->health += 10;
	animal->food -= 20;
	animal->clean -= 30;
}
void one_day_pass(Animal* animal) {
	// �Ϸ簡 ������
	animal->health -= 10;
	animal->food -= 30;
	animal->clean -= 20;
}
void show_stat(Animal* animal) {
	std::cout << animal->name << "�� ����" << std::endl;
	std::cout << "ü��    : " << animal->health << std::endl;
	std::cout << "��θ� : " << animal->food << std::endl;
	std::cout << "û��    : " << animal->clean << std::endl;
}

int main() {
	Animal* list[10];
	int animal_num = 0;

	for (;;) {
		std::cout << "1. ���� �߰��ϱ�" << std::endl;
		std::cout << "2. ��� " << std::endl;
		std::cout << "3. ���� ���� " << std::endl;

		int input;
		std::cin >> input;

		switch (input) {
			int play_with;
		case 1:
			list[animal_num] = new Animal;
			create_animal(list[animal_num]);

			animal_num++;
			break;
		case 2:
			std::cout << "������ ���? : ";
			std::cin >> play_with;

			if (play_with < animal_num) play(list[play_with]);
			break;

		case 3:
			std::cout << "������ ����? : ";
			std::cin >> play_with;
			if (play_with < animal_num) show_stat(list[play_with]);
			break;
		}

		for (int i = 0; i != animal_num; i++) {
			one_day_pass(list[i]);
		}
	}
	for (int i = 0; i != animal_num; i++) {
		delete list[i];
	}
	return 0;
}
/*
	����ڰ� play�� ȣ���ϸ� list[play_with]�� �����ؾ߸� �Ѵ�. �� ���� �����ΰ� �����ϴ� �� ����.
	������ �̷��� ���? Animal ����ü ��ü�� �Լ��� ����,
	�� ����ü ������ ���� �ڽ��� �Լ��� ������ �ϴ� ���̴�.

	�׷��� list[play_with]->play()�� ���� "
	�� ���� �ڽ��� �Լ�"�� ȣ���Ͽ� �ڽ��� �����͸� ó���ϰ� �� �� �ִ�.

	�̷��� �� �� �ִٸ� play �Լ��� ������ ���ڸ� ������ �ʿ䵵 ����
	�Լ� ���ο����� 
	void play(Animal *animal) {
	  animal->health += 10;
	  animal->food -= 20;
	  animal->clean -= 30;
	}
	�� animal->�� ���̸鼭 �۾����� �ʾƵ� �ȴ�.

	�ֳ��ϸ� list[play_with]->play() �� ���� play�� '�ڱ� �ڽ��� �Լ�' �̱� �����̴�.
	�� health, food, clean�� ��� list[play_with]�� ���̴�.

	�׸��� ���� �ҽ��ڵ忡�� ������ ���� �̰͸��� �ƴ϶� new�� ���� ���ο� ������ �Ҵ��ϴ� �κе� �����ϴ�.
	list[animal_num] = new Animal;
	create_animal(list[animal_num]);

	new Animal�� ���� ������ ������ ������ �ݵ�� create_animal �Լ��� ȣ���ؾ߸� �ߴ�.
	�ֳ��ϸ� new Animal�� ���� ���ο� Animal�� �Ҵ��� ���¶��
	health, food �� ������ �ƹ��� ���� ������� �ʱ� �����̴�.

	�� ���� Animal�� ���� �� create_animal�� ȣ������ �ʴ´ٸ� 
	���߿� play �Լ� ���� ȣ�� �� �� ������ ������ �߻��ϰ� �ȴ�.

	�׷��ٸ� ���� new�� ���ο� Animal�� ������ �� �ڵ����� ȣ��Ǵ� �Լ��� ������ ���?
	�� new�� �˾Ƽ� ȣ�����ִ� �׷� �Լ�. �׷� ���� �ִٸ� ������ create_animal�� ȣ���� �ʿ䵵 ����
	�ڵ����� ȣ��Ǵ� �Լ��� ��� �������� �ʱ�ȭ ���شٸ� ���߿� �ʱ�ȭ ���� �ʾ� �߻��ϴ� ������ ���� �� �ִ�.
*/

/*
	���� ���α׷��� �α⸦ �� Ȯ������ �����ϰ� �Ǿ��ٰ� �����غ���.
	Animal�̶� �ܼ��ϰ� �ҷ��Ͽ��� ���� ���� �� ����ȭ �ؼ� Bird, Fish ������ ������ ó���Ѵٰ� ����.

	Bird�� Fish�� �⺻������ Animal�� ���������� 
	Bird�� ���� ���� �ִ� ���� ��Ÿ���� ������ int height; �� �߰��ǰ�
	Fish�� ���� ����ϰ� �ִ� ������ ��Ÿ���� �ִ� ������ int deep;�� �߰��Ǿ���.

	typedef struct Bird {
	  char name[30];  // �̸�
	  int age;        // ����

	  int health;  // ü��
	  int food;    // ��θ� ����
	  int clean;   // ������ ����

	  // ��������� Animal �� �����ϴ�.
	  int height;  // ���� ��

	} Bird;

	typedef struct Fish {
	  char name[30];  // �̸�
	  int age;        // ����

	  int health;  // ü��
	  int food;    // ��θ� ����
	  int clean;   // ������ ����

	  // ��������� Animal �� �����ϴ�.
	  int deep;  // ���� ����

	} Fish;

	�̷��� �ۼ��ϸ� ���� ū �ð������̴�.
	Animal�� ���� ���������� ���� �޶��� �� ������ ����ü�� ���� 2���� �������.
	�׳� Animal�� ������ �κ��� ������ ���� ���� �߰��� �κи� �߰��ϸ� �ȵɱ�?

	�׷��� ������ �� �Ӹ��� �ƴϴ�.
	���̻� Animal* �迭 �ϳ��� �� �� ���� �ȴ�. 
	Animal*, Finish*,  Bird* �� ���� ���� ���� �����ؾ��Ѵ�.
	�Դٰ� play(), show_state() ���� �Լ��� ���ڿ� �°� ���� �ۼ��ؾ��Ѵ�.
	�� ���� int height �� int deep ���� �ϳ� �߰��� ���п� ���� �ۼ��� �ڵ��� ���� 2�踦 ����Ѵ�.

	==> ���� ���� ġ�� ���α׷���(OOP)�� �̸� Ż���غ���.
*/