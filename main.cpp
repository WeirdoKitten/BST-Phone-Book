#include "phonebook.h"
#include "menu.h"

int main()
{
    int inputMenu;
    char inputSearch[50];
    while (true)
    {
        system("cls");
        printMenu();
        scanf(" %d", &inputMenu);
        switch (inputMenu)
        {
        case 1:
            system("cls");
            printAllNode(root);
            getch();
            break;
        case 2:
            system("cls");
            inputData();
            break;
        case 3:
            system("cls");
            while((getchar())!='\n');
            printf("inputkan nama yang ingin dicari : ");
            scanf("%[^\n]%*c", inputSearch);
            printf("\n");
            search(root, inputSearch);
            getch();

            break;
        case 6:
            exit(false);
            break;
        default:
            break;
        }
    }

    return 0;
}