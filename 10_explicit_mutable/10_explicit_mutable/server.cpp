/*
	mutable이 왜 필요한가?
	대부분의 경우 의미상 상수 작업을 하는 경우, 실제로도 상수 작업을 한다.
	하지만 실제로 꼭 그렇지만은 않다.
*/

/*
    class Server {
      // .... (생략) ....

      // 이 함수는 데이터베이스에서 user_id 에 해당하는 유저 정보를 읽어서 반환한다.
      User GetUserInfo(const int user_id) const {
        // 1. 데이터베이스에 user_id 를 검색
        Data user_data = Database.find(user_id);

        // 2. 리턴된 정보로 User 객체 생성
        return User(user_data);
      }
    };

*/
/*
    이 서버에는 GetUserInfo라는 함수가 있는데 입력받은 user_id로
    db에서 해당 유저를 조회해서 그 유저의 정보를 리턴하는 함수이다.

    당연히도 db를 업데이트 하지 않고 무언가 수정하는 작업도 당연히 없기에 const 함수로 선언되어 있다.

    그런데 보통 db에 요청한 후 받아오는 작업은 꽤 오래 걸린다.
    그래서 보통 서버들의 경우 메모리에 캐시(cache)를 만들어서 자주 요청되는 데이터를
    굳이 db까지 가서 찾지 않아도 메모리에서 빠르게 조회할 수 있도록 한다. 

    물론 캐시는 db만큼 그지 않아서 일부 유저들의 정보만 포함한다.
    따라서 캐시에 해당 유저가 없으면(cache miss나면) 데이터베이스에 직접 요청해야한다.
    대신 db에서 유저 정보를 받으면 캐시에 저장해놓아서
    다음에 요청할 때 빠르게 받을 수 있게 된다.

    보통 한 번 요청된 정보는 계속해서 요청될 확률이 높기 때문에 캐시에 높게된다.
    물론 캐시 크기는 한정적이니까 이전에 왜래된 캐시부터 지우게 된다.

    이를 구현 하면 아래와 같다.
*/
/*
    class Server {
        // .... (생략) ....

        Cache cache; // 캐쉬!

        // 이 함수는 데이터베이스에서 user_id 에 해당하는 유저 정보를 읽어서 반환한다.
        User GetUserInfo(const int user_id) const {
            // 1. 캐쉬에서 user_id 를 검색
            Data user_data = cache.find(user_id);

            // 2. 하지만 캐쉬에 데이터가 없다면 데이터베이스에 요청
             if (!user_data) {
                user_data = Database.find(user_id);

                // 그 후 캐쉬에 user_data 등록
                cache.update(user_id, user_data); // <-- 불가능
            }

           // 3. 리턴된 정보로 User 객체 생성
            return User(user_data);
        }
    };
*/

/*
    그런데 문제는 GetuserInfo가 const 함수이다.
    따라서 아래와 같은 캐시를 업데이트 하는 작업은 불가능하다.
    cache.update(user_id, user_data); // <-- 불가능
    왜냐하면 캐시를 업데이트 한다는 것은 캐시 내부의 정보를 바꿔야하는 것이기 때문이다.
    따라서 이 update 함수는 const 함수가 아닐 것이다.

    그렇다고 해서 GetUserInfo에서 const를 제거하기는 좀 그렇다.
    이 함수를 사용하는 사용자 입장에선 당연히 const로 정의되어야하는 함수이기 때문이다.
    따라서 이 경우, Cache를 mutalbe로 선언하면 된다.

    mutable Cache cache;  // 캐쉬!
    이렇게!

    이렇게 하면 mutable 키워드는 const 함수 안에서 해당 멤버 변수에 cosnt가 아닌 작업을 할 수 있게 만들어 준다.
*/