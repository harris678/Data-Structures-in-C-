/* Program for trie data Structure...*/

#include<bits/stdc++.h>
using namespace std;
class Trie{
  struct trieNode{
    trieNode* character[256];
    int count;
    bool isEnd;
  };
  public:
  trieNode *root=NULL;
  trieNode* createNode(){            //function to create trie Node
    trieNode* newN=new trieNode();
    newN->isEnd=false;
    for(int i=0;i<256;i++)
      newN->character[i]=NULL;
    newN->count=0;
    return newN;
  }

  trieNode* searchPrefix(string key){       //function to search given prefix in trie
    trieNode *ptr=root;
    for(int i=0;i<key.length();i++){
      if(!ptr->character[key[i]])
        return NULL;
      ptr=ptr->character[key[i]];
    }
    return ptr;
  }
  bool searchWord(string key){         //function to search a word in trie...
    trieNode *ptr=searchPrefix(key);
    if(!ptr||!ptr->isEnd)
      return false;
    return true;
  }
  void insertKey(string key){         //function to insert new Word in Trie
    trieNode *ptr=root;
    for(int i=0;i<key.length();i++){
      if(!ptr->character[key[i]]){
        ptr->character[key[i]]=createNode();
        ptr->count++;
      }
      ptr=ptr->character[key[i]];
    }
    ptr->isEnd=true;
  }
  bool deleteKey(trieNode *root,string key){           //Function to delete Word from trie
    trieNode *ptr=root->character[key[0]];
    if(key.size()==1){
      if(!ptr->count){

        delete(ptr);
        root->character[key[0]]=NULL;
        root->count--;
        return true;
      }
      ptr->isEnd=false;
      return false;
    }
    if(deleteKey(ptr,key.substr(1))){
      if((!ptr->count)&&(!ptr->isEnd)){
        delete(ptr);
        root->character[key[0]]=NULL;
        root->count--;
      }
      else{
        return false;
      }
    }
  }
};
int main(){            //driver function for demonstrating trie
  
	Trie t;
	t.root= t.createNode();
	t.insertKey("hello");
	t.insertKey("hii");
	if(t.searchPrefix("ho"))
		printf("not present\n");
	else
		printf("present\n");
	cout<<t.searchWord("hie")<<endl;
	
	t.deleteKey(t.root,"hi");
	cout<<t.searchWord("hi")<<endl;
	cout<<t.searchWord("hii")<<endl;
	return 0;
}
