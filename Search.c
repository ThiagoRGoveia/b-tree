#include "Includes.h"

long int getRRNByPrimaryKey(long int rrnCurrent, int nUSP){
    FILE * fp;
    Node * node;
    long int rrnFound;
    int position = -1;

    fp = fopen(INDEX_FILE, "rb");
    fseek(fp, rrnCurrent, SEEK_SET);
    fread(&node, NODE_SIZE, 1, fp);

    position = keyPositionSearch(node->entries, node->numberOfEntries, nUSP);
    
    if(node->entries[position].key == nUSP)
        return node->entries[position].rrn;
    else
        return getRRNByPrimaryKey(node->entries[position-1].child, nUSP);

    
}

//Função que pega a posição do primeiro valor maior, que o valor que se quer encontrar, ou a posição do mesmo.
int keyPositionSearch(Entry * entries, int end, int value) {
    for(int index = 0; index < end; index++){
        if(entries[index].key >= value)
            return index;
    }
}