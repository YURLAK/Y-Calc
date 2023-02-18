#include<iostream>
#include<stack>
#include<math.h> 
#include<cstdlib> 
using namespace std;
double inStack();   //核心函数，将操作符有序的入栈计算， 最后返回结果
void calculate(stack<char>& Ope, stack<double>& Num);  //用来计算加减乘除, 结果放在数字栈顶
void factorial(stack<double>& Num);   //用来计算阶乘
int priority(char ope_);   //用来计算操作符的优先级
bool done=false;char choice;double result;
int main(){
	cout<<"Y-Calc v2.0,developed by YURLAK,2023.\nA simple calculate written in C++.\nPress Ctrl+C to exit the program."<<endl;
	while(true){
		cout<<"[INPUT]";
		result=inStack();
		cout<<"[RESULT]"<<result<<endl;
	}
	return 0;
}
double inStack() {
	stack<char> Ope;
	stack<double> Num;
	char ope_;
	double num_;
	while (1) {
		if(cin.peek()>='0'&&cin.peek()<='9'){  //判断下一个是否是数字
			cin>>num_;
			Num.push(num_);   //数字直接入栈
		}else{
			cin>>ope_;
			if (ope_ == '=') {
				while (!Ope.empty()) calculate(Ope, Num); //如果符号栈不空，就一直计算
				return Num.top();  //如果是等号且符号栈顶为空，就返回数字栈顶元素
			}
			else if (ope_ == '!') factorial(Num);  //如果是！就阶乘
			else if (ope_ == '(' || Ope.empty()) Ope.push(ope_);    //如果符号是左括号或符号栈为空直接压入
			else if (ope_ == ')') {  //如果是右括号
				while (Ope.top() != '(') calculate(Ope, Num); //一直计算完括号里的
				Ope.pop();  //左括号出栈
			}
			else if (priority(Ope.top()) >= priority(ope_)) {  //如果栈顶符号的优先级大于等于当前
				while (Ope.top() != '(') {
					calculate(Ope, Num);   //计算结果压入数字栈,取出当前栈顶
					if (Ope.empty() || priority(Ope.top()) < priority(ope_)) break;  //当符号栈为空或者待压入的符号优先级高就跳出
				}
				Ope.push(ope_);  //压入当前符号
			}
			else Ope.push(ope_);  //否则就压入符号栈
		}
	}
}
void calculate(stack<char>& Ope, stack<double>& Num) {
	double a,b;
	if (Ope.top() == '-') {
		a = Num.top(); Num.pop();
		Ope.pop();   //取出负号
		if (!Num.empty()) {
			if (Ope.empty()|| Num.size() == Ope.size())
				Ope.push('+');  //如果前面还有数字，就压入+，即变成加负值
		}
		Num.push(-a);  //压入负值
	}
	else {
		a = Num.top(); Num.pop();
		b = Num.top(); Num.pop();
		if (Ope.top() == '+') Num.push(b + a);
		else if (Ope.top() == '*') Num.push(b * a);
		else if (Ope.top() == '/') Num.push(b / a);
		else if (Ope.top() == '^') Num.push(pow(b, a));
		Ope.pop();
	}
}
void factorial(stack<double>& Num) {
	int a = static_cast<int>(Num.top());Num.pop();
	int result = 1;
	for (int i = 1; i <= a; i++) result *= i;
	Num.push(static_cast<double>(result));
}
int priority(char ope_) {
	if (ope_ == '(') return 0;
	else if (ope_ == '+' || ope_ == '-') return 1;
	else if (ope_ == '*' || ope_ == '/') return 2;
	else if (ope_ == '^') return 3;
}

