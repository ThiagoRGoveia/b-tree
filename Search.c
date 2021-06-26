#include "Includes.h"

Result * getRRNByPrimaryKey(long int rrnCurrent, int nUSP){
    FILE * fp;
    Result * result;
    int position = -1;

    fp = fopen(INDEX_FILE, "rb");
    fseek(fp, rrnCurrent, SEEK_SET);
    fread(&result->node, NODE_SIZE, 1, fp);
    fclose(fp);

    position = keyPositionSearch(result->node->entries, 0, result->node->numberOfEntries, nUSP);
    
    if(result->node->entries[position].key == nUSP){
        result->entry = result->node->entries[position];
        return result;
    }else if(result->node->entries[position].key > nUSP){
        if(position > 0)
            return getRRNByPrimaryKey(result->node->entries[position-1].child, nUSP);
        else
            return getRRNByPrimaryKey(result->node->entries[0].child, nUSP); 
    }else{
        if(position < result->node->numberOfEntries - 1)
            return getRRNByPrimaryKey(result->node->entries[position+1].child, nUSP);
        else{
            if(result->node->nextNode == -1){
                result->entry = result->node->entries[position - 1];
                result->node = NULL;
                return result;
            }else{
                result->node = getNodeByIndex(result->node->nextNode);
                position = keyPositionSearch(result->node->entries, 0, result->node->numberOfEntries, nUSP);

                if(result->node->entries[position].key == nUSP){
                    result->entry = result->node->entries[position];
                    return result;
                }else if(result->node->entries[position].key > nUSP){
                    if(position > 0)
                        return getRRNByPrimaryKey(result->node->entries[position-1].child, nUSP);
                    else
                        return getRRNByPrimaryKey(result->node->entries[0].child, nUSP); 
                } 
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