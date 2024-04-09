//#include<stdio.h>
//#include<malloc.h>
//
//typedef struct CafeneaMea Cafenea; //asta este un alias. nu o sa mai treb sa scrii "struct CafeneaMea", ci doar "Cafenea"
//typedef struct Nod Nod;
//typedef struct ListaDubla ListaDubla;
//
//struct CafeneaMea {
//    char* nume;
//    int nrLocuri;
//    float suprafata;
//};
//
//struct Nod {
//    Cafenea cafenea;
//    Nod* anterior;
//    Nod* urmator;
//};
//
//struct ListaDubla {
//    Nod* cap;
//    Nod* coada;
//};
//
//Cafenea initializareCafenea(const char* nume, int nrLocuri, float suprafata) {
//    Cafenea cafenea;
//    cafenea.nrLocuri = nrLocuri;
//    cafenea.suprafata = suprafata;
//    cafenea.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
//    strcpy(cafenea.nume, nume);
//
//    return cafenea;
//}
//
//
//void afisareCafenea(Cafenea c)
//{
//    printf("\nDenumire: %s Nr scaune: %d Suprafata: %.2f\n", 
//        c.nume, c.nrLocuri, c.suprafata);
//}
//
//void inserareInceput(ListaDubla* listaDubla, Cafenea cafenea)
//{
//    Nod* nod = malloc(sizeof(Nod));
//    nod->anterior = NULL;
//    nod->cafenea = cafenea;
//    nod->urmator = listaDubla->cap;
//    if (listaDubla->cap != NULL)
//    {
//        listaDubla->cap->anterior = nod;
//        listaDubla->cap = nod;
//    }
//    else
//    {
//        listaDubla->coada = nod;
//    }
//    listaDubla->cap = nod;
//}
//
//void afisareLista(ListaDubla listaDubla)
//{
//    Nod* temp = listaDubla.cap;
//
//    while (temp != NULL)
//    {
//        afisareCafenea(temp->cafenea);
//        temp = temp->urmator;
//    }
//}
//void afisareListaCoada(ListaDubla listaDubla)
//{
//    Nod* temp = listaDubla.coada;
//
//    while (temp != NULL)
//    {
//        afisareCafenea(temp->cafenea);
//        temp = temp->anterior;
//    }
//}
////stergere cafenea dupa nume
//ListaDubla stergeCafeneaDupaNume(ListaDubla listaDubla, const char* nume)
//{
//    if (nume == NULL)
//    {
//        return listaDubla;
//    }
//    Nod* nod = listaDubla.cap;
//
//    while (nod && strcmp(nod->cafenea.nume, nume) != 0)
//    {
//        nod = nod->urmator;
//    }
//    if (nod != NULL)
//    {
//        if (nod->urmator == NULL && nod->anterior == NULL)
//        {
//            listaDubla.cap = NULL;
//            listaDubla.coada = NULL;
//        }
//        else 
//        {
//            if (nod->anterior == NULL)
//            {
//                listaDubla.cap = nod->urmator;
//                listaDubla.cap->anterior = NULL;
//            }
//            else if (nod->urmator == NULL)
//            {
//                listaDubla.coada = nod->anterior;
//                listaDubla.coada->urmator = NULL;
//            }
//            else
//            {
//                nod->anterior->urmator = nod->urmator;
//                nod->urmator->anterior = nod->anterior;
//            }
//        }
//        free(nod->cafenea.nume);
//        free(nod);
//    }
//
//    return listaDubla;
//}
//
//ListaDubla stergeLista(ListaDubla listaDubla)
//{
//    while (listaDubla.cap != NULL && listaDubla.cap->urmator != NULL)
//    {
//        free(listaDubla.cap->cafenea.nume);
//        Nod* temp = listaDubla.cap;
//        listaDubla.cap = listaDubla.cap->urmator;
//        free(temp);
//    }
//    listaDubla.cap = NULL;
//    listaDubla.coada = NULL;
//
//    return listaDubla;
//}
//
////calc nr locuri total
//
//int nrLocuriTotal(ListaDubla listaDubla)
//{
//    if (listaDubla.cap == NULL)
//    {
//        return 0;
//    }
//    Nod* temp = listaDubla.coada;
//    int nrLocuri = 0;
//    while (temp != NULL)
//    {
//        nrLocuri += temp->cafenea.nrLocuri;
//        temp = temp->anterior;
//    }
//
//    return nrLocuri;
//}
//
//void main() {
//    Nod* cap = NULL;
//    Cafenea cafenea = initializareCafenea("Tucano", 12, 20);
//    Cafenea cafenea1 = initializareCafenea("Teds", 15, 22);
//    Cafenea cafenea2 = initializareCafenea("StarBucks", 10, 10);
//
//    ListaDubla listaDubla;
//    listaDubla.cap = NULL;
//    listaDubla.coada = NULL;
//
//    inserareInceput(&listaDubla, cafenea);
//    inserareInceput(&listaDubla, cafenea1);
//    inserareInceput(&listaDubla, cafenea2);
//
//    //afisareLista(listaDubla);
//    //afisareListaCoada(listaDubla);
//
//    //listaDubla = stergeCafeneaDupaNume(listaDubla, "StarBucks");
//    //afisareLista(listaDubla);
//
//    /*listaDubla = stergeCafeneaDupaNume(listaDubla, "Tucano");
//    afisareLista(listaDubla);
//
//    listaDubla = stergeCafeneaDupaNume(listaDubla, "Sb");*/
//
//    //listaDubla = stergeLista(listaDubla);
//    afisareLista(listaDubla);
//   
//    int nrLocuri = nrLocuriTotal(listaDubla);
//    printf("%d", nrLocuri);
//}