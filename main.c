//abdallh kokash-----1220116-----sec3
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//definitions
typedef struct node *node;
typedef struct info *hashArray;
//////////////////////////////////////////
//structure
struct node {
    char element[50];
    int frequency;
    int height;
    struct node *left;
    struct node *right;
};

struct info {
    char element[50];
    int frequency;
};


////////////////////////////////////////
//global
char string[2000] = "";
char treeStrings[1000] = "";
int treeFreq[100];
node tree;
hashArray hash = NULL;
int checkPrint = 0;
int hashCapacity = 0;
int hashSize = 0;
int full = 0;
int treeSize = 0;
int hashChecking = 0;
int threshold = 2;
//////////////////////////////////////
//functions
void load();

node find(char x[50], node t);

int max(int Lhs, int Rhs);

int height(node t);

void creatAvl();

node singleRotateWithright(node k1);

node singleRotateWithleft(node k2);

node doubleRotateWithleft(node k3);

node doubleRotateWithright(node k4);

node insert(char x[50], node t);

void insertWord(node t);

node delete(char x[50], node t);

node findMin(node t);

void deleteWord(node t);

void print(node t);

int hashFunc1(char word[50]);

int isPrime(int value);

int hashFunc2(char word[50]);

node makeEmpty(node t);

hashArray hashInitialization();

void createHash(hashArray hash);

hashArray rehash(hashArray hash);

hashArray checkCapacity(hashArray hash);

void hashInesrt(hashArray hash);

void to_lower(char *word);

void findHash(hashArray hash);

int findAddress(hashArray hash, char word[30]);

void hashDelete(hashArray hash);

void treeS(node t);

void statistics(hashArray hash);

int main(void) {
    int op;
    do {
        printf("\nmenu\n");
        printf("1.Load the input.\n");
        printf("2.Create the AVL tree.\n");
        printf("3.Insert a word to the AVL tree.\n");
        printf("4.Delete a word from the AVL tree.\n");
        printf("5.Print the words as sorted in the AVL tree.\n");
        printf("6.Create the Hash table.\n");
        printf("7.Insert a word to the Hash table.\n");
        printf("8.Delete a word from the hash table.\n");
        printf("9.Search for a word in the hash table and print its frequency.\n");
        printf("10. Print words statistics.\n");
        printf("11. Exit the application.\n");
        printf("please enter operation: ");
        //here we check if the input entered by the user is not a character
        while (scanf("%d", &op) != 1) {
            while (getchar() != '\n') {
            }
            printf("invalid input\n");
        }
        switch (op) {
            case 1:
                load();
                break;
            case 2:
                creatAvl();
                break;
            case 3:
                insertWord(tree);
                break;
            case 4:
                deleteWord(tree);
                break;
            case 5:
                printf("\n");
                if (checkPrint == 0)
                    printf("AVL not created\n");
                else
                    print(tree);
                break;
            case 6:
                printf("\n");
                if (tree != NULL) {
                    if (hashChecking == 0) {
                        treeS(tree);
                        hashCapacity = (treeSize * 2) + 1;
                        while (isPrime(hashCapacity) == 0)
                            hashCapacity++;
                        hash = hashInitialization();
                        if (hash == NULL)
                            printf("no memory sapce\n");
                        else {
                            createHash(hash);
                            printf("hash was created succesfully\n");
                            hashChecking = 1;

                        }
                    } else
                        printf("hash already created\n");
                } else
                    printf("tree was not created\n");
                break;
            case 7:
                printf("\n");
                hashInesrt(hash);
                hash = checkCapacity(hash);
                break;
            case 8:
                printf("\n");
                hashDelete(hash);
                break;
            case 9:
                printf("\n");
                findHash(hash);
                break;
            case 10:
                statistics(hash);
                break;
            case 11:
                printf("exiting system.....\n");
                break;
            default:
                printf("not a correct operation!!...please enter a valid operation\n");
                break;
        }
    } while (op != 11);
}
//here we print the function statistics
void statistics(hashArray hash) {
    int uniqueCount = 0;
    int thresholdCount=0;
    printf("\n");
    if (hash == NULL) {
        printf("hash not created\n");
        return;
    }
    printf("unique words are: ");
    for (int i = 0; i < hashCapacity; i++) {
        if (hash[i].frequency == 1) {
            printf("%s-", hash[i].element);
            uniqueCount++;
        }
    }
    printf("%d\n", uniqueCount);
    printf("words repeated more than the threshhold: ");
    for (int i = 0; i < hashCapacity; i++) {
        if (hash[i].frequency >= threshold) {
            printf("%s-", hash[i].element);
            thresholdCount++;
        }
    }
    char maxWord[50];
    int mostFreq=0;
    printf("%d\n",thresholdCount);
    for (int i = 0; i < hashCapacity; i++) {
        if(hash[i].frequency>mostFreq) {
            mostFreq=hash[i].frequency;
            strcpy(maxWord,hash[i].element);
        }
    }
    printf("most frequent word is: %s\n",maxWord);

}
//here we load the text from the file
void load() {
    printf("\n");
    char line[100];
    FILE *input_file = fopen("input.txt", "r");
    if (input_file == NULL) {
        printf("error opening file\n");
    } else {
        while (fgets(line, sizeof(line), input_file) != NULL) {
            int i = 0;
            while (line[i] != '\0') {
                //here we check only for the alphapatical input and get rid of anything else
                if ((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z') || (line[i] == ' '))
                    strncat(string, &line[i], 1);
                i++;
            }
            strcat(string, " ");
        }
    }

    printf("file loaded successfully\n");
}
//here we create the avl tree using strtok we cut each space and get the word which then will be inserted in the tree using the insert function
void creatAvl() {
    printf("\n");
    if (tree != NULL) {
        tree = makeEmpty(tree);
    }
    if (string[0] == '\0') {
        printf("no data\n");
        return;
    }
    char copy[500];
    strcpy(copy, string);
    char *ptr = strtok(copy, " ");
    while (ptr != NULL) {
        tree = insert(ptr, tree);
        ptr = strtok(NULL, " ");
    }
    printf("AVL created successfully\n");
    checkPrint = 1;
}
//here we insert a word to the tree from the user while also checking if the user input is valid or not using the insert function
void insertWord(node t) {
    printf("\n");
    if (t == NULL) {
        printf("AVL not created\n");
        return;
    }
    char word[50];
    printf("enter the word you wish to insert\n");
    scanf("%s", word);
    for (int i = 0; i < strlen(word); i++) {
        if (!((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z'))) {
            printf("invalid input\n");
            return;
        }
    }

    insert(word, t);
    printf("insert was succesfull\n");
}
//here we delete a word from the avl tree  using the delete function
void deleteWord(node t) {
    printf("\n");
    if (t == NULL) {
        printf("AVL not created\n");
        return;
    }
    char word[50];
    printf("enter the word you wish to delete\n");
    scanf("%s", word);
    node test = find(word, t);
    if (test == NULL) {
        printf("word not found\n");
        return;
    }
    delete(word, t);
    printf("delete was successfull\n");
}
//here we print the avl tree in order
void print(node t) {
    if (t == NULL)
        return;
    print(t->left);
    printf("%s %d\n", t->element, t->frequency);
    print(t->right);
}
//here we create the hash from the tree each word is inserted using the hash function and any coliision that might happen is solved using double hashing
void createHash(hashArray hash) {
    int count = 0;
    char *prt = strtok(treeStrings, " ");
    while (prt != NULL) {
        char word[100];
        strcpy(word, prt);
        char wordLower[50];
        strcpy(wordLower, word);
        to_lower(wordLower);
        int frequency = treeFreq[count];
        int index = hashFunc1(wordLower);
        if (hash[index].frequency == 0) {
            strcpy(hash[index].element, word);
            hash[index].frequency = frequency;
            hashSize++;
        } else {
            int i = 1;
            while (hash[index].frequency != 0) {
                index = index + i * hashFunc2(wordLower);
                index = index % hashCapacity;
                i++;
            }
            strcpy(hash[index].element, word);
            hash[index].frequency = frequency;
            hashSize++;
        }
        prt = strtok(NULL, " ");
        count++;
    }
    hashChecking = 1;
}
//here we get the size of the tree so we can get the hashCapacity and store each word in a seperate array and the freq in another array so we can use it when we create the hash
void treeS(node t) {
    if (t == NULL)
        return;
    treeS(t->left);
    strcat(treeStrings, t->element);
    strcat(treeStrings, " ");
    treeFreq[treeSize] = t->frequency;
    treeSize++;
    treeS(t->right);
}
//here we insert to the hash
void hashInesrt(hashArray hash) {
    if (full == 0) {
        if (hash == NULL) {
            printf("hash not created\n");
            return;
        }
        printf("enter word you would like to insert\n");
        char word[50];
        scanf("%s", word);
        int a=0;
        while(word[a]!='\0') {
            if(!((word[a] >= 'A' && word[a] <= 'Z') || (word[a] >= 'a' && word[a] <= 'z'))) {
                printf("you can only insert alphapatical words\n");
                return;
            }
            a++;
        }
        char wordLower[50];
        strcpy(wordLower, word);
        to_lower(wordLower);
        int res = findAddress(hash, wordLower);
        if (res != -1) {
            hash[res].frequency++;
        }
        int index = hashFunc1(wordLower);
        if (hash[index].frequency == 0) {
            strcpy(hash[index].element, word);
            hash[index].frequency = 1;
            hashSize++;
        } else {
            int i = 1;
            while (hash[index].frequency != 0) {
                index = index + i * hashFunc2(wordLower);
                index = index % hashCapacity;
                i++;
            }
            strcpy(hash[index].element, word);
            hash[index].frequency = 1;
            hashSize++;
        }
        printf("insert was successful\n");
    } else
        printf("hash is full\n");
}
//here we delete form the hash
void hashDelete(hashArray hash) {
    if (hash == NULL) {
        printf("hash not created\n");
        return;
    }
    printf("enter word you would like to delete\n");
    char word[50];
    scanf("%s", word);
    char wordLower[50];
    strcpy(wordLower, word);
    to_lower(wordLower);
    int res = findAddress(hash, wordLower);
    if (res != -1) {
        hash[res].frequency = 0;
        strcpy(hash[res].element, "");
        hashSize--;
        printf("delete was successful\n");
    } else
        printf("word does not exist\n");
}
//this function is used by the insert and delete function to find the word the the user inserted
int findAddress(hashArray hash, char word[30]) {
    int i = 1;
    int index = hashFunc1(word);
    while (hash[index].element[0] != '\0') {
        if (strcasecmp(hash[index].element, word) == 0) {
            return index;
        }
        index = index + i * hashFunc2(word);
        index = index % hashCapacity;
        i++;
    }
    return -1;
}
//here we find the word that the user entered
void findHash(hashArray hash) {
    if (hash == NULL) {
        printf("hash not created\n");
        return;
    }
    printf("enter word to serch for\n");
    char word[50];
    scanf("%s", word);
    to_lower(word);
    int found = 0;
    int i = 1;
    int index = hashFunc1(word);
    while (hash[index].element[0] != '\0') {
        if (strcasecmp(hash[index].element, word) == 0) {
            printf("%s %d\n", hash[index].element, hash[index].frequency);
            found = 1;
            break;
        }
        index = index + i * hashFunc2(word);
        index = index % hashCapacity;
        i++;
    }
    if (found == 0) {
        printf("word does not exist\n");
    }
}
//here we check the capacity of the hash if the hash at 70% we need to rehash
hashArray checkCapacity(hashArray hash) {
    float result = ((float) hashSize / hashCapacity);
    if (result >= 0.7) {
        hashArray newHash = rehash(hash);
        if (newHash == NULL) {
            printf("memory is Full");
            full = 1;
            return hash;
        }
        return newHash;
    }
    return hash;
}
//this function is used to make another hash double the size of the old hash incase it reches 70%
hashArray rehash(hashArray hash) {
    int oldHashCapacity = hashCapacity;
    hashCapacity = (hashCapacity * 2) + 1;
    while (isPrime(hashCapacity) == 0)
        hashCapacity++;
    hashArray newHash = hashInitialization();
    if (newHash == NULL)
        return NULL;
    for (int i = 0; i < oldHashCapacity; i++) {
        int index;
        if (hash[i].frequency != 0) {
            char wordLower[50];
            strcpy(wordLower, hash[i].element);
            to_lower(wordLower);
            index = hashFunc1(wordLower);
            if (newHash[index].frequency == 0) {
                strcpy(newHash[index].element, hash[i].element);
                newHash[index].frequency = hash[i].frequency;
            } else {
                int k = 1;
                while (newHash[index].frequency != 0) {
                    index = index + k * hashFunc2(wordLower);
                    index = index % hashCapacity;
                    k++;
                }
                strcpy(newHash[index].element, hash[i].element);
                newHash[index].frequency = hash[i].frequency;
            }
        }
    }
    free(hash);
    return newHash;
}
//this function is used to Initialize the hash table
hashArray hashInitialization() {
    hashArray hash = (hashArray) malloc(sizeof(struct info) * hashCapacity);
    if (hash != NULL) {
        for (int i = 0; i < hashCapacity; i++) {
            hash[i].frequency = 0;
            strcpy(hash[i].element, "");
        }
    }
    return hash;
}
//this is the first hash function
int hashFunc1(char word[50]) {
    int hashValue = 0;
    int i = 0;
    while (word[i] != '\0') {
        hashValue = (hashValue << 5) + word[i];
        i++;
    }
    return hashValue % hashCapacity;
}
//this is the second hash function
int hashFunc2(char word[50]) {
    int hashValue = 0;
    int r = hashCapacity - 1;
    while (isPrime(r) != 1)
        r--;
    int i = 0;
    while (word[i] != '\0') {
        hashValue = (hashValue << 5) + word[i];
        i++;
    }
    return (r - (hashValue % r));
}
//this function is used to check if the element is prime or not
int isPrime(int value) {
    for (int i = 2; i < value - 1; i++) {
        if (value % i == 0)
            return 0;
    }
    return 1;
}
/*
from here on out the rest of the functions are standard AVL functions the insert and delete form the tree
insert,delete ,find ,findMin,findMax,height,and rotation functons for the balancing
 */
node find(char x[50], node t) {
    if (t == NULL)
        return NULL;
    else if (strcasecmp(x, t->element) < 0)
        return find(x, t->left);
    else if (strcasecmp(x, t->element) > 0)
        return find(x, t->right);
    else
        return t;
}

node findMin(node t) {
    if (t == NULL)
        return NULL;
    else if (t->left == NULL)
        return t;
    else
        return findMin(t->left);
}

node makeEmpty(node t) {
    if (t != NULL) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        free(t);
    }
    return NULL;
}

int max(int Lhs, int Rhs) {
    return Lhs > Rhs ? Lhs : Rhs;
}

int height(node t) {
    if (t == NULL)
        return -1;
    int leftheight = height(t->left);
    int rightheight = height(t->right);
    return 1 + max(leftheight, rightheight);
}

node singleRotateWithright(node k1) {
    node k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = height(k1);
    k2->height = height(k2);

    return k2; /* New root */
}

node singleRotateWithleft(node k2) {
    node k1;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = height(k2);
    k1->height = height(k1);

    return k1; /* New root */
}

node doubleRotateWithleft(node k3) {
    /* Rotate between k1 and k2 */
    k3->left = singleRotateWithright(k3->left);


    /* Rotate between k3 and k2 */
    return singleRotateWithleft(k3);
}

node doubleRotateWithright(node k4) {
    /* Rotate between k3 and k2 */
    k4->right = singleRotateWithleft(k4->right);

    /* Rotate between k1 and k2 */
    return singleRotateWithright(k4);
}

node insert(char x[50], node t) {
    if (t == NULL) {
        /* Create and return a one-node tree */
        t = malloc(sizeof(struct node));
        if (t == NULL)
            printf("Out of space!!!");
        else {
            strcpy(t->element, x);
            t->height = 0;
            t->frequency = 1;
            t->left = t->right = NULL;
        }
    } else if (strcasecmp(x, t->element) < 0) {
        t->left = insert(x, t->left);
        if (height(t->left) - height(t->right) == 2)
            if (strcasecmp(x, t->left->element) < 0)
                t = singleRotateWithleft(t);
            else
                t = doubleRotateWithleft(t);
    } else if (strcasecmp(x, t->element) > 0) {
        t->right = insert(x, t->right);
        if (height(t->right) - height(t->left) == 2)
            if (strcasecmp(x, t->left->element) > 0)
                t = singleRotateWithright(t);
            else
                t = doubleRotateWithright(t);
    } else {
        t->frequency++;
    }
    if (t != NULL)
        t->height = height(t);
    return t;
}

node delete(char x[50], node t) {
    node temp;
    if (strcasecmp(x, t->element) < 0)
        t->left = delete(x, t->left);
    if (height(t->left) - height(t->right) == 2)
        if (strcasecmp(x, t->left->element) < 0)
            t = singleRotateWithleft(t);
        else
            t = doubleRotateWithleft(t);
    else if (strcasecmp(x, t->element) > 0)
        t->right = delete(x, t->right);
    if (height(t->right) - height(t->left) == 2)
        if (strcasecmp(x, t->left->element) > 0)
            t = singleRotateWithright(t);
        else
            t = doubleRotateWithright(t);
    else {
        if (t->right && t->left) {
            temp = findMin(t->right);
            strcpy(t->element, temp->element);
            t->right = delete(t->element, t->right);
        } else {
            temp = t;
            if (t->left == NULL)
                t = t->right;
            else if (t->right == NULL)
                t = t->left;
            free(temp);
        }
    }
    if (t != NULL)
        t->height = height(t);
    return t;
}

void to_lower(char *word) {
    int i = 0;
    while (word[i] != '\0') {
        word[i] = tolower(word[i]);
        i++;
    }
}
