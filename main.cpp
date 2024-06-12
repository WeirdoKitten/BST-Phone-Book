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
        bool ditemukan = false;
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
            search(root, inputSearch, &ditemukan);
            if (ditemukan == false)
            {
                printf("\nTidak ada...");
            }
            printf("\nEnter untuk melanjutkan------ ");
            getch();
            break;
        case 4:
            system("cls");
            while ((getchar()) != '\n')
                ;
            printf("Cari nama kontak yang ingin update : ");
            scanf("%[^\n]%*c", inputSearch);
            toCapitalizeCase(inputSearch); // Ubah nama yang diinput menjadi kapital case
            search(root, inputSearch, &ditemukan);
            if (ditemukan == false)
            {
                printf("\nKosong\nEnter untuk melanjutkan------ ");
                getch();
                goto break_case4;
            }
            printf("\nEnter untuk melanjutkan------ ");
            while ((getchar()) != '\n')
                ;
            printf("Inputkan nama yang ingin diupdate: ");
            fgets(inputSearch, sizeof(inputSearch), stdin);
            inputSearch[strcspn(inputSearch, "\n")] = '\0'; // Menghilangkan newline dari akhir input
            toCapitalizeCase(inputSearch);

            printf("Inputkan nama baru (tekan enter jika tidak ingin mengubah nama): ");
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = '\0'; // Menghilangkan newline dari akhir input
            toCapitalizeCase(newName);

            printf("Inputkan nomor telepon baru (tekan enter jika tidak ingin mengubah nomor telepon): ");
            fgets(newNumber, sizeof(newNumber), stdin);
            newNumber[strcspn(newNumber, "\n")] = '\0'; // Menghilangkan newline dari akhir input

            updateContact(root, inputSearch, strlen(newName) > 0 ? newName : NULL, strlen(newNumber) > 0 ? newNumber : NULL, 0);

            printf("\nEnter untuk melanjutkan------ ");
            getch();
        break_case4:
            break;
        case 5:
            system("cls");
            while ((getchar()) != '\n')
                ;
            printf("Cari nama kontak yang ingin dihapus: ");
            scanf("%[^\n]%*c", inputSearch);
            toCapitalizeCase(inputSearch); // Ubah nama yang diinput menjadi kapital case
            search(root, inputSearch, &ditemukan);
            if (ditemukan == false)
            {
                printf("\nKosong\nEnter untuk melanjutkan------ ");
                getch();
                goto break_case5;
            }
            printf("\nEnter untuk melanjutkan------ ");
            while ((getchar()) != '\n')
                ;
            printf("inputkan nama yang ingin dihapus : ");
            scanf("%[^\n]%*c", inputSearch);
            toCapitalizeCase(inputSearch); // Ubah nama yang diinput menjadi kapital case
            printf("\n");
            root = deleteContact(root, inputSearch);
            printf("Kontak berhasil dihapus.\n");
            printf("Enter untuk melanjutkan------ ");
            getch();
        break_case5:
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
