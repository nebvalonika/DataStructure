#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Number{
	int number;
	
	Number *left, *right;
	int height;
}*root;

Number *createNum(int number){
	Number *newNum = (Number *)malloc(sizeof(Number));
	newNum -> number = number;
	
	newNum -> left = newNum -> right = NULL;
	newNum -> height = 1;
	
	return newNum;
}

int max(int a, int b){
	if(a > b){
		return a;
	}
	else{
		return b;
	}
}

int height(Number *node){
	if(!node){
		return 0;
	}
	return node->height;
}

int getBalance(Number *node){
	if(!node){
		return 0;
	}
	
	return height(node->left) - height(node->right);
}

Number *rightRotate(Number *node){
	Number *temp = node->left;
	Number *subTemp = temp->right;
	
	temp->right = node;
	node->left = subTemp;
	
	node->height = 1 + max(height(node->left), height(node->right));
	temp->height = 1 + max(height(temp->left), height(temp->right));
	
	return temp;
}

Number *leftRotate(Number *node){
	Number *temp = node->right;
	Number *subTemp = temp->left;
	
	temp->left = node;
	node->right = subTemp;
	
	node->height = 1 + max(height(node->left), height(node->right));
	temp->height = 1 + max(height(temp->left), height(temp->right));
	
	return temp;
}

Number *insertNum(Number *node, int number){
	if(!node){
		return createNum(number);
	}
	else if(number < node->number){
		node->left = insertNum(node->left, number);
	}
	else if(number > node->number){
		node->right = insertNum(node->right, number);
	}
	
	node->height = 1 + max(height(node->left), height(node->right));
	int balance = getBalance(node);
	
	if(balance > 1 && number < node->left->number){
		return rightRotate(node);
	}
	
	if(balance > 1 && number > node->left->number){
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	
	if(balance < -1 && number > node->right->number){
		return leftRotate(node);
	}
	
	if(balance < -1 && number < node->right->number){
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}	
	return node;
}

void preOrder(Number *node){
	if(node){
		printf("%d ",node->number);
		preOrder(node->left);
		preOrder(node->right);
	}
}

void inOrder(Number *node){
	if(node){
		inOrder(node->left);
		printf("%d ",node->number);
		inOrder(node->right);
	}
}

void postOrder(Number *node){
	if(node){
		postOrder(node->left);
		postOrder(node->right);
		printf("%d ",node->number);
	}
}

Number *search(Number *node, int number){
	if(!node){
		return NULL;
	}
	else if(number < node->number){
		return search(node ->left, number);
	}
	else if(number > node->number){
		return search(node ->right, number);
	}
	return node;
}

void update(int number){
	Number *find = search(root, number);
	if(find){
		find->number =  number;
		printf("Data successful\n");
		return;
	}
	printf("Data not found\n");
	return;
}

Number *mostLeftChild(Number *node){
	Number *curr = node;
	while(curr->left) curr = curr->left;
	return curr;
}

Number *deleteNum(Number *node, int number){
	if(!node) return node;
	else if(number < node->number) node->left = deleteNum(node->left, number);
	else if(number > node->number) node->right = deleteNum(node->right, number);
	else{
		if(!node->left || !node->right){
			Number *temp = node->left ? node->left : node->right;
			
			if(!temp){
				temp = node;
				node = NULL;
			}
			else *node = *temp;
			free(temp);
		} else{
			Number *temp = mostLeftChild(node->right);
			node->number = temp->number;
			node->right = deleteNum(node->right, temp->number);
		}
	}
	if(!node) return node;
	
	node->height = 1 + max(height(node->left), height(node->right));
	int balance = getBalance(node);
	
	if(balance > 1 && node->left->left) return rightRotate(node);
	else if(balance > 1 && node->left->right){
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	else if(balance < -1 && node->right->right) return leftRotate(node);
	else if(balance < -1 && node->right->left){
		node->right - rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

void print(){
	puts ("1. Insertion");
	puts ("2. Deletion");
	puts ("3. Traversal");
	puts ("4. Exit");
	puts ("Choose:");
}

int main(){
	root = NULL;
	int option;
	
	do{
		print();
		scanf("%d",&option);
		getchar();
		if(option == 1){
			int number;
			scanf("%d",&number);
			getchar();
			root = insertNum(root, number);
		}
		else if(option == 2){
			int number;
			scanf("%d",&number);
			getchar();
			root = deleteNum(root,number);
		}
		else if(option == 3){
			printf("Preorder: ");
			preOrder(root);
			puts("");
			printf("Inorder: ");
			inOrder(root);
			puts("");
			printf("Postorder: ");
			postOrder(root);
			puts("");
		}
	}
	while(option != 4);
	printf("Thank you");
	
	return 0;
}
