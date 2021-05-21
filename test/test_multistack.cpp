#include "MultiStack.h"

#include <../gtest/gtest.h>
#include <sstream>

TEST(TMultiStack, create_multistack)
{
	TMultiStack<int> MS(1,1);
	EXPECT_NO_THROW();
}

TEST(TMultiStack, push_any_elements)
{
	TMultiStack<int>MS(6, 3);
	MS.Push(1, 0);
	MS.Push(2, 0);
	MS.Push(3, 1);
	MS.Push(4, 2);
	EXPECT_EQ(2, MS.Get(0));
}

TEST(TMultiStack, pop_any_elements)
{
	TMultiStack<int>MS(6, 3);
	MS.Push(1, 0);
	MS.Push(2, 0);
	MS.Push(3, 1);
	MS.Push(4, 2);
	MS.Pop(2);
	MS.Pop(1);
	MS.Pop(0);
	EXPECT_EQ(1, MS.Get(0));
}

TEST(TMultiStack, repack_test)
{
	TMultiStack<int>MS(9, 3);
	MS.Push(1, 0);
	MS.Push(2, 0);
	MS.Push(3, 1);
	MS.Push(4, 1);
	MS.Push(5, 2);
	MS.Push(6, 0);
	MS.Push(7, 0);
	MS.Push(8, 0);
	MS.Push(9, 0);
	string expMS = "126789345";
	EXPECT_EQ(expMS, MS.GetMultiStack());
}

TEST(TMultiStack, find_min_elem_stack)
{
	TMultiStack<int>MS(9, 3);
	MS.Push(1, 0);
	MS.Push(2, 0);
	MS.Push(3, 0);
	MS.Push(4, 1);
	MS.Push(5, 1);
	MS.Push(6, 2);
	MS.Push(7, 2);
	MS.Push(8, 2);

	EXPECT_EQ(1, MS.GetMinElemStack());
}

TEST(TMultiStack, write_to_file_multistack)
{
	TMultiStack<int>MS(9, 3);
	MS.Push(1, 0);
	MS.Push(2, 0);
	MS.Push(3, 0);
	MS.Push(4, 1);
	MS.Push(5, 1);
	MS.Push(6, 1);
	MS.Push(7, 2);
	MS.Push(8, 2);
	MS.Push(9, 2);
	MS.WriteToFile("MultiStackOI.txt");
	string ExpString = "123456789";
	string MultiStack_String = "";
	ifstream fin("MultiStackOI.txt");
	fin >> MultiStack_String;
	fin.close();
	EXPECT_EQ(ExpString, MultiStack_String);
}

