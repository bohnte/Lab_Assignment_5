#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    struct Trie *children[26];
    int count;
};

struct Trie* createTrie()
{
    struct Trie* newNode = malloc(sizeof(struct Trie));
    newNode -> count = 0;
    for(int i = 0; i < 26; i++){
        newNode -> children[i] = NULL;
    }
    return newNode;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie* current = pTrie;
    for(int i = 0; word[i] != '\0'; i++){
        int index = word[i] - 'a';
        if(current -> children[index] == NULL){
                current -> children[index] = createTrie();
            }
        current = current -> children[index];
    }
    current -> count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie* current = pTrie;
    for(int i = 0; word[i] != '\0'; i++){
        int index = word[i] - 'a';
        if(current -> children[index] == NULL){
            return 0;
        }
        current = current -> children[index];
    }
    return current -> count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie == NULL){
        return NULL;
    }
    for(int i = 0; i < 26; i++){
        deallocateTrie(pTrie -> children[i]);
    }
    free(pTrie);
    return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("Error.\n");
        exit(1);
    }

    int word = 0;
    char len[100];
    *pInWords = malloc(256 * sizeof(char*));

    while(fscanf(file, "%s", len) != EOF){
        pInWords[word] = strdup(len);
        word++;
    }
    fclose(file);
    return word;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}

    for(int i = 0; i < numWords; i++){
        free(inWords[i]);
    }
    
    deallocateTrie(pTrie);
	return 0;
}