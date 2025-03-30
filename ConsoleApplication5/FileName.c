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
    {"가게1", 1000, 100, 0},
    {"가게2", 3000, 300, 0},
    {"가게3", 5000, 500, 0}
};

Asset buildings[NUM_BUILDINGS] = {
    {"건물1", 10000, 200, 0},
    {"건물2", 30000, 400, 0},
    {"건물3", 50000, 600, 0}
};

// 시간 증가 함수
void passTime() {
    hour++;
    if (hour == 24) {
        hour = 0;
        day++;
        //20% 확률로 1000원 지급
        int chance = rand() % 100;
        if (chance < 20) { // 20% 확률
            money += 1000;
            printf("[행운 보너스] 하루가 지나고 1000원을 얻었습니다!\n");
        }
    }

    

    // 수입 계산
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

// 상태 출력
void showStatus() {
    printf("\n[현재 상태] 돈: %d원 | 시간: %d일 %d시\n", money, day, hour);
}

// 가게 구매
void buyShop() {
    printf("구매할 가게를 선택하세요:\n");
    for (int i = 0; i < NUM_SHOPS; i++) {
        printf("%d. %s - 가격: %d원 / 시간당 수입: %d원\n", i + 1, shops[i].name, shops[i].price, shops[i].incomePerHour);
    }
    int choice;
    scanf_s("%d", &choice);
    if (choice >= 1 && choice <= NUM_SHOPS) {
        Asset* shop = &shops[choice - 1];
        if (money >= shop->price) {
            money -= shop->price;
            shop->owned = 1;
            printf("%s를 구매했습니다!\n", shop->name);
        }
        else {
            printf("돈이 부족합니다!\n");
        }
    }
    else {
        printf("잘못된 선택입니다!\n");
    }
    passTime();
}

// 건물 구매
void buyBuilding() {
    printf("구매할 건물을 선택하세요:\n");
    for (int i = 0; i < NUM_BUILDINGS; i++) {
        printf("%d. %s - 가격: %d원 / 시간당 수입: %d원\n", i + 1, buildings[i].name, buildings[i].price, buildings[i].incomePerHour);
    }
    int choice;
    scanf_s("%d", &choice);
    if (choice >= 1 && choice <= NUM_BUILDINGS) {
        Asset* building = &buildings[choice - 1];
        if (money >= building->price) {
            money -= building->price;
            building->owned = 1;
            printf("%s를 구매했습니다!\n", building->name);
        }
        else {
            printf("돈이 부족합니다!\n");
        }
    }
    else {
        printf("잘못된 선택입니다!\n");
    }
    passTime();
}

int main() {
    char input[50];
    srand(time(NULL));  // 랜덤 시드 설정

    printf("=== 거지 키우기 게임 시작 ===\n");

    while (money < 100000) {
        showStatus();
        printf("\n무엇을 하시겠습니까? (구걸 / 가게 / 부동산)\n");
        scanf_s("%s", input, 50);

        if (strcmp(input, "구걸") == 0) {
            int chance = rand() % 100; // 0부터 99까지의 랜덤 숫자
            if (chance < 20) {  // 20% 확률
                money += 500;
                printf("행운이다! 구걸해서 500원을 얻었습니다!\n");
            }
            else {
                money += 200;
                printf("구걸해서 200원을 얻었습니다!\n");
            }
            passTime();
        }
        else if (strcmp(input, "가게") == 0) {
            buyShop();
        }
        else if (strcmp(input, "부동산") == 0) {
            buyBuilding();
        }
        else {
            printf("잘못된 입력입니다!\n");
        }
    }

    printf("\n축하합니다! %d일 %d시간 만에 10만원을 모았습니다!\n", day, hour);
    printf("=== 게임 종료 ===\n");

    return 0;
}
