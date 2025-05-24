#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MOD=1e9+7;
int main(){
	int t;
	cin>> t;
	while(t--){
		int n,k;
		cin>>n>>k;
		vector<int>A(n);
		for(int i=0;i<n;i++){
			cin>>A[i];
		}
		sort(A.begin(),A.end());
		vector<int>b=A;
		b.resize(k);
		vector<int>c=A;
		sort(C.begin(),C.end(),greater<int>());
		c.resize(n-k);
		int tongb=0,tongc=0;
		for(int i=0;i<b.size();i++){
			tongb+=b[i];
		}
		for(int i=0;i<c.size();i++){
			tongc+=c[i];
		}
		if(tongc> tongb){
			cout<<tongc-tongb<<endl;
		}else{
			cout<<tongb- tongc<<endl;
		}
	
		}
return 0;
}