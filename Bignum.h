#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <iostream>
#include <assert.h>
#include <string>
using namespace std;


#define MAX_INT64 9223372036854775807  
#define MIN_INT64 -9223372036854775808 


typedef long long INT64;

class BigData
{
public:
	BigData(INT64 data); 
	BigData(const char *_pdata);  
	BigData operator+(BigData& bigData);  
	BigData operator-(const BigData& bigData);  
	BigData operator*(const BigData& bigData);  
	BigData operator/(const BigData& bigData); 
	BigData operator%(const BigData& bigData);    
	friend std::ostream& operator<<(std::ostream& _cout, const BigData& bigData);  
	//friend std::istream& operator>>(std::istream& _cin, BigData bigData);  
	bool IsINT64Overflow()const; 
private:
	void INT64ToString();  
	std::string Add(std::string left, std::string right);  
	std::string Sub(std::string left, std::string right);  
	std::string Mul(std::string left, std::string right);  
	std::string Div(std::string left, std::string right);  
	bool IsLeftStrBig(char *pLeft, size_t LSize, char *pRight, size_t RSize);  
	char SubLoop(char *&pLeft, int& LSize, char *pRight, size_t RSize);
private:
	INT64 _value;
	std::string _strData;
};