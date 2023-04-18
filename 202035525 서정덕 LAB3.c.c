//202035525
//서정덕
//LAB#3

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#define RMAX 100

typedef struct node
{
	int data;
	struct node* left, * right;
	int ht;
}node;

node* insert(node*, int);
node* Delete(node*, int);
void preorder(node*);
void inorder(node*);
int height(node*);
node* rotateright(node*);
node* rotateleft(node*);
node* RR(node*);
node* LL(node*);
node* LR(node*);
node* RL(node*);
int BF(node*);
void randomArr();
void findUnique();
void searchMax(node*);
node* searchKey(node* root, int x);
node* prtSearch(node*, int x);
void underPrint(node*root, int x);
void overPrint(node* root, int x);
void overUnder(node* root, int x, int y);

int data[200];
int unique[50] = { 0, };

int main()
{
	node* root = NULL;
	randomArr();
	findUnique();
	
	int i = 0;

	//insert arr to tree
	while (i < 50 && unique[i] != 0) {
		root = insert(root, unique[i]);
		i++;
	}

	//Search 15, 20, 50, 70, 90
	prtSearch(root, 15);
	prtSearch(root, 20);
	prtSearch(root, 50);
	prtSearch(root, 70);
	prtSearch(root, 90);

	//Search MAX
	searchMax(root);
	
	//print under 15
	printf("\nprint under 15:\n");
	underPrint(root, 15);

	//print over 50
	printf("\nprint over 50:\n");
	overPrint(root, 50);

	//print over 15, under 50
	printf("\nprint over 15, under 50\n");
	overUnder(root, 15, 50);
}

void underPrint(node* root, int x)
{
	if (x > root->data) {

		inorder(root->left);
		printf("%d\n", root->data);
		if(root->right != NULL)
			underPrint(root->right, x);

	}
	else {
		if (root->left != NULL) {
			underPrint(root->left, x);
		}
		else
			return;
	}

}

void overPrint(node* root, int x)
{
	if (x < root->data) {
		if (root->left != NULL)
			overPrint(root->left, x);
		printf("%d\n", root->data);
		inorder(root->right);



	}
	else {
		if (root->right != NULL) {
			overPrint(root->right, x);
		}
		else
			return;
	}
}

void overUnder(node* root, int x, int y)
{
	if (x >= root->data) {
		overUnder(root->right, x, y);
		return;
	}
	else if (y <= root->data) {
		overUnder(root->left, x, y);
		return;
	}
	else {//x < data < y

		if (root->left != NULL)
			overUnder(root->left, x, y);
		printf("%d\n", root->data);
		if(root->right != NULL)
			overUnder(root->right, x, y);

	}
}


node* prtSearch(node* root, int x)
{
	node* ptr = searchKey(root, x);
	if (ptr != NULL)
		printf("search success : %d\n", ptr->data);
	else
		printf("search failed : %d\n", x);
}



node* searchKey(node* root, int x)
{
	node* ptr = root;
	node* ptr2 = NULL;

	if (x > ptr->data) {
		if (ptr->right != NULL)
			ptr2 = searchKey(ptr->right, x);
		else
			return NULL;
	}
	else if (x < ptr->data) {
		if (ptr->left != NULL)
			ptr2 = searchKey(ptr->left, x);
		else
			return NULL;
	}
	else
		return ptr;

	return ptr2;

}


void searchMax(node* root)
{
	node* ptr = root;
	while (ptr->right) {
		ptr = ptr->right;
	}
	printf("Max key : %d\n", ptr->data);
}



void randomArr()
{
	srand(time(NULL));
	int i = 0;
	data[0] = 15;
	data[1] = 50;
	for (i = 2; i < 200; i++) {
		data[i] = 1 + (int)rand() % RMAX;
	}
}

void findUnique()
{
	int i = 0;//data index
	int ui = 0;//unique index
	int j = 0;
	while (ui < 50 && i < 200) {
		for ( j= 0; j < ui; j++) {
			if (unique[j] == data[i])
				break;
		}
		if (unique[j] != data[i]) {
			unique[ui] = data[i];
			ui++;
		}
		i++;
	}
}

node* insert(node* T, int x)
{
	if (T == NULL)
	{
		T = (node*)malloc(sizeof(node));
		T->data = x;
		T->left = NULL;
		T->right = NULL;
	}
	else {
		if (x > T->data)		// insert in right subtree
		{
			T->right = insert(T->right, x);
			if (BF(T) == -2)
				if (x > T->right->data)// R자식 값
					T = RR(T);
				else
					T = RL(T);
		}
		else
			if (x < T->data)
			{
				T->left = insert(T->left, x);
				if (BF(T) == 2)
					if (x < T->left->data)
						T = LL(T);
					else
						T = LR(T);
			}
	}

	T->ht = height(T);

	return(T);
}

int height(node* T)
{
	int lh, rh;
	if (T == NULL)
		return(0);

	if (T->left == NULL)
		lh = 0;
	else
		lh = 1 + T->left->ht;

	if (T->right == NULL)
		rh = 0;
	else
		rh = 1 + T->right->ht;

	if (lh > rh)
		return(lh);

	return(rh);
}

int BF(node* T)
{
	int lh, rh;
	if (T == NULL)
		return(0);

	if (T->left == NULL)
		lh = 0;
	else
		lh = 1 + T->left->ht;

	if (T->right == NULL)
		rh = 0;
	else
		rh = 1 + T->right->ht;

	return(lh - rh);
}

node* rotateright(node* x)
{
	node* y;
	y = x->left;
	x->left = y->right;
	y->right = x;
	x->ht = height(x);
	y->ht = height(y);
	return(y);
}

node* rotateleft(node* x)
{
	node* y;
	y = x->right;
	x->right = y->left;
	y->left = x;
	x->ht = height(x);
	y->ht = height(y);

	return(y);
}

node* RR(node* T)
{
	T = rotateleft(T);
	return(T);
}

node* LL(node* T)
{
	T = rotateright(T);
	return(T);
}

node* LR(node* T)
{
	T->left = rotateleft(T->left);
	T = rotateright(T);

	return(T);
}

node* RL(node* T)
{
	T->right = rotateright(T->right);
	T = rotateleft(T);
	return(T);
}



void preorder(node* T)
{
	if (T != NULL)
	{
		printf("%d", T->data);
		preorder(T->left);
		preorder(T->right);
	}
}

void inorder(node* T)
{
	if (T != NULL)
	{
		inorder(T->left);
		printf("%d\n", T->data);
		inorder(T->right);
	}
}


node* Delete(node* T, int x)
{
	node* p;

	if (T == NULL)
	{
		return NULL;
	}
	else
		if (x > T->data)		// insert in right subtree
		{
			T->right = Delete(T->right, x);
			if (BF(T) == 2)
				if (BF(T->left) >= 0)
					T = LL(T);
				else
					T = LR(T);
		}
		else
			if (x < T->data)
			{
				T->left = Delete(T->left, x);
				if (BF(T) == -2)	//Rebalance during windup
					if (BF(T->right) <= 0)
						T = RR(T);
					else
						T = RL(T);
			}
			else
			{
				//data to be deleted is found
				if (T->right != NULL)
				{	//delete its inorder succesor
					p = T->right;

					while (p->left != NULL)
						p = p->left;

					T->data = p->data;
					T->right = Delete(T->right, p->data);

					if (BF(T) == 2)//Rebalance during windup
						if (BF(T->left) >= 0)
							T = LL(T);
						else
							T = LR(T);
				}
				else
					return(T->left);
			}
	T->ht = height(T);
	return(T);
}