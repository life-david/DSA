#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>> T;
	while(T--){
	int N;
	cin>>N;
	queue<string> q;
	q.push("9");
	while (!q.empty()){
		string ht=q.front();
		q.pop();
		long long sht=stoll(ht);// chuyen doi kdl sang long long
		if(sht%N==0){
			cout<<sht<<endl;
			break;
		}else{
			q.push(ht+'0');
			q.push(ht+'9');
		}	
	}
}}