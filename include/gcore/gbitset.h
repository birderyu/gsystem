// 位操作封装类
#ifndef _CORE_BIT_SET_H_
#define _CORE_BIT_SET_H_

#include "gtype.h"

namespace gsystem { // gsystem

template<gsize SIZE>
class GBitSet
{
public:
	GBitSet(gulong n = 0);
	GBitSet(const GBitSet<SIZE> &bitset);
	GBitSet(GBitSet<SIZE> &&bitset);

	gbool GetAt(gsize pos) const;
};

} // namespace gsystem

#include<cassert>  // assert  
#include<cstddef>   // std::size_t  
#include<string>   // std::string   
#include<cstring>   // std::memset  
#include<exception>     
#include<iostream>  

#ifdef __cplusplus  
namespace mystd {
	typedef std::size_t size_type;

	unsigned char get_true(size_type index) // 1 - 8  
	{
		assert(index >= 1 && index <= 8);
		return (unsigned char)1 << (index - 1);
		// 得到形如00010000这样的数  
	}
	unsigned char get_false(size_type index)
	{
		assert(index >= 1 && index <= 8);
		return ~get_true(index);
		// 得到形如11101111这样的数  
	}

	void set_false(unsigned char& val, size_type index) // index (1 - 8)  
	{
		assert(index >= 1 && index <= 8);
		val &= get_false(index);
	}
	void set_true(unsigned char& val, size_type index) // index (1 - 8)   
	{
		assert(index >= 1 && index <= 8);
		val |= get_true(index);
	}

	void* set(void* ptr, size_type pos, bool val = true)
	{   //一般性的函数，处理数组中单个值的单个bit的设定  
		assert(ptr != 0);
		unsigned char *pointer = (unsigned char*)ptr;
		size_type subpos = (pos + 7) / 8 - 1;
		size_type index = (pos + 7) % 8 + 1;
		if (val)
			set_true(pointer[subpos], index);
		else
			set_false(pointer[subpos], index);
		return ptr;
	}

	bool read(void *ptr, size_type pos)
	{
		assert(ptr != 0);
		unsigned char *pointer = (unsigned char*)ptr;
		size_type subpos = (pos + 7) / 8 - 1;
		size_type index = (pos + 7) % 8 + 1;
		unsigned char tmp_val = (pointer[subpos] >> (index - 1)) & unsigned char(1);
		return tmp_val > 0;
	}

	class  invalid_argument_1 {};

	template<std::size_t N>
	class bitset {
	private:
		typedef bitset self;
		typedef std::size_t size_type;
		typedef unsigned long ULONG;
		typedef unsigned long long ULLONG;
		typedef unsigned char UCHAR;
	private:
		class ref {  //写一个辅助类，因为c++无法对单个的位进行索引，  
					 // c++之父在<<c++程序设计语言>>（十周年纪念版436页）中有提到这一技术，但是只有接口，没有实现，  
					 // 这个是我的一个实现，当然接口不太一样，我有所改变  
		private:
			typedef std::size_t size_type;
			typedef ref self;
			UCHAR *head;
			size_type position;
		public:
			ref(UCHAR* tmp_ptr, size_type pos) :head(tmp_ptr), position(pos)
			{
			}
		public:
			self& operator = (const self& tmp)
			{//mystd::set的pos以1开始计数,因此加1,以下都是如此  
				mystd::set(head, position + 1, mystd::read(tmp.head, tmp.position + 1));
				return *this;
			}
			self& operator = (const bool& tmp)
			{
				assert(head != 0);
				mystd::set(head, position + 1, tmp);
				return *this;
			}
			bool operator == (const bool& tmp) const
			{
				assert(head != 0);
				return mystd::read(head, position + 1) == tmp;
			}
			bool operator != (const bool& tmp) const
			{
				assert(head != 0);
				return !(*this == tmp);
			}
			bool operator == (const self& tmp) const
			{
				assert(head != 0);
				return mystd::read(head, position + 1) ==
					mystd::read(tmp.head, tmp.position + 1);
			}
			bool operator != (const self& tmp) const
			{
				return !(*this == tmp);
			}

			friend std::ostream& operator << (std::ostream& os, const self& tmp)
			{
				return os << mystd::read(const_cast<UCHAR*>(tmp.head), tmp.position + 1);
			}
			friend std::istream& operator >> (std::istream& is, self& tmp)
			{ // 标准库无此功能,感觉应该加上，个人见解，呵呵！  
				bool tmp_val = false;
				is >> tmp_val;
				mystd::set(tmp.head, tmp.position + 1, tmp_val);
				return is;
			}
		};

	private:
		typedef ref reference;
		typedef const ref const_reference;
		static const size_type SIZE = N;
		UCHAR *head;
	private:   //内部使用的一些函数  
		bool read(void *ptr, size_type pos) const   // 从0开始  
		{ // mystd里的read以1开始计数，在这里转换下,以下同理可得  
			return mystd::read(ptr, pos + 1);
		}
		void* set(void* ptr, size_type pos, bool val = true) const  // 从0开始  
		{ //从逻辑上讲，不应该用const，为了通用性，加了个const  
		  // 也可以另外写一个非const版本  
			return mystd::set(ptr, pos + 1, val);
		}
		size_type get_pos(size_type pos) const   // 从0开始  
		{ // 举例说明，低位到高位假如有10位1000 0001 11 则最后一位getpos的结果为1,  
		  // 是第二个字节，getsub则是1  
			return pos / 8;
		}
		size_type get_sub(size_type pos) const   // 从0开始  
		{  //   
			return pos % 8;
		}
		// 计算有效位数,由低位到高位，如11010000有效位为4位  
		size_type get_num_count() const
		{
			size_type m_count = 0;
			for (size_type i = size(); i >= 1; )
				if (test(--i))
					break;
				else
					++m_count;
			return size() - m_count;
		}
		void zero_last() //将最后剩余位清零  
		{  //如，有4位1101,但是分配的是一个字节，最后的4位无用，清零  
			size_type cur_pos = get_pos(size());
			size_type cur_sub = get_sub(size());
			++cur_sub;
			for (size_type i = cur_sub; i < 8; ++i)
				set(&head[cur_pos], i, false);
		}
		void fill(size_type first, size_type last, bool val = false)
		{  // 对区间[first,last)内的位进行填充  
			assert(first >= 0 && last <= size());
			for (size_type i = first; i < last; ++i)
				set(i, val);  // 成员函数  
		}
		void copy_left(size_type des, size_type beg, size_type end)
		{  // 区间[beg,end);  
			assert(des >= 0 && des <= beg);
			if (des == beg)  // 移动0位的情况  
				return;
			while (beg != end)
				set(des++, test(beg++));
		}
		void copy_right(size_type des, size_type beg, size_type end)
		{  // 向后复制,des为末端位置加 1  
			assert(des >= end && des <= size());
			if (end == size())   // 移动0位的情况  
				return;
			while (end != beg)
				set(--des, test(--end));
		}
	public:
		bitset()
			try :head(0)
		{  //计算分配的字节数，如SIZE 为10则分配2个字节就可以了，剩余6位。（16-10）  
		   // 以下同理可得  
			head = new UCHAR[get_pos(size()) + 1];
			std::memset(head, 0, get_pos(size()) + 1); //   
		}
		catch (...)
		{
#ifdef _DEBUG  
			std::cerr << "out of memory" << std::endl;
#endif  
		}
		explicit bitset(ULONG val)    // unsigned long 版本  
			try :head(0)
		{
			head = new UCHAR[get_pos(size()) + 1];
			std::memset(head, 0, get_pos(size()) + 1); //   
			for (size_type i = 0; i < size() && i < sizeof(ULONG) * 8; ++i)
				set(i, read(&val, i));
		}
		catch (...)
		{
#ifdef _DEBUG  
			std::cerr << "out of memory" << std::endl;
#endif  
		}
		explicit bitset(const std::string& str, size_type pos = 0, size_type n = std::string::npos)
			try :head(0)
		{

			head = new UCHAR[get_pos(size()) + 1];
			std::memset(head, 0, get_pos(size()) + 1); //   
			assert(n == std::string::npos || pos + n < str.size());
			if (pos + n > str.size())
				n = str.size() - pos;
			for (size_type i = 0, j = pos + n; i < size() && j >= pos + 1; )
			{
				assert(str[j - 1] == '0' || str[j - 1] == '1');
#ifdef NDEBUG  
				if (str[j - 1] != '0' && str[j - 1] != '1')
					throw mystd::invalid_argument_1();  //非法参数，抛出异常  
#endif  
				set(head, i++, str[--j] == '1');
			}
		}
		catch (...)
		{
#ifdef _DEBUG  
			std::cerr << "out of memory" << std::endl;
#endif  
		}
		//复制构造函数  
		bitset(const self& temp) :head(0)
		{
			head = new UCHAR[get_pos(size()) + 1];
			std::memcpy(head, temp.head, get_pos(size()) + 1);
		}
		self& operator = (const self& temp)  //复制赋值  
		{    // 直接覆盖，这里不用先释放资源，因为类型一致，SIZE一样  
			if (this == &temp)
				return *this;
			std::memcpy(head, temp.head, get_pos(size()) + 1);
			return *this;
		}
		~bitset()
		{
			delete[] head;
		}
	public:
		const_reference operator [] (size_type pos) const
		{
			assert(pos < size());
			return reference(head, pos);
		}

		reference operator [] (size_type pos)
		{
			assert(pos < size());
			return reference(head, pos);
		}

		size_type size() const
		{
			return SIZE;
		}

		size_type count() const
		{
			size_type m_count = 0;
			for (size_type i = 0; i < size(); ++i)
			{
				size_type cur_pos = get_pos(i);
				size_type cur_sub = get_sub(i);
				if (read(&head[cur_pos], cur_sub))
					++m_count;
			}
			return m_count;
		}

		self& set()
		{
			std::memset(head, 0xFF, get_pos(size()) + 1);
			// 将剩余的位清零  
			zero_last();
			return *this;
		}
		self& set(size_type pos, bool val = true)
		{
			assert(pos < size());
			size_type cur_pos = get_pos(pos);
			size_type cur_sub = get_sub(pos);
			set(&head[cur_pos], cur_sub, val);
			return *this;
		}

		bool any() const
		{
			for (size_type i = 0; i <= get_pos(size()); ++i)
				if (head[i])
					return true;
			return false;
		}
		bool none() const
		{
			for (size_type i = 0; i <= get_pos(size()); ++i)
				if (head[i])
					return false;
			return true;
		}
		self& reset()
		{
			std::memset(head, 0, get_pos(SIZE) + 1);
			return *this;
		}
		self& reset(size_type pos)
		{
			assert(pos < size());
			size_type cur_pos = get_pos(pos);
			size_type cur_sub = get_sub(pos);
			set(&head[cur_pos], cur_sub, false);
			return *this;
		}
		bool test(size_t pos) const
		{
			assert(pos < size());
			size_type cur_pos = get_pos(pos);
			size_type cur_sub = get_sub(pos);
			return read(&head[cur_pos], cur_sub);
		}

		self& flip()
		{
			size_type pos = get_pos(size());
			for (size_type i = 0; i <= pos; ++i)
				head[i] = ~head[i];
			zero_last();
			return *this;
		}
		self& filp(size_type pos)
		{
			assert(pos < size());
			if (test(pos))
				set(pos, false);
			else
				set(pos, true);
			return *this;
		}
		std::string to_string() const
		{
			std::string str(size(), '0');   // 自动增长效率低，所以直接初始化  
			for (size_type i = size(), j = 0; i >= 1; )
				if (test(--i))
					str[j++] = '1';
				else
					++j; // 不做无用功，直接跳过，不用复制了  
			return str;
		}
		ULONG to_ulong() const
		{
			size_type num_count = get_num_count();
			assert(num_count <= sizeof(ULONG) * 8);
#ifdef NDEBUG  
			if (num_count > sizeof(ULONG) * 8)
				throw std::overflow_error("overflow error,please check it");
#endif  
			if (size() == sizeof(ULONG) * 8 || num_count == sizeof(ULONG) * 8)
				return *(ULONG*)head;
			ULONG tmp_val = 0;
			for (size_type i = 0; i < num_count; ++i)
				set(&tmp_val, i, test(i));
			return tmp_val;
		}
		ULLONG to_ullong() const   // c++11 功能  
		{
			size_type num_count = get_num_count();
			assert(num_count <= sizeof(ULLONG) * 8);
#ifdef NDEBUG  
			if (num_count > sizeof(ULLONG) * 8)
				throw std::overflow_error("overflow error,please check it");
#endif  
			if (size() == sizeof(ULLONG) * 8 || num_count == sizeof(ULLONG) * 8)
				return *(ULLONG*)head;
			if (num_count <= sizeof(ULONG) * 8)
				return to_ulong();
			ULLONG tmp_val = 0;
			for (size_type i = 0; i < num_count; ++i)
				set(&tmp_val, i, test(i));
			return tmp_val;
		}
		//下面是一些位操作符的重载  
		self& operator &= (const self& obj)
		{
			size_type position = get_pos(size());
			for (size_type i = 0; i <= position; ++i)
				head[i] &= obj.head[i];
			return *this;
		}
		self& operator |= (const self& obj)
		{
			size_type position = get_pos(size());
			for (size_type i = 0; i <= position; ++i)
				head[i] |= obj.head[i];
			return *this;
		}
		self& operator ^= (const self& obj)
		{
			size_type position = get_pos(size());
			for (size_type i = 0; i <= position; ++i)
				head[i] ^= obj.head[i];
			return *this;
		}
		self operator | (const self& obj) const
		{
			self temp(*this);
			temp |= obj;
			return temp;
		}
		self operator & (const self& obj) const
		{
			self temp(*this);
			temp &= obj;
			return temp;
		}
		self operator ^ (const self& obj) const
		{
			self temp(*this);
			temp ^= obj;
			return temp;
		}
		self operator ~ () const
		{
			self temp(*this);
			temp.flip();
			return temp;
		}
		self& operator <<= (size_type n)
		{
			if (n == 0)
				return *this;
			if (n >= size())
				std::memset(head, 0, get_pos(size()) + 1);
			//相对向右复制覆盖  
			else
			{
				copy_right(size(), 0, size() - n);
				fill(0, n, false); // 空出的位置填充0  
			}
			return *this;
		}
		self& operator >>= (size_type n)
		{
			if (n == 0)
				return *this;
			if (n >= size())
				std::memset(head, 0, get_pos(size()) + 1);
			else
			{
				copy_left(0, n, size());
				fill(size() - n, size(), false);
			}
			return *this;
		}
		self operator << (size_type n) const
		{
			self temp(*this);
			temp <<= n;  // 转调operator <<=   
			return temp;
		}
		self operator >> (size_type n) const
		{
			self temp(*this);
			temp >>= n;
			return temp;
		}
		bool operator == (const self& obj) const
		{
			size_type pos = get_pos(size());
			for (size_type i = 0; i <= pos; ++i)
				if (head[i] != obj.head[i])
					return false;
			return true;
		}
		bool operator != (const self& obj) const
		{
			return !(*this == obj);
		}
		friend std::ostream& operator << (std::ostream& os, const self& obj)
		{
			for (size_type i = obj.size(); i > 0; )
				os << obj.test(--i);
			return os;
		}
	};

} // end of namespace mystd 
#endif // __cplusplus  

#endif // _CORE_BIT_SET_H_