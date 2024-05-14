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

int calculGradEchilibru(Nod* rad)
{
	int inaltimeSubarboreStang = calculInaltime(rad->st);
	int inaltimeSubarboreDrept = calculInaltime(rad->dr);

	return inaltimeSubarboreStang - inaltimeSubarboreDrept;
}

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
		int grad = calculGradEchilibru(*radacina);

		if (grad == 2) //dezechilibru stanga
		{
			//verificare dezechilibru simplu/complex
			//(dezechilibru stanga stanga)

			int gradCopil = calculGradEchilibru((*radacina)->st);
			if (gradCopil == -1)
			{
				//situatia simpla
				*radacina = rotireDreapta(*radacina);
			}
			else
			{
				(*radacina)->st = rotireStanga((*radacina)->st);
			}
			*radacina = rotireDreapta(*radacina);
		}
		else if (grad == -2)
		{
			if (calculGradEchilibru((*radacina)->dr) == 1)
			{
				(*radacina)->dr = rotireDreapta((*radacina)->dr);
			}
			else
			{
				(*radacina) = rotireStanga(*radacina);
			}
			(*radacina)->dr = rotireDreapta((*radacina)->dr);
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

Nod* rotireDreapta(Nod* rad)
{
	if (rad)
	{
		Nod* aux = rad->st;
		rad->st = aux->dr;
		aux->dr = rad;

		return aux;
	}
	else
	{
		return rad;
	}
}

Nod* rotireStanga(Nod* rad)
{
	if (rad)
	{
		Nod* aux = rad->dr;
		rad->dr = aux->st;
		aux->st = rad;

		return aux;
	}
	else
	{
		return rad;
	}
}

int calculInaltime(Nod* rad)
{
	if (rad)
	{
		int inaltimeSt = calculIntaltime(rad->st);
		int inaltimeDr = calculInaltime(rad->dr);

		if (inaltimeSt > inaltimeDr)
		{
			return 1 + inaltimeSt;
		}
		else
		{
			return 1 + inaltimeDr;
		}
	}
	else
	{
		return 0;
	}
}

void stergereArbore(Nod** rad)
{
	if (*rad)
	{
		stergereArbore(&((*rad))->st);
		stergereArbore(&((*rad))->dr);
		if ((*rad)->cinema.listaFilme)
		{
			for (int i = 0; i < (*rad)->cinema.nrFilme; i++)
			{
				free((*rad)->cinema.listaFilme);
			}
		}
		free((*rad));
		(*rad) = NULL;
	}
}

//cinematograful cu cele mai multe filme
Cinema calculCinemaCuNrMax(Nod* rad)
{
	if (rad)
	{
		Cinema cinemaStanga = calculCinemaCuNrMax(rad->st);
		{
			Cinema cinemaDreapta = calculCinemaCuNrMax(rad->dr);

			Cinema cinemaMaxim;
			if (rad->cinema.nrFilme > cinemaStanga.nrFilme && rad->cinema.nrFilme > cinemaDreapta.nrFilme)
			{
				cinemaMaxim = rad->cinema;
			}
			else if (cinemaStanga.nrFilme > cinemaDreapta.nrFilme)
			{
				cinemaMaxim = cinemaStanga;
			}
			else
			{
				cinemaMaxim = cinemaDreapta;
			}

			return cinemaMaxim;
		}
	}
	else
	{
		Cinema c;
		c.id = -1;
		c.listaFilme = NULL;
		c.nrFilme = 0;

		return c;
	}
}

void main()
{
	Nod* arbore = NULL;

	arbore = citireArbore("date.txt");

	afisareArborePreordine(arbore);

	printf("\n\n Numar filme: %d", calculFilmeDifuzate(arbore));
}