#ifndef _QFLOAT_H_
#define _QFLOAT_H_
//---------------------------
// smallest normalized: 1.[112 số 0] * 2^(-16382)
// largest normalized: 1.[112 số 1] * 2^(16383)
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
	int data[4];					// kiểu dữ liệu 16 bytes (128 bits)

	void SetBit1(int);						// đặt bit 1 tại vị trí i
	int GetBit(int);						// lấy bit ở vị trí bất kỳ
	string Div2String(string);				// trả về kết quả là chuỗi string/2
	string Mul2String(string);				// trả về kết quả là chuỗi string*2
	string SumString(string, string);		// cộng 2 chuỗi nguyên
	string Double(string);					// x2 chuỗi nguyên
	string BinToDec(string);				// chuyển số nguyên hệ 2 -> 10
	string FloatDivTwo(string);				// chia số thực cho 2
	string SumFloatString(string, string);	// cộng 2 số thực
	string PowerNeg2(int);					// tính 2^(-x)
	string DecBinToDec(string);				// chuyển phần thập phân hệ 2 -> 10
	string IntegerToBinary(string);			// trả về chuỗi đã chuyển số đằng trước dấu chấm thành nhị phân
	string DecimalToBinary(string);			// trả về chuỗi đã chuyển số đằng sau dấu chấm thành nhị phân				=> PROBLEM: chưa làm tròn lên, xuống
	int ExponentValue(string, string);		// trả về giá trị exponent 
	void AddExponent(int);					// ghi exponent vào data
	void AddFraction(int, string, string);	// chuyển thành dạng chuẩn rồi ghi fraction vào data 
	string CheckDenormalized();				// kiểm tra số đặc biệt
	string MovePoint(string, int);          // truyền vào F và E, trả về chuỗi ban đầu (chuyển dạng 1.F*2^E về dạng chưa chuẩn) 
public:
	Qfloat();								// default constructor
	Qfloat(const Qfloat&);					// copy constructor
	Qfloat(string);							// constructor với tham số là chuỗi thập phân
	Qfloat(bool*);							// constructor với tham số là dãy nhị phân
	~Qfloat();								// hàm huỷ
	void ScanQfloat();						// đọc Qfloat ở dạng thập phân												=> PROBLEM: chưa giới hạn range
	void ScanBinQfloat();					// đọc Qfloat ở dạng nhị phân
	void PrintQfloat();						// in ra Qfloat dưới dạng nhị phân	
	string GetDecimalValue();				// trả về chuỗi giá trị thập phân của Qfloat	
	string GetBinaryString();				//tra ve chuoi gia tri nhi phan cua Qfloat
};

void DecToBin(Qfloat a);					// chuyển đổi số Qfloat thập phân sang nhị phân
void BinToDec(Qfloat a);					// chuyển đổi số Qfloat nhị phân sang thập phân	

#endif
