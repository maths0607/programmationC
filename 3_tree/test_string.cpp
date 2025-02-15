#include <iostream>
#include <string>
using namespace std;
string leftTree(string chaine){
    int q=0 ;bool changed=0;
    int i;
    for (i=0;i<chaine.size();i++){
        if(chaine[i]=='(' ){
            q++;changed=1;
        }else{
            if(chaine[i]==')'){
                q--;changed=1;
            }
        }
        if(q==0 && changed ) break;
    }
    if(i==chaine.size()){
        int x=chaine.find_first_of(",");
        return chaine.substr(0,x-1);
    }
    return chaine.substr(0,i+1);

}
string rightTree(string chaine){
    int q=0 ;bool changed=0;
    int i;
    for (i=0;i<chaine.size();i++){
        cout<<i;
        if(chaine[i]=='(' ){
            q++;changed=1;
        }else{
            if(chaine[i]==')'){
                q--;changed=1;
            }
        }
        if(q==0 && changed ) break;
    }
    if(i==chaine.size()){
        int x=chaine.find_first_of(",");
        return chaine.substr(x+1,chaine.size()-x);
    }
    return chaine.substr(i+2,chaine.size()-i-1);

}

int main(){
    string chain = "3(1,.),4(5,6)),(3(1,.),4(5,6)";
    cout<<rightTree(chain)<<endl;
    return 0;
}