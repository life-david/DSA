#include <bits/stdc++.h>
using namespace std;
#define ll long long
string timSNN(int S, int D){
	if(S>D*9){
		return "-1";
	}
	vector<int>a(D,0);
	for(int i=D-1;i>=0;i--){
		if(S>9){
			a[i]=9;
			S-=9;
		}else{
			a[i]=S;
			S=0;
		}
	}
	if(a[0]==0){
		for(int i=1;i<D;i++){
			if(a[i]>0){
				a[i]--;
				a[0]++;
				break;
			}
		}
	}
	string res = "";
    for (int i = 0; i < D; i++) {
        res += to_string(a[i]);
    }
    return res;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
    	int S,D;
    	cin>>S>>D;
    	string a=timSNN(S,D);
    	cout<<a<<endl;
    }
    return 0;
}