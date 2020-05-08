#include "Qint.h"

QInt::QInt()
{
	Data[0] = 0;
	Data[1] = 0;
	Data[2] = 0;
	Data[3] = 0;
}

QInt::QInt(const QInt& x)
{
	this->Data[0] = x.Data[0];
	this->Data[1] = x.Data[1];
	this->Data[2] = x.Data[2];
	this->Data[3] = x.Data[3];
}

QInt::QInt(const string& Bin)
{
	Data[0] = 0;
	Data[1] = 0;
	Data[2] = 0;
	Data[3] = 0;
	if (!Bin.empty() && Bin.length() <= 128)
	{
		for (size_t i = 0; i < Bin.length(); i++)
		{
			if (Bin[i] == '1')
			{
				size_t pos = i / (sizeof(int) * CHAR_BIT);
				Data[pos] = Data[pos] | (1 << (31 - (i % (sizeof(int) * CHAR_BIT))));
			}
		}
	}
}

QInt::~QInt()
{
}

bool QInt::is_Negative()
{
	if (Data[0] < 0)
	{
		return true;
	}
	return false;
}

bool QInt::is_Zero()
{
	for (int i = 0; i < 4; i++)
	{
		if (Data[i] != 0)
		{
			return false;
		}
	}
	return true;
}

void QInt::ScanQInt(QInt& x)
{
	string src;
	getline(cin, src);
	src = StrDectoBin(src);
	x = QInt(src);
}

void QInt::PrintQInt(QInt x)
{
	cout << x.QInttoStrDec() << endl;
}

QInt& QInt::operator=(const QInt& x)
{
	if (this == &x)
	{
		return *this;
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			this->Data[i] = x.Data[i];
		}
		return *this;
	}
}

QInt QInt::operator>>(const int& Bit)
{
	QInt result;
	int k = Bit / 32;
	int n = Bit % 32;

	// Xử lý chuỗi âm
	if (this->Data[0] < 0)
	{
		for (int i = 0; (i < 4) && (k - i > 0); i++)
		{
			result.Data[i] = -1;
		}
	}

	// Dịch bit
	if (k < 4)
	{
		result.Data[k] = this->Data[0] >> n;
		for (int i = k + 1; i < 4; i++)
		{
			// Đẩy bit tràn lên
			for (int j = 0; j < n; j++)
			{
				result.Data[i] = result.Data[i] | (((this->Data[i - 1] >> j) & 1) << (32 - n + j));
			}

			// Dịch bit
			if (n > 0)
			{
				result.Data[i] = result.Data[i] | ((this->Data[i - k] >> n)& (_Max_Int >> (n - 1)));
				//(this->Data[i - k] >> n)& (_Max_Int >> (n - 1)) tạo ra chuỗi bit 0000... khi dịch n bit tại block data[i-k]
				//để tránh ảnh hưởng để những bit đã được thay đổi và lưu trong result.Data[i] ở trên khi được thêm vào.
			}
			else
			{
				result.Data[i] = this->Data[i - k];
			}
		}
	}
	return result;
}

QInt QInt::operator<<(const int& Bit)
{
	QInt result;
	int k = Bit / 32;
	int n = Bit % 32;
	for (int i = 0; i < 4 - k; i++)
	{
		result.Data[i] = this->Data[i + k] << n;

		// Đẩy bit tràn xuống
		if (i + k + 1 < 3)
		{
			for (int j = 0; j < n; j++)
			{
				result.Data[i] = result.Data[i] | ((((this->Data[i + k + 1]) >> (31 - j)) & 1) << (n - 1 - j));
			}
		}
	}
	return result;
}





QInt& QInt::rol()
{
	QInt temp;
	temp = *this;
	char top = ((temp.Data[0] >> 31) & 1) + '0';	// Lưu bit đầu
	temp = temp << 1;
	temp.Data[3] = temp.Data[3] | (top - '0');		// Chèn bit đầu ở cuối
	return temp;
}

QInt& QInt::ror()
{
	QInt temp;
	temp = *this;
	char bot = ((temp.Data[3]) & 1) + '0';	// Lưu bit đầu
	temp = temp >> 1;

	// Xử lý chèn bit
	if (temp.Data[0] < 0)
	{
		temp.Data[0] = temp.Data[0] & (_Max_Int | (bot << 31));
	}
	else
	{
		temp.Data[0] = temp.Data[0] | (bot << 31);
	}
	return temp;
}

string QInt::StrDivTwo(string src)
{
	string result;
	int temp = 0;
	for (int i = 0; i < src.length(); i++)
	{
		temp = temp * 10 + (src[i] - '0');
		if (i > 0 || (i == 0 && temp >= 2))
		{
			int q = temp / 2;
			result.push_back(q + '0');
		}
		temp = temp % 2;
	}
	return result;
}

string QInt::StrDectoBin(string src)
{
	string result;
	bool Negative = false;

	// kiểm tra chuỗi số có phải chuỗi số âm không
	if (src[0] == '-')
	{
		src.erase(src.begin());
		Negative = true;
	}

	// chuyển chuỗi thập phân thành nhị phân
	while (!src.empty())
	{
		result.push_back((src[src.length() - 1] - '0') % 2 + '0');	//thêm bit vào chuỗi
		src = StrDivTwo(src);
	}

	//chèn số 0 vào chuỗi nhị phân cho đủ 128 bit
	while (result.length() < 128)
	{
		result.push_back('0');
	}


	// Xử lý chuyển qua dạng bù 2 cho số âm
	if (Negative)
	{
		int pos = result.find('1');
		for (int i = pos + 1; i < 128; i++)
		{
			if (result[i] == '1')
			{
				result[i] = '0';
			}
			else
			{
				result[i] = '1';
			}
		}
	}

	reverse(result.begin(), result.end());
	return result;
}

string QInt::SumString(string a, string b)
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



string QInt::Double(string src)
{
	return SumString(src, src);
}

string QInt::QInttoStrDec()
{
	// Xét số 0
	if (this->is_Zero())
	{
		return "0";
	}

	string Bin = this->QInttoBin();
	bool Negative = false;

	// Kiểm tra số âm và chuyển chuỗi bit âm thành bit dương
	if (this->is_Negative())
	{
		Negative = true;
		size_t pos = Bin.find_last_of('1');
		for (int i = 0; i < pos; i++)
		{
			if (Bin[i] == '0')
			{
				Bin[i] = '1';
			}
			else
			{
				Bin[i] = '0';
			}
		}
	}

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

	// Kiêm tra số âm và thêm dấu trừ
	if (Negative)
	{
		result = "-" + result;
	}
	return result;
}

QInt QInt::bu2()
{
	QInt temp(StrDectoBin("1"));  // so 1 int bit
	return this->bu1() + temp;	  // bu2 = bu1+1;
}

QInt QInt::operator~()
{
	QInt result;
	/*
	NOT(~) =>{
		not 0 = 1
		not 1 = 0
	}
	*/
	for (int i = 0; i < 128; i++) {
		if (this->getBitPositionI(i) == 0) {
			result.setBitPositionIto1(i);
		}
		else
		{
			result.setBitPositionIto0(i);
		}
	}
	return result;
}




string QInt::QInttoBin()
{
	string Bin;
	char temp;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			temp = ((Data[i] >> (31 - j)) & 1) + '0';
			Bin.push_back(temp);
		}
	}
	return Bin;
}

QInt QInt::bu1()
{
	QInt result;
	string Bin;
	char temp;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			int Bit = getBitPositionI(i * 32 + j);
			if (Bit == 1) {
				result.setBitPositionIto0(i * 32 + j); // chuyen tu 1 ->0
			}
			else {
				result.setBitPositionIto1(i * 32 + j); // chuyen tu 0 ->1
			}
		}
	}
	return result;
}

int QInt::getBitPositionI(int i)
{
	int result;
	size_t posIntArr = i / (sizeof(int) * CHAR_BIT); // vi tri - Data[pos]
	size_t posBitInArr = i - posIntArr *(sizeof(int) * CHAR_BIT); // vi tri - Data[pos]
	result = (Data[posIntArr]>>(31- posBitInArr)) & 1;
	return result;
}

void QInt::setBitPositionIto1(int i)
{
	int result;
	size_t posIntArr = i / (sizeof(int) * CHAR_BIT); // vi tri - Data[pos]
	size_t posBitInArr = i - posIntArr * (sizeof(int) * CHAR_BIT); // vi tri - Data[pos]
	Data[posIntArr] = (Data[posIntArr] | (1 << (31 - posBitInArr))); // dung OR voi bit 1 duoc dich qua trai 31 - posBitInArr 
}

void QInt::setBitPositionIto0(int i)
{
	int result;
	size_t posIntArr = i / (sizeof(int) * CHAR_BIT); // vi tri - Data[pos]
	size_t posBitInArr = i - posIntArr * (sizeof(int) * CHAR_BIT); // vi tri - Data[pos]
	Data[posIntArr] = (Data[posIntArr] & (~(1 << (31 - posBitInArr)))); // dung AND voi bit 0 dich qua trai 31 - posBitInArr - tat ca cac bit con lai la 1
}

QInt operator+( QInt a,  QInt b)
{
	QInt result;
	int memorize = 0; // lưu biến nhớ khi thức hiện phép cộng vd: 1 + 1 thì memorize = 1
	int sum = 0; // tổng khi cộng 2 bit lại
	// chạy từ bit 127 ->0
	for (int i = 3; i >= 0; i--) 
	{
		for (int j = 31; j >= 0; j--)
		{	
			int Bita = a.getBitPositionI(i * 32 + j); // lấy vị trí 2 bit
			int Bitb = b.getBitPositionI(i * 32 + j);	// lấy vị trí 2 bit
			
			sum = Bita + Bitb + memorize; //tổng 2 bit với biến nhớ ở bit trước
			//gán kết quả 
			if (sum % 2 == 0) {
				result.setBitPositionIto0(i * 32 + j);
			}
			else {
				result.setBitPositionIto1(i * 32 + j);
			}

			//lưu biến nhớ cho bit sau
			memorize =(int)sum / 2;
		}
	}
	return result;
}

QInt operator-(QInt a, QInt b)
{
	QInt result;
	/*
		ý tưởng : a - b = a + (-b);
		-b = b.bu2();
	*/
	b = b.bu2();
	result = a + b;
	return result;
}

QInt operator*(QInt a, QInt b)
{
	QInt result;
	QInt tempMulti;
	int isNegative = 1; //kiem tra xem sau khi chia xong la so duong hay am
	//Kiem tra so am  de chuyen thanh so duong
	if (a.getBitPositionI(0) == 1) {
		a = a.bu2();
		isNegative = isNegative * -1;
	}
	if (b.getBitPositionI(0) == 1) {
		b = b.bu2();
		isNegative = isNegative * -1;
	}

	/*
		y tuong :
		Neu bit a vi tri i = 1 :
			+ Lấy b dịch qua trái i vị trí rồi cộng vào kq
		Do đều chuyển qua số dương nên bit dấu bằng 0
	*/ 

	for (int i = 3; i >= 0; i--)
	{
		for (int j = 31; j >= 0; j--)
		{
			if (a.getBitPositionI(i * 32 + j) == 1) {
				tempMulti = b << (127 - (i * 32 + j));
				result = result + tempMulti;
			}
		}
	}
	//Nếu (a*b<0) thì chuyển kết quả sang bù 2 
	if (isNegative == -1) {
		result = result.bu2();
	}
	return result;
}

QInt operator/(QInt a, QInt b)
{
	QInt result;
	//kiem tra xem sau khi chia xong la so duong hay am
	int isNegative = 1;

	//Kiem tra so am  de chuyen thanh so duong
	if (a.getBitPositionI(0) == 1) {
		a = a.bu2();
		isNegative = isNegative * -1; //neu am thi *-1
	}
	if (b.getBitPositionI(0) == 1) {
		b = b.bu2();
		isNegative = isNegative * -1; //neu am thi *-1
	}
	/*
		y tuong :
		Dịch temp = 1(Dec) qua trái khi nào b*temp > a thì 
		lấy 
			+ temp = temp >> 1;
			+ a = a - b * temp;
			+ result = result + temp;
		Lặp lại đến khi a = 0;
	*/
	while (!a.is_Zero()) {
		QInt temp;
		temp.setBitPositionIto1(127);  //temp = 1;
	
		for (int i = 0; i < 128; i++) { //de dich so 1(DEC) qua trai
			if (temp * b > a && i!=0) {  
				temp = temp >> 1; 
				result = result + temp;
				a = a - b * temp;
				break;
			}
			if (temp * b > a && i == 0) {
				temp = temp >> 1;
				a = temp;
				break;
			}
			temp = temp << 1;
		}
	}
	//Nếu (a*b<0) thì chuyển kết quả sang bù 2 
	if (isNegative == -1) {
		result = result.bu2();
	}
	return result;
}

QInt operator&(QInt a, QInt b)
{
	QInt result;
	/*
		and(&) =>{
			0 and 0 = 0
			1 and 1 = 1
			0 and 1 = 0
			1 and 0 = 0
		}
	*/
	for (int i = 0; i < 128; i++) {
		int A_BitI = a.getBitPositionI(i);
		int B_BitI = b.getBitPositionI(i);
		if (A_BitI == 1 && B_BitI == 1) {
			result.setBitPositionIto1(i);
		}
		else {
			result.setBitPositionIto0(i);
		}
	}
	return result;
}

QInt operator|(QInt a, QInt b)
{
	QInt result;
	/*
		or(|) =>{
			0 or 0 = 0
			1 or 1 = 1
			0 or 1 = 1
			1 or 0 = 1
		}
	*/
	for (int i = 0; i < 128; i++) {
		int A_BitI = a.getBitPositionI(i);
		int B_BitI = b.getBitPositionI(i);
		if (A_BitI == 0 && B_BitI == 0) {
			result.setBitPositionIto0(i);
		}
		else {
			result.setBitPositionIto1(i);
		}
	}
	return result;
}

QInt operator^(QInt a, QInt b)
{
	QInt result;
	/*
		xor(^) =>{
			0 xor 0 = 0
			1 xor 1 = 0
			0 xor 1 = 1
			1 xor 0 = 1
		}
	*/
	for (int i = 0; i < 128; i++) {
		int A_BitI = a.getBitPositionI(i);
		int B_BitI = b.getBitPositionI(i);
		if ((A_BitI == 1 && B_BitI == 1) || (A_BitI == 0 && B_BitI == 0)) {
			result.setBitPositionIto0(i);
		}
		else {
			result.setBitPositionIto1(i);
		}
	}
	return result;
}





bool operator>(QInt a, QInt b)
{
	QInt minus = a - b;
	if (minus.getBitPositionI(0) == 0 && !minus.is_Zero()) {
		return true;
	}
	return false;
}

bool operator<(QInt a, QInt b)
{
	QInt minus = a - b;
	if (minus.getBitPositionI(0) == 1) {
		return true;
	}
	return false;
}

bool operator==(QInt a, QInt b)
{
	QInt minus = a - b;
	if (minus.is_Zero()) {
		return true;
	}
	return false;
}

bool operator>=(QInt a, QInt b)
{
	QInt minus = a - b;
	if (minus.getBitPositionI(0) == 1) {
		return false;
	}
	return true;
}

bool operator<=(QInt a, QInt b)
{
	QInt minus = a - b;
	if (minus.getBitPositionI(0) == 0 && !minus.is_Zero()) {
		return false;
	}
	return true;
}


