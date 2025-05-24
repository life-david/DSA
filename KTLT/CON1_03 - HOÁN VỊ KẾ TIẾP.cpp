#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    int t;
    cin >> t;
    while (t--) {
    	int n;
    	cin>>n;
    	vector<int> a(n);
    	for(int i=0;i<n;i++){
    		cin>>a[i];
		}
		int vt=n-2;
		while(vt>0&&a[vt]>a[vt+1]){
			vt--;
		}
		if(vt>=0){
		int j=n-1;
		while (a[j] <= a[vt]) j--; 
        swap(a[vt], a[j]); 
		}
		reverse(a.begin() + vt + 1, a.end());
		for (int i = 0; i < n; i++)
            cout << a[i] << " ";
        cout << endl;
    }
    return 0;
}