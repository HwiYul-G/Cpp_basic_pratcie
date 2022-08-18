/*
	memory management is always important.
	the address values of all variables had to be fixed at compile time 
	in order to run program correctly.

	�̸� ���ؼ� ���� ������ ������ ������
	���α׷� ���� �� �����Ӱ� �Ҵ��ϰ� ������ �� �ִ� heap�̶� ������ �����.

	������ ������ �����Ϸ��� ���� ������� �������� ����Ǵ� stack�� �޸�
	���� ����ڰ� ������ �����ؾ��ϴ� �κ��� ��ŭ å���� ������.

	C���� malloc�� free �Լ��� ������ �� �󿡼� �޸��� �Ҵ��� �����ߴ�.
	C++���� malloc�� freee �Լ��� �̿��� �� �ִ�.

	������ ��� �������� �����ϴ� ���� �ٷ� new�� delete�̴�.
	new�� �� �״�� malloc�� �����Ǵ� ������ �޸𸮸� �Ҵ��ϰ� delete�� free�� �����Ǵ� ������ �޸𸮸� �����Ѵ�.

	�� ������ ����.
*/
#include <iostream>
int main() {
	int* p = new int;	// int ũ���� ������ �Ҵ��� �� �ּҰ��� p�� �������
	*p = 10;

	std::cout << *p << std::endl;

	delete p;	// p�� �Ҵ�� ������ ������

	/*
		delete�� ���ؼ��� ����ڰ� new�� ���� �Ҵ��� ������ ������ �����ϴ�.
		���� �Ʒ��� ���� ���������� �����ϰ� delete �Ϸ��� �ϸ�
		#include <iostream>
		int main() {
		  int a = 5;
		  delete &a;
		  return 0;
		}
		Heap�� �ƴ� ������ �����Ϸ� �ߴٴ� ��� �޽����� ���´�.

	*/
	return 0;
}