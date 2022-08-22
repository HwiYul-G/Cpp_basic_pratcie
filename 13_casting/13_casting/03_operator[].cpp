/*
	arr[1][2][3][4]
	arr[1]�� ó���ϸ� ù ��° �������� 1�� �����ߴٴ� ������ ��� � ��ü T�� ������
	(T)[2][3][4]�� ����ȴ�. �� T ���� operaotr[]�� �־ �� ��° �������� 2�� �����ߴٴ� ������ ��� ��ü T'�� �����Ѵ�.

	T'[3][4]�� �ǰ� ��� �����ϸ� T''[4]�� �ǰ� T'''�� �ȴ�.
	�׸��� �� T'''�� int Ÿ���̱� �ٶ�� �ִ�.

	�̸� �����Ϸ��� Array�� �ƴ� ���ο� Ÿ���� ��ü�� ������ �Ѵ�.
	�ֳ��ϸ� operator[]�� Array& Ÿ���̶��
	1���� Array �迭�� ���ؼ� arr[1] = 3;�̶� ������ �Ұ����ϱ� �����̴�.
	�׷��ٰ� �ؼ� operator[]�� int&�� ������ ���� ����.
	���� int&�� �����ϸ� 1���� �迭�� arr[1]=3;�� �� ó���� �� ������ 
	������ �迭���� arr[1][2] = 3;�� ��� ó���� �� ������?
	arr[1]�� ���� Ÿ���� int&�̶�� int�� ���� operator[]�� ���ǵǾ� ������ �ʰ� ������ ���� ����.
	�׷��ٸ� ��Ȳ�� ���� 1�����̸� int�� �׺��� ������ �迭�̸� �ٸ� ���� �����ϸ� ���� �ʳ�? �� �� �ִ�.
	������ �����ε��� ��Ģ �� ������ ���ڸ� �޴� �Լ��� ���ؼ� �� ���� ���� Ÿ�Ը� �����ϴ�.

	�ʿ��� �� intó�� �۵������� int�� �ƴ� Ŭ������ ���� �� �־���.
	�ٷ� int�� Wrapper Ŭ��������.
	int�� Wrapper Ŭ������ Ÿ�� ��ȯ �����ڸ� �����ؼ� int�� ������ �����ϰų�, ���� ���� �� ��
	��ġ intó�� �۵��ϵ��� ���� �� �ִ�.
	�׷��ٸ� �츮�� operator[]�� int�� Wrapper Ŭ���� ��ü�� �����ؼ� ���� int ���� ������ ���� int ����ó�� �ൿ�ϰ� �ϰ�
	T�� T'ó�� ���ҿ� �������� ���� �߰� �ܰ��� �깰�� ��� �� �߰� �ܰ� ������ �����Ѵ� ������ ����ϸ� �ȴ�.

	�̷� ������ �������� int�� wrapper Ŭ���� Int�� �󰳸� �׷����� �Ʒ��� ����.
	class Int{
		void* data;
		int level;
		Array* array;
	};

	level ������ �ݵ�� ������ �־�߸� Int�� �� ������ '���� int  ������ �����ϴ� ��ü����, �߰��� ���Ҹ� �����ϴ� �������� �� �� �ִ�.

	���� �� arr[1][2];�� �����غ� �� arr[1]�� level�� 1�� Int�� ���ϵȴ�.
	�̶�, �̴� int �����Ͱ� �ƴ϶� [1][2]�� ������ ������ ���� �߰� �����̴�.
	(�̰��� Int�� �����ϴ� ����� Int�� ������ �ִ� int�� dim ������ �����ϸ� �ȴ�.)

	�̶� Int���� '���� arr[1]�� ����Ű�� ����'�� ���� ������ Int�� data�� �� �ִ�.
	�� ������ operaotr[]�� �����ϰ� �ȴٸ�(���� Int Ŭ������ operator[]���� ������ ��)
	�̹����� level 2�� Int�� ���ϵȴ�.
	����ڰ� level 2�� Int�� ���� ������ �ϰ� �ȴٸ�, 
	void* data�� int ���Ҹ� ����Ű�� �ִ� �ּҷ� �ؼ��ؼ� ������ int�� ����ó�� ������ ���� �ȴ�.

	����� array�� � �迭�� Int ���� ����Ű�� ������ �Ѵ�.

	���� Int�� �����ڴ� �Ʒ��� ���� ������ �� �ִ�.
	Int(int index, int _level = 0, void* _data = NULL, Array* _array = NULL)
		: level(_level), data(_data), array(_array) {
		if(_level < 1 || index >= array->size[_level -1]){
			data = NULL;
			return;
		}
		if (level == array->dim) {
			// ���� data �� �츮�� int �ڷ����� �����ϵ��� �ؾ� �Ѵ�.
			data = static_cast<void *>(
			  (static_cast<int *>(static_cast<Array::Address *>(data)->next) + index));
		  } else {
			// �׷��� ���� ��� data �� �׳� ���� addr �� �־��ش�.
			data = static_cast<void *>(
			  static_cast<Array::Address *>(static_cast<Array::Address *>(data)->next) +
			  index);
		  }
	};
*/

#include <iostream>

namespace MyArray {
	// ���ӽ����̽� ���� Ŭ������ ������ ���� ������
	// Array Ŭ�������� friend Int;�� �� �� ���� �ȴ�.
	// �ֳ��ϸ� �����Ϸ� ���忡�� Int�� �������� �� �� ���� �빮�̴�.
	class Array;
	class Int;

	class Array {
		friend Int;

		const int dim;
		int* size; // size[0] * size[1] * ... * size[dim-1] ¥�� �迭

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
				// data�� int �� �ڷ����� �����ϰ� �ؾ���
				data = static_cast<void*>((
					static_cast<int*>(static_cast<Array::Address*>(data)->next) + index));
			}
			else {
				// �׷��� ���� ��� data�� ���� addr�� ����
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
		Array Ŭ���� �ȿ� ���� �ʰ� �� �κ��� ���� ����� ���� Int�� ������ '�̿�'�ϱ� ���ؼ�
		Ŭ������ ���� ������ ������� �ʱ� �����̴�.

		Ŭ���� ������ ���ؼ� Ŭ������ ���� ������ �ʿ� ���� �͵� 
		���� ��� friend �����̳� Ŭ������ ������ ���� ���� �ൿ�� �����ϰ� 
		
		Arrayó�� ��ü������ Int Ŭ���� ���� ����(������)�� ����ϴ� ��쿣 
		�ݵ�� Int Ŭ������ ���ǰ� ����Ǿ�� �Ѵ�.
		���� ��¿ �� ���� ArrayŬ������ operator[]�� ���� ����Ҵ�.
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