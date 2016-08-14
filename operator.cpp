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
	bool point = false; //�ж��Ƿ���С����
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
//ִ�мӼ��˳�����
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
	//����Ӧ���ҳ�����д������
	double num[MAX_BUF] = {0};	//������������
	char op[MAX_BUF] = {NULL}; //�������ǼӼ��˳�
	
	int nump = 0 ; //������ָ�����λ������
	int opp = 0;
	char tmp[MAX_BUF] = {0};
	int tmpSize = 0; 
	int bracketNum = 0;
	/*cout<<buf<<":nump = "<<nump<<",opp="<<opp<<endl;*/

	int num_muldiv = 0; //�˳�������
	int num_addsub = 0; //�Ӽ������� 
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
			num[nump++] = Calculator(buf + tmp + 1,i- tmp - 1);//����-2���Ǽ�ȥ��������λ
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
	//����������Ͼ�ȫ�������ˡ����ִ浽num�������棬�������Ŵ浽op��������
	/*cout<<"num[i]"<<endl;
	for(int i = 0;i < nump;i++)
		cout<<num[i]<<endl;
	cout<<"opp[i]"<<endl;
	for(int i = 0;i < opp;i++)
		cout<<op[i]<<endl;*/
	//����˳�
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
	//����Ӽ�

	for(int i = 0;i< opp;i++)
	{
		num[i+1] = Computing(num[i],num[i+1],op[i]);
	}

	return num[opp];
}
int main()
{

	char buf[MAX_BUF] = {0};
	//char buf[16] = "16.5+3*(3+12)/3"; //15λ ����һλ��
	cin>>buf;  
	int strlength = strlen(buf);
	double ret =  Calculator(buf,strlength);
	//cout<<ret<<endl;
	//Ҫ��ʽ������λС��
	printf("%.2lf\n",ret);

	system("pause");
	return 0;
}