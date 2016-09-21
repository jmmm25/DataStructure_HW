#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct HeapStruct* Heap;
typedef struct HeapStruct{
    
    int Capacity;
    int Size;
    ElementType *Element;
    
}HeapStruct;
// make pointer struct HeapStruct.

// declare available function.
Heap CreateHeap(int heapsize);
void Insert(Heap H, ElementType X);
ElementType DeleteMax(Heap H);
void PrintHeap(Heap H);
ElementType IsFull(Heap H);


int main(int argc, char* argv[]){
    
    FILE *fp1 = fopen(argv[1],"r");     //to read input.txt file, make file I/O function.
    char ch;
    int su=0,value= 0;
    Heap my_MaxHeap;            //make Heap.
    my_MaxHeap = NULL;
    
    while((ch=fgetc(fp1)) != EOF){

        switch(ch){
                
            case 'n' :
                fscanf(fp1,"%d", &su);
                my_MaxHeap = CreateHeap(su);    //to create Heap, call CreateHeap function.
                break;
                
            case 'i' :
                fscanf(fp1,"%d",&su);
                Insert(my_MaxHeap,su);    //insert su's value to my_MaxHeap.
                break;
                
            case 'd':
                if(my_MaxHeap->Size == 0)
                    printf("Delete error, Heap is Empty Space\n");
                else
                    value = DeleteMax(my_MaxHeap);  //Delete maximum value in the Heap.
                break;
                
            case 'p':
                PrintHeap(my_MaxHeap);  // print all my_MaxHeap's element.
                break;
                
        }//switch end.
        
    }//while end
    
    fclose(fp1);        // close input.txt file.
    free(my_MaxHeap);
    free(my_MaxHeap->Element);      // free dynamic allocation.
    
    return 0;
    
    
}//main end


Heap CreateHeap(int heapsize){
    
    Heap H; // create Heap.
    H = (Heap)malloc(sizeof(struct HeapStruct));    //dynamic allocate H.
    H->Element = (ElementType*)malloc(sizeof(ElementType)*heapsize);  //dynamic allocate H->Element.
    H->Capacity = heapsize;
    H->Size = 0;
    H->Element[0] = 255;
    return H;
}
//create Heap , initiate Heap.

ElementType IsFull(Heap H){
    
    if(H->Size==H->Capacity)
        return 1;
    else
        return 0;
}

void Insert(Heap H, ElementType X){
    ElementType i;
    if(IsFull(H)){
        printf("Heap is FULL!!\n");
        return;
    }
   
    for (i= ++H->Size; H->Element[i/2]<X ; i/=2) {
        H->Element[i] = H->Element[i/2];
    }
    
    H->Element[i] = X;
    
}

// Insert X to Heap.

ElementType DeleteMax(Heap H){
    int i, child;
    ElementType MaxElement=0, LastElement=0;
    
    MaxElement = H->Element[1];
    LastElement = H->Element[H->Size--];
    
    for( i=1 ; i*2 <= H->Size ; i = child)
    {
        
        child = i*2;
        
        if (child != H->Size && H->Element[child+1]> H->Element[child])
            child++;
        
        if(LastElement < H->Element[child])
            H->Element[i] = H->Element[child];
        else
            break;
        
    }
    H->Element[i] = LastElement;
    return MaxElement;
}
// Delete Maximum value in the heap.

void PrintHeap(Heap H){
    int i;
    
    if(H->Size == 0)
        printf("Print Error, Heap is Empty Space\n");
    
    else
    {
        for(i = 1 ; i <= H->Size ; i++)
            printf("%d ",H->Element[i]);
       printf("\n");
    }

    
}
//print all Heap's element.
