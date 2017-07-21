/********************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file ghashtable.h
** @brief 哈希表
** @author birderyu
** @contact https://github.com/birderyu
** @date 2017-1-24
** @version 0.5.0
**
** 哈希表是一种以空间换取时间以达到高效数据检索的数据结构，其理论基础是数组下标的常数级访问效率。
** GHashTable是一个模板类，其键类型、值类型、哈希节点类型、求取哈希码的算法、比较值的算法、解
** 决哈希冲突的方法，都是模板的参数，以达到灵活和高效的目的。其中，解决哈希冲突的数据结构被称作
** 哈希桶。在哈希表中，一次哈希查询，其返回的结果是一个哈希桶，这是一个具有同样哈希值的数据节点
** 的集合，如何从哈希桶中定位到真正需要的哈希值，需要哈希桶提供查找算法。通过不同的哈希桶结构，
** 可以实现拉链法、二次哈希等哈希冲突解决方法，用于各种不同的场景需求。
**
********************************************************************************/

#ifndef _CORE_HASH_TABLE_H_
#define _CORE_HASH_TABLE_H_

#include "ghash.h"
#include "glist.h"
#include "gdynamicarray.h"
#include "gstruct.h"
#include "gnocopyable.h"
#include "gnew.h"

/********************************************************************************
**
** @name G_HASH_TABLE_DEFAULT_MODULE_SIZE
** @brief 哈希表默认模值，等于2的4次方
**
********************************************************************************/
#define G_HASH_TABLE_DEFAULT_MODULE_SIZE 0x10

/********************************************************************************
**
** @name G_HASH_TABLE_MAX_MODULE_SIZE
** @brief 哈希表最大模值，等于2的30次方
**
********************************************************************************/
#define G_HASH_TABLE_MAX_MODULE_SIZE 0x40000000

/********************************************************************************
**
** @name G_HASH_TABLE_DEFAULT_LOAD_FACTOR
** @brief 哈希表默认负载因子
**
********************************************************************************/
#define G_HASH_TABLE_DEFAULT_LOAD_FACTOR 0.75f

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 哈希表
** @template KeyT {type} 键类型
** @template ValueT {type} 值类型
** @template HashT {gunctor} 键的哈希算法
** @template CompareT {gunctor} 键的比较算法
** @template NodeT {type} 哈希节点类型
** @template SlotT {type} 哈希桶类型
**
********************************************************************************/
template<typename KeyT, typename ValueT, 
	typename HashT, typename CompareT, 
	typename NodeT, typename SlotT>
class GHashTable;

/********************************************************************************
**
** @brief 一个默认的哈希节点
** @template KeyT {type} 键类型
** @template ValueT {type} 值类型
**
** 默认的哈希节点，一般情况下不需要额外指定
**
********************************************************************************/
template<typename KeyT, typename ValueT>
struct GHashTableNode 
	: public GNextNodeT<GHashTableNode<KeyT, ValueT>>
	, public GPairNodeT<KeyT, ValueT>
	, public GNewT<GHashTableNode<KeyT, ValueT>>
{
	/****************************************************************************
	**
	** @name GHashTableNode
	** @brief 构造函数（constructor）
	** @param [in] key {const KeyT &} 键
	** @param [in] value {const ValueT &} 值
	** @param [in] next {GHashTableNode *} 下一个节点的指针，默认为空
	**
	****************************************************************************/
	GHashTableNode(const KeyT &key, const ValueT &value = ValueT(),
		GHashTableNode *next = GNULL);

	/****************************************************************************
	**
	** @name GHashTableNode
	** @brief 构造函数（constructor）
	** @param [in] key {const KeyT &} 键
	** @param [in] value {ValueT &&} 值
	** @param [in] next {GHashTableNode *} 下一个节点的指针，默认为空
	**
	****************************************************************************/
	GHashTableNode(const KeyT &key, ValueT &&value, GHashTableNode *next = GNULL);
};

/********************************************************************************
**
** @brief 哈希桶
** @template KeyT {type} 键类型
** @template ValueT {type} 值类型
** @template NodeT {type} 哈希节点类型
**
** 哈希桶是一种用于处理哈希冲突的数据结构。
**
********************************************************************************/
template<typename KeyT, typename ValueT, typename NodeT>
class GHashTableSlot
{
public:
	/****************************************************************************
	**
	** @name Nodes
	** @brief 哈希表节点指针的列表
	**
	****************************************************************************/
	typedef GList<NodeT *> Nodes;

	/****************************************************************************
	**
	** @name Nodes
	** @brief 哈希表节点常量指针的列表
	**
	****************************************************************************/
	typedef GList<const NodeT *> ConstNodes;

public:
	/****************************************************************************
	**
	** @name ~GHashTableSlot
	** @brief 析构函数（destructor）
	**
	****************************************************************************/
	virtual ~GHashTableSlot() = 0 {}

	/****************************************************************************
	**
	** @name Size
	** @brief 获取哈希桶中节点的个数
	** @return {gsize} 节点的个数
	**
	****************************************************************************/
	virtual gsize Size() const = 0;

	/****************************************************************************
	**
	** @name IsEmpty
	** @brief 判断哈希桶是否为空
	** @return {gbool} 若哈希桶为空，则返回true，否则返回false
	**
	****************************************************************************/
	virtual gbool IsEmpty() const = 0;

	/****************************************************************************
	**
	** @name FirstNode
	** @brief 获取第一个节点
	** @return {NodeT *} 节点的指针
	**
	****************************************************************************/
	virtual NodeT *FirstNode() = 0;

	/****************************************************************************
	**
	** @name FirstNode
	** @brief 获取第一个节点
	** @return {NodeT *} 节点的指针
	**
	****************************************************************************/
	virtual const NodeT *FirstNode() const = 0;

	/****************************************************************************
	**
	** @name NextNode
	** @brief 获取节点的下一个节点
	** @param [in] node {NodeT *} 节点的指针
	** @return {NodeT *} 节点的指针
	**
	****************************************************************************/
	virtual NodeT *NextNode(NodeT *node) = 0;

	/****************************************************************************
	**
	** @name NextNode
	** @brief 获取节点的下一个节点
	** @param [in] node {const NodeT *} 节点的指针
	** @return {const NodeT *} 节点的指针
	**
	****************************************************************************/
	virtual const NodeT *NextNode(const NodeT *node) const = 0;

	/****************************************************************************
	**
	** @name Contains
	** @brief 判断是否包含键
	** @param [in] key {const KeyT &} 键
	** @return {gbool} 节点的指针
	**
	****************************************************************************/
	virtual gbool Contains(const KeyT &key) const = 0;

	/****************************************************************************
	**
	** @name Search
	** @brief 查找键
	** @param [in] key {const KeyT &} 键
	** @param [out] nodes {Nodes &} 键为key的节点的集合
	** @return {gbool} 若查找成功，则返回true，否则返回false
	**
	****************************************************************************/
	virtual gbool Search(const KeyT &key, Nodes &nodes) = 0;

	/****************************************************************************
	**
	** @name Search
	** @brief 查找键
	** @param [in] key {const KeyT &} 键
	** @param [out] nodes {ConstNodes &} 键为key的节点的集合
	** @return {gbool} 若查找成功，则返回true，否则返回false
	**
	****************************************************************************/
	virtual gbool Search(const KeyT &key, ConstNodes &nodes) const = 0;

	/****************************************************************************
	**
	** @name SearchFirst
	** @brief 查找键的第一个节点
	** @param [in] key {const KeyT &} 键
	** @return {NodeT *} 节点的指针，若查找失败则返回GNULL
	**
	****************************************************************************/
	virtual NodeT *SearchFirst(const KeyT &key) = 0;

	/****************************************************************************
	**
	** @name SearchFirst
	** @brief 查找键的第一个节点
	** @param [in] key {const KeyT &} 键
	** @return {const NodeT *} 节点的指针，若查找失败则返回GNULL
	**
	****************************************************************************/
	virtual const NodeT *SearchFirst(const KeyT &key) const = 0;

	/****************************************************************************
	**
	** @name Insert
	** @brief 插入一个键值对
	** @param [in] key {const KeyT &} 键
	** @param [in] value {const ValueT &} 值
	** @param [out] realInsert {gbool &} 是否真正地插入了一个节点
	** @return {NodeT *} 节点的指针
	**
	** 若当前哈希桶键是唯一的，且已经存在键为key的节点，则不会执行真正的插入操作，而是将原本键为
	** key的节点的值改为value，节点个数并没有增加。在这种情况下，realInsert会返回false。
	**
	****************************************************************************/
	virtual NodeT *Insert(const KeyT &key, const ValueT &value, gbool &realInsert) = 0;

	/****************************************************************************
	**
	** @name Insert
	** @brief 插入一个键值对
	** @param [in] key {const KeyT &} 键
	** @param [in] value {ValueT &&} 值
	** @param [out] realInsert {gbool &} 是否真正地插入了一个节点
	** @return {NodeT *} 节点的指针
	**
	** 若当前哈希桶键是唯一的，且已经存在键为key的节点，则不会执行真正的插入操作，而是将原本键为
	** key的节点的值改为value，节点个数并没有增加。在这种情况下，realInsert会返回false。
	**
	****************************************************************************/
	virtual NodeT *Insert(const KeyT &key, ValueT &&value, gbool &realInsert) = 0;

	/****************************************************************************
	**
	** @name Delete
	** @brief 删除指定键的节点
	** @param [in] key {const KeyT &} 键
	** @return {gsize} 删除的节点数
	**
	** 删除指定键的节点，返回删除的节点数
	**
	****************************************************************************/
	virtual gsize Delete(const KeyT &key) = 0;

	/****************************************************************************
	**
	** @name Equals
	** @brief 比较两个哈希桶是否相等
	** @param [in] slot {const GHashTableSlot &} 哈希桶
	** @return {gbool} 若相等，则返回true，否则返回false
	**
	****************************************************************************/
	virtual gbool Equals(const GHashTableSlot &slot) const = 0;

	/****************************************************************************
	**
	** @name InsertNode
	** @brief 插入一个节点
	** @param [in] node {NodeT *} 节点的指针
	** @return {NodeT *} 节点的指针
	**
	** 在哈希桶外部创建了一个节点，并将其直接插入，需要保证插入后哈希桶的结构是一个正确有效的结构，
	** 至于插入到哪个位置，如何实现插入，都不做要求。
	**
	****************************************************************************/
	virtual NodeT *InsertNode(NodeT *node) = 0;

	/****************************************************************************
	**
	** @name RemoveNode
	** @brief 移除一个节点
	** @return {NodeT *} 节点的指针
	**
	** 从哈希桶中移除一个节点，这个节点可以是任意位置，不做要求，移除出来的节点还未析构，如何使用
	** 也不做要求。对于哈希桶，仅仅需要保证移除该节点后，剩余的结构仍然是一个正确有效的结构。
	**
	****************************************************************************/
	virtual NodeT *RemoveNode() = 0;
};

/********************************************************************************
**
** @brief 线性哈希桶
** @template KeyT {type} 键类型
** @template ValueT {type} 值类型
** @template CompareT {gunctor} 键的比较算法
** @template NodeT {type} 哈希节点类型
**
** 线性哈希桶是一种使用单链表解决哈希冲突的数据结构
**
********************************************************************************/
template<typename KeyT, typename ValueT, 
	typename CompareT, typename NodeT>
class GListSlot
	: public GHashTableSlot<KeyT, ValueT, NodeT>
	, public GNewT<GListSlot<KeyT, ValueT, CompareT, NodeT>>
{
private:
	/****************************************************************************
	**
	** 判断键是否相等的函数对象
	**
	****************************************************************************/
	static const CompareT m_fCompare;

public:
	/****************************************************************************
	**
	** @name GListSlot
	** @brief 构造函数（constructor）
	** @param [in] unique {gbool} 键是否唯一，默认为true，表示键是唯一的
	**
	****************************************************************************/
	GListSlot(gbool unique = true);

	/****************************************************************************
	**
	** @name GListSlot
	** @brief 拷贝构造函数（copy constructor）
	** @param [in] slot {const GHashTableSlot &} 哈希桶
	**
	****************************************************************************/
	GListSlot(const GListSlot &slot);

	/****************************************************************************
	**
	** @name GListSlot
	** @brief 移动构造函数（move constructor）
	** @param [in] slot {GHashTableSlot &&} 哈希桶
	**
	****************************************************************************/
	GListSlot(GListSlot &&slot);

	/****************************************************************************
	**
	** @name ~GListSlot
	** @brief 析构函数（destructor）
	**
	****************************************************************************/
	~GListSlot();

	/****************************************************************************
	**
	** @name operator=
	** @brief 拷贝运算符
	** @param [in] slot {const GHashTableSlot &} 哈希桶
	** @return {GHashTableSlot &} 哈希桶的引用
	**
	****************************************************************************/
	GListSlot &operator=(const GListSlot &slot);

	/****************************************************************************
	**
	** @name operator=
	** @brief 移动运算符
	** @param [in] slot {GHashTableSlot &&} 哈希桶
	** @return {GHashTableSlot &} 哈希桶的引用
	**
	****************************************************************************/
	GListSlot &operator=(GListSlot &&slot);

	/****************************************************************************
	**
	** @name Size
	** @brief 获取哈希桶中节点的个数
	** @return {gsize} 节点的个数
	** @see GHashTableSlot::Size
	**
	****************************************************************************/
	gsize Size() const;

	/****************************************************************************
	**
	** @name IsEmpty
	** @brief 判断哈希桶是否为空
	** @return {gbool} 若哈希桶为空，则返回true，否则返回false
	** @see GHashTableSlot::IsEmpty
	**
	****************************************************************************/
	gbool IsEmpty() const;

	/****************************************************************************
	**
	** @name FirstNode
	** @brief 获取第一个节点
	** @return {NodeT *} 节点的指针
	** @see GHashTableSlot::FirstNode
	**
	****************************************************************************/
	NodeT *FirstNode();

	/****************************************************************************
	**
	** @name FirstNode
	** @brief 获取第一个节点
	** @return {NodeT *} 节点的指针
	** @see GHashTableSlot::FirstNode
	**
	****************************************************************************/
	const NodeT *FirstNode() const;

	/****************************************************************************
	**
	** @name NextNode
	** @brief 获取节点的下一个节点
	** @param [in] node {NodeT *} 节点的指针
	** @return {NodeT *} 节点的指针
	** @see GHashTableSlot::NextNode
	**
	****************************************************************************/
	NodeT *NextNode(NodeT *node);

	/****************************************************************************
	**
	** @name NextNode
	** @brief 获取节点的下一个节点
	** @param [in] node {const NodeT *} 节点的指针
	** @return {const NodeT *} 节点的指针
	** @see GHashTableSlot::NextNode
	**
	****************************************************************************/
	const NodeT *NextNode(const NodeT *node) const;

	/****************************************************************************
	**
	** @name Contains
	** @brief 判断是否包含键
	** @param [in] key {const KeyT &} 键
	** @return {gbool} 节点的指针
	** @see GHashTableSlot::Contains
	**
	****************************************************************************/
	gbool Contains(const KeyT &key) const;

	/****************************************************************************
	**
	** @name Search
	** @brief 查找键
	** @param [in] key {const KeyT &} 键
	** @param [out] nodes {Nodes &} 键为key的节点的集合
	** @return {gbool} 若查找成功，则返回true，否则返回false
	** @see GHashTableSlot::Search
	**
	****************************************************************************/
	gbool Search(const KeyT &key, Nodes &nodes);

	/****************************************************************************
	**
	** @name Search
	** @brief 查找键
	** @param [in] key {const KeyT &} 键
	** @param [out] nodes {ConstNodes &} 键为key的节点的集合
	** @return {gbool} 若查找成功，则返回true，否则返回false
	** @see GHashTableSlot::Search
	**
	****************************************************************************/
	gbool Search(const KeyT &key, ConstNodes &nodes) const;

	/****************************************************************************
	**
	** @name SearchFirst
	** @brief 查找键的第一个节点
	** @param [in] key {const KeyT &} 键
	** @return {NodeT *} 节点的指针，若查找失败则返回GNULL
	** @see GHashTableSlot::SearchFirst
	**
	****************************************************************************/
	NodeT *SearchFirst(const KeyT &key);

	/****************************************************************************
	**
	** @name SearchFirst
	** @brief 查找键的第一个节点
	** @param [in] key {const KeyT &} 键
	** @return {const NodeT *} 节点的指针，若查找失败则返回GNULL
	** @see GHashTableSlot::SearchFirst
	**
	****************************************************************************/
	const NodeT *SearchFirst(const KeyT &key) const;

	/****************************************************************************
	**
	** @name Insert
	** @brief 插入一个键值对
	** @param [in] key {const KeyT &} 键
	** @param [in] value {const ValueT &} 值
	** @param [out] realInsert {gbool &} 是否真正地插入了一个节点
	** @return {NodeT *} 节点的指针
	** @see GHashTableSlot::Insert
	**
	****************************************************************************/
	NodeT *Insert(const KeyT &key, const ValueT &value, gbool &realInsert);

	/****************************************************************************
	**
	** @name Insert
	** @brief 插入一个键值对
	** @param [in] key {const KeyT &} 键
	** @param [in] value {ValueT &&} 值
	** @param [out] realInsert {gbool &} 是否真正地插入了一个节点
	** @return {NodeT *} 节点的指针
	** @see GHashTableSlot::Insert
	**
	****************************************************************************/
	NodeT *Insert(const KeyT &key, ValueT &&value, gbool &realInsert);

	/****************************************************************************
	**
	** @name Delete
	** @brief 删除指定键的节点
	** @param [in] key {const KeyT &} 键
	** @return {gsize} 删除的节点数
	** @see GHashTableSlot::Delete
	**
	****************************************************************************/
	gsize Delete(const KeyT &key);

	/****************************************************************************
	**
	** @name Equals
	** @brief 比较两个哈希桶是否相等
	** @param [in] slot {const GHashTableSlot &} 哈希桶
	** @return {gbool} 若相等，则返回true，否则返回false
	** @see GHashTableSlot::Equals
	**
	****************************************************************************/
	gbool Equals(const GHashTableSlot &slot) const;

	/****************************************************************************
	**
	** @name Equals
	** @brief 比较两个哈希桶是否相等
	** @param [in] slot {const GListSlot &} 线性哈希桶
	** @return {gbool} 若相等，则返回true，否则返回false
	**
	****************************************************************************/
	gbool Equals(const GListSlot &slot) const;

	/****************************************************************************
	**
	** @name InsertNode
	** @brief 插入一个节点
	** @param [in] node {NodeT *} 节点的指针
	** @return {NodeT *} 节点的指针
	** @see GHashTableSlot::InsertNode
	**
	** 对于线性哈希桶，该方法在头节点之前插入一个新的节点，并将头节点设置为该节点
	**
	****************************************************************************/
	NodeT *InsertNode(NodeT *node);

	/****************************************************************************
	**
	** @name RemoveNode
	** @brief 移除一个节点
	** @return {NodeT *} 节点的指针
	** @see GHashTableSlot::InsertNode
	**
	** 对于线性哈希桶，该方法将头节点移除并返回，并将头节点设置为头节点的下一个节点
	**
	****************************************************************************/
	NodeT *RemoveNode();

private:
	/****************************************************************************
	**
	** @name DeleteAt
	** @brief 删除指定位置的节点
	** @param [in] node {NodeT *} 待删除的节点的指针
	** @param [in] preNode {NodeT *} 待删除的节点的上一个节点的指针
	** @return {NodeT *} 若删除成功，则返回true，否则返回false
	**
	****************************************************************************/
	gbool DeleteAt(NodeT *node, NodeT *preNode);

	/****************************************************************************
	**
	** @name Destroy
	** @brief 销毁哈希桶
	**
	****************************************************************************/
	gvoid Destroy();

private:
	/****************************************************************************
	**
	** 头节点
	**
	****************************************************************************/
	NodeT *m_pHead;

	/****************************************************************************
	**
	** 节点的总数
	**
	****************************************************************************/
	gsize m_nSize;

	/****************************************************************************
	**
	** 键是否唯一
	**
	****************************************************************************/
	gbool m_bUnique;
};

/********************************************************************************
**
** @brief 二次哈希桶
** @template KeyT {type} 键类型
** @template ValueT {type} 值类型
** @template HashT {gunctor} 键的哈希算法
** @template CompareT {gunctor} 键的比较算法
** @template NodeT {type} 哈希节点类型
**
** 使用哈希表的方式解决哈希冲突的数据结构
**
********************************************************************************/
template<typename KeyT, typename ValueT,
	typename HashT, typename CompareT, 
	typename NodeT>
class GHashSlot
{

private:
	GHashTable<KeyT, ValueT, HashT, CompareT, NodeT, GListSlot<KeyT, ValueT, CompareT, NodeT>> m_tTable;
};

/********************************************************************************
**
** @brief 哈希表
** @template KeyT {type} 键类型
** @template ValueT {type} 值类型
** @template HashT {gunctor} 键的哈希算法
** @template CompareT {gunctor} 键的比较算法
** @template NodeT {type} 哈希节点类型
** @template SlotT {type} 哈希桶类型
**
********************************************************************************/
template<typename KeyT, typename ValueT,
	typename HashT = GHashF<KeyT>,
	typename CompareT = GEqualToF<KeyT>,
	typename NodeT = GHashTableNode<KeyT, ValueT>,
	typename SlotT = GListSlot<KeyT, ValueT, CompareT, NodeT>>
class GHashTable
	: public GObject
{
private:
	/****************************************************************************
	**
	** 求键的哈希码的函数对象
	**
	****************************************************************************/
	static const HashT m_fHash;

public:
	typedef GHashTable<KeyT, ValueT, HashT, CompareT, NodeT, SlotT> Table;
	typedef NodeT Node;
	typedef GList<NodeT *> Nodes;
	typedef GList<const NodeT *> ConstNodes;

public:
	GHashTable(gsize module = G_HASH_TABLE_DEFAULT_MODULE_SIZE, 
		gfloat factor = G_HASH_TABLE_DEFAULT_LOAD_FACTOR,
		gbool unique = true);
	GHashTable(const GHashTable &table);
	GHashTable(GHashTable &&table);
	~GHashTable();

	GHashTable &operator=(const GHashTable &table);
	GHashTable &operator=(GHashTable &&table);

	gsize Size() const;
	gbool IsEmpty() const;

	gvoid Destroy();

	gbool Contains(const KeyT &key) const;

	NodeT *FirstNode();
	const NodeT *FirstNode() const;

	NodeT *NextNode(NodeT *node);
	const NodeT *NextNode(const NodeT *node) const;

	NodeT *Find(const KeyT &key);
	const NodeT *Find(const KeyT &key) const;
	gbool Find(const KeyT &key, Nodes &nodes);
	gbool Find(const KeyT &key, ConstNodes &nodes) const;

	NodeT *Insert(const KeyT &key, const ValueT &value);
	NodeT *Insert(const KeyT &key, ValueT &&value);
	gvoid Delete(const KeyT &key);

	gbool operator==(const GHashTable &table) const;
	gbool operator!=(const GHashTable &table) const;

protected:
	/****************************************************************************
	**
	** @name HashSlotEquals
	** @brief 判断两个哈希桶是否相等
	** @param [in] slot1 {const SlotT *} 第一个哈希桶的指针
	** @param [in] slot2 {const SlotT *} 第二个哈希桶的指针
	** @return {gbool} 若相等，则返回true，否则返回false
	**
	****************************************************************************/
	gbool HashSlotEquals(const SlotT *slot1, const SlotT *slot2) const;

	/****************************************************************************
	**
	** @name Inflate
	** @brief 扩容
	** @param [in] module {gsize} 模值
	**
	** 使用新的模值对哈希表进行扩容，扩容时会对所有元素进行重新哈希。注意传入的参数module并非
	** 一定是实际扩容之后的哈希表的模值。
	**
	****************************************************************************/
	gvoid Inflate(gsize module);

	/****************************************************************************
	**
	** @name RoundUpToPowerOf2
	** @brief 获取不小于n的一个最小的2整数次方值
	** @param [in] n {gsize} 数值
	** @return {gsize} 数值
	**
	** 如 n = 30，则返回2的5次方，即32。注意，这个值一定不会小于
	** G_HASH_TABLE_DEFAULT_MODULE_SIZE，也不会大于G_HASH_TABLE_MAX_MODULE_SIZE。
	**
	****************************************************************************/
	gsize RoundUpToPowerOf2(gsize n) const;

	/****************************************************************************
	**
	** @name IndexOf
	** @brief 获取键的下标
	** @param [in] key {const KeyT &} 键
	** @param [in] module {gsize} 模值
	** @return {gsize} 哈希桶的下标，从0开始计数
	**
	** 根据键和模值获取哈希桶的下标
	**
	****************************************************************************/
	gsize IndexOf(const KeyT &key, gsize module) const;

private:
	/****************************************************************************
	**
	** 负载因子
	**
	****************************************************************************/
	gfloat m_nFactor;

	/****************************************************************************
	**
	** 主键是否唯一
	**
	****************************************************************************/
	gbool m_bUnique;

	/****************************************************************************
	**
	** 哈希表节点的个数
	**
	****************************************************************************/
	gsize m_nSize;

	/****************************************************************************
	**
	** 扩容阈值，等于模值*负载因子，为了减少浮点运算，将这个值存储下来
	**
	****************************************************************************/
	gsize m_nThreshold;

	/****************************************************************************
	**
	** 哈希桶的列表，其元素的个数等于哈希表的模值
	**
	****************************************************************************/
	GDynamicArray<SlotT*> m_tBuckets;
};

// 拉链哈希表
template<typename KeyT, typename ValueT, 
	typename HashT, typename CompareT>
class GListHashTable
	: public GHashTable<KeyT, ValueT, 
		HashT, CompareT, 
		GHashTableNode<KeyT, ValueT>, 
		GListSlot<KeyT, ValueT, CompareT, GHashTableNode<KeyT, ValueT>>>
{

};

// 二次哈希表
template<typename KeyT, typename ValueT, 
	typename HashT, typename CompareT>
class GDoubleHashTable
	: public GHashTable<KeyT, ValueT,
		HashT, CompareT,
		GHashTableNode<KeyT, ValueT>,
		GHashSlot<KeyT, ValueT, HashT, CompareT, GHashTableNode<KeyT, ValueT>>>
{

};

} // namespace gsystem

#include "inline/ghashtable.inl"

#undef G_HASH_TABLE_DEFAULT_LOAD_FACTOR
#undef G_HASH_TABLE_MAX_MODULE_SIZE
#undef G_HASH_TABLE_DEFAULT_MODULE_SIZE

#endif // _CORE_HASH_TABLE_H_