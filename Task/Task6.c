#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct Date Date;
typedef struct Nod Nod;
typedef struct Vecini Vecini;
typedef struct NodSimplu NodSimplu;

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

struct NodSimplu
{
	Date date;
	NodSimplu* next;
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

void printListSimplu(NodSimplu* head)
{
	NodSimplu* temp = head;

	while (temp != NULL)
	{
		printf("%d->", temp->date.valoare);
		temp = temp->next;
	}
	printf("NULL\n");
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

void adaugaInListaSimpla(NodSimplu** head, Date date)
{
	NodSimplu* pointer = (*head);
	NodSimplu* nodNou;
	nodNou = (NodSimplu*)malloc(sizeof(NodSimplu));
	nodNou->next = NULL;
	nodNou->date = date;

	if (pointer == NULL)
	{
		(*head) = nodNou;
	}
	else
	{
		while (pointer->next != NULL)
		{
			pointer = pointer->next;
		}

		pointer->next = nodNou;
	}
}

NodSimplu* copiereInListaSimpla(Nod* head, int valoareData)
{
	//parcurg el, daca gasesc il adaug
	Nod* pointer = head;
	NodSimplu* headSimplu;
	headSimplu = (NodSimplu*)malloc(sizeof(NodSimplu));
	headSimplu = NULL;

	while (pointer != NULL)
	{
		if (pointer->date.valoare > valoareData)
		{
			Date date = pointer->date;

			adaugaInListaSimpla(&headSimplu, date);
		}
		pointer = pointer->next;
	}

	return headSimplu;
}

void aranjarePozitiiCrescator(int* poz1, int* poz2)
{
	if (poz1 > poz2)
	{
		int aux = *poz1;
		*poz1 = *poz2;
		*poz2 = aux;
	}
}

void interschimbareElemente(Nod** head, Nod** tail ,int nrElementeLista, int pozitie1, int pozitie2)
{
	aranjarePozitiiCrescator(&pozitie1, &pozitie2);

	if (pozitie2 > nrElementeLista - 1)
	{
		printf("Pozitie prea mare!");
	}
	else
	{
		if (pozitie1 == 0 && pozitie2 == nrElementeLista - 1)
		{
			(*head)->prev = (*tail)->prev;
			(*tail)->next = (*head)->next;

			(*head)->next->prev = (*tail);
			(*tail)->prev->next = (*head);

			Nod* aux;
			aux = (Nod*)malloc(sizeof(Nod));
			aux->next = (*head);

			(*head) = (*tail);
			(*tail) = aux->next;

			(*head)->prev = NULL;
			(*tail)->next = NULL;
		}
		else if (pozitie1 == 0)
		{
			if (pozitie2 == 1)
			{
				Nod* pointer = (*head)->next;

				Nod aux;
				aux.next = (*head);

				(*head)->prev = pointer;
				(*head)->next = pointer->next;

				pointer->next->prev = (*head);

				pointer->prev = NULL;
				pointer->next = (*head);

				(*head) = pointer;
			}
			else
			{
				Nod* pointer = (*head);
				int indexPozitie = 0;

				while (indexPozitie < pozitie2)
				{
					pointer = pointer->next;
					indexPozitie++;
				}

				Nod aux;
				aux.next = (*head)->next;
				aux.prev = (*head);

				(*head)->next->prev = pointer;
				(*head)->prev = pointer->prev;
				(*head)->next = pointer->next;

				pointer->prev->next = (*head);
				pointer->next->prev = (*head);
				pointer->prev = NULL;
				pointer->next = aux.next;


				(*head) = pointer;
			}
		}
		else if (pozitie2 == nrElementeLista - 1)
		{
			if (pozitie1 == nrElementeLista - 2)
			{
				Nod* pointer = (*tail)->prev;

				Nod aux;
				aux.prev = (*tail);

				(*tail)->prev = pointer->prev;
				(*tail)->next = pointer;

				pointer->prev->next = (*tail);

				pointer->next = NULL;
				pointer->prev = (*tail);			

				(*tail) = pointer;
			}
			else
			{
				Nod* pointer = (*head);
				int indexPozitie = 0;

				while (indexPozitie < pozitie1)
				{
					pointer = pointer->next;
					indexPozitie++;
				}

				Nod aux;
				aux.prev = (*tail)->prev;
				aux.next = (*tail);

				(*tail)->prev->next = pointer;
				(*tail)->next = pointer->next;
				(*tail)->prev = pointer->prev;

				pointer->prev->next = (*tail);
				pointer->next->prev = (*tail);
				pointer->next = NULL;
				pointer->prev = aux.prev;

				(*tail) = pointer;
			}
		}
		else
		{
			if (pozitie2 - pozitie1 == 1)
			{
				Nod* pointer1 = (*head);
				Nod* pointer2 = (*head);
				int indexPozitie = 0;

				while (indexPozitie < pozitie1)
				{
					pointer1 = pointer1->next;
					indexPozitie++;
				}

				indexPozitie = 0;

				while (indexPozitie < pozitie2)
				{
					pointer2 = pointer2->next;
					indexPozitie++;
				}
				printf("%d %d\n", pointer1->date.valoare, pointer2->date.valoare);
				Nod aux1;
				aux1.prev = pointer1->prev;
				aux1.next = pointer1;

				pointer1->prev->next = pointer2;
				pointer2->next->prev = pointer1;

				pointer1->next = pointer2->next;
				pointer1->prev = pointer2;

				pointer2->next = aux1.next;
				pointer2->prev = aux1.prev;
			}
			else
			{
				Nod* pointer1 = (*head);
				Nod* pointer2 = (*head);
				int indexPozitie = 0;

				while (indexPozitie < pozitie1)
				{
					pointer1 = pointer1->next;
					indexPozitie++;
				}

				indexPozitie = 0;

				while (indexPozitie < pozitie2)
				{
					pointer2 = pointer2->next;
					indexPozitie++;
				}

				Nod aux1;
				aux1.next = pointer1->next;
				aux1.prev = pointer1->prev;

				pointer1->prev->next = pointer2;
				pointer1->next->prev = pointer2;
				pointer2->next->prev = pointer1;
				pointer2->prev->next = pointer1;

				pointer1->next = pointer2->next;
				pointer1->prev = pointer2->prev;

				pointer2->next = aux1.next;
				pointer2->prev = aux1.prev;
			}
			
		}
	}
}

void main()
{
	Nod* head = NULL;
	Nod* tail = NULL;
	int nrElementeLista = 0;

	citireLista("liste.txt", &head, &tail, &nrElementeLista);
	printListHead(head);

	interschimbareElemente(&head, &tail, nrElementeLista, 2, 3);
	printListHead(head);
	printListTail(tail);

	//stergeNod(&head, &tail, &nrElementeLista, 0);
	//printListTail(tail);

	//sortarePrinInserare("liste.txt", &head, &tail, &nrElementeLista);
	//printListHead(head);

	/*NodSimplu* headSimplu;
	headSimplu = (NodSimplu*)malloc(sizeof(NodSimplu));

	headSimplu = copiereInListaSimpla(head, 0);

	head->date.valoare = 10;
	printf("%d", head->date.valoare);
	printListSimplu(headSimplu);*/
}