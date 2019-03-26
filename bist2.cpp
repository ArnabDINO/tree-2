#include<iostream>
using namespace std;
class node{
	public:
		int data;
		//children
		node* parent;
		node* left;
		node* right;
		
		//default constructor;
		node(int val){
			data=val;
			parent=NULL;
			left=NULL;
			right=NULL;
			;
		}
};

class bist{
	public:
		node* root;
		int count;
		//default;
		bist(){
			count=0;
			root=NULL;
		}
		void insertHelper(node* curr, int value){
			
			//current NULL, insert
			if (curr==NULL){
				curr=new node(value);
				count++;
				if (root==NULL){
					root=curr;
				}
				
				return;
			}
			//else compare and go to left or right
			else{
				if(curr->data>value){
					if (curr->left==NULL){
						curr->left=new node(value);
						count++;
						curr->left->parent=curr;
					}
					else insertHelper(curr->left, value);
				}
				else{
					if (curr->right==NULL){
						curr->right=new node(value);
						count++;
						curr->right->parent=curr;
					}
					else insertHelper(curr->right, value);
				}
			}
			//value < current->data   ...   move left  recurse
			//else   ...   move right  recuse
			
		}
		void insert(int value){
			insertHelper(root, value);
		}
		void display2(node* curr){
			//base condition
			if (curr==NULL)return;
			else{
				display2(curr->left);
				cout<<curr->data<<", ";
				display2(curr->right);
			}
		}
		
		void display(){
			display2(root);
			cout<<endl;
		}
		
		void print2DUtil(node *root, int space)  
    {  
        // Base case  
        if (root == NULL)  
            return;  
        // Increase distance between levels  
        space += 5;  
        // Process right child first  
        print2DUtil(root->right, space);  
    
        // Print current node after space  
        // count  
        cout<<endl;  
        for (int i = 5; i < space; i++)  
            cout<<" ";  
        cout<<root->data<<"\n";  
    
        // Process left child  
        print2DUtil(root->left, space);  
    }  
  
    // Wrapper over print2DUtil()  
    void print2D()  
    {  
        cout << "******************************" << endl;
        // Pass initial space count as 0  
        print2DUtil(root, 0);  
        cout << "******************************" << endl;
        
    }

		node* search_helper(node* curr,int value){
			if (curr==NULL||curr->data==value){
				return curr;
			}
			else if(curr->data>value){
				return search_helper(curr->left,value);
			}
			else{
				return search_helper(curr->right,value);
			}
		}
		
		node* search(int value){
			search_helper(root,value);
		}
		
		//find_min(node* curr)
		node* min_help(node* curr){
			while(curr->left!=NULL){
				curr=curr->left;
			}
			return curr;
		}
		node* find_min(int value){
			if (search(value)!=NULL) min_help(search(value));
			else cout<<"there is no such number\n";
		}
		//count
		void f_count(){
			cout<<count<<endl;
		}
		//void replace_At_Parent(Node * A, Node *B)
		void replace_At_Parent(node* par, node* chi){
			if(par!=root){
				//this code executes when the parent is not root
				chi->parent=par->parent;	//the child's parent is being updated here
				if(par->parent->left==par){	//if par is the left child of its parent
					par->parent->left=chi;	
				}
				else{						//if par is the right child of its parent
					par->parent->right=chi;
				}
				delete par;					//memory dealocation??
			}
			else{							//par is the root
				root=chi;					//root update
				delete par;					//memory dealocation
			}
		}
		
		// void deleteNode(int value)
		//helper
		void deleteHelper(node* curr){
			//case1: when curr is leaf -- 0 child
			if(curr->left==NULL && curr->right==NULL){
				if(curr!=root){
					if(curr->parent->left==curr){	//if curr is the left child of its parent
						curr->parent->left=NULL;	
					}
					else{							//if curr is the right child of its parent
						curr->parent->right=NULL;
					}
				}
				else{
					root=NULL;
				}
			}
			//case2: when curr has one right child
			else if(curr->left==NULL && curr->right!=NULL){
				replace_At_Parent(curr, curr->right);
			}
			//case3: when curr has one left child
			else if(curr->left!=NULL && curr->right==NULL){
				replace_At_Parent(curr, curr->left);
			}
			//case4: when curr has two child
			else{
				node* ptr=min_help(curr->right);
				curr->data=ptr->data;
				deleteHelper(min_help(curr->right));
			}
		}
		//local driver
		 void deleteNode(int value){
		 	if(search(value)!=NULL){
		 		deleteHelper(search(value));
		 	}
		 	else{
		 		cout<<"the value is not present in the tree.\n";
		 	}
		 }
};
/*
int main(){
	bist b1;
	//cout<<b1.find_min(5)->data<<endl;
	b1.insert(10);
	b1.insert(5);
	b1.insert(-1);
	b1.insert(100);
	b1.insert(7);
	b1.display();
	if(b1.search(5)!=NULL){
		cout<<"found\n";
	}
	else{
		cout<<"Invalid input\n";
	}
	cout<<b1.find_min(5)->data<<endl;
	b1.f_count();
	return 0;
}
*/

int main(){
    
    bist bst1;
    bst1.insert(4);
    bst1.insert(2);
    bst1.insert(3);
    bst1.insert(1);
    bst1.insert(6);
    bst1.insert(5);
    bst1.insert(7);
    bst1.insert(8);
    bst1.display();
    if(bst1.search(3) != NULL){
        cout << endl << bst1.search(3)->data << endl;
    }
    bst1.print2D();
    bst1.deleteNode(6);
    bst1.print2D();
    bst1.deleteNode(5);
    bst1.print2D();
    cout << "Deleting 2" << endl;
    bst1.deleteNode(2);
    bst1.print2D();
    bst1.deleteNode(4);
    bst1.print2D();
    bst1.deleteNode(7);
    bst1.print2D();
    bst1.deleteNode(8);
    bst1.print2D();
    bst1.deleteNode(3);
    bst1.print2D();
    bst1.deleteNode(1);
    bst1.print2D();
    bst1.deleteNode(1);
    bst1.print2D();

}
