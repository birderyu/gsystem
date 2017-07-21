#pragma once
#include <gtest/gtest.h>
#include "gbintree.h"
#include "gbstree.h"
#include "grbtree.h"
#include "gstring.h"

TEST(RedBlackTreeTest, HandleNoneZeroInput)
{
	using namespace gsystem;

	GRedBlackTree<gint, GString> bst;
	bst.Insert(5, GString("step1"));
	bst.Insert(3, GString("step1"));
	bst.Insert(2, GString("step1"));
	bst.Insert(10, GString("step1"));


}
