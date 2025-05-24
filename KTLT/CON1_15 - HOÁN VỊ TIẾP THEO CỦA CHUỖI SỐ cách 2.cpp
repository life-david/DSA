#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    int t;
    cin >> t;
    while (t--) {
    	int stt;
    	cin>>stt;
    	int n;
    	string s;
    	cin>>s;
    	n=s.size();
    	int ok=1;
    	int vt=0;
    	for(int i=n-1;i>0;i--){
    		if(s[i]>s[i-1]){
    			vt=i-1;
    			ok=0;
    			break;
			}}
			if(ok==1){
				cout<<stt<<" "<<"BIGGEST"<<endl;
			}else{
				int k=0;
				for(int i=n-1;i>vt;i--){
					if(s[i]>s[vt]){
						k=i;
						break;
					}
				}
				swap(s[vt],s[k]);
				reverse(s.begin()+vt+1,s.end());
				cout<<stt<<" "<<s<<endl;
			}
    }
    return 0;
}