#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct Nod
{
	int valoare;
	struct Nod* link;
};

void adaugaNod(struct Nod** head, int valoare_noua)
{
	struct Nod* nodNou = (struct Nod*)malloc(sizeof(struct Nod));
	nodNou->link = NULL;
	nodNou->valoare = valoare_noua;

	if (*head == NULL)
	{
		*head = nodNou;
	}
	else
	{
		struct Nod* pointer = (*head);

		while (pointer->link != NULL)
		{
			pointer = pointer->link;
		}

		pointer->link = nodNou;
	}
}

void citesteListaDinFisier(char* numeFisier, struct Nod* head)
{
	FILE* f = fopen(numeFisier, "r");

	if (f == NULL)
	{
		printf("Nu exista fisierul!");
		return;
	}
	else
	{
		int n;
		char buffer[100];
		char delimitator[] = " \n";

		while (fgets(buffer, 100, f))
		{
			char* token;
			char* context = NULL;
			token = strtok_s(buffer, delimitator, &context);
			n = atoi(token);
			adaugaNod(&head, n);
		}
	}
}

void printList(struct Nod* head)
{
	struct Nod* temp = head;

	//iterate the entire linked list and print the data
	while (temp != NULL)
	{
		printf("%d->", temp->valoare);
		temp = temp->link;
	}
	printf("NULL\n");
}

void main()
{
	struct Nod* head = NULL;

	//citesteListaDinFisier("liste.txt", head);
	adaugaNod(&head, 1);
	adaugaNod(&head, 2);
	printList(head);
}