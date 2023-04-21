#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

struct Trie {
    int isWord;
    struct Trie* next[ALPHABET_SIZE];
};

struct Trie* init();
void insert(struct Trie **ppTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
void deallocateTrie(struct Trie *pTrie);

int main(void)
{
    // read the number of the words in the dictionary
    //  parse line by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    struct Trie* trie = init();

    for (int i = 0; i < 5; i++)
        insert(&trie, pWords[i]);

    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    deallocateTrie(trie);
    return 0;
}

struct Trie* init() {
    // Create the struct, not a word.
    struct Trie* myTree = malloc(sizeof(struct Trie));
    myTree->isWord = 0;

    // Set each pointer to NULL.
    for (int i=0; i<ALPHABET_SIZE; i++)
        myTree->next[i] = NULL;

    // Return a pointer to the new root.
    return myTree;
}

void insertRec(struct Trie* tree, char word[], int k, int wordlen) {
    // Down to the end, insert the word.
    if (k == wordlen) {
        tree->isWord = 1;
        return;
    }

    // See if the next place to go exists, if not, create it.
    int nextIndex = word[k] - 'a';
    if (tree->next[nextIndex] == NULL)
        tree->next[nextIndex] = init();

    // Insert recursively down the path of this word, advancing one letter.
    insertRec(tree->next[nextIndex], word, k+1, wordlen);
}

void insert(struct Trie** ppTrie, char* word) {
    struct Trie* tree = *ppTrie;
    insertRec(tree, word, 0, strlen(word));
}

int numberOfOccurances(struct Trie* pTrie, char* word) {
    struct Trie* tree = pTrie;
    int n = strlen(word);
    for (int i = 0; i < n; i++) {
        int nextIndex = word[i] - 'a';
        if (tree->next[nextIndex] == NULL) {
            return 0;
        }
        tree = tree->next[nextIndex];
    }
    return tree->isWord;
}

void deallocateTrie(struct Trie* pTrie) {
    if (pTrie == NULL) {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        free(pTrie->next[i]);
    }
    free(pTrie);
}
