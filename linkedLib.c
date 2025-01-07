#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//book object -> has author, year made and the name of the book
typedef struct book {
    char author[100], bookName[100];
    int year;
    

    struct book *next; //pointer to the next book (linked list)
} book;


//all functions used
void printLine(); //formatting makes it look nice

book *createBook(char *author, char* bookName, int year);
void addBook(book** head, char* author, char* bookName, int year);
void displayAllBooks(book* head); 
void findBook(book* head, char *name); //finds a book with the given name
void removeBook(book** head, char* name); //used to remove book with matching name
void insertBookPos(book** head, int pos, char *author, char* bookName, int year); //inserts a book at the given pos
void deleteBookPos(book** head, int pos); //deletes a book at the given pos

void printLine()
{
    printf("-----------------------------------------------------------------------------\n");
}

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

    printf("\"%s\" has been successfully added!\n");
    printLine();
}

void displayAllBooks(book* head) //only book* head as we dont want to modify the head
{
    // if (head == NULL)
    // {
    //     printf("There are no books in the current library!!!\n");
    //     return;
    // }

    int pos = 0;

    book* current = head;
    while (current != NULL)
    {
        pos++;
        printf("Position: %d \t Author: %s \t Year: %d \t Name: %s \n", pos, current->author, current->year, current->bookName);
        current = current->next;
    }
    printLine();
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
    printLine();
    
}

void removeBook(book** head, char* name)
{   

    book* current = *head;
    book* previous = NULL;

    if (*head == NULL)
    {
        printf("The library is empty!\n");
        return;
    }

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

    printf("\"%s\" has beed successfully removed!\n", name);
    printLine();
}

void insertBookPos(book** head, int pos, char *author, char* bookName, int year)
{
    //edge case
    if (pos == 1)
    {   
        book* new = createBook(author, bookName, year);
        new->next = *head;
        *head = new;
        return;
    }

    if (pos < 1)
    {
        printf("Invalid Position!");
        printLine();
        return;
    }

    int count = 1;

    book* prev = *head;

    while (count < pos - 1 && prev != NULL)
    {
        prev = prev->next;
        count++;
    }

    book* new = createBook(author, bookName, year);
    new->next = prev->next;
    prev->next = new;

}

void deleteBookPos(book** head, int pos)
{
    //edge cases
    if (*head == NULL)
    {
        printf("The library is empty!\n");
        return;
    }

    if (pos == 1)
    {
       book* prev = *head;
       *head = prev->next;
       free(prev);
       return; 
    }

    if (pos < 1 || *head == NULL)
    {
        printf("Invalid Position!");
        return;
    }

    int count = 1;
    book* current = *head;
    book* prev =  NULL;

    while (count != pos && current != NULL)
    {
        prev = current;
        current = current->next;
        count++;
    }

    if (current == NULL)
    {
        printf("The position is out of range!");
    }

    printf("\"%s\" has been successfully removed!", current->bookName);
    printLine();

    prev->next = current->next; //skips node to be deleted
    free(current); //deletes node


    


}

int main()
{
    book* library = NULL;
    int choice, year, pos = 0;
    char author[100], bookName[100];

    while (1)
    {
        printf("1. Add book \n2. Remove book \n3. Display library\n4. Insert book\n5. Exit\n");
        printLine();
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                printf("Enter author name: \n");
                //printLine();
                scanf("%s", author);
                printf("Enter book name: \n");
                // printLine();
                scanf("%s", bookName);
                printf("Enter the year published: \n");
                // printLine();
                scanf("%d", &year);
                printLine();
                addBook(&library, author, bookName, year);
                displayAllBooks(library);
                break;
            }
            case 2:
            {
                printf("Remove book by:\n1. Position\n2. Name\n");
                scanf("%d", &pos);

                if (pos == 1)
                {
                    int del;

                    displayAllBooks(library);

                    printf("Enter position: \n");
                    scanf("%d", del);

                    printLine();

                    deleteBookPos(&library, del);

                    printLine();

                    displayAllBooks(library);

                }

                else if (pos == 2)
                {
                    printf("Enter book name: \n");
                    scanf("%s", bookName);
                    printLine();
                    removeBook(&library, bookName);
                    displayAllBooks(library);
                }

                break;
            }
                
            case 3:
            {
                displayAllBooks(library);
                break;
            }
                
            case 4:
            {
                displayAllBooks(library);
                printf("Enter position to insert at: \n");
                scanf("%d", &pos);

                printf("Enter author name: \n");
                //printLine();
                scanf("%s", author);
                printf("Enter book name: \n");
                // printLine();
                scanf("%s", bookName);
                printf("Enter the year published: \n");
                // printLine();
                scanf("%d", &year);
                printLine();

                insertBookPos(&library, pos, author, bookName, year);

                displayAllBooks(library);
                break; 
            }

            case 5:
            {
                printf("Exiting...");
                while(library != NULL)
                {
                    book* temp = library;
                    library = library->next;
                    free(temp);
                }
                printf("Successfully exited!!!");
                return 0;
            }
                
            default:
            {
                printf("Please enter a valid option!\n");
                break; 
            }
                
        }
    }

    

}