#include "gtest/gtest.h"
#include "DynamicArray.h"

TEST(TestString, TestString1) {
    DynamicArray <std::string> arr;
    arr.insert("aboba");
    arr.insert("aboba2");
    EXPECT_EQ(arr[0], std::string("aboba"));
    EXPECT_EQ(arr[1], std::string("aboba2"));
}

TEST(TestString, TestString2) {
    DynamicArray<std::string> arr;
    for (int i = 0; i < 30; i++)
        arr.insert("aboba");
    arr.insert("aboba2");
    EXPECT_EQ(arr[30], std::string("aboba2"));
}

TEST(TestString, TestCapaab) {
    DynamicArray<std::string> arr(3);
    for (int i = 0; i < 30; i++)
        arr.insert("aboba");
    arr.insert("aboba2");
    EXPECT_EQ(arr[30], std::string("aboba2"));
}

TEST(TestString, TestInsert) {
    DynamicArray<std::string> arr;
    for (int i = 0; i < 30; i++)
        arr.insert("abob");
    arr.insert("abo");
    arr.insert("ab");
    arr.insert(30, "a");
    EXPECT_EQ(arr[29], std::string("abob"));
    EXPECT_EQ(arr[30], std::string("a"));
    EXPECT_EQ(arr[31], std::string("abo"));
    EXPECT_NE(arr[32], std::string("ab"));
}

TEST(TestString, TestInsert2) {
    DynamicArray<std::string> arr;
    for (int i = 0; i < 30; i++)
        arr.insert("abob");
    arr.insert("a");
    arr.insert("a");
    arr.insert("abo");
    arr.insert("ab");
    arr.remove(30);
    EXPECT_EQ(arr[29], std::string("abob"));
    EXPECT_EQ(arr[30], std::string("a"));
    EXPECT_EQ(arr[31], std::string("abo"));
    EXPECT_EQ(arr[32], std::string("ab"));
}

TEST(TestString, TestInsertLong) {
    DynamicArray <std::string> arr;
    for (int i = 0; i < 30; i++) {
        arr.insert(
                "abobaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    }
    arr.insert(
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    arr.insert(
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    arr.insert(
            "aboaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    arr.insert(
            "abaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    arr.remove(30);
    EXPECT_EQ(arr[29], std::string(
            "abobaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
    EXPECT_EQ(arr[30], std::string(
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
    EXPECT_EQ(arr[31], std::string(
            "aboaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
    EXPECT_EQ(arr[32], std::string(
            "abaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
}

TEST(TestIterator, TestIterator1) {
    DynamicArray<int> a;
    for (int i = 0; i < 10; ++i)
        a.insert(i + 1);
    for (auto it = a.iterator(); it.hasNext(); it.next())
        it.set(it.get() * 2);
    int i = 1;
    for (auto it = a.iterator(); it.hasNext(); it.next()) {
        EXPECT_EQ(it.get(), i * 2);
        i += 1;
    }
    for (auto it = a.reverseIterator(); it.hasNext(); it.next()) {
        if (i == 10)
            EXPECT_EQ(it.get(), 10);
        else
            EXPECT_EQ(it.get(), i * 2);
        i -= 1;
    }
}

TEST(TestOtherArray, TestOtherArray1) {
    DynamicArray <std::string> arr;
    for (int i = 0; i < 30; i++)
        arr.insert("abob");
    arr.insert("a");
    arr.insert("abo");
    arr.insert("ab");
    DynamicArray <std::string> arr2(arr);
    EXPECT_EQ(arr2[29], std::string("abob"));
    EXPECT_EQ(arr2[30], std::string("a"));
    EXPECT_EQ(arr2[31], std::string("abo"));
    EXPECT_EQ(arr2[32], std::string("ab"));
}

TEST(TestOtherArray, TestOtherArray2) {
    DynamicArray <std::string> arr;
    for (int i = 0; i < 30; i++)
        arr.insert("abob");
    arr.insert("a");
    arr.insert("abo");
    arr.insert("ab");
    DynamicArray <std::string> arr2;
    arr2 = arr;
    EXPECT_EQ(arr2[29], std::string("abob"));
    EXPECT_EQ(arr2[30], std::string("a"));
    EXPECT_EQ(arr2[31], std::string("abo"));
    EXPECT_EQ(arr2[32], std::string("ab"));
    EXPECT_EQ(arr[29], std::string("abob"));
    EXPECT_EQ(arr[30], std::string("a"));
    EXPECT_EQ(arr[31], std::string("abo"));
    EXPECT_EQ(arr[32], std::string("ab"));
}

TEST(TestOtherArray, TestOtherArray3) {
    DynamicArray <std::string> arr;
    for (int i = 0; i < 30; i++)
        arr.insert("abob");
    arr.insert("a");
    arr.insert("abo");
    arr.insert("ab");
    DynamicArray <std::string> arr2(std::move(arr));
    EXPECT_EQ(arr2[29], std::string("abob"));
    EXPECT_EQ(arr2[30], std::string("a"));
    EXPECT_EQ(arr2[31], std::string("abo"));
    EXPECT_EQ(arr2[32], std::string("ab"));
    EXPECT_EQ(arr.size(), 0);
}

TEST(TestOtherArray, TestOtherArray4) {
    DynamicArray <std::string> arr;
    for (int i = 0; i < 30; i++)
        arr.insert("abob");
    arr.insert("a");
    arr.insert("abo");
    arr.insert("ab");
    DynamicArray <std::string> arr2 = std::move(arr);
    EXPECT_EQ(arr2[29], std::string("abob"));
    EXPECT_EQ(arr2[30], std::string("a"));
    EXPECT_EQ(arr2[31], std::string("abo"));
    EXPECT_EQ(arr2[32], std::string("ab"));
    EXPECT_EQ(arr.size(), 0);
}

TEST(TestString, TestInsertWrong) {
    DynamicArray <std::string> arr;
    for (int i = 0; i < 30; i++)
        arr.insert("abob");
    arr.insert(30, "a");
    EXPECT_EQ(arr[29], std::string("abob"));
    EXPECT_NE(arr[30], std::string("a"));
}