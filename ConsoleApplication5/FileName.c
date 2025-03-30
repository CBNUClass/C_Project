#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define NUM_SHOPS 3
#define NUM_BUILDINGS 3

typedef struct {
    char name[20];
    int price;
    int incomePerHour;
    int owned;
} Asset;

int money = 0;
int hour = 0;
int day = 0;

Asset shops[NUM_SHOPS] = {
    {"����1", 1000, 100, 0},
    {"����2", 3000, 300, 0},
    {"����3", 5000, 500, 0}
};

Asset buildings[NUM_BUILDINGS] = {
    {"�ǹ�1", 10000, 200, 0},
    {"�ǹ�2", 30000, 400, 0},
    {"�ǹ�3", 50000, 600, 0}
};

// �ð� ���� �Լ�
void passTime() {
    hour++;
    if (hour == 24) {
        hour = 0;
        day++;
        //20% Ȯ���� 1000�� ����
        int chance = rand() % 100;
        if (chance < 20) { // 20% Ȯ��
            money += 1000;
            printf("[��� ���ʽ�] �Ϸ簡 ������ 1000���� ������ϴ�!\n");
        }
    }

    

    // ���� ���
    for (int i = 0; i < NUM_SHOPS; i++) {
        if (shops[i].owned) {
            money += shops[i].incomePerHour;
        }
    }
    for (int i = 0; i < NUM_BUILDINGS; i++) {
        if (buildings[i].owned) {
            money += buildings[i].incomePerHour;
        }
    }
}

// ���� ���
void showStatus() {
    printf("\n[���� ����] ��: %d�� | �ð�: %d�� %d��\n", money, day, hour);
}

// ���� ����
void buyShop() {
    printf("������ ���Ը� �����ϼ���:\n");
    for (int i = 0; i < NUM_SHOPS; i++) {
        printf("%d. %s - ����: %d�� / �ð��� ����: %d��\n", i + 1, shops[i].name, shops[i].price, shops[i].incomePerHour);
    }
    int choice;
    scanf_s("%d", &choice);
    if (choice >= 1 && choice <= NUM_SHOPS) {
        Asset* shop = &shops[choice - 1];
        if (money >= shop->price) {
            money -= shop->price;
            shop->owned = 1;
            printf("%s�� �����߽��ϴ�!\n", shop->name);
        }
        else {
            printf("���� �����մϴ�!\n");
        }
    }
    else {
        printf("�߸��� �����Դϴ�!\n");
    }
    passTime();
}

// �ǹ� ����
void buyBuilding() {
    printf("������ �ǹ��� �����ϼ���:\n");
    for (int i = 0; i < NUM_BUILDINGS; i++) {
        printf("%d. %s - ����: %d�� / �ð��� ����: %d��\n", i + 1, buildings[i].name, buildings[i].price, buildings[i].incomePerHour);
    }
    int choice;
    scanf_s("%d", &choice);
    if (choice >= 1 && choice <= NUM_BUILDINGS) {
        Asset* building = &buildings[choice - 1];
        if (money >= building->price) {
            money -= building->price;
            building->owned = 1;
            printf("%s�� �����߽��ϴ�!\n", building->name);
        }
        else {
            printf("���� �����մϴ�!\n");
        }
    }
    else {
        printf("�߸��� �����Դϴ�!\n");
    }
    passTime();
}

int main() {
    char input[50];
    srand(time(NULL));  // ���� �õ� ����

    printf("=== ���� Ű��� ���� ���� ===\n");

    while (money < 100000) {
        showStatus();
        printf("\n������ �Ͻðڽ��ϱ�? (���� / ���� / �ε���)\n");
        scanf_s("%s", input, 50);

        if (strcmp(input, "����") == 0) {
            int chance = rand() % 100; // 0���� 99������ ���� ����
            if (chance < 20) {  // 20% Ȯ��
                money += 500;
                printf("����̴�! �����ؼ� 500���� ������ϴ�!\n");
            }
            else {
                money += 200;
                printf("�����ؼ� 200���� ������ϴ�!\n");
            }
            passTime();
        }
        else if (strcmp(input, "����") == 0) {
            buyShop();
        }
        else if (strcmp(input, "�ε���") == 0) {
            buyBuilding();
        }
        else {
            printf("�߸��� �Է��Դϴ�!\n");
        }
    }

    printf("\n�����մϴ�! %d�� %d�ð� ���� 10������ ��ҽ��ϴ�!\n", day, hour);
    printf("=== ���� ���� ===\n");

    return 0;
}
