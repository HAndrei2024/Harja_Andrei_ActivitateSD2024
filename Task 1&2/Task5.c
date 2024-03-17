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

void citesteListaDinFisier(char* numeFisier, struct Nod* head, int* nrNoduri)
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
			adaugaNod(head, n);
			(*nrNoduri)++;
		}
	}
}

void printList(struct Nod* head)
{
	struct Nod* temp = head;

	while (temp != NULL)
	{
		printf("%d->", temp->valoare);
		temp = temp->link;
	}
	printf("NULL\n");
}

void stergereNod(struct Nod** head, int* nrNoduri, int pozitieDeSters)
{
	struct Nod* pointer = *head;
	int sters = 0;

	if (pozitieDeSters > nrNoduri)
	{
		printf("Pozitia nu exista!\n");
		return;
	}

	int k = 0;
	/*if (pozitieDeSters == 0)
	{
		printf("Nu exista pozitia 0!\n");
		return;
	}*/
	if (pozitieDeSters == 0)
	{
		*head = (*head)->link;
		(*nrNoduri)--;
		return;
	}
	if (pozitieDeSters == nrNoduri-1)
	{
		for (k = 0; k < nrNoduri; k++)
			pointer = pointer->link;
		pointer->link = NULL;
	}
	while (sters == 0)
	{
		struct Nod* adresaNodAnterior = pointer;
		pointer = pointer->link;
		k++;
		if (k == pozitieDeSters)
		{
			pointer = pointer->link;
			adresaNodAnterior->link = pointer;
			sters = 1;
		}
	}
	(*nrNoduri)--;
}

void numarNoduriConditie(struct Nod* head, int* k, int valoareConditie)
{
	struct Nod* temp = head;

	while (temp != NULL)
	{
		if (temp->valoare > valoareConditie) (*k)++;
		temp = temp->link;
	}
}



void salvareInVectorElementeCuOConditie(struct Nod* head, struct Nod** vector,
	int* nrElementeVector, int valoareConditie)
{
	int i = 0;
	(*nrElementeVector) = 0;
	numarNoduriConditie(head, nrElementeVector, valoareConditie);

	(*vector) = (struct Nod*)malloc(sizeof(struct Nod) * (*nrElementeVector));

	struct Nod* temp = head;

	while (temp != NULL)
	{
		if (temp->valoare > valoareConditie)
		{
			(*vector)[i].link = temp->link;
			(*vector)[i].valoare = temp->valoare;
			i++;
		}
		temp = temp->link;
	}
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

void interschimbareElementeInLista1(struct Nod** head, int nrNoduri, 
	int pozitie1, int pozitie2)
{
	aranjarePozitiiCrescator(&pozitie1, &pozitie2);
	if (pozitie1 > nrNoduri || pozitie2 > nrNoduri)
	{
		printf("Pozitie prea mare!\n");
		return;
	}
	if (pozitie1 == pozitie2)
	{
		printf("Pozitii egale!");
		return;
	}
	struct Nod* nodAnterior1 = NULL;
	struct Nod* nodAnterior2 = NULL;
	struct Nod* nodDeSchimbat1 = NULL;
	struct Nod* nodDeSchimbat2 = NULL;
	struct Nod* temp = *head;
	struct Nod* aux;

	int k = 0;

	if (pozitie1 == 0)
	{
		struct Nod* pointer;

		while (temp != NULL)
		{
			pointer = temp;
			temp = temp->link;
			//if (k == pozitie2) pozitieAnterioara2 = pointer;
			k++;
		}

		aux = *head;
		//(*head) = pozitieAnterioara2->link;
		//pozitieAnterioara2->link->link = aux;

		return;
	}

	if (pozitie2 == nrNoduri - 1)
	{
		struct Nod* pointer;
		struct Nod* pozitieFinala = NULL;
		while (temp != NULL)
		{
			pointer = temp;
			temp = temp->link;
			pozitieFinala = temp;
			if (k == pozitie1) //pozitieAnterioara1 = pointer;
			k++;
		}

		aux = pozitieFinala;
		//pozitieFinala->link = pozitieAnterioara1;
		//pozitieAnterioara1->link = aux->link;

		return;
	}
	struct Nod* pointer = NULL;

	while (temp != NULL)
	{
		if (k == pozitie1)
		{
			nodAnterior1 = pointer;
			nodDeSchimbat1 = temp;
		}
		if (k == pozitie2)
		{
			nodAnterior2 = pointer;
			nodDeSchimbat2 = temp;
		}
		pointer = temp;
		temp = temp->link;
		k++;
	}
	aux = (struct Nod*)malloc(sizeof(struct Nod));
	aux = nodDeSchimbat2->link;

	nodDeSchimbat2->link = nodDeSchimbat1->link;
	nodDeSchimbat1->link = aux;

	nodAnterior1->link = nodDeSchimbat2;
	nodAnterior2->link = nodDeSchimbat1;

	printList(*head);
}

void interschimbareElementeInLista(struct Nod** head, int nrNoduri, int pozitie1,
	int pozitie2)
{
	aranjarePozitiiCrescator(&pozitie1, &pozitie2);
	if (pozitie1 > nrNoduri || pozitie2 > nrNoduri)
	{
		printf("Pozitie prea mare!\n");
		return;
	}
	if (pozitie1 == pozitie2)
	{
		printf("Pozitii egale!");
		return;
	}

	struct Nod* nodAnterior1 = NULL;
	struct Nod* nodAnterior2 = NULL;
	struct Nod* nodDeSchimbat1 = NULL;
	struct Nod* nodDeSchimbat2 = NULL;
	struct Nod* temp = *head;
	struct Nod* pointer = NULL;
	struct Nod* aux;
	int k = 0;

	while (temp != NULL)
	{
		if (k == pozitie1)
		{
			nodAnterior1 = pointer;
			nodDeSchimbat1 = temp;
		}
		if (k == pozitie2)
		{
			nodAnterior2 = pointer;
			nodDeSchimbat2 = temp;
		}
		pointer = temp;
		temp = temp->link;
		k++;
	}
	if (pozitie2 - pozitie1 == 1 && pozitie1 == 0)
	{
		aux = nodDeSchimbat2->link;

		nodDeSchimbat2->link = nodDeSchimbat1;
		nodDeSchimbat1->link = aux;

		(*head) = nodDeSchimbat2;

		return;
	}
	if (pozitie2 - pozitie1 == 1)
	{
		aux = nodDeSchimbat2->link;

		nodDeSchimbat2->link = nodDeSchimbat1;
		nodDeSchimbat1->link = aux;

		nodAnterior1->link = nodDeSchimbat2;

		return;
	}
	
	aux = nodDeSchimbat2->link;

	nodDeSchimbat2->link = nodDeSchimbat1->link;
	nodDeSchimbat1->link = aux;

	if (nodAnterior1 == NULL)
	{
		(*head) = nodDeSchimbat2;
		nodAnterior2->link = nodDeSchimbat1;

		return;
	}

	nodAnterior1->link = nodDeSchimbat2;
	nodAnterior2->link = nodDeSchimbat1;
}

void main()
{
	struct Nod* head = NULL;
	int nrNoduri = 0;
	int nrElementeVector = 0;
	struct Nod* vector;

	citesteListaDinFisier("liste.txt", &head, &nrNoduri);
	printList(head);
	
	salvareInVectorElementeCuOConditie(head, &vector, &nrElementeVector, 2);
	//printf("%d\n", vector[2].valoare);

	interschimbareElementeInLista(&head, nrNoduri, 3, 4);
	printList(head);
}