#include <stdio.h>

int menu()
{
    printf("###########################\n");
    printf("##   1.Play    2.Exit   ##\n");
    printf("###########################\n");
    printf("###########################\n");
    printf("##    P1:O      P2:X    ##\n");
    printf("###########################\n");
    return 0;
}

typedef struct {
    int board[3][3];    // -1 = empty, 0 = O, 1 = X
    int turn;           // O first
} state;

void init(state* s) {
    int i, j;
    for (j = 0; j < 3; j++)
        for (i = 0; i < 3; i++)
            s->board[j][i] = -1;
    s->turn = 0;
}

void display(const state* s) {
    int i, j;
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 3; i++) {
            switch (s->board[j][i]) {
                case -1: printf(" %d ", j * 3 + i + 1); break;
                case  0: printf(" O "); break;
                case  1: printf(" X "); break;
            }
            if (i < 2)
                printf("|");
            else
                printf("\n");
        }
        if (j < 2)
            printf("---+---+---\n");
        else
            printf("\n");
    }
}

int Move(state* s, int i, int j) {
    if (s->board[j][i] != -1){
        printf("this place has been played\n");
        return 0;}
    else s->board[j][i] = s->turn++ % 2;
    return 1;
}

void human(state* s) {
    char c;
    do {
        printf("%c: ", "OX"[s->turn % 2]);
        c = getchar();
        while (getchar() != '\n');
        printf("\n");
    } while (c < '1' || c > '9' || !Move(s, (c - '1') % 3, (c - '1') / 3));
}

#define CHECK(j1, i1, j2, i2, j3, i3) \
if (s->board[j1][i1] != -1 && s->board[j1][i1] == s->board[j2][i2] && s->board[j1][i1] == s->board[j3][i3]) \
return s->board[j1][i1] == 0 ? 1 : -1;

int evaluate(const state* s) {
    int i;
    for (i = 0; i < 3; i++) {
        CHECK(i, 0, i, 1, i, 2);    // horizontal
        CHECK(0, i, 1, i, 2, i);    // vertical
    }
    CHECK(0, 0, 1, 1, 2, 2);        // diagonal
    CHECK(0, 2, 1, 1, 2, 0);        // diagonal
    return 0;
}

int main() {
    int a;
    menu();
    printf("Please enter your choose:");
    scanf("%d",&a);
    if(a!= 1){ return 0; }
    while(1)
    {
        state s;
        init(&s);
        display(&s);
        while (s.turn < 9) {
            human(&s);
            display(&s);
            switch (evaluate(&s)) {
                case  1: printf("O is winner\n\n"); return 0;
                case -1: printf("X is winner\n\n"); return 0;
            }
        }
        printf("Draw\n\n"); break;}
    
}
