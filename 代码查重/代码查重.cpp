
#include "pch.h"
#include "function.h"


int main()
{
	int lenA, lenB;
	int repeat_row;
	double repeat_rate;
	double threshold;
	string A = "A.cpp";
	string B = "B.cpp";
	Code code;
	lenA = code.string_init(A, code.a);
	lenB = code.string_init(B, code.b);
	//code.print_string(code.a, lenA);
	//code.print_string(code.b, lenB);
	cout << "输入阈值：";
	cin >> threshold;
	/* LCS计算重复率 */
	code.cal_D_LCS(code.a, code.b, lenA, lenB);
	code.convert(code.D, lenA, lenB, threshold);
	repeat_row = code.get_repeat_num(code.D, lenA, lenB);
	repeat_rate = code.get_repeat_rate(repeat_row, lenA, lenB);
	cout << "LCS-最大重复行数： " << repeat_row << endl;
	cout << "LCS-最大重复率： " << repeat_rate * 100 << "%" << endl;

	/* 编辑距离（LD）计算重复率 */
	code.cal_D_Cmpdistance(code.a, code.b, lenA, lenB);
	code.convert(code.D, lenA, lenB, threshold);
	repeat_row = code.get_repeat_num(code.D, lenA, lenB);
	repeat_rate = code.get_repeat_rate(repeat_row, lenA, lenB);
	cout << "LD-最大重复行数： " << repeat_row << endl;
	cout << "LD-最大重复率： " << repeat_rate * 100 << "%" << endl;

	/* 匈牙利算法计算重复率 */
	code.cal_D_Hungary(code.a, code.b, lenA, lenB);
	//code.print_matrix(code.D,lenA,lenB);
	code.convert(code.D, lenA, lenB, threshold);
	//code.print_matrix(code.D,lenA,lenB);
	repeat_row = code.get_repeat_num(code.D, lenA, lenB);
	repeat_rate = code.get_repeat_rate(repeat_row, lenA, lenB);
	cout << "Hungary-最大重复行数： " << repeat_row << endl;
	cout << "Hungary-最大重复率： " << repeat_rate * 100 << "%" << endl;

	return 0;
}


