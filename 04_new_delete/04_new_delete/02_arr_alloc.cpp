#include <iostream>

int main() {
	int arr_size;
	std::cout << "array size : ";
	std::cin >> arr_size;
	
	/*
		T* pointer = new T[size];
		T를 임의의 타입이라 하면 위와 같이 배열을 할당할 수 있다.
		따라서 list는 이제 크기가 arr_size인 int 배열을 가지게 된다.
	*/
	int* list = new int[arr_size];
	for (int i = 0; i < arr_size; i++) {
		std::cin >> list[i];
	}
	for (int i = 0; i < arr_size; i++) {
		std::cout << i << "the element of list : " << list[i] << std::endl;
	}
	/* new []을 이용해 할당했다면 지울땐 delete[]로 지워라! */
	delete[] list;
	return 0;
}