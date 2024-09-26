#include "../bits/stdc++.h"
using namespace std;

class TrieNode{
    public:
    bool isTerminal;
    TrieNode* child[26];
    
    TrieNode(){
        this->isTerminal= false;
        for( int i=0; i<26; i++){
            this->child[i]= NULL;
        }
    }
 
};

void insert(string s, TrieNode* dummy){
    TrieNode* root= dummy;

    for( int i=0; i<s.length(); i++){
        int ind= s[i]-'a';
        if( root->child[ind] ){
            root= root->child[ind];
        } 
        else{
            TrieNode* children= new TrieNode();
            root->child[ind]= children;
            root= children;
        }
    }
    root->isTerminal = true;  // Mark the last node as terminal
}

void printSugg(TrieNode* curr, vector<string> &temp, string& prefix){
    if( curr->isTerminal){
        temp.push_back(prefix);
    }
    
    for( char ch='a'; ch<='z'; ch++){
        if( curr->child[ch-'a'] != NULL){
            prefix.push_back( ch);
            printSugg(curr->child[ch-'a'],temp,prefix);
            prefix.pop_back();
        }
    }
}

 void search( string s, vector<vector<string> >&ans,TrieNode* root){

    string prefix="";
    TrieNode* prev= root;
    
    for( int i=0; i<s.length(); i++){
        prefix+= s[i];
        char lastch= s[i];
        
        if( prev->child[lastch-'a'] == NULL){
            while (i < s.length()) {
                vector<string> v(1,"0");
                ans.push_back(v);
                i++;
            }
            return;
        }
        
        TrieNode* curr= prev->child[lastch-'a'];
        vector<string> temp;
        printSugg(curr, temp,prefix);
        ans.push_back(temp);
        prev= curr;
    }
}

vector<vector<string> > displaySuggestions(int n, string allWords[], string quer)
{
    TrieNode* root= new TrieNode();
    for( int i=0; i<n; i++){
        insert(allWords[i],root);
    }
        
    vector<vector<string> >ans;
    search(quer,ans,root);
    
    return ans;
}



int main(){
    int n; 
    cout<<"Enter the size of your search space: ";
    cin>>n;

    string availWords[n], query;
    cout<<"Enter your search space in lowercase: "<<endl;
    for( int i=0; i<n; i++){
        cin>> availWords[i];
    }
    cout<<"Enter the query whose letter wise suggestions you wanna see: ";
    cin>>query;

    vector<vector<string> > ans= displaySuggestions(n,availWords,query);
    cout<<"Printing suggestions from the provided search space"<<endl;
    for( int i=0; i<ans.size(); i++){
        cout<<query[i]<<"->";
        for( int j=0; j<ans[i].size(); j++){
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }


    return 0;
}