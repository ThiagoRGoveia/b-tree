#include "Includes.h"

void getRRNByPrimaryKey(Result * result, long int nodeIndex, int nUSP){
    // printf("N_USP %d\n", nUSP);
    int position = -1, nextIndex;
    // result = (Result *) malloc(sizeof(Result));
    // printf("FIND 1\n");
    // result->node = getNodeByIndex(nodeIndex);
    // printf("FIND 2\n");
    Node *node = getNodeByIndex(nodeIndex);
    // printf("FIND 3\n");

    position = keyPositionSearch(node->entries, 0, node->numberOfEntries, nUSP);
    // printf("POSITION %d\n", position);

    if(node->entries[position].key == nUSP){
        result->entry = node->entries[position];
        result->node = node;
        return;
    }else if(node->entries[position].key > nUSP){
        if(position > 0) {
            nextIndex = node->entries[position-1].child;
            // free(node);
            getRRNByPrimaryKey(result, nextIndex, nUSP);
        }
        else {
            nextIndex = node->entries[0].child;
            // free(node);
            getRRNByPrimaryKey(result, nextIndex, nUSP);
        }
    }else{
        if(position < node->numberOfEntries - 1) {
            nextIndex = node->entries[position+1].child;
            // free(node);
            getRRNByPrimaryKey(result, nextIndex, nUSP);
        }
        else{
            if(node->nextNode == -1){
                result->entry.key = -1;
                result->node = node;
                return;
            }else{
                nextIndex = node->nextNode;
                // free(node);
                getRRNByPrimaryKey(result, nextIndex, nUSP);
            }
        }
    }
}

//Função que pega a posição do primeiro valor maior, que o valor que se quer encontrar, ou a posição do mesmo.
int keyPositionSearch(Entry * entries, int start, int end, int value) {
    int middle = (start + end) / 2;

    while( start <= end ){
        middle = (start + end) / 2;

        if(entries[middle].key == value)
            return middle;
        else if(value < entries[middle].key)
            end = middle - 1;
        else if (value > entries[middle].key)
            start = middle + 1;
    }

    return middle;
}