#include "pch.h"
#include "../Lab¹1/tset.cpp"
#include "../Lab¹1/tbitfield.h"

TEST(Set, InsDelIsmemTest) {
    TSet s(5);
    EXPECT_EQ(s.IsMember(3), 0);
    s.InsElem(3);
    EXPECT_EQ(s.IsMember(3), 1);
    s.DelElem(3);
    EXPECT_EQ(s.IsMember(3), 0);
}

TEST(Set, UniIntersOps) {
    TSet a(4), b(4);
    a.InsElem(1); b.InsElem(2);
    TSet u = a + b;
    EXPECT_TRUE(u.IsMember(1) && u.IsMember(2));
    TSet inter = a * b;
    EXPECT_FALSE(inter.IsMember(1));
}

TEST(Set, Complement) {
    TSet s(3);
    s.InsElem(0);
    TSet comp = ~s; // 011
    EXPECT_FALSE(comp.IsMember(0));
    EXPECT_TRUE(comp.IsMember(1));
    EXPECT_TRUE(comp.IsMember(2));
}
