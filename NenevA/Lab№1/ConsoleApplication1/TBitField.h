#pragma once
#include <cstring>
#include <exception>
using namespace std;
typedef unsigned int TELEM;
class TBitField {
private:
	int  BitLen;
	TELEM* pMem;
	int  MemLen;
	int GetMemIndex(const int n) const {
		if (n >= BitLen) {
			throw out_of_range("The bit number must be within the bit field");
		}
		return n / (sizeof(TELEM) * 8);
	}
	TELEM GetMemMask(const int n) const {
		if (n >= BitLen) {
			throw out_of_range("The bit number must be within the bit field");
		}
		return 1 << (n % (sizeof(TELEM) * 8));
	}
public:
	TBitField(int len) {
		if (len <= 0) {
			throw out_of_range("The length of the bit field must be positive");
		}
		BitLen = len;
		MemLen = (len + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; ++i) {
			pMem[i] = 0;
		}
	}
	TBitField(const TBitField& bf) {
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; ++i) {
			pMem[i] = bf.pMem[i];
		}
	}
	~TBitField() {
		delete[] pMem;
	}
	int GetLength(void) const {
		return BitLen;
	}
	void SetBit(const int n) {
		if (n < 0 || n >= BitLen) {
			throw out_of_range("Bit index is out of range");
		}
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
	void ClrBit(const int n) {
		if (n < 0 || n >= BitLen) {
			throw out_of_range("Bit index is out of range");
		}
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	}
	int  GetBit(const int n) const {
		if (n < 0 || n >= BitLen) {
			throw out_of_range("Bit index out of range");
		}
		return ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0);
	}
	int operator==(const TBitField& bf) const {
		if (BitLen != bf.BitLen) {
			return 0;
		}
		for (int i = 0; i < MemLen; ++i) {
			if (pMem[i] != bf.pMem[i]) {
				return 0;
			}
		}
		return 1;
	}

	int operator!=(const TBitField& bf) const {
		if (BitLen != bf.BitLen) {
			return 1;
		}
		for (int i = 0; i < MemLen; ++i) {
			if (pMem[i] != bf.pMem[i]) {
				return 1;
			}
		}
		return 0;
	}

	TBitField& operator=(const TBitField& bf) {
		if (this != &bf) {
			delete[] pMem;
			BitLen = bf.BitLen;
			MemLen = bf.MemLen;
			pMem = new TELEM[MemLen];
			for (int i = 0; i < MemLen; ++i) {
				pMem[i] = bf.pMem[i];
			}
		}
		return *this;
	}

	TBitField operator|(const TBitField& other) const {
		int maxLength = max(BitLen, other.BitLen);
		TBitField result(maxLength);
		int offset1 = 0;
		int offset2 = 0;
		if (BitLen < other.BitLen) {
			offset1 = other.BitLen - BitLen;
		}
		else if (other.BitLen < BitLen) {
			offset2 = BitLen - other.BitLen;
		}
		for (int i = 0; i < maxLength; ++i) {//Добавляем нули в начало строки, если строки разного размера
			TELEM bit1 = (i >= offset1 && i - offset1 < BitLen) ? GetBit(i - offset1) : 0;
			TELEM bit2 = (i >= offset2 && i - offset2 < other.BitLen) ? other.GetBit(i - offset2) : 0;
			TELEM bit = bit1 | bit2;
			if (bit) {
				result.SetBit(i);
			}
			else {
				result.ClrBit(i);
			}
		}
		return result;
	}

	TBitField operator&(const TBitField& other) const {
		int maxLength = max(BitLen, other.BitLen);
		TBitField result(maxLength);
		int offset1 = 0;
		int offset2 = 0;
		if (BitLen < other.BitLen) {
			offset1 = other.BitLen - BitLen;
		}
		else if (other.BitLen < BitLen) {
			offset2 = BitLen - other.BitLen;
		}
		for (int i = 0; i < maxLength; ++i) { //Добавляем нули в начало строки, если строки разного размера
			TELEM bit1 = (i >= offset1 && i - offset1 < BitLen) ? GetBit(i - offset1) : 0;
			TELEM bit2 = (i >= offset2 && i - offset2 < other.BitLen) ? other.GetBit(i - offset2) : 0;
			TELEM bit = bit1 & bit2;
			if (bit) {
				result.SetBit(i);
			}
			else {
				result.ClrBit(i);
			}
		}
		return result;
	}

	TBitField  operator~(void) {
		TBitField result(BitLen);
		for (int i = 0; i < MemLen; ++i) {
			result.pMem[i] = ~pMem[i];
		}
		//Убирает лишние биты
		int lastBitIndex = BitLen % (sizeof(TELEM) * 8);
		if (lastBitIndex != 0) {
			result.pMem[MemLen - 1] &= (1 << lastBitIndex) - 1;
		}
		return result;
	}
	friend istream& operator>>(istream& istr, TBitField& bf) {//Вводим некую последовательность цифр 1 и 0 длины BitLen
		string str;
		istr >> str;
		if (str.length() != bf.BitLen) {
			throw invalid_argument("Input string length does not match BitField length");
		}
		for (int i = 0; i < bf.BitLen; ++i) {
			if (str[i] == '1') {
				bf.SetBit(i);
			}
			else if (str[i] == '0') {
				bf.ClrBit(i);
			}
			else {
				throw invalid_argument("Input string must contain only '0' or '1'");
			}
		}
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TBitField& bf) {
		for (int i = 0; i < bf.BitLen; ++i) {
			ostr << bf.GetBit(i);
		}
		return ostr;
	}
};