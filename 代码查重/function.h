#pragma once
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <algorithm>
using namespace std;

#define M 500


class Code {
public:
	string *a;
	string *b;
	double **D;
	bool isNote;
	Code() {
		isNote = false;
		a = new string[M];
		b = new string[M];
		D = new double *[M];
		for (int i = 0; i < M; i++)
			D[i] = new double[M];
		for (int i = 0; i < M; i++)
			for (int j = 0; j < M; j++)
				D[i][j] = 0;
	}
	// 将文件内容读取到字符串中
	int string_init(string filename, string *str) {
		int i = 0;
		string s;
		ifstream infile; 
		infile.open(filename.data());
		assert(infile.is_open());
		while (getline(infile, s)) {
			//if(trim(s) && !s.empty())
				//if(!isNote)
					str[i++] = s;
		}
		infile.close();
		return i;
	}

	// 打印字符串数组
	void print_string(string *str, int len) {
		for (int i = 0; i < len; i++)
			cout << str[i] << endl;
	}
	
	// 去除空格和注释
	bool trim(string &s) {
		//bool flag = false;
		if (!s.empty()) {
			size_t index = 0;
			while ((index = s.find(' ')) != string::npos) {
				s.erase(index, 1);
			}
			if ((index = s.find("//")) != string::npos) {
				s.erase(index);
				return true;
			}
			
			if ((index = s.find("/*")) != string::npos) {
				isNote = true;
				return false;
			}
			if ((index = s.find("*/")) != string::npos) {
				isNote = false;
				return false;
			}
			return true;
		}
		return false;
	}

	// LCS
	double LCS(string x, string y) {
		int m = x.length() + 1;
		int n = y.length() + 1;
		//cout << m << " " << n << endl;
		int i, j;
		int **c;
		
		c = new int *[m];
		for (i = 0; i < m; i++)
			c[i] = new int[n];
		for (i = 0; i < m; i++)
			c[i][0] = 0;
		for (j = 0; j < n; j++)
			c[0][j] = 0;
		for (i = 1; i < m; i++) {
			for (j = 1; j < n; j++) {
				if (x[i-1] == y[j-1]) {
					c[i][j] = c[i - 1][j - 1] + 1;
				} else {
					c[i][j] = max(c[i - 1][j], c[i][j - 1]);
				}
			}
		}
		double rate = c[m-1][n-1] * 1.0 / min(m-1, n-1);
		for (i = 0; i < m; i++)
			delete[] c[i];
		delete[] c;
		return rate;	
	}

	// 编辑距离
	double compare_distance(string x, string y) {
		int i, j;
		int temp;
		int m = x.length();
		int n = y.length();
		int **c;
		c = new int*[m + 1];
		for (i = 0; i < m + 1; i++)
			c[i] = new int[n + 1];
		for (i = 0; i <= m; i++)
			c[i][0] = i;
		for (j = 0; j <= n; j++)
			c[0][j] = j;
		for (i = 1; i <= m; i++) {
			for (j = 1; j <= n; j++) {
				if (x[i - 1] == y[j - 1]) {
					temp = 0;
				} else {
					temp = 1;
				}
				c[i][j] = min(c[i - 1][j] + 1, c[i][j - 1] + 1);
				c[i][j] = min(c[i][j], c[i - 1][j - 1] + temp);
			}
		}
		double rate = (max(m, n) - c[m][n]) * 1.0 / max(m, n);
		for (i = 0; i <= m; i++)
			delete[] c[i];
		delete[] c;
		return rate;
	}

	// 转换
	void convert(double **D, int lenA, int lenB, double threshold) {
		//print_matrix(D, lenA, lenB);
		for (int i = 0; i < lenA; i++) {
			for (int j = 0; j < lenB; j++) {
				if (D[i][j] >= threshold) {
					D[i][j] = 1;
				} else {
					D[i][j] = 0;
				}
			}
		}
		//print_matrix(D, lenA, lenB);
	}

	// 计算D矩阵-LCS
	void cal_D_LCS(string *a, string *b, int lenA, int lenB) {
		for (int i = 0; i < lenA; i++) {
			for (int j = 0; j < lenB; j++) {
				D[i][j] = LCS(a[i], b[j]);
			}
		}
	}

	// 计算D矩阵-编辑距离
	void cal_D_Cmpdistance(string *a, string *b, int lenA, int lenB) {
		for (int i = 0; i < lenA; i++) {
			for (int j = 0; j < lenB; j++) {
				D[i][j] = compare_distance(a[i], b[j]);
			}
		}
	}

	// 计算D矩阵-匈牙利算法
	void cal_D_Hungary(string *a, string *b, int lenA, int lenB) {
		for (int i = 0; i < lenA; i++) {
			for (int j = 0; j < lenB; j++) {
				D[i][j] = Hungary(a[i], b[j]);
			}
		}
	}

	// 匈牙利
	bool find(string a, string b, int *btmp, int *used, int x, int n) {
		int j;
		for (j = 0; j < n; j++) {
			if (a[x] == b[j] && used[j] == 0) {
				used[j] = 1;
				if (btmp[j] == 0 || find(a,b,btmp,used,btmp[j],n)) {
					btmp[j] = x;
					return true;
				}
			}
		}
		return false;
	}
	double Hungary(string a, string b) {
		int i;
		int sum = 0;
		int m = a.length();
		int n = b.length();
		int *used = new int[n];
		int *btmp = new int[n];
		for (i = 0; i < n; i++) {
			btmp[i] = 0;
		}
		for (i = 0; i < m; i++) {
			for (int k = 0; k < n; k++)
				used[k] = 0;
			if (find(a, b, btmp, used, i, n))
				sum++;
		}
		return sum * 1.0 / min(m, n);
	}

	// 打印矩阵
	void print_matrix(double **D, int lenA, int lenB) {
		for (int i = 0; i < lenA; i++) {
			for (int j = 0; j < lenB; j++) {
				
				cout << D[i][j] << "\t";
				/*if (i != 2)
					cout << "\t";*/
				//printf("%.3lf ", D[i][j]);
			}
			cout << endl;
		}
	}

	// 求重复行数
	int get_repeat_num(double **D, int lenA, int lenB) {
		int i, j;
		int **c;
		c = new int*[lenA + 1];
		for (i = 0; i < lenA + 1; i++) {
			c[i] = new int[lenB + 1];
			c[i][0] = 0;
		}
		for (i = 0; i < lenB + 1; i++) {
			c[0][i] = 0;
		}

		for (i = 1; i < lenA + 1; i++) {
			for (j = 1; j < lenB + 1; j++) {
				if (D[i - 1][j - 1] == 1) {
					c[i][j] = c[i - 1][j - 1] + 1;
				} else {
					c[i][j] = max(c[i - 1][j], c[i][j - 1]);
				}
			}
		}
		return c[lenA][lenB];
	}

	// 求重复率
	double get_repeat_rate(int repeat_row, int lenA, int lenB) {
		return repeat_row * 1.0 / min(lenA, lenB);
	}
};