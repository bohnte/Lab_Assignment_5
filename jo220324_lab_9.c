#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
    struct RecordType* next;
};

// Fill out this structure
struct HashType
{
    struct RecordType* record;
};

// Compute the hash function
int hash(int x, int hashSz)
{
    return x % hashSz;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		if(pHashArray[i].record != NULL){
            printf("Index %d: ID: %d, Name: %c, Order: %d", i, pHashArray[i].record -> id, pHashArray[i].record -> name, pHashArray[i].record -> order);

            struct RecordType* nextRecord = pHashArray[i].record->next;
            while(nextRecord != NULL){
                printf(" -> ID: %d, Name: %c, Order: %d", nextRecord -> id, nextRecord -> name, nextRecord -> order);
                nextRecord = nextRecord->next;
            }
            printf("\n");
        }
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;
    const int hashSz = 50;

	recordSz = parseData("input.txt", &pRecords);
    struct HashType* pHashTable = malloc(sizeof(struct HashType) * hashSz);
    for(int i = 0; i < hashSz; ++i){
        pHashTable[i].record = NULL;
    }
    for(int i = 0; i <recordSz; ++i){
        int value = hash(pRecords[i].id, hashSz);
        if(pHashTable[value].record == NULL){
            pHashTable[value].record = &pRecords[i];
            pRecords[i].next = NULL;
        }
        else{
            struct RecordType* current = pHashTable[value].record;
            while(current -> next != NULL){
                current = current -> next;
            }
            current -> next = &pRecords[i];
            pRecords[i].next = NULL;
        }
    }
	printRecords(pRecords, recordSz);
	displayRecordsInHash(pHashTable, hashSz);
    free(pHashTable);
    return 0;
}