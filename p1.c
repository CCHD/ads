/*This program implements insert operation 
and delete operation on binary serach* tree, 
AVL tree and splay tree. Also, compare the 
three trees in running time*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//define the variable CLK_TCK
#ifndef CLK_TCK
#define CLK_TCK 1000
#endif

clock_t  start, stop;      //used to compute the running time
typedef struct node *Tree;
//the structure
struct node{
	int value;          //key stored in the node
    Tree left;          //the pointer to the left child
    Tree right;         //the pointer to the right chile
    int height;         //only used in AVL tree 
};
//all functions to use
Tree BST_Insert(int a,Tree T);        //Insert
Tree BST_Delete(int a,Tree T);        //Delete
Tree AVL_Insert(int a,Tree T);
Tree AVL_Delete(int a,Tree T);
Tree SPT_Insert(int a,Tree T);
Tree SPT_Delete(int a,Tree T);
Tree Splay(int a,Tree T);              //find the node and spla
int Height(Tree T);                    //compute the height of a node
Tree FindMin(Tree T);                  //find the node having the smallest key
int Max(int a,int b);
Tree SingleLeftRotation(Tree T);      //LL rorate
Tree SingleRightRotation(Tree T);     //RR rorate
Tree DoubleLeftRotation(Tree T);      //LR rorate
Tree DoubleRightRotation(Tree T);     //RL rorate
void SameOrder(int a[],int n);        //insert in increasing order and delete in same order
void ReOrder(int a[],int n);          //insert in increasing order and delete in reverse order
void RandomOrder(int a[],int n);      //insert in random and delete in random

int main(){
	int N,i,ri,repeat;               //N is the number of integers to be operated
	int *a;                    //an array storing all the integers
	char ch[1000];                   //decide whether to run the program or not
	while(1){
		printf("If you want to run the program, please enter '$'. If you want to stop, please enter '#'.\n");
		gets(ch);
		if(ch[0]=='#'){
			break;
		}
		if(ch[0]=='$'){
		    printf("Please input an integer from 1000 to 10000.\n");
	        printf("Input the amount of the numbers:\n");
	        scanf("%d",&N);
	        getchar();
	        if(N<1000||N>10000){
	    	   printf("%d does not meet the input requirements, please input again.\n\n",N);
	    	   continue;
	        }
	        a=(int*)malloc(sizeof(int)*N);
	        //generate N distinct integers
            //to store in the increasing order
	        for(i=0;i<N;i++){
	           a[i]=i;
	        }
	        SameOrder(a,N);
	        ReOrder(a,N);
	        RandomOrder(a,N);
	    }
	    else{
	    	printf("Please enter '$' or '#!\n\n");
	    }
    }
	return 0;
}
//insertion of binary search tree
//Insert a into the tree T, unless it's already there
Tree BST_Insert(int a,Tree T){
	//if T is empty
	if(T==NULL){
		T=(Tree)malloc(sizeof(struct node));
		if(T==NULL)     //the allocation failed
			return NULL;
		else{           //successfully, store the value in the root
			T->value=a;
			T->left=NULL;
			T->right=NULL;
			T->height=0;     //not used in BST
		}
	}
	//T is not empty
	else{
		if(a<T->value)       //the key is expected to be stored in the left subtree of T
			T->left=BST_Insert(a,T->left);
		else if(a>T->value)   //stored in the right subtree of T
			T->right=BST_Insert(a,T->right);
		else    //the key is already in T
			;
	}
	return T;
}
//Delete operation of binary search tree
//delete a from the tree T, unless it's not in the tree
Tree BST_Delete(int a,Tree T){
	Tree Tmp;          //a temporary pointer
	Tmp=(Tree)malloc(sizeof(struct node));  //allocate space to Tmp
	if(T==NULL)      //The tree is empty, can not do deletion
		return NULL;
	else{
		if(a<T->value)     //the node is in the left subtree
			T->left=BST_Delete(a,T->left);
		else if(a>T->value) //the node is in the right subtree 
			T->right=BST_Delete(a,T->right);
		else{   //find the node successfully
			if(T->left&&T->right){       //two children
				Tmp=FindMin(T->right);     //find the minimum node in the right subtree
				T->value=Tmp->value;  //replace the current node's key with the minimum node'key
				T->right=BST_Delete(Tmp->value,T->right);//delete the minimum node in the right subtree
			}
			else{   //one or no child
				Tmp=T;
				if(T->left==NULL)    //no child or a right child 
					T=T->right;
				else      //only a left child
					T=T->left;
			}
		}
	}
	return T;
}
//used to find the minimum node in the tree T
Tree FindMin(Tree T){
     if(T==NULL)
     	return NULL;
     else if(T->left==NULL)    //find the minimum node successfully
     	return T;
     else      //find in the left subtree, according to the property of BST
     	return FindMin(T->left);
}
//compute the height
int Height(Tree T){
	if(T==NULL)    //empty tree
	return -1;
	else return T->height;
}

int Max(int a,int b){
    if(a>b) 
    	return a;
    else
    	return b;
}
//LL
Tree SingleLeftRotation(Tree T){
	Tree tn;
	tn=T->left;
	T->left=tn->right;
	tn->right=T;
	T->height=Max(Height(T->left),Height(T->right))+1;
	tn->height=Max(Height(tn->left),Height(tn->right))+1;
	return tn;
}
//RR
Tree SingleRightRotation(Tree T){
	Tree tn;
	tn=T->right;
	T->right=tn->left;
	tn->left=T;
	T->height=Max(Height(T->left),Height(T->right))+1;
	tn->height=Max(Height(tn->left),Height(tn->right))+1;
	return tn;
}
//LR
Tree DoubleLeftRotation(Tree T){
	T->left=SingleRightRotation(T->left);
	return SingleLeftRotation(T);
}
//RL
Tree DoubleRightRotation(Tree T){
	T->right=SingleLeftRotation(T->right);
	return SingleRightRotation(T);
}
//insert operation of AVL tree
//Insert a into the tree T, unless it's already there
Tree AVL_Insert(int a,Tree T){
	//empty tree
	if(T==NULL){
		T=(Tree)malloc(sizeof(struct node));
		if(T==NULL)   //allocation failed
			return NULL;
		else{         //allocation successfully
			T->value=a;
			T->left=NULL;
			T->right=NULL;
			T->height=0;   //initialize the height of root
		}
	}
	//not empty
	else{
		if(a<T->value){    //the node to be inserted is expected to store in the left subtree
			T->left=AVL_Insert(a,T->left);
			//AVL tree is not balanced
			if(Height(T->left)-Height(T->right)==2){
				if(a<T->left->value)    //LL
					T=SingleLeftRotation(T);
				else        //LR
					T=DoubleLeftRotation(T);
			}
		}
		else if(a>T->value){//the node to be inserted is expected to store in the right subtree
			T->right=AVL_Insert(a,T->right);
			//AVL tree is not balanced
			if(Height(T->right)-Height(T->left)==2){
				if(a>T->right->value)   //RR
					T=SingleRightRotation(T);
				else       //RL
					T=DoubleRightRotation(T);
			}
		}
		else  //the node is already in the tree
			;
	}
	//compute the height of the node again
	T->height=Max(Height(T->left),Height(T->right))+1;
	return T;
}
//Delete operation of AVL tree
//delete a from the tree T, unless it's not in the tree
Tree AVL_Delete(int a,Tree T){
	int i;
	Tree tmp;
	tmp=(Tree)malloc(sizeof(struct node));
	//the tree is empty, the deletion failed
	if(T==NULL){
		printf("Can not find the element.\n");
		return NULL;
	}
	//the node is in the left subtree
	else if(a<T->value){
		T->left=AVL_Delete(a,T->left);
		//the AVL tree is not balanced
		if(Height(T->right)-Height(T->left)==2){
			//the height of right subtree of T depends on the height of 
			//the right subtree of it
			if(Height(T->right->right)>=Height(T->right->left))
				T=SingleRightRotation(T);   
			else 
				T=DoubleRightRotation(T);
		}
	}
    //the node is in the right subtree
	else if(a>T->value){
		T->right=AVL_Delete(a,T->right);
		//the AVL tree is not balanced
		if(Height(T->left)-Height(T->right)==2){
			//the height of left subtree of T depends on the height of 
			//the left subtree of it
			if(Height(T->left->left)>=Height(T->left->right))
				T=SingleLeftRotation(T);
			else 
				T=DoubleLeftRotation(T);
		}
	}
	else{//find it
		if(T->left&&T->right){     //two child
			tmp=FindMin(T->right);
			T->value=tmp->value;
			T->right=AVL_Delete(tmp->value,T->right);
			//not balanced
			if(Height(T->left)-Height(T->right)==2){
				//the height of left subtree of T depends on the height of 
			    //the left subtree of it
				if(Height(T->left->left)>=Height(T->left->right))
					T=SingleLeftRotation(T);
				else 
					T=DoubleLeftRotation(T);
			}
		}
		else{   //one or no child
			if(T->left==NULL)     //one right child or no child
				T=T->right;
			else         //one left child
				T=T->left;
		}
	}
	if(T!=NULL)    //compute the height again
	   T->height=Max(Height(T->left),Height(T->right))+1;
	free(tmp);
    return T;
}
//to find the node having key a, and let it be the root
//if not find, then let the closest node be the root
Tree Splay(int a,Tree T){
	struct node N;
	Tree l,r,y;        
    l=(Tree)malloc(sizeof(struct node));
    r=(Tree)malloc(sizeof(struct node));
    y=(Tree)malloc(sizeof(struct node));
    if(T==NULL)  //empty tree
    	return NULL;
    N.left=N.right=NULL;
    l=r=&N;
    while(1){
    	if(a<T->value){     //may find in the left subtree of T
    		if(T->left==NULL)//not find in the tree
    			break;
    		if(a<T->left->value){   //expect zig-zig or zig
    			y=T->left;          //rorate right
    			T->left=y->right;
    			y->right=T;
    			T=y;
    			if(T->left==NULL)    //only zig, but not find in the tree
    				break;
    		}
    		//link right
    		r->left=T;
    		r=T;
    		T=T->left;
    	}
    	else if(a>T->value){    //may find in the right subtree of T
    		if(T->right==NULL)   //not find
    			break;
    		if(a>T->right->value){   //expect zig-zig or zig
    			y=T->right;         //rorate left
    			T->right=y->left;
    			y->left=T;
    			T=y;
    			if(T->right==NULL) //only zig, but not find
    				break;
    		}
    		//link left
    		l->right=T;
    		l=T;
    		T=T->right;
    	}
    	else  //not find in the tree
    		break;
    }
    //Reassemble
    l->right=T->left;
    r->left=T->right;
    T->left=N.right;
    T->right=N.left;
    return T;
}
//insert operation on splay tree
//Insert a into the tree T, unless it's already there
Tree SPT_Insert(int a,Tree T){
	Tree new;
	new=(Tree)malloc(sizeof(struct node));
	if(new==NULL){
		printf("Ran out of space\n");
		exit(1);
	}
	//a node having the key a
	new->value=a;
	//empty tree
	if(T==NULL){
		new->left=new->right=NULL;
		return new;
	}
	//find a in the tree, or let the closest node be the root
	T=Splay(a,T);
	if(a<T->value){     
	//can not find a, then insert
	//let new be the root
		new->left=T->left;
		new->right=T;
		T->left=NULL;
		return new;
	}
	else if(a>T->value){
		//can not find a, then insert
	    //let new be the root
		new->right=T->right;
		new->left=T;
		T->right=NULL;
		return new;
	}
	else{//find it in the tree
		free(new);
		return T;
	}
}
//delete operation on splay tree
//delete a from the tree T, unless it's not in the tree
Tree SPT_Delete(int a,Tree T){
	Tree x;
	if(T==NULL)    //empty tree
		return NULL;
	T=Splay(a,T);   //find a in the tree
	if(a==T->value){   //find successfully
		if(T->left==NULL){   //only have a right child or no child
			x=T->right;
		}
		else{   //two children or only one left child
			x=Splay(a,T->left);// let the closest node in the left subtree be the root
			x->right=T->right;
		}
		return x;
	}
	//not find a in the tree
	return T;
}
//increasing order 
void SameOrder(int a[],int n){
     double duration1,duration2,duration3;
     Tree BST,AVL,SPT;
     BST=NULL;
     AVL=NULL;
     SPT=NULL;
     int i;
//compute the time of BST
     start=clock();
     for(i=0;i<n;i++)
     	BST=BST_Insert(a[i],BST);
     for(i=0;i<n;i++)
     	BST=BST_Delete(a[i],BST);
     stop=clock();
     duration1=((double)(stop-start))/CLK_TCK;
//compute the time of AVL
     start=clock();
     for(i=0;i<n;i++)
     	AVL=AVL_Insert(a[i],AVL);
     for(i=0;i<n;i++)
     	AVL=AVL_Delete(a[i],AVL);
     stop=clock();
     duration2=((double)(stop-start))/CLK_TCK;
//compute the time of splay tree
     start=clock();
     for(i=0;i<n;i++)
     	SPT=SPT_Insert(a[i],SPT);
     for(i=0;i<n;i++)
     	SPT=AVL_Delete(a[i],SPT);
     stop=clock();
     duration3=((double)(stop-start))/CLK_TCK;

     printf("Insert %d integers in increasing order and delete them in the same order:\n",n);
     printf("Time of unbalanced binary search tree:  %lf\n",duration1);
     printf("Time of AVL tree:  %lf\n",duration2);
     printf("Time of splay tree:  %lf\n\n",duration3);
}
//in decreasing order
void ReOrder(int a[],int n){
     double duration1,duration2,duration3;
     Tree BST,AVL,SPT;
     BST=NULL;
     AVL=NULL;
     SPT=NULL;
     int i;
     //compute the time of BST
     start=clock();
     for(i=0;i<n;i++)
     	BST=BST_Insert(a[i],BST);
     for(i=n-1;i>=0;i--)
     	BST=BST_Delete(a[i],BST);
     stop=clock();
     duration1=((double)(stop-start))/CLK_TCK;
     //compute the time of AVL
     start=clock();
     for(i=0;i<n;i++)
     	AVL=AVL_Insert(a[i],AVL);
     for(i=n-1;i>=0;i--)
     	AVL=AVL_Delete(a[i],AVL);
     stop=clock();
     duration2=((double)(stop-start))/CLK_TCK;
     //compute the time of splay tree
     start=clock();
     for(i=0;i<n;i++)
     	SPT=SPT_Insert(a[i],SPT);
     for(i=n-1;i>=0;i--)
     	SPT=AVL_Delete(a[i],SPT);
     stop=clock();
     duration3=((double)(stop-start))/CLK_TCK;

     printf("Insert %d integers in increasing order and delete them in the reverse order:\n",n);
     printf("Time of unbalanced binary search tree:  %lf\n",duration1);
     printf("Time of AVL tree:  %lf\n",duration2);
     printf("Time of splay tree:  %lf\n\n",duration3);
}
//two operations are both in random order
void RandomOrder(int a[],int n){
	 double duration1,duration2,duration3;
     Tree BST,AVL,SPT;
     BST=NULL;
     AVL=NULL;
     SPT=NULL;
     srand((unsigned)time(NULL));
     int i,j;
     //used to generate N distinct integers in random order
     //0 for not used, 1 for used
     int sign[10000];   
     //compute the time of BST
     start=clock();
     //generate a sequence of N distinct integers in random order
     for(i=0;i<n;i++)   //initialize
     	sign[i]=0;
     for(i=0;i<n;i++){
     	while(1){
           j=rand()%n;    //generate a integer between 0~N
           if(sign[j]!=1)  //not have been used
           	break;
     	}
     	sign[j]=1;//sign it as it's used
     	BST=BST_Insert(a[j],BST);
     }
     //generate a sequence of N distinct integers in random order again
     for(i=0;i<n;i++)
     	sign[i]=0;
     for(i=0;i<n;i++){
     	while(1){
     		j=rand()%n;
     		if(sign[j]!=1)
     			break;
     	}
     	sign[j]=1;
     	BST=BST_Delete(a[j],BST);
     }
     stop=clock();
     duration1=((double)(stop-start))/CLK_TCK;
//compute the time of AVL 
     start=clock();
     for(i=0;i<n;i++)
     	sign[i]=0;
     for(i=0;i<n;i++){
     	while(1){
           j=rand()%n;
           if(sign[j]!=1)
           	break;
     	}
     	sign[j]=1;
     	AVL=AVL_Insert(a[j],AVL);
     }
     for(i=0;i<n;i++)
     	sign[i]=0;
     for(i=0;i<n;i++){
     	while(1){
     		j=rand()%n;
     		if(sign[j]!=1)
     			break;
     	}
     	sign[j]=1;
     	AVL=AVL_Delete(a[j],AVL);
     }
     stop=clock();
     duration2=((double)(stop-start))/CLK_TCK;
//compute the time of splay tree
     start=clock();
     for(i=0;i<n;i++)
     	sign[i]=0;
     for(i=0;i<n;i++){
     	while(1){
           j=rand()%n;
           if(sign[j]!=1)
           	break;
     	}
     	sign[j]=1;
     	SPT=SPT_Insert(a[j],SPT);
     }
     for(i=0;i<n;i++)
     	sign[i]=0;
     for(i=0;i<n;i++){
     	while(1){
     		j=rand()%n;
     		if(sign[j]!=1)
     			break;
     	}
     	sign[j]=1;
     	SPT=SPT_Delete(a[j],SPT);
     }
     stop=clock();
     duration3=((double)(stop-start))/CLK_TCK;
     
     printf("Insert %d integers in random order and delete them in the random order:\n",n);
     printf("Time of unbalanced binary search tree:  %lf\n",duration1);
     printf("Time of AVL tree:  %lf\n",duration2);
     printf("Time of splay tree:  %lf\n\n",duration3);
}
