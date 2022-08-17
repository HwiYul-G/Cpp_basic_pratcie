#include <iostream>
/*
	C++������ ���ӽ����̽��� ���� �̸��� �������� �ʾƵ� �ȴ�.

	�� ��� �ش� ���ӽ����̽��� ���ǵ� �͵��� �ش� ���� '��'������ ������ �� �ְ� �ȴ�.
	�� ��� ��ġ static�� �̿��� �Ͱ� ���� ȿ���� ����.
*/

namespace {
	// �� �Լ��� �� ���� �ȿ����� ����� �� �ִ�.
	// �̴� ��ġ static int OnlyInThisfile() �� �����ϴ�.
	int OnlyInThisFile() {}

	// �� ���� ���� static int x; �� �����ϴ�.
	int only_in_this_file = 0;
} // namespace

int main() {
	OnlyInThisFile();
	only_in_this_file = 3;
	return 0;
}