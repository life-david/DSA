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
		for(int i=0;i<n;i++){
		cin>>a[i];}
		vector<int>b=a;
		bool check=true;
		sort(b.begin(),b.end());
		for(int i=0;i<n/2;i++){
			int A1=a[i],A2=a[n-i-1];
			int B1=b[i],B2=b[n-i-1];
			if(A1>A2)swap(A1,A2);
			if(B1>B2)swap(B1,B2);
			if((A1!=B1)||(A2!=B2)){
				check=false;
				break;
			}
		}if(check==true){
			cout<<"Yes"<<endl;
		}else{
			cout<<"No"<<endl;
		}
	}
		return 0;
}