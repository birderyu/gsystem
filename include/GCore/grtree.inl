#ifndef _CORE_R_TREE_INLINE_
#define _CORE_R_TREE_INLINE_

template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::GRTree()
{
	GASSERT(MAXNODES > MINNODES);
	GASSERT(MINNODES > 0);


	// We only support machine word size simple data type eg. integer index or object pointer.
	// Since we are storing as union with non data branch
	GASSERT(sizeof(DATATYPE) == sizeof(void*) || sizeof(DATATYPE) == sizeof(int));

	// Precomputed volumes of the unit spheres for the first few dimensions
	const float UNIT_SPHERE_VOLUMES[] = {
		0.000000f, 2.000000f, 3.141593f, // Dimension  0,1,2
		4.188790f, 4.934802f, 5.263789f, // Dimension  3,4,5
		5.167713f, 4.724766f, 4.058712f, // Dimension  6,7,8
		3.298509f, 2.550164f, 1.884104f, // Dimension  9,10,11
		1.335263f, 0.910629f, 0.599265f, // Dimension  12,13,14
		0.381443f, 0.235331f, 0.140981f, // Dimension  15,16,17
		0.082146f, 0.046622f, 0.025807f, // Dimension  18,19,20 
	};

	m_root = AllocNode();
	m_root->m_level = 0;
	m_unitSphereVolume = (ELEMTYPEREAL)UNIT_SPHERE_VOLUMES[NUMDIMS];
}

template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::~GRTree()
{
	Reset(); // Free, or reset node memory
}

template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::Insert(const ELEMTYPE a_min[NUMDIMS], const ELEMTYPE a_max[NUMDIMS], const DATATYPE& a_dataId)
{
#ifdef _DEBUG
	for (int index = 0; index < NUMDIMS; ++index)
	{
		GASSERT(a_min[index] <= a_max[index]);
	}
#endif //_DEBUG

	Rect rect;

	for (int axis = 0; axis < NUMDIMS; ++axis)
	{
		rect.m_min[axis] = a_min[axis];
		rect.m_max[axis] = a_max[axis];
	}

	InsertRect(&rect, a_dataId, &m_root, 0);
}

template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::Remove(const ELEMTYPE a_min[NUMDIMS], const ELEMTYPE a_max[NUMDIMS], const DATATYPE& a_dataId)
{
#ifdef _DEBUG
	for (int index = 0; index < NUMDIMS; ++index)
	{
		GASSERT(a_min[index] <= a_max[index]);
	}
#endif //_DEBUG

	Rect rect;

	for (int axis = 0; axis < NUMDIMS; ++axis)
	{
		rect.m_min[axis] = a_min[axis];
		rect.m_max[axis] = a_max[axis];
	}

	RemoveRect(&rect, a_dataId, &m_root);
}

template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
int GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::Search(const ELEMTYPE a_min[NUMDIMS], const ELEMTYPE a_max[NUMDIMS], bool __cdecl a_resultCallback(DATATYPE a_data, void* a_context), void* a_context)
{
#ifdef _DEBUG
	for (int index = 0; index < NUMDIMS; ++index)
	{
		GASSERT(a_min[index] <= a_max[index]);
	}
#endif //_DEBUG

	Rect rect;

	for (int axis = 0; axis < NUMDIMS; ++axis)
	{
		rect.m_min[axis] = a_min[axis];
		rect.m_max[axis] = a_max[axis];
	}

	// NOTE: May want to return search result another way, perhaps returning the number of found elements here.

	int foundCount = 0;
	Search(m_root, &rect, foundCount, a_resultCallback, a_context);

	return foundCount;
}

template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
int GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::Count()
{
	int count = 0;
	CountRec(m_root, count);

	return count;
}

template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::CountRec(Node* a_node, gsize& a_count)
{
	if (a_node->IsInternalNode())  // not a leaf node
	{
		for (gsize index = 0; index < a_node->m_count; ++index)
		{
			CountRec(a_node->m_branch[index].m_child, a_count);
		}
	}
	else // A leaf node
	{
		a_count += a_node->m_count;
	}
}

template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::RemoveAll()
{
	// Delete all existing nodes
	Reset();

	m_root = AllocNode();
	m_root->m_level = 0;
}

template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::Reset()
{
#ifdef RTREE_DONT_USE_MEMPOOLS
	// Delete all existing nodes
	RemoveAllRec(m_root);
#else // RTREE_DONT_USE_MEMPOOLS
	// Just reset memory pools.  We are not using complex types
	// EXAMPLE
#endif // RTREE_DONT_USE_MEMPOOLS
}

template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::RemoveAllRec(Node* a_node)
{
	GASSERT(a_node);
	GASSERT(a_node->m_level >= 0);

	if (a_node->IsInternalNode()) // This is an internal node in the tree
	{
		for (int index = 0; index < a_node->m_count; ++index)
		{
			RemoveAllRec(a_node->m_branch[index].m_child);
		}
	}
	FreeNode(a_node);
}

template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
typename GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::Node* GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::AllocNode()
{
	Node* newNode;
#ifdef RTREE_DONT_USE_MEMPOOLS
	newNode = new Node;
#else // RTREE_DONT_USE_MEMPOOLS
	// EXAMPLE
#endif // RTREE_DONT_USE_MEMPOOLS
	InitNode(newNode);
	return newNode;
}

template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::FreeNode(Node* a_node)
{
	GASSERT(a_node);

#ifdef RTREE_DONT_USE_MEMPOOLS
	delete a_node;
#else // RTREE_DONT_USE_MEMPOOLS
	// EXAMPLE
#endif // RTREE_DONT_USE_MEMPOOLS
}

// Allocate space for a node in the list used in DeletRect to
// store Nodes that are too empty.
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
typename GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::ListNode* GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::AllocListNode()
{
#ifdef RTREE_DONT_USE_MEMPOOLS
	return new ListNode;
#else // RTREE_DONT_USE_MEMPOOLS
	// EXAMPLE
#endif // RTREE_DONT_USE_MEMPOOLS
}

template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::FreeListNode(ListNode* a_listNode)
{
#ifdef RTREE_DONT_USE_MEMPOOLS
	delete a_listNode;
#else // RTREE_DONT_USE_MEMPOOLS
	// EXAMPLE
#endif // RTREE_DONT_USE_MEMPOOLS
}

template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::InitNode(Node* a_node)
{
	a_node->m_count = 0;
	a_node->m_level = -1;
}

template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::InitRect(Rect* a_rect)
{
	for (int index = 0; index < NUMDIMS; ++index)
	{
		a_rect->m_min[index] = (ELEMTYPE)0;
		a_rect->m_max[index] = (ELEMTYPE)0;
	}
}

// Inserts a new data rectangle into the index structure.
// Recursively descends tree, propagates splits back up.
// Returns 0 if node was not split.  Old node updated.
// If node was split, returns 1 and sets the pointer pointed to by
// new_node to point to the new node.  Old node updated to become one of two.
// The level argument specifies the number of steps up from the leaf
// level to insert; e.g. a data rectangle goes in at level = 0.
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
bool GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::InsertRectRec(Rect* a_rect, const DATATYPE& a_id, Node* a_node, Node** a_newNode, int a_level)
{
	GASSERT(a_rect && a_node && a_newNode);
	GASSERT(a_level >= 0 && a_level <= a_node->m_level);

	int index;
	Branch branch;
	Node* otherNode;

	// Still above level for insertion, go down tree recursively
	if (a_node->m_level > a_level)
	{
		index = PickBranch(a_rect, a_node);
		if (!InsertRectRec(a_rect, a_id, a_node->m_branch[index].m_child, &otherNode, a_level))
		{
			// Child was not split
			a_node->m_branch[index].m_rect = CombineRect(a_rect, &(a_node->m_branch[index].m_rect));
			return false;
		}
		else // Child was split
		{
			a_node->m_branch[index].m_rect = NodeCover(a_node->m_branch[index].m_child);
			branch.m_child = otherNode;
			branch.m_rect = NodeCover(otherNode);
			return AddBranch(&branch, a_node, a_newNode);
		}
	}
	else if (a_node->m_level == a_level) // Have reached level for insertion. Add rect, split if necessary
	{
		branch.m_rect = *a_rect;
		branch.m_child = (Node*)a_id;
		// Child field of leaves contains id of data record
		return AddBranch(&branch, a_node, a_newNode);
	}
	else
	{
		// Should never occur
		GASSERT(0);
		return false;
	}
}

// Insert a data rectangle into an index structure.
// InsertRect provides for splitting the root;
// returns 1 if root was split, 0 if it was not.
// The level argument specifies the number of steps up from the leaf
// level to insert; e.g. a data rectangle goes in at level = 0.
// InsertRect2 does the recursion.
//
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
bool GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::InsertRect(Rect* a_rect, const DATATYPE& a_id, Node** a_root, int a_level)
{
	GASSERT(a_rect && a_root);
	GASSERT(a_level >= 0 && a_level <= (*a_root)->m_level);
#ifdef _DEBUG
	for (int index = 0; index < NUMDIMS; ++index)
	{
		GASSERT(a_rect->m_min[index] <= a_rect->m_max[index]);
	}
#endif //_DEBUG  

	Node* newRoot;
	Node* newNode;
	Branch branch;

	if (InsertRectRec(a_rect, a_id, *a_root, &newNode, a_level))  // Root split
	{
		newRoot = AllocNode();  // Grow tree taller and new root
		newRoot->m_level = (*a_root)->m_level + 1;
		branch.m_rect = NodeCover(*a_root);
		branch.m_child = *a_root;
		AddBranch(&branch, newRoot, GNULL);
		branch.m_rect = NodeCover(newNode);
		branch.m_child = newNode;
		AddBranch(&branch, newRoot, GNULL);
		*a_root = newRoot;
		return true;
	}

	return false;
}

// Find the smallest rectangle that includes all rectangles in branches of a node.
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
typename GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::Rect GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::NodeCover(Node* a_node)
{
	GASSERT(a_node);

	int firstTime = true;
	Rect rect;
	InitRect(&rect);

	for (int index = 0; index < a_node->m_count; ++index)
	{
		if (firstTime)
		{
			rect = a_node->m_branch[index].m_rect;
			firstTime = false;
		}
		else
		{
			rect = CombineRect(&rect, &(a_node->m_branch[index].m_rect));
		}
	}

	return rect;
}

// Add a branch to a node.  Split the node if necessary.
// Returns 0 if node not split.  Old node updated.
// Returns 1 if node split, sets *new_node to address of new node.
// Old node updated, becomes one of two.
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
bool GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::AddBranch(Branch* a_branch, Node* a_node, Node** a_newNode)
{
	GASSERT(a_branch);
	GASSERT(a_node);

	if (a_node->m_count < MAXNODES)  // Split won't be necessary
	{
		a_node->m_branch[a_node->m_count] = *a_branch;
		++a_node->m_count;

		return false;
	}
	else
	{
		GASSERT(a_newNode);

		SplitNode(a_node, a_branch, a_newNode);
		return true;
	}
}

// Disconnect a dependent node.
// Caller must return (or stop using iteration index) after this as count has changed
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::DisconnectBranch(Node* a_node, int a_index)
{
	GASSERT(a_node && (a_index >= 0) && (a_index < MAXNODES));
	GASSERT(a_node->m_count > 0);

	// Remove element by swapping with the last element to prevent gaps in array
	a_node->m_branch[a_index] = a_node->m_branch[a_node->m_count - 1];

	--a_node->m_count;
}

// Pick a branch.  Pick the one that will need the smallest increase
// in area to accomodate the new rectangle.  This will result in the
// least total area for the covering rectangles in the current node.
// In case of a tie, pick the one which was smaller before, to get
// the best resolution when searching.
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
int GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::PickBranch(Rect* a_rect, Node* a_node)
{
	GASSERT(a_rect && a_node);

	bool firstTime = true;
	ELEMTYPEREAL increase;
	ELEMTYPEREAL bestIncr = (ELEMTYPEREAL)-1;
	ELEMTYPEREAL area;
	ELEMTYPEREAL bestArea;
	int best;
	Rect tempRect;

	for (int index = 0; index < a_node->m_count; ++index)
	{
		Rect* curRect = &a_node->m_branch[index].m_rect;
		area = CalcRectVolume(curRect);
		tempRect = CombineRect(a_rect, curRect);
		increase = CalcRectVolume(&tempRect) - area;
		if ((increase < bestIncr) || firstTime)
		{
			best = index;
			bestArea = area;
			bestIncr = increase;
			firstTime = false;
		}
		else if ((increase == bestIncr) && (area < bestArea))
		{
			best = index;
			bestArea = area;
			bestIncr = increase;
		}
	}
	return best;
}

// Combine two rectangles into larger one containing both
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
typename GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::Rect GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::CombineRect(Rect* a_rectA, Rect* a_rectB)
{
	GASSERT(a_rectA && a_rectB);

	Rect newRect;

	for (int index = 0; index < NUMDIMS; ++index)
	{
		newRect.m_min[index] = GMath::Min(a_rectA->m_min[index], a_rectB->m_min[index]);
		newRect.m_max[index] = GMath::Max(a_rectA->m_max[index], a_rectB->m_max[index]);
	}

	return newRect;
}

// Split a node.
// Divides the nodes branches and the extra one between two nodes.
// Old node is one of the new ones, and one really new one is created.
// Tries more than one method for choosing a partition, uses best result.
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::SplitNode(Node* a_node, Branch* a_branch, Node** a_newNode)
{
	GASSERT(a_node);
	GASSERT(a_branch);

	// Could just use local here, but member or external is faster since it is reused
	PartitionVars localVars;
	PartitionVars* parVars = &localVars;
	int level;

	// Load all the branches into a buffer, initialize old node
	level = a_node->m_level;
	GetBranches(a_node, a_branch, parVars);

	// Find partition
	ChoosePartition(parVars, MINNODES);

	// Put branches from buffer into 2 nodes according to chosen partition
	*a_newNode = AllocNode();
	(*a_newNode)->m_level = a_node->m_level = level;
	LoadNodes(a_node, *a_newNode, parVars);

	GASSERT((a_node->m_count + (*a_newNode)->m_count) == parVars->m_total);
}

// Calculate the n-dimensional volume of a rectangle
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
ELEMTYPEREAL GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::RectVolume(Rect* a_rect)
{
	GASSERT(a_rect);

	ELEMTYPEREAL volume = (ELEMTYPEREAL)1;

	for (int index = 0; index < NUMDIMS; ++index)
	{
		volume *= a_rect->m_max[index] - a_rect->m_min[index];
	}

	GASSERT(volume >= (ELEMTYPEREAL)0);

	return volume;
}

// The exact volume of the bounding sphere for the given Rect
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
ELEMTYPEREAL GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::RectSphericalVolume(Rect* a_rect)
{
	GASSERT(a_rect);

	ELEMTYPEREAL sumOfSquares = (ELEMTYPEREAL)0;
	ELEMTYPEREAL radius;

	for (int index = 0; index < NUMDIMS; ++index)
	{
		ELEMTYPEREAL halfExtent = ((ELEMTYPEREAL)a_rect->m_max[index] - (ELEMTYPEREAL)a_rect->m_min[index]) * 0.5f;
		sumOfSquares += halfExtent * halfExtent;
	}

	radius = (ELEMTYPEREAL)sqrt(sumOfSquares);

	// Pow maybe slow, so test for common dims like 2,3 and just use x*x, x*x*x.
	if (NUMDIMS == 3)
	{
		return (radius * radius * radius * m_unitSphereVolume);
	}
	else if (NUMDIMS == 2)
	{
		return (radius * radius * m_unitSphereVolume);
	}
	else
	{
		return (ELEMTYPEREAL)(pow(radius, NUMDIMS) * m_unitSphereVolume);
	}
}

// Use one of the methods to calculate retangle volume
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
ELEMTYPEREAL GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::CalcRectVolume(Rect* a_rect)
{
#ifdef RTREE_USE_SPHERICAL_VOLUME
	return RectSphericalVolume(a_rect); // Slower but helps certain merge cases
#else // RTREE_USE_SPHERICAL_VOLUME
	return RectVolume(a_rect); // Faster but can cause poor merges
#endif // RTREE_USE_SPHERICAL_VOLUME  
}

// Load branch buffer with branches from full node plus the extra branch.
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::GetBranches(Node* a_node, Branch* a_branch, PartitionVars* a_parVars)
{
	GASSERT(a_node);
	GASSERT(a_branch);

	GASSERT(a_node->m_count == MAXNODES);

	// Load the branch buffer
	for (int index = 0; index < MAXNODES; ++index)
	{
		a_parVars->m_branchBuf[index] = a_node->m_branch[index];
	}
	a_parVars->m_branchBuf[MAXNODES] = *a_branch;
	a_parVars->m_branchCount = MAXNODES + 1;

	// Calculate rect containing all in the set
	a_parVars->m_coverSplit = a_parVars->m_branchBuf[0].m_rect;
	for (int index = 1; index < MAXNODES + 1; ++index)
	{
		a_parVars->m_coverSplit = CombineRect(&a_parVars->m_coverSplit, &a_parVars->m_branchBuf[index].m_rect);
	}
	a_parVars->m_coverSplitArea = CalcRectVolume(&a_parVars->m_coverSplit);

	InitNode(a_node);
}

// Method #0 for choosing a partition:
// As the seeds for the two groups, pick the two rects that would waste the
// most area if covered by a single rectangle, i.e. evidently the worst pair
// to have in the same group.
// Of the remaining, one at a time is chosen to be put in one of the two groups.
// The one chosen is the one with the greatest difference in area expansion
// depending on which group - the rect most strongly attracted to one group
// and repelled from the other.
// If one group gets too full (more would force other group to violate min
// fill requirement) then other group gets the rest.
// These last are the ones that can go in either group most easily.
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::ChoosePartition(PartitionVars* a_parVars, int a_minFill)
{
	GASSERT(a_parVars);

	ELEMTYPEREAL biggestDiff;
	int group, chosen, betterGroup;

	InitParVars(a_parVars, a_parVars->m_branchCount, a_minFill);
	PickSeeds(a_parVars);

	while (((a_parVars->m_count[0] + a_parVars->m_count[1]) < a_parVars->m_total)
		&& (a_parVars->m_count[0] < (a_parVars->m_total - a_parVars->m_minFill))
		&& (a_parVars->m_count[1] < (a_parVars->m_total - a_parVars->m_minFill)))
	{
		biggestDiff = (ELEMTYPEREAL)-1;
		for (int index = 0; index < a_parVars->m_total; ++index)
		{
			if (!a_parVars->m_taken[index])
			{
				Rect* curRect = &a_parVars->m_branchBuf[index].m_rect;
				Rect rect0 = CombineRect(curRect, &a_parVars->m_cover[0]);
				Rect rect1 = CombineRect(curRect, &a_parVars->m_cover[1]);
				ELEMTYPEREAL growth0 = CalcRectVolume(&rect0) - a_parVars->m_area[0];
				ELEMTYPEREAL growth1 = CalcRectVolume(&rect1) - a_parVars->m_area[1];
				ELEMTYPEREAL diff = growth1 - growth0;
				if (diff >= 0)
				{
					group = 0;
				}
				else
				{
					group = 1;
					diff = -diff;
				}

				if (diff > biggestDiff)
				{
					biggestDiff = diff;
					chosen = index;
					betterGroup = group;
				}
				else if ((diff == biggestDiff) && (a_parVars->m_count[group] < a_parVars->m_count[betterGroup]))
				{
					chosen = index;
					betterGroup = group;
				}
			}
		}
		Classify(chosen, betterGroup, a_parVars);
	}

	// If one group too full, put remaining rects in the other
	if ((a_parVars->m_count[0] + a_parVars->m_count[1]) < a_parVars->m_total)
	{
		if (a_parVars->m_count[0] >= a_parVars->m_total - a_parVars->m_minFill)
		{
			group = 1;
		}
		else
		{
			group = 0;
		}
		for (int index = 0; index < a_parVars->m_total; ++index)
		{
			if (!a_parVars->m_taken[index])
			{
				Classify(index, group, a_parVars);
			}
		}
	}

	GASSERT((a_parVars->m_count[0] + a_parVars->m_count[1]) == a_parVars->m_total);
	GASSERT((a_parVars->m_count[0] >= a_parVars->m_minFill) &&
		(a_parVars->m_count[1] >= a_parVars->m_minFill));
}

// Copy branches from the buffer into two nodes according to the partition.
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::LoadNodes(Node* a_nodeA, Node* a_nodeB, PartitionVars* a_parVars)
{
	GASSERT(a_nodeA);
	GASSERT(a_nodeB);
	GASSERT(a_parVars);

	for (int index = 0; index < a_parVars->m_total; ++index)
	{
		GASSERT(a_parVars->m_partition[index] == 0 || a_parVars->m_partition[index] == 1);

		if (a_parVars->m_partition[index] == 0)
		{
			AddBranch(&a_parVars->m_branchBuf[index], a_nodeA, GNULL);
		}
		else if (a_parVars->m_partition[index] == 1)
		{
			AddBranch(&a_parVars->m_branchBuf[index], a_nodeB, GNULL);
		}
	}
}

// Initialize a PartitionVars structure.
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::InitParVars(PartitionVars* a_parVars, int a_maxRects, int a_minFill)
{
	GASSERT(a_parVars);

	a_parVars->m_count[0] = a_parVars->m_count[1] = 0;
	a_parVars->m_area[0] = a_parVars->m_area[1] = (ELEMTYPEREAL)0;
	a_parVars->m_total = a_maxRects;
	a_parVars->m_minFill = a_minFill;
	for (int index = 0; index < a_maxRects; ++index)
	{
		a_parVars->m_taken[index] = false;
		a_parVars->m_partition[index] = -1;
	}
}

template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::PickSeeds(PartitionVars* a_parVars)
{
	int seed0, seed1;
	ELEMTYPEREAL worst, waste;
	ELEMTYPEREAL area[MAXNODES + 1];

	for (int index = 0; index < a_parVars->m_total; ++index)
	{
		area[index] = CalcRectVolume(&a_parVars->m_branchBuf[index].m_rect);
	}

	worst = -a_parVars->m_coverSplitArea - 1;
	for (int indexA = 0; indexA < a_parVars->m_total - 1; ++indexA)
	{
		for (int indexB = indexA + 1; indexB < a_parVars->m_total; ++indexB)
		{
			Rect oneRect = CombineRect(&a_parVars->m_branchBuf[indexA].m_rect, &a_parVars->m_branchBuf[indexB].m_rect);
			waste = CalcRectVolume(&oneRect) - area[indexA] - area[indexB];
			if (waste > worst)
			{
				worst = waste;
				seed0 = indexA;
				seed1 = indexB;
			}
		}
	}
	Classify(seed0, 0, a_parVars);
	Classify(seed1, 1, a_parVars);
}

// Put a branch in one of the groups.
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::Classify(int a_index, int a_group, PartitionVars* a_parVars)
{
	GASSERT(a_parVars);
	GASSERT(!a_parVars->m_taken[a_index]);

	a_parVars->m_partition[a_index] = a_group;
	a_parVars->m_taken[a_index] = true;

	if (a_parVars->m_count[a_group] == 0)
	{
		a_parVars->m_cover[a_group] = a_parVars->m_branchBuf[a_index].m_rect;
	}
	else
	{
		a_parVars->m_cover[a_group] = CombineRect(&a_parVars->m_branchBuf[a_index].m_rect, &a_parVars->m_cover[a_group]);
	}
	a_parVars->m_area[a_group] = CalcRectVolume(&a_parVars->m_cover[a_group]);
	++a_parVars->m_count[a_group];
}

// Delete a data rectangle from an index structure.
// Pass in a pointer to a Rect, the tid of the record, ptr to ptr to root node.
// Returns 1 if record not found, 0 if success.
// RemoveRect provides for eliminating the root.
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
bool GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::RemoveRect(Rect* a_rect, const DATATYPE& a_id, Node** a_root)
{
	GASSERT(a_rect && a_root);
	GASSERT(*a_root);

	Node* tempNode;
	ListNode* reInsertList = GNULL;

	if (!RemoveRectRec(a_rect, a_id, *a_root, &reInsertList))
	{
		// Found and deleted a data item
		// Reinsert any branches from eliminated nodes
		while (reInsertList)
		{
			tempNode = reInsertList->m_node;

			for (int index = 0; index < tempNode->m_count; ++index)
			{
				InsertRect(&(tempNode->m_branch[index].m_rect),
					tempNode->m_branch[index].m_data,
					a_root,
					tempNode->m_level);
			}

			ListNode* remLNode = reInsertList;
			reInsertList = reInsertList->m_next;

			FreeNode(remLNode->m_node);
			FreeListNode(remLNode);
		}

		// Check for redundant root (not leaf, 1 child) and eliminate
		if ((*a_root)->m_count == 1 && (*a_root)->IsInternalNode())
		{
			tempNode = (*a_root)->m_branch[0].m_child;

			GASSERT(tempNode);
			FreeNode(*a_root);
			*a_root = tempNode;
		}
		return false;
	}
	else
	{
		return true;
	}
}

// Delete a rectangle from non-root part of an index structure.
// Called by RemoveRect.  Descends tree recursively,
// merges branches on the way back up.
// Returns 1 if record not found, 0 if success.
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
bool GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::RemoveRectRec(Rect* a_rect, const DATATYPE& a_id, Node* a_node, ListNode** a_listNode)
{
	GASSERT(a_rect && a_node && a_listNode);
	GASSERT(a_node->m_level >= 0);

	if (a_node->IsInternalNode())  // not a leaf node
	{
		for (int index = 0; index < a_node->m_count; ++index)
		{
			if (Overlap(a_rect, &(a_node->m_branch[index].m_rect)))
			{
				if (!RemoveRectRec(a_rect, a_id, a_node->m_branch[index].m_child, a_listNode))
				{
					if (a_node->m_branch[index].m_child->m_count >= MINNODES)
					{
						// child removed, just resize parent rect
						a_node->m_branch[index].m_rect = NodeCover(a_node->m_branch[index].m_child);
					}
					else
					{
						// child removed, not enough entries in node, eliminate node
						ReInsert(a_node->m_branch[index].m_child, a_listNode);
						DisconnectBranch(a_node, index); // Must return after this call as count has changed
					}
					return false;
				}
			}
		}
		return true;
	}
	else // A leaf node
	{
		for (int index = 0; index < a_node->m_count; ++index)
		{
			if (a_node->m_branch[index].m_child == (Node*)a_id)
			{
				DisconnectBranch(a_node, index); // Must return after this call as count has changed
				return false;
			}
		}
		return true;
	}
}

// Decide whether two rectangles overlap.
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
bool GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::Overlap(Rect* a_rectA, Rect* a_rectB)
{
	GASSERT(a_rectA && a_rectB);

	for (int index = 0; index < NUMDIMS; ++index)
	{
		if (a_rectA->m_min[index] > a_rectB->m_max[index] ||
			a_rectB->m_min[index] > a_rectA->m_max[index])
		{
			return false;
		}
	}
	return true;
}

// Add a node to the reinsertion list.  All its branches will later
// be reinserted into the index structure.
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
void GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::ReInsert(Node* a_node, ListNode** a_listNode)
{
	ListNode* newListNode;

	newListNode = AllocListNode();
	newListNode->m_node = a_node;
	newListNode->m_next = *a_listNode;
	*a_listNode = newListNode;
}

// Search in an index tree or subtree for all data retangles that overlap the argument rectangle.
template<typename DATATYPE, typename ELEMTYPE, gsize NUMDIMS, typename ELEMTYPEREAL, gsize TMAXNODES, gsize TMINNODES>
inline bool GRTree<DATATYPE, ELEMTYPE, NUMDIMS, ELEMTYPEREAL, TMAXNODES, TMINNODES>::Search(Node* a_node, Rect* a_rect, int& a_foundCount, bool __cdecl a_resultCallback(DATATYPE a_data, void* a_context), void* a_context)
{
	GASSERT(a_node);
	GASSERT(a_node->m_level >= 0);
	GASSERT(a_rect);

	if (a_node->IsInternalNode()) // This is an internal node in the tree
	{
		for (int index = 0; index < a_node->m_count; ++index)
		{
			if (Overlap(a_rect, &a_node->m_branch[index].m_rect))
			{
				if (!Search(a_node->m_branch[index].m_child, a_rect, a_foundCount, a_resultCallback, a_context))
				{
					return false; // Don't continue searching
				}
			}
		}
	}
	else // This is a leaf node
	{
		for (int index = 0; index < a_node->m_count; ++index)
		{
			if (Overlap(a_rect, &a_node->m_branch[index].m_rect))
			{
				DATATYPE& id = a_node->m_branch[index].m_data;

				// NOTE: There are different ways to return results.  Here's where to modify
				if (&a_resultCallback)
				{
					++a_foundCount;
					if (!a_resultCallback(id, a_context))
					{
						return false; // Don't continue searching
					}
				}
			}
		}
	}

	return true; // Continue searching
}

#endif // _CORE_R_TREE_INLINE_