#include <iostream>
#include "HandlerLogin.h"
#include "Initializer.h"
#include "MemPoolObject.h"
#include <ctime>

#include "msgpack.h"
#pragma region 사용되는 패킷 선언
#include "..\..\..\Share\packet\PacketLogin.h"
#pragma endregion

using namespace std;

class Tmp : public MemPoolObject
{
	int p;
public:
	Tmp() {/* static int n = 0; printf("%d\n", ++n); p = n; */}
	~Tmp() {/* static int m = 0; printf("%d\n",--m); */}
	void print() {/* printf("saved : %d\n", p); */}

	Tmp(int t) { p = t; }
};

int main() {
	clock_t start = clock();
	Initialize();
	clock_t end = clock();
	printf("Initialize Time (%ldms)\n", (end - start));

	HandlerLogin la;
	int n = 74;

	PacketLogin pkt;
	pkt.sText = "Hello World!";

	// 실제로 패킷을 전송할 때는 PKT_ID / PKT_LENGTH / BYTE_STREAM 으로 전달이 됩니다.
	// STREAM_CONVERT는 pkt을 전달하면 pStream에 위의 내용대로 바이트 정보를 채웁니다.
	// 이 때 pStream의 길이는 nLength에서 저장하고 있게 됩니다.
	// Send를 하고 싶을 때에는 패킷을 STREAM_CONVERT로 바이트로 변환 후
	// pStream을 nLength만큼 전송하면 됩니다.

	STREAM_CONVERT(pkt, pStream, nLength);

	// 반대로 Recv를 하게 되었을 경우, pStream을 nLength만큼 정보를 받은 후, execute를 호출하세요.
	// 정해진 핸들러의 Do로 전달이 됩니다.
	// PACKET_CONVERT를 이용해 패킷으로 변환 후 사용하면 됩니다.
	HandlerBase::execute(pStream, nLength);
	
	delete[] pStream;
	
	cout << n << endl;
	{
		std::vector<std::shared_ptr<Tmp>> vec;
		for (int i = 0; i < n; i++)
		{
//			auto p = constructor<Tmp>();
			vec.push_back(std::shared_ptr<Tmp>(new Tmp()));// shared_ptr<Tmp>(MemoryPool::malloc<Tmp>(), destructor<Tmp>()));
		}
		for (int i = 0; i < (int)vec.size(); i++)
		{
			vec[i]->print();
		}
	}
	{
		std::shared_ptr<int> tt = std::shared_ptr<int>(MemoryPool::malloc<int>(124), destructor<int>());
		Tmp* arr = MemoryPool::malloc<Tmp>(100);
		std::string* arr2 = new std::string[100];
		for (int i = 0; i < 100; i++)
		{
			arr[i].print();
			arr2[i] = "Hello" + i;
		}
		MemoryPool::free(arr);
		delete[] arr2;
		// 중요! malloc<T>(size)로 하면, 선형적인 메모리가 잡힌다. 따라서 delete[] arr; 를 호출하게 되면 서버 크래시를 경험할 것이다.
		// ( new T[size] -> delete [] )가 맞고, ( malloc<T>(size)는 free(ptr) 이 맞다. 이 둘을 섞어쓰는 당신은 헬게이트가 오픈될지어니...
	}
	{
		for (int i = 0; i < 10; i++)
		{
			Tmp* arr = MemoryPool::malloc<Tmp>();
			arr->print();
			MemoryPool::free(arr);
		}
	}
	system("pause");
}
