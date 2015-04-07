#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define ALPHABET_SIZE 26

typedef struct n
{
    bool isEndOfWord;
    struct n *next[ALPHABET_SIZE];
} Node;

Node *CreateNode()
{
    Node *temp;
    int i;
    temp = malloc(sizeof(Node));
    temp->isEndOfWord = false;
    for(i=0;i<ALPHABET_SIZE;i++)
        temp->next[i] = NULL;
    return temp;
}

void insertWord(Node *root,char word[])
{
    Node *temp;
    temp = root;
    int i,idx;
    for(i=0;word[i]!='\0';i++)
    {
        idx = word[i] - 'a';
        if(temp->next[idx]== NULL)
            temp->next[idx] = CreateNode();
        temp = temp->next[idx];

    }
    temp->isEndOfWord = true;
    printf("Inserted\n");
}

void PrintAllWords(Node *root,char prefix[])
{
    int i;
    if(root->isEndOfWord)
        printf("\n%s",prefix);

    for(i=0;i<ALPHABET_SIZE;i++)
    {
        if(root->next[i]!=NULL)
        {
            int len = strlen(prefix);
            //printf("%s\n",prefix);
            //newPrefix creation
            char *newPrefix = malloc(len+2);//for null character new char
            strcpy(newPrefix,prefix);
            newPrefix[len] = i+'a';
            newPrefix[len+1] = '\0';
            PrintAllWords(root->next[i],newPrefix);
            free(newPrefix);
        }

    }

}

void AutoSuggest(Node *root,char prefix[])
{
    int i,idx;
    int len = strlen(prefix);
    Node *temp;
    temp = root;
    for(i=0;prefix[i]!='\0';i++)
    {
        idx = prefix[i] - 'a';
        if(temp->next[idx]!=NULL)
        {
            temp = temp->next[idx];

        }
    }
    PrintAllWords(temp,prefix);

}

int showMenu()
{
    int choice;
    printf("\nMenu\n");

    printf("=====\n");
    printf("1. Insert word\n");
    printf("2. Auto suggest word\n");
    printf("3. Print words\n");
    printf("4. Exit\n");
    printf("Your Choice: ");
    scanf("%d",&choice);
    return choice;

}



int main()
{
    //printf("Hello world!\n");
    int ch;
    FILE *fp;
    char word[100];
    Node *root = CreateNode();

    while(1)
    {
        ch = showMenu();
        switch(ch)
        {
        case 1:
            //printf("Enter Word:\n");
            //scanf("%s",word);
            fp = fopen("dictionary.txt","r");
            if(fp!=NULL)
            {
                while(!feof(fp)){
                    fscanf(fp,"%s",word);
                    insertWord(root,word);
                }

            }
            else
            {
                printf("\nWrong file path\n");
                return -1;
            }
            fclose(fp);
            break;
        case 2:
            scanf("%s",word);
            AutoSuggest(root,word);
            break;
        case 3:
            PrintAllWords(root,"");
            break;
        case 4:
            return 0;
        default:
            printf("\nBad choice...\n");
        }

    }
    return 0;
}
