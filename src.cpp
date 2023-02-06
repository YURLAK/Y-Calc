#include <bits/stdc++.h>
using namespace std;
string tinp;//输入算式 
int tsize=0;
char inp[51];//正规的算式（string转char，否则无法进行运算） 
int num[51];int n=0;//存数字 
char calcan[5];//优先级
char calinp[51];int c=0;//输入符号
char calpd[5];//判断符号
int start=0,ans=0;
bool yes=false;
void welcome(){
	cout<<"Y-Calc v1.0,developed by YURLAK,2023.\nA simple calculate written in C++."<<endl;
}
 int suan(int left,int right,char fh){
	switch(fh){
		case '+':return (left+right);
		case '-':return (left-right);
		case '*':return (left*right);
		case '/':return (left/right);
		case '^':return pow(left,right);
	}
}
bool can(int i){
	if(calcan[calinp[i]]<calcan[calinp[i+1]]) return false;
	else return true;
}
int read(char end){
	int ans=0,ws=0,num=0; 
	while(isdigit(inp[end])){
		ws++;
		end--;
	}
	end+=ws;
	for(int j=0;j<ws;j++){
		ans+=(inp[end-j]-48)*pow(10,j);
	}
	return ans;
}
void run(){
	while(yes==false){
		if(!can(start)){
			start++;
			num[start+1]=suan(num[start],num[start+1],calinp[start]);
			num[start]=num[start-1];
			calinp[start]=calinp[start-1];
			run();
		}else{
			num[start+1]=suan(num[start],num[start+1],calinp[start]);
			if(start+1==c){
				cout<<"[RESULT]"<<num[start+1];
				exit(0);
			}
			start++;run();
		}
	}
}
bool check(){
	int tot=0;
	for(int i=0;i<=tsize;i++){
		if(inp[i]=='(') tot++;
		if(inp[i]==')') tot--;
	}
	if(tot==0) return true;
	else return false;
}
int main(){
	calcan['+']=calcan['-']=1;
	calcan['/']=calcan['*']=2;
	calcan['^']=3;
	//初始化优先级 
	welcome();
	printf("[INPUT]");
	getline(cin,tinp);//输入 
	tsize=tinp.size();
	strcpy(inp,tinp.data());//将string的输入复制到char输入数组 
	if(!check()){
		cout<<"WRONG!";//判断括号是否合法
		return 0;
	}
	for(int i=0;i<tsize;i++){
		if(!isdigit(inp[i])){
			num[n]=read(i-1);
			calinp[c]=inp[i];
			c++;
			n++;
		}
		if(i==tsize-1&&isdigit(inp[tsize-1])){
			num[n]=read(tsize-1);
			n++;
		} 
	}//将数和符号存进数组
	run();
}
