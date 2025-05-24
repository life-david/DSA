#include <bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin >> t;
	while(t--){
		int n;
		cin>>n;
		vector<int>a(n);
		for(int i=0;i<n;i++){
			cin>>a[i];
		}
		stack<vector<int>>res;
		while(!a.empty()){
			res.push(a);
			vector<int>t;
			for(int i=0;i<a.size()-1;i++){
			t.push_back(a[i]+a[i+1]);
		}
		a=t;
	  }
	  while(!res.empty()){
	  	cout<<"[";
	  	vector<int>dong=res.top();
	  	for(int i=0;i<dong.size();i++){
	  		cout<<dong[i];
	  		if(i!=dong.size()-1){
	  			cout<<" ";
			  }
		  }
		  cout<<"]"<<" ";
		  res.pop();
	  }
	  cout<<endl;
	}	
	return 0;
}
