#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MOD=1e9+7;
ll biendoi(ll S,ll T){
	int step=0;
	while(T>S){
	if(T%2==0){
		T=T/2;
	}else{T=T+1;}
	step++;
}if(T<=S){
	step+=(S-T);
}
 return step;
}
int main(){
	int t;
	cin>> t;
	while(t--){
		ll S,T;
		cin>>S>>T;
		int res=biendoi(S,T);
		cout<<res<<endl;
		
	}
		return 0;
}