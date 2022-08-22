/*
	2,3차원 배열정도는 for문을 다중으로 사용할만 하다.
	하지만 차원이 깊어질 수록 for문을 중첩해서 돌리면 가독성도 떨어지고 복잡하다.
	
	따라서 우리의 Array 클래스에 또다른 기능으로, 
	모든 원소들을 순차적으로 접근할 수 있는 반복자(iterator)라는 것을 추가해보자.

	이를 위해 Array에 Iterator라는 클래스를 추가하자.
	class Iterator{
		int* location;
		Array* arr;
	}
	이 iterator는 배열의 특정한 원소에 대한 포인터이다.
	C언어에서 배열의 어떤 원소를 가리키고 있는 포인터 ptr에 ptr++을 하면 다음 원소를 가리키듯
	반복자 itr이 Array의 어떤 원소를 가리키고 있을 때 itr++을 하면 그 다음 원소를 가리키게 된다.
	따라서 사용자는 N중 for문을 사용해서 전체 원소를 참조하는 방법보단 
	itr을 이용해 itr++을 통해 마지막 원소까지 가리키게 할 수 있다.

	이를 위해 우리의 Iterator 클래스에 
	현재 Iteraotr가 어떤 원소를 가리키고 있는지에 대한 정보를 멤버 변수로 가지게 하자.
	이는 int* location에 배열로 보관되는데
	예를 들어 3차원 배열에서 Iterator가 arr[1][2][3]을 가리키고 있다면 location 배열엔 {1,2,3}이 들어가는 것이다.
	단순한 방법이므로 operator++() 함수도 간단하게 만들 수 있다.

	Iterator& operator++(){
		if(location[0] >= arr->size[0] ) return (*this);

		bool carry = false;
		int i = arr->dim -1;
		do{
			location[i]++;
			if(location[i] >= arr->size[i] && >=1){
				location[i] -= arr=>size[i];
				carry = true;
				i--;
			}
		} while(i>= 0 && carry);

		return (*this);
	}
*/
#include <iostream>

namespace MyArray {
	class Array;
	class Int;

	class Array {
		friend Int;

		const int dim;
		int* size; // size[0] * size[1] * ... * size[dim-1] 짜리 배열

		struct Address {
			int level;
			void* next;
		};

		Address* top;

	public:
		class Iterator {
			int* location;
			Array* arr;

			friend Int;

		public:
			Iterator(Array* arr, int* loc = NULL) : arr(arr) {
				location = new int[arr->dim];
				for (int i = 0; i != arr->dim; i++)
					location[i] = (loc != NULL ? loc[i] : 0);
			}
			Iterator(const Iterator& itr) : arr(itr.arr) {
				location = new int[arr->dim];
				for (int i = 0; i != arr->dim; i++) 
					location[i] = itr.location[i];
			}
			~Iterator() { delete[] location; }

			// 다음 원소를 가리키게 된다.
			Iterator& operator++(){
				if (location[0] >= arr->size[0]) return (*this);

				bool carry = false;
				int i = arr->dim - 1;
				do {
					location[i]++;
					if (location[i] >= arr->size[i] && i >= 1) {
						location[i] -= arr->size[i];
						carry = true;
						i--;
					}
				} while (i > 0 && carry);

				return (*this);
			}
			Iterator& operator=(const Iterator& itr) {
				arr = itr.arr;
				location = new int[itr.arr->dim];
				for (int i = 0; i != arr->dim; i++)
					location[i] = itr.location[i];

				return (*this);
			}
			Iterator operator++(int) {
				// 후위연산자
				Iterator itr(*this);
				++(*this);
				return itr;
			}
			bool operator!=(const Iterator& itr) {
				if (itr.arr->dim != arr->dim) return true;

				for (int i = 0; i != arr->dim; i++) {
					if (itr.location[i] != location[i]) return true;
				}

				return false;
			}
			Int operator*();
		};

		Array(int dim, int* array_size) :dim(dim) {
			size = new int[dim];
			for (int i = 0; i < dim; i++) size[i] = array_size[i];

			top = new Address;
			top->level = 0;

			initialize_address(top);
		}
		Array(const Array& arr) : dim(arr.dim) {
			size = new int[dim];
			for (int i = 0; i < dim; i++) size[i] = arr.size[i];

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

		void initialize_address(Address* current) {
			if (!current) return;
			if (current->level == dim - 1) {
				current->next = new int[size[current->level]];
				return;
			}
			current->next = new Address[size[current->level]];
			for (int i = 0; i != size[current->level]; i++) {
				(static_cast<Address*>(current->next) + i)->level = current->level + i;
				initialize_address(static_cast<Address*>(current->next) + i);
			}
		}

		void delete_address(Address* current) {
			if (!current) return;
			for (int i = 0; current->level < dim - 1 && i < size[current->level]; i++) {
				delete_address(static_cast<Address*>(current->next) + i);
			}

			if (current->level == dim - 1) {
				delete[] static_cast<int*>(current->next);
			}
			delete[] static_cast<Address*>(current->next);
		}

		Int operator[](const int index);

		~Array() {
			delete_address(top);
			delete[] size;
		}

		Iterator begin() {
			int* arr = new int[dim];
			for (int i = 0; i != dim; i++)
				arr[i] = 0;

			Iterator temp(this, arr);
			delete[] arr;

			return temp;
		}
		Iterator end() {
			int* arr = new int[dim];
			arr[0] = size[0];
			for (int i = 1; i < dim; i++)
				arr[i] = 0;

			Iterator temp(this, arr);
			delete[] arr;

			return temp;
		}
	};

	class Int {
		void* data;

		int level;
		Array* array;

	public:
		Int(int index, int _level = 0, void* _data = NULL, Array* _array = NULL)
			: level(_level), data(_data), array(_array) {
			if (_level < 1 || index >= array->size[_level - 1]) {
				data = NULL;
				return;
			}

			if (level == array->dim) {
				// data에 int 형 자료형을 저장하게 해야함
				data = static_cast<void*>((
					static_cast<int*>(static_cast<Array::Address*>(data)->next) + index));
			}
			else {
				// 그렇지 않은 경우 data에 다음 addr을 넣음
				data = static_cast<void*>(static_cast<Array::Address*>(
					static_cast<Array::Address*>(data)->next) + index);

			}
		}

		Int(const Int& i) : data(i.data), level(i.level), array(i.array) {}

		operator int() {
			if (data) return *static_cast<int*>(data);
			return 0;
		}
		Int& operator=(const int& a) {
			if (data) *static_cast<int*>(data) = a;
			return *this;
		}
		Int operator[](const int index) {
			if (!data) return 0;
			return Int(index, level + 1, data, array);
		}
	};

	Int Array::operator[](const int index) {
		return Int(index, 1, static_cast<void*>(top), this);
	}
	Int Array::Iterator::operator*() {
		Int start = arr->operator[](location[0]);
		for (int i = 1; i <= arr->dim - 1; i++) {
			start = start.operator[](location[i]);
		}
		return start;
	}
}

int main() {
	int size[] = { 2, 3, 4 };
	MyArray::Array arr(3, size);

	MyArray::Array::Iterator itr = arr.begin();
	for (int i = 0; itr != arr.end(); itr++, i++) (*itr) = i;
	for (itr = arr.begin(); itr != arr.end(); itr++)
		std::cout << *itr << std::endl;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 4; k++) {
				arr[i][j][k] = (i + 1) * (j + 1) * (k + 1) + arr[i][j][k];
			}
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 4; k++) {
				std::cout << i << " " << j << " " << k << " " << arr[i][j][k]
					<< std::endl;
			}
		}
	}
}