#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000
#define MAX_WORD_LENGTH 100

typedef struct KeywordNode
{
    char *word;
    int occurrences;
    struct KeywordNode *next; // Pointer to the next node in the linked list
} KeywordNode;

typedef struct
{
    KeywordNode *table[TABLE_SIZE];
} HashTable;

// Function to check if the word is a stop-word (verb, preposition, adjective etc)
int is_stop_word(char *word)
{
    FILE *stop_words_file = fopen("stop_words.txt", "r");
    if (stop_words_file == NULL)
    {
        printf("Error opening stop words file\n");
        exit(1);
    }

    char stop_word[100];
    // Read each word from the stop words file and compare with the input word
    while (fscanf(stop_words_file, "%s", stop_word) != EOF)
    {
        if (strcmp(word, stop_word) == 0)
        {
            fclose(stop_words_file);
            return 1; // It's a stop word
        }
    }
    fclose(stop_words_file);
    return 0; // It's not a stop word
}

// Function to generate the hash value for each word
int hash(char *word)
{
    int hashval = 0;
    while (*word != '\0')
    {
        hashval = *word + 31 * hashval;
        word++;
    }
    return hashval % TABLE_SIZE;
}

// Function to insert the keyword in the hash table
void insert_keyword(HashTable *ht, char *word)
{
    int index = hash(word);
    KeywordNode *new_node = (KeywordNode *)malloc(sizeof(KeywordNode));
    if (new_node == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->word = strdup(word);
    if (new_node->word == NULL)
    {
        printf("Memory allocation failed\n");
        free(new_node);
        exit(EXIT_FAILURE);
    }
    new_node->occurrences = 1;
    new_node->next = NULL;

    if (ht->table[index] == NULL)
    {
        // No collision, insert at the beginning of the linked list
        ht->table[index] = new_node;
    }
    else
    {
        // Collision occurred, append to the end of the linked list
        KeywordNode *current = ht->table[index];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Function to check if the word is a keyword or not
int is_keyword(char *word)
{
    static int keyword_count[TABLE_SIZE] = {0}; // Static array to keep track of keyword occurrences
    int index = hash(word);

    keyword_count[index]++;
    return keyword_count[index] > 2; // Return 1 if the word appears more than twice
}

// Function to update the hash table with new keywords from the files
void update_keyword(HashTable *ht, char *word)
{
     int index = hash(word);
    KeywordNode *current = ht->table[index];

    // Traverse the linked list to find the node with the matching word
    while (current != NULL)
    {
        if (strcmp(current->word, word) == 0)
        {
            // Found the matching keyword, update its occurrences
            current->occurrences++;
            return; // Exit the function after updating
        }
        current = current->next;
    }

    // If the keyword is not found in the linked list, it means it doesn't exist in the hash table
    // Thus, we use the function below to insert it in the hash table
    insert_keyword(ht, word);
}

// Function to print the HashTable
void print_statistics(HashTable *ht)
{
    printf("Keyword\t\tOccurrences\n");
    printf("==============================\n");

    // Create an array to keep track of printed keywords
    int printed[TABLE_SIZE] = {0};

    // Traverse each bucket in the hash table
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        KeywordNode *current = ht->table[i];

        // Traverse the linked list for the current bucket
        while (current != NULL)
        {
            // If the keyword hasn't been printed yet, print it
            if (!printed[i])
            {
                printf("%s\t\t%d\n", current->word, current->occurrences + 2);
                printed[i] = 1; // Mark keyword as printed
            }
            current = current->next;
        }
    }
}

int main()
{
    char sentence[10000];
    // Opening text_file_1.txt for writing
    printf("Enter sentences for text_file_1.txt:\n");
    FILE *file1 = fopen("text_file_1.txt", "w");
    if (file1 == NULL)
    {
        printf("Error creating or opening file\n");
        return 1;
    }
    scanf("%9999[^\n]%*c", sentence);
    fprintf(file1, "%s\n", sentence);

    fclose(file1);
    // Opening text_file_2.txt for writing
    printf("Enter sentences for text_file_2.txt:\n");
    FILE *file2 = fopen("text_file_2.txt", "w");
    if (file2 == NULL)
    {
        printf("Error creating or opening file\n");
        return 1;
    }
    scanf("%9999[^\n]%*c", sentence);
    fprintf(file2, "%s\n", sentence);

    fclose(file2);
    // Opening both text_file_1.txt and text_file_2.txt for reading
    FILE *file1r = fopen("text_file_1.txt", "r");
    FILE *file2r = fopen("text_file_2.txt", "r");

    if (file1r == NULL || file2r == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    HashTable ht;

    // Initialize the table pointers to NULL
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        ht.table[i] = NULL;
    }

    char word[MAX_WORD_LENGTH];

    // Read text_file_1.txt to identify keywords and build the hash table
    while (fscanf(file1r, "%99s", word) == 1)
    { // Ensure successful read
        if (!is_stop_word(word))
        {
            if (is_keyword(word))
                update_keyword(&ht, word);
        }
    }
    printf("The HASHTABLE AFTER READING CONTENTS FROM THE FIRST FILE\n\n");
    // Print statistics
    print_statistics(&ht);

    // Read text_file_2.txt to search for keywords and update the hash table
    while (fscanf(file2r, "%99s", word) == 1)
    { // Ensure successful read
        if (!is_stop_word(word))
        {
            if (is_keyword(word))
                update_keyword(&ht, word);
        }
    }
    printf("The HASHTABLE AFTER READING CONTENTS FROM THE SECOND FILE\n\n");
    // Print statistics
    print_statistics(&ht);

    // Close files and free memory
    fclose(file1);
    fclose(file2);
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        KeywordNode *current = ht.table[i];
        while (current != NULL)
        {
            KeywordNode *temp = current;
            current = current->next;
            free(temp->word);
            free(temp);
        }
    }

    return 0;
}