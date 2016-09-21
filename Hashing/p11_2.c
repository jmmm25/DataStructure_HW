#include<stdio.h>
#include<stdlib.h>


typedef struct HashTable Hashtbl;

struct HashTable
{
    int* data;
    int TableSize;
    int count;
};

Hashtbl* createHash(int size);
int Find(Hashtbl* tbl, int input);
void Insert(Hashtbl* tbl, int input);
int Hash(int input, int size);
Hashtbl* rehashing(Hashtbl* tbl);

int main(int argc, char* argv[])
{
    FILE *fi = fopen(argv[1], "r");
    int val,temp;
    char ch;
    Hashtbl* myHash;
    fscanf(fi,"%d",&val);
    
    myHash = createHash(val);
    
    do
    {
        fscanf(fi,"%d",&val);
       
       if(myHash->count == (myHash->TableSize / 2) )
            myHash = rehashing(myHash);
        
        Insert(myHash, val);
       	ch = fgetc(fi);
    }
    while(ch != '\n' && ch != '\r');
    
    while(!feof(fi))
    {
        fscanf(fi,"%d ",&val);
        temp = Find(myHash, val);
        
        if(temp == 0)
            printf("%d is not in table\n",val);
        else if(temp == 1)
        {
            printf("%d is in hashtable\n",val);
        }
    }
    
    free(myHash->data);
    free(myHash);
    fclose(fi);
    return 0;
    
}



Hashtbl* createHash(int size)
{
    Hashtbl* H;
    H = (Hashtbl*)malloc(sizeof(Hashtbl));
    H->data = (int*)calloc(size, sizeof(int));
    H->TableSize = size;
    H->count = 0;
    return H;
}

int Find(Hashtbl* tbl, int input)
{
    int index = Hash(input, tbl->TableSize);
    int temp = index;
    while(1)
    {
        if(tbl->data[temp]==0)
            break;
        
        if(tbl->data[temp] == input)
            return 1;
        else
        {
            temp += 1;
            temp = temp % tbl->TableSize;
            
            if(temp == index)
            {
                return 0;
            }
        }
    }
    
    return 0;
}

void Insert(Hashtbl* tbl, int input)
{
    int index = Hash(input, tbl->TableSize);
    int temp;
    
    temp = Find(tbl,input);
    if(temp == 1)
    {
        printf("%d is already inserted in table\n",input);
        return;
    }
    
    
    while(1)
        
    {
        
        if(tbl->data[index] == 0)
        {
            tbl->data[index] = input;
            tbl->count ++;
            //            printf("[%d]\n",tbl->data[index]);
            return;
        }
        else if(tbl->data[index] != 0)
        {
            printf("Collision occurs: %d\n",input);
            index += 1;
            index = index % tbl->TableSize;
            
        }
        
    }
}

int Hash(int input, int size)
{
    return input % size;
}

Hashtbl* rehashing(Hashtbl* tbl)
{
    Hashtbl* newHash;
    newHash = createHash(tbl->TableSize * 2);
    int i;
    printf("rehasing start\n");
    for(i=0 ; i< tbl->TableSize ; i++)
    {
        Insert(newHash , tbl->data[i]);
    }
    free(tbl->data);
    free(tbl);
    
    return newHash;
}

