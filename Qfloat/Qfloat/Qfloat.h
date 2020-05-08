#ifndef _QFLOAT_H_
#define _QFLOAT_H_
//---------------------------
#define fraction_num 112				// số bit phần fraction
#define exponent_num 15					// số bit phần exponent (k bits)
#define sign_num 1						// số bit phần sign
#define bias_num 16383					// giá trị bias = 2^(k-1) - 1
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
	int data[4];				// kiểu dữ liệu 32 bytes (128 bits)

	void SetBit1(int);						// đặt bit 1 tại vị trí i
	int GetBit(int);						// lấy bit ở vị trí bất kỳ
	string Div2String(string);				// trả về kết quả là chuỗi string*2
	string Mul2String(string);				// trả về kết quả là chuỗi string/2
	string IntegerToBinary(string);			// chuyển chuỗi số đằng trước dấu chấm thành nhị phân
	string DecimalToBinary(string);			// chuyển chuỗi số đằng sau dấu chấm thành nhị phân => PROBLEM: chưa làm tròn lên, xuống
	int ExponentValue(string, string);		// tính exponent 
	void AddExponent(int);					// ghi exponent vào data
	void AddFraction(int, string, string);	// ghi fraction vào data
public:
	Qfloat();							// default constructor
	Qfloat(const Qfloat&);				// copy constructor
	Qfloat(string);						// constructor với tham số là chuỗi
	~Qfloat();							// hàm huỷ
	void ScanQfloat();					// đọc Qfloat ở dạng thập phân
	void PrintQfloat();					// in ra Qfloat dưới dạng nhị phân	-> hàm DecToBin, tách ra làm 1 hàm riêng cũng dc
};



#endif
