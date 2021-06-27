#include "Includes.h"

void getRRNByPrimaryKey(Result * result, int nodeIndex, int nUSP, Search *search){
    int position = -1, nextIndex;

    Node *node = getNodeByIndex(nodeIndex);
    printf("SEARCH NUSP %d\n", nUSP);
    printNode(node);
    position = keyPositionSearch(node->entries, 0, node->numberOfEntries, nUSP);
    // printf("POSITION %d\n", position);
    if (position < 0) {
        if (node->nextNode < 0) {
            result->entry.key = -1;
            result->node = node;
            return;
        } else {
            nextIndex = node->nextNode;
            search->history = (int *) realloc(search->history, sizeof(int) * ++search->currentIndex + 1);
            search->history[search->currentIndex] = nextIndex;
            free(node);
            getRRNByPrimaryKey(result, nextIndex, nUSP, search);
        }
    } else {
        if(node->entries[position].key == nUSP){
            result->entry = node->entries[position];
            result->node = node;
            return;
        }else if(node->entries[position].key > nUSP){
            if (node->entries[position].child == -1) {
                result->entry.key = -1;
                result->node = node;
                return;
            }
            nextIndex = node->entries[position].child;
            search->history = (int *) realloc(search->history, sizeof(int) * ++search->currentIndex + 1);
            search->history[search->currentIndex] = nextIndex;
            free(node);
            getRRNByPrimaryKey(result, nextIndex, nUSP, search);
        }
    }

}

//Função que pega a posição do primeiro valor maior, que o valor que se quer encontrar, ou a posição do mesmo.
// int keyPositionSearch(Entry * entries, int start, int end, int value) {
//     int middle = (start + end) / 2;

//     while( start <= end ){
//         middle = (start + end) / 2;

//         if(entries[middle].key == value)
//             return middle;
//         else if(value < entries[middle].key)
//             end = middle - 1;
//         else if (value > entries[middle].key)
//             start = middle + 1;
//     }

//     return middle;
// }

int keyPositionSearch(Entry * entries, int start, int end, int value) {
    for (int i = 0; i < end; i++) {
        if (entries[i].key >= value) {
            return i;
        }
    }
    return -1;
}