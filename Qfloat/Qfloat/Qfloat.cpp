#include "Qfloat.h"
// default constructor
Qfloat::Qfloat() {
	for (int i = 0; i < 4; i++)						// khởi tạo Qfloat với giá trị 0
		this->data[i] = 0;
}
// copy constructor
Qfloat::Qfloat(const Qfloat &p) {
	for (int i = 0; i < 4; i++)						// copy từng byte của p vào Qfloat
		this->data[i] = p.data[i];
}
// destructor
Qfloat::~Qfloat() {}
// đặt bit 1 tại vị trí i
void Qfloat::SetBit1(int i) {
	this->data[i / 32] = this->data[i / 32] | (1 << (31 - i % 32));
}
// lấy bit ở vị trí i 
int Qfloat::GetBit(int i) {							// lấy bit tại vị trí i
	return (this->data[i / 32] >> (31 - i % 32)) & 1;
}
// đọc Qfloat ở dạng thập phân	
void Qfloat::ScanQfloat() {
	string s;										// chuỗi string dạng thập phân
	fflush(stdin);
	getline(cin, s);
	*this = Qfloat(s);
}
// đọc Qfloat ở dạng nhị phân
void Qfloat::ScanBinQfloat() {
	string s;										// chuỗi string dạng nhị phân
	fflush(stdin);
	getline(cin, s);
	int len = s.length();
	int qfloat_num = fraction_num + exponent_num + sign_num;		// tổng số bit của Qfloat
	bool* bits = new bool[qfloat_num];				// khởi tạo chuỗi bool chứa dãy nhị phân
	for (int i = 0; i < qfloat_num; i++) {			// khởi tạo Qfloat = 0
		bits[i] = 0;
	}
	for (int i = 0; i < len; i++) {					// đưa giá trị dãy nhị phân vào Qfloat
		if (s[i] == '1') {
			bits[i] = 1;
		}
	}
	*this = Qfloat(bits);
}
// in ra Qfloat dưới dạng nhị phân	
void Qfloat::PrintQfloat() {
	for (int i = 0; i < 128; i++) {
		cout << this->GetBit(i);
		if (i == 0)
			cout << " ";
		if (i == 15)
			cout << " ";
	}
}
// constructor với tham số là dãy nhị phân
Qfloat::Qfloat(bool* bits) {
	for (int i = 0; i < 4; i++) {					// khởi tạo Qfloat với giá trị 0 
		this->data[i] = 0;
	}
	for (int i = 0; i < 128; i++) {
		if (bits[i] == 1) {
			this->SetBit1(i);
		}
	}
}
// constructor với tham số là chuỗi thập phân
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
// chuyển chuỗi số đằng trước dấu chấm thành nhị phân
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
// chuyển chuỗi số đằng sau dấu chấm thành nhị phân		
string Qfloat::DecimalToBinary(string s) {
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
// tính exponent 
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
// trả về kết quả là chuỗi string*2
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
// trả về kết quả là chuỗi string/2
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
	//	result.erase(0, 1);							// không xoá số 0 ở đầu, vd: 03 x 2 = 06 
	//}
	return result;
}
// ghi exponent vào data
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
// ghi fraction vào data
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
// chuyển đổi số Qfloat thập phân sang nhị phân
void DecToBin(Qfloat a) {
	cout << "Nhap so thap phan" << endl;
	cout << "Dec: ";
	a.ScanQfloat();
	cout << "Bin: ";
	a.PrintQfloat();
}

string Qfloat::SumString(string a, string b)
{
	// đảo 2 chuỗi
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	// chèn số 0 vào cuối chuỗi
	a.push_back('0');
	b.push_back('0');

	char temp = 0;	// biến nhớ
	string result;
	int i = 0;

	// cộng từ hàng số tương ứng của 2 chuỗi
	while ((i < a.length()) && (i < b.length()))
	{
		char sum = (a[i] - '0' + b[i] - '0' + temp) % 10 + '0';
		temp = (a[i] - '0' + b[i] - '0' + temp) / 10;
		result.push_back(sum);
		i++;
	}
	if (i < a.length())
	{
		result = result + a.substr(i);
	}
	else
	{
		if (i < b.length())
		{
			result = result + b.substr(i);
		}
	}
	if (result[result.length() - 1] == '0')
	{
		result.pop_back();
	}

	reverse(result.begin(), result.end());
	return result;
}
string Qfloat::Double(string src)
{
	return this->SumString(src, src);
}
string Qfloat::BinToDec(string Bin) {
	string pow = "1";
	string result = "0";

	// Chuyển chuỗi nhị phân sang chuỗi thập phân
	for (int i = Bin.length() - 1; i >= 0; i--)
	{
		if (Bin[i] == '1')
		{
			result = SumString(result, pow);
		}
		pow = Double(pow);	//tính 2^i
	}

	return result;
}
string Qfloat::FloatDivTwo(string a)
{
	string result;
	int i = 0;
	char temp = 0;
	while ((i < a.length()) || (temp != 0))
	{
		if (i < a.length())
		{
			if (a[i] == '.')
			{
				result.push_back('.');
				i++;
			}
			else
			{
				result.push_back((a[i] - '0' + temp * 10) / 2 + '0');
				temp = (a[i] - '0' + temp * 10) % 2;
				i++;
			}
		}
		else
		{
			size_t dot = result.find('.');
			if (dot != string::npos)
			{
				result.push_back((temp * 10) / 2 + '0');
				temp = (temp * 10) % 2;
			}
			else
			{
				result.push_back('.');
				result.push_back((temp * 10) / 2 + '0');
				temp = (temp * 10) % 2;
			}
		}

	}
	if (result.length() >= 2)
	{
		if ((result[0] == '0') && (result[1] != '.'))
		{
			result.erase(result.begin());
		}
	}
	return result;
}
string Qfloat::SumFloatString(string a, string b)
{
	size_t ad = a.find('.');
	size_t bd = b.find('.');
	string f1, f2;
	string z1, z2;
	string result;
	if (ad != string::npos)
	{
		f1 = a.substr(ad + 1);
		z1 = a.substr(0, ad);
	}
	else
	{
		z1 = a;
	}

	if (bd != string::npos)
	{
		f2 = b.substr(bd + 1);
		z2 = b.substr(0, bd);
	}
	else
	{
		z2 = b;
	}
	string fadd;
	int min;
	if (f1.length() < f2.length())
	{
		min = f1.length() - 1;
		fadd = f2.substr(f1.length());
	}
	else
	{
		min = f2.length() - 1;
		if (f1.length() != f2.length())
		{
			fadd = f1.substr(f2.length());
		}
	}

	char temp = 0;
	for (int i = min; i >= 0; i--)
	{
		char sum = (f1[i] - '0' + f2[i] - '0' + temp) % 10 + '0';
		temp = (f1[i] - '0' + f2[i] - '0' + temp) / 10;
		result = sum + result;
	}
	if ((ad != string::npos) || (bd != string::npos))
	{
		result = '.' + result + fadd;
	}

	int k = z1.length() - z2.length();
	int i = z1.length() - 1;
	while ((i >= 0) || (temp != 0) || (i - k >= 0))
	{
		if ((i >= 0) && (i - k >= 0))
		{
			char sum = (z1[i] - '0' + z2[i - k] - '0' + temp) % 10 + '0';
			temp = (z1[i] - '0' + z2[i - k] - '0' + temp) / 10;
			result = sum + result;
		}
		else if (i >= 0)
		{
			if (temp == 1)
			{
				char sum = (z1[i] - '0' + temp) % 10 + '0';
				temp = (z1[i] - '0' + temp) / 10;
				result = sum + result;
			}
			else
			{
				result = z1.substr(0, i + 1) + result;
				break;
			}
		}
		else if (i - k >= 0)
		{
			if (temp == 1)
			{
				char sum = (z2[i] - '0' + temp) % 10 + '0';
				temp = (z2[i] - '0' + temp) / 10;
				result = sum + result;
			}
			else
			{
				result = z2.substr(0, i - k + 1) + result;
				break;
			}
		}
		else
		{
			if (temp == 1)
			{
				result = '1' + result;
			}
			break;
		}
		i--;
	}
	while (result[result.length() - 1] == '0')
	{
		result.pop_back();
		if (result[result.length() - 1] == '.')
		{
			result.pop_back();
			break;
		}
	}
	return result;
}
// tính 2^(-x)
string Qfloat::PowerNeg2(int x) {  
	string result = "1";							// bắt đầu từ 1
	for (int i = 0; i < x; i++) {
		result = this->FloatDivTwo(result);			// x/2
	}
	return result;
}
// chuyển phần thập phân hệ 2 -> 10
string Qfloat::DecBinToDec(string s) {
	string result = "0";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '1') {
			result = this->SumFloatString(result,PowerNeg2(i+1));
		}
	}
	result.erase(0, 1);								// xoá "0."
	result.erase(0, 1);
	return result;
}
// kiểm tra số đặc biệt
string Qfloat::CheckDenormalized() {
	bool check_exp_0 = true;						// nếu exponent toàn số 0
	bool check_exp_1 = true;						// nếu exponent toàn số 1
	for (int i = 1; i < 16; i++) {
		if (this->GetBit(i) != 0) {
			check_exp_0 = false;
		}
		if (this->GetBit(i) != 1) {
			check_exp_1 = false;
		}
	}
	if (check_exp_0 == true) {						// underflow hoặc số 0
		bool check_frac_0 = true;					// nếu fraction toàn số 0
		for (int i = 16; i < 127; i++) {
			if (this->GetBit(i) != 0) {				
				check_frac_0 = false;
			}
		}
		if (check_frac_0 == true) {					// fraction toàn số 0
			return "0";
		}
		else {										// fraction không toàn số 0
			return "underflow";					
		}
		
	}
	else if (check_exp_1 == true) {					// +-infinity hoặc NaN
		bool check_frac_0 = true;					// nếu fraction toàn số 0
		for (int i = 16; i < 127; i++) {
			if (this->GetBit(i) != 0) {
				check_frac_0 = false;
			}
		}
		if (check_frac_0 == true) {					// fraction toàn số 0
			if (this->GetBit(0) == 0) {
				return "+infinity";
			}
			else {
				return "-infinity";
			}
		}
		else {										// fraction không toàn số 0
			return "NaN";
		}
	}
	return "";
}
// chuyển dạng 1.F * 2 ^ E về dạng chưa chuẩn
string Qfloat::MovePoint(string frac, int e) {			//1.frac * 2^e 
	string result;
	if (e < 0) {								// result = 0.<e-1 số 0>1<frac>
		e = -e;
		result += "0.";
		for (int i = 0; i < e - 1; i++) {
			result += '0';
		}
		result += '1' + frac;
	}
	else if (e == 0) {							// result = 1.<frac>
		result += "1." + frac;
	}
	else {
		if (e >= frac.length()) {				// result = 1<frac><e-frac.len số 0>.0
			result += "1" + frac;
			for (int i = 0; i < e - frac.length(); i++) {
				result += '0';
			}
			result += ".0";
		}
		else {									// result = 1<e bit đầu frac>.<frac còn lại>
			result += '1';
			int i = 0;
			for (; i < e; i++) {
				result += frac[i];
			}
			result += '.';
			for (; i < frac.length(); i++) {
				result += frac[i];
			}
		}
	}
	return result;
}
string Qfloat::GetDecimalValue() {
	if (this->CheckDenormalized() != "")			// là một trong các số đặc biệt thì thoát
		return this->CheckDenormalized();
	string result;									// chuỗi lưu kết quả
	if (this->GetBit(0) == 1) {						// số âm
		result += '-';
	}
	// tính F (1.F)
	string frac;									// lấy fraction 
	for (int i = 16; i < 128; i++) {
		frac += this->GetBit(i) + '0';
	}

	int j = 111;
	while (frac[j] == '0' && frac.length() > 1) {	// xoá số 0 ở cuối
		frac.erase(j, 1);
		j--;
	}
	// tính E (2^E) 
	string exp_bin;									// lấy exponent (hệ 2)
	for (int i = 1; i < 16; i++) {
		exp_bin += this->GetBit(i) + '0';
	}
	string exp_dec = this->BinToDec(exp_bin);		// exponent hệ 10
	int exponent = stoi(exp_dec, nullptr, 10);		// chuyển dạng string sang int
	int E = exponent - bias_num;
	// chuyển về dạng chưa chuẩn
	string denormalized = MovePoint(frac, E);
	string IntBin, DecBin;							// tách phần integer và decimal
	int i = 0;
	for (; i < denormalized.length(); i++) {
		if (denormalized[i] != '.') {
			IntBin += denormalized[i];
		}
		else {
			break;
		}
	}
	i++;
	for (; i < denormalized.length(); i++) {
		DecBin += denormalized[i];
	}
	// tính phần nguyên
	string IntDec = this->BinToDec(IntBin);
	// tính phần thập phân
	string DecDec = this->DecBinToDec(DecBin);
	// ghép phần nguyên và thập phân lại
	result += IntDec + '.' + DecDec;
	return result;
}
void BinToDec(Qfloat a) {
	cout << "Nhap day nhi phan: ";
	a.ScanBinQfloat();
	cout << "Bin: ";
	a.PrintQfloat();
	cout << endl;
	cout << "Dec: " << a.GetDecimalValue();
}