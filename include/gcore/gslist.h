/********************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file gslist.h
** @brief 单向链表（single linked list）
** @author birderyu
** @contact https://github.com/birderyu
** @date 2016-08-07
** @version 1.0.0
**
********************************************************************************/

#ifndef _CORE_SINGLE_LINKED_LIST_H_
#define _CORE_SINGLE_LINKED_LIST_H_

#include "glinkedlist.h"
#include "gstruct.h"
#include "gnew.h"

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 默认的单向链表节点
** @template T {type} 链表元素值的类型
**
********************************************************************************/
template<typename T>
struct GSListNode
	: public GNextNodeT<GSListNode<T>>
	, public GValueNodeT<T>
	, public GNewT<GSListNode<T>>
{
	/****************************************************************************
	**
	** @name GSListNode
	** @brief 构造函数（constructor）
	** @param [in] value {const T &} 值
	** @param [in] next {GSListNode *} 下一个节点的指针
	**
	****************************************************************************/
	GSListNode(const T &value = T(), GSListNode *next = GNULL);

	/****************************************************************************
	**
	** @name GSListNode
	** @brief 构造函数（constructor）
	** @param [in] value {T &&} 值
	** @param [in] next {GSListNode *} 下一个节点的指针
	**
	****************************************************************************/
	GSListNode(T &&value, GSListNode *next = GNULL);
};

/********************************************************************************
**
** @brief 单向链表
** @template T {type} 链表元素值的类型
** @template NodeT {type} 链表节点的类型
**
********************************************************************************/
template<typename T, typename NodeT = GSListNode<T>>
class GSList 
	: public GLinkedList<T, NodeT>
{
public:
	/****************************************************************************
	**
	** @name GSList
	** @brief 构造函数（constructor）
	**
	****************************************************************************/
	GSList();

	/****************************************************************************
	**
	** @name GSList
	** @brief 构造函数（constructor）
	** @param [in] value {const T &} 值
	**
	****************************************************************************/
	GSList(const T &value);

	/****************************************************************************
	**
	** @name GSList
	** @brief 构造函数（constructor）
	** @param [in] value {T &&} 值
	**
	****************************************************************************/
	GSList(T &&value);

	/****************************************************************************
	**
	** @name GSList
	** @brief 拷贝构造函数（copy constructor）
	** @param [in] list {const GSList &} 单向链表
	**
	****************************************************************************/
	GSList(const GSList &list);

	/****************************************************************************
	**
	** @name GSList
	** @brief 移动构造函数（move constructor）
	** @param [in] list {GSList &&} 单向链表
	**
	****************************************************************************/
	GSList(GSList &&list);

	/****************************************************************************
	**
	** @name ~GSList
	** @brief 析构函数（destructor）
	**
	****************************************************************************/
	virtual ~GSList();

	/****************************************************************************
	**
	** @name operator=
	** @brief 拷贝运算符
	** @param [in] list {const GSList &} 单向链表
	** @return {GSList &} 单向链表的引用
	**
	****************************************************************************/
	GSList &operator=(const GSList &list);

	/****************************************************************************
	**
	** @name operator=
	** @brief 移动运算符
	** @param [in] list {const GSList &} 单向链表
	** @return {GSList &} 单向链表的引用
	**
	****************************************************************************/
	GSList &operator=(GSList &&list);

	/****************************************************************************
	**
	** @name Size
	** @brief 获取链表元素的数量
	** @return {gsize} 元素的数量
	** @see GLinkedList::Size
	**
	****************************************************************************/
	gsize Size() const;

	/****************************************************************************
	**
	** @name IsEmpty
	** @brief 判断链表是否为空
	** @return {gbool} 若元素的数量为0，则返回true，否则返回false
	** @see GLinkedList::IsEmpty
	**
	****************************************************************************/
	gbool IsEmpty() const;

	/****************************************************************************
	**
	** @name GetFirstNode
	** @brief 获取第一个节点
	** @return {NodeT *} 节点的指针，若无则返回GNULL
	** @see GLinkedList::GetFirstNode
	**
	****************************************************************************/
	NodeT *GetFirstNode();

	/****************************************************************************
	**
	** @name GetFirstNode
	** @brief 获取第一个节点
	** @return {const NodeT *} 节点的指针，若无则返回GNULL
	** @see GLinkedList::GetFirstNode
	**
	****************************************************************************/
	const NodeT *GetFirstNode() const;

	/****************************************************************************
	**
	** @name GetLastNode
	** @brief 获取最后一个节点
	** @return {NodeT *} 节点的指针，若无则返回GNULL
	** @see GLinkedList::GetLastNode
	**
	****************************************************************************/
	NodeT *GetLastNode();

	/****************************************************************************
	**
	** @name GetLastNode
	** @brief 获取最后一个节点
	** @return {const NodeT *} 节点的指针，若无则返回GNULL
	** @see GLinkedList::GetLastNode
	**
	****************************************************************************/
	const NodeT *GetLastNode() const;

	/****************************************************************************
	**
	** @name GetNodeBefore
	** @brief 获取指定节点的前一个节点
	** @param [in] node {const NodeT *} 节点
	** @return {NodeT *} 节点的指针，若无则返回GNULL
	** @see GLinkedList::GetNodeBefore
	**
	****************************************************************************/
	NodeT *GetNodeBefore(const NodeT *node);

	/****************************************************************************
	**
	** @name GetNodeBefore
	** @brief 获取指定节点的前一个节点
	** @param [in] node {const NodeT *} 节点
	** @return {const NodeT *} 节点的指针，若无则返回GNULL
	** @see GLinkedList::GetNodeBefore
	**
	****************************************************************************/
	const NodeT *GetNodeBefore(const NodeT *node) const;

	/****************************************************************************
	**
	** @name GetNodeAfter
	** @brief 获取指定节点的后一个节点
	** @param [in] node {const NodeT *} 节点
	** @return {NodeT *} 节点的指针，若无则返回GNULL
	** @see GLinkedList::GetNodeAfter
	**
	****************************************************************************/
	NodeT *GetNodeAfter(const NodeT *node);

	/****************************************************************************
	**
	** @name GetNodeAfter
	** @brief 获取指定节点的后一个节点
	** @param [in] node {const NodeT *} 节点
	** @return {const NodeT *} 节点的指针，若无则返回GNULL
	** @see GLinkedList::GetNodeAfter
	**
	****************************************************************************/
	const NodeT *GetNodeAfter(const NodeT *node) const;

	/****************************************************************************
	**
	** @name GetNodeAt
	** @brief 获取指定位置的节点
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @return {NodeT *} 节点的指针，若无则返回GNULL
	** @see GLinkedList::GetNodeAt
	**
	****************************************************************************/
	NodeT *GetNodeAt(gsize pos);

	/****************************************************************************
	**
	** @name GetNodeAt
	** @brief 获取指定位置的节点
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @return {const NodeT *} 节点的指针，若无则返回GNULL
	** @see GLinkedList::GetNodeAt
	**
	****************************************************************************/
	const NodeT *GetNodeAt(gsize pos) const;

	/****************************************************************************
	**
	** @name GetFirstValue
	** @brief 获取首位置的值
	** @return {T &} 值的引用
	** @see GLinkedList::GetFirstValue
	**
	****************************************************************************/
	T &GetFirstValue();

	/****************************************************************************
	**
	** @name GetFirstValue
	** @brief 获取首位置的值
	** @return {const T &} 值的引用
	** @see GLinkedList::GetFirstValue
	**
	****************************************************************************/
	const T &GetFirstValue() const;

	/****************************************************************************
	**
	** @name GetLastValue
	** @brief 获取最后位置的值
	** @return {T &} 值的引用
	** @see GLinkedList::GetLastValue
	**
	****************************************************************************/
	T &GetLastValue();

	/****************************************************************************
	**
	** @name GetLastValue
	** @brief 获取最后位置的值
	** @return {const T &} 值的引用
	** @see GLinkedList::GetLastValue
	**
	****************************************************************************/
	const T &GetLastValue() const;

	/****************************************************************************
	**
	** @name GetValueAt
	** @brief 获取指定位置元素的值
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @return {T &} 值的引用
	** @see GLinkedList::GetValueAt
	**
	****************************************************************************/
	T &GetValueAt(gsize pos);

	/****************************************************************************
	**
	** @name GetValueAt
	** @brief 获取指定位置元素的值
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @return {const T &} 值的引用
	** @see GLinkedList::GetValueAt
	**
	****************************************************************************/
	const T &GetValueAt(gsize pos) const;

	/****************************************************************************
	**
	** @name SetValueAt
	** @brief 设置指定位置的值
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @param [in] value {const T &} 值
	** @see GLinkedList::SetValueAt
	**
	****************************************************************************/
	gvoid SetValueAt(gsize pos, const T &value);

	/****************************************************************************
	**
	** @name SetValueAt
	** @brief 设置指定位置的值
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @param [in] value {T &&} 值
	** @see GLinkedList::SetValueAt
	**
	****************************************************************************/
	gvoid SetValueAt(gsize pos, T &&value);

	/****************************************************************************
	**
	** @name FirstIndexOf
	** @brief 获取值第一次出现的位置
	** @param [in] value {const T &} 值
	** @return {gsize} 元素的下标，从0开始计数，若无则返回NULL_POS
	** @see GLinkedList::FirstIndexOf
	**
	****************************************************************************/
	gsize FirstIndexOf(const T &value) const;

	/****************************************************************************
	**
	** @name LastIndexOf
	** @brief 获取值从最后开始第一次出现的位置
	** @param [in] value {const T &} 值
	** @return {gsize} 元素的下标，从0开始计数，若无则返回NULL_POS
	** @see GLinkedList::LastIndexOf
	**
	****************************************************************************/
	gsize LastIndexOf(const T &value) const;

	/****************************************************************************
	**
	** @name Find
	** @brief 查找第一个值为value的节点
	** @param [in] value {const T &} 值
	** @return {NodeT *} 节点的指针，若无则返回GNULL
	** @see GLinkedList::Find
	**
	****************************************************************************/
	NodeT *Find(const T &value);

	/****************************************************************************
	**
	** @name Find
	** @brief 查找第一个值为value的节点
	** @param [in] value {const T &} 值
	** @return {const NodeT *} 节点的指针，若无则返回GNULL
	** @see GLinkedList::Find
	**
	****************************************************************************/
	const NodeT *Find(const T &value) const;

	/****************************************************************************
	**
	** @name AddFirst
	** @brief 将值插入到列表的首位
	** @param [in] value {const T &} 值
	** @return {NodeT *} 返回插入的节点
	** @see GLinkedList::AddFirst
	**
	****************************************************************************/
	NodeT *AddFirst(const T &value);

	/****************************************************************************
	**
	** @name AddFirst
	** @brief 将值插入到列表的首位
	** @param [in] value {T &&} 值
	** @return {NodeT *} 返回插入的节点
	** @see GLinkedList::AddFirst
	**
	****************************************************************************/
	NodeT *AddFirst(T &&value);

	/****************************************************************************
	**
	** @name AddLast
	** @brief 将值插入到列表的末尾
	** @param [in] value {const T &} 值
	** @return {NodeT *} 返回插入的节点
	** @see GLinkedList::AddLast
	**
	****************************************************************************/
	NodeT *AddLast(const T &value);

	/****************************************************************************
	**
	** @name AddLast
	** @brief 将值插入到列表的末尾
	** @param [in] value {T &&} 值
	** @return {NodeT *} 返回插入的节点
	** @see GLinkedList::AddLast
	**
	****************************************************************************/
	NodeT *AddLast(T &&value);

	/****************************************************************************
	**
	** @name InsertBefore
	** @brief 在指定位置之前插入值
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @param [in] value {const T &} 值
	** @return {NodeT *} 返回插入的节点
	** @see GLinkedList::InsertBefore
	**
	****************************************************************************/
	NodeT *InsertBefore(gsize pos, const T &value);

	/****************************************************************************
	**
	** @name InsertBefore
	** @brief 在指定位置之前插入值
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @param [in] value {T &&} 值
	** @return {NodeT *} 返回插入的节点
	** @see GLinkedList::InsertBefore
	**
	****************************************************************************/
	NodeT *InsertBefore(gsize pos, T &&value);

	/****************************************************************************
	**
	** @name InsertBefore
	** @brief 在指定节点之前插入值
	** @param [in] node {NodeT *} 节点
	** @param [in] value {const T &} 值
	** @return {NodeT *} 返回插入的节点
	** @see GLinkedList::InsertBefore
	**
	****************************************************************************/
	NodeT *InsertBefore(NodeT *node, const T &value);

	/****************************************************************************
	**
	** @name InsertBefore
	** @brief 在指定节点之前插入值
	** @param [in] node {NodeT *} 节点
	** @param [in] value {T &&} 值
	** @return {NodeT *} 返回插入的节点
	** @see GLinkedList::InsertBefore
	**
	****************************************************************************/
	NodeT *InsertBefore(NodeT *node, T &&value);

	/****************************************************************************
	**
	** @name InsertAfter
	** @brief 在指定位置之后插入值
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @param [in] value {const T &} 值
	** @return {NodeT *} 返回插入的节点
	** @see GLinkedList::InsertAfter
	**
	****************************************************************************/
	NodeT *InsertAfter(gsize pos, const T &value);

	/****************************************************************************
	**
	** @name InsertAfter
	** @brief 在指定位置之后插入值
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @param [in] value {T &&} 值
	** @return {NodeT *} 返回插入的节点
	** @see GLinkedList::InsertAfter
	**
	****************************************************************************/
	NodeT *InsertAfter(gsize pos, T &&value);

	/****************************************************************************
	**
	** @name InsertAfter
	** @brief 在指定节点之后插入值
	** @param [in] node {NodeT *} 节点
	** @param [in] value {const T &} 值
	** @return {NodeT *} 返回插入的节点
	** @see GLinkedList::InsertAfter
	**
	****************************************************************************/
	NodeT *InsertAfter(NodeT *node, const T &value);

	/****************************************************************************
	**
	** @name InsertAfter
	** @brief 在指定节点之后插入值
	** @param [in] node {NodeT *} 节点
	** @param [in] value {T &&} 值
	** @return {NodeT *} 返回插入的节点
	** @see GLinkedList::InsertAfter
	**
	****************************************************************************/
	NodeT *InsertAfter(NodeT *node, T &&value);

	/****************************************************************************
	**
	** @name Remove
	** @brief 移除节点
	** @param [in] node {const NodeT *} 节点
	** @see GLinkedList::Remove
	**
	****************************************************************************/
	gvoid Remove(const NodeT *node);

	/****************************************************************************
	**
	** @name RemoveAt
	** @brief 移除指定位置的元素
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @param [out] value {T *} 该位置上的值，若传入参数为GNULL则说明不需要此返回值
	** @see GLinkedList::RemoveAt
	**
	****************************************************************************/
	virtual gvoid RemoveAt(gsize pos, T *value = GNULL);

	/****************************************************************************
	**
	** @name RemoveFirst
	** @brief 移除第一个元素
	** @param [out] value {T *} 该位置上的值，若传入参数为GNULL则说明不需要此返回值
	** @see GLinkedList::RemoveFirst
	**
	****************************************************************************/
	gvoid RemoveFirst(T *value = GNULL);

	/****************************************************************************
	**
	** @name RemoveLast
	** @brief 移除最后一个元素
	** @param [out] value {T *} 该位置上的值，若传入参数为GNULL则说明不需要此返回值
	** @see GLinkedList::RemoveLast
	**
	****************************************************************************/
	gvoid RemoveLast(T *value = GNULL);

	/****************************************************************************
	**
	** @name RemoveAll
	** @brief 移除所有元素
	** @see GLinkedList::RemoveLast
	**
	****************************************************************************/
	gvoid RemoveAll();

	/****************************************************************************
	**
	** @name Invert
	** @brief 翻转链表
	** @see GLinkedList::RemoveLast
	**
	****************************************************************************/
	gvoid Invert();

	/****************************************************************************
	**
	** @name IndexOfCircle
	** @brief 若链表为环，则返回环首位置元素的下标，否则返回NULL_POS
	** @return {gsize} 元素的下标，从0开始计数，若非环则返回NULL_POS
	** @see GLinkedList::IndexOfCircle
	**
	****************************************************************************/
	gsize IndexOfCircle() const;

	/****************************************************************************
	**
	** @name FindCircle
	** @brief 若链表为环，则返回环首位置的节点，否则返回GNULL
	** @return {NodeT *} 节点的指针，若非环则返回GNULL
	** @see GLinkedList::FindCircle
	**
	****************************************************************************/
	NodeT *FindCircle();

	/****************************************************************************
	**
	** @name FindCircle
	** @brief 若链表为环，则返回环首位置的节点，否则返回GNULL
	** @return {const NodeT *} 节点的指针，若非环则返回GNULL
	** @see GLinkedList::FindCircle
	**
	****************************************************************************/
	const NodeT *FindCircle() const;

	/****************************************************************************
	**
	** @name IndexOfCross
	** @brief 若该链表与另一个链表相交叉，则返回交叉首位置元素的下标，否则返回NULL_POS
	** @param [in] list {const GLinkedList &} 链表
	** @return {gsize} 元素的下标，从0开始计数，若没有交叉则返回NULL_POS
	** @see GLinkedList::IndexOfCross
	**
	****************************************************************************/
	gsize IndexOfCross(const GLinkedList<T, NodeT> &list);

protected:
	/****************************************************************************
	**
	** 链表元素的个数
	**
	****************************************************************************/
	gsize m_nSize;

	/****************************************************************************
	**
	** 单向链表首节点
	**
	****************************************************************************/
	Node *m_pFirst;
};

} // namespace gsystem

#include "inline/gslist.inl"

#endif // _CORE_SINGLE_LINKED_LIST_H_