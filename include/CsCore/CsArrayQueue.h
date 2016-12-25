/*队列的抽象数据类型*/
template <typename T>
class ArrayQueue
{
public:
	//构造函数
	ArrayQueue(int s) : maxsize(s), begin(0), end(0), array(NULL) {
		array = new T[maxsize];
	}
	//析构函数
	~ArrayQueue()
	{
		delete[]array;
	}


	T front();          //对首元素
	bool pop();         //出对
	bool push(T t);     //入队
	bool isEmpty();     //判空
	int size();         //队列的大小
private:
	int begin;      //对首元素
	int end;        //对尾
	T *array;       //数组
	int maxsize;    //容量
};

template <typename T>
T ArrayQueue<T>::front()
{
	if (begin != end)
		return array[begin];
};

template <typename T>
bool ArrayQueue<T>::pop()
{
	if (begin == end)
		return false;
	begin = (begin + 1) % maxsize;
	return true;
};

template <typename T>
bool ArrayQueue<T>::push(T t)
{
	if ((end + 1) % maxsize == begin)
		return false;
	array[end] = t;
	end = (end + 1) % maxsize;
	return true;
};

template <typename T>
bool ArrayQueue<T>::isEmpty()
{
	if (begin == end)
		return true;
	else
		return false;
};

template <typename T>
int ArrayQueue<T>::size()
{
	return (end - begin + maxsize) % maxsize;
};