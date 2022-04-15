#include "gtest/gtest.h"
#include "trit.h"

using namespace std;

enum Trit{False, Unknown, True};

TEST(TritSetFixture, isEmpty) {
    TritSet a;
    EXPECT_EQ(a.capacity(), 0);
    TritSet c(100);
    EXPECT_EQ(c.getData(0) + 1, Unknown);
    EXPECT_EQ(c.capacity(), 100);
    c[5] = False;
    c[0] = True;
    c[100] = True;

    EXPECT_EQ(c.getData(5) + 1, False);
    EXPECT_EQ(c.getData(4) + 1, Unknown);
    EXPECT_EQ(c.getData(6) + 1, Unknown);
    EXPECT_EQ(c.getData(100) + 1, True);
    EXPECT_EQ(c.getData(0) + 1, True);

    int ln = c.capacity();
    EXPECT_EQ(c.capacity(), ln);
    c.reallocate(10000);
    EXPECT_EQ(c.capacity(), 10000);
    c.shrink();
    EXPECT_EQ(c.capacity(), ln);

    TritSet y(6);
    TritSet x(6);
    y[0] = False;
    y[1] = False;
    y[2] = False;
    y[3] = True;
    y[4] = True;
    y[5] = Unknown;
    x[0] = False;
    x[1] = True;
    x[2] = Unknown;
    x[3] = True;
    x[4] = Unknown;
    x[5] = Unknown;
    TritSet z = x&y;
    EXPECT_EQ(z.getData(0) + 1, False);
    EXPECT_EQ(z.getData(1) + 1, False);
    EXPECT_EQ(z.getData(2) + 1, False);
    EXPECT_EQ(z.getData(3) + 1, True);
    EXPECT_EQ(z.getData(4) + 1, Unknown);
    EXPECT_EQ(z.getData(5) + 1, Unknown);
    z = y&x;
    EXPECT_EQ(z.getData(0) + 1, False);
    EXPECT_EQ(z.getData(1) + 1, False);
    EXPECT_EQ(z.getData(2) + 1, False);
    EXPECT_EQ(z.getData(3) + 1, True);
    EXPECT_EQ(z.getData(4) + 1, Unknown);
    EXPECT_EQ(z.getData(5) + 1, Unknown);
    z = y|x;
    EXPECT_EQ(z.getData(0) + 1, False);
    EXPECT_EQ(z.getData(1) + 1, True);
    EXPECT_EQ(z.getData(2) + 1, Unknown);
    EXPECT_EQ(z.getData(3) + 1, True);
    EXPECT_EQ(z.getData(4) + 1, True);
    EXPECT_EQ(z.getData(5) + 1, Unknown);
    z = x|y;
    EXPECT_EQ(z.getData(0) + 1, False);
    EXPECT_EQ(z.getData(1) + 1, True);
    EXPECT_EQ(z.getData(2) + 1, Unknown);
    EXPECT_EQ(z.getData(3) + 1, True);
    EXPECT_EQ(z.getData(4) + 1, True);
    EXPECT_EQ(z.getData(5) + 1, Unknown);
    z = ~y;
    EXPECT_EQ(z.getData(0) + 1, True);
    EXPECT_EQ(z.getData(1) + 1, True);
    EXPECT_EQ(z.getData(2) + 1, True);
    EXPECT_EQ(z.getData(3) + 1, False);
    EXPECT_EQ(z.getData(4) + 1, False);
    EXPECT_EQ(z.getData(5) + 1, Unknown);
    EXPECT_TRUE(z[0] == 1);
    TritSet setA(1000);
    TritSet setB(2000);
    TritSet setC = setA & setB;
    EXPECT_TRUE(setC.capacity() == setB.capacity());

}


TEST(Task, TasksAsserts) {
    TritSet set(1000);
    size_t allocLength = set.capacity();
    assert(allocLength >= 1000*2 / 8 / sizeof(uint) );
    set[1000000000] = Unknown;
    assert(allocLength == set.capacity());
    if(set[2000000000]==True){}
    assert(allocLength == set.capacity());
    set[1000000000] = True;
    assert(allocLength < set.capacity());
    allocLength = set.capacity();
    set[1000000000] = Unknown;
    set[1000000] = False;
    assert(allocLength == set.capacity());
    set.shrink();
    assert(allocLength > set.capacity());
    TritSet setA(1000);
    TritSet setB(2000);
    TritSet setC = setA & setB;
    assert(setC.capacity() == setB.capacity());
}