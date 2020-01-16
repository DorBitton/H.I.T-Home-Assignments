#pragma once
#include <stdio.h>
//Structs for EX3
typedef struct values{
	int value;
	int i;
	int j;
}values;

typedef struct node {
	values data;
	struct node *next;
}node;

typedef struct result {
	node *lst;
	node **arr;
	int lenght;
}result;

//Structs for EX4
 typedef struct numbers {
	int num;
	struct numbers *next;
}numbers;

 typedef numbers* list;
 typedef int list_type;

 //Global variables for EX5
 struct numbers *head = NULL;
 struct numbers *secondListHead = NULL;