/*
	C언어에서 작성된 코드를 그대로 C++에 붙여넣기 해도 문제가 없다해도 과언이 아니다.
	그 정도로 C++은 C언어의 문법을 거의 완전히 포함한다.
	물론 C의 모든 코드가 C++ 코드에 컴파일 되는 것은 아니다.
	C 컴파일러로는 컴파일 되지만 C++ 컴파일러로는 되지 않는 요소들이 있다.
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
	변수를 정의하는 부분은 C언어 때와 달라진 것이 없다.
	그래도 좋은 변수명(이른바 C++ 스타일 변수명)을 위해
	https://google.github.io/styleguide/cppguide.html#Variable_Names을 보도록 하자.

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

	// const or constexpr처럼 '고정된' 값은 k로 시작한다. 
	// _는 분리를 드물게 사용한다. 
	const int kDaysInAWeek = 7;
	const int KAndroid8_0_0 = 24; // Android 8.0.0

	accessors나 mutators는 변수와 같이 사용할 수 있다.
	보통 함수는 카멜케이스이다.
	AddTableEntry();
	DeleteUrl();
	
	등등의 규칙이 있다.
*/
