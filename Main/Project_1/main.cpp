#include<iostream>
#include<fstream>
#include <string>
#include<vector>
#include"Qint.h"
#include"Qfloat.h"
using namespace std;
vector<string> cutstring(string temp,string signal) {
	vector<string> result;
	int pos = temp.find(signal);
	string a;
	while (pos>0) {
		a = temp.substr(0, pos);
		temp.erase(0, pos + 1);
		result.push_back(a);
		pos = temp.find(signal);
	}
	result.push_back(temp);
	return result;
}

vector<string> ReadDataFromFile(char* file_name)
{
	fstream f;
	f.open(file_name, ios::in);
	string temp;
	vector<string> result;
	getline(f, temp);
	while (!f.eof()&&temp!="") {
		result.push_back(temp);
		getline(f, temp);
		
	}
	getline(f, temp);
	result.push_back(temp);
	f.close();
	return result;
}
void WriteDataToFile(char* file_name,vector<string>data)
{
	fstream f;
	f.open(file_name, ios::out);
	cout << data.size();
	for (int i = 0; i < data.size(); i++)
	{
		
		f << data[i] <<endl;
	}

	f.close();
}
void CalQint(QInt& a, QInt& b, QInt& c, string Cal_Operator ) {
	if (Cal_Operator == "+") {
		c = a + b;
	}
	if (Cal_Operator == "-") {
		c = a - b;
	}
	if (Cal_Operator == "*") {
		c = a * b;
	}
	if (Cal_Operator == "/") {
		c = a / b;
	}
	if (Cal_Operator == "|") {
		c = a | b;
	}
	if (Cal_Operator == "^") {
		c = a ^ b;
	}
	if (Cal_Operator == "&") {
		c = a & b;
	}

}
void CompareQint(QInt& a, QInt& b, string& c, string Com_Operator) {
	if (Com_Operator == ">") {
		if (a > b) {
			c = "1";
		}
		else {
			c="0";
		}
	}
	if (Com_Operator == "<") {
		if (a < b) {
			c = "1";
		}
		else {
			c = "0";
		}
	}
	if (Com_Operator == "==") {
		if (a == b) {
			c = "1";
		}
		else {
			c = "0";
		}
	}
	if (Com_Operator == "<=") {
		if (a <= b) {
			c = "1";
		}
		else {
			c = "0";
		}
	}
	if (Com_Operator == ">=") {
		if (a >= b) {
			c = "1";
		}
		else {
			c = "0";
		}
	}
}
void CreateQint(QInt& LNumber,string src,string base) {
	if (base == "2") {
		QInt a(src);
		LNumber = a;
	}
	if (base == "10") {
		QInt init;
		string temp_string;
		temp_string = init.DecToBin(src);
		QInt a(temp_string);
		LNumber = a;
	}
	if (base == "16") {
		QInt init;
		string temp_string;
		temp_string = init.StrHextoBin(src);
		QInt a(temp_string);
		LNumber = a;
	}
}
void MainMenuCommanline() {
	cout << "Chon loai so can tinh: " << endl;
	cout << "1. QInt" << endl;
	cout << "2. QFloat" << endl;
	cout << "3. Thoat" << endl;
}
void QIntMenuCommandline() {
	cout << "1. Chuyen doi Qint thap phan sang nhi phan" << endl;
	cout << "2. Chuyen doi Qint nhi phan sang thap phan" << endl;
	cout << "3. Chuyen doi Qint nhi phan sang thap luc phan" << endl;
	cout << "4. Chuyen doi Qint thap phan sang thap luc phan" << endl;
	cout << "5. Tinh toan" << endl;
	cout << "6. So sanh " << endl;
	cout << "7. Cac phep tinh AND, OR, XOR, NOT " << endl;
	cout << "8. Cac phep tinh <<, >>, Xoay Trai, Xoay Phai: " << endl;
	cout << "9. Quay lai menu chinh" << endl;
}
void QFloatMenuCommandline() {
	cout << "1. Chuyen doi Qfloat nhi phan sang thap phan " << endl;
	cout << "2. Chuyển doi Qfloat thap phan sang nhi phan " << endl;
	cout << "3.Quay lai menu chinh " << endl;
}
int main(int argc, char* argv[]) {
	if (argc == 1) {
		int command=0;
		int Qint_command = 0;
		int Qfloat_command = 0;
		do {
			MainMenuCommanline();
			cout << "Vui long nhap lenh: " << endl;
			cin >> command;
			switch (command) {
			case 1: {
				do {
					QInt temp_m;
					QIntMenuCommandline();
					cout << "Vui long nhap lenh: " << endl;
					cin >> Qint_command;
					switch (Qint_command)
					{
					case 1: {
						string dec;
						cout << "Vui long nhap so can chuyen " << endl;
						cin.ignore();
						getline(cin, dec);
						CreateQint(temp_m, dec, "10");
						cout << temp_m.QInttoBin()<<endl;
						break;
					}
					case 2: {
						string bin;
						cout << "Vui long nhap so can chuyen " << endl;
						cin.ignore();
						getline(cin, bin);
						cout<<temp_m.BinToDec(bin)<<endl;
						break;
					}
					case 3: {
						//string bin;
						////cout << "Vui long nhap so can chuyen " << endl;
						////cin.ignore();
						////getline(cin, bin);
						////cout<<temp_m.BinToHex(bin)<<endl;
						//break;
					}
					case 4: {
						string dec;
						cout << "Vui long nhap so can chuyen " << endl;
						cin.ignore();
						getline(cin, dec);
						cout<<temp_m.DecToHex(dec)<<endl;
						break;
					}
					case 5: {
						string base;
						string cal_string;
						string temp_res;
						cout << "Nhap vao co so can tinh: " << endl;
						cin.ignore();
						getline(cin,base);
						cout << "Nhap vao phep tinh: " << endl;
						getline(cin, cal_string);
						vector<string> temp;
						temp = cutstring(cal_string, " ");
						QInt result_c;
						if (base == "2") {
							QInt a(temp[0]);
							QInt b(temp[2]);
							CalQint(a, b, result_c, temp[1]);
							temp_res = result_c.QInttoBin();
							cout << temp_res<<endl;
						}
						if (base == "10") {
							QInt init;
							string temp_string;
							temp_string = init.DecToBin(temp[0]);
							QInt a(temp_string);
							temp_string = init.DecToBin(temp[2]);
							QInt b(temp_string);
							QInt result_c;
							CalQint(a, b, result_c, temp[1]);
							temp_string = result_c.QInttoBin();
							temp_res = result_c.BinToDec(temp_string);
							cout << temp_res<<endl;
						}
						if (base == "16") {
							QInt init;
							string temp_string;
							temp_string = init.StrHextoBin(temp[0]);
							QInt a(temp_string);
							temp_string = init.StrHextoBin(temp[2]);
							QInt b(temp_string);
							QInt result_c;
							CalQint(a, b, result_c, temp[1]);
							temp_string = result_c.QInttoBin();
							temp_res = result_c.BinToHex(temp_string);
							cout << temp_res<<endl;
						}
						break;
					}
					case 6: {
						string base;
						string cal_string;
						string temp_res;
						cout << "Nhap vao co so can tinh: " << endl;
						cin.ignore();
						getline(cin, base);
						cout << "Nhap vao phep tinh: " << endl;
						getline(cin, cal_string);
						vector<string> temp;
						temp = cutstring(cal_string, " ");
						string result_compare_c;
						
						if (base == "2") {
							QInt a(temp[0]);
							QInt b(temp[2]);
							CompareQint(a, b, result_compare_c, temp[1]);
							cout << result_compare_c << endl;
						}
						if (base == "10") {
							QInt init;
							string temp_string;
							temp_string = init.DecToBin(temp[0]);
							QInt a(temp_string);
							temp_string = init.DecToBin(temp[2]);
							QInt b(temp_string);
							CompareQint(a, b, result_compare_c, temp[1]);
							cout << result_compare_c << endl;
						}
						if (base == "16") {
							QInt init;
							string temp_string;
							temp_string = init.StrHextoBin(temp[0]);
							QInt a(temp_string);
							temp_string = init.StrHextoBin(temp[2]);
							QInt b(temp_string);
							CompareQint(a, b, result_compare_c, temp[1]);
							cout << result_compare_c << endl;
						}
						break;

					}
					case 7: {
						string base;
						string cal_string;
						string temp_res;
						cout << "Nhap vao co so can tinh: " << endl;
						cin.ignore();
						getline(cin, base);
						cout << "Nhap vao phep tinh: " << endl;
						getline(cin, cal_string);
						vector<string> temp;
						temp = cutstring(cal_string, " ");
						QInt result_c;
						if(temp[0] == "~") {
							QInt temp_m;
							CreateQint(temp_m, temp[1], base);
							temp_m = ~temp_m;
							temp_res = temp_m.QInttoBin();
							cout << temp_res<<endl;
						}
						else {
							if (base == "2") {
								QInt a(temp[0]);
								QInt b(temp[2]);
								CalQint(a, b, result_c, temp[1]);
								temp_res = result_c.QInttoBin();
								cout << temp_res<<endl;
							}
							if (base == "10") {
								QInt init;
								string temp_string;
								temp_string = init.DecToBin(temp[0]);
								QInt a(temp_string);
								temp_string = init.DecToBin(temp[2]);
								QInt b(temp_string);
								QInt result_c;
								CalQint(a, b, result_c, temp[1]);
								temp_string = result_c.QInttoBin();
								temp_res = result_c.BinToDec(temp_string);
								cout<<temp_res<<endl;
							}
							if (base == "16") {
								QInt init;
								string temp_string;
								temp_string = init.StrHextoBin(temp[0]);
								QInt a(temp_string);
								temp_string = init.StrHextoBin(temp[2]);
								QInt b(temp_string);
								QInt result_c;
								CalQint(a, b, result_c, temp[1]);
								temp_string = result_c.QInttoBin();
								temp_res = result_c.BinToHex(temp_string);
								cout<<temp_res<<endl;
							}
						}
						break;
						
					}
					case 8: 
					{
						string base;
						string cal_string;
						string temp_res;
						cout << "Nhap vao co so can tinh: " << endl;
						cin.ignore();
						getline(cin, base);
						cout << "Nhap vao phep tinh: " << endl;
						getline(cin, cal_string);
						vector<string> temp;
						temp = cutstring(cal_string, " ");
						if (temp[1] == "<<") {
							int n = stoi(temp[2]);
							QInt LNumber;
							CreateQint(LNumber, temp[0], base);
							QInt result_c;
							result_c = LNumber << n;
							temp_res = result_c.QInttoBin();
							cout<<temp_res<<endl;
						}
						if (temp[1] == ">>") {
							int n = stoi(temp[2]);
							QInt LNumber;
							CreateQint(LNumber, temp[0], base);
							QInt result_c;
							result_c = LNumber >> n;
							temp_res = result_c.QInttoBin();
							cout<<temp_res<<endl;
						}
						if (temp[1] == "ror") {
							int n = stoi(temp[2]);
							QInt LNumber;
							CreateQint(LNumber, temp[0], base);
							LNumber = LNumber.ror(n);
							temp_res = LNumber.QInttoBin();
							cout << temp_res << endl;
						}
						if (temp[1] == "rol") {
							int n = stoi(temp[2]);
							QInt LNumber;
							CreateQint(LNumber, temp[0], base);
							LNumber = LNumber.rol(n);
							temp_res = LNumber.QInttoBin();
							cout<<temp_res<<endl;
						}
						break;
					}
					default:
						break;
					}
				} while (Qint_command != 9);
				break;
				}
			case 2: {
				do {
					Qfloat res;
					QFloatMenuCommandline();
					cout << "Vui long nhap lenh: " << endl;
					cin >> Qfloat_command;
					switch (Qfloat_command)
					{ 
					case 1: {
						string bin;
						cout << "Vui long nhap so can chuyen " << endl;
						getline(cin, bin);
						int size = 128;
						bool* a = new bool[128];
						for (int i = 0; i < size; i++) {
							if (bin[i] == '0') {
								a[i] = 0;
							}
							else {
								a[i] = 1;
							}
						}
						Qfloat n(a);
						string temp_res = n.GetDecimalValue();
						cout << temp_res;
						break;
					}
					case 2:
					{
						string dec;
						cout << "Vui long nhap so can chuyen " << endl;
						getline(cin, dec);
						
						Qfloat n(dec);
						n.PrintQfloat();
					}
					default:
						break;
					}
				} while (Qfloat_command != 3);
				break;
			}
			default:break;
			}

		}while (command != 3);
	}
	else {
		vector <string> input, output;
		input = ReadDataFromFile(argv[1]);
		vector<string> temp;
		QInt n;
		string temp_res;
		for (int i = 0; i < input.size(); i++) {
			temp = cutstring(input[i], " ");
			switch (temp.size()) {
			case 3: {//chuyen doi co so
				if (temp[1] == "~") {
					QInt temp_m;
					CreateQint(temp_m, temp[2], temp[0]);
					temp_m = ~temp_m;
					temp_res = temp_m.QInttoBin();
					output.push_back(temp_res);
				}
				else {
					if (temp[0] == "10" && temp[1] == "2") {
						temp_res = n.DecToBin(temp[2]);
						output.push_back(temp_res);
					}
					if (temp[0] == "2" && temp[1] == "10") {
						temp_res = n.BinToDec(temp[2]);
						output.push_back(temp_res);
					}
					if (temp[0] == "2" && temp[1] == "16") {
						temp_res = "LOI";
						output.push_back(temp_res);
					}
					if (temp[0] == "10" && temp[1] == "16") {
						temp_res = n.DecToHex(temp[2]);
						output.push_back(temp_res);
					}

				}
				break;
			}

			case 4: {
				if (temp[2] == "<<") {
					int n = stoi(temp[3]);
					QInt LNumber;
					CreateQint(LNumber, temp[1], temp[0]);
					QInt result_c;
					result_c = LNumber << n;
					temp_res = result_c.QInttoBin();
					output.push_back(temp_res);
				}
				if (temp[2] == ">>") {
					int n = stoi(temp[3]);
					QInt LNumber;
					CreateQint(LNumber, temp[1], temp[0]);
					QInt result_c;
					result_c = LNumber >> n;
					temp_res = result_c.QInttoBin();
					output.push_back(temp_res);
				}
				if (temp[2] == "ror") {
					int n = stoi(temp[3]);
					QInt LNumber;
					CreateQint(LNumber, temp[1], temp[0]);
					QInt result_c;
					result_c = LNumber.ror(n);
					temp_res = result_c.QInttoBin();
					output.push_back(temp_res);
				}
				if (temp[2] == "rol") {
					int n = stoi(temp[3]);
					QInt LNumber;
					CreateQint(LNumber, temp[1], temp[0]);
					QInt result_c;
					result_c = LNumber.rol(n);
					temp_res = result_c.QInttoBin();
					output.push_back(temp_res);
				}
				if (temp[2] == ">" || temp[2] == "<" || temp[2] == ">=" || temp[2] == "<=" || temp[2] == "==") {
					string result_compare_c;
					if (temp[0] == "2") {
						QInt a(temp[1]);
						QInt b(temp[3]);
						CompareQint(a, b, result_compare_c, temp[2]);
						output.push_back(result_compare_c);
					}
					if (temp[0] == "10") {
						QInt init;
						string temp_string;
						temp_string = init.DecToBin(temp[1]);
						QInt a(temp_string);
						temp_string = init.DecToBin(temp[3]);
						QInt b(temp_string);
						CompareQint(a, b, result_compare_c, temp[2]);
						output.push_back(result_compare_c);
					}
					if (temp[0] == "16") {
						QInt init;
						string temp_string;
						temp_string = init.StrHextoBin(temp[1]);
						QInt a(temp_string);
						temp_string = init.StrHextoBin(temp[3]);
						QInt b(temp_string);
						CompareQint(a, b, result_compare_c, temp[2]);
						output.push_back(result_compare_c);
					}
				}
				if (temp[2] == "+" || temp[2] == "-" || temp[2] == "*" ||temp[2]=="/"||temp[2]=="^"||temp[2]=="|"||temp[2]=="&") {
					QInt result_c;
					if (temp[0] == "2") {
						QInt a(temp[1]);
						QInt b(temp[3]);
						CalQint(a, b, result_c, temp[2]);
						temp_res = result_c.QInttoBin();
						output.push_back(temp_res);
					}
					if (temp[0] == "10") {
						QInt init;
						string temp_string;
						temp_string = init.DecToBin(temp[1]);
						QInt a(temp_string);
						temp_string = init.DecToBin(temp[3]);
						QInt b(temp_string);
						QInt result_c;
						CalQint(a, b, result_c, temp[2]);
						temp_string = result_c.QInttoBin();
						temp_res = result_c.BinToDec(temp_string);
						output.push_back(temp_res);
					}
					if (temp[0] == "16") {
						QInt init;
						string temp_string;
						temp_string = init.StrHextoBin(temp[1]);
						QInt a(temp_string);
						temp_string = init.StrHextoBin(temp[3]);
						QInt b(temp_string);
						QInt result_c;
						CalQint(a, b, result_c, temp[2]);
						temp_string = result_c.QInttoBin();
						temp_res = result_c.BinToHex(temp_string);
						output.push_back(temp_res);
					}
				}
				break;
			}

			{
			default:
				break;
			}

	}
		}
		WriteDataToFile(argv[2], output);
		}

	

	/*vector<string> input_float, output_float;
	
	input_float = ReadDataFromFile("QFloat_input.txt");
	vector<string> temp;
		string temp_res;
		for (int i = 0; i < input_float.size(); i++) {
			
			temp = cutstring(input_float[i], " ");
			if (temp[0] == "10" && temp[1] == "2") {
				Qfloat n(temp[2]);
				temp_res = "LOI";
				output_float.push_back(temp_res);
			}
			if (temp[0] == "2" && temp[1] == "10") {
				int size = temp[2].size();
				bool* a=new bool[128];
				for (int i = 0; i < size; i++) {
					if (temp[2][i] == '0') {
						a[i] = 0;
					}
					else {
						a[i] = 1;
					}
				}
				Qfloat n(a);
				temp_res = n.GetDecimalValue();
				output_float.push_back(temp_res);
			}

			
	}
	WriteDataToFile("QFloat_output.txt",output_float);*/
	return 0;
}

