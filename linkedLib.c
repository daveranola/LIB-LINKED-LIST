#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//book object -> has author, year made and the name of the book
typedef struct book {
    char author[100], bookName[100];
    int year;
    bool available;

    struct book *next; //pointer to the next book (linked list)
} book;


//all functions used / function prototypes
void printLine(); //formatting makes it look nice

book *createBook(char *author, char* bookName, int year, bool status);
void addBook(book** head, char* author, char* bookName, int year, bool status);
void displayAllBooks(book* head); 
void findBook(book* head, char *name); //finds a book with the given name
void removeBook(book** head, char* name); //used to remove book with matching name
void insertBookPos(book** head, int pos, char *author, char* bookName, int year); //inserts a book at the given pos
void deleteBookPos(book** head, int pos); //deletes a book at the given pos
void borrowBook(book* head, int pos);
void returnBook(book* head, int pos);

void saveLib(book* head);
void loadLib(book** head);


void printLine()
{
    printf("-----------------------------------------------------------------------------\n");
}

//createBook makes new book node || createBook is a pointer as malloc can not be operated off static object's (only works if pointer)
book *createBook(char *author, char* bookName, int year, bool status)
{
    book* newBook = (book*)malloc(sizeof(book)); //allocated memory for new book

    strcpy(newBook->author, author);
    strcpy(newBook->bookName, bookName);

    newBook->year = year;
    newBook->available = status;
    newBook->next = NULL;

    return newBook;
}

// addBook, adds book to library || book** is a double pointer as if it is only one pointer we wouldnt be able to change the value of head
void addBook(book** head, char* author, char* bookName, int year, bool status)
{
    book* newBook = createBook(author, bookName, year, status);
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
    char status;

    printf("%-10s %-20s %-10s %-20s %-10s\n", "Position", "Author", "Year", "Book Name", "Status");

    printLine();

    book* current = head;


    while (current != NULL)
    {
        pos++;


        if (current->available)
        {
            status = 'Y';
        }
        else if (!current->available)
        {
            status = 'N';
        }

        printf("%-10d %-20s %-10d %-20s %-10c\n", pos, current->author, current->year, current->bookName, status);
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
        book* new = createBook(author, bookName, year, true);
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

    book* new = createBook(author, bookName, year, true);
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

void borrowBook(book* head, int pos)
{
    int count = 1;
    book* temp = head;

    while (temp != NULL && count != pos)
    {
        temp=temp->next;
    }

    if (temp->available == false)
    {
        printf("Book is being lended at this time!\n");
        printLine();
        return;
    }

    temp->available = false;

    printf("\"%s\" by \"%s\" has been successfully borrowed!\n", temp->bookName, temp->author);
    printLine();
}

void returnBook(book* head, int pos)
{
    int count = 1;
    book* temp = head;
    while (temp != NULL && pos != count)
    {
        temp = temp->next;
    }

    if (temp->available == true)
    {
        printf("Book is already there!\n");
        printLine();
        return;
    }

    temp->available = true;

    printf("\"%s\" by \"%s\" was returned successfully!\n", temp->bookName, temp->author);
    printLine();

}

void saveLib(book* head)
{
    FILE *fp = fopen("library.txt", "w"); 

    book* temp = head;


    while (temp != NULL)
    {
        fprintf(fp, "%s,%d,%s,%d\n", temp->author, temp->year, temp->bookName, temp->available);
        temp = temp->next;
    }

    fclose(fp);
    

}

void loadLib(book** head)
{
    FILE *fp = fopen("library.txt", "r");

    char author[100], bookName[100];
    int year;
    int available;

    while(fscanf(fp, "%99[^,],%d,%99[^,],%d\n", author, &year, bookName, &available) != EOF) //[^,] is called a delimiter, reads up to a coma and includes spaces. only used on strings, cannot be used on int's
    {
        addBook(head, author, bookName, year, available);
    }
    fclose(fp);
}

int main()
{
    book* library = NULL;
    int choice, year, pos = 0;
    char author[100], bookName[100];

    // addBook(&library, "Auth 1", "Book 1", 2001, true);
    // addBook(&library, "Auth 2", "Book 2", 2002, true);
    // addBook(&library, "Auth 3", "Book 3", 2003, true);
    // addBook(&library, "Auth 4", "Book 4", 2004, true);

    loadLib(&library);

    while (1)
    {
        printf("1. Add book \n2. Remove book \n3. Insert book\n4. Display library\n5. Borrow book\n6. Return book\n7. Exit\n");
        printLine();
        scanf("%d", &choice);
        printLine();
        while (getchar() != '\n');

        switch (choice)
        {
            case 1:
            {
                printf("Enter author name: \n");
                //printLine();
                fgets(author, sizeof(author), stdin);
                author[strlen(author) - 1] = '\0';
                printf("Enter book name: \n");
                // printLine();
                fgets(bookName, sizeof(bookName), stdin);
                bookName[strlen(bookName) - 1] = '\0';
                printf("Enter the year published: \n");
                // printLine();
                scanf("%d", &year);
                printLine();
                addBook(&library, author, bookName, year, true);
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

                    pos = 0;

                }

                else if (pos == 2)
                {
                    printf("Enter book name: \n");
                    fgets(bookName, sizeof(bookName), stdin);
                    bookName[strlen(bookName)] = '\0';
                    printLine();
                    removeBook(&library, bookName);
                    displayAllBooks(library);

                    pos = 0;
                }

                break;
            }
                     
            case 3:
            {
                displayAllBooks(library);
                printf("Enter position to insert at: \n");
                scanf("%d", &pos);

                printf("Enter author name: \n");
                //printLine();
                fgets(author, sizeof(author), stdin);
                author[strlen(author)] = '\0';
                printf("Enter book name: \n");
                // printLine();
                fgets(bookName, sizeof(bookName), stdin);
                bookName[strlen(bookName)] = '\0';
                printf("Enter the year published: \n");
                // printLine();
                scanf("%d", &year);
                printLine();

                insertBookPos(&library, pos, author, bookName, year);

                displayAllBooks(library);

                pos = 0;
                break; 
            }

            case 4:
            {
                displayAllBooks(library);
                break;
            }

            case 5:
            {
                printf("Enter the book position you want to borrow: \n");

                printLine();

                displayAllBooks(library);

                scanf("%d", &pos);
                
                printLine();

                borrowBook(library, pos);

                // displayAllBooks(library);

                pos = 0;

                break;
            }

            case 6:
            {
                printf("Enter the book position you want to return: \n");

                printLine();

                displayAllBooks(library);

                scanf("%d", &pos);
                
                printLine();

                returnBook(library, pos);

                // displayAllBooks(library);

                pos = 0;

                break;
            }

            case 7:
            {
                printf("Exiting...");

                saveLib(library);

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