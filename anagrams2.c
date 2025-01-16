/*
 * Author: Luis Fernando Encinas
 * Class:  CSC 352
 * File:   anagrams2.c
 * purpose: Take in back to back strings, adding to Node list,checking which are anagrams
 *            then printing each original word found by then all anagrams seen in order
 *          skipping any words with ints or non letter characters
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
typedef struct Node
{
    int isAnagram;
    char *word;
    struct Node *next;
    struct Node *nextAnagram;
} Node;

// Function prototypes
Node* make_node(char *word);
Node* insert(Node *head, char *word);
void insertAnagram(Node *head, char *word);
void printWordAndAnagrams(Node *first);
void printList(Node *head);
int isAnagram(char *word1, char *word2);

// Make my node
Node* make_node(char *word){
    // create node of node size
    Node *new_node = (Node*) malloc(sizeof(Node));
    // return 1 if couldn't make the space
    if (new_node == NULL){
        fprintf(stderr, "Memory allocation failed. \n");
        exit(1);
    }
    // find length of word
    int length = 0;
    while (word[length] != '\0'){
        length++;
    }
    //Make malloc for word of proper size
    new_node->word = malloc((length + 1) * sizeof(char));
    if (new_node->word == NULL){
        // exiting on fail
        fprintf(stderr, "Memory allocation failed\n");
        free(new_node);
        exit(1);
    }
    //Copy word found into stored word
    strcpy(new_node->word,word);
    new_node->next = NULL;
    new_node->nextAnagram = NULL;
    return new_node;
}

// insert word into node list
Node* insert (Node *head, char *word){
    //if empty, we add onto our list
    if (head == NULL){
        Node *new_Node = make_node(word);
        return new_Node;
    }
    // will go until hitting null or finding word
    Node *curr = head;
    Node *prev = NULL;
    while (curr != NULL){
        prev = curr;
        if (isAnagram(curr->word,word) == 1){
            insertAnagram(curr,word);
            return head;
        }
        curr = curr->next;
    }
    //make last of list newest node
    prev->next = make_node(word);
    //return head
    return head;
} 

// when found word that is original, insert it at end of anagram list
void insertAnagram(Node *head, char *word){
    // this function only called if head is not null so only checking if next null
    if (head->nextAnagram == NULL){
        head->nextAnagram = make_node(word);
        return;
    }
    // goes until becoming last node in list, appending new node anagram
    Node *currAlagram = head;
    while (currAlagram->nextAnagram != NULL){
        currAlagram = currAlagram->nextAnagram;
    }
    currAlagram->nextAnagram = make_node(word);
}

//Goes in and prints word and its anagrams
void printWordAndAnagrams(Node *first){
    Node *curr = first;
    while (curr->nextAnagram != NULL){
        printf("%s ", curr->word);
        Node *next = curr->nextAnagram;
        curr = next;
    }
    printf("%s\n", curr->word);
}

// goes and tells to print each word and anagrams given function above
void printList(Node *head){
    if (head == NULL){
        return;
    }
    Node *curr = head;
    while (curr->next != NULL){
        printWordAndAnagrams(curr);
        curr = curr->next;
    }
    printWordAndAnagrams(curr);
}

//Checks if two words are anagrams of each other
int isAnagram(char *word1, char *word2){
    //if differient lengths, can't be anagram
    if (strlen(word1) != strlen(word2)){
        return 0;
    }
    //checks each letter and see if counts match per letter
    int letterCount1;
    int letterCount2;
    int wordLength = strlen(word1);
    for (int i = 0; i < wordLength; i ++){
        letterCount1 = 0;
        letterCount2 = 0;
        char letter = tolower(word1[i]);
        for (int x = 0; x < wordLength; x ++){
            if (letter == tolower(word1[x])){
                letterCount1 ++;
            }
            if (letter == tolower(word2[x])){
                letterCount2 ++;
            }
        }
        //if any letter count doesn't match, can't be anagram
        if (letterCount1 != letterCount2){
            return 0;
        }
    }
    //this is an anagram
    return 1;

}

int main(){
    //keep track of fact if we have encountered error
    int error = 0;
    //create input
    char *input = malloc(65 *sizeof(char));
    //ensure creates
    if (input == NULL){
        printf("Memory allocation failed\n");
        return 1;
    }
    //beings head node
    Node *head = NULL;
    int currError = 0;
    // scans each word, adding to list
    while (scanf("%s", input) != EOF){
        int size = strlen(input);
        currError = 0;
        //checks if not letter
        for (int i = 0; i < size;i ++){
            if (!isalpha(input[i])){
                error = 1;
                currError = 1;
            }
        }
        //if not letter found, skip word and tell error output
        if (currError == 1){
            fprintf(stderr, "found non-letter character\n");
            continue;
        }
        //insert word into list of nodes
        head = insert(head,input);
    }
    printList(head);
    free(input);
    return error;
}
