#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    int t;
    cin >> t;
    queue<int>a;
    while (t--) {
    	string s;
    	cin>>s;
    	if(s=="PUSH"){
    		int x;
    		cin>>x;
    		a.push(x);
		}else if(s=="PRINTFRONT"){
			if(a.size()>0){
				cout<<a.front()<<endl;
			}else{
				cout<<"NONE"<<endl;
			}
		}else if(s=="POP"&&a.size()>0){
			a.pop();
		}
    }
    return 0;
}