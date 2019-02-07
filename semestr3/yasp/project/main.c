# include <stdio.h>
# include <malloc.h>

struct Position{
	int n;
	char arr[9][9];
};
typedef struct Position Position;

Position* new_Position(int k){
	Position *pos = (Position*) malloc(1 * sizeof(Position*));
	pos->n = k;
	return pos;
}

Position* copy_Position(Position* pos){
    Position *copy = (Position*) malloc(1 * sizeof(Position*));
    copy->n = pos->n;
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
		for(int j = 1; j <= pos->n; j++){
			pos->arr[i][j] = get_next_char();
		}
	}
}

void printPosition(Position* pos){
	for(int i = 1; i <= pos->n; i++){
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
    int kol_hit = 0;
    for(int i = 1; i <= pos->n; i++){
        for(int j = 1; j <= pos->n; j++){
            if(pos->arr[i][j] == 'b'){
                if((1 <= i - 2) && (j + 2 <= pos->n)){
                    if(((pos->arr[i-1][i+1] == 'w') || (pos->arr[i-1][j+1] == 'W')) &&
                        (pos->arr[i-2][j+2] == '*')) kol_hit++;
                }
                if((1 <= i - 2) && (1 <= j - 2)){
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
                    for(int x = i - 2, y = j - 2; ((1 <= x) && (1 <= y)); x--; y--){
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
                    for(int x = i - 2, y = j + 2; ((1 <= x) && (y <= pos->n)); x--; y++){
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
                    for(int x = i + 2, y = j - 2; ((x <= pos->n) && (1 <= y)); x++; y--){
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
                    for(int x = i + 2, y = j + 2; ((x <= pos->n) && (y <= pos->n)); x++; y++){
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
    Position copy = copy_Position(pos);
    
    int kol_hit = 0;
    for(int i = 1; i <= pos->n; i++){
        for(int j = 1; j <= pos->n; j++){
            if(pos->arr[i][j] == 'b'){
                if((1 <= i - 2) && (j + 2 <= pos->n)){
                    if(((pos->arr[i-1][i+1] == 'w') || (pos->arr[i-1][j+1] == 'W')) &&
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
}

Position* Black_hit(Position* pos, int k){
    Position copy = copy_Position(pos);
    
    int kol_hit = 0;
    for(int i = 1; i <= pos->n; i++){
        for(int j = 1; j <= pos->n; j++){
            if(pos->arr[i][j] == 'B'){
                
                if((1 <= i - 2) && (1 <= j - 2)){
                    char last = pos->arr[i - 1][j - 1];
                    for(int x = i - 2, y = j - 2; ((1 <= x) && (1 <= y)); x--; y--){
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
                    for(int x = i - 2, y = j + 2; ((1 <= x) && (y <= pos->n)); x--; y++){
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
                    for(int x = i + 2, y = j - 2; ((x <= pos->n) && (1 <= y)); x++; y--){
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
                    for(int x = i + 2, y = j + 2; ((x <= pos->n) && (y <= pos->n)); x++; y++){
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
    Position* copy = copy_Position(pos);
    
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
	Position *pos1 = make_new_Pos(8);
	printf(" write position \n");
	readPosition(pos1);
	printf(" Hello 1 \n");
	printPosition(pos1);
	if(check_position(pos1)) printf("true");
	else printf("false");
}
