#include <stdio.h>
// 678
// 5 1
// 432
// A/Z and K/M
// 80 x 25

void start();
int win();  // подсчет результатов
void maincycle();
void drawscreen();
void drawLeft(int strnum);
void drawRight(int strnum);
void drawMiddle(int strnum);  // рисует шарик и счетчик
void checkForBorderTouch();  // проверяет результы
void mooveBall();
void reset();
void drawscore();  // вывод счета отдельной строкой + уловия победы
int reboundLeftRocket();
int reboundRightRocket();
void mvLeftRocketTop();
void mvLeftRocketBottom();
void mvRightRocketTop();
void mvRightRocketBottom();
void clrscr(void);

char ball = 'O';
int ball_pos_x = 75;
int ball_pos_y = 12;
int ball_direction = 3;  // 1-8

char rocket = 'X';
int left_pos = 12;
int right_pos = 12;
int rocket_len = 3;

int winscore = 21;  // задаем число очков за которое присуждается победа
int scores_left = 0;
int scores_right = 0;

int main() {
    maincycle();
    return 0;
}

void maincycle() {
    char c;
    start();
    do {
        checkForBorderTouch();
        win();
        scanf("%c", &c);
        if (c == ' ') {
            mooveBall();
            drawscreen();
        }
        if (c == 'A' || c == 'a') {
            mvLeftRocketTop();
            mooveBall();
            drawscreen();
        }
        if (c == 'Z' || c == 'z') {
            mvLeftRocketBottom();
            mooveBall();
            drawscreen();
        }
        if (c == 'K' || c == 'k') {
            mvRightRocketTop();
            mooveBall();
            drawscreen();
        }
        if (c == 'M' || c == 'm') {
            mvRightRocketBottom();
            mooveBall();
            drawscreen();
        }
    } while (win() == 0);
}

void drawscreen() {
    clrscr();
    printf("           Player 1: %d                       Player 2: %d\n", scores_left, scores_right);
    for (int y = 1; y <= 27; y++) {
        drawLeft(y);
        drawMiddle(y);
        drawRight(y);
        printf("%d\n", y);
    }
}

void drawLeft(int strnum) {
    char c = strnum > left_pos - 2 && strnum < left_pos + 2 ? rocket : ' ';
    if (strnum != 1 || strnum != 27) {
        printf("*%c", c);
    }
}

void drawRight(int strnum) {
    char c = strnum > right_pos - 2 && strnum < right_pos + 2 ? rocket : ' ';
    if (strnum != 1 || strnum != 27) {
        printf("%c*", c);
    }
}

void drawMiddle(int strnum) {
    char c;
    if (ball_pos_y != strnum) {  // no ball in the string
        for (int i = 1; i <= 82; i++) {
            if (strnum == 1 || strnum == 27) {
                printf("*");
                } else if (i == 42) {
                printf("|");
                } else {printf("%c", ' ');
            }
        }
    } else {  // ball is in the string
        for (int i = 1; i <= 82; i++) {
            if (strnum == 1 || strnum == 27) {
                printf("*");
                } else if (i == 42) {
                    printf("|");
                } else {
                    c = i == ball_pos_x ? ball : ' ';
                    printf("%c", c);
                }
        }
    }
}

int win() {
    if (scores_left == winscore) {
        printf("\033c");
        printf("left player win");
        return 1;
    }
    if (scores_right == winscore) {
        printf("\033c");
        printf("right player win");
        return 1;
    }
    return 0;
}

void checkForBorderTouch() {
    if (ball_pos_x == 1) {
        scores_right++;
        reset();
    }
    if (ball_pos_x == 82) {
        scores_left++;
        reset();
    }
}

void reset() {
    ball_pos_x = 40;
    ball_pos_y = 12;
    ball_direction = 2;
}

void mooveBall() {
    if (ball_pos_y == 2 || ball_pos_y == 26 || (ball_pos_x == 2 && reboundLeftRocket()) ||
        (ball_pos_x == 81 && reboundRightRocket())) {  // ball must spring
        if (ball_pos_x == 2) {  // left rocket touch
            switch (ball_direction) {
            case 6:
                ball_direction = 8;
                ball_pos_x++;
                ball_pos_y++;
                break;
            case 5:
                ball_direction = 1;
                ball_pos_x++;
                break;
            case 4:
                ball_direction = 2;
                ball_pos_x++;
                ball_pos_y--;
                break;
            }
        }
        if (ball_pos_x == 81) {  // right rocket touch
            switch (ball_direction) {
            case 8:
                ball_direction = 6;
                ball_pos_x--;
                ball_pos_y++;
                break;
            case 1:
                ball_direction = 5;
                ball_pos_x--;
                break;
            case 2:
                ball_direction = 4;
                ball_pos_x--;
                ball_pos_y--;
                break;
            }
        }
        if (ball_pos_y == 2) {  //  bottom touch
            switch (ball_direction) {
            case 4:
                ball_direction = 6;
                ball_pos_y++;
                ball_pos_x--;
                break;
            case 3:
                ball_direction = 7;
                ball_pos_y++;
                break;
            case 2:
                ball_direction = 8;
                ball_pos_y++;
                ball_pos_x++;
                break;
            }
        }
        if (ball_pos_y == 26) {  // ceil touch
            switch (ball_direction) {
            case 6:
                ball_direction = 4;
                ball_pos_y--;
                ball_pos_x--;
                break;
            case 7:
                ball_direction = 3;
                ball_pos_y--;
                break;
            case 8:
                ball_direction = 2;
                ball_pos_y--;
                ball_pos_x++;
                break;
            }
        }
    } else {
        switch (ball_direction) {
        case 1:  // right
            ball_pos_x++;
            break;
        case 2:  // right down
            ball_pos_x++;
            ball_pos_y--;
            break;
        case 3:  // down
            ball_pos_y--;
            break;
        case 4:  // left down
            ball_pos_x--;
            ball_pos_y--;
            break;
        case 5:  // left
            ball_pos_x--;
            break;
        case 6:  // let up
            ball_pos_x--;
            ball_pos_y++;
            break;
        case 7:  // up
            ball_pos_y++;
            break;
        case 8:  // right up
            ball_pos_x++;
            ball_pos_y++;
            break;
        }
    }
}

void mvLeftRocketTop() {
    if (left_pos >= 4) {
        --left_pos;
    }
}

void mvLeftRocketBottom() {
    if (left_pos <= 24) {
        ++left_pos;
    }
}

void mvRightRocketTop() {
    if (right_pos >= 4) {
        --right_pos;
    }
}

void mvRightRocketBottom() {
    if (right_pos <= 24) {
        ++right_pos;
    }
}

void clrscr(void) {
    printf("\033[2J");  //  Clear the entire screen.
}

int reboundRightRocket() {
    return ball_pos_y > right_pos - 2 && ball_pos_y < right_pos + 2;
}

int reboundLeftRocket() {
    return ball_pos_y > left_pos - 2 && ball_pos_y < left_pos + 2;
}

void start() {
    char c;
    printf("I want to play a game with you\n");
    printf("Rules:\n");
    printf("1. Score 21 points to win.\n");
    printf("Controls:\n");
    printf("1. A/Z and K/M to move the rackets\n");
    printf("2. Press the space bar to make a move\n");
    scanf("%c", &c);
    if (c == 's') {
        return;
    }
}
