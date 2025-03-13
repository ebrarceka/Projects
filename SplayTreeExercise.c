#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/*Comparison of an alternative splay tree , Mod-Splay tree which does a splay operation based on the frequency of keys, with a regular one. Ebrar Çelikkaya 150123067*/
typedef struct s{
	int key;
	 struct s*right;
     struct s*left;
	 struct s*parent;
	int frequency;
	
}Tree;

Tree* insertKey (Tree** root, int key,int*ctr);/*inserts the given key , returns the created node*/
void preOrder (Tree ** root, int mode); /*prints out the tree in preorder. 'mode' is to determine whether to print out the frequency values or not*/ 
void rightRotation( Tree **root,Tree* parent); /*does a single right rotation between parent and child.*/
void leftRotation( Tree **root,Tree* parent);/*does a single left rotation between parent and child.*/
void splay ( Tree** root , Tree ** node , int *ctr);/* distinguishes the splay type and splays.*/
void modSplay ( Tree**root , Tree**node, int *ctr);/*does a frequency check , calls splay when necessary.*/


Tree* insertKey (Tree** root, int key, int*ctr){
	
	Tree *current = *root;
	
	if(*root == NULL){/*the new node is the root.*/
		Tree *newPtr = (Tree*)malloc (sizeof(Tree));
	
		newPtr->key = key;
		newPtr->frequency =0;
		newPtr->parent=NULL;
		newPtr->right =NULL;
		newPtr->left =NULL;
		
		*root = newPtr;
	
		return newPtr;
	}
	
	else{
		if (key< current->key){
			(*ctr)++;	
			if( current->left ==NULL){
			
		Tree *newPtr = (Tree*)malloc (sizeof(Tree));
	
		newPtr->key = key;
		newPtr->frequency =0;
		newPtr->parent=current;
		newPtr->right =NULL;
		newPtr->left =NULL;
		
		current->left= newPtr;
		
		return newPtr;  
			}
			else 
			
			insertKey(&(current->left),key,ctr);
			
		}
		
		else if (key > current->key){
				(*ctr)++;
			if( current->right ==NULL){
		  
		Tree *newPtr = (Tree*)malloc (sizeof(Tree));
	
		newPtr->key = key;
		newPtr->frequency =0;
		newPtr->parent=current;
		newPtr->right =NULL;
		newPtr->left =NULL;
		
		current->right= newPtr;
		return newPtr;
			}
			else 
			insertKey(&(current->right),key,ctr);
			
		}
			
		else{
	    (*ctr)++;
		current->frequency++;
	     return current;
		}
	
		
		}
		
	} 
	
 void preOrder (Tree ** root, int mode){
 	/*mode is to determine whether to print out the frequency values or not.*/
 	
 	if (*root ==NULL)
 	return;
 	
 	else {
 		if(mode == 0){
 			
 	
		printf( (*root)->parent==NULL? "(%d)": ",(%d)",(*root)->key);

 		preOrder(&((*root)->left),0);
 		preOrder(&((*root)->right),0);
 		
		 }
		 
 		else if (mode == 1)/*with frequency values*/{
 			
 	    printf( (*root)->parent==NULL? "(%d,%d)": ",(%d,%d)",(*root)->key,(*root)->frequency);
 	
 		preOrder(&((*root)->left),1);
 		preOrder(&((*root)->right),1);
	 }

 	
 }
}

  void splay ( Tree** root , Tree ** node, int *ctr){
  	/*there are 6 cases of splaying , RR , LL , RL ,LR ( zigzag & zigzig for both cases) and X-R (root swap for both left and right)
  	Final condition is that our node is the new root.(which means that its parent ptr is null*/
  
  	if ( *root == NULL){ /* no splaying here */
  	  
  	  *root = *node;

			return;
	  }
	  
  	   while ( (*node)->parent != NULL){ 
  	   	
  	   
  		   
		   Tree * grandpa = (*node)->parent->parent;
  		   Tree * pa = (*node)->parent ;
  		     if ( pa == NULL)break;
			
			 if ( grandpa == NULL){ /*single swap*/
  		   	   
  		   	   if ( (*node) == pa->left){
  		   	   	/*single right rotation*/
						rightRotation ( root, pa); 
  		   	   	  (*ctr)++;
 	
			}	else{
				/*single left rotation*/
				    leftRotation (root, pa);
  		       (*ctr)++;
  		
				 }
			 }
			 
			 else if ( (*node)== pa->left && pa == grandpa->left ){
			 
			 rightRotation( root ,  grandpa); 
			 rightRotation( root , pa);
		     (*ctr)=(*ctr)+2;
		}
			 
			 else if ( (*node)== pa->left && pa == grandpa->right){
			  
			  rightRotation ( root, pa);
			  leftRotation ( root , grandpa);
			 (*ctr)=(*ctr)+2;
			 }
			 
			 else if ( (*node)== pa->right && pa == grandpa->left ){
			 	
			leftRotation ( root , pa);
			rightRotation ( root, grandpa);
			 (*ctr)=(*ctr)+2;
			 }
			 
			 else if ( (*node)== pa->right && pa == grandpa->right){
			 	
			leftRotation ( root , grandpa);
			leftRotation ( root , pa);
	     	(*ctr)=(*ctr)+2;
			 }
			 	
  		
  		
  		if ( (*node)->parent == NULL){ /*condition to stop the loop. its done in the rotation methods as well but this check makes sure not to create an infinite loop*/
  				*root = *node;
  		   (*node)->parent = NULL;
		  }
  	
  			
  		}
		  
  		
  		
	  }
  
  	
 void leftRotation ( Tree **root , Tree *parent){
 	
 	Tree * node = (parent)->right ;
 	Tree *nodeLeft = node->left;
 	
 	
 	/*do the rotation */
 	node->left = parent;
 	parent->right = nodeLeft;
 	
 	/*parent updates */
 	if( nodeLeft!=NULL) 
 	nodeLeft->parent = parent;
 	
 	/*root update when necessary */ 
 	   if((parent)->parent==NULL) /* meaning node is the root now.*/
 	   *root = node;
	  
	  else if ( (parent) == parent->parent->left) /* if the parent was the leftchild of grandpa*/
	  parent->parent->left =node;
	  
	  else 
	  parent->parent->right = node;
 	
 	
 	/*finally assign the child as the parent*/
 	node->parent = parent->parent;
 	parent->parent = node;
 	
 	
 }
 
 
 void rightRotation ( Tree **root , Tree *parent){
 	
 	Tree *node = parent->left ;
 	Tree *nodeRight = node->right ;
 	
 	
 	/*rotation part*/
 	node->right = parent;
 	parent->left = nodeRight ;
 	
 	/*parent & root updates*/
 	 if(nodeRight!=NULL)
 	 nodeRight->parent = parent;
 	 
 	 
 	 if(parent->parent==NULL) /*node is the new root*/ 
 	 *root = node;
 	 
 	 else if ( parent == parent->parent->left)
 	 parent->parent->left = node;
 	 
 	 else 
 	 parent->parent->right = node;
 	 
 	 
 	 node->parent = parent->parent;
 	 parent->parent = node;
 	
 	
 }


 void modSplay ( Tree**root , Tree**node, int *ctr){
 	/*1.if the node is already the root , no splay.*/
 	if ( *root==NULL ||*root == *node){
 		return;
	 }
	 /*2. if the node is not on the root & has a higher frequency value , do the splay.*/
	 
	 else if ( (*node)->frequency >(*root)->frequency){
	 	splay (root , node ,ctr);
	 }
 }
 

int main (void){
	
	Tree *root =NULL;
	Tree *modRoot = NULL;
	
	int costCtr = 0;
	int modCostCtr =0;
	
	FILE *fPtr = fopen("input.txt","r"); 
	char ch ;

    int key =0;
      while ((ch = fgetc(fPtr))!= EOF){
		
		if(isdigit(ch)){
		 key = 10*key + (ch-'0'); 
		 
		}	
		else {
			if(key){
		
		    Tree* newNode = insertKey (&root, key,&costCtr);
			splay (&root , &newNode,&costCtr);
			
			
	     	newNode = insertKey ( &modRoot , key,&modCostCtr);
			modSplay( &modRoot , &newNode,&modCostCtr);	
			
			
				key =0;
		}
	
		}
	
	
		
	}
	printf( "Splay Tree:");  preOrder(&root,0);printf("\n");
   printf( "Mod-Splay Tree:"); preOrder(&modRoot,1);printf("\n");
  
   printf("\n%20s%10d\n%-20s%12d","Cost of Ordinary Splay",costCtr,"Cost of Mod-Splay", modCostCtr);
  
   
   fclose(fPtr);
   
}


