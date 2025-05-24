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
		ll s1=0, s2=0;
		for(int i=0;i<n;i++){
			cin>>a[i];
		}
		sort(a.begin(),a.end());
		for(int i=0;i<n;i+=2){
			if(a[i]==0){
				continue;
			}
			s1*=10;
			s1+=a[i];
		}
		for(int i=1;i<n;i+=2){
			if(a[i]==0){
				continue;
			}
			s2*=10;
			s2+=a[i];
	}
	cout<<s1+s2<<endl;
}}