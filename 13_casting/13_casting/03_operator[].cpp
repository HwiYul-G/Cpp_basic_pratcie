/*
	arr[1][2][3][4]
	arr[1]을 처리하면 첫 번째 차원으로 1을 선택했다는 정보가 담긴 어떤 객체 T를 리턴함
	(T)[2][3][4]가 수행된다. 이 T 또한 operaotr[]가 있어서 두 번째 차원으로 2를 선택했다는 정보가 담긴 객체 T'을 리턴한다.

	T'[3][4]가 되고 계속 진행하면 T''[4]가 되고 T'''이 된다.
	그리고 이 T'''이 int 타입이길 바라고 있다.

	이를 구현하려면 Array가 아닌 새로운 타입의 객체를 만들어야 한다.
	왜냐하면 operator[]가 Array& 타입이라면
	1차원 Array 배열에 대해서 arr[1] = 3;이란 문장이 불가능하기 때문이다.
	그렇다고 해서 operator[]가 int&을 리턴할 수도 없다.
	만일 int&를 리턴하면 1차원 배열인 arr[1]=3;은 잘 처리될 수 있지만 
	고차원 배열에서 arr[1][2] = 3;은 어떻게 처리할 수 있을까?
	arr[1]의 리턴 타입이 int&이라면 int에 대한 operator[]는 정의되어 있지도 않고 정의할 수도 없다.
	그렇다면 상황에 따라서 1차원이면 int를 그보다 고차원 배열이면 다른 것을 리턴하면 되지 않나? 할 수 있다.
	하지만 오버로딩의 원칙 상 동일한 인자를 받는 함수에 대해선 한 가지 리턴 타입만 가능하다.

	필요할 때 int처럼 작동하지만 int가 아닌 클래스를 만들 수 있었다.
	바로 int의 Wrapper 클래스였다.
	int의 Wrapper 클래스는 타입 변환 연산자를 제공해서 int와 연산을 수행하거나, 대입 등을 할 때
	마치 int처럼 작동하도록 만들 수 있다.
	그렇다면 우리는 operator[]가 int의 Wrapper 클래스 객체를 리턴해서 시제 int 값에 접근할 때는 int 변수처럼 행동하게 하고
	T나 T'처럼 원소에 접ㄱ느해 가는 중간 단계의 산물일 경우 그 중간 단게 정보를 포함한느 것으로 사용하면 된다.

	이런 생각을 바탕으로 int의 wrapper 클래스 Int의 얼개를 그려보면 아래와 같다.
	class Int{
		void* data;
		int level;
		Array* array;
	};

	level 정보를 반드시 가지고 있어야만 Int가 맨 마지막 '실제 int  정보를 포함하는 객체인지, 중간에 원소를 참조하는 과정인지 알 수 있다.

	예를 들어서 arr[1][2];를 생각해볼 때 arr[1]은 level이 1인 Int가 리턴된다.
	이때, 이는 int 데이터가 아니라 [1][2]를 참조해 나가기 위한 중간 과정이다.
	(이것을 Int가 구별하는 방법은 Int가 가지고 있는 int의 dim 정보를 참조하면 된다.)

	이때 Int에는 '현재 arr[1]를 가리키고 있음'에 대한 정보가 Int의 data에 들어가 있다.
	그 다음에 operaotr[]를 수행하게 된다면(따라서 Int 클래스의 operator[]역시 만들어야 함)
	이번에는 level 2인 Int가 리턴된다.
	사용자가 level 2인 Int에 대입 연산을 하게 된다면, 
	void* data를 int 원소를 가리키고 있는 주소로 해석해서 실제로 int형 변수처럼 대입이 수행 된다.

	참고로 array는 어떤 배열의 Int 인지 가리키는 역할을 한다.

	먼저 Int의 생성자는 아래와 같이 구성할 수 있다.
	Int(int index, int _level = 0, void* _data = NULL, Array* _array = NULL)
		: level(_level), data(_data), array(_array) {
		if(_level < 1 || index >= array->size[_level -1]){
			data = NULL;
			return;
		}
		if (level == array->dim) {
			// 이제 data 에 우리의 int 자료형을 저장하도록 해야 한다.
			data = static_cast<void *>(
			  (static_cast<int *>(static_cast<Array::Address *>(data)->next) + index));
		  } else {
			// 그렇지 않을 경우 data 에 그냥 다음 addr 을 넣어준다.
			data = static_cast<void *>(
			  static_cast<Array::Address *>(static_cast<Array::Address *>(data)->next) +
			  index);
		  }
	};
*/

#include <iostream>

namespace MyArray {
	// 네임스페이스 위에 클래스를 선언해 놓지 않으면
	// Array 클래스에서 friend Int;를 할 수 없게 된다.
	// 왜냐하면 컴파일러 입장에서 Int가 무엇인지 알 수 없기 대문이다.
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


	/*
		Array 클래스 안에 넣지 않고 이 부분을 따로 배놓은 것은 Int를 실제로 '이용'하기 위해선
		클래스의 선은 만으론 충분하지 않기 때문이다.

		클래스 선언을 통해선 클래스의 내부 정보가 필요 없는 것들 
		예를 들면 friend 선언이나 클래스의 포인터 정의 등의 행동만 가능하고 
		
		Array처럼 구체적으로 Int 클래스 내부 정보(생성자)를 사용하는 경우엔 
		반드시 Int 클래스의 정의가 선행되어야 한다.
		따라서 어쩔 수 없이 Array클래스의 operator[]만 따로 배놓았다.
	*/
	Int Array::operator[](const int index) {
		return Int(index, 1, static_cast<void*>(top), this);
	}
}

int main() {
	int size[] = { 2,3,4 };
	MyArray::Array arr(3, size);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 4; k++) {
				arr[i][j][k] = (i + 1) * (j + 1) * (k + 1);
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

	return 0;
}