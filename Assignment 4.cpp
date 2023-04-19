//Cedric Dortch 
//Wednesday April 5th, 2023
//Assignment 4


#include <iostream>
#include <queue>
#include <set>

using namespace std;

// Data structure to store a binary tree node
struct Node
{
    int key;
    Node* left, * right;

    Node(int key)
    {
        this->key = key;
        this->left = this->right = nullptr;
    }
};



//if you need any helper functions, write them here:
/* A helper function that stores inorder
   traversal of a tree rooted with node */
void storeInorder(Node* node, int inorder[], int* index_ptr)
{
    // Base Case
    if (node == NULL)
        return;
 
    /* first store the left subtree */
    storeInorder(node->left, inorder, index_ptr);
 
    /* Copy the root's data */
    inorder[*index_ptr] = node->key;
    (*index_ptr)++; // increase index for next entry
 
    /* finally store the right subtree */
    storeInorder(node->right, inorder, index_ptr);
}

/* A helper function that copies contents of arr[]
   to Binary Tree. This function basically does Inorder
   traversal of Binary Tree and one by one copy arr[]
   elements to Binary Tree nodes */
void arrayToBST(int* arr, Node* root, int* index_ptr)
{
    // Base Case
    if (root == NULL)
        return;
 
    /* first update the left subtree */
    arrayToBST(arr, root->left, index_ptr);
 
    /* Now update root's data and increment index */
    root->key = arr[*index_ptr];
    (*index_ptr)++;
 
    /* finally update the right subtree */
    arrayToBST(arr, root->right, index_ptr);
}


//getting the maximum of two integers
int max(int a, int b) {
    return(a > b) ? a : b; 
}




//function to print every node's key using inorder traversal
void inorder(Node* root) {

    if (root==nullptr) {
        return;
    }
    else {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
        
}


//  function to calculate the height of a binary tree
int height(Node* root)
{
    // TODO 1: return the height of the tree. If the tree is empty, return -1
    //use 7.8 zybook. What is max?
    if (root == nullptr) {
        return -1; 
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + max(leftHeight, rightHeight);
}



//  function to calculate the total number of nodes in a binary tree   
int size(Node* root)
{
    // TODO 2: return the total number of nodes in the tree
    if (root == nullptr) {
        return 0; 
    }

    return(1 + size(root->left) + size(root->right)); 

}


//  function to check if a given binary tree is a complete tree or not

bool isComplete(Node* root)
{
    // TODO 3: return a bool value: if the tree is complete, return 1; otherwise, return 0
    queue<Node*> q; //queue to store values
    q.push(root);

    bool flag = false; //boolean type flag

    while(!q.empty()) { //while loop


        Node* temp = q.front();
        q.pop(); 
        if(temp->left) {
            if(flag == true) {
                return false;
            }
            q.push(temp->left);
        }

        else {
            flag = true; 
        }
        

        if (temp->right) {
            if(flag == true) {
                return false;
            }

            q.push(temp->right); 
        }

        else {
            flag = true; 
        }
    }

    return true; 

}

// Following function is needed for library function qsort()
int compare(const void* a, const void* b) //compare two values
{
    return (*(int*)a - *(int*)b);
}



//  function to convert the binary tree to a binary search tree, but maintaining its structure 
void convert_BST(Node* root) {
    //TODO 4: convert the binary tree to a binary search tree, but maintaining its structure 
    // base case: tree is empty
    if (root == NULL)
        return;
 
    /* Count the number of nodes in Binary Tree so that
    we know the size of temporary array to be created */
    int n = size(root);
 
    // Create a temp array arr[] and store inorder
    // traversal of tree in arr[]
    int* arr = new int[n];
    int i = 0;
    storeInorder(root, arr, &i);
 
    // Sort the array using library function for quick sort
    qsort(arr, n, sizeof(arr[0]), compare);
 
    // Copy array elements back to Binary Tree
    i = 0;
    arrayToBST(arr, root, &i);
 
    // delete dynamically allocated memory to
    // avoid memory leak
    delete[] arr;


}


int main()
{
    
    /* Construct the following tree
              1
            /   \               
           2     3
            \   / \
             5 6   7                      
    */

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    cout << "Printing all nodes with inorder traversal:" << endl;
    inorder(root);
    cout << endl;

    
    cout << "The size of the tree is " << size(root) <<endl;
    
    cout << "The height of the tree is " << height(root) << endl;

    
    if (isComplete(root)) {
        cout << "The tree is a complete binary tree" << endl;
    }
    else {
        cout << "The tree is not a complete binary tree" << endl;
    }

    

    convert_BST(root);

    cout << "Printing all nodes with inorder traversal after the conversion:" << endl;
    inorder(root);
    cout << endl;

    return 0;
}