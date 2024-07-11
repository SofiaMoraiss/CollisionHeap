#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "event.h"
#include "PQ.h"

struct pq {
    Event **arr;      // Posição
    int size;        // Cor
    int capacity;          // Número de colisões
};

// TODO: Aqui você deve implementar uma fila com prioridade mínima para
//       ordenar os eventos por tempo, isto é, o evento com o menor tempo tem
//       a maior prioridade. Veja as funções definidas em 'event.h' para
//       a manipulação das estruturas de evento. A princípio, as funções já
//       existentes em 'event.h' são suficientes para implementar a simulação,
//       isto é, você não precisa implementar mais nada lá.
//
//       Você é livre para implementar a fila com prioridade da forma que quiser
//       mas é recomendado usar um min-PQ para obter um bom desempenho. As
//       simulações maiores geram uma quantidade grande de eventos: um
//       limite superior frouxo (mas seguro) para o número máximo simultâneo de
//       eventos é N^3, aonde N é o número de partículas.

// TODO: Crie a struct pq.

/*
 * Cria uma nova fila de prioridade mínima com o limite de elementos informado.
 */
PQ* PQ_create(int max_N) {
    // TODO: Implemente a criação da fila que suporta no máximo o número de
    //       de eventos informados no parâmetro.

    int cap = pow(max_N,3);

    PQ* pq = (PQ*)malloc(sizeof(PQ));

    if (pq == NULL) {
        printf("Heap was not created\n");
        return NULL;
    }

    pq->size= 0;
    pq->capacity = cap;

    pq->arr = (Event**)malloc(cap * sizeof(Event*));

    if (pq->arr == NULL){
        printf("Array was not allocated!\n");
        return NULL;
    }

    return pq;
}

/*
 * Libera a memória da fila.
 */
void PQ_destroy(PQ *pq) {
    // TODO: Implemente essa função que libera toda a memória da fila,
    //       destruindo inclusive os eventos que estavam na fila.
}

void insertHelper(PQ* pq, int index)
{
 
    // Store parent of element at index
    // in parent variable
    int parent = (index - 1) / 2;
 
    if (pq->arr[parent] > pq->arr[index]) {
        // Swapping when child is smaller
        // than parent element
        Event * temp = pq->arr[parent];
        pq->arr[parent] = pq->arr[index];
        pq->arr[index] = temp;
 
        // Recursively calling insertHelper
        insertHelper(pq, parent);
    }
}

/*
 * Insere o evento na fila segundo o seu tempo.
 */
void PQ_insert(PQ *pq, Event *e) {
    // TODO: Implemente essa função que insere o evento dado na fila segundo
    //       o tempo do evento.
    //       Assuma que 'e' não é nulo. É importante testar overflow (inserção
    //       em uma fila que já contém o número máximo de eventos) para evitar
    //       dores de cabeça com acessos inválidos na memória.

    if (pq->size==pq->capacity){
        printf("Overflow! Heap is full\n");
        return;
    }

    pq->arr[pq->size] = e;

    insertHelper(pq, pq->size);


}

void minHeapify(PQ* pq, int index)
{
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index;
 
    // Checking whether our left or child element
    // is at right index or not to avoid index error
    if (left >= pq->size || left < 0)
        left = -1;
    if (right >= pq->size || right < 0)
        right = -1;
 
    // store left or right element in min if
    // any of these is smaller that its parent
    if (left != -1 && pq->arr[left] < pq->arr[index])
        min = left;
    if (right != -1 && pq->arr[right] < pq->arr[index])
        min = right;
 
    // Swapping the nodes
    if (min != index) {
        Event * temp = pq->arr[min];
        pq->arr[min] = pq->arr[index];
        pq->arr[index] = temp;
 
        // recursively calling for their child elements
        // to maintain min PQ
        minHeapify(pq, min);
    }
}

/*
 * Remove e retorna o evento mais próximo.
 */
Event* PQ_delmin(PQ *pq) {
    // TODO: Implemente essa função que remove o evento com o menor tempo da
    //       fila e o retorna.

    if (PQ_is_empty(pq)){
        return NULL;
    }

    Event * closest = pq->arr[0];

    pq->arr[0] = pq->arr[pq->size-1];
    pq->size--;

    minHeapify(pq, 0);
    return closest;
}

/*
 * Testa se a fila está vazia.
 */
bool PQ_is_empty(PQ *pq) {
    // TODO: Implemente essa função.
    return pq->size==0;
}

/*
 * Retorna o tamanho da fila.
 */
int PQ_size(PQ *pq) {
    // TODO: Implemente essa função.
    return pq->size;
}
