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
    int number;
    TrieNode(){
        for(int i = 0; i<256; i++)
        children[i] = NULL;
        isword = false;
        freq = 0;
        number=0;
    }
};
class TrieNode *root = new TrieNode();
 TrieNode *getnode()
    {
        TrieNode *temp = new TrieNode();
        return temp;
    }

bool search(int number,TrieNode* root,string s) {
    if(root==NULL) return  false;
    if(root->number==number && root->isword==true)
    {
    cout<<s<<endl;
    return true;
    }
        for(int i=0;i<256;i++)
        {

            if(root->children[i] != NULL)
            {
                string p(1, i);
                //cout<<p<<" ";
                bool ans=search(number,root->children[i],s+p);
                if(ans) return true;
            }
        }
        return false;
    }

void insert(string word,int number)
{
    //cout<<word<<" ";
    TrieNode *temp = root;
        for(int i=0;i<word.size();i++)
        {
            int index = word[i];
            if(temp->children[index] == NULL)
                temp->children[index] = getnode();
             temp = temp->children[index];
        }
        temp->isword = true;
        temp->number = number;
}
int main(int argc, char **argv)
{
    fstream finput;
    finput.open(argv[1] ,ios::in);
    string word ;
     int number=0;
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
        insert(current, number++);
       word.clear();
    }

    int n;
    cout<<"Enter number of words to be search: " ;cin>>n;
    while(n--){
   int searchNumber;
   cout<<"Enter number to search : ";cin>>searchNumber;
   TrieNode* temp=root;
   if(!search(searchNumber,temp,""))
    cout<<"Word at this Number not found\n";
   }
    return 0;
}
