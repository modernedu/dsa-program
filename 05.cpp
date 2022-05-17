#include<iostream>
#include<string.h>
using namespace std;

struct BstNode {
    string word, meaning;
    BstNode* left;
    BstNode* right;
};

class BST
{
    BstNode* root;
    BstNode* tree;
    BstNode* tree1;
    int flag=0,flag1=0,flag2=0,flag3=0;
    int cmp=0;

public:
    BST()
    {
        root=NULL;
    }
    void insert();
    void createBST(BstNode* root, BstNode* new_node);
    void display(char option);
    void inorderDisplay(BstNode* root);
    void descendingDisplay(BstNode* root);
    void check_same_word(BstNode* node1, BstNode* node2);
    void in_remove();
    BstNode* remove(BstNode* root, string toDelete);
    void in_find();
    BstNode* find(BstNode* root, string toFind);
    void in_update();
    BstNode* updateMeaning(BstNode* root, string newMeaning);
    BstNode* findmin(BstNode* root);
};
void BST::insert()
{
	   BstNode* node = new BstNode();
	   cout<<"\nEnter keyword:";
	   cin>>node->word;
	   cout<<"Enter the meaning of the keyword:";
	   cin.ignore();
	   getline(cin,node->meaning);
	   createBST(root, node);
}
void BST::createBST(BstNode* tree, BstNode* node1)
{
    int i,res;
    char a[20],b[20];
    if(root==NULL)
    {
        root = new BstNode();
        root->word=node1->word;
        root->meaning=node1->meaning;
        root->left=NULL;
        root->right=NULL;
        cout<<"(Root node created)\n";
        return;
    }
    for(i=0;node1->word[i]!='\0';i++)
    {
    	a[i]=node1->word[i];
    }
    for(i=0;tree->word[i]!='\0';i++)
    {
    	b[i]=tree->word[i];
    }
    res = strcmp(b,a);
    check_same_word(tree,node1);
    if(flag==1)
    {
        cout<<"The word you entered already exists.\n";
        flag=0;
    }
    else
    {
    	if(res>0)
    	{
        	if(tree->left!=NULL)
        	{
        		createBST(tree->left,node1);
        	}
        	else
        	{
            	tree->left=node1;
            	(tree->left)->left=NULL;
            	(tree->left)->right=NULL;
            	cout<<"(Node added to left of "<<tree->word<<")\n";
            	return;
        	}
    	}
    	else if(res<0)
    	{
        	if(tree->right!=NULL)
         	{
            	createBST(tree->right,node1);
         	}
         	else
         	{
            	tree->right=node1;
             	(tree->right)->left=NULL;
             	(tree->right)->right=NULL;
             	cout<<"(Node added to right of "<<tree->word<<")\n";
             	return;
         	}
    	}
    }
}
void BST::check_same_word(BstNode* tree,BstNode* node1)
{
	if(tree->word==node1->word)
	{
		flag=1;
		return;
	}
	else if(tree->word>node1->word)
    {
		if(tree->left!=NULL)
		{
    		check_same_word(tree->left,node1);
		}
    }
    else if(tree->word<node1->word)
    {
    	if(tree->right!=NULL)
    	{
    		check_same_word(tree->right,node1);
    	}
    }
}
void BST::display(char option)
{
	if(root!=NULL)
	{
        if(option == 'a'){
    	    cout<<"The words entered in the dictionary are(ascending order):\n\n";
    	    inorderDisplay(root);
        }
        else if(option == 'd'){
            cout<<"The words entered in the dictionary are(descending order):\n\n";
    	    descendingDisplay(root);
        }
	}
	else
	{
        cout<<"\nThere are no words in the dictionary.\n";
	}
}
void BST::inorderDisplay(BstNode* tree)
{
    if(tree->left==NULL&&tree->right==NULL)
    {	
    	cout<<tree->word<<": "<<tree->meaning<<"\n\n";
    }
    else
    {
        if(tree->left!=NULL)
        {
        	inorderDisplay(tree->left);
        }
        cout<<tree->word<<": "<<tree->meaning<<"\n\n";
        if(tree->right!=NULL)
        {
        	inorderDisplay(tree->right);
        }
    }
}
void BST::descendingDisplay(BstNode* tree)
{
    if(tree->left==NULL&&tree->right==NULL)
    {
    	cout<<tree->word<<": "<<tree->meaning<<"\n\n";
    }
    else
    {
        if(tree->right!=NULL)
        {
        	descendingDisplay(tree->right);
        }
        cout<<tree->word<<": "<<tree->meaning<<"\n\n";
        if(tree->left!=NULL)
        {
        	descendingDisplay(tree->left);
        }
    }
}
void BST::in_remove()
{
	//char t;
    string delWord;
	if(root!=NULL)
	{
		cout<<"\nEnter a keyword to be deleted:";
	  	cin>>delWord;
	  	remove(root, delWord);
	  	if(flag1==0)
	  	{
	    	cout<<"\nThe word '"<<delWord<<"' has been deleted.\n";
	  	}
	  	flag1=0;
	}
	else
	{
		cout<<"\nThere are no words in the dictionary.\n";
	}
}
BstNode* BST::remove(BstNode* tree, string toDelete)
{
	BstNode* temp;
    if(tree==NULL)
    {
    	cout<<"\nWord not found.\n";
    	flag1=1;
    	return tree;
    }
    else if(tree->word > toDelete)
    {
    	tree->left=remove(tree->left,toDelete);
    	return tree;
    }
    else if(tree->word<toDelete)
    {
    	tree->right=remove(tree->right,toDelete);
    	return tree;
    }
    else
    {
    	if(tree->left==NULL&&tree->right==NULL)
    	{
    		delete tree;
    		tree=NULL;
    	}
    	else if(tree->left==NULL)
    	{
    		temp=tree;
    		tree=tree->right;
    		delete temp;
    	}
    	else if(tree->right==NULL)
    	{
    		temp=tree;
    		tree=tree->left;
    		delete temp;
    	}
    	else
    	{
    		temp=findmin(tree->right);
    		tree->word=temp->word;
    		tree->meaning=temp->meaning;
    		tree->right=remove(tree->right,temp->word);
    	}
    }
    return tree;
}
BstNode* BST::findmin(BstNode* tree)
{
	while(tree->left!=NULL)
	{
		tree=tree->left;
	}
	return tree;
}
void BST::in_find()
{
	flag2=0,cmp=0;
    string word;
	if(root!=NULL)
	{
		cout<<"\nEnter the keyword to be searched:";
		cin>>word;
    	find(root,word);
    	if(flag2==0)
    	{
			cout<<"Number of comparisons needed: "<<cmp<<"\n";
			cmp=0;
    	}
	}
	else
	{
		cout<<"\nThere are no words in the dictionary.\n";
	}
}
BstNode* BST::find(BstNode *tree, string toDelete)
{
	if(tree==NULL)
	{
		cout<<"\nWord not found.\n";
		flag2=1;
		flag3=1;
		cmp=0;
	}
	else
	{
		if(tree->word==toDelete)
		{
			cmp++;
			cout<<"\nWord found.\n";
			cout<<tree->word<<": "<<tree->meaning<<"\n";
			tree1=tree;
			return tree;
		}
		else if(tree->word>toDelete)
		{
			cmp++;
			find(tree->left,toDelete);
		}
		else if(tree->word<toDelete)
		{
			cmp++;
			find(tree->right,toDelete);
		}
	}
	return tree;
}
void BST::in_update()
{   
    string word;
	if(root!=NULL)
	{
		cout<<"\nEnter the keyword to be updated:";
		cin>>word;
    	updateMeaning(root,word);
	}
	else
	{
		cout<<"\nThere are no words in the dictionary.\n";
	}
}
BstNode* BST::updateMeaning(BstNode *tree, string toDelete)
{
	flag3=0;
	find(tree,toDelete);
	if(flag3==0)
	{
    	cout<<"\nEnter the updated meaning of the keyword:";
    	cin.ignore();
    	getline(cin,tree1->meaning);
    	cout<<"\nThe meaning of '"<<toDelete<<"' has been updated.\n";
	}
    return tree;
}
int main()
{
    int ch;
    BST obj;
    do
    {
    	cout<<"\n******************************************\n"
    	  "DICTIONARY OPERATIONS:\n"
          "1. Add new keyword.\n"
          "2. Display the contents of the Dictionary(Ascending order).\n"
          "3. Display the contents of the Dictionary(Descending order).\n"
    	  "4. Delete a keyword.\n"
    	  "5. Find a keyword.\n"
    	  "6. Update the meaning of a keyword.\n"
    	  "7. Exit.\n"
    	  "******************************************\n"
          "\nEnter a choice(1 to 7):";
    	cin>>ch;
    	switch(ch)
    	{
        	case 1:obj.insert();
        			break;
        	case 2:obj.display('a');
        	   		break;
        	case 3:obj.display('d');
        	   		break;
        	case 4:obj.in_remove();
               		break;
        	case 5:obj.in_find();
               		break;
        	case 6:obj.in_update();
        	   		break;
        	case 7:cout<<"***You have exited***";
               		break;
        	default:cout<<"\nPlease enter a valid option.\n";
        			break;
    	}
    }while(ch!=7);
    return 0;
}
