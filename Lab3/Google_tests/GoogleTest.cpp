#include "gtest/gtest.h"
#include "Sort.h"

Sort sort;

TEST(BasicTest, test)
{
    EXPECT_EQ(sort.test(0), 1);
    EXPECT_EQ(sort.test(1), 0);
    EXPECT_EQ(sort.test(5), 2);
}


TEST(BasicTest, ChoosePivotTest) {
    int sample[5] = {1, 2, 3, 4, 5};
    int a1[5] = {1, 2, 3, 4, 5};
    int p1 = sort.choosePivot(a1, a1 + 2, a1 + 4, [](int a, int b) { return a < b; });
    EXPECT_EQ(p1, 3);
    for (int i = 0; i < 5; i++)
        EXPECT_EQ(a1[i], sample[i]);
    int a2[5] = {3, 2, 1, 4, 5};
    int p2 = sort.choosePivot(a2, a2 + 2, a2 + 4, [](int a, int b) { return a < b; });
    EXPECT_EQ(p2, 3);
    for (int i = 0; i < 5; i++)
        EXPECT_EQ(a2[i], sample[i]);
    int a3[5] = {1, 2, 5, 4, 3};
    int p3 = sort.choosePivot(a3, a3 + 2, a3 + 4, [](int a, int b) { return a < b; });
    EXPECT_EQ(p3, 3);
    for (int i = 0; i < 5; i++)
        EXPECT_EQ(a3[i], sample[i]);
}


TEST(Insert, InsertionSortTest1) {
    int a[10];
    for (int i = 0; i < 10; i++)
        a[i] = 10 - i;
    sort.insertionSort(a, a + 9, [](int a, int b) { return a < b; });
    for (int i = 0; i < 10; i++)
        EXPECT_EQ(a[i], i + 1);
}
TEST(Insert, InsertionSortTest2) {
    int a[10];
    for (int i = 0; i < 10; i++)
        a[i] = i + 1;
    sort.insertionSort(a, a + 9, [](int a, int b) { return a > b; });
    for (int i = 0; i < 10; i++)
        EXPECT_EQ(a[i], 10 - i);
}
TEST(Insert, InsertionSortTest3) {
    int a[1] = {1};
    sort.insertionSort(a, a, [](int a, int b) { return a < b; });
    EXPECT_EQ(a[0], 1);
}
TEST(Insert, InsertionSortTest4) {
    std::string sample[5] = {"1", "11", "111", "1111", "11111"};
    std::string a[5] = {"11111", "1111", "111", "11", "1"};
    sort.insertionSort(a, a + 4, [](std::string a, std::string b) { return a.length() < b.length(); });
    for (int i = 0; i < 5; i++)
        EXPECT_EQ(a[i], sample[i]);
}
TEST(Insert, InsertionSortTest5) {
    int a[10];
    for (int & i : a) {
        i = 1;
    }
    sort.insertionSort(a, a + 9, [](int a, int b) { return a < b; });
    for (int i : a)
        EXPECT_EQ(i, 1);
}
TEST(Insert, InsertionSortTest6) {
    int sample[5] = {2, 3, 3, 5, 5};
    int a[5] = {5, 3, 3, 2, 5};
    sort.insertionSort(a, a + 4, [](int a, int b) { return a < b; });
    for (int i = 0; i < 5; i++)
        EXPECT_EQ(a[i], sample[i]);
}
TEST(Insert, InsertionSortTest7) {
    std::srand(std::time(nullptr));
    int a[100];
    int b[100];
    for (int i = 0; i < 100; i++) {
        a[i] = std::rand();
        b[i] = a[i];
    }
    sort.insertionSort(a, a + 99, [](int a, int b) { return a < b; });
    std::qsort(b, 100, sizeof(int), [](const void *a, const void *b) { return (*(int *) a - *(int *) b); });
    for (int i = 0; i < 100; i++)
        EXPECT_EQ(a[i], b[i]);
}


TEST(Quick, QuickSortTest1) {
    int a[10];
    for (int i = 0; i < 10; i++)
        a[i] = 10 - i;
    sort.quickSort(a, a + 9, [](int a, int b) { return a < b; });
    for (int i = 0; i < 10; i++)
        EXPECT_EQ(a[i], i + 1);
}
TEST(Quick, QuickSortTest2) {
    int a[10];
    for (int i = 0; i < 10; i++)
        a[i] = i + 1;
    sort.quickSort(a, a + 9, [](int a, int b) { return a > b; });
    for (int i = 0; i < 10; i++)
        EXPECT_EQ(a[i], 10 - i);
}
TEST(Quick, QuickSortTest3) {
    int a[1] = {1};
    sort.quickSort(a, a, [](int a, int b) { return a < b; });
    EXPECT_EQ(a[0], 1);
}
TEST(Quick, QuickSortTest4) {
    std::string sample[5] = {"1", "11", "111", "1111", "11111"};
    std::string a[5] = {"11111", "1111", "111", "11", "1"};
    sort.quickSort(a, a + 4, [](std::string a, std::string b) { return a.length() < b.length(); });
    for (int i = 0; i < 5; i++)
        EXPECT_EQ(a[i], sample[i]);
}
TEST(Quick, QuickSortTest5) {
    int a[10];
    for (int & i : a) {
        i = 1;
    }
    sort.quickSort(a, a + 9, [](int a, int b) { return a < b; });
    for (int i : a)
        EXPECT_EQ(i, 1);
}
TEST(Quick, QuickSortTest6) {
    int sample[5] = {2, 3, 3, 5, 5};
    int a[5] = {5, 3, 3, 2, 5};
    sort.quickSort(a, a + 4, [](int a, int b) { return a < b; });
    for (int i = 0; i < 5; i++)
        EXPECT_EQ(a[i], sample[i]);
}
TEST(Quick, QuickSortTest7) {
    std::srand(std::time(nullptr));
    int a[100];
    int b[100];
    for (int i = 0; i < 100; i++) {
        a[i] = std::rand();
        b[i] = a[i];
    }
    sort.quickSort(a, a + 99, [](int a, int b) { return a < b; });
    std::qsort(b, 100, sizeof(int), [](const void *a, const void *b) { return (*(int *) a - *(int *) b); });
    for (int i = 0; i < 100; i++)
        EXPECT_EQ(a[i], b[i]);
}

TEST(Mixed, MixedSortTest1) {
    int a[10];
    for (int i = 0; i < 10; i++)
        a[i] = 10 - i;
    sort.mixedSort(a, a + 9, [](int a, int b) { return a < b; });
    for (int i = 0; i < 10; i++)
        EXPECT_EQ(a[i], i + 1);
}
TEST(Mixed, MixedSortTest2) {
    int a[10];
    for (int i = 0; i < 10; i++)
        a[i] = i + 1;
    sort.mixedSort(a, a + 9, [](int a, int b) { return a > b; });
    for (int i = 0; i < 10; i++)
        EXPECT_EQ(a[i], 10 - i);
}
TEST(Mixed, MixedSortTest3) {
    int a[1] = {1};
    sort.mixedSort(a, a, [](int a, int b) { return a < b; });
    EXPECT_EQ(a[0], 1);
}
TEST(Mixed, MixedSortTest4) {
    std::string sample[5] = {"1", "11", "111", "1111", "11111"};
    std::string a[5] = {"11111", "1111", "111", "11", "1"};
    sort.mixedSort(a, a + 4, [](std::string a, std::string b) { return a.length() < b.length(); });
    for (int i = 0; i < 5; i++)
        EXPECT_EQ(a[i], sample[i]);
}
TEST(Mixed, MixedSortTest5) {
    int a[10];
    for (int & i : a) {
        i = 1;
    }
    sort.mixedSort(a, a + 9, [](int a, int b) { return a < b; });
    for (int i : a)
        EXPECT_EQ(i, 1);
}
TEST(Mixed, MixedSortTest6) {
    int sample[5] = {2, 3, 3, 5, 5};
    int a[5] = {5, 3, 3, 2, 5};
    sort.mixedSort(a, a + 4, [](int a, int b) { return a < b; });
    for (int i = 0; i < 5; i++)
        EXPECT_EQ(a[i], sample[i]);
}
TEST(Mixed, MixedSortTest7) {
    std::srand(std::time(nullptr));
    int a[100];
    int b[100];
    for (int i = 0; i < 100; i++) {
        a[i] = std::rand();
        b[i] = a[i];
    }
    sort.mixedSort(a, a + 99, [](int a, int b) { return a < b; });
    std::qsort(b, 100, sizeof(int), [](const void *a, const void *b) { return (*(int *) a - *(int *) b); });
    for (int i = 0; i < 100; i++)
        EXPECT_EQ(a[i], b[i]);
}