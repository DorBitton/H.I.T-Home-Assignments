#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

/*
Assigned by:
Dor_Bitton #
Class number: 0061104-61
*/

/* Function declarations */

BstNode* buildBST_Ex1();
void printBST_Ex2(BstNode *root);
void printBSTUpDown_Ex3(BstNode *root);
void freeTree_Ex4(BstNode* root);

/* ------------------------------- */



int main()
{
	BstNode *root = NULL;
	int select = 0, i, all_Ex_in_loop = 0;

	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
	if (scanf_s("%d", &all_Ex_in_loop) == 1)
		do
		{
			printf("\n--------------- Main Menu ---------------\n");
			printf("1--->\tBuild BST\n");
			printf("2--->\tPrint BST inorder\n");
			printf("3--->\tPrint BST from Root to bottom\n");
			printf("4--->\tFree BST\n");
			printf("EXIT-->\t0\n");
			do {
				select = 0;
				printf("please select 0-4 : ");
				scanf_s("%d", &select);
			} while ((select < 0) || (select > 4));
			switch (select)
			{
			case 1:
				if (root != NULL)
					freeTree_Ex4(root);
				root = buildBST_Ex1();
				break;
			case 2: printBST_Ex2(root); break;
			case 3: printBSTUpDown_Ex3(root); break;
			case 4: 
				freeTree_Ex4(root);
				root = NULL; // make root NULL so ex1 can rebuild BST
				break;
			}
		} while (all_Ex_in_loop && select);

		freeTree_Ex4(root);
		root = NULL;
		return 0;
}


/* Function definitions */
BstNode* GetNewNode(int data) { // build new node
	BstNode* newNode = (BstNode*)malloc(sizeof(BstNode));
	(*newNode).data = data;
	(*newNode).left = (*newNode).right = NULL;

	return newNode;
}

BstNode* Insert(BstNode* root, int data) { // using recursion
	if (root == NULL) { // empty tree
		root = GetNewNode(data);
	}
	else if (data <= root->data){
		root->left = Insert(root->left, data);
	}
	else {
		root->right = Insert(root->right, data);
	}

	return root;
}


BstNode* buildBST_Ex1() { // build new Binary Search Tree
	int data = 0;
	BstNode *root = NULL;

	printf("\n[+] Building Binary Search Tree\n");
	printf("[+] Enter '-1' to end input.\n");
	while (data != -1) {
		printf("\tNumber to instert: ");
		scanf_s("%d", &data);

		if (data == -1) // end input
			break;

		root = Insert(root, data);
	}

	return root;
}

bool isEmpty(sNode *top) { // check if empty
	return (top == NULL) ? 1 : 0;
}

void push(sNode** top_ref, BstNode *t)
{
	struct sNode* new_tNode = (sNode*) malloc(sizeof(sNode));

	if (new_tNode == NULL)
	{
		printf("Stack Overflow \n");
		exit(0);
	}

	new_tNode->t = t;

	new_tNode->next = (*top_ref);

	(*top_ref) = new_tNode;
}

BstNode *pop(struct sNode** top_ref)
{
	struct BstNode *res;
	struct sNode *top;

	if (isEmpty(*top_ref))
	{
		printf("Stack Underflow \n");
		exit(0);
	}
	else
	{
		top = *top_ref;
		res = top->t;
		*top_ref = top->next;
		free(top);
		return res;
	}
}



void printInOrder(BstNode *root) {
	struct BstNode *current = root;
	struct sNode *s = NULL;
	int flag = 0;

	while (flag != -1) {
		if (current != NULL) {
			push(&s, current);
			current = current->left;
		}
		else {
			if (!isEmpty(s)) {
				current = pop(&s);
				printf("%d\t", current->data);

				current = current->right;
			}
			else {
				flag = -1;
			}
		}
	}

}

void printBST_Ex2(BstNode *root) { // used stack to solve
	if (root == NULL) {
		printf("[-] BST Empty!\n");
		return;
	}

	printf("\n[+] BST Inorder print:\n");
	printInOrder(root);
	printf("\n\n");

}

BstNode** createQueue(int *front, int *rear) {
	BstNode **queue = (BstNode**)malloc(sizeof(BstNode*));

	*front = *rear = 0;
	return queue;
}

void enQueue(BstNode **queue, int *rear, BstNode *newNode) { // using array
	queue[*rear] = newNode;
	(*rear)++;
}

BstNode *deQueue(BstNode **queue, int *front) { // using array
	(*front)++;
	return queue[*front - 1];
}


void printBSTUpDown_Ex3(BstNode *root) { // array implementation of Queue
	if (root == NULL) {
		printf("[-] BST Empty!\n");
		return;
	}

	int rear, front;
	struct BstNode **queue = createQueue(&front, &rear);
	struct BstNode *temp_node = root;

	printf("\n[+] BST from Root to bottom print:\n");
	while (temp_node)
	{
		printf("%d ", temp_node->data);

		// enqueue left
		if (temp_node->left)
			enQueue(queue, &rear, temp_node->left);

		// enqueue right 
		if (temp_node->right)
			enQueue(queue, &rear, temp_node->right);

		// new temp after dequeue
		temp_node = deQueue(queue, &front);
	}
	printf("\n\n");

}

void freeTree_Ex4(BstNode* root) {
	if (root == NULL) return;

	// recursive delete of subtrees
	freeTree_Ex4(root->left);
	freeTree_Ex4(root->right);

	// free root position
	free(root);
}

/* ------------------------------- */
