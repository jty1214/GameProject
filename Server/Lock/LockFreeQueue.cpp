#include "LockFreeQueue.h"

template <class T>
LockFreeQueue<T>::LockFreeQueue()
{
	//list.push_back(T());
	iHead = list.begin();
	iTail = list.end();
}

template <class T>
void LockFreeQueue<T>::Enqueue(const T& t) {
	list.push_back(t);
	iTail = list.end();
	list.erase(list.begin(), iHead);
}

template <class T>
T LockFreeQueue<T>::Dequeue(T& t) {
	T tmp;
	while (true) {
		typename TList::iterator *iptr = iHead;
		typename TList::iterator iNext = ++iptr;
		
		if (iHead == iptr) {
			iHead = iNext;
			break;
		}
	}

	tmp = iptr;

	return tmp;
	/*typename TList::iterator iNext = iHead;
	++iNext;
	if (iNext != iTail)
	{
		iHead = iNext;
		t = *iHead;
		return true;
	}
	return false;
	*/
}