#pragma once
#include <stdio.h>

struct BstNode {
	int data;
	BstNode* left;
	BstNode* right;
};

struct sNode {
	struct BstNode *t;
	struct sNode *next;
};