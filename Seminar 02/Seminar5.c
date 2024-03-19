#include<stdio.h>
#include<malloc.h>

typedef struct CafeneaMea Cafenea; //asta este un alias. nu o sa mai treb sa scrii "struct CafeneaMea", ci doar "Cafenea"
typedef struct Nod Nod;

struct CafeneaMea {
    char* nume;
    int nrLocuri;
    float suprafata;
};

struct Nod {
    Cafenea info;
    Nod* next;
};

Cafenea initializareCafenea(const char* nume, int nrLocuri, float suprafata) {
    Cafenea cafenea;
    cafenea.nrLocuri = nrLocuri;
    cafenea.suprafata = suprafata;
    cafenea.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(cafenea.nume, nume);

    return cafenea;
}

Nod* inserareInceput(Cafenea c, Nod* cap)
{
    Nod* nou = malloc(sizeof(Nod));
    nou->next = cap;
    nou->info = initializareCafenea(c.nume, c.nrLocuri, c.suprafata);

    return nou;
}

void afisareCafenea(Cafenea c)
{
    printf("\nDenumire: %s Nr scaune: %d Suprafata: %.2f\n", 
        c.nume, c.nrLocuri, c.suprafata);
}

void afisareCafenele(Nod* lista)
{

    while (lista != NULL)
    {
        afisareCafenea(lista->info);
        lista = lista->next;
    }
}

//numele cafenelei cu densitatea cea mai mica
char* numeCafeneaDensitateMinima(Nod* lista)
{
    if (lista != NULL)
    {
        if (lista->info.suprafata != 0)
        {
            float minim = lista->info.nrLocuri / lista->info.suprafata;
            Nod* adresa = lista;

            while (lista != NULL)
            {
                float densitate = lista->info.nrLocuri / lista->info.suprafata;

                if (densitate < minim)
                {
                    minim = densitate;
                    adresa = lista;
                }
                lista = lista->next;
            }
            char* nume;
            nume = (char*)malloc(sizeof(char) * strlen(adresa->info.nume) + 1);
            strcpy(nume, adresa->info.nume);

            return nume;
        }
    }
}

void stergeLista(Nod** nod)
{
    while (*nod != NULL)
    {
        Nod* aux = (*nod);

        (*nod) = (*nod)->next;
        free(aux->info.nume);
        free(aux);
    }
}

void inserareFinal(Nod** lista, Cafenea c)
{
    Nod* pointer = (*lista);
    //verificare daca lista e goala

    while (pointer->next != NULL)
    {
        pointer = pointer->next;
    }

    Nod* nodNou = (Nod*)malloc(sizeof(Nod));
    nodNou->info = initializareCafenea(c.nume, c.nrLocuri, c.suprafata);
    nodNou->next = NULL;

    pointer->next = nodNou;
}

void main() {
    Nod* cap = NULL;
    Cafenea cafenea = initializareCafenea("Tucano", 12, 20);
    Cafenea cafenea1 = initializareCafenea("Teds", 15, 22);
    Cafenea cafenea2 = initializareCafenea("StarBucks", 10, 10);

    cap = inserareInceput(cafenea, cap);
    cap = inserareInceput(cafenea1, cap);
    cap = inserareInceput(cafenea2, cap);

    afisareCafenele(cap);

    char* nume = numeCafeneaDensitateMinima(cap);
    printf("%s", nume);

    inserareFinal(&cap, cafenea);
    afisareCafenele(cap);

    stergeLista(&cap);
    afisareCafenele(cap);

    free(cafenea.nume);
    free(cafenea1.nume);
    free(cafenea2.nume);

    free(nume);
}