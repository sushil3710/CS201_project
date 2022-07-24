#include <stdio.h>
#include <malloc.h>
#include <time.h>

  
struct TreapNode{//structure of a treap node
                    int key;//key to store the data of the node
                    int priority;//to store randomly assigned number(priority) of the node
                    struct TreapNode *left, *right;//two pointers for left and right child of a node
                 };
 
 //global pointer for root of our treap initially assigned to NULL
struct TreapNode *root=NULL;

//function to right rotate subtree with root y
struct TreapNode *R_Rotate(struct TreapNode *y)
                                               {
                                                 struct  TreapNode *x = y->left;//assign root's left to node x 
                                                 struct TreapNode  *temp = x->right;//assign x's right to node temp 
                                                //right rotation
                                                 x->right = y;// x's right is assigned the root
                                                 y->left = temp;//assign  temp to the root's left
                                                 
                                                 return x;
                                                }
 
//function to left rotate subtree with root y
struct TreapNode *L_Rotate(struct TreapNode *y)
                                                 {
                                                  struct TreapNode *x = y->right;//assigns root's right to node x 
                                                   struct TreapNode *temp= x->left;//assigns root's left to node temp
                   
                                                  // left rotation
                                                  x->left = y;// assigns y to  x's left 
                                                  y->right = temp;// assigns temp to root's right 
 
                                                  return x;
                                                  }
 
//function to create a new treap node 
struct TreapNode* getNode(int data)
                                  {  //memory allocation for the new node
                                   struct TreapNode* temp =( struct TreapNode*)malloc(sizeof(struct TreapNode)); 
                                   temp->key = data;//input data to the key
                                       //using rand() function to generate random priority for a node
                                   temp->priority = rand()%100;
                                   temp->left = NULL;
                                   temp->right = NULL;
     
                                   return temp;
                                  }
 
//search function to search a particular node if present
struct TreapNode* search(struct TreapNode* root, int data)
                                                          {                                             
                                                            if(root==NULL || root->key==data){//if the root is null or the key of root contains the data value
                                                                                              return root;
                                                                                             }
                                                          
                                                          if(data<root->key) {//if data<root->key then search in the left subtree of the root
                                                                              return   search(root->left,data);
                                                                             }
                                                          else   {//if data>root->key then search in the right subtree of the root
                                                                  return   search(root->right,data);
                                                                 }
    
                                                          }
 
//function to Insert node a treapnode
struct TreapNode* Insert_Tnode(struct TreapNode* root, int data ){     //returning a new node with data in the key of the root if the  root is NULL
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
                                                                                  
                                                             else{ //if data is greater than root->key
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
                                                                if (root == NULL){//if the node is empty return that node
                                                                                return root;
                                                                                 }
                                                                //if data !=root->key and data<root->key then call function delete for the left subtree of the root
                                                                if (data < root->key){
                                                                                     root->left = Delete_Tnode(root->left, data);
                                                                                     }
                                                               //if data !=root->key and data>root->key then call function delete for the right subtree of the root
                                                                else if (data > root->key){
                                                                                           root->right = Delete_Tnode(root->right, data);
                                                                                          }
                                                               //if data==root->key and left subtree is empty
                                                                 else if (root->left == NULL){
                                                                                             struct TreapNode *temp = root->right;
                                                                                             //delete root
                                                                                             free( root);
                                                                                            //right child becomes root
                                                                                             root = temp;  
                                                                                            }
                                                                //if data==root->key and right subtree is empty
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
                                             display(root->left);//to display the left child first
                                             printf("\n Node key is:%d  Priority is:%d ",root->key,root->priority);
       
                                    if (root->left!=NULL)
                                            printf(" left child:%d",root->left->key);
           
                                     if (root->right!=NULL)
                                            printf("  Right child:%d",root->right->key);
           
                                               display(root->right);//then display right child
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
   
      if(tsk=='S'){//if tsk=S search operation will take place if root is not NULL and we have entered the Key to be serached
          if(root==NULL)
          {printf("Treap is empty!! Insert first..\n");
           continue;}
          printf("Enter the key of node to be searched:");
          scanf("%d",&data);
         struct TreapNode*temp=search(root,data);
          if(temp==NULL) printf("Searched node is not present\n"); 
          else printf("Searched node is present\n");
      }
      if(tsk=='I'){//if tsk=I key will be inserted by calling Insert_Node function
                    printf("Enter the key of node to be Inserted:");
                        scanf("%d",&data);
                      root=Insert_Tnode(root,data);
                     printf("Insertion done!!\n");
                     

      }
      if(tsk=='R'){ //If tsk=R a key can be deleted from the treap
          if(root==NULL)
          {printf("Treap is empty!! Insert first..\n");
           continue;}
          printf("Enter the key of node to be deleted:");
           scanf("%d",&data);
           //to check if the node to be deleted is actually present
          struct TreapNode*temp= search(root,data);
           if(temp==NULL) printf("This node is not present in the Treap\n"); 
          else  {
                root=Delete_Tnode(root,data);
                printf("Deletion done!!\n");
                 }
      }
      if(tsk=='D'){//D to display the treap elements
          
          if(root==NULL)
          {printf("Treap is empty!! Insert first..\n");
                         continue;}
              
            printf("The treap is displayed below:\n");
          display(root);
        
          printf("\n");
      }
          if(tsk=='E'){//E to exit
          return -1;
      }


   }
 
 return 0;
}
