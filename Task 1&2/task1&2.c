//#include <stdio.h>
//#include <malloc.h>
////#include <string.h>
//
//struct Pahar {
//	float ldi[3]; //lungime, diametru, inaltime
//	char* material;
//	//variabila de tip pointer, stocheaza adresa de memorie a unui char
//	float pret;
//	int cod;
//};
//// memorie alocata in BSS (Block started by symbol)
//
//struct Pahar citire()
//{
//	struct Pahar p;
//	char material[100];
//
//	printf("Introduceti lungime, diametru, inaltime pahar:");
//	scanf_s("%f %f %f", &p.ldi[0], &p.ldi[1], &p.ldi[2]);
//
//	printf("Introduceti materialul: ");
//	scanf_s("%s", material, 100);
//	if (material != NULL && strlen(material) > 0) {
//		p.material = (char*)malloc(sizeof(char) * strlen(material) + 1);
//		//malloc() returns a pointer of type void, wich is casted to char with (char*)
//		strcpy(p.material, material);
//	}
//
//	printf("Introduceti pretul: ");
//	scanf_s("%f", &p.pret);
//	//&p.pret = memory adress of p.pret, where the value will be stored.
//	//p.pret represents the value itself
//
//	printf("Introduceti codul: ");
//	scanf_s("%d", &p.cod);
//	printf("\n");
//
//	return p;
//}
////calling a void function creates a new separate section on the stack, called Stack Frame, 
////wich will be deallocated when the function returns (including space for local variables declared)
//void volum(struct Pahar p, float* v)
//{
//	//*v represents the value stored at the memory adress pointed by v
//	(*v) = p.ldi[0] * p.ldi[1] * p.ldi[2];
//}
//
//
//void modificarePret(struct Pahar* p, float pret)
//{
//	(*p).pret = pret;
//}
//
//void afisare(struct Pahar p)
//{
//	printf("!");
//	printf("Lungime, diametru si inaltime: %.2f %.2f %.2f\n", p.ldi[0], p.ldi[1], p.ldi[2]);
//	printf("Material: %s\n", p.material);
//	printf("Pret: %.2f\n", p.pret);
//	printf("Cod: %d\n", p.cod);
//
//}
//
//void afisareFaraNewLine(struct Pahar p)
//{
//	printf("Lungime, diametru si inaltime: %.2f %.2f %.2f || ", p.ldi[0], p.ldi[1], p.ldi[2]);
//	printf("Material: %s || ", p.material);
//	printf("Pret: %.2f || ", p.pret);
//	printf("Cod: %d || ", p.cod);
//	printf("\n");
//
//}
//
//void copiere(struct Pahar sursa[], int el_sursa, struct Pahar* destinatie, int el_destinatie)
//{
//	for (int i = 0; i < 3; i++)
//		destinatie[el_destinatie].ldi[i] = sursa[el_sursa].ldi[i];
//	destinatie[el_destinatie].material = (char*)malloc(sizeof(char) * strlen(sursa[el_sursa].material) + 1);
//	strcpy(destinatie[el_destinatie].material, sursa[el_sursa].material);
//	destinatie[el_destinatie].pret = sursa[el_sursa].pret;
//	destinatie[el_destinatie].cod = sursa[el_sursa].cod;
//}
//
//
//struct Pahar* creeareVectorPaharePlastic(struct Pahar* v, int n, int* j)
//{
//	(*j) = 0;
//	static struct Pahar vpp[10];
//
//	for (int i = 0; i < n; i++)
//		if (strcmp(v[i].material, "plastic") == 0) {
//			copiere(v, i, vpp, (*j));
//			(*j)++;
//		}
//	return vpp;
//}
//
//void mutareInAltVector(struct Pahar v[], int n, struct Pahar* m, int* k)
//{
//	//conditie: pret > 5
//	(*k) = 0;
//
//	for (int i = 0; i < n; i++)
//		if (v[i].pret > 5) {
//			copiere(v, i, m, (*k));
//			(*k)++;
//		}
//}
//
//void concatenareVectori(struct Pahar v1[], int n, struct Pahar v2[], int m, struct Pahar* vf,
//	int* l)
//{
//	(*l) = 0;
//
//	for (int i = 0; i < n; i++) {
//		copiere(v1, i, vf, (*l));
//		(*l)++;
//	}
//	for (int i = 0; i < m; i++) {
//		copiere(v2, i, vf, (*l));
//		(*l)++;
//	}
//}
//
//
//void afisareVector(struct Pahar v[], int n)
//{
//	for (int i = 0; i < n; i++)
//		afisare(v[i]);
//}
//
//void dezalocareMemorie(struct Pahar* v, int j)
//{
//	for (int i = 0; i < j; i++) {
//		free(v[i].material);
//		v[i].material = NULL;
//	}
//
//}
//
//void citireDinFisier(FILE* f, struct Pahar* vector_t3, int n)
//{
//	char material[100];
//
//	for (int i = 0; i < n; i++) {
//		fscanf_s(f, "%f %f %f", &vector_t3[i].ldi[0], &vector_t3[i].ldi[1], &vector_t3[i].ldi[2]);
//		fscanf_s(f, "%s", material, sizeof(material));
//		vector_t3[i].material = (char*)malloc(sizeof(char) * strlen(material) + 1);
//		strcpy(vector_t3[i].material, material);
//		fscanf_s(f, "%f %d", &vector_t3[i].pret, &vector_t3[i].cod);
//	}
//}
//
//void numarLiniiFisier(FILE* f, int* nrLinii)
//{
//	int c = 0;
//	(*nrLinii) = 0;
//
//	for (c = getc(f); c != EOF; c = getc(f))
//		if (c == '\n') // Increment count if this character is newline 
//			(*nrLinii) = (*nrLinii) + 1;
//
//	fseek(f, 0, SEEK_SET);
//}
//
//void salvareObiectInFisier(char* fisier, struct Pahar p)
//{
//	FILE* f = fopen(fisier, "a");
//	if (f == NULL) {
//		FILE* f = fopen(fisier, "w");
//	}
//
//	fprintf(f, "%f %f %f %s %f %d\n", p.ldi[0], p.ldi[1], p.ldi[2], p.material, p.pret, p.cod);
//	
//}
//
//void salvareVectorObiecteInFisier(char* fisier, struct Pahar* vp, int n)
//{
//	FILE* f = fopen(fisier, "a");
//	if (f == NULL) {
//		FILE* f = fopen(fisier, "w");
//	}
//	for (int i = 0; i < n; i++) {
//		fprintf(f, "%.2f %.2f %.2f %s %.2f %d\n", vp[i].ldi[0], vp[i].ldi[1], vp[i].ldi[2], vp[i].material,
//			vp[i].pret, vp[i].cod);
//	}
//}
//
//struct Pahar** copiereVectorInMatric1e(struct Pahar* vector, int lungimeVector,
//	int elementeMatricePerLinie[], float pret)
//{	
//	struct Pahar** matrice;
//	elementeMatricePerLinie[0] = 0;
//	elementeMatricePerLinie[1] = 0;
//
//	//matricea va avea 2 linii, in functie de pret (>5 si <=5)
//	for (int i = 0; i < lungimeVector; i++)
//	{
//		if (vector[i].pret > 5) elementeMatricePerLinie[1]++;
//		else elementeMatricePerLinie[0]++;
//	}
//	matrice = (struct Pahar**)malloc(sizeof(struct Pahar*) * 2);
//
//	for (int i = 0; i < 2; i++)
//	{
//		matrice[i] = (struct Pahar*)malloc(sizeof(struct Pahar) * elementeMatricePerLinie[i]);
//	}
//
//	
//	printf("%d-------------------------------------------\n", elementeMatricePerLinie[1]);
//
//	return matrice;
//}
//
//void copiereVectorInMatrice(struct Pahar* vector, int* nrElementeVector, struct Pahar*** matrice,
//	int* nrElementeMatricePerLinie, float pret)
//{
//	for (int i = 0; i < nrElementeVector; i++)
//	{
//		if (vector[i].pret > pret) nrElementeMatricePerLinie[1]++;
//		else nrElementeMatricePerLinie[0]++;
//	}
//
//	(*matrice) = (struct Pahar**)malloc(sizeof(struct Pahar*) * 2);
//	for (int i = 0; i < 2; i++)
//	{
//		(*matrice)[i] = (struct Pahar*)malloc(sizeof(struct Pahar) * nrElementeMatricePerLinie[i]);
//	}
//
//	int j = 0;
//	int k = 0;
//	for (int i = 0; i < nrElementeVector; i++)
//	{
//		if (vector[i].pret > pret)
//		{
//			copiere(vector, i, (*matrice)[1], k);
//			k++;
//		}
//		else
//		{
//			copiere(vector, i, (*matrice)[0], j);
//			j++;
//		}
//	}
//
//}
//
//void afisareMatrice(struct Pahar** matrice, int* nrElementeMatricePerLinie)
//{
//	for (int i = 0; i < 2; i++)
//	{	
//		printf("\n ---- Vector %d: ---- \n", i);
//		for (int j = 0; j < nrElementeMatricePerLinie[i]; j++)
//			afisareFaraNewLine(matrice[i][j]);
//		printf(" ---- ----\n");
//	}
//}
//
//void sortareIndexi(int* vector, int n, int* indexiVectorNrElementeMatricePerLinie)
//{
//	int aux;
//	for(int i=0; i<n-1; i++)
//		for(int j = i+1; j<n; j++)
//			if (vector[i] > vector[j])
//			{
//				aux = indexiVectorNrElementeMatricePerLinie[i];
//				indexiVectorNrElementeMatricePerLinie[i] = indexiVectorNrElementeMatricePerLinie[j];
//				indexiVectorNrElementeMatricePerLinie[j] = aux;
//			}
//}
//
//void sortareVector(int* vector, int n)
//{
//	int aux;
//	for (int i = 0; i < n - 1; i++)
//		for (int j = i + 1; j < n; j++)
//			if (vector[i] > vector[j])
//			{
//				aux = vector[i];
//				vector[i] = vector[j];
//				vector[j] = aux;
//			}
//}
//
//struct Pahar** sortareLiniiMatriceDupaNrElemente(struct Pahar** matriceInitiala, 
//	int* nrElementeMatricePerLinie)
//{
//	int indexiVectorNrElementeMatricePerLinie[2];
//	indexiVectorNrElementeMatricePerLinie[0] = 0;
//	indexiVectorNrElementeMatricePerLinie[1] = 1;
//
//	sortareIndexi(nrElementeMatricePerLinie, 2, indexiVectorNrElementeMatricePerLinie);
//
//	struct Pahar** matriceFinala;
//
//	matriceFinala = (struct Pahar**)malloc(sizeof(struct Pahar*) * 2);
//	for (int i = 0; i < 2; i++)
//		matriceFinala[i] = (struct Pahar*)malloc(sizeof(struct Pahar) * nrElementeMatricePerLinie[indexiVectorNrElementeMatricePerLinie[i]]);
//
//	for (int i = 0; i < 2; i++)
//	{
//		for (int j = 0; j < nrElementeMatricePerLinie[i]; j++)
//		{
//			copiere(matriceInitiala[i], j, matriceFinala[indexiVectorNrElementeMatricePerLinie[i]], j);
//		}
//	}
//
//	sortareVector(nrElementeMatricePerLinie, 2);
//
//	return matriceFinala;
//}
//
//void dezalocareMatrice(struct Pahar** matrice, int* nrElementePerLinie)
//{
//	for (int i = 0; i < 2; i++)
//	{
//		for (int j = 0; j < nrElementePerLinie[i]; j++)
//		{
//			dezalocareMemorie(matrice[i], j);
//		}
//		free(matrice[i]);
//	}
//	free(matrice);
//}
//
//void main()
//{
//	//struct Pahar p;
//	//float v, pret;
//
//	//printf(" --- (Task 1) --- \n"); //------------------------------------------------------------------------
//
//	//p = citire();
//	////&v = the adress of v (pointer to a memory zone), wich is passed as a parameter
//	//volum(p, &v);
//	//printf("Volum pahar: %.2f\n\n", v);
//
//	//printf("Noul pret: ");
//	//scanf_s("%f", &pret);
//	//printf("Datele modificate: \n");
//	//modificarePret(&p, pret);
//
//	//afisare(p);
//
//
//	//printf(" --- (Task 2) --- \n"); //------------------------------------------------------------------------
//
//	//struct Pahar* vector;
//	//struct Pahar* vpp;
//	//struct Pahar m[10];
//	//int j, n, k, l;
//
//	//printf("Introduceti cate elemente sa contina vectorul - maxim 10: ");
//	//scanf_s("%d", &n);
//
//	//vector = (struct Pahar*)malloc(sizeof(struct Pahar) * n);
//
//
//	//for (int i = 0; i < n; i++)
//	//	vector[i] = citire();
//
//	//vpp = creeareVectorPaharePlastic(vector, n, &j);
//	//printf("afisare vector pahare plastic: ---------- \n");
//	//afisareVector(vector, j);
//	//printf("\n");
//
//	//mutareInAltVector(vector, n, m, &k);
//	//printf("afisare vector mutat: ---------- \n");
//	//afisareVector(m, k);
//	//printf("\n");
//
//	//struct Pahar concat[10];
//	//concatenareVectori(vpp, j, m, k, concat, &l);
//	//printf("afisare vector concatenat: ---------- \n");
//	//afisareVector(concat, l);
//
//	//free(p.material);
//
//	//dezalocareMemorie(vector, n);
//	//free(vector);
//
//	//dezalocareMemorie(vpp, j);
//
//	//dezalocareMemorie(m, k);
//
//	//dezalocareMemorie(concat, l);
//	////free citire, creare, mutare, concatenare/copiere
//
//	//printf("--- Task 3 ---\n"); //------------------------------------------------------------------------
//
//	//int x;
//	//struct Pahar vector_t3[10];
//
//	/*FILE* f = fopen("obiecte.txt", "r");
//	if (f == NULL) {
//		printf("Eroare deschidere fisier!");
//	}
//	else {*/
//
//		printf("Fisier deschis!");
//
//		//
//		//	citireDinFisier(f, vector_t3, 10);
//
//		//	salvareObiectInFisier("obiecte.txt", vector_t3[0]);
//		//	afisareVector(vector_t3, 10);
//		//	salvareVectorObiecteInFisier("obiecte_test.txt", vector_t3, 10);
//
//		//	dezalocareMemorie(vector_t3, 10);
//
//		//	fclose(f);
//		//}
//
//		printf("--- Task 4 ---\n"); //------------------------------------------------------------------------
//
//		struct Pahar* vector_t4;
//		int nrElementeVector;
//		struct Pahar** matrice;
//		int* nrElementeMatricePerLinie;
//		nrElementeMatricePerLinie = (int*)malloc(sizeof(int) * 2);
//		nrElementeMatricePerLinie[0] = 0;
//		nrElementeMatricePerLinie[1] = 0;
//
//		FILE* f = fopen("obiecte.txt", "r");
//		if (f == NULL) {
//			printf("Eroare deschidere fisier!");
//		}
//		else {
//			numarLiniiFisier(f, &nrElementeVector);
//
//			vector_t4 = (struct Pahar*)malloc(sizeof(struct Pahar) * nrElementeVector);
//
//			int k = 0;
//			int j = 0;
//			citireDinFisier(f, vector_t4, nrElementeVector);
//			//afisareVector(vector_t4, nrElementeVector);
//			copiereVectorInMatrice(vector_t4, nrElementeVector, &matrice,
//				nrElementeMatricePerLinie, 5);
//			afisareMatrice(matrice, nrElementeMatricePerLinie);
//			
//			matrice = sortareLiniiMatriceDupaNrElemente(matrice, nrElementeMatricePerLinie);
//
//			afisareMatrice(matrice, nrElementeMatricePerLinie);
//			dezalocareMatrice(matrice, nrElementeMatricePerLinie);
//		}
//
//}
