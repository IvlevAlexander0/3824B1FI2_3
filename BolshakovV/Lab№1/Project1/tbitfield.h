#pragma once

#include <iostream>



typedef unsigned int TELEM;

class TBitField
{
private:
	//


	int shiftSize() const; //������� ��� ��������� ��� ������ ����� (32 - �� 0 �� 31. ����� 5 ���)

	///
	int  BitLen; // ����� �������� ���� - ����. �-�� �����
	TELEM* pMem; // ������ ��� ������������� �������� ����
	int  MemLen; // �-�� ��-��� ��� ��� ������������� ���.����

	// ������ ����������
	int   GetMemIndex(const int n) const; // ������ � p��� ��� ���� n       (#�2)
	TELEM GetMemMask(const int n) const; // ������� ����� ��� ���� n       (#�3)
public:
	TBitField(int len);                //                                   (#�1)
	TBitField(const TBitField& bf);    //                                   (#�1)
	~TBitField();                      //                                    (#�)

	// ������ � �����
	int GetLength(void) const;      // �������� ����� (�-�� �����)           (#�)
	void SetBit(const int n);       // ���������� ���                       (#�4)
	void ClrBit(const int n);       // �������� ���                         (#�2)
	int  GetBit(const int n) const; // �������� �������� ����               (#�1)

	// ������� ��������
	int operator==(const TBitField& bf) const; // ���������                 (#�5)
	int operator!=(const TBitField& bf) const; // ���������
	TBitField& operator=(const TBitField& bf); // ������������              (#�3)
	TBitField  operator|(const TBitField& bf); // �������� "���"            (#�6)
	TBitField  operator&(const TBitField& bf); // �������� "�"              (#�2)
	TBitField  operator~(void);                // ���������                  (#�)

	friend std::istream& operator>>(std::istream& istr, TBitField& bf);       //      (#�7)
	friend std::ostream& operator<<(std::ostream& ostr, const TBitField& bf); //      (#�4)
};
// ��������� �������� �������� ����
//   ���.���� - ����� ����� � �������� �� 0 �� BitLen
//   ������ p��� ��������������� ��� ������������������ MemLen ���������
//   ���� � ��-��� p��� ���������� ������ ������ (�� ������� � �������)