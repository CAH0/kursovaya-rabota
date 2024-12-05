#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#define MAX_VERTICES 100

int** createG(int size) {
    int** G;
    G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        G[i] = ((int*)malloc(size * sizeof(int)));
    }

    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            G[i][j] = rand() % 2;
            if (i == j) G[i][j] = 0;
            G[j][i] = G[i][j];
        }
    }
    return G;
}

int** writeCreateG(int **G, int size) {
    G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        G[i] = (int*)malloc(size * sizeof(int));
    }

    printf("Введите матрицу смежности графа (%d x %d):\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            while (1) {
                printf("Введите значение для G[%d][%d] (0 или 1): ", i, j);
                int input;
                scanf("%d", &input);
                if (input == 0 || input == 1) {
                    G[i][j] = input;
                    break;
                }
                else {
                    printf("Ошибка: введите 0 или 1.\n");
                }
            }
        }
    }
    return G;
}

void printG(int** G, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
}

int chromatic_number(int **graph, int n) {
    int color[MAX_VERTICES];
    for (int i = 0; i < n; i++) {
        color[i] = -1; 
    }
    color[0] = 0;

    for (int v = 1; v < n; v++) {
        int available[MAX_VERTICES] = { 0 };
        for (int u = 0; u < n; u++) {
            if (graph[v][u] == 1 && color[u] != -1) {
                available[color[u]] = 1; 
            }
        }
        for (int c = 0; c < n; c++) {
            if (available[c] == 0) {
                color[v] = c;
                break;
            }
        }
    }
    int max_color = -1;
    for (int i = 0; i < n; i++) {
        if (color[i] > max_color) {
            max_color = color[i];
        }
    }
    return max_color + 1; 
}

void saveGraphToFile(int** G, int size) {
    FILE* file = fopen("input.txt", "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла для записи.\n");
        return;
    }

    fprintf(file, "%d\n", size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(file, "%d ", G[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Граф успешно сохранен в файл input.txt\n");
}

void firstMenu() {
    printf("| %12sСоздание графа %12s |\n","","");
    printf("|1. Создать граф случайным образом. %6s|\n", "");
    printf("|2. Задать граф в ручную. %16s|\n", "");
    printf("|3. Скопировать граф из файла(input.txt). |\n");
    printf("|4. Выход.%31s |\n", "");
    printf("Выберите действие: ");
}

void nameMenu() {
    printf("\%40s Курсовая работа\n", "");
    printf("\%20s Тема: Разработка алгоритма нахождения хроматического числа графа\n\n\n\n\n\n\n\n\n", "");
    printf("\%90s Выполнил: ст. гр. 23ВВВ1\n", "");
    printf("\%103s Казаков А.Д.\n", "");
    printf("Для продолжения нажмите клавишу Enter...");
}

void secondText() {
    printf("| %12sРабота с графом %12s |\n", "", "");
    printf("|1. Просмотр графа. %23s|\n", "");
    printf("|2. Подсчёт Хроматического числа графа. %3s|\n", "");
    printf("|3. Запись графа в файл (input.txt). %6s|\n", "");
    printf("|4. Вернуться к созданию графа. %11s|\n", "");
    printf("Выберите действие: ");
}

int** loadGraphFromFile(int *size) {
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла для чтения.\n");
        return NULL;
    }

    fscanf(file, "%d", size);
    int size1 = *size;

    int** G = (int**)malloc(size1 * sizeof(int*));
    for (int i = 0; i < size1; i++) {
        G[i] = (int*)malloc( size1 * sizeof(int));
    }

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size1; j++) {
            fscanf(file, "%d ", &G[i][j]); 
        }
    }

    fclose(file);
    printf("Граф успешно загружен из файла input.txt\n");
    return G;
}

int secondMenu(int **G, int size, char ch) {
    int secondChoice = 0;

    do {
        system("cls");
        secondText();
        scanf("%d", &secondChoice);
        switch (secondChoice)
        {
        case 1: {
            system("cls");
            printf("Матрица смежности для графа\n");
            printG(G,size);
            printf("Для вовращения напишите 'y'\n");
            scanf("%s", &ch);
            break;
        }
        case 2: {
            system("cls");
            int chromaticNum = chromatic_number(G, size);
            printG(G,size);
            printf("Хроматическое число этого графа: %d\n", chromaticNum);
            printf("Для вовращения напишите 'y'\n");
            scanf("%s", &ch);
            break;
        }
        case 3: {
            system("cls");
            saveGraphToFile(G, size);
            Sleep(2000);
            break;
        }
        case 4: {
            system("cls");
            break;
        }
        default:
            printf("\nНеверный выбор! Повтори попытку.\n\nЧерез ");
            for (int i = 2; i > 0; i--) {
                printf("%d.. ", i);
                Sleep(1000);
            }
            break;
        }

    } while (secondChoice != 4);
    
    return 1;
}

void displayProgressBar(int progress, int total) {
    int barWidth = 50;
    float ratio = (float)progress / total;
    int pos = barWidth * ratio;

    printf("[");
    for (int i = 0; i < barWidth; i++) {
        if (i < pos) {
            printf("#"); 
        }
        else printf(" "); 
    }
    printf("] %.2f%%\r", ratio * 100);
    fflush(stdout);
}


int main() {
    
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");
    int** G = NULL, count = 0;
    int* size1 = 0;
    int size = 0;
    int choice = 0, secondChoice  = 0;
    char wait = '0';

    nameMenu();
    getchar();
    do {
        system("cls");
        firstMenu();
        scanf("%d", &choice);
        switch (choice) {
        case 1: {
            system("cls");
            printf("Введите размер графа (количество вершин): ");
            scanf("%d", &size);
            G = createG(size);

            printf("Создание Графа\n");
            for (int i = 0; i <= 3; i++) {
                displayProgressBar(i, 3);
                Sleep(1000);
            }
            secondMenu(G,size, wait);

            break;
        }
        case 2: {
            system("cls");
            printf("Введите размер графа (количество вершин): ");
            scanf("%d", &size);
            G= writeCreateG(G,size);

            printf("Введённый граф:\n");
            printG(G, size);
            printf("\nПереход к следущему меню.\n");
            for (int i = 0; i <= 2; i++) {
                displayProgressBar(i, 2);
                Sleep(1000);
            }
            system("cls");
            secondText();
            scanf("%d", &secondChoice);

            secondMenu(G, size, wait);
            break;
        }
        case 3:
            system("cls");
            G = loadGraphFromFile(&size);
            printf("\nПереход к следущему меню.\n");
            for (int i = 0; i <= 2; i++) {
                displayProgressBar(i, 2);
                Sleep(1000);
            }
            secondMenu(G, size,  wait);
            break;
        case 4:
            break;
        
        default:
            printf("\nНеверный выбор! Повтори попытку.\n\nЧерез ");
            for (int i = 2; i >0; i--) {
                printf("%d.. ", i);
                Sleep(1000);
            }
            break;
        }
        
    } while (choice != 4);

    

    for (int i = 0; i < size; i++) {
        free(G[i]);
    }
    free(G);
    return 0;
}

