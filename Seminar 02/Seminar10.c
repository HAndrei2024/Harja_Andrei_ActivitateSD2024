#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Cinema Cinema;
typedef struct Nod Nod;

struct Cinema
{
	int id;
	int nrFilme;
	char** listaFilme;
};

struct Nod
{
	Cinema cinema;
	Nod* st;
	Nod* dr;
};

void inserareInArbore(Nod** radacina, Cinema cinema)
{
	if (*radacina)
	{
		if ((*radacina)->cinema.id > cinema.id)
		{
			inserareInArbore(&((*radacina)->st), cinema);
		}
		else
		{
			inserareInArbore(&((*radacina)->dr), cinema);
		}
	}
	else
	{
		Nod* nodNou = (Nod*)malloc(sizeof(Nod));

		nodNou->cinema = cinema;
		nodNou->dr = NULL;
		nodNou->st = NULL;

		(*radacina) = nodNou;
	}
}

Cinema citireCinema(FILE* f)
{
	Cinema cinema;
	fscanf(f, "d", &cinema.id);
	fscanf(f, "d", &cinema.nrFilme);
	if (cinema.nrFilme)
	{
		cinema.listaFilme = (char**)malloc(sizeof(char*) * cinema.nrFilme);

		for (int i = 0; i < cinema.nrFilme; i++)
		{
			char buffer[100];
			fscanf(f, "%s", buffer);
			cinema.listaFilme[i] = (char*)malloc(sizeof(char) * strlen(buffer) + 1);
			strcpy(cinema.listaFilme[i], buffer);
		}
	}
	else
	{
		cinema.listaFilme = NULL;
	}
	return cinema;
}

Nod* citireArbore(const char* fileName)
{
	Nod* radacina = NULL;

	if (fileName != NULL && strlen(fileName) > 0)
	{
		FILE* f = fopen(fileName, "r");

		if (f != NULL)
		{
			int nr;
			fscanf(f, "%d", &nr);

			for (int i = 0; i < nr; i++)
			{
				Cinema cinema = citireCinema(f);

				inserareInArbore(&radacina, cinema);
			}
		}
	}

	return radacina;
}

void afisareCinema(Cinema cinema)
{
	printf("Cinematograful cu id-ul %d are in derulare %d filme:", cinema.id, cinema.nrFilme);

	for (int i = 0; i < cinema.nrFilme; i++)
	{
		printf(" %s ", cinema.listaFilme[i]);
	}

	printf("\n");
}

void afisareArborePreordine(Nod* radacina)
{
	if (radacina != NULL)
	{
		afisareCinema(radacina->cinema);

		afisareArborePreordine(radacina->st);
		afisareArborePreordine(radacina->dr);
	}
}

void afisareArboreInOrdine(Nod* radacina)
{
	if (radacina)
	{
		afisareArboreInOrdine(radacina->st);
		afisareCinema(radacina->cinema);
		afisareArboreInOrdine(radacina->dr);
	}
}

int calculFilmeDifuzate(Nod* radacina)
{
	if (radacina)
	{
		int suma = radacina->cinema.nrFilme;

		suma += calculFilmeDifuzate(radacina->st);
		suma += calculFilmeDifuzate(radacina->dr);

		return suma;
	}
	return 0;
}

void main()
{
	Nod* arbore = NULL;

	arbore = citireArbore("date.txt");

	afisareArborePreordine(arbore);

	printf("\n\n Numar filme: %d", calculFilmeDifuzate(arbore));
}