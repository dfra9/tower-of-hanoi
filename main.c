#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


bool isDuplicate(int *arr, int size, int num) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == num) {
            return true; // Found a duplicate
        }
    }
    return false; // No duplicates found
}

bool isNumeric(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}


void towerOfHanoi(int n, int source[], int result[], const char *sourcePole, const char *auxiliaryPole, const char *destinationPole)
{
    if (n > 0)
    {
        towerOfHanoi(n - 1, source, result, sourcePole, destinationPole, auxiliaryPole);

        int movedDisk = source[n - 1];
        result[n - 1] = movedDisk;

        printf("Pindahkan Box %d dari %s ke %s\n", movedDisk, sourcePole, destinationPole);

        towerOfHanoi(n - 1, source, result, auxiliaryPole, sourcePole, destinationPole);
    }
}

void solveTowerOfHanoi(int n, int source[], int result[])
{
    towerOfHanoi(n, source, result, "Troli 1", "Troli 2", "Troli 3");

     for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (result[i] < result[j]) {
                int temp = result[i];
                result[i] = result[j];
                result[j] = temp;
            }
        }
    }
}

int main()
{
    int **allNumbers = NULL;
    int **allSortedNumbers = NULL;
    int *numDisksArray = NULL;
    int choice;
    int setCounter = 0;
    int **inputHistory = NULL;
    int *historySizes = NULL;
    int historyCounter = 0;
    bool *deletedHistory = calloc(historyCounter, sizeof(bool));
    bool *deletedSet = calloc(setCounter, sizeof(bool));



    do
    {
        printf("\n=======Menu:=======\n");
        printf("|1. Input Data    |\n");
        printf("|2. Show Data     |\n");
        printf("|3. Delete Data   |\n");
        printf("|4. History Input |\n");
        printf("|5. History Delete|\n");
        printf("|6. Exit          |\n");
        printf("===================\n");
        printf("Pilih menu (1-6): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
    setCounter++;
    int numDisks;
char buffer[50]; // Buffer untuk input
bool isValidInput = false;

do {
    printf("Masukkan Banyak Jumlah Box (Set %d): ", setCounter);
    scanf("%s", buffer);

    // Memeriksa apakah input adalah angka
    if (isNumeric(buffer)) {
        numDisks = atoi(buffer); // Mengonversi string ke integer
        isValidInput = true;
    } else {
        printf("Input tidak valid. Masukkan angka.\n");
        while (getchar() != '\n'); // Membersihkan buffer input
    }

} while (!isValidInput);

allNumbers = realloc(allNumbers, setCounter * sizeof(int *));
allSortedNumbers = realloc(allSortedNumbers, setCounter * sizeof(int *));
numDisksArray = realloc(numDisksArray, setCounter * sizeof(int));

if (allNumbers == NULL || allSortedNumbers == NULL || numDisksArray == NULL)
{
    printf("Memory allocation failed.\n");
    exit(EXIT_FAILURE);
}

allNumbers[setCounter - 1] = malloc(numDisks * sizeof(int));
allSortedNumbers[setCounter - 1] = malloc(numDisks * sizeof(int));

if (allNumbers[setCounter - 1] == NULL || allSortedNumbers[setCounter - 1] == NULL)
{
    printf("Memory allocation failed.\n");
    exit(EXIT_FAILURE);
}

numDisksArray[setCounter - 1] = numDisks;

printf("Masukkan Angkanya (dalam bentuk cm^2, Set %d):\n", setCounter);

for (int i = 0; i < numDisks; i++)
{
    int inputNum;
    bool isValidNum = false;

    do {
        printf("Angka ke %d: ", i + 1);
        scanf("%d", &inputNum);

        if (isDuplicate(allNumbers[setCounter - 1], i, inputNum)) {
            printf("Angka sudah ada dalam set. Coba lagi.\n");
        } else {
            allNumbers[setCounter - 1][i] = inputNum;
            isValidNum = true;
        }
    } while (!isValidNum);
}


    inputHistory = realloc(inputHistory, (historyCounter + 1) * sizeof(int *));
    historySizes = realloc(historySizes, (historyCounter + 1) * sizeof(int));

    if (inputHistory == NULL || historySizes == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    inputHistory[historyCounter] = malloc(numDisks * sizeof(int));
    if (inputHistory[historyCounter] == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Menyalin data set saat ini ke History Input
    historySizes[historyCounter] = numDisks;
    for (int i = 0; i < numDisks; ++i)
    {
        inputHistory[historyCounter][i] = allNumbers[setCounter - 1][i];
    }

    
    historyCounter++;
    printf("Set berhasil disimpan ke history.\n");
    break;

        case 2:

            if (setCounter > 0)
            {
                for (int set = 0; set < setCounter; set++)
                {
                    int numDisksSet = numDisksArray[set];
                    printf("Data (Set %d): ", set + 1);
                    for (int i = 0; i < numDisksSet; i++)
                    {
                        printf("%d ", allNumbers[set][i]);
                    }
                    printf("\n");

                    solveTowerOfHanoi(numDisksSet, allNumbers[set], allSortedNumbers[set]);

                    printf("Sorted Numbers (Set %d): ", set + 1);
                    for (int i = 0; i < numDisksSet; i++)
                    {
                        printf("%d ", allSortedNumbers[set][i]);
                    }
                    printf("\n");
                }
            }
            else
            {
                printf("Data doesn't exist.\n");
            }
            break;

        case 3:
        
    if (setCounter > 0) {
        printf("Masukkan nomor set yang ingin dihapus: ");
        int setToDelete;
        scanf("%d", &setToDelete);

        if (setToDelete >= 1 && setToDelete <= setCounter) {
            setToDelete--;

            // Salin data yang akan dihapus ke histori input sebelum menghapusnya
            inputHistory = realloc(inputHistory, (historyCounter + 1) * sizeof(int *));
            inputHistory[historyCounter] = malloc(numDisksArray[setToDelete] * sizeof(int));

            if (inputHistory[historyCounter] == NULL) {
                printf("Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }

            historySizes = realloc(historySizes, (historyCounter + 1) * sizeof(int));
            historySizes[historyCounter] = numDisksArray[setToDelete];

            for (int i = 0; i < numDisksArray[setToDelete]; ++i) {
                inputHistory[historyCounter][i] = allNumbers[setToDelete][i];
            }


            historyCounter++;

            free(allNumbers[setToDelete]);
            free(allSortedNumbers[setToDelete]);

            for (int i = setToDelete; i < setCounter - 1; i++) {
                allNumbers[i] = allNumbers[i + 1];
                allSortedNumbers[i] = allSortedNumbers[i + 1];
                numDisksArray[i] = numDisksArray[i + 1];
            }

            setCounter--;

            printf("Set %d berhasil dihapus.\n", setToDelete + 1);
            deletedHistory[historyCounter - 1] = true;
        } else {
            printf("Nomor set tidak valid.\n");
        }
    } else {
        printf("Tidak ada data yang dapat dihapus. Datanya tidak ada.\n");
    }
    break;
    
        case 4:
        if (historyCounter > 0) {
        printf("History Input Data:\n");
        int inputSet = 0;
        for (int i = 0; i < setCounter; ++i) {
            int found = 0;
        
            for (int j = 0; j < historyCounter; ++j) {
                int match = 1;
                for (int k = 0; k < numDisksArray[i]; ++k) {
                    if (inputHistory[j][k] != allNumbers[i][k]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                printf("History Input %d: ", inputSet + 1);
                for (int k = 0; k < numDisksArray[i]; ++k) {
                    printf("%d ", allNumbers[i][k]);
                }
                printf("\n");
                inputSet++;
            }
        }
        if (inputSet == 0) {
            printf("Tidak ada data yang disimpan ke history dari Input Data.\n");
        }
    } else {
        printf("Tidak ada data yang disimpan ke history dari Input Data.\n");
    }
    break;
        case 5:
    if (historyCounter > 0) {
        printf("Deleted History Data:\n");
        int deletedCount = 0;
        for (int i = 0; i < historyCounter; ++i) {
            if (deletedHistory[i]) {
                deletedCount++;
                printf("Deleted History %d: ", deletedCount);
                for (int j = 0; j < historySizes[i]; ++j) {
                    printf("%d ", inputHistory[i][j]);
                }
                printf("\n");
            }
        }
        if (deletedCount == 0) {
            printf("No deleted history data.\n");
        }
    } else {
        printf("No history data available.\n");
    }
    break;

        case 6:
            for (int i = 0; i < historyCounter; ++i)
            {
                free(inputHistory[i]);
            }
            free(inputHistory);
            free(historySizes);
            free(deletedHistory);
            printf("Terima Kasih");
            break;  

        default:
            printf("Pilihan salah, Coba lagi!\n");
        }
    } while (choice != 6);

    return 0;
}