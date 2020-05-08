#include "Qfloat.h"
Qfloat::Qfloat() {
	for (int i = 0; i < 4; i++)						// khởi tạo Qfloat với giá trị 0
		this->data[i] = 0;
}
Qfloat::Qfloat(const Qfloat &p) {
	for (int i = 0; i < 4; i++)						// copy từng byte của p vào Qfloat
		this->data[i] = p.data[i];
}
Qfloat::~Qfloat() {}
void Qfloat::SetBit1(int i) {						// set bit 1 tai vi tri i
	this->data[i / 32] = this->data[i / 32] | (1 << (31 - i % 32));
}
int Qfloat::GetBit(int i) {							// lấy bit tại vị trí i
	return (this->data[i / 32] >> (31 - i % 32)) & 1;
}
void Qfloat::ScanQfloat() {
	string s;
	fflush(stdin);
	getline(cin, s);
	*this = Qfloat(s);
}
void Qfloat::PrintQfloat() {
	for (int i = 0; i < 128; i++) {
		cout << GetBit(i);
		if (i == 0)
			cout << " ";
		if (i == 15)
			cout << " ";
	}
}
Qfloat::Qfloat(string s) {
	for (int i = 0; i < 4; i++) {					// khởi tạo Qfloat với giá trị 0 
		this->data[i] = 0;
	}
	string integer, decimal;						// integer chứa phần nguyên, decimal chứa phần thập phân
	int len = s.length();							// độ dài tham số chuỗi 
	int i = 0;										// biến đếm dùng cho vòng lặp
	if (s[0] == '-') {								// nếu là số âm
		this->SetBit1(0);							// thì set bit data là 1 tại vị trí 0
		i++;										// tăng biến đếm đến vị trí tiếp theo
	}
	// tách integer và decimal
	for (i; i < len; i++) {							// chuyển phần nguyên vào integer
		if (s[i] != '.') {
			integer += s[i];
		}
		else {
			break;									// nếu gặp dấu . thì ngừng
		}
	}
	i++;
	for (; i < len; i++) {							// chuyển phần thập phân vào decimal
		decimal += s[i];
	}
	string integer_bin = this->IntegerToBinary(integer);			// chuyển integer sang nhị phân
	string decimal_bin = this->DecimalToBinary(decimal);			// chuyển decimal sang nhị phân
	int exponent = this->ExponentValue(integer_bin, decimal_bin);	// tính exponent
	AddExponent(exponent);											// ghi vào exponent
	AddFraction(exponent, integer_bin, decimal_bin);				// ghi vào fraction
}
string Qfloat::IntegerToBinary(string s) {
	string result;
	while (s != "0") {								// chia integer tới khi s = 0
		int len = s.length();
		if ((s[len - 1] - '0') % 2 == 0) {			// chia hết cho 2
			result += '0';
		}
		else {										// không chia hết cho 2
			result += '1';
		}
		s = this->Div2String(s);					// chia chuỗi cho 2, đã xử lý trường hợp nhập 000x.
	}
	if (result.empty()) {
		result = "0";
	}
	reverse(result.begin(), result.end());			// đảo chuỗi
	return result;
}
string Qfloat::DecimalToBinary(string s) { // chưa làm tròn
	string result;
	int count = fraction_num;						// biến đếm trường hợp phần bit thập phân dài hơn fraction
	while (count--) {
		string temp = this->Mul2String(s);			// *2 phàn decimal
		if (temp.length() > s.length()) {			// nếu ra trường hợp 1.xx
			result += '1';							// thêm bit 1
			temp.erase(0, 1);						// xoá số 1 ở đầu (1.xx -1 = 0.xx)
		}
		else {
			result += '0';							// thêm bit 0
		}
		s = temp;
		bool check = 0;								// check xem = 1 chưa
		for (int i = 0; i < s.length(); i++) {
			if (s[i] != '0')
				check = 1;
		}
		if (check == 0)								// nếu đã = 1 thì thoát				
			break;
	}
	return result;
}
int Qfloat::ExponentValue(string integer, string decimal) {
	int int_len = integer.length();					// độ dài phần nguyên
	int dec_len = decimal.length();					// độ dài phần thập phân
	int exponent;									// giá trị exponent
	for (int i = 0; i < int_len; i++) {
		if (integer[i] == '1') {					// gặp số 1 đầu tiên
			exponent = bias_num + (int_len - i - 1);// số dấu , phải dời = độ dài - (số số 0 phía trc + số 1 đầu tiên)
			return exponent;
		}
	}
	for (int i = 0; i < dec_len; i++) {				// nếu không gặp số 1 ở phần integer thì chuyển sang phần decimal
		if (decimal[i] == '1') {					// gặp số 1 đầu tiên
			exponent = bias_num - i - 1;			// số dấu , phải dời = số số đứng trc số 1 + số 1 đầu tiên 
			return exponent;
		}
	}
	exponent = 0;									// chuỗi = 0
	return exponent;
}
string Qfloat::Div2String(string s) {
	string result;									// chuỗi lưu kết quả
	int	dividend = 0;								// số bị chia
	int	len = s.length();							//  chiều dài chuỗi
	for (int i = 0; i < len; i++) {
		if (dividend != 0) {   						// nếu phép chia đang có dư 
			dividend = 10 + s[i] - '0';				// 10 vì chia 2 nên số dư luôn luôn là 1
			result += dividend / 2 + '0';
			dividend = dividend % 2;				// sau khi chia xong, số bị chia tiếp theo là số dư
		}
		else if (s[i] - '0' < 2) {					// s[i] nhỏ hơn 2, cho nên ta ko chia 2 dc mà phải mượn số kế tiếp 
			result += '0';							// thêm số 0
			dividend = s[i] - '0';					// cập nhật số bị chia = s[i]
		}
		else if (s[i] - '0' >= 2) {					// s[i] lớn hơn 2
			result += (s[i] - '0') / 2 + '0';
			dividend = (s[i] - '0') % 2;
		}
	}
	while (result[0] == '0' && result.length() > 1) {
		result.erase(0, 1);							// xoá số 0 dư ở đầu tiên
	}
	return result;
}
string Qfloat::Mul2String(string s) {
	string result;									// result = null
	int product = 0;								// tích
	for (int i = s.length() - 1; i >= 0; i--) {
		if (product != 0) {							// còn nhớ 1
			product = 2 * (s[i] - '0') + 1;			// +1 nhớ lúc trước
			result = char((product % 10) + '0') + result;
			if (product / 10 != 0) {
				if (i > 0) {
					product = 1;					// nhớ 1
				}
				else {
					result = '1' + result;			// nếu là số đầu tiên thì thêm 1 vào đầu 
				}
			}
			else {
				product = 0;						// không nhớ
			}
		}
		else {
			product = 2 * (s[i] - '0');
			result = char((product % 10) + '0') + result;
			if (product > 9) {						// nhớ 1
				if (i > 0) {
					product = 1;
				}
				else {
					result = '1' + result;			// nếu là số đầu tiên thì thêm 1 vào đầu 
				}
			}
			else {
				product = 0;						// <9 nên không nhớ
			}
		}
	}
	//while (result[0] == '0' && result.length() > 1) {
	//	result.erase(0, 1);							// không xoá số 0 ở đầu tránh TH 03 x 2 = 6
	//}
	return result;
}
void Qfloat::AddExponent(int exponent) {
	string exp = to_string(exponent);				// chuyển exponent từ dạng int -> string
	string exp_bin = this->IntegerToBinary(exp);	// chuyển từ decimal string -> binary string
	int len = exp_bin.length();						// độ dài string 
	if (len > 15) {
		cout << "ERROR";
		return;
	}
	int j = len - 1;								// đếm chỉ số exp_bin từ phải sang trái
	for (int i = 15; i > 0; i--) {					// vòng lặp để ghi exp_bin vào phần exponent
		if (exp_bin[j] == '1') {
			this->SetBit1(i);						// ghi vào phần exponent những bit = 1
		}
		j--;
		if (j < 0)									// thêm hết exp_bin vào phần exponent thì dừng
			break;
	}
}
void Qfloat::AddFraction(int exponent, string integer, string decimal) {
	int int_len = integer.length();					// độ dài phần nguyên
	int dec_len = decimal.length();					// độ dài phần thập phân
	int E = exponent - bias_num;					// 2^E
	if (E == 0) {									// dạng chuẩn
		// ghi phần decimal vào fraction
		int j = 0;									// biến đếm cho decimal
		for (int i = 16; i < 128; i++) {
			if (decimal[j] == '1') {				// ghi những chỗ bit = 1
				this->SetBit1(i);
			}
			j++;
			if (j >= dec_len)						// ghi hết decimal thì dừng, bit còn lại = 0
				break;
		}
	}
	else if (E > 0) {								// dịch dấu . sang trái E lần (ghi E bit cuối của integer vô fraction)
		// ghi phần integer vào fraction
		int i = 16;
		int temp = E;
		for (; i < 16 + E; i++) {
			if (integer[int_len - 1 - temp + 1] == '1') {	// ghi những chỗ bit = 1 trong E bit cuối của phần integer
				this->SetBit1(i);
			}
			temp--;
		}
		// ghi phần decimal vào fraction
		int j = 0;									// biến đếm cho decimal
		for (; i < 128; i++) {
			if (decimal[j] == '1') {				// ghi những chỗ bit = 1
				this->SetBit1(i);
			}
			j++;
			if (j >= dec_len)						// ghi hết decimal thì dừng, bit còn lại = 0
				break;
		}
	}
	else {											// dịch dấu . sang phải E lần (bỏ E bit đầu của decimal vô fraction)
		// ghi phần decimal vào fraction
		int j = 0 - E;								// biến đếm cho decimal bỏ đi E bit đầu
		for (int i = 16; i < 128; i++) {
			if (decimal[j] == '1') {				// ghi những chỗ bit = 1
				this->SetBit1(i);
			}
			j++;
			if (j >= dec_len)						// ghi hết decimal thì dừng, bit còn lại = 0
				break;
		}
	}

}
