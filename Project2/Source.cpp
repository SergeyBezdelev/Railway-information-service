/*3)Организовать работу справочной службы железнодорожного вокзала.Структура сведений об отправлении поездов:#поезда,
станция назначения, время отправления, время в пути, наличие билетов.Предусмотреть добавление новых рейсов.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>

#pragma warning(disable : 4996)

struct time {
    int hour;
    int min;
};
struct info {
    int train;                  // номер поезда
    char place[20];             // Станция пребывания
    struct time start_time;     // время отправления
    struct time travel_time;    // время в пути
    int tickets;                // число билетов

};

void append(char*);             // добавить строчку в конец расписания
void show(char*);               // показать расписание
void edit(char*);               // изменяем поля структуры и перезаписываем файл
void TicketAvailability(char*); // проверить наличие билетов в выбранной строчке
void erase(char*);              // удалить выбранную строчку и перезаписать файл

//Вспомогательные функции
int Hour(char*);
int Min(char*);
int reading(FILE*, struct info*);

int main() {
    setlocale(LC_ALL, "rus");
    char filename[10];
    strcpy(filename, "file.txt");
    int option;
    printf("\n\t\t*** Добро пожаловать в расписание о поездах ***\n");
    while (1){
        printf("\n\n\t\t------------ Main Menu ----------\n");
        printf("\n Введите (1), чтобы добавить новую строку в расписание поездов (в конец).\n\
            \n Введите (2), чтобы показать текущее расписание.\n\n Введите (3), чтобы изменить поля в расписании.\n\
            \n Введите (4), для поиска наличия билетов в пункте назначения.\n\
            \n Введите (5), чтобы удалить строку расписания поездов.\n\n Введите (6), чтобы выйти.\n");
        scanf("%d", &option);
        switch (option){
        case 1:
            append(filename);break;
        case 2:
            show(filename);break;
        case 3:
            edit(filename);break;
        case 4:
            TicketAvailability(filename);break;
        case 5:
            erase(filename);break;
        case 6:
            printf("Данные не изменены");return 0;
        default:
            printf("Пожалуйста, выберите правильный номер (1-6)!");
        }
    } 
}

void append(char* filename) {
    struct info TrainsInfo; 
    FILE* file = fopen(filename, "a");
    printf("\nВведите номер поезда (цифрами): ");
    scanf("%d", &TrainsInfo.train);
    printf("\nВведите пункт назначения (город): ");
    scanf("%s", TrainsInfo.place);
    char str1[10]; char str2[10];
    printf("\nВведите время отправления (чч:мм):");
    scanf("%s", str1);
    printf("\nВведите время в пути (чч:мм): ");
    scanf("%s", str2);
    TrainsInfo.start_time.hour = Hour(str1);
    TrainsInfo.start_time.min = Min(str1);
    TrainsInfo.travel_time.hour = Hour(str2);
    TrainsInfo.travel_time.min = Min(str2);
    printf("\nВведите количество билетов:");
    scanf("%d", &TrainsInfo.tickets);
    fprintf(file, "%d %s %d %d %d %d %d\n", TrainsInfo.train, TrainsInfo.place, TrainsInfo.start_time.hour,
    TrainsInfo.start_time.min, TrainsInfo.travel_time.hour, TrainsInfo.travel_time.min, TrainsInfo.tickets);
    fclose(file);
    printf("\nДобавлена новая строка\n");
    getch();
}

void show(char* filename) {
    FILE* file = fopen(filename, "r");
    struct info TrainsInfo[100];// Массив структур - буффер
    int count = reading(file, TrainsInfo);
    if (!count) {
        printf("Ошибка, нет элементов!");
        getch();
        return;
    }
    printf("\nПоезд № | Пункт назначения | Время отправления | Время в пути | Билеты\n");
    for (int j = 0; j < count; ++j)
        printf("№%d  \t %-20s %-d:%02d \t\t   %-d:%02d \t  %4d\n", TrainsInfo[j].train, TrainsInfo[j].place,
            TrainsInfo[j].start_time.hour, TrainsInfo[j].start_time.min,
            TrainsInfo[j].travel_time.hour, TrainsInfo[j].travel_time.min, TrainsInfo[j].tickets);
    fclose(file);
    getch();
}

void edit(char* filename) {
    FILE* file = fopen(filename, "r+");
    int line;
    struct info TrainsInfo[100];
    int count = reading(file, TrainsInfo);
    printf("\nСтрока | Поезд № | Пункт назначения | Время отправления | Время в пути | Билеты \n");
    for (int j = 0; j < count; ++j)
        printf("%3d)    №%-3d\t  %-25s %-d:%02d \t    %-d:%02d \t  %4d\n", j + 1, TrainsInfo[j].train,
            TrainsInfo[j].place, TrainsInfo[j].start_time.hour, TrainsInfo[j].start_time.min,
            TrainsInfo[j].travel_time.hour, TrainsInfo[j].travel_time.min, TrainsInfo[j].tickets);
    printf("\nВведите номер строки для изменения:\n");
    scanf("%d", &line);
    printf("\nВыберите:\nНажмите (1), чтобы изменить номер поезда\nНажмите (2), чтобы изменить пункт назначения\
        \nНажмите (3), чтобы изменить время отправления\nНажмите (4), чтобы изменить время в пути\nНажмите (5), чтобы изменить билеты\
         \nНажмите нажмите на любые другие числа, чтобы выйти\n");
    int option;
    scanf("%d", &option);
    char str1[10], str2[10];
    switch (option){
    case 1:
        printf("\nВведите номер поезда (цифрами): ");
        scanf("%d", &TrainsInfo[line - 1].train);break;
    case 2:
        printf("\nВведите пункт назначения (город): ");
        scanf("%s", &TrainsInfo[line - 1].place);break;
    case 3:
        printf("\nВведите время отправления (чч:мм):");
        scanf("%s", str1);
        TrainsInfo[line - 1].start_time.hour = Hour(str1);
        TrainsInfo[line - 1].start_time.min = Min(str1);break;
    case 4:
        printf("\nВведите время в пути (чч:мм): ");
        scanf("%s", str2);
        TrainsInfo[line - 1].travel_time.hour = Hour(str2);
        TrainsInfo[line - 1].travel_time.min = Min(str2);break;
    case 5:
        printf("\nВведите количество билетов");
        scanf("%d", &TrainsInfo[line - 1].tickets);break;
    default:
        printf("Увидимся в следующий раз :)");
        getch();
        return;
    }
    fclose(file);
    file = fopen(filename, "w+");
    for (int j = 0; j < count; ++j)
        fprintf(file, "%d %s %d %d %d %d %d\n", TrainsInfo[j].train, TrainsInfo[j].place, TrainsInfo[j].start_time.hour,
            TrainsInfo[j].start_time.min, TrainsInfo[j].travel_time.hour, TrainsInfo[j].travel_time.min, TrainsInfo[j].tickets);
    printf("\nУспешно изменено!\n");
    getch();
    fclose(file);
}

void TicketAvailability(char* filename) {
    FILE* file = fopen(filename, "r");
    struct info TrainsInfo[100];
    int count = reading(file, TrainsInfo);
    printf("\nПоезд № | Пункт назначения\n");
    for (int j = 0; j < count; ++j)
        printf("№%-d  \t %-20s\n", TrainsInfo[j].train, TrainsInfo[j].place);
    printf("\nВведите пункт назначения:");
    char str[20];
    scanf("%s", str);
    for (int j = 0; j < count; ++j) {
        if (strcmp(TrainsInfo[j].place, str) == 0) {
            if (TrainsInfo[j].tickets != 0)
                printf("Осталось еще %d билетов", TrainsInfo[j].tickets);
            else printf("Извините, билетов не осталось!");  
        }
    }
    fclose(file);
    getch();
}

void erase(char* filename) {
    FILE* file = fopen(filename, "r");
    int line;
    struct info TrainsInfo[100];
    int count = reading(file, TrainsInfo);
    printf("\nСтрока | Поезд № | Пункт назначения | Время отправления | Время в пути | Билеты  \n");
    for (int j = 0; j < count; ++j)
        printf("%3d)    №%-3d\t  %-25s %-d:%02d \t    %-d:%02d \t  %4d\n", j + 1, TrainsInfo[j].train,
            TrainsInfo[j].place, TrainsInfo[j].start_time.hour, TrainsInfo[j].start_time.min,
            TrainsInfo[j].travel_time.hour, TrainsInfo[j].travel_time.min, TrainsInfo[j].tickets);
    printf("\nВведите номер строки для удаления:\n");
    scanf("%d", &line);
    fclose(file);
    file = fopen(filename, "w+");
    for (int j = 0; j < count; ++j) {
        if (j == line - 1) continue;
       fprintf(file, "%d %s %d %d %d %d %d\n", TrainsInfo[j].train, TrainsInfo[j].place,
           TrainsInfo[j].start_time.hour, TrainsInfo[j].start_time.min, TrainsInfo[j].travel_time.hour,
           TrainsInfo[j].travel_time.min, TrainsInfo[j].tickets);
    }
    fclose(file);
    printf("\nУдалено успешно!");
    getch();
}

int Hour(char* str) {
    int hour = atoi(str);//до первого не числового символа
    return hour;
}

int Min(char* str) {
    int min = atoi(str + 3);
    return min;
}

int reading(FILE* file, struct info* B) {
    int count = 0;
    while (fscanf(file, "%d %s %d %d %d %d %d", &B[count].train, B[count].place,
        &B[count].start_time.hour, &B[count].start_time.min, &B[count].travel_time.hour,
        &B[count].travel_time.min, &B[count].tickets) != EOF) 
        count++;
    return count;
