#include<stdio.h>
#include<malloc.h>

struct Haina { //contine datele unor obiecte omogene
	//toate elementele publice
	//nu are functii/metode in structuri

	int marime;
	char* marca;
	float pret;
	char gender;
};

struct Haina initializareHaina(int marime, const char* marca, float pret, char gender)
{
	struct Haina h;

	h.marime = marime;
	if (marca != NULL && strlen(marca) > 0) {
		h.marca = malloc(strlen(marca) + 1); //fara cast-ul (char*)
		strcpy(h.marca, marca);
	}
	else
		h.marca = NULL;
	h.pret = pret;
	h.gender = gender;

	return h;
}

void dezalocareHaina(struct Haina* h)
{
	free(h->marca);
	(*h).marca = NULL;
}

void afiseazaHaina(struct Haina h)
{
	if (h.marca != NULL)
		printf("Marca: %s\n", h.marca);
	printf("Marima: %d\n", h.marime);
	printf("Pret: %5.2f\n", h.pret);
	printf("Gender: %c\n\n", h.gender);
}

void main()
{
	struct Haina haina1;

	haina1.marime = 33;
	haina1.marca = (char*)malloc(sizeof(char) * (strlen("Nike") + 1)); //returenaza void* - pointer cater zona de memorie
	strcpy(haina1.marca, "Nike");
	haina1.pret = 45;
	haina1.gender = 'M';

	afiseazaHaina(haina1);
	dezalocareHaina(&haina1);


	struct Haina haina2 = initializareHaina(27, "Adidas", 23.6, 'F');

	afiseazaHaina(haina2);
	dezalocareHaina(&haina2); //memory leak sau dangling pointer, inainte de folosit pointer in functie
	afiseazaHaina(haina2);

}