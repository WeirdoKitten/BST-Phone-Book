#include "phonebook.h"
#include "menu.h"

int main() {
    int inputMenu;
    char inputSearch[50];
    char newName[50];
    char newNumber[13];

    loadFromFile("data.txt");
    while (true) {
        system("cls");
        printMenu();
        scanf(" %d", &inputMenu);
        switch (inputMenu) {
            case 1:
                system("cls");
                if (root == NULL){printf("Kontak kosong");}
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
                while ((getchar()) != '\n');
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
                printf("Inputkan nama yang ingin diupdate: ");
                while((getchar())!='\n');
                scanf("%[^\n]%*c", inputSearch);
                toCapitalizeCase(inputSearch); // Ubah nama yang diinput menjadi kapital case
                printf("Inputkan nama baru (tekan enter jika tidak ingin mengubah nama): ");
                while ((getchar()) != '\n');
                scanf("%[^\n]%*c", newName);
                printf("Inputkan nomor telepon baru (tekan enter jika tidak ingin mengubah nomor telepon): ");
                while ((getchar()) != '\n');
                scanf("%[^\n]%*c", newNumber);
                updateContact(root, inputSearch, newName, newNumber);
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
