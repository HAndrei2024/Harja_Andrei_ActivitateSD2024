#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct Date Date;
typedef struct Nod Nod;
typedef struct Vecini Vecini;

struct Date
{
	int valoare;
};

struct Nod
{
	Nod* prev;
	Date date;
	Nod* next;
};

struct Vecini
{
	Nod* prev;
	Nod* next;
};

void citireLista(char* numeFisier, Nod** head, Nod** tail, int* nrElementeLista)
{
	FILE* f = fopen(numeFisier, "r");

	if (f == NULL)
	{
		printf("Nu exista fisierul!");

	}
	else
	{
		Date date;

		char buffer[128];
		char delimiter[] = "\n";
		char* token;

		while (fgets(buffer, 127, f))
		{
			char* secure = NULL;
			token = strtok_s(buffer, delimiter, &secure);

			date.valoare = atoi(token);

			Nod* nodNou;
			nodNou = (Nod*)malloc(sizeof(Nod));

			nodNou->date = date;
			nodNou->next = NULL;
			nodNou->prev = NULL;

			if ((*tail) == NULL)
			{
				(*tail) = nodNou;
				(*head) = nodNou;
			}
			else
			{
				Nod aux;
				(*tail)->next = nodNou;
				aux.next = (*tail);
				(*tail) = nodNou;
				nodNou->prev = aux.next;

			}
			(*nrElementeLista)++;
		}
	}
	
}

void printListHead(Nod* head)
{
	Nod* temp = head;

	while (temp != NULL)
	{
		printf("%d->", temp->date.valoare);
		temp = temp->next;
	}
	printf("NULL\n");
}
void printListTail(Nod* head)
{
	Nod* temp = head;

	while (temp != NULL)
	{
		printf("%d->", temp->date.valoare);
		temp = temp->prev;
	}
	printf("NULL\n");
}

Date stergeNod(Nod** head, Nod** tail, int* nrElementeLista, int indexDeSters)
{
	Date dateNodSters;
	dateNodSters.valoare = NULL;

	if (indexDeSters <= (*nrElementeLista) - 1)
	{
		if (indexDeSters == 0)
		{
			(*head) = (*head)->next;
			(*head)->prev = NULL;
		}
		else if (indexDeSters == (*nrElementeLista) - 1)
		{
			(*tail) = (*tail)->prev;
			(*tail)->next = NULL;
		}
		else
		{
			Nod* pointer = (*head);

			for (int i = 0; i < indexDeSters; i++)
			{
				pointer = pointer->next;
			}

			pointer->prev->next = pointer->next;
			pointer->next->prev = pointer->prev;
			dateNodSters = pointer->date;
			free(pointer);
		}
		(*nrElementeLista)--;
	}

	return dateNodSters;
}

void sortarePrinInserare(char* numeFisier, Nod** head, Nod** tail, int* nrElementeLista)
{
	FILE* f = fopen(numeFisier, "r");

	if (f == NULL)
	{
		printf("Nu exista fisierul!");

	}
	else
	{
		Date date;

		char buffer[128];
		char delimiter[] = "\n";
		char* token;

		while (fgets(buffer, 127, f))
		{
			char* secure = NULL;
			token = strtok_s(buffer, delimiter, &secure);

			date.valoare = atoi(token);

			Nod* nodNou;
			nodNou = (Nod*)malloc(sizeof(Nod));

			nodNou->date = date;
			nodNou->next = NULL;
			nodNou->prev = NULL;

			if ((*head) == NULL)
			{
				(*head) = nodNou;
				(*tail) = nodNou;
			}
			else
			{
				Nod* pointer = (*head);
				int done = 0;

				while (pointer != (NULL) && done == 0)
				{
					if (nodNou->date.valoare < pointer->date.valoare)
					{
						done = 1;
					}
					else
					{
					pointer = pointer->next;
					}
				}		
				if (pointer == (*head))
				{
					Nod aux;
					aux.next = (*head);
					(*head) = nodNou;
					nodNou->next = aux.next;
					aux.next->prev = nodNou;
				}
				else if (pointer == NULL)
				{
					nodNou->prev = (*tail);
					(*tail)->next = nodNou;
					(*tail) = nodNou;
				}
				else
				{
					pointer->prev->next = nodNou;
					nodNou->next = pointer;
					nodNou->prev = pointer->prev;
					pointer->prev = nodNou;
					
				}
			}
			(*nrElementeLista)++;
		}
	}
}

void main()
{
	Nod* head = NULL;
	Nod* tail = NULL;
	int nrElementeLista = 0;

	//citireLista("liste.txt", &head, &tail, &nrElementeLista);
	//printListHead(head);

	//stergeNod(&head, &tail, &nrElementeLista, 0);
	//printListTail(tail);

	sortarePrinInserare("liste.txt", &head, &tail, &nrElementeLista);
	printListHead(head);
}