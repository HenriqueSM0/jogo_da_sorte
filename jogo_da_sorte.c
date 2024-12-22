// Jogo da sorte :

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

typedef struct {
    char type;
} position;

typedef struct {
    position ** P;
} game;

void game_init (game * Henrique, int size) {
    int i, j;
    Henrique->P = (position**)malloc(size * sizeof(position*));
    for (i = 0; i < size; i++) {
        Henrique->P[i] = (position*)malloc(size * sizeof(position));
        for (j = 0; j < size; j++) {
            if ((i == (size - 1) / 2) && (j == (size - 1) / 2)) {
                Henrique->P[i][j].type = 'P';
            } else {
                Henrique->P[i][j].type = 'N';
            }
        }
    }
}

int enemy_location (game * Henrique, int size, int first_time) {
    int i, j, i_enemy, j_enemy;
    i_enemy = 101;
    j_enemy = 101;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (Henrique->P[i][j].type == 'E') {
                Henrique->P[i][j].type = 'N';
            }
        }
    }
    while ((i_enemy > size - 1) || (j_enemy > size - 1) || ((Henrique->P[i_enemy][j_enemy].type == 'P') && (first_time == 1))) {
        i_enemy = rand() % 100;

        j_enemy = rand() % 100;
    }
    if (Henrique->P[i_enemy][j_enemy].type == 'P') {
        return 0;
    }
    Henrique->P[i_enemy][j_enemy].type = 'E';
    return 1;
}

void game_screen (game Henrique, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (Henrique.P[i][j].type == 'E') {
                printf("\033[31mo ");
            } else if (Henrique.P[i][j].type == 'P') {
                printf("\033[34mo ");
            } else {
                printf("\033[30mo ");
            }
        }
        printf("\033[30m\n");
    }
}

void player_move(game * Henrique, int size) {
    int i, j, i_player, j_player;
    char key;
    while (1) {
        scanf("%c%*c", &key);
        if (key == 'a') {
            break;
        } else if (key == 'w') {
            break;
        } else if (key == 'd') {
            break;
        } else if (key == 's') {
            break;
        } else if (key == 'n') {
            break;
        }
    }
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (Henrique->P[i][j].type == 'P') {
                i_player = i;
                j_player = j;
            }
        }
    }
    if ((key == 'a') && (j_player > 0)) {
        Henrique->P[i_player][j_player].type ='N';
        Henrique->P[i_player][j_player - 1].type ='P';
    } else if ((key == 'w')  && (i_player > 0)) {
        Henrique->P[i_player][j_player].type ='N';
        Henrique->P[i_player - 1][j_player].type ='P';
    } else if ((key == 'd') && (j_player < size - 1)) {
        Henrique->P[i_player][j_player].type ='N';
        Henrique->P[i_player][j_player + 1].type ='P';
    } else if ((key == 's') && (i_player < size - 1)) {
        Henrique->P[i_player][j_player].type ='N';
        Henrique->P[i_player + 1][j_player].type ='P';
    }
}

void clean(position ** P, int size) {
    int i;
    for (i = 0; i < size; i++) {
        free(P[i]);
    }
    free(P);
}

# define MIN_SIZE 3
# define MAX_SIZE 21

void main() {
    game Henrique;
    int key = 0, first_time = 1, enemy_mov = 0;
    srand(time(0));
    printf("Digite o tamanho do lado do campo quadrado :\n");
    while ((key % 2 == 0) || (key < MIN_SIZE) || (key > MAX_SIZE)) {
        printf("Tamanho minimo : (3 x 3)\n");
        printf("Tamanho maximo : (21 x 21)\n");
        printf("Deve ser impar !\n");
        scanf("%d%*c", &key);
    }
    game_init(&Henrique, key);
    while (1) {
        if (enemy_location(&Henrique, key, first_time) == 0) {
            break;
        } else {
            if (first_time == 0) {
                enemy_mov++;
            }
        }
        game_screen(Henrique, key);
        player_move(&Henrique, key);
        if (first_time == 1) {
            first_time = 0;
        }
    }
    printf("Voce foi eliminado!\n");
    printf("Voce sobreviveu a %d movimentos do inimigo.\n", enemy_mov);
    clean(Henrique.P, key);
}