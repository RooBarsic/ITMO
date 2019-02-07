# include <stdio.h>
# include <malloc.h>
//#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include<stdbool.h>

struct Position{
	int n;
	char arr[9][9];
};
typedef struct Position Position;

void printPosition(Position* pos);

Position* new_Position(int k){
	Position *pos = (Position*) malloc(1 * sizeof(Position*));
	pos->n = k;
	return pos;
}

Position* copy_Position(Position* pos){
    Position *copy = (Position*) malloc(1 * sizeof(Position*));
    copy->n = pos->n;
    printf(" flag 3.1 \n");
    for(int i = 1; i <= pos->n; i++){
        for(int j = 1; j <= pos->n; j++){
            copy->arr[i][j] = pos->arr[i][j];
        }
    }
    return copy;
}

char get_next_char(){
	char e;
	while(1 == 1){
		scanf("%c", &e);
		if(e != '\n') return e;
	}
}

void readPosition(Position *pos){
	for(int i = 1; i <= pos->n; i++){
	    char buf[8];
	    scanf("%s", &buf);
	    pos->arr[i][0] = ' ';
		for(int j = 1; j <= pos->n; j++){
	        //scanf("%c", &pos->arr[i][j]);
	        pos->arr[i][j] = buf[j - 1];
	        //printf("%c", buf[j - 1]);
	    }
	    //scanf("%c", &pos->arr[i][0]);
	    //for(int j = 1; j <= pos->n; j++){
		//	pos->arr[i][j] = get_next_char();
		//}
	}
}

void printPosition(Position* pos){
    printf("  12345678 \n");
	for(int i = 1; i <= pos->n; i++){
	    printf("%d ", i);
	    //printf("%s ", pos->arr[i]);
		for(int j = 1; j <= pos->n; j++){
			printf("%c", pos->arr[i][j]);
		}
		printf("\n");
	}
}

bool check_position(Position* pos){
    int kol_b = 0;
    int kol_w = 0;
    for(int i = 1; i <= pos->n; i++){
        for(int j = 1; j <= pos->n; j++){
            if((pos->arr[i][j] != '*') && (pos->arr[i][j] != 'w') &&
                (pos->arr[i][j] != 'W') && (pos->arr[i][j] != 'b') &&
                (pos->arr[i][j] != 'B')) return false;
            if(((i + j) % 2 == 0) && (pos->arr[i][j] != '*')) return false;
            if((pos->arr[i][j] == 'W') || (pos->arr[i][j] == 'w')) kol_w++;
            if((pos->arr[i][j] == 'B') || (pos->arr[i][j] == 'b')) kol_b++;
        }
    }
    if((kol_w > 12) || (kol_b > 12)) return false;
    return true;
}

int check_black_hit(Position* pos){
    printf("check_black_hit \n");
    int kol_hit = 0;
    for(int i = 1; i <= pos->n; i++){
        for(int j = 1; j <= pos->n; j++){
            printf("i = %d j = %d \n", i, j);
            if(pos->arr[i][j] == 'b'){
                printf("  black \n");
                if((1 <= i - 2) && (j + 2 <= pos->n)){
                    printf("      can move i-2 j+2 \n");
                    if(((pos->arr[i-1][j+1] == 'w') || (pos->arr[i-1][j+1] == 'W')) &&
                        (pos->arr[i-2][j+2] == '*')) kol_hit++;
                }
                if((1 <= i - 2) && (1 <= j - 2)){
                    printf("      can move i-2 j-2 \n");
                    if(((pos->arr[i-1][j-1] == 'w') || (pos->arr[i-1][j-1] == 'W')) &&
                        (pos->arr[i-2][j-2] == '*')) kol_hit++;
                }
            }
        }
    }

    return kol_hit;
}


int check_Black_hit(Position* pos){
    int kol_hit = 0;
    for(int i = 1; i <= pos->n; i++){
        for(int j = 1; j <= pos->n; j++){
            if(pos->arr[i][j] == 'B'){

                if((1 <= i - 2) && (1 <= j - 2)){
                    char last = pos->arr[i - 1][j - 1];
                    for(int x = i - 2, y = j - 2; ((1 <= x) && (1 <= y)); x--, y--){
                        if((pos->arr[x][y] == '*') && ((last == 'w') || (last == 'W'))){
                            kol_hit++;
                            break;
                        }
                        if(last != '*') break;
                        last = pos->arr[x][y];
                    }
                }

                if((1 <= i - 2) && (j + 2 <= pos->n)){
                    char last = pos->arr[i - 1][j + 1];
                    for(int x = i - 2, y = j + 2; ((1 <= x) && (y <= pos->n)); x--, y++){
                        if((pos->arr[x][y] == '*') && ((last == 'w') || (last == 'W'))){
                            kol_hit++;
                            break;
                        }
                        if(last != '*') break;
                        last = pos->arr[x][y];
                    }
                }

                if((i + 2 <= pos->n) && (1 <= j - 2)){
                    char last = pos->arr[i + 1][j - 1];
                    for(int x = i + 2, y = j - 2; ((x <= pos->n) && (1 <= y)); x++, y--){
                        if((pos->arr[x][y] == '*') && ((last == 'w') || (last == 'W'))){
                            kol_hit++;
                            break;
                        }
                        if(last != '*') break;
                        last = pos->arr[x][y];
                    }
                }

                if((i + 2 <= pos->n) && (j + 2 <= pos->n)){
                    char last = pos->arr[i + 1][j + 1];
                    for(int x = i + 2, y = j + 2; ((x <= pos->n) && (y <= pos->n)); x++, y++){
                        if((pos->arr[x][y] == '*') && ((last == 'w') || (last == 'W'))){
                            kol_hit++;
                            break;
                        }
                        if(last != '*') break;
                        last = pos->arr[x][y];
                    }
                }
            }
        }
    }

    return kol_hit;
}

Position* black_hit(Position* pos, int k){
    Position* copy = pos; //copy_Position(pos);

    int kol_hit = 0;
    for(int i = 1; i <= pos->n; i++){
        for(int j = 1; j <= pos->n; j++){
            if(pos->arr[i][j] == 'b'){
                if((1 <= i - 2) && (j + 2 <= pos->n)){
                    if(((pos->arr[i-1][j+1] == 'w') || (pos->arr[i-1][j+1] == 'W')) &&
                        (pos->arr[i-2][j+2] == '*')) kol_hit++;
                    if(kol_hit == k){
                        copy->arr[i-2][j+2] = copy->arr[i][j];
                        copy->arr[i][j] = copy->arr[i-1][j+1] = '*';
                        return copy;
                    }
                }
                if((1 <= i - 2) && (1 <= j - 2)){
                    if(((pos->arr[i-1][j-1] == 'w') || (pos->arr[i-1][j-1] == 'W')) &&
                        (pos->arr[i-2][j-2] == '*')) kol_hit++;
                    if(kol_hit == k){
                        copy->arr[i-2][j-2] = copy->arr[i][j];
                        copy->arr[i][j] = copy->arr[i-1][j-1] = '*';
                        return copy;
                    }
                }
            }
        }
    }
    return copy;
}

Position* Black_hit(Position* pos, int k){
    Position* copy = pos; //copy_Position(pos);

    int kol_hit = 0;
    for(int i = 1; i <= pos->n; i++){
        for(int j = 1; j <= pos->n; j++){
            if(pos->arr[i][j] == 'B'){

                if((1 <= i - 2) && (1 <= j - 2)){
                    char last = pos->arr[i - 1][j - 1];
                    for(int x = i - 2, y = j - 2; ((1 <= x) && (1 <= y)); x--, y--){
                        if((pos->arr[x][y] == '*') && ((last == 'w') || (last == 'W'))){
                            kol_hit++;
                            if(kol_hit == k){
                                copy->arr[x][y] = copy->arr[i][j];
                                copy->arr[i][j] = copy->arr[x+1][y+1] = '*';
                                return copy;
                            }
                            break;
                        }
                        if(last != '*') break;
                        last = pos->arr[x][y];
                    }
                }

                if((1 <= i - 2) && (j + 2 <= pos->n)){
                    char last = pos->arr[i - 1][j + 1];
                    for(int x = i - 2, y = j + 2; ((1 <= x) && (y <= pos->n)); x--, y++){
                        if((pos->arr[x][y] == '*') && ((last == 'w') || (last == 'W'))){
                            kol_hit++;
                            if(kol_hit == k){
                                copy->arr[x][y] = copy->arr[i][j];
                                copy->arr[i][j] = copy->arr[x+1][y-1] = '*';
                                return copy;
                            }
                            break;
                        }
                        if(last != '*') break;
                        last = pos->arr[x][y];
                    }
                }

                if((i + 2 <= pos->n) && (1 <= j - 2)){
                    char last = pos->arr[i + 1][j - 1];
                    for(int x = i + 2, y = j - 2; ((x <= pos->n) && (1 <= y)); x++, y--){
                        if((pos->arr[x][y] == '*') && ((last == 'w') || (last == 'W'))){
                            kol_hit++;
                            if(kol_hit == k){
                                copy->arr[x][y] = copy->arr[i][j];
                                copy->arr[i][j] = copy->arr[x-1][y+1] = '*';
                                return copy;
                            }
                            break;
                        }
                        if(last != '*') break;
                        last = pos->arr[x][y];
                    }
                }

                if((i + 2 <= pos->n) && (j + 2 <= pos->n)){
                    char last = pos->arr[i + 1][j + 1];
                    for(int x = i + 2, y = j + 2; ((x <= pos->n) && (y <= pos->n)); x++, y++){
                        if((pos->arr[x][y] == '*') && ((last == 'w') || (last == 'W'))){
                            kol_hit++;
                            if(kol_hit == k){
                                copy->arr[x][y] = copy->arr[i][j];
                                copy->arr[i][j] = copy->arr[x-1][y-1] = '*';
                                return copy;
                            }
                            break;
                        }
                        if(last != '*') break;
                        last = pos->arr[x][y];
                    }
                }
            }
        }
    }

    return copy;
}

int check_bBlack_move(Position* pos){
    int kol_move = 0;
    for(int i = 1; i <= pos->n; i++){
        for(int j = 1; j <= pos->n; j++){
            if(pos->arr[i][j] == 'b'){
                if((1 <= i-1) && (1 <= j-1) && (pos->arr[i-1][j-1] == '*')) kol_move++;
                if((1 <= i-1) && (j+1 <= pos->n) && (pos->arr[i-1][j+1] == '*')) kol_move++;
            }
            else if(pos->arr[i][j] == 'B'){
                for(int x = i - 1, y = j - 1; ((1 <= x) && (1 <= y)); x--, y--){
                    if(pos->arr[x][y] == '*') kol_move++;
                    else break;
                }
                for(int x = i - 1, y = j + 1; ((1 <= x) && (y <= pos->n)); x--, y++){
                    if(pos->arr[x][y] == '*') kol_move++;
                    else break;
                }
                for(int x = i + 1, y = j - 1; ((x <= pos->n) && (1 <= y)); x++, y--){
                    if(pos->arr[x][y] == '*') kol_move++;
                    else break;
                }
                for(int x = i + 1, y = j + 1; ((x <= pos->n) && (y <= pos->n)); x++, y++){
                    if(pos->arr[x][y] == '*') kol_move++;
                    else break;
                }
            }
        }
    }
    return kol_move;
}

Position* bBlack_move(Position* pos, int k){
    Position* copy = pos; //copy_Position(pos);
    
    int kol_move = 0;
    for(int i = 1; i <= pos->n; i++){
        for(int j = 1; j <= pos->n; j++){
            if(pos->arr[i][j] == 'b'){
                if((1 <= i-1) && (1 <= j-1) && (pos->arr[i-1][j-1] == '*')){
                    kol_move++;
                    if(kol_move == k){
                        copy->arr[i-1][j-1] = copy->arr[i][j];
                        copy->arr[i][j] = '*';
                        return copy;
                    }
                }
                if((1 <= i-1) && (j+1 <= pos->n) && (pos->arr[i-1][j+1] == '*')){
                    kol_move++;
                    if(kol_move == k){
                        copy->arr[i-1][j+1] = copy->arr[i][j];
                        copy->arr[i][j] = '*';
                        return copy;
                    }
                }
            }
            else if(pos->arr[i][j] == 'B'){
                for(int x = i - 1, y = j - 1; ((1 <= x) && (1 <= y)); x--, y--){
                    if(pos->arr[x][y] == '*') kol_move++;
                    else break;

                    if(kol_move == k){
                        copy->arr[x][y] = copy->arr[i][j];
                        copy->arr[i][j] = '*';
                        return copy;
                    }
                }
                for(int x = i - 1, y = j + 1; ((1 <= x) && (y <= pos->n)); x--, y++){
                    if(pos->arr[x][y] == '*') kol_move++;
                    else break;

                    if(kol_move == k){
                        copy->arr[x][y] = copy->arr[i][j];
                        copy->arr[i][j] = '*';
                        return copy;
                    }
                }
                for(int x = i + 1, y = j - 1; ((x <= pos->n) && (1 <= y)); x++, y--){
                    if(pos->arr[x][y] == '*') kol_move++;
                    else break;

                    if(kol_move == k){
                        copy->arr[x][y] = copy->arr[i][j];
                        copy->arr[i][j] = '*';
                        return copy;
                    }
                }
                for(int x = i + 1, y = j + 1; ((x <= pos->n) && (y <= pos->n)); x++, y++){
                    if(pos->arr[x][y] == '*') kol_move++;
                    else break;

                    if(kol_move == k){
                        copy->arr[x][y] = copy->arr[i][j];
                        copy->arr[i][j] = '*';
                        return copy;
                    }
                }
            }
        }
    }
    return copy;
}

int main(){
    srand(time(NULL));
    Position* pos = new_Position(8);
    printf("write position \n");
    readPosition(pos);
    printf("Whos turn (2-b, 1-w)? \n");
    int t;
    scanf("%d", &t);
    while(1 == 1){
        printf(" position 1 = \n");
        printPosition(pos);
        if(t == 1){
            printf("Your turn \n");
            int k;
            printf("write number of jumping \n");
            scanf("%d", &k);
            for(int i = 1; i <= k; i++){
                printf(" i = %d \n", i);
                int x1, y1, x2, y2;
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                printf("x1 = %d y1 = %d char = %c \n", x1, y1, pos->arr[x1][y1]);
                printf("x2 = %d y2 = %d char = %c \n", x2, y2, pos->arr[x2][y2]);
                char e = pos->arr[x1][y1];
                pos->arr[x1][y1] = pos->arr[x2][y2];
                pos->arr[x2][y2] = e;
                printf(" done pos = \n");
                printf("x1 = %d y1 = %d char = %c \n", x1, y1, pos->arr[x1][y1]);
                printf("x2 = %d y2 = %d char = %c \n", x2, y2, pos->arr[x2][y2]);
                
                printPosition(pos);
            }
            
            printPosition(pos);
            //readPosition(pos);
            
        }
        else {
            printf("My turn \n");
            printf(" Go next ? \n");
            int ddl;
            scanf("%d", &ddl);
            int kol_hit_b = check_black_hit(pos);
            int kol_hit_B = check_Black_hit(pos);
            printf("kol_hit_b = %d \n", kol_hit_b);
            printf("kol_hit_B = %d \n", kol_hit_B);
            if(kol_hit_b > 0){
                if(kol_hit_B > 0){
                    if((rand() % 2) == 1){
                        pos = black_hit(pos, (rand() % kol_hit_b) + 1);
                    }
                    else {
                        pos = Black_hit(pos, (rand() % kol_hit_B) + 1);
                    }
                }
                else {
                    pos = black_hit(pos, (rand() % kol_hit_b) + 1);
                }
            }
            else {
                if(kol_hit_B > 0){
                    pos = Black_hit(pos, (rand() % kol_hit_B) + 1);
                }
                else {
                    int kol_move = check_bBlack_move(pos);
                    if(kol_move == 0) {
                        printf(" I can't move \n");
                        printPosition(pos);
                        return 0;
                    }
                    pos = bBlack_move(pos, (rand() % kol_move) + 1);
                }
            }
            printf("\n\n\n");
            printPosition(pos);
            printf(" \n\n\n");
        
        }

        t = (t % 2) + 1;
        
    }
}
