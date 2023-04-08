#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;


void heapify(int pData[], int n, int i) {
    
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && pData[left] > pData[largest])
      largest = left;
  
    if (right < n && pData[right] > pData[largest])
      largest = right;
  
    
    if (largest != i) {
      
		int temp = pData[i];
    	pData[i] = pData[largest];
    	pData[largest] = temp;

      heapify(pData, n, largest);
    }
  }


// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int pData[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--){
      heapify(pData, n, i);
	}
  
    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
      int temp = pData[0];
        pData[0] = pData[i];
        pData[i] = temp;
  
      // Heapify root element to get highest element at root again
      heapify(pData, i, 0);
    }

	extraMemoryAllocated += sizeof(int) * n;
}

void merge(int pData[], int l, int m, int r)
{
    
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = pData[l + i];
    for (j = 0; j < n2; j++)
        R[j] = pData[m + 1 + j];
  
    i = 0;
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            pData[k] = L[i];
            i++;
        }
        else {
            pData[k] = R[j];
            j++;
        }
        k++;
    }
   
    while (i < n1) {
        pData[k] = L[i];
        i++;
        k++;
    }
  

    while (j < n2) {
        pData[k] = R[j];
        j++;
        k++;
    }

}

void mergeSort(int pData[], int l, int r)
{
    if (l < r) {
    
        int m = l + (r - l) / 2;
  
      
        mergeSort(pData, l, m);
        mergeSort(pData, m + 1, r);
  
        merge(pData, l, m, r);


		extraMemoryAllocated += sizeof(int) * (r - l + 1);
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block

		
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i;
	int sz = dataSz > 100 ? dataSz - 100 : 0;
	printf("\tData:\n\t");
	
	if(sz != 0)
	{
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	}
	
	for (i=sz;i<dataSz && i<dataSz-1;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}