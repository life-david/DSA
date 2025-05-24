#include <bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin >> t;
	while(t--){
		string s;
		cin >> s;
		stack<string> st;
		for(int i = 0; i < s.size(); i++){
			if(isalnum(s[i])){ // nếu là chữ hoặc số
				st.push(string(1, s[i]));
			}
			else{ // là toán tử
				string op2 = st.top(); st.pop();
				string op1 = st.top(); st.pop();
				string tmp = "(" + op1 + s[i] + op2 + ")";
				st.push(tmp);
			}
		}
		cout << st.top() << endl;
	}
	return 0;
}
