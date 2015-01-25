#include <iostream>
#include "HandlerLogin.h"
#include "Initializer.h"
#include "MemPoolObject.h"
#include <ctime>

#include "msgpack.h"
#pragma region ���Ǵ� ��Ŷ ����
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

	// ������ ��Ŷ�� ������ ���� PKT_ID / PKT_LENGTH / BYTE_STREAM ���� ������ �˴ϴ�.
	// STREAM_CONVERT�� pkt�� �����ϸ� pStream�� ���� ������ ����Ʈ ������ ä��ϴ�.
	// �� �� pStream�� ���̴� nLength���� �����ϰ� �ְ� �˴ϴ�.
	// Send�� �ϰ� ���� ������ ��Ŷ�� STREAM_CONVERT�� ����Ʈ�� ��ȯ ��
	// pStream�� nLength��ŭ �����ϸ� �˴ϴ�.

	STREAM_CONVERT(pkt, pStream, nLength);

	// �ݴ�� Recv�� �ϰ� �Ǿ��� ���, pStream�� nLength��ŭ ������ ���� ��, execute�� ȣ���ϼ���.
	// ������ �ڵ鷯�� Do�� ������ �˴ϴ�.
	// PACKET_CONVERT�� �̿��� ��Ŷ���� ��ȯ �� ����ϸ� �˴ϴ�.
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
		// �߿�! malloc<T>(size)�� �ϸ�, �������� �޸𸮰� ������. ���� delete[] arr; �� ȣ���ϰ� �Ǹ� ���� ũ���ø� ������ ���̴�.
		// ( new T[size] -> delete [] )�� �°�, ( malloc<T>(size)�� free(ptr) �� �´�. �� ���� ����� ����� �����Ʈ�� ���µ������...
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
