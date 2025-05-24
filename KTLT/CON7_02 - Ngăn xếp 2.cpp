#include <bits/stdc++.h>
using namespace std;
int main() {
    stack<int> stk;
    int t;
    cin>>t;
    while (t>0) {
    	string s;
    	cin>>s;
    	t--;
        if (s == "PUSH") {
            int n;        
            cin >> n;
            stk.push(n);
        }
        else if (s == "POP") {
            if (!stk.empty()){
            	stk.pop();
			}
        }else if(s == "PRINT"){
        	if(!stk.empty()){
        		cout<<stk.top()<<endl;
			}else{
				cout<<"NONE"<<endl;
			}
		}
    
    }
    return 0;
}
