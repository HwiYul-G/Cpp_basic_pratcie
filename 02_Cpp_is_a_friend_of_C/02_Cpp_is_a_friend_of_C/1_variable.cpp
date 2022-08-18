/*
	C���� �ۼ��� �ڵ带 �״�� C++�� �ٿ��ֱ� �ص� ������ �����ص� ������ �ƴϴ�.
	�� ������ C++�� C����� ������ ���� ������ �����Ѵ�.
	���� C�� ��� �ڵ尡 C++ �ڵ忡 ������ �Ǵ� ���� �ƴϴ�.
	C �����Ϸ��δ� ������ ������ C++ �����Ϸ��δ� ���� �ʴ� ��ҵ��� �ִ�.
*/
#include <iostream>
int main() {
	int i;
	char c;
	double d;
	float f;

	return 0;
}
/*
	������ �����ϴ� �κ��� C��� ���� �޶��� ���� ����.
	�׷��� ���� ������(�̸��� C++ ��Ÿ�� ������)�� ����
	https://google.github.io/styleguide/cppguide.html#Variable_Names�� ������ ����.

	std::string table_name; // lowercase with underscore.
	
	class TableInfo{
		private:
			std::string table_name_; // OK - underscore at end
			static Pool<TableInfo>* pool_; // OK
	};

	struct UrlTableProperties{
		std::string name; // do not have the trailing underscores
		int num_entries;
		static Pool<UrlTableProperties>* pool;
	};

	// const or constexpró�� '������' ���� k�� �����Ѵ�. 
	// _�� �и��� �幰�� ����Ѵ�. 
	const int kDaysInAWeek = 7;
	const int KAndroid8_0_0 = 24; // Android 8.0.0

	accessors�� mutators�� ������ ���� ����� �� �ִ�.
	���� �Լ��� ī�����̽��̴�.
	AddTableEntry();
	DeleteUrl();
	
	����� ��Ģ�� �ִ�.
*/
