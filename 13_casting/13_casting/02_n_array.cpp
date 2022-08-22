/*
	N���� �迭 �����
	arr[x1][x2]...[xn]

	1) x1 * x2 * ... * xn ũ���� 1���� �迭�� �Ҵ��� �� ������ �� ��Ȯ�� ��ġ�� ã�ƺ�
	-> �޸𸮵� ��Ȯ�� �ʿ��� ��ŭ�� ����� �� �־ ���� ���

	2) 2���� �迭�� �����Ҵ��� ������ �� �ߴ� idea
		������ �޸𸮻� �迭ó�� �������� ������ �������� �迭�� ���

		int** arr = new int*[x1];
		for(int i = 0; i<x1; i++) arr[i] = new int[x2];

		�̷��� �ϸ� int arr[x1][x2]�� �� �Ͱ� ������ ȿ���� �� �� �ִ�.
		������ ������ ��ü�� ��ƸԴ� ũ�� ������ x1*x2 + 1��ŭ�� �޸𸮸� ��Ƹ԰� �ȴ�.

		������ �޸𸮰� ����ϴ� �� ũ�Ⱑ �ſ� ū �迭�� ������ �� �ִ�.
		1) ����� ��� ��ü �迭�� ���Ҽ��� int ũ�⸦ �Ѿ��, 
		���� ū ���� ������ �ٷ� �� �ִ� ���̺귯���� ����ؼ� �޸𸮸� �������� �Ҵ��� �־���Ѵ�.

		������ 2) ����� ��� ��ü ���� ���� �ƴ϶� �� ������ ���� int ũ�⸸ �Ѿ�� ������ �ȴ�.
		�� (intũ��)^n ���� ���Ҹ� ����� �� �ִ�.
		3���� �迭�� ��� 2^96�� �ȴ�.

		���⼭ �������� ������� �迭�� ������ ��� ����� �迭�� �ƴ϶�, N ���� �迭�̶�� ���̴�.
		���� 3���� �迭�� ������ٸ� int***�� ������� ���̰� 4������ int****�� �̿����� ���̴�.
		������ N���� �迭�� ��� N���� *�� �� �����͸� ������ ���� ���� ���̴�.

		������ ��¦ ������ �ٲٸ� ���� �ذ��� �� �ִ�.
		�����͸� �̿��ϴ� ���� �ܼ��� ���� ������ �迭�� ����Ű�� �����̶�� ���� N �����͸� ������� �ʾƵ� �Ǳ� �����̴�.
*/

// n���� �迭�� ��� level0���� level n���� �ְ� level n-1���� Address ��ü�� �����ϰ� level n�� �������� �����͸� ������

class Array {
	const int dim; // �� ���� �迭����
	int* size;
	
	/*
		�ܺο� Array �迭�� ���������� ��� �۵��ϴ� �� �����ϰ� ���� �ʰ�
		���� ������ �����ϴ� ���� ��ġ �ʾƼ� Array Ŭ���� ���� Address ����ü�� ����
	*/
	struct Address {
		int level;
		// �� ������ ����(dim - 1 ����) �� ������ �迭�� ����Ű��, �� �� ����
		// ���������� ���� Address �迭�� ����Ų��.
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
		�������� 2���� �迭�� �������� ��ó�� for������ ������ ������ �� ����.
		for ���� �����ϱ� ���ؼ� �� �� for���� ������� ������ �� ���������ϴµ�
		�� ��� N������ ������ �����̹Ƿ� �׷� �� ����.

		�̸� �ذ��ϴ� ���� ���� ���̵��� '��� �Լ�'�� �̿��ϴ� ���̴�.
		����Լ��� �����ϴ� �� ���� ������ �ִµ�
		1) �Լ����� ó���ϴ� ��, �� ���� �ܰ迡�� ���� �ܰ�� �Ѿ�� ������ �����ΰ�?
		2) ��� ȣ���� ����Ǵ� ������ �����ΰ�?

		2)�� ���� �ش��� ���� ó���ϰ� �ִ� Address �迭�� ������ (dim-1)�̸� �ȴ�.
		�� Address �迭�� ������ (dim-1)�̸� �� �迭�� ���ҵ��� next���� int�� �迭�� �����Ͱ� ��
		��� ȣ���� ������ �ȴ�.

		1)�� ���� ��(����-> ���� ����)�� �����ϱ�?
		���� n������ Address �迭�̶�� �̵��� next�� ���� ������ n+1 ������ Address �迭�� �������ְ�
		���� �� ���ҿ� ���� ó�����ָ� �ȴ�.
	*/

	void initialize_address(Address* current) {
		if (!current) return; // current�� NULL�� ��
		if (current->level == dim - 1) {
			current->next = new int[size[current->level]];
			return;
		}
		current->next = new Address[size[current->level]];
		for (int i = 0; i != size[current->level]; i++) {  // ���� �ܰ�� �Ѿ�� ����
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