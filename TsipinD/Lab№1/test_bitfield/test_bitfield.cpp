#include "pch.h"
#include "../Lab¹1/tbitfield.cpp"

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