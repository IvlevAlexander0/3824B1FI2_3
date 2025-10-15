#include "pch.h"
#include <stdexcept> 
#include "../TBitField_TSet/tbitfield.cpp"
#include "../TBitField_TSet/tset.cpp"

//-----------------------  TBitField  ----------------------

TEST(BitField, ConstructAndLength) {
    TBitField bf(10);
    EXPECT_EQ(bf.GetLength(), 10);
    EXPECT_THROW(TBitField(-1), std::invalid_argument);
}

TEST(BitField, SetClrGetBit) {
    TBitField bf(5);
    bf.SetBit(2);
    EXPECT_EQ(bf.GetBit(2), 1);
    bf.ClrBit(2);
    EXPECT_EQ(bf.GetBit(2), 0);
    EXPECT_THROW(bf.SetBit(5), std::out_of_range);
    EXPECT_THROW(bf.GetBit(-1), std::out_of_range);
}

TEST(BitField, LogicOperators) {
    TBitField a(4), b(4);
    a.SetBit(1);
    b.SetBit(2);
    TBitField u = a | b;
    EXPECT_TRUE(u.GetBit(1));
    EXPECT_TRUE(u.GetBit(2));
    TBitField i = a & b;
    EXPECT_FALSE(i.GetBit(1));
    EXPECT_FALSE(i.GetBit(2));
    TBitField neg = ~a;
    EXPECT_FALSE(neg.GetBit(1));
    for (int i = 0; i < 4; ++i)
        if (i != 1) EXPECT_TRUE(neg.GetBit(i));
}

//--------------------------  TSet  --------------------------

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
