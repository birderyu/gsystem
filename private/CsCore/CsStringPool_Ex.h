#ifndef _CORE_STRING_POOL_EX_H_
#define _CORE_STRING_POOL_EX_H_

#include "CsGlobal_Ex.h"

class CsStringPool_Ex :public CsNewT<CsStringPool_Ex>
{
public:
	struct CsAddress_Ex
	{
		cs_size_t h;
		cs_size_t l;
	};

	class CsFixedStringPool_Ex
	{
	public:
		CsFixedStringPool_Ex(cs_size_t size);
		~CsFixedStringPool_Ex();

		CsAddress_Ex Add(const cs_char *pInChar);
		void DeleteAt(const CsAddress_Ex &addr);

		/// 替换字符串
		/// 将对象的内容替换为pInChar中的，约束同AddObj
		void Modify(const CsAddress_Ex &addr, const cs_char *pInChar);

		/// 读取字符串内容
		/// 缓冲区长度必须大于等于字符串的长度＋1	
		/// @param[out] pOutChar 输出缓冲区
		void GetAt(const CsAddress_Ex &addr, cs_char *pOutChar);

		/// 获取指定地址字符串的存储区地址
		/// @return 指向字符串存储区的指针
		cs_cstring GetAt(const CsAddress_Ex &addr);

	public:
		/// 设置存储器增量幅度，单位为单个字符串的长度再加上1
		void SetStep(cs_size_t Step) { m_Step = Step; }

		/// 设置对象的容量，如果数据量大，建议先调用本函数再行添加数据
		/// @param[in] NewCapacity 保留存储器可容纳的字符串数量
		cs_bool SetSize(cs_size_t NewCapacity);

		/// 扩展容量按照设定的增量扩展容量
		cs_bool ExtendSize();

		/// 紧缩存储(重设步长)
		void Pack();

	protected:
		inline cs_char * GetCellAddress(cs_size_t idx);

	protected:
		cs_size_t m_Capacity; /// 存储空间可容纳的最大字符串数量
		cs_size_t m_Size; /// 存储空间已存在的字符串数量

		cs_size_t m_WritePos; /// 写指针

		cs_size_t m_StrLen; ///
		cs_size_t m_Step;

		cs_char * m_Region;
	};
};


#endif // _CORE_STRING_POOL_EX_H_