/*基于链表的队列的ADT*/
template <typename T>
class LinkQueue
{
public:
	LinkQueue() : phead(GNULL), pend(GNULL), count(0){
		phead = new Node<T>();
		pend = phead;
		count = 0;
	}

	T front();          //对首元素
	bool pop();         //出对
	bool push(T t);     //入队
	bool isEmpty();     //判空
	int size();         //队列的大小
private:
	Node<T>* phead;
	Node<T>* pend;
	int count;    //队列元素的数量
};

template <typename T>
T LinkQueue<T>::front()
{
	if (count != 0)
		return phead->next->value;
};

template <typename T>
bool LinkQueue<T>::pop()
{
	if (count == 0)
		return false;
	Node<T>* pdel = phead->next;
	phead->next = pdel->next;
	delete pdel;
	count--;
	return true;
};

template <typename T>
bool LinkQueue<T>::push(T t)
{
	Node<T>* pnode = new Node<T>(t);
	pend->next = pnode;
	pend = pnode;
	count++;
	return true;
};

template <typename T>
bool LinkQueue<T>::isEmpty()
{
	if (count == 0)
		return true;
	else
		return false;
};

template <typename T>
int LinkQueue<T>::size()
{
	return count;
};