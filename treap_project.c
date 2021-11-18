#include <stdio.h>
#include <malloc.h>
#include <time.h>

  
struct TreapNode{
                    int key;
                    int priority;
                    struct TreapNode *left, *right;
                 };
 
 //global pointer for root of our treap
struct TreapNode *root=NULL;

//function to right rotate subtree with root y
struct TreapNode *R_Rotate(struct TreapNode *y)
                                               {
                                                 struct  TreapNode *x = y->left;
                                                 struct TreapNode  *temp = x->right;
                                                //right rotation
                                                 x->right = y;
                                                 y->left = temp;
                                                 
                                                 return x;
                                                }
 
//function to left rotate subtree with root y
struct TreapNode *L_Rotate(struct TreapNode *y)
                                                 {
                                                  struct TreapNode *x = y->right;
                                                   struct TreapNode *temp= x->left;
                   
                                                  // left rotation
                                                  x->left = y;
                                                  y->right = temp;
 
                                                  return x;
                                                 }
 
//function to create a new treap node 
struct TreapNode* getNode(int data)
                                  {      //memory allocation for the node
                                   struct TreapNode* temp =( struct TreapNode*)malloc(sizeof(struct TreapNode)); 
                                   temp->key = data;
                                       //using rand() function to generate random priority for a node
                                   temp->priority = rand()%100;
                                   temp->left = NULL;
                                   temp->right = NULL;
     
                                   return temp;
                                  }
 
//search function to search a particular node if present
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
 
//function to Insert node a treapnode
struct TreapNode* Insert_Tnode(struct TreapNode* root, int data ){     //returning a new node if root is NULL
                                                            if (root==NULL){ 
                                                                            return getNode(data);
                                                                           }
                                                                           //if data is less than root->key
                                                            if (data <= root->key){
                                                                                   root->left = Insert_Tnode(root->left, data);
                                                                //adjusting heap priority property i.e right rotating if left child(priority)>root(priority)
                                                                                   if (root->left->priority > root->priority){
                                                                                                                             root = R_Rotate(root);
                                                                                                                            }
                                                                                  }
                                                                                  //if data is greater than root->key
                                                             else{ 
                                                                   root->right = Insert_Tnode(root->right, data);
                                                                  //adjusting heap priority property i.e left rotating if right child(priority)>root(priority)
                                                                   if (root->right->priority > root->priority){
                                                                                                                root =L_Rotate(root);
                                                                                                              }
                                                                 }
                                                          return root;
                                                         }
 
//function to delete a particular node
struct TreapNode* Delete_Tnode(struct TreapNode* root, int data)
                                                               {
                                                                if (root == NULL){
                                                                                return root;
                                                                                 }
                                                    //if data !=root->key
                                                                if (data < root->key){
                                                                                     root->left = Delete_Tnode(root->left, data);
                                                                                     }
                                                                else if (data > root->key){
                                                                                           root->right = Delete_Tnode(root->right, data);
                                                                                          }
                                                    //if data==root->key 
                                                                 else if (root->left == NULL){
                                                                                             struct TreapNode *temp = root->right;
                                                                                             //delete root
                                                                                             free( root);
                                                                                            //right child becomes root
                                                                                             root = temp;  
                                                                                            }
                                                                else if (root->right == NULL) {
                                                                                              struct TreapNode *temp = root->left;
                                                                                              //delete root
                                                                                               free (root);
                                                                                               //left child becomes root
                                                                                               root = temp;  
                                                                                             }
                                                    //if data=root->key both left and right child are not NULL                                        
                                                                else if (root->left->priority < root->right->priority)  {
                                                                                                                           root = L_Rotate(root);
                                                                                                                           root->left = Delete_Tnode(root->left, data);
                                                                                                                        }
                                                                else if(root->left->priority > root->right->priority) {
                                                                                                                      root = R_Rotate(root);
                                                                                                                     root->right = Delete_Tnode(root->right, data);
                                                                                                                     }
 
                                                                 return root;
                                                                      }
 
//function to display the current treap
void display(struct TreapNode* root){
                                    if (root!=NULL)
                                            {
                                             display(root->left);
                                             printf("\n Node key is:%d  Priority is:%d ",root->key,root->priority);
       
                                    if (root->left!=NULL)
                                            printf(" left child:%d",root->left->key);
           
                                     if (root->right!=NULL)
                                            printf("  Right child:%d",root->right->key);
           
                                               display(root->right);
                                           }
                                   }
 
 
int main()
{ 
   int data;
   srand(time(NULL));//sets the seed value for rand function
 while(1){
     printf("Press 'S' to  search a node,I to Insert a node ,'R' to delete a node, 'D' for displaying current heap or 'E' for exit:");
    char tsk;
        scanf("%s",&tsk);
   
      if(tsk=='S'){ 
          if(root==NULL){printf("Treap is empty!! Insert first..\n");continue;}
          printf("Enter the key of node to be searched:");
          scanf("%d",&data);
         struct TreapNode*temp=search(root,data);
          if(temp==NULL) printf("Searched node is not present\n"); 
          else printf("Searched node is present\n");
      }
      if(tsk=='I'){
                    printf("Enter the key of node to be Inserted:");
                        scanf("%d",&data);
                      root=Insert_Tnode(root,data);
                     printf("Insertion done!!\n");
                     

      }
      if(tsk=='R'){ 
          if(root==NULL){printf("Treap is empty!! Insert first..\n");continue;}
          printf("Enter the key of node to be deleted:");
           scanf("%d",&data);
         root=Delete_Tnode(root,data);

             printf("Deletion done!!\n");
      }
      if(tsk=='D'){
          if(root==NULL){printf("Treap is empty!! Insert first..\n");continue;}
            printf("The treap is displayed below:\n");
          display(root);
        
          printf("\n");
      }
          if(tsk=='E'){
          return -1;
      }


   }
 
 return 0;
}
