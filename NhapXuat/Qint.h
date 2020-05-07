#pragma once
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
	QInt(const string &Bin); // Chuyển chuỗi nhị phân thành QInt
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

	string QInttoBin();		// Chuyển QInt thành chuỗi nhị phân
protected:
	string StrDivTwo(string src);	// Chuỗi số chia cho 2
	string StrDectoBin(string src);	// Chuyển chuỗi Dec thành chuỗi nhị phân
	string SumString(string a, string b);	// tổng hai chuỗi số
	string Double(string src);	// 2*src
	string QInttoStrDec();	// Chuyển QInt thành chuỗi thập phân
	
};

