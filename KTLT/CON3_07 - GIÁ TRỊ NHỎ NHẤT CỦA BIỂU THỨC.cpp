#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MOD=1e9+7;
int main(){
	int t;
	cin>> t;
	while(t--){
	int n;
	cin>>n;
	vector<int>a(n);
	vector<int>b(n);
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	for(int i=0;i<n;i++){
		cin>>b[i];
	}
	sort(a.begin(),a.end());
	sort(b.begin(),b.end(),greater<int>());
	ll res=0;
	for(int i=0;i<n;i++){
		res+=(a[i]*b[i]);
	}
	cout<<res<<endl;
	}
		return 0;
}