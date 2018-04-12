#include<iostream>
#include<stack>
#include<queue>
#include<set>
using namespace std;

struct node{
	int data;
	node *left,*right;
};

node* createNode(int data){
	node* newN=new node();
	newN->data=data;
	newN->left=newN->right=NULL;
	return newN;
}
void preorderR(node* root){      //Recursive Preorder Traversal
	if(root==NULL)
		return ;
	printf("%d ",root->data);
	preorderR(root->left);
	preorderR(root->right);
	return;
}
void preorderI(node *root){               //Iterative Preorder Traversal
	stack<node*> s;
	s.push(NULL);
	if(root==NULL)
		return;
	printf("%d ",root->data);
	node* ptr=root;
	if(ptr->left==NULL)
		ptr=ptr->right;
	else{
		s.push(ptr->right);
		ptr=ptr->left;
	}
	while(ptr!=NULL){
		printf("%d ",ptr->data);
		if(ptr->left==NULL){
			if(ptr->right==NULL){
				ptr=s.top();
				s.pop();
			}
			else
				ptr=ptr->right;
		}
		else{
			if(ptr->right!=NULL){
			s.push(ptr->right);
			}
			ptr=ptr->left;
		}
	}
}
void preorder(node *root){            //Morris Preorder Traversal ( traversal without recursion and stack)
	if(!root)
		return;
	node *current=root;
	while(current){
		if(!current->left){
			printf("%d ",current->data);
			current=current->right;
		}
		else{
			node *pre=current->left;
			if(pre->right&&pre->right!=current){
				pre=pre->right;
			}
			if(!pre->right){
				pre->right=current;
				printf("%d ",current->data);
				current=current->left;
			}
			else{
				pre->right=NULL;
				current=current->right;
			}
		}
	}
}
void inorderR(node* root){      //Recursive inorder Traversal
	if(root==NULL)
		return;
	inorderR(root->left);
	printf("%d ",root->data);
	inorderR(root->right);
}

void inorderI(node* root){        //Iterative Inorder Traversal
	stack<node*> stk;
	while(1){
		while(root){
			stk.push(root);
			root=root->left;
		}
		if(stk.empty())
			return;
		root=stk.top();
		stk.pop();
		printf("%d ",root->data);
		root=root->right;
	}
	return;
}
void inorder(node *root){             //Morris Inorder Traversal
	if(!root)
		return;
	node *current=root;
	while(current){
		if(!current->left){
			printf("%d ",current->data);
			current=current->right;
		}
		else{
			node *pre=current->left;
			while((pre->right)&&pre->right!=current){
				if(pre->right)
					pre=pre->right;
			}
			if(!pre->right){
				pre->right=current;
				current=current->left;
			}
			else{
				
				printf("%d ",current->data);
				current=current->right;
				pre->right=NULL;
			}
		}
		
	}
}
void postorderR(node* root){             //Recursive Postorder Traversal
	if(root==NULL)
		return;
	postorderR(root->left);
	postorderR(root->right);
	cout<<(root->data);
void postorderI(node* root){            //Iterative Postorder Traversal
	static node* prev=NULL;
	stack<node*> stk;
	stk.push(NULL);
	if(root==NULL)
		return;
	while(root){
		while(root&&(root->left==NULL||root->left!=prev)&&(root->right==NULL||root->right!=prev)){
			stk.push(root);
			prev=root;
			root=root->left;
		}
		if(root==NULL){
			root=stk.top();
			stk.pop();
		}
		if(root->right==NULL||root->right==prev){
			printf("%d ",root->data);
			prev=root;
			root=stk.top();
			stk.pop();
		}
		else if(root->right!=NULL){
			stk.push(root);
			root=root->right;
		}
	}
}


int levelOrder(node *root){                   //Level order Traversal(BFS Traversal)
	if(root==NULL)
		return INT_MIN;
	queue<node*> q;
	q.push(root);
	int maximum=root->data;
	while(!q.empty()){
		node *ptr=q.front();
		printf("%d ",ptr->data);
		if(ptr->data>maximum)
			maximum=ptr->data;
		q.pop();
		if(ptr->left)
			q.push(ptr->left);
		if(ptr->right)
			q.push(ptr->right);
	}
	return maximum;
}

int maximum(node *root){           //maximum of a Binary tree
	if(root==NULL)
		return INT_MIN;
	return max(root->data,max(maximum(root->left),maximum(root->right)));
}

int size(node* root){              //size of a Binary tree
	if(!root)
		return 0;
	return 1+size(root->left)+size(root->right);
}

void levelOrderReversed(node *root){        //BFS traversal in Reversed order
	if(root==NULL)
		return;
	vector<int> v;
	queue<node*> q;
	q.push(root);
	while(!q.empty()){
		node *ptr=q.front();
		q.pop();
		v.push_back(ptr->data);
		if(ptr->right)
			q.push(ptr->right);
		if(ptr->left)
			q.push(ptr->left);
	}
	for(vector<int>::reverse_iterator it=v.rbegin();it!=v.rend();it++)
		printf("%d ",*it);
}

void insertEl(int data,node** root){          //Insertion in a Binary Tree
	node *newN=createNode(data);
	if(!*root){
		*root= newN;
		return;
	}
	queue<node*> q;
	q.push(*root);
	while(!q.empty()){
		node *ptr=q.front();
		q.pop();
		if(ptr->left==NULL){
			ptr->left=newN;
			break;
		}
		else
			q.push(ptr->left);
		if(ptr->right==NULL){
			ptr->right=newN;
			break;
		}
		else
			q.push(ptr->right);
	}
	return;
}
int heightR(node *root){          //Recursive function for height of a binary tree
	if(!root)
		return 0;
	return 1+max(heightR(root->left),heightR(root->right));
}

int heightI(node *root){          //Iterative function for height of a binary tree
	if(root==NULL)
		return 0;
	
	queue<pair<node*,int> > q;
	q.push(make_pair(root,1));
	pair<node*,int> p;
	while(!q.empty()){
		p=q.front();
		q.pop();
		if(p.first->left)
			q.push(make_pair(p.first->left,p.second+1));
		if(p.first->right)
			q.push(make_pair(p.first->right,p.second+1));
	}
	return p.second;
}
node* deleteTree(node *root){          //Delete a binary tree
	if(root==NULL)
		return NULL;
	deleteTree(root->left);
	deleteTree(root->right);
	delete(root);
	return NULL;
}
node* deepestNodeI(node *root){        //Iterative function for Deepest node in a binary tree
	if(root==NULL){
		printf("\nEmpty Tree");
		return NULL;
	}
	node *temp=NULL;
	queue<node*> q;
	q.push(root);
	while(!q.empty()){
		temp=q.front();
		q.pop();
		if(temp->right)
			q.push(temp->right);
		if(temp->left)
			q.push(temp->left);
		
	}
	return temp;
}
void deepestR(node *root,int h,int *max,node** deep){     //utility function for below written function...
	if(root==NULL)
		return;
	if(h>*max){
		*max=h;
		*deep=root;
	}
	if(root->left)
		deepestR(root->left,h+1,max,deep);
	if(root->right)
		deepestR(root->right,h+1,max,deep);
	
}
node* deepestNodeR(node *root){    //Recursive function for deepest node in a binary tree
	if(root==NULL)
		return NULL;
	int max=1;
	node *deep=root;
	deepestR(root,1,&max,&deep);
	return deep;
}
bool compareTwoTrees(node* root1,node* root2){       //this function compares whether two binary trees are identical
	if((!root1)&&(!root2)){
		return true;
	}
	if((root1&&!root2)||(!root1&&root2))
		return false;
	if(root1->data!=root2->data)
		return false;
	return compareTwoTrees(root1->left,root2->left)&&compareTwoTrees(root1->right,root2->right);
}
int treeDiameter(node* root,int *maxx){     //calculates diameter of a binary tree...
	if(!root)
		return 0;
	
	int x=0;
	if(root->left)
		x=treeDiameter(root->left,maxx)+1;
	int y=0;
	if(root->right)
		y=treeDiameter(root->right,maxx)+1;
	if((x+y)>*maxx)
		*maxx=x+y;
	return (x>y)?x:y;
}
int maximumSumLevel(node *root){             //this function returns level having maximum sum
	if(root==NULL)
		return -1;
	queue<node*> q;
	q.push(root);
	q.push(NULL);
	int level=1,max=INT_MIN,l=0,sum=0;
	while(!q.empty()){
		node* temp=q.front();
		q.pop();
		if(temp!=NULL){
			sum+=temp->data;
			if(temp->left)
				q.push(temp->left);
			if(temp->right)
				q.push(temp->right);
		}
		else{
			if(sum>max){
				max=sum;
				l=level;
			}
			level++;
			sum=0;
			if(!q.empty())
				q.push(NULL);
		}
	}
	return l;
}

void printingRootToLeaf(node *root,vector<int> &v){          //printing root to leaf paths for all nodes...
	if(root==NULL){
		return;
	}
	if(root->left==NULL&&root->right==NULL){
		printf("\n");
		for(int i=0;i<v.size();i++)
			printf("%d ",v[i]);
		printf("%d",root->data);
	}
	v.push_back(root->data);
	if(root->left)
		printingRootToLeaf(root->left,v);
	if(root->right)
		printingRootToLeaf(root->right,v);
	v.pop_back();
}
void printRootToLeaf(node *root){
	vector<int> v;
	printingRootToLeaf(root,v);
}

bool givenSumPathExistence(node* root,int sum){       //this function checks whether path with given sum exists...
	if(root==NULL)
		return false;
	if(!(sum-root->data))
		return true;
	return givenSumPathExistence(root->left,sum-root->data)||givenSumPathExistence(root->right,sum-root->data);
}
void interchangeToMirror(node *root){                 //this function interchanges a tree to its mirror
	if(!root)
		return;
	node* temp=root->left;
	root->left=root->right;
	root->right=temp;
	if(root->left)
		interchangeToMirror(root->left);
	if(root->right)
		interchangeToMirror(root->right);
}

bool checkMirror(node* root1,node* root2){           //this function checks whether two trees are mirror of each other or not
	if(!root1&&!root2)
		return true;
	if(!root1||!root2)
		return false;
	return root1->data==root2->data&&(checkMirror(root1->left,root2->right)&&checkMirror(root1->right,root2->left));
}

node* lca(node*root,node *n1,node *n2){            //this function computes lca of two nodes in a tree...
	if(root==NULL)
		return root;
	if(root==n1||root==n2)
		return root;
	node* l=lca(root->left,n1,n2);
	node* r=lca(root->right,n1,n2);
	if(l&&r)
		return root;
	return (l)?l:r;
}
void zigzag(node *root){                    //this function prints zigzag traversal of a binary tree...
	if(!root)
		return;
	queue<node*> q;
	q.push(root);
	q.push(NULL);
	int level=1;
	stack<int> s;
	while(!q.empty()){
		node *nod=q.front();
		q.pop();
		if(nod==NULL){
			if(level%2==0){
				while(!s.empty()){
					printf("%d ",s.top());
					s.pop();
				}
			}
			level++;
			if(!q.empty())
				q.push(NULL);
		}
		else{
			if(level%2==0)
				s.push(nod->data);
			else
				printf("%d ",nod->data);
			if(nod->left)
				q.push(nod->left);
			if(nod->right)
				q.push(nod->right);
		}
	}
}
int main(){                          //Driver function for checking utility functions...
	node *root=NULL,*root1=NULL;
	printf("enter the number of nodes in tree:");
	int n;
	scanf("%d",&n);
	while(n--){
		int el;
		scanf("%d",&el);
		insertEl(el,&root);
		insertEl(el,&root1);
 	}
 	interchangeToMirror(root1);
	printf("\nrecursive preorder traversal is: ");
	preorderR(root);
	printf("\niterative preorder traversal is: ");
	preorderI(root);
	printf("\nmorris preorder traversal is: ");
	preorder(root);
	printf("\nrecursive inorder traversal is: ");
	inorderR(root);
	printf("\niterative inorder traversal is: ");
	inorderI(root);
	printf("\nmorris inorder traversal is: ");
	inorder(root);
	printf("\nrecursive postorder traversal is: ");
	postorderR(root);
	printf("\niterative postorder traversal is: ");
	postorderI(root);
	printf("\nlevel order traversal is: ");
	printf("\n maximum is %d",levelOrder(root));
	printf("\n maximum is %d",maximum(root));
	printf("\nsize of tree is %d",size(root));
	printf("\nlevel order reversed traversal is: ");
	levelOrderReversed(root);
	printf("\n height = %d",heightR(root));
	printf("\n height = %d",heightI(root));
	node* nn=deepestNodeR(root);
	if(nn)
		printf("\ndeepest = %d",nn->data);
	nn=deepestNodeI(root);
	if(nn)
		printf("\ndeepest = %d",nn->data);
	printf("\n%d",compareTwoTrees(root,root));
	int td=0;
	treeDiameter(root,&td);
	printf("\ntree diameter is: %d",td);
	printf("\nmaximum Sum Level is: %d\n",maximumSumLevel(root));
	printf("\n printing paths from root to leaf");
	printRootToLeaf(root);
	printf("\n%d",givenSumPathExistence(root,16));
	printf("\n%d",checkMirror(root,root));
	printf("\nzigzag traversal:");
	zigzag(root);
	printf("\nlevel order traversal before interchanging:");
	levelOrder(root);
	interchangeToMirror(root);
	printf("\nlevel order traversal after interchanging:");
	levelOrder(root);
	
	root=deleteTree(root);
	root1=deleteTree(root1);
	return 0;
}
