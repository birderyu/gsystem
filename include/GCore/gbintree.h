/********************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	gbintree.h
** @brief	该文件包含了二叉树节点的定义、二叉树的定义及实现
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2016-08-07
** @version	0.9.0
**
********************************************************************************/

#ifndef _CORE_BINARY_TREE_H_
#define _CORE_BINARY_TREE_H_

#include "gobject.h"
#include "gstruct.h"
#include "gnew.h"
#include "glist.h"

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 一个默认的二叉树节点
**
** 所有的二叉树节点节点都应该直接派生自GBinTreeNodeT，这是一个奇异递归模板（CRTP）。
**
********************************************************************************/
struct GBinTreeNode 
	: public GBinTreeNodeT<GBinTreeNode>
	, public GNewT<GBinTreeNode>
{
	/****************************************************************************
	**
	** @name GBinTreeNode
	** @brief 构造函数（constructor）
	** @param [in] parent {GBinTreeNode *} 双亲节点，默认为GNULL
	** @param [in] left {GBinTreeNode *} 左孩子节点，默认为GNULL
	** @param [in] right {GBinTreeNode *} 右孩子节点，默认为GNULL
	**
	****************************************************************************/
	GBinTreeNode(GBinTreeNode *parent = GNULL, 
		GBinTreeNode *left = GNULL, 
		GBinTreeNode *right = GNULL);
};

/********************************************************************************
**
** @brief 二叉树
** @template NodeT 二叉树节点的类型，默认为GBinTreeNode
**
** 为了增加二叉树的可扩展性，可以由外部指定其节点对象NodeT，但该NodeT必须派生自GBinTreeNodeT，
** 这是一个奇异递归模板（CRTP）。默认情况下，不用特意输入参数，使用GBinTreeNode作为节点即可。
**
********************************************************************************/
template<typename NodeT = GBinTreeNode>
class GBinTree 
	: public GObject
{
public:
	typedef NodeT Node;
	typedef GList<NodeT *> Nodes;
	typedef GList<const NodeT *> ConstNodes;

	/****************************************************************************
	**
	** @name funtype
	** @brief 访问节点的函数指针的定义
	**
	****************************************************************************/
	typedef gvoid(*funtype)(const NodeT &node);

public:
	/****************************************************************************
	**
	** @name GBinaryTree
	** @brief 构造函数（constructor）
	** @param [in] root {NodeT *} 根节点，默认为GNULL
	**
	** 默认情况下构造一棵空树
	**
	****************************************************************************/
	GBinTree(NodeT *root = GNULL);

	/****************************************************************************
	**
	** @name GBinaryTree
	** @brief 拷贝构造函数（copy constructor）
	** @param [in] tree {const GBinTree<NodeT> &} 另一棵二叉树的引用
	**
	****************************************************************************/
	GBinTree(const GBinTree<NodeT> &tree);

	/****************************************************************************
	**
	** @name GBinaryTree
	** @brief 移动构造函数（move constructor）
	** @param [in] tree {GBinTree<NodeT> &&} 另一棵二叉树的引用（右值引用）
	**
	****************************************************************************/
	GBinTree(GBinTree<NodeT> &&tree);

	/****************************************************************************
	**
	** @name ~GBinaryTree
	** @brief 析构函数（destructor）
	**
	** 析构函数被调用时，会释放所有节点的内存，若一个节点同时被两棵树共享，则会造成异常。
	** 由于GBinaryTree需要作为所有二叉树的基类，因此其析构函数必须是虚拟的（virtual）。
	**
	****************************************************************************/
	virtual ~GBinTree();

	/****************************************************************************
	**
	** @name CopyFrom
	** @brief 从另一棵树拷贝数据
	** @param [in] tree {const GBinTree<NodeT> &} 另一棵二叉树的引用
	**
	** 若自己已经包含了数据，则会先释放自己的资源，再做拷贝操作。
	** 深拷贝（deep copy）。
	**
	****************************************************************************/
	gvoid CopyFrom(const GBinTree<NodeT> &tree);

	/****************************************************************************
	**
	** @name SetRoot
	** @brief 设置根节点
	** @param [in] node {NodeT *} 将作为根节点的节点指针
	**
	** 若自己已经有了根节点，则会先释放自己的资源，再设置根节点。
	**
	****************************************************************************/
	gvoid SetRoot(NodeT *node);

	/****************************************************************************
	**
	** @name Destroy
	** @brief 销毁树
	**
	****************************************************************************/
	gvoid Destroy();

public:
	/****************************************************************************
	**
	** @name Root
	** @brief 获取根节点
	** @return {NodeT *&} 根节点指针的引用
	**
	****************************************************************************/
	NodeT *&Root();

	/****************************************************************************
	**
	** @name Root
	** @brief 获取根节点
	** @return {NodeT *} 根节点的指针
	**
	****************************************************************************/
	NodeT *Root() const;

	/****************************************************************************
	**
	** @name IsEmpty
	** @brief 判断二叉树是否为空
	** @return {gbool} 若为空则返回true，否则返回false
	**
	****************************************************************************/
	gbool IsEmpty() const;

	/****************************************************************************
	**
	** @name NodeCount
	** @brief 返回节点的个数
	** @return {gsize} 节点的个数
	**
	****************************************************************************/
	gsize NodeCount() const;

	/****************************************************************************
	**
	** @name LeafCount
	** @brief 返回叶子节点的个数
	** @return {gsize} 叶子节点的个数
	**
	****************************************************************************/
	gsize LeafCount() const;

	/****************************************************************************
	**
	** @name Depth
	** @brief 返回树的深度
	** @return {gsize} 树的深度
	**
	** 认为根节点的深度为1，其余依次累加
	**
	****************************************************************************/
	gsize Depth() const;

	/****************************************************************************
	**
	** @name PreOrderTraverse
	** @brief 先（根）序遍历
	** @template VisitorT 访问节点的函数
	** @param [in] visitor {VisitorT &} 访问节点的函数对象
	**
	****************************************************************************/
	template<typename VisitorT> gvoid PreOrderTraverse(VisitorT &visitor) const;

	/****************************************************************************
	**
	** @name InOrderTraverse
	** @brief 中（根）序遍历
	** @template VisitorT 访问节点的函数
	** @param [in] visitor {VisitorT &} 访问节点的函数对象
	**
	****************************************************************************/
	template<typename VisitorT> gvoid InOrderTraverse(VisitorT &visitor) const;

	/****************************************************************************
	**
	** @name PostOrderTraverse
	** @brief 后（根）序遍历
	** @template VisitorT 访问节点的函数
	** @param [in] visitor {VisitorT &} 访问节点的函数对象
	**
	****************************************************************************/
	template<typename VisitorT> gvoid PostOrderTraverse(VisitorT &visitor) const;

public:
	/****************************************************************************
	**
	** @name operator=
	** @brief 拷贝操作符
	** @param [in] tree {const GBinTree<NodeT> &} 二叉树
	** @return {GBinTree<NodeT> &} 二叉树的引用
	**
	****************************************************************************/
	GBinTree<NodeT> &operator=(const GBinTree<NodeT> &tree);

	/****************************************************************************
	**
	** @name operator=
	** @brief 移动操作符
	** @param [in] tree {GBinTree<NodeT> &&} 二叉树
	** @return {GBinTree<NodeT> &} 二叉树的引用
	**
	****************************************************************************/
	GBinTree<NodeT> &operator=(GBinTree<NodeT> &&tree);

	/****************************************************************************
	**
	** @name operator==
	** @brief 等号运算符
	** @param [in] tree {const GBinTree<NodeT> &} 二叉树
	** @return {gbool} 若两个树相等，则返回true，否则返回false
	**
	** 满足以下条件的两棵树完全相等：
	** 1）两棵树的分布完全一致，且相同位置上的节点都相等（Equals）；
	** 2）空树与空树相等。
	**
	****************************************************************************/
	gbool operator==(const GBinTree<NodeT> &tree) const;

	/****************************************************************************
	**
	** @name operator!=
	** @brief 不等号运算符
	** @param [in] tree {const GBinTree<NodeT> &} 二叉树
	** @return {gbool} 若两个树不相等，则返回true，否则返回false
	**
	****************************************************************************/
	gbool operator!=(const GBinTree<NodeT> &tree) const;

protected:
	/****************************************************************************
	**
	** @name DestroySubTree
	** @brief 销毁一棵子树
	** @param [in] node {NodeT *} 子树的根节点
	**
	****************************************************************************/
	gvoid DestroySubTree(NodeT *node);

	/****************************************************************************
	**
	** @name CopySubTree
	** @brief 拷贝一棵子树
	** @param [in] node {NodeT *} 子树的根节点
	** @return {NodeT *} 拷贝生成的新树的根节点
	**
	****************************************************************************/
	NodeT *CopySubTree(NodeT *node);

	/****************************************************************************
	**
	** @name PreOrderTraverse
	** @brief 先（根）序遍历一棵子树
	** @template VisitorT 访问节点的函数
	** @param [in] node {const NodeT *} 子树的根节点
	** @param [in] visitor {VisitorT &} 访问节点的函数对象
	**
	****************************************************************************/
	template<typename VisitorT> gvoid PreOrderTraverse(const NodeT *node, VisitorT &visitor) const;

	/****************************************************************************
	**
	** @name InOrderTraverse
	** @brief 中（根）序遍历一棵子树
	** @template VisitorT 访问节点的函数
	** @param [in] node {const NodeT *} 子树的根节点
	** @param [in] visitor {VisitorT &} 访问节点的函数对象
	**
	****************************************************************************/
	template<typename VisitorT> gvoid InOrderTraverse(const NodeT *node, VisitorT &visitor) const;

	/****************************************************************************
	**
	** @name PostOrderTraverse
	** @brief 后（根）序遍历一棵子树
	** @template VisitorT 访问节点的函数
	** @param [in] node {const NodeT *} 子树的根节点
	** @param [in] visitor {VisitorT &} 访问节点的函数对象
	**
	****************************************************************************/
	template<typename VisitorT> gvoid PostOrderTraverse(const NodeT *node, VisitorT &visitor) const;

	/****************************************************************************
	**
	** @name NodeCount
	** @brief 返回一棵子树中节点的个数
	** @param [in] node {const NodeT *} 子树的根节点
	** @param [out]	unCount {gsize &} 子树中节点的个数
	**
	****************************************************************************/
	gvoid NodeCount(const NodeT *node, gsize &unCount) const;

	/****************************************************************************
	**
	** @name LeafCount
	** @brief 返回一棵子树中叶子节点的个数
	** @param [in]	node {const NodeT *} 子树的根节点
	** @param [out]	unCount {gsize &} 子树中叶子节点的个数
	**
	****************************************************************************/
	gvoid LeafCount(const NodeT *node, gsize &unCount) const;

	/****************************************************************************
	**
	** @name Depth
	** @brief 返回一棵子树的深度
	** @param [in] node {const NodeT *} 子树的根节点
	** @return {gsize} 子树的深度
	**
	****************************************************************************/
	gsize Depth(const NodeT *node) const;

	/****************************************************************************
	**
	** @name TreeEquals
	** @brief 判断两棵树是否相等
	** @param [in] node1 {const NodeT *} 第一棵树的根节点
	** @param [in] node2 {const NodeT *} 第二棵树的根节点
	** @return {gbool} 若树相等，则返回true，否则返回false
	**
	****************************************************************************/
	gbool TreeEquals(const NodeT *node1, const NodeT *node2) const;

	/****************************************************************************
	**
	** @name NodeEquals
	** @brief 判断两个节点是否相等
	** @param [in] node1 {const NodeT *} 第一个节点
	** @param [in] node2 {const NodeT *} 第二个节点
	** @return {gbool} 若节点相等，则返回true，否则返回false
	**
	****************************************************************************/
	virtual gbool NodeEquals(const NodeT *node1, const NodeT *node2) const;

protected:
	/****************************************************************************
	**
	** 根节点的指针
	**
	****************************************************************************/
	NodeT *m_pRoot;
};

} // namespace gsystem

#include "inline/gbintree.inl"

#endif // _CORE_BINARY_TREE_H_