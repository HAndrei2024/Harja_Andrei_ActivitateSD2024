#include <stdio.h>
#include <malloc.h>
//#include <string.h>

struct Pahar {
	float ldi[3]; //lungime, diametru, inaltime
	char* material;
	//variabila de tip pointer, stocheaza adresa de memorie a unui char
	float pret;
	int cod;
};
// memorie alocata in BSS (Block started by symbol)

struct Pahar citire()
{
	struct Pahar p;
	char material[100];

	printf("Introduceti lungime, diametru, inaltime pahar:");
	scanf_s("%f %f %f", &p.ldi[0], &p.ldi[1], &p.ldi[2]);

	printf("Introduceti materialul: ");
	scanf_s("%s", material, 100);
	if (material != NULL && strlen(material) > 0) {
		p.material = (char*)malloc(sizeof(char) * strlen(material) + 1);
		//malloc() returns a pointer of type void, wich is casted to char with (char*)
		strcpy(p.material, material);
	}

	printf("Introduceti pretul: ");
	scanf_s("%f", &p.pret);
	//&p.pret = memory adress of p.pret, where the value will be stored.
	//p.pret represents the value itself

	printf("Introduceti codul: ");
	scanf_s("%d", &p.cod);
	printf("\n");

	return p;
}
//calling a void function creates a new separate section on the stack, called Stack Frame, 
//wich will be deallocated when the function returns (including space for local variables declared)
void volum(struct Pahar p, float* v)
{
	//*v represents the value stored at the memory adress pointed by v
	(*v) = p.ldi[0] * p.ldi[1] * p.ldi[2];
}


void modificarePret(struct Pahar* p, float pret)
{
	(*p).pret = pret;
}

void afisare(struct Pahar p)
{
	printf("Lungime, diametru si inaltime: %.2f %.2f %.2f\n", p.ldi[0], p.ldi[1], p.ldi[2]);
	printf("Material: %s\n", p.material);
	printf("Pret: %.2f\n", p.pret);
	printf("Cod: %d\n", p.cod);

}

void copiere(struct Pahar sursa[], int el_sursa, struct Pahar* destinatie, int el_destinatie)
{
	for (int i = 0; i < 3; i++)
		destinatie[el_destinatie].ldi[i] = sursa[el_sursa].ldi[i];
	destinatie[el_destinatie].material = (char*)malloc(sizeof(char) * strlen(sursa[el_sursa].material) + 1);
	strcpy(destinatie[el_destinatie].material, sursa[el_sursa].material);
	destinatie[el_destinatie].pret = sursa[el_sursa].pret;
	destinatie[el_destinatie].cod = sursa[el_sursa].cod;
}


struct Pahar* creeareVectorPaharePlastic(struct Pahar* v, int n, int* j)
{
	(*j) = 0;
	static struct Pahar vpp[10];

	for (int i = 0; i < n; i++)
		if (strcmp(v[i].material, "plastic") == 0) {
			copiere(v, i, vpp, (*j));
			(*j)++;
		}
	return vpp;
}

void mutareInAltVector(struct Pahar v[], int n, struct Pahar* m, int* k)
{
	//conditie: pret > 5
	(*k) = 0;

	for (int i = 0; i < n; i++)
		if (v[i].pret > 5) {
			copiere(v, i, m, (*k));
			(*k)++;
		}
}

void concatenareVectori(struct Pahar v1[], int n, struct Pahar v2[], int m, struct Pahar* vf,
	int* l)
{
	(*l) = 0;

	for (int i = 0; i < n; i++) {
		copiere(v1, i, vf, (*l));
		(*l)++;
	}
	for (int i = 0; i < m; i++) {
		copiere(v2, i, vf, (*l));
		(*l)++;
	}
}


void afisareVector(struct Pahar v[], int n)
{
	for (int i = 0; i < n; i++)
		afisare(v[i]);
}

void dezalocareMemorie(struct Pahar* v, int j)
{
	for (int i = 0; i < j; i++) {
		free(v[i].material);
		v[i].material = NULL;
	}

}

void main()
{
	struct Pahar p;
	float v, pret;

	printf(" --- (Task 1) --- \n");

	p = citire();
	//&v = the adress of v (pointer to a memory zone), wich is passed as a parameter
	volum(p, &v);
	printf("Volum pahar: %.2f\n\n", v);

	printf("Noul pret: ");
	scanf_s("%f", &pret);
	printf("Datele modificate: \n");
	modificarePret(&p, pret);

	afisare(p);


	printf(" --- (Task 2) --- \n");

	struct Pahar* vector;
	struct Pahar* vpp;
	struct Pahar m[10];
	int j, n, k, l;

	printf("Introduceti cate elemente sa contina vectorul - maxim 10: ");
	scanf_s("%d", &n);

	vector = (struct Pahar*)malloc(sizeof(struct Pahar) * n);


	for (int i = 0; i < n; i++)
		vector[i] = citire();

	vpp = creeareVectorPaharePlastic(vector, n, &j);
	printf("afisare vector pahare plastic: ---------- \n");
	afisareVector(vector, j);
	printf("\n");

	mutareInAltVector(vector, n, m, &k);
	printf("afisare vector mutat: ---------- \n");
	afisareVector(m, k);
	printf("\n");

	struct Pahar concat[10];
	concatenareVectori(vpp, j, m, k, concat, &l);
	printf("afisare vector concatenat: ---------- \n");
	afisareVector(concat, l);

	free(p.material);

	dezalocareMemorie(vector, n);
	free(vector);

	dezalocareMemorie(vpp, j);

	dezalocareMemorie(m, k);

	dezalocareMemorie(concat, l);
	//free citire, creare, mutare, concatenare/copiere
}
