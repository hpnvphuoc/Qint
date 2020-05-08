#ifndef _QFLOAT_H_
#define _QFLOAT_H_
//---------------------------
#define fraction_num 112
#define exponent_num 15
#define sign_num 1
#define bias_num 16383
//---------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;
//---------------------------
class Qfloat {
private:
	int data[4];				// kiểu dữ liệu 32 bytes

	int SetBit(int, bool);
	int GetBit(int);					// lấy bit ở vị trí bất kỳ
	string Div2String(string);			// trả về kết quả là chuỗi string*2
	string Mul2String(string);			// trả về kết quả là chuỗi string/2
	string IntegerToBinary(string);		//Chuyển chuỗi số đằng trước dấu phẩy thành nhị phân
	string DecimalToBinary(string);
	int ExponentValue(string, string);	// Tính exponent 

public:
	Qfloat();							// default constructor
	Qfloat(const Qfloat&);				// copy constructor
	Qfloat(string);						// constructor với tham số là chuỗi
	~Qfloat();							// hàm huỷ
	void ScanQfloat();					// đọc 1 số Qfloat
	void PrintQfloat();					// in ra Qfloat dưới dạng nhị phân		
};



#endif
