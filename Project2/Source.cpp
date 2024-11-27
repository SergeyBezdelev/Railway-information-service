/*3)������������ ������ ���������� ������ ���������������� �������.��������� �������� �� ����������� �������:#������,
������� ����������, ����� �����������, ����� � ����, ������� �������.������������� ���������� ����� ������.*/
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
    int train;                  // ����� ������
    char place[20];             // ������� ����������
    struct time start_time;     // ����� �����������
    struct time travel_time;    // ����� � ����
    int tickets;                // ����� �������

};

void append(char*);             // �������� ������� � ����� ����������
void show(char*);               // �������� ����������
void edit(char*);               // �������� ���� ��������� � �������������� ����
void TicketAvailability(char*); // ��������� ������� ������� � ��������� �������
void erase(char*);              // ������� ��������� ������� � ������������ ����

//��������������� �������
int Hour(char*);
int Min(char*);
int reading(FILE*, struct info*);

int main() {
    setlocale(LC_ALL, "rus");
    char filename[10];
    strcpy(filename, "file.txt");
    int option;
    printf("\n\t\t*** ����� ���������� � ���������� � ������� ***\n");
    while (1){
        printf("\n\n\t\t------------ Main Menu ----------\n");
        printf("\n ������� (1), ����� �������� ����� ������ � ���������� ������� (� �����).\n\
            \n ������� (2), ����� �������� ������� ����������.\n\n ������� (3), ����� �������� ���� � ����������.\n\
            \n ������� (4), ��� ������ ������� ������� � ������ ����������.\n\
            \n ������� (5), ����� ������� ������ ���������� �������.\n\n ������� (6), ����� �����.\n");
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
            printf("������ �� ��������");return 0;
        default:
            printf("����������, �������� ���������� ����� (1-6)!");
        }
    } 
}

void append(char* filename) {
    struct info TrainsInfo; 
    FILE* file = fopen(filename, "a");
    printf("\n������� ����� ������ (�������): ");
    scanf("%d", &TrainsInfo.train);
    printf("\n������� ����� ���������� (�����): ");
    scanf("%s", TrainsInfo.place);
    char str1[10]; char str2[10];
    printf("\n������� ����� ����������� (��:��):");
    scanf("%s", str1);
    printf("\n������� ����� � ���� (��:��): ");
    scanf("%s", str2);
    TrainsInfo.start_time.hour = Hour(str1);
    TrainsInfo.start_time.min = Min(str1);
    TrainsInfo.travel_time.hour = Hour(str2);
    TrainsInfo.travel_time.min = Min(str2);
    printf("\n������� ���������� �������:");
    scanf("%d", &TrainsInfo.tickets);
    fprintf(file, "%d %s %d %d %d %d %d\n", TrainsInfo.train, TrainsInfo.place, TrainsInfo.start_time.hour,
    TrainsInfo.start_time.min, TrainsInfo.travel_time.hour, TrainsInfo.travel_time.min, TrainsInfo.tickets);
    fclose(file);
    printf("\n��������� ����� ������\n");
    getch();
}

void show(char* filename) {
    FILE* file = fopen(filename, "r");
    struct info TrainsInfo[100];// ������ �������� - ������
    int count = reading(file, TrainsInfo);
    if (!count) {
        printf("������, ��� ���������!");
        getch();
        return;
    }
    printf("\n����� � | ����� ���������� | ����� ����������� | ����� � ���� | ������\n");
    for (int j = 0; j < count; ++j)
        printf("�%d  \t %-20s %-d:%02d \t\t   %-d:%02d \t  %4d\n", TrainsInfo[j].train, TrainsInfo[j].place,
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
    printf("\n������ | ����� � | ����� ���������� | ����� ����������� | ����� � ���� | ������ \n");
    for (int j = 0; j < count; ++j)
        printf("%3d)    �%-3d\t  %-25s %-d:%02d \t    %-d:%02d \t  %4d\n", j + 1, TrainsInfo[j].train,
            TrainsInfo[j].place, TrainsInfo[j].start_time.hour, TrainsInfo[j].start_time.min,
            TrainsInfo[j].travel_time.hour, TrainsInfo[j].travel_time.min, TrainsInfo[j].tickets);
    printf("\n������� ����� ������ ��� ���������:\n");
    scanf("%d", &line);
    printf("\n��������:\n������� (1), ����� �������� ����� ������\n������� (2), ����� �������� ����� ����������\
        \n������� (3), ����� �������� ����� �����������\n������� (4), ����� �������� ����� � ����\n������� (5), ����� �������� ������\
         \n������� ������� �� ����� ������ �����, ����� �����\n");
    int option;
    scanf("%d", &option);
    char str1[10], str2[10];
    switch (option){
    case 1:
        printf("\n������� ����� ������ (�������): ");
        scanf("%d", &TrainsInfo[line - 1].train);break;
    case 2:
        printf("\n������� ����� ���������� (�����): ");
        scanf("%s", &TrainsInfo[line - 1].place);break;
    case 3:
        printf("\n������� ����� ����������� (��:��):");
        scanf("%s", str1);
        TrainsInfo[line - 1].start_time.hour = Hour(str1);
        TrainsInfo[line - 1].start_time.min = Min(str1);break;
    case 4:
        printf("\n������� ����� � ���� (��:��): ");
        scanf("%s", str2);
        TrainsInfo[line - 1].travel_time.hour = Hour(str2);
        TrainsInfo[line - 1].travel_time.min = Min(str2);break;
    case 5:
        printf("\n������� ���������� �������");
        scanf("%d", &TrainsInfo[line - 1].tickets);break;
    default:
        printf("�������� � ��������� ��� :)");
        getch();
        return;
    }
    fclose(file);
    file = fopen(filename, "w+");
    for (int j = 0; j < count; ++j)
        fprintf(file, "%d %s %d %d %d %d %d\n", TrainsInfo[j].train, TrainsInfo[j].place, TrainsInfo[j].start_time.hour,
            TrainsInfo[j].start_time.min, TrainsInfo[j].travel_time.hour, TrainsInfo[j].travel_time.min, TrainsInfo[j].tickets);
    printf("\n������� ��������!\n");
    getch();
    fclose(file);
}

void TicketAvailability(char* filename) {
    FILE* file = fopen(filename, "r");
    struct info TrainsInfo[100];
    int count = reading(file, TrainsInfo);
    printf("\n����� � | ����� ����������\n");
    for (int j = 0; j < count; ++j)
        printf("�%-d  \t %-20s\n", TrainsInfo[j].train, TrainsInfo[j].place);
    printf("\n������� ����� ����������:");
    char str[20];
    scanf("%s", str);
    for (int j = 0; j < count; ++j) {
        if (strcmp(TrainsInfo[j].place, str) == 0) {
            if (TrainsInfo[j].tickets != 0)
                printf("�������� ��� %d �������", TrainsInfo[j].tickets);
            else printf("��������, ������� �� ��������!");  
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
    printf("\n������ | ����� � | ����� ���������� | ����� ����������� | ����� � ���� | ������  \n");
    for (int j = 0; j < count; ++j)
        printf("%3d)    �%-3d\t  %-25s %-d:%02d \t    %-d:%02d \t  %4d\n", j + 1, TrainsInfo[j].train,
            TrainsInfo[j].place, TrainsInfo[j].start_time.hour, TrainsInfo[j].start_time.min,
            TrainsInfo[j].travel_time.hour, TrainsInfo[j].travel_time.min, TrainsInfo[j].tickets);
    printf("\n������� ����� ������ ��� ��������:\n");
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
    printf("\n������� �������!");
    getch();
}

int Hour(char* str) {
    int hour = atoi(str);//�� ������� �� ��������� �������
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
