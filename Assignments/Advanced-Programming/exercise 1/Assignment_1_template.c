#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#define R  3
#define C  3

/*
Assigned by:
Dor_Bitton #
*/

/* Function declarations */

void Ex1();
void Ex2();
void Ex3();
void Ex4();
void Ex5();



int main()
{
	int select = 0, i, all_Ex_in_loop = 0;

	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
	if (scanf_s("%d", &all_Ex_in_loop) == 1)
		do
		{
			for (i = 1; i <= 5; i++)
				printf("Ex%d--->%d\n", i, i);
			printf("EXIT-->0\n");
			do {
				select = 0;
				printf("please select 0-5 : ");
				scanf_s("%d", &select);
			} while ((select < 0) || (select > 5));
			switch (select)
			{
			case 1: Ex1(); break;
			case 2: Ex2(); break;
			case 3: Ex3(); break;
			case 4: Ex4(); break;
			case 5: Ex5(); break;
			}
		} while (all_Ex_in_loop && select);
		return 0;
}


/* Function definitions */

//EX1
void printArray(unsigned int *a, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int Power(int base, int exponent) {
	int result = 1;
	int modulo = 32;
	exponent = exponent % modulo;

	if (exponent == 0) {
		return result;
	}

	while (exponent != 0) {
		result *= base;
		--exponent;
	}
	return result;
}

unsigned int * powerArray(int n) {
	int i;
	unsigned int *p;
	p = (unsigned int*)calloc(n, sizeof(unsigned int));
	if (p == NULL) { // Memory allocation fails
		printf("Not enough memory./n returning to main menu");
		return NULL;
	}

	for (i = 0; i < n; i++) {
		p[i] = Power(2, i);
	}
	return p;
}

void Ex1(){
	int n;
	unsigned int *p;
	printf("Enter the size of the array: ");
	scanf_s("%d", &n);

	p = powerArray(n);
	printArray(p, n);

}

//Ex2
void matrixInput(int mat[R][C])
{
	int r, c;
	for (r = 0; r < R; r++) {
		for (c = 0; c < C; c++) {
			scanf_s("%d", &mat[r][c]);
		}
	}
}
void matrixPrint(int mat[R][C]){
	int r, c;
	for (r = 0; r < R; r++) {
		for (c = 0; c < C; c++) {
			printf("%d", mat[r][c]);
			printf("\t");
		}
		printf("\n");
	}
}

void matrixDinPrint(int **a, int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++) {
			printf("%d", a[i][j]);
			printf("\t");
		}
		printf("\n");
	}
}

int * matrixMultiplication(int matrixA[R][C], int matrixB[R][C]) {
	int **a, i,r,c,k;
	a = (int**)calloc(R, sizeof(int*));
	for (i = 0; i < R; i++) {
		a[i] = (int*)calloc(C, sizeof(int));
	}

	for (r = 0; r < R; ++r) {
		for (c = 0; c < C; ++c) {
			for (k = 0; k < C; ++k) {
				a[r][c] += matrixA[r][k] * matrixB[k][c];
			}
		}
	}
	printf("Matrix multiplication result:\n");
	matrixDinPrint(a, R, C);
	
	return *a;
}

void Ex2(){
	int matrixA[R][C];
	int matrixB[R][C];
	int *dynamicMatrix = NULL;
	

	printf("Input matrix A: ");
	matrixInput(matrixA);
	printf("Matrix A is:\n");
	matrixPrint(matrixA);
	printf("Input matrix B: ");
	matrixInput(matrixB);
	printf("Matrix B is:\n");
	matrixPrint(matrixB);

	dynamicMatrix = matrixMultiplication(matrixA, matrixB);



}

//EX3
values createThree(int value, int i, int j) { // Struct values
	values dt;
	dt.value = value;
	dt.i = i;
	dt.j = j;
	printf("Value:%d, I:%d, J:%d\n", value, i, j);
	return dt;
}

node *&createThreeList(int **a, int row, int col) { //Creating Linked List
	node *lst, *curr_point;
	int r, c;
	lst = (node*)malloc(sizeof(node));
	curr_point = lst;
	for (r = 0; r < row; r++) {
		for (c = 0; c < col; c++) {
			if (r + c == a[r][c]) {
				lst->data = createThree(a[r][c], r, c);
				c++;
				break; // Found the first value.
			}
		}
		break;
	}

	while(r<row) {
		if (r + c == a[r][c]) {
			curr_point->next = (node*)malloc(sizeof(node));
			curr_point = curr_point->next;
			curr_point->data = createThree(a[r][c], r, c);
		}
		c++;
		if (c == col) {
			c = 0;
			r++;
		}
	}

	curr_point->next = NULL;
	return lst;
}

int listSize(node *lst) //Size of Linked List
{
	int n = 0;

	while (lst != NULL)
	{
		n++;
		lst = lst->next;
	}
	return n;
}

node **&createThreeArr(struct node *lst, int n) { // Creating the array from Linked list
	struct node **structArray = NULL;
	int i;
	structArray = (node**)calloc(n, sizeof(node));
	for (i = 0; i < n; i++) {
		structArray[i] = lst;
		lst++;
	}
	return structArray;
}


result *createArrayAndList(int **a, int row, int col) {
	int n;
	node *list;
	result* r;
	node **array;
	list = createThreeList(a, row, col);
	n = listSize(list);
	printf("\nSize of list:%d\n", n);
	array = createThreeArr(list, n);
	r = (result*)malloc(sizeof(result));
	r->arr = array;
	r->lenght = n;
	r->lst = list;
	
	return r;
}

int **createDynamicMatrix(int row, int col) {
	int i;
	int r, c;
	int **a;

	a = (int**)calloc(row, sizeof(int*));
	for (i = 0; i < row; i++) {
		a[i] = (int*)calloc(col, sizeof(int));
	}

	for (r = 0; r < row; r++) {
		for (c = 0; c < col; c++) {
			scanf_s("%d", &a[r][c]);
		}
	}
	printf("\nMatrix is:\n");
	matrixDinPrint(a, row, col);
	printf("\n");
	return a;
}


void Ex3(){
	int row=0, col = 0;
	int **arrayPointer;
	result *r;

	printf("Enter the number of rows: ");
	scanf_s("%d", &row);
	printf("Enter the number of colums: ");
	scanf_s("%d", &col);

	printf("\nInsert Matrix:\n");
	arrayPointer = createDynamicMatrix(row, col);
	r = createArrayAndList(arrayPointer, row, col);

	//Free dynamic Matrix
	int i = 0;
	for (i = 0; i < row; i++) {
		free(arrayPointer[i]);
	}
	free(arrayPointer);

	//result *r : contains all the values we need in a struct.
	//r.lenght = the lenght of linked list. (By value)
	//r.arr = pointer to array. (By reference)
	//r.lst = pointer to list. (By reference)
	//According to excercise.
}

//Ex4

void displayLinkedList(numbers * head) {
	numbers *p = NULL;
	if (head == NULL)
		printf("\nList is empty");
	else {
		p = head;
		while (p != NULL) {
			printf("%d->", p->num);
			p = p->next;
		}
		if (p == NULL)
			printf("NULL\n");
	}
}

void Delete(numbers *pos, list *pl)
{
	numbers *temp;
	if (!(*pl)) return; // empty list
	if (!pos) // delete the first item
	{
		temp = *pl;
		*pl = temp->next;
		free(temp);
	}
	else  if (pos->next) // delete the second or other items
	{
		temp = pos->next;
		pos->next = temp->next;
		free(temp);
	}
}

numbers *Insert(list_type x, numbers *pos, list *pl){
	numbers *temp = (numbers *)malloc(sizeof(numbers));
	if (!temp) return NULL;
	temp->num = x;
	if (!pos || !(*pl)) // insert into head or list is empty
	{
		temp->next = *pl;
		*pl = temp;
	}
	else // insert into middle (or end)
	{
		temp->next = pos->next;
		pos->next = temp;
	}
	return temp;
}


numbers *createList(numbers *originList) {
	numbers *newList = NULL;
	numbers *lst = NULL;
	numbers *delLst = NULL;
	numbers *stepper = originList;

	while (stepper != NULL) {
		if (stepper->num % 2 == 1) {
			newList = Insert(stepper->num, newList, &lst);
		}
		stepper = stepper->next;
	}
	newList = lst;

	while (originList != NULL) {
		if (originList->num % 2 == 1) {
			Delete(delLst, &originList);
		}
		else {
			break;
		}
	}
	delLst = originList;
	while (delLst->next != NULL) {
		if (delLst->next->num % 2 == 1) {
			Delete(delLst, &originList);
		}
		else {
			delLst = delLst->next;
		}
			
	}
	printf("origin linked list after changes:  ");
	displayLinkedList(originList);

	return newList;
}



numbers * originalLinkedList() {
	numbers *lst, *curr_point;
	int n;

	printf("Enter the Linked list, -1 to end list:\n");
	scanf_s("%d", &n);
	if (n < 0)
		return NULL;
	// processing of the first item
	lst = (numbers*)malloc(sizeof(numbers));
	curr_point = lst;
	lst->num = n;
	// processing of the second and other items
	scanf_s("%d", &n);
	while (n > 0) {
		curr_point->next = (numbers*)malloc(sizeof(numbers));
		curr_point = curr_point->next;
		curr_point->num = n;
		scanf_s("%d", &n);
	}

	curr_point->next = NULL;
	return lst;
}

void Ex4() {
	numbers *originList = NULL;
	numbers *pointerToUnEvenList;

	originList = originalLinkedList();

	printf("Original Linked List:  ");
	displayLinkedList(originList);
	pointerToUnEvenList = createList(originList); // Pointer of the new list
	printf("Uneven numbers linked list:  ");
	displayLinkedList(pointerToUnEvenList);

}



void createList2() {
	struct numbers *temp = head;
	struct numbers *listHolder1 = NULL;
	struct numbers *listHolder2 = NULL;
	struct numbers *originListHolder = NULL;
	struct numbers *stepper;

	while (temp != NULL) {
		if (temp->num % 2 == 1) {
			stepper = (numbers*)malloc(sizeof(numbers));

			stepper->num = temp->num;
			stepper->next = NULL;

			if (secondListHead == NULL) {
				secondListHead = stepper;
			}
			else {
				listHolder1->next = stepper;
			}
			listHolder1 = stepper;
		}
		else {
			stepper = (numbers*)malloc(sizeof(numbers));

			stepper->num = temp->num;
			stepper->next = NULL;

			if (originListHolder == NULL) {
				originListHolder = stepper;
			}
			else {
				listHolder2->next = stepper;
			}
			listHolder2 = stepper;
		}
		temp = temp->next;
	}
	head = originListHolder;
}



void Ex5(){
	head = originalLinkedList();

	printf("Original Linked List:  ");
	displayLinkedList(head);

	createList2();
	printf("Uneven numbers linked list:  ");
	displayLinkedList(secondListHead);
	printf("origin linked list after changes:  ");
	displayLinkedList(head);


}

/* ------------------- */
