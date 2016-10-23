/*
1. 맵(Map)이란?

 맵(Map)은 set, multiset, multimap등과 같이 STL이 제공하는 자료형 중 하나이다. 


 2. 맵(Map)의 특징

  첫번째, 두 개의 요소가 한 쌍을 이루어 하나의 자료를 이룬다.  첫 번째 요소는 first로써 인덱스이고, 두 번째 요소는 second로써 데이터이다. 그러므로, 인덱스와 데이터가 분리된 상태이며 독립적으로 자료형을 지정해줄 수 있다.

  두번째, 반복자(iterator)와 배열 첨자를 사용하여 접근할 수 있다.
   
   세번째, 자동적으로 정렬된 상태를 유지한다. 만약에 정렬할 수 없다면 출력 순서는 먼저 입력된 것이 가장 나중에 출력된다.

    네번째, 인덱스가 중복되서 추가를 한다면, 기존의 데이터는 없어지고 새로운 데이터로 덮어씌여진다.

	 다섯번째, Template를 사용하여, 인덱스나 데이터나 형식에 대하여 자유롭다.


	 3. 선언 방법

	   map<인덱스형식,데이터형식> 사용할이름; 과 같이 선언하면 된다.
Example : map<int, string> iMapt;


4. 접근 방법

 접근 방법엔 두 가지가 있다. 

  ㄱ. iterator를 사용한 접근 방법.
  map<인덱스형식,데이터형식>::iterator iterator이름; 과 같이 iterator를 선언 한 후, 사용한다. 접근 방법은 iterator->first, iterator->second와 같은 형식으로 접근한다.

   ㄴ. 인덱스 요소를 이용하여 접근할 수 있다.


   5. 요소 추가, 삭제 방법

    추가를 하고 싶다면 map[인덱스]=데이터; 식으로 추가를 해주자. 물론, 인덱스에는 문자열이 와도 된다.
	 그리고 삭제를 하고 싶다면 map.erase(인덱스)와 같이 삭제은 방법으로 인덱스를 통하여 삭제를 할 수 있다.
*/


#include <map>
#include <string>
#include <stdio.h>

using namespace std;

int main()
{
	map<int, string> iMap;

	iMap[5] = "5번요소의 데이터"; //요소에 대한 데이터를 임의 순서로 추가
	iMap[3] = "3번요소의 데이터";
	iMap[9] = "9번요소의 데이터";

	map<int, string>::iterator itMap;

	printf("iMap\n"); 
	for(itMap = iMap.begin(); itMap != iMap.end(); itMap++)
		printf("%d : %s\n",itMap->first, itMap->second.c_str()); //정렬된 상태
	printf("\n");

	iMap[9] = "안녕하세요!"; //덮어 씌우기

	printf("iMap\n");
	for(itMap = iMap.begin(); itMap != iMap.end(); itMap++)
		printf("%d : %s\n",itMap->first, itMap->second.c_str());
	printf("\n");

	printf("iMap[5] = %s\n\n",iMap[5].c_str()); //인덱스를 통한 접근

	map<char*, string> sMap; //char*과 string 둘다 문자열이지만
	//char*는 정렬되지 않는다.

	sMap["미국"] = "United State of America";
	sMap["중국"] = "China";
	sMap["일본"] = "Japan";
	sMap["한국"] = "Korea, Republic";

	map<char*, string>::iterator itStrMap;

	printf("sMap\n");
	for(itStrMap = sMap.begin(); itStrMap != sMap.end(); itStrMap++)
		printf("%s : %s\n",itStrMap->first, itStrMap->second.c_str()); 
	printf("\n"); //마지막으로 넣은 한국이 가장 먼저 출력됨

	sMap.erase("일본"); //일본을 삭제

	printf("sMap\n");
	for(itStrMap = sMap.begin(); itStrMap != sMap.end(); itStrMap++)
		printf("%s : %s\n",itStrMap->first, itStrMap->second.c_str());
	printf("\n");
}
