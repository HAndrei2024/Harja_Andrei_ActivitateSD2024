#include <stdio.h>
#include <malloc.h>

typedef struct Cladire Cladire;
typedef struct Nod Nod;
#define TABLE_SIZE 10

struct Cladire
{
	int id;
	int an;
	char* tip;
};

struct Nod
{
	Cladire cladire;
	Nod* next;
};

Cladire initializeazaCladire(int an, int id, const char* tip)
{
	Cladire cladire;
	cladire.an = an;
	cladire.id = id;

	cladire.tip = (char*)malloc(sizeof(char) * strlen(tip) + 1);
	strcpy(cladire.tip, tip);

	return cladire;
}

void afiseazaCladire(Cladire cladire)
{
	printf("Cladire{An: %d, Id: %d, Tip: %s}", cladire.an, cladire.id, cladire.tip);
}

int functieHash(int an)
{
	return an % 10;
}

Nod** initializeazaHashTable()
{
	Nod** hashTable;

	hashTable = (Nod**)malloc(sizeof(Nod*) * TABLE_SIZE);
	
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		*(hashTable + i) = NULL;
		//hashTable[i] = NULL;
	}

	return hashTable;
}

void inserareInLista(Nod* head, Nod* nodNou)
{
	Nod* temp = head;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	temp->next = nodNou;

	return head;
}

Nod** adaugaInHashTable(Nod** hashTable, Cladire cladire)
{
	int pozitie = functieHash(cladire.an);

	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->cladire = cladire;
	nodNou->next = NULL;

	if (hashTable[pozitie] == NULL)
	{
		hashTable[pozitie] = nodNou;
	}
	else
	{
		inserareInLista(hashTable[pozitie], nodNou);
	}

	return hashTable;
}

void afiseazaCluster(Nod** hashTable, int an)
{
	int pozitie = functieHash(an);

	Nod* temp = hashTable[pozitie];

	while (temp != NULL)
	{
		afiseazaCladire(temp->cladire);
		printf(" -> ");
		temp = temp->next;
	}
	printf("NULL\n");
}

Cladire stergeElementDupaIdSiAn(Nod** hashTable, int an, int id)
{
	int pozitie = functieHash(an);
	//o lista, head = hashTable[pozitie]
	Nod* head = hashTable[pozitie];
	Nod aux;
	aux.next = head;
	Cladire cladire;
	cladire.an = -1;
	cladire.id = -1;

	if (head != NULL)
	{
		if (head->cladire.id == id)
		{
			cladire.an = head->cladire.an;
			cladire.id = head->cladire.id;
			cladire.tip = (char*)malloc(sizeof(char) * strlen(hashTable[pozitie]->cladire.tip));
			strcpy(cladire.tip, hashTable[pozitie]->cladire.tip);
			hashTable[pozitie] = head->next;
			free(aux.next);
		}
		else
		{
			Nod* temp = head;
			Nod nodAnterior;
			int gasit = 0;
			while (temp->next != NULL && temp->cladire.id != id)
			{
				nodAnterior.next = temp;
				temp = temp->next;
			}
			if (temp->cladire.id == id) gasit = 1;

			if (temp->next == NULL && gasit == 1)
			{
				nodAnterior.next->next = NULL;
				cladire = initializeazaCladire(temp->cladire.an, temp->cladire.id, temp->cladire.tip);
			}
			else if (temp->cladire.id == id)
			{
				cladire = initializeazaCladire(temp->cladire.an, temp->cladire.id, temp->cladire.tip);
				nodAnterior.next->next = temp->next;
			}
			if (gasit == 1)
			{
				free(temp->cladire.tip);
				free(temp);
			}
		}
	}

	return cladire;
}

void stergeElementDupaId(Nod** hashTable, int id)
{
	int done = 0;
	Cladire cladire;
	cladire.an = -1;

	for (int i = 0; i < TABLE_SIZE && done == 0; i++)
	{
		if(hashTable[i] != NULL)
		{
			cladire = stergeElementDupaIdSiAn(hashTable, hashTable[i]->cladire.an, id);
			if (cladire.an != -1)
			{
				done = 1;
			}
		}
	}

	if (done == 1)
	{
		printf("Cladirea: ");
		afiseazaCladire(cladire);
		printf("a fost stearsa dupa ID!");
	}
	else
	{
		printf("Nu exista cladirea cu id-ul dat!");
	}
}

Cladire* salvareInVectorCladiriDinAn(Nod** hashTable, int an, int* nrElementeVector)
{
	int pozitie = an % 10;
	Cladire* vector = NULL;
	*nrElementeVector = 0;

	if (hashTable[pozitie] != NULL)
	{
		Nod* temp = hashTable[pozitie];

		while (temp != NULL)
		{
			temp = temp->next;
			(*nrElementeVector)++;
		}

		vector = (Cladire*)malloc(sizeof(Cladire) * (*nrElementeVector));

		temp = hashTable[pozitie];
		int i = 0;

		while (temp != NULL)
		{
			vector[i] = temp->cladire;
			temp = temp->next;
			i++;
		}
	}
	else
	{
		printf("Nu exista cladiri din acest an!");
	}

	return vector;
}

Nod** modificareAn(Nod** hashTable, int id, int anModificat)
{
	int gasit = 0;
	Cladire cladire;

	for (int i = 0; i < TABLE_SIZE && gasit == 0; i++)
	{
		Nod* head = hashTable[i];

		while (head != NULL && gasit == 0)
		{
			if (head->cladire.id == id)
			{
				gasit = 1;
			}
			else
			{
				head = head->next;
			}
		}

		if (gasit == 1)
		{
			cladire = stergeElementDupaIdSiAn(hashTable, head->cladire.an, id);
			cladire.an = anModificat;
			adaugaInHashTable(hashTable, cladire);
			printf("Cladire gasita si modificata!\n");
		}
	}

	if (gasit == 0)
	{
		printf("Nu exista cladirea!");
	}

	return hashTable;
}

void main()
{
	Nod** hashTable = initializeazaHashTable();

	Cladire cladire1 = initializeazaCladire(2000, 1, "Bloc");
	Cladire cladire2 = initializeazaCladire(2000, 2, "Casa");
	Cladire cladire3 = initializeazaCladire(2000, 3, "Vila");
	Cladire cladire4 = initializeazaCladire(2003, 4, "Cladire Birouri");
	Cladire cladire5 = initializeazaCladire(2004, 5, "Bloc");

	hashTable = adaugaInHashTable(hashTable, cladire1);
	hashTable = adaugaInHashTable(hashTable, cladire2);
	hashTable = adaugaInHashTable(hashTable, cladire3);
	hashTable = adaugaInHashTable(hashTable, cladire4);

	afiseazaCluster(hashTable, 2000);
	hashTable = modificareAn(hashTable, 1, 2001);
	afiseazaCluster(hashTable, 2000);
	afiseazaCluster(hashTable, 2001);
	
	//free
	//char de la initializare cladire
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (hashTable[i] != NULL)
		{
			Nod* head = hashTable[i];

			while (head != NULL)
			{
				Nod aux;
				aux.next = head->next;

				stergeElementDupaIdSiAn(hashTable, head->cladire.an, head->cladire.id);

				head = aux.next;
			}
		}
	}
}