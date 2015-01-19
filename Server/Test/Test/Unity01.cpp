#include "MemoryPool.cpp"
#include "Test.cpp"

/*
빌드끼리의 종속성이 얽힌 파일들을 정리하는 곳입니다. 잘 신경써서 빌드간의 꼬임을 방지합시다.

선빌드파일				후빌드파일					사유	
MemoryPool.cpp			Test.cpp					메모리 풀 외부 참조 적용 후 Test.cpp 실행	(MemoryPool.cpp 를 dll로 바꿔서 포함시켜버리면 이 문제가 해결될거 같은데...)

*/