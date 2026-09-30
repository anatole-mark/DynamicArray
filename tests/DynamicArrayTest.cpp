#include "../include/DynamicArray.hpp"
#include "gtest/gtest.h"

TEST(DynamicArrayTest, EmptyConstructor)
{
    DynamicArray<int> arrInt;
    EXPECT_EQ(arrInt.size(), 0);

    DynamicArray<std::string> arrStr;
    EXPECT_EQ(arrStr.size(), 0);
}

TEST(DynamicArrayTest, CapConstructor)
{
    DynamicArray<int> arrInt = DynamicArray<int>(4);
    EXPECT_EQ(arrInt.size(), 0);

    DynamicArray<std::string> arrStr = DynamicArray<std::string>(4);
    EXPECT_EQ(arrStr.size(), 0);
}

TEST(DynamicArrayTest, CopyConstructor)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(1);
    DynamicArray<int> arrInt1 = DynamicArray<int>(arrInt);
    EXPECT_EQ(arrInt1.size(), 1);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("Hi");
    DynamicArray<std::string> arrStr1 = DynamicArray<std::string>(arrStr);
    EXPECT_EQ(arrStr1.size(), 1);
}

TEST(DynamicArrayTest, PushBack)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(1);
    arrInt.pushBack(2);
    arrInt.pushBack(3);
    EXPECT_EQ(arrInt.size(), 3);
    EXPECT_EQ(arrInt[0], 1);
    EXPECT_EQ(arrInt[1], 2);
    EXPECT_EQ(arrInt[2], 3);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("Hi");
    arrStr.pushBack("Hiya");
    arrStr.pushBack("Howdy");
    EXPECT_EQ(arrStr.size(), 3);
    EXPECT_EQ(arrStr[0], "Hi");
    EXPECT_EQ(arrStr[1], "Hiya");
    EXPECT_EQ(arrStr[2], "Howdy");
}

TEST(DynamicArrayTest, IncreaseCapacity)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(1);
    arrInt.pushBack(2);
    arrInt.pushBack(3);
    arrInt.pushBack(4);
    arrInt.pushBack(5);
    EXPECT_EQ(arrInt.capacity(), 8);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("Hi");
    arrStr.pushBack("Hiya");
    arrStr.pushBack("Howdy");
    arrStr.pushBack("Mate");
    arrStr.pushBack("Alright?");
    EXPECT_EQ(arrStr.capacity(), 8);
}

TEST(DynamicArrayTest, Remove)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(1);
    arrInt.pushBack(2);
    arrInt.remove(0);
    EXPECT_EQ(arrInt.size(), 1);
    EXPECT_EQ(arrInt[0], 2);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("Hi");
    arrStr.pushBack("Hiya");
    arrStr.remove(0);
    EXPECT_EQ(arrStr.size(), 1);
    EXPECT_EQ(arrStr[0], "Hiya");
}

TEST(DynamicArrayTest, MoveConstructor)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(1);
    arrInt.pushBack(2);
    arrInt.pushBack(3);
    DynamicArray<int> movedInt = std::move(arrInt);
    EXPECT_EQ(movedInt.size(), 3);
    EXPECT_EQ(movedInt[0], 1);
    EXPECT_EQ(movedInt[1], 2);
    EXPECT_EQ(movedInt[2], 3);
    EXPECT_EQ(arrInt.size(), 0);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("Hello");
    arrStr.pushBack("World");
    DynamicArray<std::string> movedStr = std::move(arrStr);
    EXPECT_EQ(movedStr.size(), 2);
    EXPECT_EQ(movedStr[0], "Hello");
    EXPECT_EQ(movedStr[1], "World");
    EXPECT_EQ(arrStr.size(), 0);
}

TEST(DynamicArrayTest, AssignmentOperator)
{
    DynamicArray<int> arrInt1;
    arrInt1.pushBack(10);
    arrInt1.pushBack(20);
    DynamicArray<int> arrInt2;
    arrInt2.pushBack(30);
    arrInt2.pushBack(40);
    arrInt2.pushBack(50);
    arrInt1 = arrInt2;
    EXPECT_EQ(arrInt1.size(), 3);
    EXPECT_EQ(arrInt1[0], 30);
    EXPECT_EQ(arrInt1[1], 40);
    EXPECT_EQ(arrInt1[2], 50);
    EXPECT_EQ(arrInt2.size(), 3);

    DynamicArray<std::string> arrStr1;
    arrStr1.pushBack("First");
    DynamicArray<std::string> arrStr2;
    arrStr2.pushBack("Alpha");
    arrStr2.pushBack("Beta");
    arrStr1 = arrStr2;
    EXPECT_EQ(arrStr1.size(), 2);
    EXPECT_EQ(arrStr1[0], "Alpha");
    EXPECT_EQ(arrStr1[1], "Beta");
}

TEST(DynamicArrayTest, InsertElement)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(1);
    arrInt.pushBack(3);
    int valueInt = 2;
    arrInt.insert(1, valueInt);
    EXPECT_EQ(arrInt.size(), 3);
    EXPECT_EQ(arrInt[0], 1);
    EXPECT_EQ(arrInt[1], 2);
    EXPECT_EQ(arrInt[2], 3);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("Apple");
    arrStr.pushBack("Cherry");
    std::string valueStr = "Banana";
    arrStr.insert(1, valueStr);
    EXPECT_EQ(arrStr.size(), 3);
    EXPECT_EQ(arrStr[0], "Apple");
    EXPECT_EQ(arrStr[1], "Banana");
    EXPECT_EQ(arrStr[2], "Cherry");
}

TEST(DynamicArrayTest, InsertAtBeginning)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(2);
    arrInt.pushBack(3);

    int valueInt = 1;
    arrInt.insert(0, valueInt);
    EXPECT_EQ(arrInt.size(), 3);
    EXPECT_EQ(arrInt[0], 1);
    EXPECT_EQ(arrInt[1], 2);
    EXPECT_EQ(arrInt[2], 3);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("Beta");
    arrStr.pushBack("Gamma");

    std::string valueStr = "Alpha";
    arrStr.insert(0, valueStr);
    EXPECT_EQ(arrStr.size(), 3);
    EXPECT_EQ(arrStr[0], "Alpha");
    EXPECT_EQ(arrStr[1], "Beta");
    EXPECT_EQ(arrStr[2], "Gamma");
}

TEST(DynamicArrayTest, InsertAtEnd)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(1);
    arrInt.pushBack(2);

    int valueInt = 3;
    arrInt.insert(arrInt.size() - 1, valueInt);
    EXPECT_EQ(arrInt.size(), 3);
    EXPECT_EQ(arrInt[0], 1);
    EXPECT_EQ(arrInt[1], 3);
    EXPECT_EQ(arrInt[2], 2);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("First");
    arrStr.pushBack("Second");

    std::string valueStr = "Third";
    arrStr.insert(arrStr.size() - 1, valueStr);
    EXPECT_EQ(arrStr.size(), 3);
    EXPECT_EQ(arrStr[0], "First");
    EXPECT_EQ(arrStr[1], "Third");
    EXPECT_EQ(arrStr[2], "Second");
}

TEST(DynamicArrayTest, ElementAccessOperator)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(10);
    arrInt.pushBack(20);

    // Read access
    EXPECT_EQ(arrInt[0], 10);
    EXPECT_EQ(arrInt[1], 20);

    // Write access
    arrInt[0] = 100;
    arrInt[1] = 200;
    EXPECT_EQ(arrInt[0], 100);
    EXPECT_EQ(arrInt[1], 200);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("Hello");
    arrStr.pushBack("There");

    EXPECT_EQ(arrStr[0], "Hello");
    EXPECT_EQ(arrStr[1], "There");

    arrStr[0] = "Hi";
    arrStr[1] = "World";
    EXPECT_EQ(arrStr[0], "Hi");
    EXPECT_EQ(arrStr[1], "World");
}

TEST(DynamicArrayTest, ConstElementAccess)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(5);
    arrInt.pushBack(10);

    const DynamicArray<int>& constArrInt = arrInt;
    EXPECT_EQ(constArrInt[0], 5);
    EXPECT_EQ(constArrInt[1], 10);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("Constant");
    arrStr.pushBack("String");

    const DynamicArray<std::string>& constArrStr = arrStr;
    EXPECT_EQ(constArrStr[0], "Constant");
    EXPECT_EQ(constArrStr[1], "String");
}

TEST(DynamicArrayTest, RemoveFromMiddle)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(1);
    arrInt.pushBack(2);
    arrInt.pushBack(3);
    arrInt.pushBack(4);
    arrInt.pushBack(5);

    arrInt.remove(2); // Remove element at index 2 (value 3)
    EXPECT_EQ(arrInt.size(), 4);
    EXPECT_EQ(arrInt[0], 1);
    EXPECT_EQ(arrInt[1], 2);
    EXPECT_EQ(arrInt[2], 4);
    EXPECT_EQ(arrInt[3], 5);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("A");
    arrStr.pushBack("B");
    arrStr.pushBack("C");
    arrStr.pushBack("D");
    arrStr.pushBack("E");

    arrStr.remove(2); // Remove "C"
    EXPECT_EQ(arrStr.size(), 4);
    EXPECT_EQ(arrStr[0], "A");
    EXPECT_EQ(arrStr[1], "B");
    EXPECT_EQ(arrStr[2], "D");
    EXPECT_EQ(arrStr[3], "E");
}

TEST(DynamicArrayTest, RemoveFromEnd)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(1);
    arrInt.pushBack(2);
    arrInt.pushBack(3);

    arrInt.remove(2); // Remove last element
    EXPECT_EQ(arrInt.size(), 2);
    EXPECT_EQ(arrInt[0], 1);
    EXPECT_EQ(arrInt[1], 2);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("First");
    arrStr.pushBack("Second");
    arrStr.pushBack("Third");

    arrStr.remove(2); // Remove "Third"
    EXPECT_EQ(arrStr.size(), 2);
    EXPECT_EQ(arrStr[0], "First");
    EXPECT_EQ(arrStr[1], "Second");
}

TEST(DynamicArrayTest, RemoveInvalidIndex)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(1);
    arrInt.pushBack(2);

    // These should not crash
    arrInt.remove(-1);
    arrInt.remove(5);
    arrInt.remove(2);

    // Array should remain unchanged
    EXPECT_EQ(arrInt.size(), 2);
    EXPECT_EQ(arrInt[0], 1);
    EXPECT_EQ(arrInt[1], 2);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("Test");

    arrStr.remove(-1);
    arrStr.remove(10);

    EXPECT_EQ(arrStr.size(), 1);
    EXPECT_EQ(arrStr[0], "Test");
}

TEST(DynamicArrayTest, SizeMethod)
{
    DynamicArray<int> arrInt;
    EXPECT_EQ(arrInt.size(), 0);

    arrInt.pushBack(1);
    EXPECT_EQ(arrInt.size(), 1);

    arrInt.pushBack(2);
    EXPECT_EQ(arrInt.size(), 2);

    arrInt.remove(0);
    EXPECT_EQ(arrInt.size(), 1);

    arrInt.remove(0);
    EXPECT_EQ(arrInt.size(), 0);

    DynamicArray<std::string> arrStr;
    EXPECT_EQ(arrStr.size(), 0);

    arrStr.pushBack("One");
    EXPECT_EQ(arrStr.size(), 1);

    arrStr.pushBack("Two");
    EXPECT_EQ(arrStr.size(), 2);

    arrStr.remove(0);
    EXPECT_EQ(arrStr.size(), 1);
}

// ============================================
// ITERATOR TESTS
// ============================================

TEST(DynamicArrayTest, ForwardIteratorBasic)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(1);
    arrInt.pushBack(2);
    arrInt.pushBack(3);

    auto itInt = arrInt.iterator();
    EXPECT_TRUE(itInt.hasNext());
    EXPECT_EQ(itInt.get(), 1);

    itInt.next();
    EXPECT_TRUE(itInt.hasNext());
    EXPECT_EQ(itInt.get(), 2);

    itInt.next();
    EXPECT_TRUE(itInt.hasNext());
    EXPECT_EQ(itInt.get(), 3);

    itInt.next();
    EXPECT_FALSE(itInt.hasNext());

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("A");
    arrStr.pushBack("B");

    auto itStr = arrStr.iterator();
    EXPECT_TRUE(itStr.hasNext());
    EXPECT_EQ(itStr.get(), "A");

    itStr.next();
    EXPECT_TRUE(itStr.hasNext());
    EXPECT_EQ(itStr.get(), "B");

    itStr.next();
    EXPECT_FALSE(itStr.hasNext());
}

TEST(DynamicArrayTest, ForwardIteratorLoop)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(10);
    arrInt.pushBack(20);
    arrInt.pushBack(30);

    std::vector<int> resultInt;
    for (auto it = arrInt.iterator(); it.hasNext(); it.next())
    {
        resultInt.push_back(it.get());
    }

    EXPECT_EQ(resultInt.size(), 3);
    EXPECT_EQ(resultInt[0], 10);
    EXPECT_EQ(resultInt[1], 20);
    EXPECT_EQ(resultInt[2], 30);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("Hello");
    arrStr.pushBack("World");
    arrStr.pushBack("!");

    std::vector<std::string> resultStr;
    for (auto it = arrStr.iterator(); it.hasNext(); it.next())
    {
        resultStr.push_back(it.get());
    }

    EXPECT_EQ(resultStr.size(), 3);
    EXPECT_EQ(resultStr[0], "Hello");
    EXPECT_EQ(resultStr[1], "World");
    EXPECT_EQ(resultStr[2], "!");
}

TEST(DynamicArrayTest, ForwardIteratorModification)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(1);
    arrInt.pushBack(2);
    arrInt.pushBack(3);

    // Double each element using iterator
    for (auto it = arrInt.iterator(); it.hasNext(); it.next())
    {
        it.set(it.get() * 2);
    }

    EXPECT_EQ(arrInt[0], 2);
    EXPECT_EQ(arrInt[1], 4);
    EXPECT_EQ(arrInt[2], 6);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("cat");
    arrStr.pushBack("dog");

    // Append to each string using iterator
    for (auto it = arrStr.iterator(); it.hasNext(); it.next())
    {
        it.set(it.get() + "_animal");
    }

    EXPECT_EQ(arrStr[0], "cat_animal");
    EXPECT_EQ(arrStr[1], "dog_animal");
}

TEST(DynamicArrayTest, ReverseIteratorBasic)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(1);
    arrInt.pushBack(2);
    arrInt.pushBack(3);

    auto ritInt = arrInt.reverseIterator();
    EXPECT_TRUE(ritInt.hasNext());
    EXPECT_EQ(ritInt.get(), 3);

    ritInt.next();
    EXPECT_TRUE(ritInt.hasNext());
    EXPECT_EQ(ritInt.get(), 2);

    ritInt.next();
    EXPECT_TRUE(ritInt.hasNext());
    EXPECT_EQ(ritInt.get(), 1);

    ritInt.next();
    EXPECT_FALSE(ritInt.hasNext());

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("A");
    arrStr.pushBack("B");
    arrStr.pushBack("C");

    auto ritStr = arrStr.reverseIterator();
    EXPECT_TRUE(ritStr.hasNext());
    EXPECT_EQ(ritStr.get(), "C");

    ritStr.next();
    EXPECT_EQ(ritStr.get(), "B");

    ritStr.next();
    EXPECT_EQ(ritStr.get(), "A");

    ritStr.next();
    EXPECT_FALSE(ritStr.hasNext());
}

TEST(DynamicArrayTest, ReverseIteratorLoop)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(1);
    arrInt.pushBack(2);
    arrInt.pushBack(3);

    std::vector<int> resultInt;
    for (auto it = arrInt.reverseIterator(); it.hasNext(); it.next())
    {
        resultInt.push_back(it.get());
    }

    EXPECT_EQ(resultInt.size(), 3);
    EXPECT_EQ(resultInt[0], 3);
    EXPECT_EQ(resultInt[1], 2);
    EXPECT_EQ(resultInt[2], 1);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("First");
    arrStr.pushBack("Second");
    arrStr.pushBack("Third");

    std::vector<std::string> resultStr;
    for (auto it = arrStr.reverseIterator(); it.hasNext(); it.next())
    {
        resultStr.push_back(it.get());
    }

    EXPECT_EQ(resultStr.size(), 3);
    EXPECT_EQ(resultStr[0], "Third");
    EXPECT_EQ(resultStr[1], "Second");
    EXPECT_EQ(resultStr[2], "First");
}

TEST(DynamicArrayTest, ConstIterator)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(100);
    arrInt.pushBack(200);
    arrInt.pushBack(300);

    const DynamicArray<int>& constArrInt = arrInt;

    std::vector<int> resultInt;
    for (auto it = constArrInt.iterator(); it.hasNext(); it.next())
    {
        resultInt.push_back(it.get());
    }

    EXPECT_EQ(resultInt.size(), 3);
    EXPECT_EQ(resultInt[0], 100);
    EXPECT_EQ(resultInt[1], 200);
    EXPECT_EQ(resultInt[2], 300);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("Read");
    arrStr.pushBack("Only");

    const DynamicArray<std::string>& constArrStr = arrStr;

    std::vector<std::string> resultStr;
    for (auto it = constArrStr.iterator(); it.hasNext(); it.next())
    {
        resultStr.push_back(it.get());
    }

    EXPECT_EQ(resultStr.size(), 2);
    EXPECT_EQ(resultStr[0], "Read");
    EXPECT_EQ(resultStr[1], "Only");
}

TEST(DynamicArrayTest, ConstReverseIterator)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(5);
    arrInt.pushBack(10);
    arrInt.pushBack(15);

    const DynamicArray<int>& constArrInt = arrInt;

    std::vector<int> resultInt;
    for (auto it = constArrInt.reverseIterator(); it.hasNext(); it.next())
    {
        resultInt.push_back(it.get());
    }

    EXPECT_EQ(resultInt.size(), 3);
    EXPECT_EQ(resultInt[0], 15);
    EXPECT_EQ(resultInt[1], 10);
    EXPECT_EQ(resultInt[2], 5);

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("One");
    arrStr.pushBack("Two");
    arrStr.pushBack("Three");

    const DynamicArray<std::string>& constArrStr = arrStr;

    std::vector<std::string> resultStr;
    for (auto it = constArrStr.reverseIterator(); it.hasNext(); it.next())
    {
        resultStr.push_back(it.get());
    }

    EXPECT_EQ(resultStr.size(), 3);
    EXPECT_EQ(resultStr[0], "Three");
    EXPECT_EQ(resultStr[1], "Two");
    EXPECT_EQ(resultStr[2], "One");
}

TEST(DynamicArrayTest, IteratorOnEmptyArray)
{
    DynamicArray<int> arrInt;

    auto itInt = arrInt.iterator();
    EXPECT_FALSE(itInt.hasNext());

    auto ritInt = arrInt.reverseIterator();
    EXPECT_FALSE(ritInt.hasNext());

    DynamicArray<std::string> arrStr;

    auto itStr = arrStr.iterator();
    EXPECT_FALSE(itStr.hasNext());

    auto ritStr = arrStr.reverseIterator();
    EXPECT_FALSE(ritStr.hasNext());
}

TEST(DynamicArrayTest, IteratorWithOneElement)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(42);

    auto itInt = arrInt.iterator();
    EXPECT_TRUE(itInt.hasNext());
    EXPECT_EQ(itInt.get(), 42);
    itInt.next();
    EXPECT_FALSE(itInt.hasNext());

    auto ritInt = arrInt.reverseIterator();
    EXPECT_TRUE(ritInt.hasNext());
    EXPECT_EQ(ritInt.get(), 42);
    ritInt.next();
    EXPECT_FALSE(ritInt.hasNext());

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("Single");

    auto itStr = arrStr.iterator();
    EXPECT_TRUE(itStr.hasNext());
    EXPECT_EQ(itStr.get(), "Single");

    auto ritStr = arrStr.reverseIterator();
    EXPECT_TRUE(ritStr.hasNext());
    EXPECT_EQ(ritStr.get(), "Single");
}

TEST(DynamicArrayTest, IteratorAfterModifications)
{
    DynamicArray<int> arrInt;
    arrInt.pushBack(1);
    arrInt.pushBack(2);

    auto it = arrInt.iterator();
    EXPECT_EQ(it.get(), 1);

    // Modify array while iterator exists
    arrInt.pushBack(3);
    arrInt.remove(0);

    // Iterator might be invalidated, but let's test basic functionality
    // This tests that iterator doesn't crash after array modifications
    it = arrInt.iterator(); // Get fresh iterator
    EXPECT_TRUE(it.hasNext());

    DynamicArray<std::string> arrStr;
    arrStr.pushBack("A");

    auto itStr = arrStr.iterator();
    EXPECT_EQ(itStr.get(), "A");

    arrStr.pushBack("B");
    itStr = arrStr.iterator(); // Fresh iterator
    EXPECT_TRUE(itStr.hasNext());
}

TEST(DynamicArrayTest, MixedOperations)
{
    DynamicArray<int> arrInt;

    // Push, remove, insert, iterate
    arrInt.pushBack(1);
    arrInt.pushBack(3);

    int value = 2;
    arrInt.insert(1, value);

    EXPECT_EQ(arrInt.size(), 3);

    // Use iterator to verify
    std::vector<int> result;
    for (auto it = arrInt.iterator(); it.hasNext(); it.next())
    {
        result.push_back(it.get());
    }

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);

    // Remove and iterate again
    arrInt.remove(0);
    result.clear();
    for (auto it = arrInt.iterator(); it.hasNext(); it.next())
    {
        result.push_back(it.get());
    }

    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 3);

    // Similar test for strings
    DynamicArray<std::string> arrStr;
    arrStr.pushBack("Hello");
    arrStr.pushBack("!");

    std::string mid = "World";
    arrStr.insert(1, mid);

    std::vector<std::string> strResult;
    for (auto it = arrStr.iterator(); it.hasNext(); it.next())
    {
        strResult.push_back(it.get());
    }

    EXPECT_EQ(strResult.size(), 3);
    EXPECT_EQ(strResult[0], "Hello");
    EXPECT_EQ(strResult[1], "World");
    EXPECT_EQ(strResult[2], "!");
}
