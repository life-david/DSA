#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
    int Max=0;
    int a[30]={};
    for(int i=0;i<s.size();i++){
        a[s[i]-'a']++;
    }
    for(int i=0;i<30;i++){
         Max=max(Max,a[i]);
    }
    if(Max<=(s.size()+1)/2){
        cout<<"1";
    }else{
        cout<<"-1";
    }

    }
}