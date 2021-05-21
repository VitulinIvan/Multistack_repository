#include "Stack.h"

#include <../gtest/gtest.h>


TEST(TStack, create_stack)
{
	TStack<int> S(3);
	EXPECT_NO_THROW();
}

TEST(TStack, throw_create_negative_size_stack)
{
	
	EXPECT_ANY_THROW(TStack<int> S(-3));
}

TEST(TStack, push_any_elements)
{
	TStack<int> S(4);
	S.Push(1);
	S.Push(2);
	EXPECT_EQ(2, S.Get());
}

TEST(TStack, pop_any_elements)
{
	TStack<int> S(4);
	S.Push(1);
	S.Push(2);
	S.Push(3);
	S.Pop();
	S.Pop();
	EXPECT_EQ(1, S.Get());
}

TEST(TStack, find_max_element)
{
	TStack<int> S(4);
	S.Push(1);
	S.Push(5);
	S.Push(-3);
	EXPECT_EQ(5, S.GetMaxElement());
}

TEST(TStack, find_min_element)
{
	TStack<int> S(4);
	S.Push(1);
	S.Push(5);
	S.Push(-3);
	EXPECT_EQ(-3, S.GetMinElement());
}

TEST(TStack, write_to_file_stack)
{
	const int size = 9;
	TStack<int> S(size);
	for (int i = 0; i < size / 2; i++)
		S.Push(i);
	S.WriteToFile("StackOI.txt");
	string ExpString = "0123";
	string StackString = "";
	ifstream fin("StackOI.txt");
	fin >> StackString;
	fin.close();
	EXPECT_EQ(ExpString, StackString);
}