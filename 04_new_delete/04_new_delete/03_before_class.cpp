/*
	객체지향언어의 class를 보기전에 
	C에서 struct를 이용해 만들었던 동물 관리 프로그램을 다시 보자.
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
	std::cout << "동물의 이름? ";
	std::cin >> animal->name;

	std::cout << "동물의 나이? ";
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
	// 하루가 지나면
	animal->health -= 10;
	animal->food -= 30;
	animal->clean -= 20;
}
void show_stat(Animal* animal) {
	std::cout << animal->name << "의 상태" << std::endl;
	std::cout << "체력    : " << animal->health << std::endl;
	std::cout << "배부름 : " << animal->food << std::endl;
	std::cout << "청결    : " << animal->clean << std::endl;
}

int main() {
	Animal* list[10];
	int animal_num = 0;

	for (;;) {
		std::cout << "1. 동물 추가하기" << std::endl;
		std::cout << "2. 놀기 " << std::endl;
		std::cout << "3. 상태 보기 " << std::endl;

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
			std::cout << "누구랑 놀게? : ";
			std::cin >> play_with;

			if (play_with < animal_num) play(list[play_with]);
			break;

		case 3:
			std::cout << "누구껄 보게? : ";
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
	사용자가 play를 호출하면 list[play_with]를 전달해야만 한다. 이 점이 무엇인가 낭비하는 것 같다.
	하지만 이러면 어떨까? Animal 구조체 자체에 함수를 만들어서,
	각 구조체 변수가 각각 자신의 함수를 가지게 하는 것이다.

	그러면 list[play_with]->play()와 같이 "
	각 변수 자신의 함수"를 호출하여 자신의 데이터를 처리하게 할 수 있다.

	이렇게 할 수 있다면 play 함수에 귀찮게 인자를 전달할 필요도 없고
	함수 내부에서도 
	void play(Animal *animal) {
	  animal->health += 10;
	  animal->food -= 20;
	  animal->clean -= 30;
	}
	의 animal->을 붙이면서 작업하지 않아도 된다.

	왜냐하면 list[play_with]->play() 일 때의 play는 '자기 자신의 함수' 이기 때문이다.
	즉 health, food, clean이 모두 list[play_with]의 것이다.

	그리고 위의 소스코드에서 불편한 점은 이것만이 아니라 new를 통해 새로운 동물을 할당하는 부분도 불편하다.
	list[animal_num] = new Animal;
	create_animal(list[animal_num]);

	new Animal을 통해 동물을 생성한 다음에 반드시 create_animal 함수를 호출해야만 했다.
	왜냐하면 new Animal을 통해 새로운 Animal을 할당한 상태라면
	health, food 등 변수에 아무런 값이 들어있지 않기 때문이다.

	즉 만약 Animal을 생성 후 create_animal을 호출하지 않는다면 
	나중에 play 함수 등을 호출 할 때 끔찍한 오류가 발생하게 된다.

	그렇다면 만일 new로 새로운 Animal을 생성할 때 자동으로 호출되는 함수가 있으면 어떨까?
	즉 new가 알아서 호출해주는 그런 함수. 그런 것이 있다면 귀찮게 create_animal을 호출할 필요도 없고
	자동으로 호출되는 함수에 멤버 변수들을 초기화 해준다면 나중에 초기화 되지 않아 발생하는 오류도 막을 수 있다.
*/

/*
	동물 프로그램이 인기를 얻어서 확장팩을 제작하게 되었다고 생각해보자.
	Animal이라 단순하게 불류하였던 것을 조금 더 세분화 해서 Bird, Fish 등으로 나누어 처리한다고 하자.

	Bird와 Fish는 기본적으로 Animal과 유사하지만 
	Bird엔 현재 날고 있는 고도를 나타내는 변수인 int height; 가 추가되고
	Fish엔 현재 잠수하고 있는 수심을 나타내고 있는 변수인 int deep;이 추가되었다.

	typedef struct Bird {
	  char name[30];  // 이름
	  int age;        // 나이

	  int health;  // 체력
	  int food;    // 배부른 정도
	  int clean;   // 깨끗한 정도

	  // 여기까지는 Animal 과 동일하다.
	  int height;  // 나는 고도

	} Bird;

	typedef struct Fish {
	  char name[30];  // 이름
	  int age;        // 나이

	  int health;  // 체력
	  int food;    // 배부른 정도
	  int clean;   // 깨끗한 정도

	  // 여기까지는 Animal 과 동일하다.
	  int deep;  // 현재 깊이

	} Fish;

	이렇게 작성하면 정말 큰 시간낭비이다.
	Animal과 거의 유사하지만 조금 달라진 것 때문에 구조체를 새로 2개나 만들었다.
	그냥 Animal과 동일한 부분을 가져다 쓰고 새로 추가된 부분만 추가하면 안될까?

	그런데 문제는 이 뿐만이 아니다.
	더이상 Animal* 배열 하나로 살 수 없게 된다. 
	Animal*, Finish*,  Bird* 를 각가 따로 만들어서 관리해야한다.
	게다가 play(), show_state() 등의 함수도 각자에 맞게 새로 작성해야한다.
	즉 고작 int height 나 int deep 변수 하나 추가한 덕분에 여태 작성한 코드의 양의 2배를 써야한다.

	==> 이제 객제 치향 프로그래밍(OOP)로 이를 탈출해보자.
*/