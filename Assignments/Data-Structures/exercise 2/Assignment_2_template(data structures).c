#include <stdio.h>
#include <stdlib.h>
#include "Header2.h"
#define MAX 25

/*
Assigned by:
Dor_Bitton #203285630
*/


/* ------- Exercise Function declarations ------- */

void Ex1();
void Ex2();


void create_stack(Stack *ps);
int pop(Stack *ps, stack_type *px);
int push(stack_type x, Stack *ps);


Node * build_empty_linked_list();
void sort_polynomial(Node *head);
Node *push_at_element(Node *head_ref, int power, int coefficient);
Node *push_element(Node *head_ref, int power, int coefficient);
void free_list(Node *head_ref);
Node *substract_two_polynomials(Node *P1, Node *P2);
Node *add_two_polynomials(Node *P1, Node *P2);
void print_linked_list(Node *head_ref);
Node *zero_poly(Node *head_ref);
int highest_power(Node *head_ref);
Node *multiply_poly(Node *head_ref, int C);



/* -------- Stack Function Implementing --------- */

void create_stack(Stack  *ps) {
	ps->top = -1;
}

int pop(Stack *ps, stack_type *px) {
	if (ps->top >= 0) {
		ps->S[ps->top] = NULL; //Reset memory for debugging comfort
		*px = ps->S[ps->top--];
		return 1;
	}
	return 0;
}

int push(stack_type x, Stack *ps) {
	if (ps->top < MAX - 1) {
		ps->top++;
		ps->S[ps->top] = x;
		return 1;
	}
	return 0;
}


/* ------ LinkedList Function Implementing ------- */


Node * build_empty_linked_list() {
	Node *newNode = (Node*)malloc(sizeof(Node));
	if (!newNode) {
		return NULL;
	}
	newNode->power = 0;
	newNode->coefficient = 0;
	newNode->next = NULL;
	newNode->prev = NULL;

	printf("\n [+] Empty Polynomial created \n \n");

	return newNode;
}


void sort_polynomial(Node *head) {
	Node *index = NULL;
	Node *current = head;
	int tempP, tempC;

	if (head == NULL || (head->coefficient == 0 && head->power == 0)) {
		return;
	}
	else {
		while (current != NULL) {
			index = current->next;

			while (index != NULL) {
				if (current->power > index->power) {
					tempP = current->power;
					tempC = current->coefficient;
					current->power = index->power;
					current->coefficient = index->coefficient;
					index->power = tempP;
					index->coefficient = tempC;
				}
				index = index->next;
			}
			current = current->next;
		}
	}
}

Node *push_at_element(Node *head_ref, int power, int coefficient) {
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->power = power;
	temp->coefficient = coefficient;
	head_ref = head_ref->next;
	temp->next = head_ref;

	return temp;
}


//At print function ex it shows as an example from highest power to lowest.
//At the start of the exercise it says the opposite.
//I did it from the highest to lowest as it showed in example. 
Node *push_element(Node *head_ref, int power, int coefficient) {
	Node *temp = (Node*)malloc(sizeof(Node));
	Node *index = (Node*)malloc(sizeof(Node));
	temp->coefficient = coefficient;
	temp->power = power;
	temp->next = NULL;
	temp->prev = NULL;

	while (1) {
		if (temp->power == head_ref->power) {
			head_ref->coefficient += coefficient;
		}
		else if (temp->power > head_ref->power) {
			temp->next = head_ref;
		}
		else if (temp->power < head_ref->power) {
			index = head_ref;
			while (temp->power < head_ref->power) {
				if (temp->power < head_ref->power && temp->power > head_ref->next->power) {
					head_ref->next = push_at_element(head_ref, power, coefficient);
					temp = index;
					break;
				}
				head_ref = head_ref->next;

				if (temp->power == head_ref->power) {
					head_ref->coefficient += coefficient;
					temp = index;
					break;
				}

			}
		}
		break;
	}
	return temp;
}

void free_list(Node *head_ref) {
	Node *to_free = head_ref;
	while (to_free != NULL) {
		head_ref = head_ref->next;
		free(to_free);
		to_free = head_ref;
	}
}

Node *substract_two_polynomials(Node *P1, Node *P2) {
	Node *temp = (Node*)malloc(sizeof(Node));
	temp = P1;

	while (P1 != NULL && P2 != NULL) {
		if (P1->power == P2->power) {
			P1->coefficient -= P2->coefficient;
			if (P1->coefficient == 0)
				P1->power = 0;
			P1 = P1->next;
			P2 = P2->next;

		}
		else if (P1->power > P2->power) {
			P1 = P1->next;
		}
		else if (P1->power < P2->power) {
			temp = push_element(temp, P2->power, -(P2->coefficient));
			P2 = P2->next;
		}
	}

	return temp;
}

Node *add_two_polynomials(Node *P1, Node *P2) {
	Node *temp = (Node*)malloc(sizeof(Node));
	temp = P1;

	while (P1 != NULL && P2 != NULL) {
		if (P1->power == P2->power) {
			P1->coefficient += P2->coefficient;
			P1 = P1->next;
			P2 = P2->next;
		}
		else if (P1->power > P2->power) {
			P1 = P1->next;
		}
		else if (P1->power < P2->power) {
			temp = push_element(temp, P2->power, P2->coefficient);
			P2 = P2->next;
		}
	}

	return temp;
}

void print_linked_list(Node *head_ref)
{
	int flag = 0;
	printf("\Polynomial is:\t");

	if (head_ref->coefficient == 0 && head_ref->power == 0) {
		printf("Zero (Empty Polynomial) \n\n");
		return;
	}

	while (head_ref != NULL) //NEED TO FIX STATMENT
	{
		if (head_ref->power == 0) {
			if (head_ref->coefficient > 0) {
				printf("+%d", head_ref->coefficient);
				break;
			}
			else if (head_ref->coefficient < 0) {
				printf("-%d", head_ref->coefficient);
			}
		}
		else if (head_ref->power == 1) {
			if (head_ref->coefficient > 0)
				printf("+%dX", head_ref->coefficient);
			else
				printf("%dX", head_ref->coefficient);

		}
		else if (head_ref->power > 0) {
			if (head_ref->coefficient == 1) {
				printf("+X^%d", head_ref->power);
			}
			else if (head_ref->coefficient == -1) {
				printf("-X^%d", head_ref->power);
			}
			else if (head_ref->coefficient > 1) {
				if (flag == 0) {
					printf("%dX^%d", head_ref->coefficient, head_ref->power);
					flag++;
				}
				else
					printf("+%dX^%d", head_ref->coefficient, head_ref->power);
			}
			else if (head_ref->coefficient < -1) {
				printf("%dX^%d", head_ref->coefficient, head_ref->power);
			}
		}

		head_ref = head_ref->next;
	}
	printf("\n\n");
}

Node *zero_poly(Node *head_ref) {
	Node *current = head_ref;
	if (current == NULL)
		return NULL;

	free_list(head_ref);
	head_ref->coefficient = 0;
	head_ref->power = 0;
	head_ref->next = NULL;
	head_ref->prev = NULL;

	return current;
}

int highest_power(Node *head_ref) {
	int highest = 0;
	if (head_ref == NULL)
		return 0;

	for (; head_ref != NULL; head_ref = head_ref->next) {
		if (head_ref->power > highest)
			highest = head_ref->power;
	}

	if (highest == 0)
		return -1;

	return highest;

}

Node *multiply_poly(Node *head_ref, int C) {
	Node *temp = head_ref;
	if (head_ref == NULL)
		return 0;

	if (C == 0) {
		zero_poly(head_ref);
		return temp;
	}

	for (; head_ref != NULL; head_ref = head_ref->next) {
		head_ref->coefficient *= C;
	}
	return temp;
}


int main()
{
	int select = 0, i, all_Ex_in_loop = 0;

	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
	if (scanf_s("%d", &all_Ex_in_loop) == 1)
		do
		{
			for (i = 1; i <= 2; i++)
				printf("Ex%d--->%d\n", i, i);
			printf("EXIT-->0\n");
			do {
				select = 0;
				printf("please select 0-2 : ");
				scanf_s("%d", &select);
			} while ((select < 0) || (select > 2));
			switch (select)
			{
			case 1: Ex1(); break;
			case 2: Ex2(); break;
			}
		} while (all_Ex_in_loop && select);
		return 0;
}


/* ----------- Function definitions ------------ */


/* ------------------ EX1 ---------------------- */

int isOperator(char x) {
	switch (x) {
	case '+':
		return 1;
	case '-':
		return 1;
	case '/':
		return 2;
	case '*':
		return 2;
	case '^':
		return 3;
	}

	return -1;
}


void print(char x, int flag) {
	if (flag == 0)
		printf("\nOperation\t Operand1\t Operand2\t Result\n");
	else
		printf("    %c\t\t", x);
}


void arrange_stacks_ex1(char *s) {
	Stack s1, s2;
	int i = 0, letter = 0, flag = 0;
	char temp = NULL;
	char resultToPush = 'Z';
	create_stack(&s1);
	create_stack(&s2);

	print(NULL, flag);
	flag++;

	while (s[i] != '\0' && i < MAX - 1) {
		if (isOperator(s[i]) != -1) {
			if (isOperator(s[i]) > isOperator(s2.S[s2.top])) {
				push(s[i], &s2);
			}
			else if (isOperator(s[i]) == 3 && isOperator(s2.S[s2.top]) == 3) {
				push(s[i], &s2);
				i++;
				push(s[i], &s1);

			}
			else {
				while (isOperator(s[i]) <= isOperator(s2.S[s2.top]) && isOperator(s2.S[s2.top]) != -1) {
					print(s2.S[s2.top], flag);
					pop(&s2, &s2.S[s2.top]);

					print(s1.S[s1.top - 1], flag);
					temp = s1.S[s1.top];
					pop(&s1, &s1.S[s1.top]);

					print(temp, flag);
					pop(&s1, &s1.S[s1.top]);

					push((resultToPush - letter), &s1);
					print(s1.S[s1.top], flag);
					letter++;

					printf("\n");
				}
				push(s[i], &s2);

			}
		}
		else
			push(s[i], &s1);
		i++;
	}


	while (s2.S[s2.top] != -1) {
		print(s2.S[s2.top], flag);
		pop(&s2, &s2.S[s2.top]);

		print(s1.S[s1.top - 1], flag);
		temp = s1.S[s1.top];
		pop(&s1, &s1.S[s1.top]);

		print(temp, flag);
		pop(&s1, &s1.S[s1.top]);

		push((resultToPush - letter), &s1);
		print(s1.S[s1.top], flag);
		letter++;

		printf("\n");
	}
}


void Ex1() {
	char s[MAX];

	printf("Enter the expression:");
	scanf_s("%s", s, MAX);

	arrange_stacks_ex1(s);
}


/* ------------------ EX2 ---------------------- */


void Ex2() {
	int choice, power, coefficient;
	Node *list = NULL, *list2 = NULL;

	while (1)
	{
		printf("  1 -- Create an empty Polynomial \n");
		printf("  2 -- Insert new element \n");
		printf("  3 -- Add two Polynomial \n");
		printf("  4 -- Substract two Polynomial \n");
		printf("  5 -- Multiply Polynomial with a number \n");
		printf("  6 -- Highest power of the Polynomial \n");
		printf("  7 -- Zero Polynomial \n");
		printf("  8 -- Display Polynomial \n");
		printf("  9 -- Quit \n");
		printf("Enter your choice: ");
		scanf_s("%d", &choice);
		switch (choice)
		{
		case 1:
			if (list == NULL)
				list = build_empty_linked_list();
			else
				list2 = build_empty_linked_list();
			break;

		case 2:
			if (list != NULL && list2 != NULL) {

				printf("Enter the coefficient of X: ");
				scanf_s("%d", &coefficient);
				printf("Enter the power of X: ");
				scanf_s("%d", &power);

				printf("Select a Polynomial to enter new element: (1 / 2)\t");
				scanf_s("%d", &choice);
				if (choice == 1) {
					list = push_element(list, power, coefficient);
					break;
				}
				if (choice == 2) {
					list2 = push_element(list2, power, coefficient);
					break;
				}

			}
			else {
				printf("Enter the coefficient of X: ");
				scanf_s("%d", &coefficient);
				printf("Enter the power of X: ");
				scanf_s("%d", &power);
				list = push_element(list, power, coefficient);
				break;
			}
		case 3:
			if (list == NULL || list2 == NULL) {
				printf("[-] Error: Got only one Polynomial. \n\n");
			}
			else
				list = add_two_polynomials(list, list2);
			free_list(list2);
			list2 = NULL;
			break;

		case 4:
			if (list == NULL || list2 == NULL) {
				printf("[-] Error: Got only one Polynomial. \n\n");
			}
			else
				list = substract_two_polynomials(list, list2);
			free_list(list2);
			list2 = NULL;
			break;

		case 5:
			int C;
			printf("Enter the number you wish to multiply: \t");
			scanf_s("%d", &C);
			if (list != NULL && list2 == NULL) {
				list = multiply_poly(list, C);
				break;
			}
			else {
				printf("Select a Polynomial to check highest power: (1 / 2)\t");
				scanf_s("%d", &choice);
				if (choice == 1) {
					list = multiply_poly(list, C);
					break;
				}
				if (choice == 2) {
					list2 = multiply_poly(list2, C);
					break;
				}

			}
			break;

		case 6:
			int highest;
			if (list != NULL && list2 == NULL) {
				highest = highest_power(list);
				printf("Highest power: %d \n", highest);
				break;
			}
			else {
				printf("Select a Polynomial to check highest power: (1 / 2)\t");
				scanf_s("%d", &choice);
				if (choice == 1) {
					highest = highest_power(list);
					printf("Highest power: %d \n\n", highest);
					break;
				}
				if (choice == 2) {
					highest = highest_power(list2);
					printf("Highest power: %d \n\n", highest);
					break;
				}

			}
			break;

		case 7:
			if (list != NULL && list2 == NULL)
				list = zero_poly(list);
			else {
				printf("Select a Polynomial to zero out: (1 / 2)\t");
				scanf_s("%d", &choice);
				if (choice == 1) {
					list = zero_poly(list);
					break;
				}
				if (choice == 2) {
					list2 = zero_poly(list2);
					break;
				}

			}
			break;

		case 8:
			if (list != NULL && list2 == NULL)
				print_linked_list(list);
			if (list != NULL && list2 != NULL) {
				printf("\nThere are 2 Polynomials lists:\n");
				print_linked_list(list);
				print_linked_list(list2);
				printf("\n");
			}
			break;

		case 9:
			return;
			break;

		default:
			printf("Wrong choice \n");
			break;

		}


	}
}