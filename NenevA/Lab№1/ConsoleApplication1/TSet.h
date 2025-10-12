#pragma once
#include "TBitField.h"
class TSet
{
private:
    int MaxPower;
    TBitField BitField;
public:
    TSet(int mp) : MaxPower(mp), BitField(mp) {} //����� �� ��������� mp, ��������� �������� �������� ���� � TBitField

    TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

    TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {}

    operator TBitField() {
        return BitField;
    }

    //���������� ��������� ������� ��� ��������� � ��������������� �������� TBitField
    int GetMaxPower(void) const {
        return MaxPower;
    }
    void InsElem(const int Elem) {
        BitField.SetBit(Elem);
    }
    void DelElem(const int Elem) {
        BitField.ClrBit(Elem);
    }
    int IsMember(const int Elem) const {
        return BitField.GetBit(Elem);
    }
    //���������
    int operator== (const TSet& s) const {
        return BitField == s.BitField;
    }
    int operator!= (const TSet& s) const {
        return ~(BitField == s.BitField);
    }
    TSet& operator=(const TSet& s) {
        if (this != &s) {
            MaxPower = s.MaxPower;
            BitField = s.BitField;
        }
        return *this;
    }
    TSet operator+ (const int Elem) {
        TSet result(*this);
        result.InsElem(Elem);
        return result;
    }
    TSet operator- (const int Elem) {
        TSet result(*this);
        result.DelElem(Elem);
        return result;
    }
    TSet operator+ (const TSet& s) {
        if (MaxPower != s.MaxPower) {//�� ����� ���������� �������� �� ������ ���������
            throw invalid_argument("Sets must be of the same power");
        }
        TSet result(MaxPower);
        result.BitField = BitField | s.BitField;
        return result;
    }
    TSet operator* (const TSet& s) {
        if (MaxPower != s.MaxPower) {//�� ����� �������� �������� �� ������ ���������
            throw invalid_argument("Sets must be of the same power");
        }
        TSet result(MaxPower);
        result.BitField = BitField & s.BitField;
        return result;
    }
    TSet operator~ (void) {//���������� � ���������
        TSet result(MaxPower);
        result.BitField = ~BitField;
        return result;
    }

    //��������� ����� � ������, ������ ��� �� ��� ������� ������
    friend istream& operator>>(istream& istr, TSet& s) {
        istr >> s.BitField;
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TSet& s) {
        ostr << s.BitField;
        return ostr;
    }
};