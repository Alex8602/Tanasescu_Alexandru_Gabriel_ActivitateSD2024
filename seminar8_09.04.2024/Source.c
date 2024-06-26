#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include<string.h>
// heap folosit pt cozi de prioritate

typedef struct Mail Mail;
typedef struct Heap Heap;

struct Mail {
    char* text;
    int prioritate;
};

struct Heap {
    Mail* vector;
    int dim;
};

Heap initializareHeap(int dim) {
    Heap heap;
    heap.vector = (Mail*)malloc(sizeof(Mail) * dim);
    heap.dim = dim;
    return heap;
}

Mail initializareMail(const char* text, int prioritate) {
    Mail mail;
    mail.text = (char*)malloc(strlen(text) + 1);
    strcpy(mail.text, text);
    mail.prioritate = prioritate;
    return mail;
}

void afisareMail(Mail mail) {
    printf("Mail cu textul %s si grad de prioritate %d\n", mail.text, mail.prioritate);
}

void afisareHeap(Heap heap) {
    for (int i = 0; i < heap.dim; i++) {
        afisareMail(heap.vector[i]);
    }
}

void filtrare(Heap heap, int pozRad) {
    int fs = pozRad * 2 + 1; // fiu stanga
    int fd = pozRad * 2 + 2; // fiu dreapta
    int pozMax = pozRad;

    if (fs < heap.dim && heap.vector[pozMax].prioritate < heap.vector[fs].prioritate) {
        pozMax = fs;
    }
    if (fd < heap.dim && heap.vector[pozMax].prioritate < heap.vector[fd].prioritate) {
        pozMax = fd;
    }

    if (pozMax != pozRad) {

        if (heap.vector[pozRad].prioritate < heap.vector[pozMax].prioritate) {
            Mail aux = heap.vector[pozRad];
            heap.vector[pozRad] = heap.vector[pozMax];
            heap.vector[pozMax] = aux;

            if (pozMax < (heap.dim - 2) / 2) {
                filtrare(heap, pozMax);
            }

        }
    }
}

Mail extragereMax(Heap* heap) {
    if (heap->dim > 0) {
        Mail extras = (*heap).vector[0];
        Mail* aux = (Mail*)(malloc(sizeof(Mail) * ((*heap).dim - 1)));
        for (int i = 1; i < heap->dim; i++) {
            aux[i - 1] = heap->vector[i];
        }
        free(heap->vector);
        heap->vector = aux;

        heap->dim--;
        for (int i = (heap->dim - 2) / 2; i >= 0; i--) {
            filtrare((*heap), i);
        }
        return extras;
    }
    Mail mail = {"NULL", 0};
    return mail;
    
}

void inserareMailInHeap(Heap* heap, Mail mail) {
    Mail* aux = (Mail*)(malloc(sizeof(Mail) * (heap->dim + 1)));
    aux[0]=mail;
    for (int i = 1; i < heap->dim+1; i++) {
        aux[i] = heap->vector[i-1];
    }
    free(heap->vector);
    heap->vector = aux;
    heap->dim++;

    filtrare((*heap), 0);
}

void dezalocareHeap(Heap* heap) {
    for (int i = 0; i < heap->dim; i++) {
        free(heap->vector[i].text);
    }
    free(heap->vector);
    heap->vector = NULL;
    heap->dim = 0;

}

int main() {
    Heap heap = initializareHeap(6);

    heap.vector[0] = initializareMail("Salut1", 7);
    heap.vector[1] = initializareMail("Salut2", 9);
    heap.vector[2] = initializareMail("Salut3", 3);
    heap.vector[3] = initializareMail("Salut4", 8);
    heap.vector[4] = initializareMail("Salut5", 6);
    heap.vector[5] = initializareMail("Salut6", 10);

    afisareHeap(heap);
    printf("\nFiltrare:\n");

    for (int i = (heap.dim - 2) / 2; i >= 0; i--) {
        filtrare(heap, i);
    }
    afisareHeap(heap);

    printf("\nElemente extrase: \n");
    afisareMail(extragereMax(&heap));
    afisareMail(extragereMax(&heap));
    afisareMail(extragereMax(&heap));
    afisareMail(extragereMax(&heap));
    afisareMail(extragereMax(&heap));
    afisareMail(extragereMax(&heap));
    
    printf("\nInserare: \n");
    inserareMailInHeap(&heap, initializareMail("Buna ziua", 6));
    inserareMailInHeap(&heap, initializareMail("Buna ziua", 10));
    inserareMailInHeap(&heap, initializareMail("Buna ziua", 4));
    afisareHeap(heap);

    dezalocareHeap(&heap);
    
    return 0;

}
