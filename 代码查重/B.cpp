// Name        : Knapsack.cpp  

#include <iostream> 
#include"Knapsack.h"
#include<fstream>     
#include<cstdlib>
#include <string>  
using namespace std;

const char up = '|';
const char left = '-';
const char least = '\\';

int *w
int *c
int *value;     //value_array 
int *weight;    //The weight array  
int** output;   //outputs