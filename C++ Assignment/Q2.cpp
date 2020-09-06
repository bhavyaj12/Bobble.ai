#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<vector>
#include<sstream>
#include<fstream>
#include<unistd.h>
#define ALPHABETS 26
using namespace std;
static int vocab=0;                                   //static variable to count dictionary vocab

struct TrieNode                                       //tree node
{ 
    struct TrieNode* children[ALPHABETS]; 
	  int count;  
    bool isLeaf; 
}; 

struct TrieNode* getNode()                             //create new node
{ 
  struct TrieNode* pNode = new TrieNode;   
  for (int i = 0; i < ALPHABETS; i++) 
      pNode->children[i] = NULL;   
  pNode->isLeaf = false; 
	pNode->count=0;  
    return pNode; 
}; 

void insert(struct TrieNode* root, string key)           //insert node
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
    R->count=vocab++;                                   //At each leaf increment the vocab
} 

bool isLeafNode(struct TrieNode* root) 
{ 
    return root->isLeaf != false; 
} 

void revsearch(struct TrieNode* root, char str[], int level,int num) 
{ 
    
    if (isLeafNode(root) && root->count==num)           //reverse search using number
    { 
        str[level] = '\0'; 
        cout << str << endl; 
    } 
  
    int i; 
    for (i = 0; i < ALPHABETS; i++)  
    { 
       
        if (root->children[i])  
        { 
            str[level] = i + 'a'; 
            revsearch(root->children[i], str, level + 1,num); 
        } 
    } 
} 

 

int main(int argc,char *argv[])
{

	struct TrieNode *root = getNode();   
	
    std::ifstream ifile(argv[1] + std::string(".csv"));			//Pass filename
    std::string line; 
    while (std::getline(ifile, line)) // read the current line
    {
        std::istringstream iss{line}; 
        std::vector<std::string> tokens; 
        std::string token; 
        while (std::getline(iss, token, ','))			           //vector of each row
        {
            tokens.push_back(token); 
        }

       
        std::cout << std::endl;
        std::string key = tokens[0]; 				           //extract string key from vector
        for (int i = 0, len = key.size(); i < len; i++) 
          { 
              if (ispunct(key[i])) 				            //Remove apostrophes to store just alphabets in tree
            { 
                key.erase(i--, 1); 
                len = key.size(); 
            } 
          } 
        cout<<key<<" "<<endl;
       insert(root, key);
        
    }
  
   int ch=0;
   while(1)								     //Search until required
   { 
    int num;
    cout<<"Enter number to reverse search\n";
    cin>>num;
    int level = 0; 
    char str[20]; 
    revsearch(root, str, level,num);
    cout<<"\nEnter 1 to exit\n";
    cin>>ch;
    if(ch==1)
    break;
   }
    
    return 0; 

}
