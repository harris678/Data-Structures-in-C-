//program to demonstrate all utility functions of BST....

#include<bits/stdc++.h>
using namespace std;
struct node{
	int data;
	node *left,*right;
};
struct llnode{
	int data;
	llnode *next;
};
node* createNode(int data){
	node* newN=new node();
	newN->data=data;
	newN->left=NULL;
	newN->right=NULL;
	return newN;
}
llnode* createllNode(int data){
	llnode* newN=new llnode();
	newN->data=data;
	newN->next=NULL;
	return newN;
}
llnode* insertLL(llnode* head,int data){
	llnode* newN=createllNode(data);
	newN->next=head;
	return newN;
}
bool find(node *root,int data,node *prev,node **par){
	if(!root){
		*par=prev;
		return false;
	}
	
	if(root->data==data){
		*par=prev;
		return true;
	}
	else if(root->data<data){
		return find(root->right,data,root,par);
	}
	else{
		return find(root->left,data,root,par);
	}
	return false;
}

node* insert(node *root,int data){
	if(!root){
		root=createNode(data);
		return root;
	}
	node *ptr=root;
	while(((ptr->data>data)&&(ptr->left))||((ptr->data<data)&&(ptr->right))){
		if(ptr->data>data)
			ptr=ptr->left;
		else
			ptr=ptr->right;
	}
	if(ptr->data>data)
		ptr->left=createNode(data);
	else if(ptr->data<data)
		ptr->right=createNode(data);
	else
		printf("\n<<<< %d IS DUPLICATE ELEMENT>>>>\n",data);
	return root;
}

node* insertR(node *root,int data){
	node *par=NULL;
	if(!root){
		root=createNode(data);
		return root;
	}
	if(!find(root,data,NULL,&par)){
		if(par->data>data)
			par->left=createNode(data);
		else
			par->right=createNode(data);
	}
	else{
		printf("\n<<<< %d IS DUPLICATE ELEMENT>>>>\n",data);
	}
	return root;
}

void preorder(node *root){
	if(!root)
		return;
	printf("%d ",root->data);
	preorder(root->left);
	preorder(root->right);
}
void inorder(node *root){
	if(!root)
		return;
	inorder(root->left);
	printf("%d ",root->data);
	inorder(root->right);
}
void postorder(node *root){
	if(!root)
		return;
	postorder(root->left);
	postorder(root->right);
	printf("%d ",root->data);
}

int extractMin(node *root){
	if(!root)
		return INT_MAX;
	node *ptr=root;
	while(ptr->left){
		ptr=ptr->left;
	}
	return ptr->data;
}

int extractMax(node *root){
	if(!root)
		return INT_MIN;
	node *ptr=root;
	while(ptr->right){
		ptr=ptr->right;
	}
	return ptr->data;
}

node* lcar(node *root,node *alpha,node *beta){
	if(((alpha->data>root->data)&&(beta->data<root->data))||((alpha->data<root->data)&&(beta->data>root->data)))
		return root;
	else if(alpha->data<root->data){
		lcar(root->left,alpha,beta);
	}
	else
		lcar(root->right,alpha,beta);
	return NULL;
}
node* lcai(node *root,node *alpha,node *beta){
	if(!root){
		return NULL;	
	}
	node *ptr=root;
	while(ptr){
		if(ptr->data>alpha->data&&ptr->data>beta->data)
			ptr=ptr->left;
		else if(ptr->data<alpha->data&&ptr->data<beta->data)
			ptr=ptr->right;
		else
			break;
	}
	return ptr;
}
node* deleteNode(node *root,int data){
	if(!root){
		printf("\n<<<TREE EMPTY>>>\n");
		return root;
	}
	node *par=NULL;
	if(!find(root,data,NULL,&par)){
		printf("\n<<<ITEM NOT FOUND>>>\n");
		return root;
	}
	node *ptr=NULL;
	if(par==NULL){
		ptr=root;
	}
	else if((par->left)&&data==par->left->data)
		ptr=par->left;
	else
		ptr=par->right;
	if((!ptr->left)&&(!ptr->right)){
		if(!par)
			root=NULL;
		else if(par->left==ptr)
			par->left=NULL;
		else
			par->right=NULL;
		free(ptr);
		return root;
	}
	if(!ptr->left){
		if(!par)
			root=ptr->right;
		else if(par->left==ptr){
			par->left=ptr->right;
		}
		else{
			par->right=ptr->right;
		}
		free(ptr);
		return root;
	}
	else if(!ptr->right){
		if(!par){
			root=ptr->left;
		}
		if(par->left==ptr){
			par->left=ptr->left;
		}
		else{
			par->right=ptr->left;
		}
		free(ptr);
		return root;
	}
	else{
		int pre=extractMax(ptr->left);
		ptr->left=deleteNode(ptr->left,pre);
		ptr->data=pre;
		return root;
	}
	return root;
}

bool isBST(node *root){
	if(!root)
		return true;
	if(root->left&&root->left->data>=root->data)
		return false;
	if(root->right&&root->right->data<=root->data)
		return false;
	return isBST(root->left)&&isBST(root->right);
}

bool isBST2(node *root,int *prev){   //provided that tree cannot
	if(!root)                       // have duplicate values...
		return true;
	bool x=isBST2(root->left,prev);
	bool y=root->data>*prev;
	*prev=root->data;
	bool z=isBST2(root->right,prev);
	return x&&y&&z;
}
node* bst2dll(node *root,node **t){
	if(root==NULL){
		*t=NULL;
		return NULL;
	}
	node *lh,*lt,*rh,*rt;
	lh=bst2dll(root->left,&lt);
	rh=bst2dll(root->right,&rt);
	root->left=lt;
	root->right=rh;
	if(!rt){
		*t=root;
	}
	else{
		rh->left=root;
		*t=rt;
	}
	if(!lh){
		return root;
	}
	else{
		lt->right=root;
		return lh;
	}
}
node* bst2circulardll(node *root){
	if(!root)
		return NULL;
	node *tail=NULL;
	node *head=bst2dll(root,&tail);
	head->left=tail;
	tail->right=head;
	return head;
}
node* getMedium(node *head){
	node* ptr=head,*med=head;
	head->left->right=NULL;
	while(ptr&&ptr->right){
		med=med->right;
		ptr=ptr->right;
		if(ptr)
			ptr=ptr->right;
	}
	head->left->right=head;
	return med;
}
node* cdll2bst(node *head){
	if(head->left==head){
		head->left=NULL;
		head->right=NULL;
		return head;
	}
	node *med=getMedium(head);
	if(med==head){
		med->left=NULL;
		med->right->right=NULL;
		return med;
	}
	med->left->right=head;
	med->right->left=head->left;
	head->left->right=med->right;
	head->left=med->left;
	med->left=cdll2bst(head);
	med->right=cdll2bst(med->right);
	return med;
}
void traversecdll(node *head){
	if(!head)
		return;
	head->left->right=NULL;
	node *ptr=head;
	while(ptr!=NULL){
		printf("%d ",ptr->data);
		ptr=ptr->right;
	}
	head->left->right=head;
}
node* deleteTree(node *root){
	if(!root)
		return NULL;
	deleteTree(root->left);
	deleteTree(root->right);
	free(root);
	return NULL;
}
node* deletecdll(node *head){
	if(!head)
		return NULL;
	head->left->right=NULL;
	node *ptr=head;
	while(ptr->right!=NULL){
		node *temp=ptr;
		ptr=ptr->right;
		free(temp);
	}
	return NULL;
}
node* sa2bst(int arr[],int si,int ei){
	if(si>ei)
		return NULL;
	if(si==ei){
		return createNode(arr[si]);
	}
	int med=(si+ei)/2;
	node *root=createNode(arr[med]);
	root->left=sa2bst(arr,si,med-1);
	root->right=sa2bst(arr,med+1,ei);
	return root;
}
node* con2bst(llnode** hd,int si,int ei){
	llnode *ptr=*hd;
	if(!(ptr))
		return NULL;
	//printf("data = %d ",ptr->data);
	if(si>ei)
		return NULL;
	node* root=NULL;
	if(si==ei){
		root=createNode((*hd)->data);
		(*hd)=(*hd)->next;
		return root;
	}
	int mid=(si+ei)/2;
	node* l=con2bst(hd,si,mid-1);
	root=createNode((*hd)->data);
	(*hd)=(*hd)->next;
	root->left=l;
	root->right=con2bst(hd,mid+1,ei);
	return root;
}
node* sll2bst(llnode** hd){
	llnode *ptr=*hd;
	int size=0;
	while(ptr){
		size++;
		ptr=ptr->next;
	}
	//printf("hd=%d,size=%d ",(*hd)->data,size);
	//return NULL;
	//ptr=*hd;
	return con2bst(hd,0,size-1);
}
int main(){
	node *root=NULL;
	root=insert(root,6);
	root=insert(root,2);
	root=insert(root,1);
	root=insert(root,8);
	root=insert(root,3);
	root=insert(root,4);
	root=insert(root,5);
	root=insertR(root,7);
	//root->right->right=createNode(2);
	preorder(root);
	printf("\n");
	postorder(root);
	printf("\n");
	inorder(root);
	printf("\n");
	root=deleteNode(root,8);
	preorder(root);
	printf("\n");
	postorder(root);
	printf("\n");
	inorder(root);
	node *lca=lcai(root,root->left->left,root->left->right);
	printf("\nlca is %d",lca->data);
	printf("\nis the given tree a BST? :");
	int prev=INT_MIN;
	isBST2(root,&prev)?printf("yes\n"):printf("no\n");
	int max=extractMax(root);
	if(max!=INT_MIN){
		printf("\nmaximum element in tree is %d",max);
	}
	int min=extractMin(root);
	if(min!=INT_MAX){
		printf("\nminimum element in tree is %d",min);
	}
	node *cll=bst2circulardll(root);
	root=NULL;
	printf("\ncircular doubly linked list is: ");
	traversecdll(cll);
	root=cdll2bst(cll);
	cll=NULL;
	printf("\ninorder traversal of tree is: ");
	inorder(root);
	cll=deletecdll(cll);
	root=deleteTree(root);
	int arr[]={1,2,6,7,9,11,14,15};
	root=sa2bst(arr,0,sizeof(arr)/sizeof(int)-1);
	printf("\ninorder traversal of tree is: ");
	inorder(root);
	root=deleteTree(root);
	llnode* head=NULL;
	head=insertLL(head,15);
	head=insertLL(head,14);
	head=insertLL(head,11);
	head=insertLL(head,9);
	head=insertLL(head,7);
	head=insertLL(head,6);
	head=insertLL(head,1);
	root=sll2bst(&head);
	printf("\ninorder traversal of tree is: ");
	inorder(root);
	root=deleteTree(root);
	return 0;
}
