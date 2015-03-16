#include <list>

template <class T>
class LockFreeQueue {
	LockFreeQueue();
	void Enqueue(const T& t);
	T Dequeue(T& t);
private:
	typedef std::list<T> TList;
	TList list;
	typename TList::iterator iHead, iTail;	
};