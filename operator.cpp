#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <string.h>
using namespace std;
#define MAX_BUF 1000
double CharNumToDoule(char *num,int length)
{
	//num = "15.4";
	bool point = false; //判断是否有小数点
	double ret = 0;
	for(int i = 0;i < length;i++)
	{
		if(num[i] == '.')
		{
			point = true;
		}
		else
		{
			if(!point)
				ret = ret * 10 + (int)(num[i] - 0x30);
			else
				ret = ret + 0.1 * (int)(num[i] - 0x30);
		}
	}
	return ret;
}
//执行加减乘除操作
double Computing(double a,double b,char op) 
{
	double ret = 0;
	if(op == '*')
	{
		ret = a * b;
	}
	else if(op == '/')
	{
		ret = a / b;
	}
	else if(op == '+')
	{
		ret = a + b;
	}
	else if(op == '-')
	{
		ret = a - b;
	}
	return ret;
}

double Calculator(char *buf,int length)
{
	//首先应该找出数字写入数组
	double num[MAX_BUF] = {0};	//这里存的是数据
	char op[MAX_BUF] = {NULL}; //这里存的是加减乘除
	
	int nump = 0 ; //这两个指向最高位置数组
	int opp = 0;
	char tmp[MAX_BUF] = {0};
	int tmpSize = 0; 
	int bracketNum = 0;
	/*cout<<buf<<":nump = "<<nump<<",opp="<<opp<<endl;*/

	int num_muldiv = 0; //乘除法数量
	int num_addsub = 0; //加减法数量 
	//char bracket[MAX_BUF/2] = {NULL};
	for(int i = 0;i < length;i++)
	{
		if(buf[i] == '+' ||buf[i] == '-')
		{
			op[opp++] = buf[i];
			
			num_addsub++;
			if(tmpSize != 0)
			{
				num[nump++] = CharNumToDoule(tmp,tmpSize);
				tmpSize = 0;
			}

		}
		else if(buf[i] == '*' ||buf[i] == '/')
		{			
			op[opp++] = buf[i];
			num_muldiv++;
			if(tmpSize != 0)
			{
				num[nump++] = CharNumToDoule(tmp,tmpSize);
				tmpSize = 0;
			}
		}
		else if(buf[i] == '(')
		{
			int tmp = i++; 
			bracketNum = 1;
			while(1)
			{
				if(buf[i] == '(')
					bracketNum++;
				else if(buf[i] == ')')
					bracketNum--;
				if(bracketNum == 0)
					break;
				i++;
			}
			//memcpy( bracket,buf + tmp + 1,i- tmp - 1);
			num[nump++] = Calculator(buf + tmp + 1,i- tmp - 1);//这里-2就是减去两个括号位
		}
		else
		{
			tmp[tmpSize++] = buf[i];
		}
	}
	if(tmpSize != 0)
	{
		num[nump++] = CharNumToDoule(tmp,tmpSize);
	}
	//到这里基本上就全部找完了。数字存到num数组里面，操作符号存到op数组里面
	/*cout<<"num[i]"<<endl;
	for(int i = 0;i < nump;i++)
		cout<<num[i]<<endl;
	cout<<"opp[i]"<<endl;
	for(int i = 0;i < opp;i++)
		cout<<op[i]<<endl;*/
	//计算乘除
	bool calculate;
	while(num_muldiv != 0)
	{
		calculate = false;
		for(int i = 0;i< opp;i++)
		{

			if((op[i] == '*' || op[i] == '/') && calculate == false)
			{
				num[i+1] = Computing(num[i], num[i+1], op[i]);
				calculate =true;
			}
			if(calculate)
			{
				num[i] = num[i+1];
				op[i] = op[i+1];
			}
			
		}
		num_muldiv--;
		opp--;
	}
	//计算加减

	for(int i = 0;i< opp;i++)
	{
		num[i+1] = Computing(num[i],num[i+1],op[i]);
	}

	return num[opp];
}
int main()
{

	char buf[MAX_BUF] = {0};
	//char buf[16] = "16.5+3*(3+12)/3"; //15位 还有一位是
	cin>>buf;  
	int strlength = strlen(buf);
	double ret =  Calculator(buf,strlength);
	//cout<<ret<<endl;
	//要格式化成两位小数
	printf("%.2lf\n",ret);

	system("pause");
	return 0;
}