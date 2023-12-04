#include<stdio.h>
#include<stdlib.h>

struct Number{
	int number;
	int color;
	
	struct Number *parent;
	struct Number *right;
	struct Number *left;
}*root;

struct Number *newNbr(int number){
	Number *temp = (Number *)malloc(sizeof(Number));
	temp -> number = number;
	
	
	temp -> left = temp -> right = temp -> parent = NULL;
	temp -> color = 1;
	
	return temp;
}

struct Number *createNbr(struct Number *trav, struct Number *temp){
	if(trav == NULL) return temp;
	if(temp->number < trav->number){
		trav->left = createNbr(trav->left, temp);
		trav->left->parent = trav;
	}
	else if(temp->number > trav->number){
		trav->right = createNbr(trav->right, temp);
		trav->right->parent = trav;
	}
	return trav;
}

void inOrder ( Number *node ){
	if (node ) {
		inOrder (node -> left);
		printf ("%d ", node -> number);
		inOrder (node -> right);
	}
}

void rightRotate(struct Number* temp){
    struct Number* left = temp->left;
    temp->left = left->right;
    if (temp->left)
        temp->left->parent = temp;
    left->parent = temp->parent;
    if (!temp->parent)
        root = left;
    else if (temp == temp->parent->left)
        temp->parent->left = left;
    else
        temp->parent->right = left;
    	left->right = temp;
    	temp->parent = left;
}

void leftRotate(struct Number *temp){
    struct Number* right = temp->right;
    temp->right = right->left;
    if (temp->right)
        temp->right->parent = temp;
    right->parent = temp->parent;
    if (!temp->parent)
        root = right;
    else if (temp == temp->parent->left)
        temp->parent->left = right;
    else
        temp->parent->right = right;
    	right->left = temp;
    	temp->parent = right;
}

void fixup(struct Number *root, struct Number* pointer){
    struct Number *parentpointer = NULL;
    struct Number *grandParentpointer = NULL;
 
    while ((pointer != root) && (pointer->color != 0)&& (pointer->parent->color == 1)){
        parentpointer = pointer->parent;
        grandParentpointer = pointer->parent->parent;
 
        if (parentpointer == grandParentpointer->left){
            struct Number* unclepointer = grandParentpointer->right;
            if (unclepointer != NULL && unclepointer->color == 1){
                grandParentpointer->color = 1;
                parentpointer->color = 0;
                unclepointer->color = 0;
                pointer = grandParentpointer;
            }
            else {
                if (pointer == parentpointer->right){
                    leftRotate(parentpointer);
                    pointer = parentpointer;
                    parentpointer = pointer->parent;
                }
                rightRotate(grandParentpointer);
                int parentcolor = parentpointer->color;
                parentpointer->color = grandParentpointer->color;
                grandParentpointer->color = parentcolor;
                pointer = parentpointer;
            }
        }
        else {
            struct Number *unclepointer = grandParentpointer->left;
            if ((unclepointer != NULL) && (unclepointer->color == 1)){
                grandParentpointer->color = 1;
                parentpointer->color = 0;
                unclepointer->color = 0;
                pointer = grandParentpointer;
            }
            else {
                if (pointer == parentpointer->left) {
                    rightRotate(parentpointer);
                    pointer = parentpointer;
                    parentpointer = pointer->parent;
                }
                leftRotate(grandParentpointer);
                int parentcolor = parentpointer->color;
                parentpointer->color = grandParentpointer->color;
                grandParentpointer->color = parentcolor;
               	pointer = parentpointer;
            }
        }
    }
    root->color = 0;
    return;
}
 

int main(){
	Number *temp = newNbr(41);
	root = createNbr(root, temp);
	fixup(root,temp);
	
	temp = newNbr(22);
	root = createNbr(root, temp);
	fixup(root,temp);
	
	temp = newNbr(5);
	root = createNbr(root, temp);
	fixup(root,temp);
	
	temp = newNbr(51);
	root = createNbr(root, temp);
	fixup(root,temp);
	
	temp = newNbr(48);
	root = createNbr(root, temp);
	fixup(root,temp);
	
	temp = newNbr(29);
	root = createNbr(root, temp);
	fixup(root,temp);
	
	temp = newNbr(18);
	root = createNbr(root, temp);
	fixup(root,temp);
	
	temp = newNbr(21);
	root = createNbr(root, temp);
	fixup(root,temp);
	
	temp = newNbr(45);
	root = createNbr(root, temp);
	fixup(root,temp);
	
	temp = newNbr(3);
	root = createNbr(root, temp);
	fixup(root,temp);
	
	inOrder(root);
	
	return 0;
}
