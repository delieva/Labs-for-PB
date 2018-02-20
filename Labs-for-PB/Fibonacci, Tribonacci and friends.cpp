//
// Created by Александра Делиева on 20.02.18.
//
using namespace std;
vector<int> xbonacci(vector<int> signature, int n)
{
    // Your code here
    if(n >= signature.size()){
        vector<int> vct(n);
        for(int k = 0; k < signature.size(); k++){
            vct[k] = signature[k];
        }
        for(int i = signature.size(); i < vct.size(); i++){
            vct[i] = 0;
            for(int m = signature.size(); m > 0; m--){
                vct[i] += vct[i - m];
            }
        }
        return vct;
    }
    else{
        vector<int> vct(n);
        for(int k = 0; k < n; k++){
            vct[k] = signature[k];
        }
        return vct;
    }
}
