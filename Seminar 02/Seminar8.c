//#include <stdio.h>
//#include <malloc.h>
//
//typedef struct Quiz Quiz;
//typedef struct Heap Heap;
//
//struct Quiz
//{
//	char* materie;
//	int grileGresite;
//};
//
//struct Heap
//{
//	Quiz* vector;
//	int dimensiune;
//	int dimensiuneTotala;
//};
//
//Heap initializareHeap(int nrElemente)
//{
//	Heap heap;
//	
//	heap.vector = malloc(nrElemente * sizeof(Quiz));
//	heap.dimensiuneTotala = nrElemente;
//	heap.dimensiune = 0;
//
//	return heap;
//}
//
//Heap adaugareQuizInHeap(Quiz quiz, Heap heap)
//{
//	if (heap.dimensiune < heap.dimensiuneTotala)
//	{
//		heap.vector[heap.dimensiune] = quiz;
//		heap.dimensiune++;
//		//TO DO filtrare
//	}
//	return heap;
//}
//
//Quiz initializareQuiz(const char* materie, int nrGrileGresite)
//{
//	Quiz quiz;
//	quiz.grileGresite = nrGrileGresite;
//	quiz.materie = malloc(sizeof(char) * strlen(materie) + 1);
//	strcpy(quiz.materie, materie);
//
//	return quiz;
//}
//
//void afisareQuiz(Quiz quiz)
//{
//	printf("%s %d\n", quiz.materie, quiz.grileGresite);
//}
//
//void afisareHeap(Heap heap)
//{
//	for (int i = 0; i < heap.dimensiune; i++)
//	{
//		afisareQuiz(heap.vector[i]);
//	}
//}
//
//void afisareTotalaHeap(Heap heap)
//{
//	for (int i = 0; i < heap.dimensiuneTotala; i++)
//	{
//		afisareQuiz(heap.vector[i]);
//	}
//}
//
//void filtreazaHeap(Heap heap, int pozitieRadacina)
//{
//	int pozitieStanga = pozitieRadacina * 2 + 1;
//	int pozitieDreapta = pozitieRadacina * 2 + 2;
//	int indexMinim = pozitieRadacina;
//
//	if (pozitieStanga < heap.dimensiune && heap.vector[pozitieStanga].grileGresite < heap.vector[indexMinim].grileGresite)
//	{
//		indexMinim = pozitieStanga;
//	}
//	if (pozitieStanga < heap.dimensiune && heap.vector[pozitieDreapta].grileGresite < heap.vector[indexMinim].grileGresite)
//	{
//		indexMinim = pozitieDreapta;
//	}
//
//	if (indexMinim != pozitieRadacina)
//	{
//		Quiz aux = heap.vector[pozitieRadacina];
//		heap.vector[pozitieRadacina] = heap.vector[indexMinim];
//		heap.vector[indexMinim] = aux;
//
//		if (indexMinim * 2 + 1 < heap.dimensiune - 1)
//		{
//			filtreazaHeap(heap, indexMinim);
//		}
//	}
//}
//
//Quiz extragereMinim(Heap* heap)
//{
//	if (heap->dimensiune > 0)
//	{
//		Quiz aux = heap->vector[0];
//
//		heap->vector[0] = heap->vector[heap->dimensiune - 1];
//		heap->vector[heap->dimensiune - 1] = aux;
//
//		heap->dimensiune--;
//
//		for (int i = (heap->dimensiune / 2) - 1; i >= 0; i--)
//		{
//			filtreazaHeap(*heap, i);
//		}
//
//		return aux;
//	}
//	else
//	{
//		return initializareQuiz("null", -1);
//	}
//}
//
//void dezalocareTotHeap(Heap* heap)
//{
//	for (int i = 0; i < heap->dimensiuneTotala; i++)
//	{
//		free(heap->vector[i].materie);
//	}
//	free(heap->vector);
//}
//
//void main()
//{
//	Heap heap;
//	heap = initializareHeap(6);
//	heap.vector[0] = initializareQuiz("SDD", 3);
//	heap.vector[1] = initializareQuiz("Java", 7);
//	heap.vector[2] = initializareQuiz("SGBD", 5);
//	heap.vector[3] = initializareQuiz("ATP", 2);
//	heap.vector[4] = initializareQuiz("POO", 9);
//	heap.vector[5] = initializareQuiz("Analiza", 4);
//	heap.dimensiune = 6;
//
//	afisareHeap(heap);
//	printf("\n");
//	
//	for (int i = heap.dimensiune/2 - 1; i>=0; i--)
//	{
//		filtreazaHeap(heap, i);
//	}
//
//	afisareHeap(heap);
//
//	afisareQuiz(extragereMinim(&heap));
//	afisareQuiz(extragereMinim(&heap));
//	afisareQuiz(extragereMinim(&heap));
//	afisareQuiz(extragereMinim(&heap));
//	afisareQuiz(extragereMinim(&heap));
//	afisareQuiz(extragereMinim(&heap));
//}