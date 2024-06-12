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
            printBanner();
            printf("\n\n");
            if (root == NULL)
            {
                printf("\t\t\t\tKontak Tidak Tersedia");
            }
            printAllNode(root);
            printf("\n\t\t\t\tEnter untuk melanjutkan------ ");
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
                printBanner();
                printf("\n\n\n\t\t\t\tData Tidak Tersedia");
                getch();
                break;
            }
            while ((getchar()) != '\n');
            printBanner();
            printf("\n\n\n\t\t\t\t\tinputkan nama yang ingin dicari : ");
            scanf("%[^\n]%*c", inputSearch);
            toCapitalizeCase(inputSearch); // Ubah nama yang diinput menjadi kapital case
            printf("\n");
            printf("\t\t\t\tBerikut adalah nama-nama kontak yang sesuai:\n\n");
            search(root, inputSearch, &ditemukan);
            if (ditemukan == false)
            {
                printf("\n\t\t\t\t\tKontak Tidak Ditemukan...");
            }
            printf("\n\t\t\t\t\tEnter untuk melanjutkan------ ");
            getch();
            break;
        case 4:
            system("cls");
            while ((getchar()) != '\n');
            printBanner();
            printf("\n\n\n\t\t\t\t\tCari nama kontak yang ingin update : ");
            scanf("%[^\n]%*c", inputSearch);
            toCapitalizeCase(inputSearch); // Ubah nama yang diinput menjadi kapital case
            printf("\t\t\t\tBerikut adalah nama-nama kontak yang sesuai:\n\n");
            search(root, inputSearch, &ditemukan);
            if (ditemukan == false)
            {
                printf("\n\t\t\t\tKontak Tidak Ditemukan\n\t\t\t\tEnter untuk melanjutkan------ ");
                getch();
                goto break_case4;
            }
            printf("\n\t\t\t\tEnter untuk melanjutkan------ ");
            while ((getchar()) != '\n');
            printf("\t\t\t\t\tInputkan nama yang ingin diupdate: ");
            fgets(inputSearch, sizeof(inputSearch), stdin);
            inputSearch[strcspn(inputSearch, "\n")] = '\0'; // Menghilangkan newline dari akhir input
            toCapitalizeCase(inputSearch);

            printf("\t\t\t\t\tInputkan nama baru (tekan enter jika tidak ingin mengubah nama): ");
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = '\0'; // Menghilangkan newline dari akhir input
            toCapitalizeCase(newName);

            printf("\t\t\t\t\tInputkan nomor telepon baru (tekan enter jika tidak ingin mengubah nomor telepon): ");
            fgets(newNumber, sizeof(newNumber), stdin);
            newNumber[strcspn(newNumber, "\n")] = '\0'; // Menghilangkan newline dari akhir input

            updateContact(root, inputSearch, strlen(newName) > 0 ? newName : NULL, strlen(newNumber) > 0 ? newNumber : NULL, 0);

            printf("\n\t\t\t\t\tEnter untuk melanjutkan------ ");
            getch();
        break_case4:
            break;
        case 5:
            system("cls");
            printBanner();
            while ((getchar()) != '\n');
            printf("\n\n\n\t\t\t\t\tCari nama kontak yang ingin dihapus: ");
            scanf("%[^\n]%*c", inputSearch);
            toCapitalizeCase(inputSearch); // Ubah nama yang diinput menjadi kapital case
            printf("\t\t\t\tBerikut adalah nama-nama kontak yang sesuai:\n\n");
            search(root, inputSearch, &ditemukan);
            if (ditemukan == false)
            {
                printf("\n\t\t\t\tKontak Tidak Ditemukan\n\t\t\t\tEnter untuk melanjutkan------ ");
                getch();
                goto break_case5;
            }
            printf("\n\t\t\t\tEnter untuk melanjutkan------ ");
            while ((getchar()) != '\n');
            printf("\t\t\t\t\tinputkan nama yang ingin dihapus : ");
            scanf("%[^\n]%*c", inputSearch);
            toCapitalizeCase(inputSearch); // Ubah nama yang diinput menjadi kapital case
            printf("\n");
            root = deleteContact(root, inputSearch);
            printf("\t\t\t\t\tKontak berhasil dihapus.\n");
            printf("\t\t\t\t\tEnter untuk melanjutkan------ ");
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
