#include "Includes.h"

void getRRNByPrimaryKey(Result * result, long int nodeIndex, int nUSP, Search *search){
    int position = -1, nextIndex;


    Node *node = getNodeByIndex(nodeIndex);

    position = keyPositionSearch(node->entries, 0, node->numberOfEntries, nUSP);

    if(node->entries[position].key == nUSP){
        result->entry = node->entries[position];
        result->node = node;
        return;
    }else if(node->entries[position].key > nUSP){
        if(position > 0) {
            nextIndex = node->entries[position-1].child;
            search->history = (int *) realloc(search->history, sizeof(int) * ++search->currentIndex + 1);
            search->history[search->currentIndex] = nextIndex;
            // free(node);
            getRRNByPrimaryKey(result, nextIndex, nUSP, search);
        }
        else {
            if (node->entries[0].child == -1) {
                result->entry.key = -1;
                result->node = node;
                return;
            }
            nextIndex = node->entries[0].child;
            search->history = (int *) realloc(search->history, sizeof(int) * ++search->currentIndex + 1);
            search->history[search->currentIndex] = nextIndex;
            // free(node);
            getRRNByPrimaryKey(result, nextIndex, nUSP, search);
        }
    }else{
        if(position < node->numberOfEntries - 1) {
            nextIndex = node->entries[position+1].child;
            search->history = (int *) realloc(search->history, sizeof(int) * ++search->currentIndex + 1);
            search->history[search->currentIndex] = nextIndex;
            // free(node);
            getRRNByPrimaryKey(result, nextIndex, nUSP, search);
        }
        else{
            if(node->nextNode == -1){
                result->entry.key = -1;
                result->node = node;
                return;
            }else{
                nextIndex = node->nextNode;
                search->history = (int *) realloc(search->history, sizeof(int) * ++search->currentIndex + 1);
                search->history[search->currentIndex] = nextIndex;
                // free(node);
                getRRNByPrimaryKey(result, nextIndex, nUSP, search);
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