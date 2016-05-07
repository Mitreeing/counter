// counter2.cpp : Defines the entry point for the console application.
// ʵ�ּ�������+,- * / С��

//#include "stdafx.h"
#define MAXSIZE 100
#define END '\n'
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "math.h"

char ops[MAXSIZE];   //�����ջ
int  ops_top;        //�����ջ����ʶ
double ovs[MAXSIZE];  //������ջ
int  ovs_top;         //������ջ����ʶ

void push_ops(char x); //�������ջ
void push_ovs(double x); //��������ջ
char pop_ops(); //�������ջ
double pop_ovs();//��������ջ

char gettop_ops();  //ȡ�������ջ��Ԫ��
double gettop_ovs();  //ȡ��������ջ��Ԫ��
void inistack_ops();  //��ʼ�������ջ
void inistack_ovs(); //��ʼ��������ջ
char Precede(char t1,char t2);  //�ж�t1��t2�����ȼ���
int char_In(char c); //�ж�c�Ƿ�Ϊ�����
double Operate(double a,char theta,double b); //�Գ�ջ������������
double  EvaluateExpression( );//ʹ����������㷨����������ʾʽ��ֵ
//ops[]Ϊ�����ջ��ovs[]Ϊ������ջ
char input_h='\n';//����ȫ�ֱ��������ڻ������롾+�� 

int main(int argc, char* argv[]) {
	printf("�������������ʽ���Իس�����\n");
	printf("%f\n",EvaluateExpression( ));
	getchar();
}

void push_ops(char x) { //�������ջ
	if(ops_top==MAXSIZE-1) {
		printf("�����ջ����������\n");
		exit(1);
	} else

	{
		ops_top++;
		ops[ops_top]=x;
	}

}


void push_ovs(double x) { //��������ջ
	if(ovs_top==MAXSIZE-1) {
		printf("������ջ����������\n");
		exit(1);
	} else {
		ovs_top++;
		ovs[ovs_top]=x;
	}
}


char pop_ops() { //�������ջ
	char y;
	if(ops_top==-1) {
		printf("�����ջ�գ�����\n");
		exit(1);
	} else {
		y=ops[ops_top];
		ops_top--;
	}
	return y;
}


double pop_ovs() { //��������ջ
	double y;
	if(ovs_top==-1) {
		printf("������ջ�գ�����\n");
		exit(1);
	} else {
		y=ovs[ovs_top];
		ovs_top--;
	}
	return y;
}


char gettop_ops() { //ȡ�������ջ��Ԫ��
	if (ops_top!=-1)
		return ops[ops_top];
	else {
		printf("ȡ��ʱ�����ջ�ѿ�\n");
		exit(1);
	}
}




double gettop_ovs() { //ȡ��������ջ��Ԫ��
	if (ovs_top!=-1)
		return ovs[ovs_top];
	else {
		printf("ȡ��ʱ������ջ�ѿ�\n");
		exit(1);
	}
}


void inistack_ops() { //��ʼ�������ջ
	ops_top=-1;
}

void inistack_ovs() { //��ʼ��������ջ
	ovs_top=-1;
}


char Precede(char t1,char t2) { //�ж�t1��t2�����ȼ���
	char f;
	switch(t2) {
		case '+':
		case '-':
			if (t1=='('||t1==END)
				f='<';
			else
				f='>';
			break;
		case '*':
		case '/':
			if (t1=='*'||t1=='/'||t1==')')
				f='>';
			else f='<';
			break;
		case '(':
			if (t1==')') {
				printf("�����error1\n");
				exit(1);
			} else
				f='<';
			break;
		case ')':
			switch(t1) {
				case '(':
					f='=';
					break;
				case END:
					printf("���������2\n");
					exit(1);
				default:
					f='>';
			}
			break;
		case END:
			switch(t1) {
				case END:
					f='=';
					break;
				case '(':
					printf("���������3\n");
					exit(1);
				default:
					f='>';
			}
	}
	return f;
}

int char_In(char c) { //�ж�c�Ƿ�Ϊ�����
	switch(c) {
		case '+':
		case '*':
		case '/':
		case '(':
		case ')':
		case END:
			return 1;
		case '-':
			if(char_In(input_h)||input_h=='\n') {//���ڼ����һ�������Ƿ�Ϊ��������+�� 
				push_ovs(0);
			}
			return 1;
		default :
			return 0;
	}
}



double Operate(double a,char theta,double b) { //�Գ�ջ������������
	double c;
	switch(theta) { //thetaΪ�����
		case '+':
			c=a+b; //���0-9��ASCII��
			break;
		case '-':
			c=a-b;
			break;
		case '*':
			c=a*b;
			break;
		case '/':
			c=a/b;
	}
	return c;
}

double EvaluateExpression( ) {
//ʹ����������㷨����������ʾʽ��ֵ
//ops[]Ϊ�����ջ��ovs[]Ϊ������ջ
	int cache_Len=0,i,j,flag=0,temp1=0,temp2,temp3;
	double a,b,curnum;
	char stack_x,theta,input_c,buff[MAXSIZE];
	inistack_ops();  //��ʼ�������ջ
	push_ops(END);   //ʹ��������ջ
	inistack_ovs(); //��ʼ��������ջ
	input_c=getchar();
	stack_x=gettop_ops();
	while(input_c!=END||stack_x!=END) { //�жϼ����Ƿ����
		if (char_In(input_c)) { //��������ַ���7�������֮һ
			input_h=input_c;//������һ�����롾+��
			for(i=0;i<flag;i++){
				buff[i]='\0';
			}
			flag=0;//��־�ع� 
			if(temp1){
				push_ovs(curnum);
			}
			temp1=0;
			switch (Precede(stack_x,input_c)) {
				case '<':
					push_ops(input_c); //��ջ��(x)���ȼ�<�����������ջ
					input_c=getchar();
					break;
				case '=':
					stack_x=pop_ops();//������ջ���������Ž�����һ���ַ�
					input_c=getchar();
					break;
				case '>':
					theta=pop_ops();
					b=pop_ovs();
					a=pop_ovs();
					push_ovs(Operate(a,theta,b));
					break;
			}

		} else if(input_c>='0'&&input_c<='9') { //input_c�ǲ�����
			input_h=input_c;//������һ�����롾+�� 
//			input_c=input_c-'0';
			flag++;
			temp1++;
				buff[flag-1]=input_c;
			curnum=(double)atof(buff);	
			input_c=getchar();
		} else {
			printf("�Ƿ��ַ�\n");
			exit(1);
		}
		stack_x=gettop_ops();
	}
	return(gettop_ovs());
}
