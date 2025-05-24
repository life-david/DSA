#include <bits/stdc++.h>
using namespace std;
int ut(char c){
	if(c=='^') return 3;
	if(c=='*'||c=='/')return 2;
	if(c=='+'||c=='-')return 1;
	return 0;
}
int main() {
	int t;
	cin>>t;
	while(t--){
		string s;
		cin>>s;
		stack<char>a;
		string kq="";
		for(int i=0;i<s.size();i++){
			char c=s[i];
			if(isalnum(c)){
				kq+=c;
			}
			else if(c=='('){                                   //them dau mo ngoac vao stack
				a.push(c);
			}else if(c==')'){
				while(!a.empty()&&a.top()!='('){         // neu la ngoac dong thi in trong stack ra cho den khi gap ngoac mo
					kq+=a.top();
					a.pop();
				}a.pop();                                //bo ngoac mo
			}else{
				while(!a.empty()&&ut(a.top())>=ut(c)){
					kq+=a.top();
					a.pop();
				}a.push(c);
			}}
			while(!a.empty()){
				kq+=a.top();
				a.pop();
			}
        cout << kq<< endl; 
		
	}
    return 0;
}
