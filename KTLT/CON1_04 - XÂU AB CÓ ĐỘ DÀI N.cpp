#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MOD=1e9+7;
void dequy(string current,int N){
	if(current.length()==N){
		cout<<current<<endl;
		return;
	}
	dequy(current+'A',N);
	dequy(current+'B',N);
}
int main(){
	int T;
	cin>> T;
	while(T--){
		int N;
		cin>>N;
		dequy("",N);
	}
		return 0;
}