#define MAX 25
//EX1
typedef char stack_type;
typedef struct {
	int top;
	stack_type S[MAX];
}Stack;

//Ex2
struct Node
{
	int coefficient;
	int power;
	struct Node *next;
	struct Node *prev;
};



