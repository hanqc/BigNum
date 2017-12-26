#define _CRT_SECURE_NO_WARNINGS 1
#include "Bignum.h"

BigData::BigData(INT64 data)  
: _value(data)  
, _strData("")  
{
	INT64ToString();  
}
BigData::BigData(const char *_pdata)  
{  
	assert(_pdata);  
	char symbol = _pdata[0];  
	char* pdata = (char*)_pdata;  
	if (symbol == '+' || symbol == '-')  
	{  
		pdata++;  
	}  
	else if (*pdata >= '0'&& *pdata <= '9')  
	{  
		symbol = '+';  
	}  
	else  
	{  
		_value = 0;  
		_strData = '0';  
		return;  
	}  
	while (*pdata == '0')  
	{  
		pdata++;  
	}  
	_strData.resize(strlen(pdata) + 1);  
	_value = 0;  
	_strData[0] = symbol;  
	int count = 1;  
	while (pdata)  
	{  
		if (*pdata >= '0' && *pdata <= '9')  
		{  
			_value = _value * 10 + *pdata - '0';  
			_strData[count++] = *pdata++;  
		}  
		else  
		{  
			break;  
		}  
	}  

	if ('-' == symbol)  
	{  
		_value = 0 - _value;  
	}  
} 
 BigData BigData:: operator+(BigData& bigData)
 {
  	if (!IsINT64Overflow() && !bigData.IsINT64Overflow())  
  	{
  		if (_strData[0] != bigData._strData[0])
  		{
  			return BigData(_value + bigData._value);
  		}
  		else
  		{
  			if ((_strData[0] == '+' && MAX_INT64 - _value >= bigData._value  
  				|| (_strData[0]) == '-' && MIN_INT64 - _value <= bigData._value))  
  			{  
  				return BigData(_value + bigData._value);  
  			}  
  		}
  	}
  	std::string tmp;  
  	if (_strData[0] == bigData._strData[0])  
  	{  
  		tmp = Add(_strData, bigData._strData);  
  	}  
  	else  
  	{  
  		tmp = Sub(_strData, bigData._strData);  
  	}  
  	return BigData(tmp.c_str());  
 }

void BigData::INT64ToString()
{
	char symbol = '+';
	INT64 tmp = _value;
	if (tmp < 0)
	{
		symbol = '-';
		tmp = 0 - tmp;
	}
	_strData.append(1,symbol);
	while (tmp)
	{
		_strData.append(1,tmp%10 + '0');
		tmp /= 10;
	}
	char* left = (char*)(_strData.c_str()+1);
	char* right = (char*)(_strData.c_str()+_strData.size()-1);
	while (left < right)
	{
		char tmp = *left;
		*left = *right;
		*right = tmp;
		*left++;
		*right--;
	}
}

bool BigData::IsINT64Overflow()const   
{  
	std::string tmp;  
	if ('+' == _strData[0])  
	{  
		tmp = "MAX_INT64";  
	}  
	else  
	{  
		tmp = "MIN_INT64";  
	}  
	if ((_strData.size() > tmp.size()) ||  
		((_strData.size() == tmp.size())&&(_strData > tmp)))  
	{  
		return true;  
	}  

	return false;  
}  
std::ostream& operator<<(std::ostream& _cout, const BigData& bigData)  
{  
	if (!bigData.IsINT64Overflow())
	{  
		_cout << bigData._value;  
	}  
	else  
	{  
		char* pData = (char*)bigData._strData.c_str();  
		if (pData[0] == '+')  
		{  
			pData++;  
		}  
		_cout << pData;  
	}  
	return _cout;  
} 
std::string BigData::Add(std::string left,std::string right) 
{
	int lsize = left.size();
	int rsize = right.size();
	char ch = left[0];  
	if (lsize < rsize)  
	{  
		std::swap(left,right);  
		std::swap(lsize,rsize);  
	}  
	std::string tmp;  
	tmp.resize(lsize + 1);  
	tmp[0] = ch;  
	char step = 0;  
	int n = 1;  
	while (n < lsize)  
	{  
		char ret = left[lsize - n] - '0' + step;  
		if (n < rsize)  
		{  
			ret += right[rsize - n] - '0';  
		}  
		tmp[lsize - n + 1] = (ret % 10 + '0');  
		step = ret / 10;  
		n++;  
	}  
	tmp[1] = step + '0';  

	return tmp;  
}
std::string BigData::Sub(std::string left, std::string right)  
{  
	int lsize = left.size();  
	int rsize = right.size();  
	char symbol = left[0];  
	if ((lsize < rsize) ||  
		(lsize == rsize && left < right))  
	{  
		std::swap(left, right);  
		std::swap(lsize, rsize);  
		if (symbol == '+')  
		{  
			symbol = '-';  
		}  
		else  
		{  
			symbol = '+';  
		}  
	}  
	std::string tmp;  
	tmp.resize(lsize);  
	tmp[0] = symbol;  
	int n = 1;  
	while (n < lsize)  
	{  
		char ret = left[lsize - n] - '0';  
		if (n < rsize)  
		{  
			ret -= right[rsize - n] - '0';  
		}  
		if (ret < 0)  
		{  
			left[lsize - n - 1] -= 1;  
			ret += 10;  
		}  
		tmp[lsize - n] = (ret + '0');  
		n++;  
	}  
	return tmp;  
}
BigData BigData::operator-(const BigData& bigData)  
{  
	if (!IsINT64Overflow() && !bigData.IsINT64Overflow())  
	{  
		if (_strData[0] == bigData._strData[0])  
		{  
			return BigData(_value - bigData._value);  
		}  
		else  
		{     
			if ((_strData[0] == '+' && MAX_INT64 + bigData._value >= _value)  
				|| (_strData[0] == '-' && (MIN_INT64 + bigData._value) <= _value))  
			{  
				return BigData(_value - bigData._value);  
			}  
		}  
	}  
	std::string tmp;  
	if (_strData[0] != bigData._strData[0])  
	{  
		tmp = Add(_strData, bigData._strData);  
	}  
	else  
	{  
		tmp = Sub(_strData, bigData._strData);  
	}  
	return BigData(tmp.c_str());  
}  

BigData BigData::operator*(const BigData& bigData)  
{  
	if (_value == 0 || bigData._value == 0)  
	{  
		return BigData(INT64(0));  
	}  
	if (!IsINT64Overflow() && !bigData.IsINT64Overflow())  
	{  
		if (_strData[0] == bigData._strData[0])  
		{  
			if ((_strData[0] == '+' && MAX_INT64 / _value >= bigData._value)  
				|| (_strData[0] == '-' && MAX_INT64 / _value <= bigData._value))  
			{  
				return BigData(_value * bigData._value);  
			}  
		}  
		else  
		{  
			if ((_strData[0] == '+' && MIN_INT64 / _value <= bigData._value)  
				|| (_strData[0] == '-' && MIN_INT64 / _value >= bigData._value))  
			{  
				return BigData(_value * bigData._value);  
			}  
		}  
	}  
	return BigData(Mul(_strData, bigData._strData).c_str());  
}  

std::string BigData::Mul(std::string left, std::string right)  
{  
	int lsize = left.size();  
	int rsize = right.size();  
	if (lsize > rsize)  
	{  
		swap(left, right);  
		swap(lsize, rsize);  
	}  
	char symbol = '+';  
	if (left[0] != right[0])  
	{  
		symbol = '-';  
	}  
	string tmp;  
	tmp.assign(lsize + rsize - 1, '0');  
	tmp[0] = symbol;  
	int datalen = tmp.size();  
	int ioffset = 0;  
	for (int lidx = 1; lidx < lsize; lidx++)  
	{  
		char cleft = left[lsize - lidx] - '0';  
		char step = 0;  
		if (cleft == 0)  
		{  
			ioffset++;  
			continue;  
		}  
		for (int ridx = 1; ridx < rsize; ridx++)  
		{  
			char ret = cleft*(right[rsize - ridx]-'0');  
			ret += step;  
			ret += (tmp[datalen - ioffset - ridx] - '0');  
			tmp[datalen - ioffset - ridx] = (ret % 10 + '0');  
			step = ret / 10;  
		}   
		tmp[datalen - ioffset - rsize] += step;  
		ioffset++;  
	}  
	return tmp;  
}  
BigData BigData::operator/(const BigData& bigData)  
{  
	if (bigData._value == 0)  
	{  
		assert("除数不能为0");  
		return BigData(INT64(0));  
	}  
	if (!IsINT64Overflow() && bigData.IsINT64Overflow())  
	{  
		return BigData(_value / bigData._value);  
	}  
	return BigData(Div(_strData, bigData._strData).c_str());  
}  

int idx = 0;

std::string BigData::Div(std::string left, std::string right)  
{  
	char lsize = left.size();  
	char rsize = right.size();  
	char symbol = '+';  
	if (left[0] != right[0])  
	{  
		symbol = '-';  
	}  
	if ((lsize < rsize) ||   
		(lsize == rsize && strcmp(left.c_str() + 1, right.c_str() + 1) < 0))  
	{  
		return "0";  
	}  
	else  
	{  
		if (right == "-1" || right == "+1")  
		{  
			left[0] = symbol;  
			return left;  
		}  
	}  
	string tmp;  
	tmp.append(1, symbol);  
	char *pleft = (char*)(left.c_str() + 1);  
	char *pright = (char*)(right.c_str() + 1);  
	int datalen = 1;  
	lsize -= 1;  
	for (idx = 0; idx < lsize;)  
	{  
		if (*pleft == '0')  
		{  
			tmp.append(1, '0');  
			pleft++;  
			idx++;  
			continue;  
		}  
		if (!IsLeftStrBig(pleft, datalen, pright, rsize - 1))  
		{  
			tmp.append(1, '0');  
			datalen++;  
			if (idx + datalen > lsize)  
			{  
				break;  
			}  
			continue;  
		}    
		else  
		{  
			tmp.append(1,SubLoop(pleft, datalen, pright ,rsize - 1));  
			datalen++;  
		}  
	}  
	return tmp;  
}

bool BigData::IsLeftStrBig(char *pLeft, size_t LSize, char *pRight, size_t RSize)  
{  
	assert(pLeft != NULL && pRight != NULL);  
	if ((LSize > RSize) ||(LSize == RSize && strncmp(pLeft,pRight,LSize) >= 0))  
	{  
		return true;  
	}  
	return false;  
}  

char BigData::SubLoop(char *&pLeft, int& LSize, char *pRight, size_t RSize)  
{  
	assert(pLeft != NULL && pRight != NULL);  
	char ret = '0';  
	while (true)  
	{  
		if (!IsLeftStrBig(pLeft, LSize, pRight, RSize))  
		{  
			break;  
		}  
		int ldatalen = LSize - 1;  
		int rdatalen = RSize - 1;  
		while (ldatalen >= 0 && rdatalen >= 0)  
		{  
			if (pLeft[ldatalen] < pRight[rdatalen])  
			{  
				pLeft[ldatalen - 1] -= 1;  
				pLeft[ldatalen] += 10;  
			}  
			pLeft[ldatalen] = pLeft[ldatalen] - pRight[rdatalen] + '0';  
			ldatalen--;  
			rdatalen--;  
		}  
		while ((*pLeft == '0') && (LSize > 0))  
		{  
			pLeft++;  
			LSize--;  
			idx++;  
		}  
		ret++;  
	}  
	return ret;  
} 