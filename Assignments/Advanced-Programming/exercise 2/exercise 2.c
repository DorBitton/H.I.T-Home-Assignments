#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h> 
#include <ctype.h>
#define MAX 54

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

// function to free matrix, but im getting a msg:"loading symbols for combase.dll"
// couldnt find online solution that works for me.
void free_matrix(char **str, int n)
{
	int i;
	for (i = 0; i < n; i++)
		free(str[i]);
	free(str);
}

void print_matrix(char **str, int rows) {
	int i, j;
	if (str == NULL) {
		printf("Nothing to print.");
		return;
	}

	for (i = 0; i < rows; i++)
	{
		printf("[+]	");
		j = 0;
		while (str[i][j] != '\0')
		{
			printf("%c", str[i][j]);
			j++;
		}
		printf("\n\n");
	}
}

int words_lenght_counter(char *str) {
	int counter = 0;

	while (*str != ' ' && *str != '\0') {
		counter++;
		str++;
	}
	return counter;
}

int number_of_words(char *str, char letter) {
	int counter = 0;
	if (*str == letter)
		counter++;
	str++;

	while (*str) {
		if (*str == ' ') {
			str++;
			if (*str == letter || (int)*str == (int)letter - 32)
				counter++;
		}
		str++;
	}
	return counter;
}

char **split(char *str, char letter, int *rows) {
	int cols, i = 0, c = 0, j = 0;
	*rows = number_of_words(str, letter);
	char **temp = (char**)calloc(*rows, sizeof(char*));

	// First letter check
	if (*str == letter || (int)*str == (int)letter - 32) { // == letter, or == Uppercase letter.((int) for Ascii convertion)
		cols = words_lenght_counter(str);
		temp[i] = (char*)calloc(cols - i + 1, sizeof(char));
		temp[i][cols] = '\0';
		while (*str != ' ') {
			temp[i][c] = *str;
			str++;
			c++;
		}
		c = 0;
		i++;
	}
	else
		str++;

	// Rest of the string check
	while (*str) {
		if (*str == ' ') {
			str++;
			if ((int)*str == (int)letter - 32 || *str == letter) {
				cols = words_lenght_counter(str);
				temp[i] = (char*)calloc(cols - i + 1, sizeof(char));
				temp[i][cols] = '\0';
				while (*str != ' ' && *str != '\n') {
					temp[i][c] = *str;
					str++;
					c++;
				}
				c = 0;
				i++;
			}
		}
		else
			str++;

	}
	return temp;
}

void Ex1() {
	char str[MAX], letter;
	int size_matrix;
	char **ptr;

	printf("Enter the string:	");
	while ((getchar() != '\n')); // clear buffer. "fflush(stin)" unsafe.
	fgets(str, MAX, stdin); // the slide shows says use "gets" to input strings. "gets" Can cause buffer overflow! So I had to use different method.

	printf("Enter the letter to check:	");
	letter = getchar();

	ptr = split(str, letter, &size_matrix);
	printf("There are %d words that start with the letter '%c':	\n", size_matrix, letter);
	print_matrix(ptr, size_matrix);
	//free_matrix(ptr, size_matrix);
	// ^^ function to free matrix, but im getting a msg:"loading symbols for combase.dll"
	// couldnt find online solution that works for me.
}

void clearDigitsAndSpaces(char *str) {
	const char* d = str;
	do {
		while (*d == ' ' || isdigit(*d)) { // isdigit function is in <ctype.h> library
			++d;
		}
	} while (*str++ = *d++);

}

void Ex2() {
	char newString[MAX];

	printf("Enter the string:	");
	while ((getchar() != '\n')); // clear buffer. "fflush(stin)" unsafe.
	fgets(newString, MAX, stdin); //ALL of the slide shows says use "gets" to input strings. "gets" Can cause buffer overflow! So I had to use different method.


	clearDigitsAndSpaces(newString);
	printf("String without spaces and numbers:	");
	printf("%s\n", newString);
}

char commonestLetter(char *fileName) {
	char ch;
	int i, count[26];
	int max = 0, location;
	FILE *f = fopen(fileName, "r");

	if (f == NULL) {
		return NULL;
	}

	memset(&count, 0, sizeof(count));
	while ((ch = fgetc(f)) != EOF) {
		if (isalpha(ch))
			count[toupper(ch) - 'A']++; // The toupper() function is used to convert lowercase alphabet to uppercase
	}

	for (i = 0; i < 26; i++) {
		if (count[i] >= max) {
			max = count[i];
			location = i;
		}
	}

	fclose(f);

	if (max == 0)
		return NULL;
	else
		return location + 'A';
}

void createFilechar(char *fileName) {
	char str[101];
	FILE *fp;

	printf("Enter the string to write in %s: \n", fileName);
	scanf("%s", str);

	fp = fopen(fileName, "w");
	fputs(str, fp);
	fclose(fp);
}


void Ex3() {
	int i;

	//Integer for paragraph 1
	char fileName[] = "input.txt";

	//Integer for paragraph 2
	char ch;

	printf("\n     ------ Menu for exc 3: ------     \n\n");
	printf("[+] For 'createFile' function type: 1 \n");
	printf("[+] For 'commonestLetter' function type: 2 \n\n");
	printf("Input:	"); scanf("%d", &i);

	switch (i)
	{
	case 1: createFilechar(fileName); break;
	case 2: ch = commonestLetter(fileName);
		if (ch)
			printf("The most common letter is: %c	\n", ch);
		else
			printf("No letters in the file\n");
		break;
	}
}

const char * decode(char *str) {
	int i, j = 0, pos = 0, decoder = -1;
	char newString[MAX];

	while (*str != '\0') {
		i = words_lenght_counter(str);
		for (j = 0; j < i; j++) {
			newString[pos] = (int)*str + decoder;
			str++;
			pos++;
			decoder--;
		}

		decoder = -1;
		while (*str == ' ') {
			newString[pos] = ' ';
			str++;
			pos++;
		}
	}

	return newString;

}

void Ex4() {
	char str[54] = "Btwlzx Dqqes Eq|pj2 Tjhvqujs Iqoqjy bpg Eqfxtx Xcwwtt";
	const char *str2;
	int i = 0;

	printf("Original string:	");
	puts(str);

	str2 = decode(str);
	for (i = 0; i < MAX; i++) {
		str[i] = *str2;
		str2++;
		if (i == 53) //I know the size of str, because there is no need to input the string.
			str[i] = '\0';
	}

	printf("Decryption of string:	");
	puts(str);
}
int sizeOfArray(char *str, int *i) {
	int size = 0;

	if (str[*i] != '\0') {
		if (str[*i] != '[') { //Not array
			(*i)++;
			return 1;
		}
		(*i)++;
		while (str[*i] != ']') {
			size = size * 10 + (str[*i] - '0');
			(*i)++;
		}
		(*i)++;
		if (str[*i] == '=') {
			while (str[*i] != '}' && str[*i] != '"')
				(*i)++;
		}
		while (str[*i] != ';' && str[*i] != ',')
			(*i)++;
		(*i)++;
	}

	return size;
}

void readAndWriteFile(char* filename)
{
	FILE *file;
	if (!(file = fopen(filename, "r"))) { // read only check
		printf("Can't open file!");
		return;
	}
	while (!(feof(file)))
		printf("%c", fgetc(file));
	fclose(file);
}

void memoryReport(char *str, char *filename) {
	int i = 0, size;
	int checkPointer = 0;
	char typeOf;
	FILE *file;
	if (!(file = fopen(filename, "w"))) { // if cant create file -> return
		printf("Can't open file!\n");
		return;
	}
	while (!isalpha(str[i])) // The isalpha() function checks whether a character is an alphabet or not.
		i++;
	typeOf = str[i]; // first letter
	switch (typeOf) // checking what kind of variable it is, by the first letter
	{
	case 'c': { size = sizeof(char);   i += 4; break; }
	case 'i': { size = sizeof(int);    i += 3; break; }
	case 'd': { size = sizeof(double); i += 6; break; }
	case 'f': { size = sizeof(float);  i += 5; break; }
	case 's': { size = sizeof(short);  i += 5; break; }
	default: i += 5; // if non of the above, probably a long type
	{
		if (str[i++] == 'l' && str[i + 2] == 'g') { // checking for long long type
			size = sizeof(long long);
			break;
		}
		i = 4;
		size = sizeof(long);
		break;
	}

	}
	while (str[i] != '\0')
	{
		if (str[i] == '*' || checkPointer == 1) //pointer checking
			checkPointer = 1;
		else
			checkPointer = 0;

		if (isalpha(str[i])) {
			while (str[i] != ',' && str[i] != ';' && str[i] != '[') {
				if (str[i] == '=') {
					while (str[i] != ';' && str[i] != ',') {
						i++;
						break;
					}
				}
				if (str[i] != ' ') {
					fputc(str[i], file);
					i++;
				}
				else
					i++;
			}
			if (checkPointer == 1) { //pointer
				fputs(" requires 4 bytes\n", file);
				i++;
				checkPointer = 0;
			}
			else {
				fputs(" requires ", file);
				fprintf(file, "%d", size * sizeOfArray(str, &i));
				fputs(" bytes\n", file);
			}
		}
		else
			i++;
	}
	fclose(file);
	readAndWriteFile(filename);
}

char* inputstring(void)
{
	char temp[MAX], *str2;
	int size;
	fgets(temp, sizeof(temp), stdin); //The slide shows says use "gets" to input strings. "gets" Can cause buffer overflow! So I had to use different method.
	size = strlen(temp);
	str2 = (char*)malloc(size * sizeof(char));

	temp[size - 1] = '\0'; // instead of '\n' because of fgets function.

	strcpy(str2, temp);
	return str2;
}


void Ex5() {
	char *declaration, *filename;
	while ((getchar() != '\n')); // clear buffer before input fucntions. "fflush(stin)" unsafe.
	printf("Enter Declaration:	");
	declaration = inputstring();
	printf("Enter file name (with extansion):	");
	filename = inputstring();
	memoryReport(declaration, filename);

	free(declaration);
	free(filename);
}
