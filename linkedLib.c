#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//book object -> has author, year made and the name of the book
typedef struct book {
    char author[100];
    int year;
    char bookName[100];

    struct book *next; //pointer to the next book (linked list)
} book;


//all functions used
book *createBook(char *author, char* bookName, int year);
void addBook(book** head, char* author, char* bookName, int year);
void displayAllBooks(book* head);
void findBook(book* head, char *name);

void insertBookPos();
void removeBook(book** head, char* name);


//createBook makes new book node || createBook is a pointer as malloc can not be operated off static object's (only works if pointer)
book *createBook(char *author, char* bookName, int year)
{
    book* newBook = (book*)malloc(sizeof(book)); //allocated memory for new book

    strcpy(newBook->author, author);
    strcpy(newBook->bookName, bookName);

    newBook->year = year;
    newBook->next = NULL;

    return newBook;
}


// addBook, adds book to library || book** is a double pointer as if it is only one pointer we wouldnt be able to change the value of head
void addBook(book** head, char* author, char* bookName, int year)
{
    book* newBook = createBook(author, bookName, year);
    if (*head == NULL)
    {
        *head = newBook;
    }
    else
    {
        book* temp = *head; //creates a temp book, which holds the first book in the list, effectively tranversing through the linked list
        while (temp->next != NULL)
        {
            temp = temp->next; //goes to the next book, as temp->next points to the next book in the next list
        }
        temp->next = newBook; //once it finds the last book, the node with a NULL pointer, it sets the newBook as the last node in the linked list
    }

    printf("%s has been successfully added!\n");
}

void displayAllBooks(book* head) //only book* head as we dont want to modify the head
{
    if (head == NULL)
    {
        printf("There are no books in the current library!!!");
        return;
    }

    book* current = head;
    while (current != NULL)
    {
        printf("Author: %s \t Year: %d \t Name: %s \n", current->author, current->year, current->bookName);
        current = current->next;
    }
}

void findBook(book* head, char *name)
{
    int count = 0;
    book* current = head;
    while (current != NULL)
    {
        count++;
        if (strcmp(current->bookName, name) == 0)
        {
            printf("The book %s is at position %d\n", name, count);
            return;
        }
        else {
            current = current->next;
        }

    }

    printf("The book is not in the library\n");
    
}

void removeBook(book** head, char* name)
{   

    book* current = *head;
    book* previous = NULL;

    while (current != NULL)
    {
        if (strcmp(current->bookName, name) == 0)
        {
            if (previous == NULL)
            {
                *head = current->next; //edge case for when the first book is the one to be skipped
            }
            else
            {   
                previous->next = current->next; //skips currrent node
            }

            free(current);
            return;
        }
        previous = current;
        current = current->next;

    }


}

int main()
{
    book* library = NULL;

    addBook(&library, "Auth1", "Book 1", 1);
    addBook(&library, "Auth2", "Book 2", 2);
    addBook(&library, "Auth3", "Book 3", 3);
    addBook(&library, "Auth4", "Book 4", 4);

    printf("\n");

    displayAllBooks(library);

    printf("\n");

    findBook(library, "Book 1");

    printf("\n");

    removeBook(&library, "Book 1");

    printf("\n");

    displayAllBooks(library);

    printf("\n");

    findBook(library, "Book 1");

    printf("\n");

    return 0;
}