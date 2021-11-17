#include <stdio.h>
#include <malloc.h>
#include <time.h>


  struct TreapNode {
    int key, priority;
    struct TreapNode *left, *right;
};
 struct TreapNode *root=NULL;

struct TreapNode *rightRotate(struct TreapNode *y)
{
   struct  TreapNode *x = y->left;
   struct TreapNode  *T2 = x->right;
 
    x->right = y;
    y->left = T2;
 
    
    return x;
}
 

struct TreapNode *leftRotate(struct TreapNode *x)
{
   struct TreapNode *y = x->right, *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
  
    return y;
}
 

struct TreapNode* newNode(int data)
{
    struct TreapNode* temp =( struct TreapNode*)malloc(sizeof(struct TreapNode)); 
    temp->key = data;
    temp->priority = rand()%100;
    temp->left = temp->right = NULL;
    return temp;
}
 

struct TreapNode* search(struct TreapNode* root, int data)
{
    if(root==NULL || root->key==data){
       return root;
              
    }
     if(data<root->key) {
                         return   search(root->left,data);
                            }
                   else   {
                     return   search(root->right,data);
                         }
    
}
 

struct TreapNode* insert(struct TreapNode* root, int data)
{     
    
    if (root==NULL){ 
        return newNode(data);}
 
    if (data <= root->key)
    {
      
        struct TreapNode*temp=root->left = insert(root->left, data);
    
    
        if (root->left->priority > root->priority)
            root = rightRotate(root);
    }
    else  
    { 
      
        root->right = insert(root->right, data);
 
     
        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }
    return root;
}
 

struct TreapNode* deleteNode(struct TreapNode* root, int data)
{
    if (root == NULL)
        return root;
 
    if (data < root->key)
        root->left = deleteNode(root->left, data);
    else if (data > root->key)
        root->right = deleteNode(root->right, data);
 
   
    else if (root->left == NULL)
    {
        struct TreapNode *temp = root->right;
        free(root);
        root = temp;  
    }
 
    else if (root->right == NULL)
    {
       struct TreapNode *temp = root->left;
        free(root);
        root = temp;  
    }
 
    
    else if (root->left->priority < root->right->priority)
    {
        root = leftRotate(root);
        root->left = deleteNode(root->left, data);
    }
    else
    {
        root = rightRotate(root);
        root->right = deleteNode(root->right, data);
    }
 
    return root;
}
 

void display(struct TreapNode* root)
{
    if (root)
    {
        display(root->left);
        printf("\n Node key is:%d  Priority is:%d ",root->key,root->priority);
       
        if (root->left)
        printf(" left child:%d",root->left->key);
           
        if (root->right)
        printf("Right child:%d",root->right->key);
           
    
        display(root->right);
    }
}
 
 

int main()
{ 
   int data;
    srand(time(NULL));
 while(1){
     printf("Press 'S' to  search a node,I to insert a node ,'R' to delete a node, 'D' for displaying current heap or 'E' for exit:");
    char tsk;
        scanf("%s",&tsk);
   
      if(tsk=='S'){ 
          printf("Enter the key of node to be searched:");
          scanf("%d",&data);
         struct TreapNode*temp=search(root,data);
          if(temp==NULL) printf("Searched node is not present\n"); 
          else printf("Searched node is present\n");
      }
      if(tsk=='I'){
                    printf("Enter the key of node to be inserted:");
                        scanf("%d",&data);
                       if(root==NULL) root=insert(root,data);
                     else  insert(root,data);

      }
      if(tsk=='R'){
          printf("Enter the key of node to be deleted:");
           scanf("%d",&data);
           deleteNode(root,data);
      }
      if(tsk=='D'){
          display(root);
          printf("\n");
      }
          if(tsk=='E'){
          return -1;
      }


   }
 
    
 
   
 

 

 
    return 0;
}