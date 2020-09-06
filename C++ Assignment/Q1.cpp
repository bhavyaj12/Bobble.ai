#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<sstream>
#include<vector>
#include<fstream>
#include<unistd.h>
#define ALPHABETS 26
using namespace std;

struct TrieNode  
{ 
    struct TrieNode* children[ALPHABETS]; 
	int freq;  
    bool isLeaf; 
}; 

struct TrieNode* getNode() 
{ 
    struct TrieNode* pNode = new TrieNode;   
    for (int i = 0; i < ALPHABETS; i++) 
        pNode->children[i] = NULL;   
    pNode->isLeaf = false; 
	pNode->freq=0;  
    return pNode; 
}; 

void insert(struct TrieNode* root, string key,int freq) 
{ 
    struct TrieNode* R = root;   
    for (int i = 0; i < key.length(); i++)  
    { 
        int index = key[i] - 'a';   
        if (R->children[index] == NULL) 
            R->children[index] = getNode();   
        R = R->children[index]; 
    }   
    R->isLeaf = true; 
    R->freq=freq;
} 

bool isLeafNode(struct TrieNode* root) 
{ 
    return root->isLeaf != false; 
} 

void search(struct TrieNode *root, string key) 
{ 
    struct TrieNode *R = root; 
    int f=0;  
    for (int i = 0; i < key.length(); i++) 
    { 
        int index = key[i] - 'a'; 
        if (!R->children[index])
		{
			cout<<"NO";
			f=1;
			return;
		 
		}        
  
        R = R->children[index]; 
    } 
  
    if(f==0 && R != NULL && R->isLeaf)
    {
    	cout<<"YES "<<R->freq;
	}
	else
	cout<<"NO";
} 

int main(int argc, char *argv[])
{
	
    struct TrieNode *root = getNode();   
	
	std::ifstream ifile(argv[1]);
    std::string line; 
    while (std::getline(ifile, line)) // read the current line
    {
        std::istringstream iss{line}; 
        std::vector<std::string> tokens; 
        std::string token; 
        while (std::getline(iss, token, ','))
        {
            tokens.push_back(token); 
        }

       
        std::cout << std::endl;
        std::string key = tokens[0]; 
        int f = std::stoi(tokens[1]); 
        for (int i = 0, len = key.size(); i < len; i++) 
          { 
              if (ispunct(key[i])) 
            { 
                key.erase(i--, 1); 
                len = key.size(); 
            } 
          } 
        cout<<key<<" "<<f<<endl;
       insert(root, key,f);
        
    }
    
   int ch=0;
   while(1)
   { 
    string key;
    cout<<"\nEnter word to search\n";
    cin>>key;
    for (int i = 0, len = key.size(); i < len; i++) 
          { 
              if (ispunct(key[i])) 
            { 
                key.erase(i--, 1); 
                len = key.size(); 
            } 
          } 
    search(root,key);
    cout<<"\nEnter 1 to exit\n";
    cin>>ch;
    if(ch==1)
    break;
   }
	
    return 0; 
}
