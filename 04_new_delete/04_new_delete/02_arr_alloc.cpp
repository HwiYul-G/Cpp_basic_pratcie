#include <iostream>

int main() {
	int arr_size;
	std::cout << "array size : ";
	std::cin >> arr_size;
	
	/*
		T* pointer = new T[size];
		T�� ������ Ÿ���̶� �ϸ� ���� ���� �迭�� �Ҵ��� �� �ִ�.
		���� list�� ���� ũ�Ⱑ arr_size�� int �迭�� ������ �ȴ�.
	*/
	int* list = new int[arr_size];
	for (int i = 0; i < arr_size; i++) {
		std::cin >> list[i];
	}
	for (int i = 0; i < arr_size; i++) {
		std::cout << i << "the element of list : " << list[i] << std::endl;
	}
	/* new []�� �̿��� �Ҵ��ߴٸ� ���ﶩ delete[]�� ������! */
	delete[] list;
	return 0;
}