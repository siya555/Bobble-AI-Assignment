#include<bits/stdc++.h>
#include<fstream>
#include<iostream>
using namespace std; 
class TrieNode
{
    public:
    TrieNode *children[256];
    bool isword;
    int freq;
    TrieNode(){
        for(int i = 0; i<256; i++)
        children[i] = NULL;
        isword = false;
        freq = 0;
    }
};
class TrieNode *root = new TrieNode();
  
string serialize(TrieNode* root) {
        string result;
        if(!root)
            return result;
        result += "<"; // it tells new level has started
        for(int c = 0; c < 256 ; c++){
            if(root->children[c] != NULL){
                char x = c;
                result += x;
                string f = to_string(0);
                if(root->children[c]->isword)
                {
                        f = to_string(root->children[c]->freq);
                }
                result+=f;
                result += serialize(root->children[c]);
            }
        }
        result += ">"; // level has serialized
        return result;
    }
 TrieNode *getnode()
    {
        TrieNode *temp = new TrieNode();
        return temp;
    }
bool search(string word) {
        TrieNode *temp = root;
        for(int i=0;i<word.size();i++)
        {
            int index = word[i];
            if(temp->children[index] == NULL)
                return false;
            temp= temp->children[index];
        }
        return temp!=NULL && temp->isword==true;
    }
    
void insert(string word, int freq)
{
    TrieNode *temp = root;
        for(int i=0;i<word.size();i++)
        {
            int index = word[i];
            if(temp->children[index] == NULL)
                temp->children[index] = getnode();
             temp = temp->children[index];
        }
        temp->isword = true;
        temp->freq = freq;
}
pair<bool,int>  abc(string data, string word, int index)
{

    if(word.size() == index) {

        int freq = 0;
        int i = 0;
        while(i < data.size() && (data[i] >='0' && data[i]<='9' ) )
        freq = freq * 10 + (data[i++] -'0');

        return make_pair(true, freq);
        
    }
    
    if(data.size() == 0)
    return make_pair(false, -1);
    int i = 0;
    if(data[0] == '<')
    i++;
    else
    {
        while(i < data.size() && (data[i] >='0' && data[i] <= '9') )
        i++;
        i++;
    }
    
    while( i <data.size() && data[i] != word[index])
    {
       
       
        int left = 0;
        int right = 0;
        if(data[i] == '<') left++;
        else if(data[i] == '>') right++;
        i++;
        while( i < data.size() && left != right)
        {
              if(data[i] == '<') left++;
            else if(data[i] == '>') right++;
            i++;
        }
    }
    if(i >= data.size()) return make_pair(false, -1);
    return abc(data.substr(i + 1) , word, index+1);
}
int main(int argc, char **argv) 
{ 
    fstream finput;
    finput.open(argv[1] ,ios::in);
    string word ;
   
    while (finput) {
        string current, freq;
        int i = 0;
        getline(finput,word);
        while(word[i] != ',') {
            current += word[i];
            ++i;
        }
        ++i;
        while(word[i]) {
            freq += word[i];
            ++i;
        }
        insert(current, stoi(freq));
        cout<<current<<" "<<freq<<endl ;
       word.clear();
    }
   /* int n;
    cin>>n;
    while(n--)
    {
        string s;
        int freq;
        cin>>s>>freq;
        insert(s, freq);
    }*/
    string data = serialize(root);
    //cout<<data<<endl;
    int n;
    cout<<"Enter number of words : " ;cin>>n;
    while(n--){
   string in_word;
   cout<<"Enter word to search : ";cin>>in_word;
   pair<bool, int> ans = abc(data, in_word , 0);
   if(ans.first && ans.second)
   cout<<"Yes "<<ans.second<<endl;
   else cout<<"NO"<<ans.second<<endl;
   }
    return 0; 
} 
