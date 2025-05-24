#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
    	int n,k;
    	cin>>n>>k;
    	int xh=0;
    	int a[n]={};
    	for(int i=0;i<n;i++){
    		cin>>a[i];
		}
    	for(int i=0;i<n;i++){
    		if(a[i]==k){
			cout<<i+1<<endl;
			xh++;
		}}
		if(xh==0){
			cout<<"NO"<<endl;
		}
    	
    }
}