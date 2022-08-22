/*
	N차원 배열 만들기
	arr[x1][x2]...[xn]

	1) x1 * x2 * ... * xn 크기의 1차원 배열을 할당한 뒤 접근할 때 정확한 위치를 찾아분
	-> 메모리도 정확히 필요한 만큼만 사용할 수 있어서 좋은 방법

	2) 2차원 배열의 동적할당을 수행할 때 했던 idea
		실제로 메모리상에 배열처럼 나열되지 않지만 논리적으로 배열로 사용

		int** arr = new int*[x1];
		for(int i = 0; i<x1; i++) arr[i] = new int[x2];

		이렇게 하면 int arr[x1][x2]를 한 것과 동일한 효과를 낼 수 있다.
		하지만 포인터 자체가 잡아먹는 크기 때문에 x1*x2 + 1만큼의 메모리를 잡아먹게 된다.

		장점은 메모리가 허용하는 한 크기가 매우 큰 배열도 생성할 수 있다.
		1) 방식의 경우 저체 배열의 원소수가 int 크기를 넘어가면, 
		따로 큰 수의 정수를 다룰 수 있는 라이브러리를 사용해서 메모리를 동적으로 할당해 주어야한다.

		하지만 2) 방식의 경우 전체 원소 수가 아니라 한 차원의 수가 int 크기만 넘어가지 않으면 된다.
		즉 (int크기)^n 개의 원소를 사용할 수 있다.
		3차원 배열의 경우 2^96이 된다.

		여기서 문제점은 만들려는 배열이 정해진 상수 차우너 배열이 아니라, N 차원 배열이라는 것이다.
		만일 3차원 배열을 만들었다면 int***을 사용했을 것이고 4차원은 int****를 이용했을 것이다.
		하지만 N차원 배열의 경우 N개의 *이 들어간 포인터를 정의할 수는 없을 것이다.

		하지만 살짝 관점을 바꾸면 쉽게 해결할 수 있다.
		포인터를 이용하는 것이 단순히 다음 레벨의 배열을 가리키기 위함이라면 굳이 N 포인터를 사용하지 않아도 되기 때문이다.
*/

// n차원 배열의 경우 level0부터 level n까지 있고 level n-1까지 Address 객체를 보관하고 level n에 실질적인 데이터를 보관함

class Array {
	const int dim; // 몇 차원 배열인지
	int* size;
	
	/*
		외부에 Array 배열이 내부적으로 어떻게 작동하는 지 공개하고 싶지 않고
		내부 정보에 접근하는 것을 원치 않아서 Array 클래스 내에 Address 구조체를 넣음
	*/
	struct Address {
		int level;
		// 맨 마지막 레벨(dim - 1 레벨) 은 데이터 배열을 가리키고, 그 위 상위
		// 레벨에서는 다음 Address 배열을 가리킨다.
		void* next;
	};
	
	Address* top;

public:
	Array(int dim, int* array_size) :dim(dim) {
		size = new int[dim];
		for (int i = 0; i < dim; i++)
			size[i] = array_size[i];
		top = new Address;
		top->level = 0;

		initialize_address(top);
	}
	Array(const Array& arr) : dim(arr.dim) {
		size = new int[dim];
		for (int i = 0; i < dim; i++)
			size[i] = arr.size[i];
		top = new Address;
		top->level = 0;

		initialize_address(top);

		copy_address(top, arr.top);
	}

	void copy_address(Address* dst, Address* src) {
		if (dst->level == dim - 1) {
			for (int i = 0; i < size[dst->level]; ++i) {
				static_cast<int*>(dst->next)[i] = static_cast<int*>(src->next)[i];
			}
			return;
		}
		for (int i = 0; i != size[dst->level]; i++) {
			Address* new_dst = static_cast<Address*>(dst->next) + i;
			Address* new_src = static_cast<Address*>(src->next) + i;
			copy_address(new_dst, new_src);
		}
	}

	~Array() {
		delete_address(top);
		delete[] size;
	}

	/* 
		동적으로 2차원 배열을 생성했을 때처럼 for문으로 간단히 수행할 수 없다.
		for 문을 수행하기 위해선 몇 중 for문을 사용할지 컴파일 시 정해져야하는데
		이 경우 N차원인 임의의 차원이므로 그럴 수 없다.

		이를 해결하는 아주 좋은 아이디어는 '재귀 함수'를 이용하는 것이다.
		재귀함수를 구성하는 두 가지 스텝이 있는데
		1) 함수에서 처리하는 것, 즉 현재 단계에서 다음 단계로 넘어가는 과정은 무엇인가?
		2) 재귀 호출이 종료되는 조건은 무엇인가?

		2)에 대한 해답은 현재 처리하고 있는 Address 배열의 레벨이 (dim-1)이면 된다.
		즉 Address 배열의 레빌이 (dim-1)이면 이 배열의 원소들의 next에는 int형 배열의 데이터가 들어가
		재귀 호출이 끊나게 된다.

		1)에 대한 답(현재-> 다음 과정)은 무엇일까?
		현재 n레벨의 Address 배열이라면 이들의 next에 다음 레벨인 n+1 레벨의 Address 배열을 지정해주고
		각각 이 원소에 대해 처리해주면 된다.
	*/

	void initialize_address(Address* current) {
		if (!current) return; // current가 NULL일 때
		if (current->level == dim - 1) {
			current->next = new int[size[current->level]];
			return;
		}
		current->next = new Address[size[current->level]];
		for (int i = 0; i != size[current->level]; i++) {  // 다음 단계로 넘어가는 과정
			(static_cast<Address*>(current->next) + i)->level = current->level + 1;

			initialize_address(static_cast<Address*>(current->next) + i);
		}
	}

	void delete_address(Address* current) {
		if (!current) return;
		for (int i = 0; current->level < dim - 1 && i < size[current->level]; i++)
			delete_address(static_cast<Address*>(current->next) + i);

		if (current->level == dim - 1)
			delete[] static_cast<int*>(current->next);

		delete[] static_cast<Address*>(current->next);
	}
};