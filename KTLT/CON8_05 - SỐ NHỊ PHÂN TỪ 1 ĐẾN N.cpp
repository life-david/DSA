#include <bits/stdc++.h>
using namespace std;
int main() {
	int t;
	cin>>t;
	while(t--){
	queue<string>q;
	q.push("1");
	int n;
	cin>>n;
	while(n--){
		string s=q.front();
		q.pop();
		cout<<s<<" ";
		q.push(s+"0");
		q.push(s+"1");
	}
	cout<<endl;
	}
    return 0;
}
