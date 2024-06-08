#include "phonebook.h"
#include "menu.h"

int main()
{
    int inputMenu;
    char inputSearch[50];
    char newName[50];
    char newNumber[13];

    loadFromFile("data.txt");
    while (true)
    {
        system("cls");
        printMenu();
        scanf(" %d", &inputMenu);
        switch (inputMenu)
        {
        case 1:
            system("cls");
            if (root == NULL)
            {
                printf("Kontak kosong");
            }
            printAllNode(root);
            printf("\nEnter untuk melanjutkan------ ");
            getch();
            break;
        case 2:
            system("cls");
            inputData();
            break;
        case 3:
            system("cls");
            if (root == NULL)
            {
                printf("Kosong");
                getch();
                break;
            }
            while ((getchar()) != '\n')
                ;
            printf("inputkan nama yang ingin dicari : ");
            scanf("%[^\n]%*c", inputSearch);
            toCapitalizeCase(inputSearch); // Ubah nama yang diinput menjadi kapital case
            printf("\n");
            search(root, inputSearch);
            printf("\nEnter untuk melanjutkan------ ");
            getch();
            break;
        case 4:
            system("cls");
            while ((getchar()) != '\n');
            printf("Inputkan nama yang ingin diupdate: ");
            fgets(inputSearch, sizeof(inputSearch), stdin);
            inputSearch[strcspn(inputSearch, "\n")] = '\0'; // Menghilangkan newline dari akhir input
            toCapitalizeCase(inputSearch);

            printf("Inputkan nama baru (tekan enter jika tidak ingin mengubah nama): ");
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = '\0'; // Menghilangkan newline dari akhir input

            printf("Inputkan nomor telepon baru (tekan enter jika tidak ingin mengubah nomor telepon): ");
            fgets(newNumber, sizeof(newNumber), stdin);
            newNumber[strcspn(newNumber, "\n")] = '\0'; // Menghilangkan newline dari akhir input

            updateContact(root, inputSearch, strlen(newName) > 0 ? newName : NULL, strlen(newNumber) > 0 ? newNumber : NULL);

            printf("\nEnter untuk melanjutkan------ ");
            getch();
            break;
        case 5:
            system("cls");
            while ((getchar()) != '\n');
            printf("inputkan nama yang ingin dihapus : ");
            scanf("%[^\n]%*c", inputSearch);
            toCapitalizeCase(inputSearch); // Ubah nama yang diinput menjadi kapital case
            printf("\n");
            root = deleteContact(root, inputSearch);
            printf("Kontak berhasil dihapus.\n");
            printf("Enter untuk melanjutkan------ ");
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
