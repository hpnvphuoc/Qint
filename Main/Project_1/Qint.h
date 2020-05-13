﻿#pragma once
#define _Max_Bit 31
#define _Max_Int 2147483647 // chuỗi bit: 0111 1111 1111 1111 1111 1111 1111 1111

#include <iostream>
#include <string>

using namespace std;

class QInt
{
private:
	int Data[4];
public:
	QInt();
	QInt(const QInt& x);

	QInt(const string& Bin); // Chuyển chuỗi nhị phân thành QInt
	~QInt();

	// Hàm kiểm tra mở rộng
	bool is_Negative();
	bool is_Zero();

	// Hàm nhập xuất
	void ScanQInt(QInt& x);
	void PrintQInt(QInt x);

	QInt& operator =(const QInt& x);

	//toán tử bit
	QInt operator >>(const int& Bit);
	QInt operator <<(const int& Bit);
	QInt& rol();
	QInt& ror();
	QInt& rol(const int& Bit);
	QInt& ror(const int& Bit);

	//18120210
	QInt bu1();
	QInt bu2();

	// operator +,-,*,/ - 18120210
	friend QInt operator+(QInt a, QInt b);
	friend QInt operator-(QInt a, QInt b);
	friend QInt operator*(QInt a, QInt b);
	friend QInt operator/(QInt a, QInt b);

	// operator: AND “&”, OR “|”, XOR “^”, NOT “~” - 18120210
	friend QInt operator&(QInt a, QInt b);
	friend QInt operator|(QInt a, QInt b);
	friend QInt operator^(QInt a, QInt b);
	QInt operator~();

	// operator “<”, “>”, “ == ”, “ <= ”, “ >= ” - 18120210
	friend bool operator>(QInt a, QInt b);
	friend bool operator<(QInt a, QInt b);
	friend bool operator==(QInt a, QInt b);
	friend bool operator>=(QInt a, QInt b);
	friend bool operator<=(QInt a, QInt b);
	
	//Chuyển đổi các hệ số
	string BinToHex(string bit);//Chuyển chuỗi nhị phân sang thập lục phân
	string DecToHex(string s);//Chuyển đổi thập phân sang thập lục phân
	string BinToDec(string bit);//Dùng lại trong hàm QInttoStrDec()
	string DecToBin(string bit);//Dùng lại hàm StrDectoBin()

	void ChuyenDoiHeSo();
	char ConvertHex(int a);

	string QInttoBin();		// Chuyển QInt thành chuỗi nhị phân
	string StrHextoBin(string src);//chuyển chuổi hệ 16 sang chuỗi nhị phân
protected:
	int getBitPositionI(int i); // Lấy bit vị trí i - 18120210
	void setBitPositionIto1(int i); // set bit vị trí i = 1 - 18120210
	void setBitPositionIto0(int i); // set bit vị tri i = 0 - 18120210

	string StrDivTwo(string src);	// Chuỗi số chia cho 2
	string StrDectoBin(string src);	// Chuyển chuỗi Dec thành chuỗi nhị phân
	string SumString(string a, string b);	// tổng hai chuỗi số
	string Double(string src);	// 2*src
	string QInttoStrDec();	// Chuyển QInt thành chuỗi thập phân
	
	//string ConvertHexCharToBin(char src);//chuyển đổi một kí tự thập phân sang nhị phân
	//my code

};


