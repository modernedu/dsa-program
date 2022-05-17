#include<iostream>
using namespace std;

int flag2 = 0, flag3 = 0, cmp = 0;

struct AVLNode{
    string word, meaning;
    AVLNode* left;
    AVLNode* right;
};
AVLNode* tree1;

AVLNode* GetNewNode(AVLNode* new_node){
    AVLNode* newNode = new AVLNode();
    newNode->word = new_node->word;
    newNode->meaning = new_node->meaning;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int FindHeight(AVLNode* root){
    if(root == NULL){
        return -1;
    }
    int leftHeight = FindHeight(root->left);
    int rightHeight = FindHeight(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int getBalanceFactor(AVLNode* root){
    if(root == NULL) return -1;
    else{
        return(FindHeight(root->left) - FindHeight(root->right));
    }
}

AVLNode* rightRotate(AVLNode* current_root){
    AVLNode* new_root = current_root->left;
    AVLNode* T2 = new_root->right;

    //Perform rotation
    new_root->right = current_root;
    current_root->left = T2;

    return new_root;
}

AVLNode* leftRotate(AVLNode* current_root){
    AVLNode* new_root = current_root->right;
    AVLNode* T2 = new_root->left;

    //Perform rotation
    new_root->left = current_root;
    current_root->right = T2;

    return new_root;
}

AVLNode* insertRecursive(AVLNode* root, AVLNode* new_node){
    if(root == NULL){   //empty tree
        root = GetNewNode(new_node);
        return root;
    } 
    else if(new_node->word < root->word){
        root->left = insertRecursive(root->left, new_node);
    }
    else if(new_node->word > root->word){
        root->right = insertRecursive(root->right, new_node);
    }
    else{
        cout<<"*** No duplicates allowed! ***"<<endl;
        return root;
    }

    //AVL operations begin

    int bf = getBalanceFactor(root);
    if(bf > 1 && new_node->word < root->left->word){  //LL imbalance
        return rightRotate(root);
    }
    else if(bf < -1 && new_node->word > root->right->word){   //RR imbalance
        return leftRotate(root);
    }
    else if(bf > 1 && new_node->word > root->left->word){ //LR imbalance
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    else if(bf < -1 && new_node->word < root->right->word){   //RL imbalance
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    else{
        return root;
    } 
}

AVLNode* insert(AVLNode* root)
{
	   AVLNode* new_node = new AVLNode();
	   cout<<"\nEnter keyword:";
	   cin>>new_node->word;
	   cout<<"Enter the meaning of the keyword:";
	   cin.ignore();
	   getline(cin, new_node->meaning);
	   insertRecursive(root, new_node);
}


AVLNode* FindMinRecursive(AVLNode* root){
    if(root == NULL){
        cout<<"BST is empty!\n";
        return NULL;
    }
    else if(root->left == NULL){
        return root;
    }
    return FindMinRecursive(root->left);
}

AVLNode* deleteNode(AVLNode* root, string toDelete){
    if(root == NULL) return root;

    else if(toDelete < root->word){     //Target word in left subtree
        root->left = deleteNode(root->left, toDelete);
    }
    else if(toDelete > root->word){     //Target word in right subtree
        root->right = deleteNode(root->right, toDelete);
    }
    else{   //Target word found

        //Case 1: No child(Leaf node)
        if(root->left == NULL && root->right == NULL){
            delete root;
            root = NULL;
        }

        //Case 2:- 
        //One child(right child)
        else if(root->left == NULL){
            AVLNode* temp = root;
            root = root->right;
            delete temp;
        }
        //One child(left child)
        else if(root->right == NULL){
            AVLNode* temp = root;
            root = root->left;
            delete temp;
        }

        //Case 3: Two children
        else {
            AVLNode* temp = FindMinRecursive(root->right);
            root->word = temp->word;
            root->right = deleteNode(root->right, temp->word);
        }
    }

    int bf = getBalanceFactor(root);
    if(bf == 2 && getBalanceFactor(root->left) >= 0){
        return rightRotate(root);
    }
    else if(bf == 2 && getBalanceFactor(root->left) == -1){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    else if(bf == -2 && getBalanceFactor(root->right) <= 0){
        return leftRotate(root);
    }
    else if(bf == -2 && getBalanceFactor(root->right) == 1){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

AVLNode* remove(AVLNode* root){
    string toDelete;
    cout<<"Enter word to be deleted: ";
    cin>>toDelete;

    return deleteNode(root, toDelete);
}

void ascendingDisplay(AVLNode* tree)    //inorder traversal
{
    if(tree->left==NULL&&tree->right==NULL)
    {	
    	cout<<tree->word<<": "<<tree->meaning<<"\n";
    }
    else
    {
        if(tree->left!=NULL)
        {
        	ascendingDisplay(tree->left);
        }
        cout<<tree->word<<": "<<tree->meaning<<"\n";
        if(tree->right!=NULL)
        {
        	ascendingDisplay(tree->right);
        }
    }
}

void descendingDisplay(AVLNode* tree)
{
    if(tree->left==NULL&&tree->right==NULL)
    {
    	cout<<tree->word<<": "<<tree->meaning<<"\n";
    }
    else
    {
        if(tree->right!=NULL)
        {
        	descendingDisplay(tree->right);
        }
        cout<<tree->word<<": "<<tree->meaning<<"\n";
        if(tree->left!=NULL)
        {
        	descendingDisplay(tree->left);
        }
    }
}

bool Search(AVLNode* root, string data){
    if(root == NULL) return false;
    else if(root->word == data) return true;
    else if(data <= root->word) return Search(root->left, data);
    else return Search(root->right, data);
}

void in_search(AVLNode* root){
    string toSearch;
    cout<<"Enter word to be searched: ";
    cin>>toSearch;
    bool res = Search(root, toSearch);
    if(res)
    {
        cout<<"Word found in dictionary\n\n";
    }
    else
    {
        cout<<"Word not found!\n\n";
    }
}

AVLNode* find(AVLNode* tree, string toFind)
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
        //AVLNode* tree1;
		if(tree->word==toFind)
		{
			cmp++;
			cout<<"\nWord found.\n";
			cout<<tree->word<<": "<<tree->meaning<<"\n";
			tree1=tree;
			return tree;
		}
		else if(tree->word>toFind)
		{
			cmp++;
			find(tree->left,toFind);
		}
		else if(tree->word<toFind)
		{
			cmp++;
			find(tree->right,toFind);
		}
	}
	return tree;
}

void in_find(AVLNode* root)
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

AVLNode* updateMeaning(AVLNode* tree, string toUpdate)
{
	flag3=0;
	find(tree,toUpdate);
	if(flag3==0)
	{
    	cout<<"\nEnter the updated meaning of the keyword:";
    	cin.ignore();
    	getline(cin,tree1->meaning);
    	cout<<"\nThe meaning of '"<<toUpdate<<"' has been updated.\n";
	}
    return tree;
}

void in_update(AVLNode* root)
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


int main(){

    AVLNode* rootPtr;   //Pointer to root node
    rootPtr = NULL; //Initialising an empty BST

    for(int i=0; i<7; i++)
    {
        rootPtr = insert(rootPtr);
    }

    cout<<"\nAscending order of AVL tree:"<<endl;
    ascendingDisplay(rootPtr);
    cout<<endl<<endl;

    cout<<"\nDescending order of AVL tree:"<<endl;
    descendingDisplay(rootPtr);
    cout<<endl<<endl;

    in_find(rootPtr);

    in_update(rootPtr);

    cout<<"Ascending order of AVL tree after updating: "<<endl;
    ascendingDisplay(rootPtr);
    cout<<endl<<endl;

    rootPtr = remove(rootPtr);

    cout<<"Ascending order of AVL tree after deleting: "<<endl;
    ascendingDisplay(rootPtr);
    cout<<endl<<endl;


    return 0;
    
}