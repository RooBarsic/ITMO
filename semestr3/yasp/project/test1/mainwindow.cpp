#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bits/stdc++.h>
#include<QDebug>
using namespace  std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->pushButton->text() == "0") ui->pushButton->setText("*");
    else if(ui->pushButton->text() == "*") ui->pushButton->setText("b");
    else if(ui->pushButton->text() == "b") ui->pushButton->setText("B");
    else if(ui->pushButton->text() == "B") ui->pushButton->setText("w");
    else if(ui->pushButton->text() == "w") ui->pushButton->setText("W");
    else if(ui->pushButton->text() == "W") ui->pushButton->setText("*");
}
//-------------------------------------------------------------------------------------------------
// Chess brain
struct Position{
    int n;
    char arr[9][9];
};
typedef struct Position Position;

Position* new_Position(int k){
    Position *pos = (Position*) malloc(1 * sizeof(Position*));
    k = 8;
    pos->n = k;
    return pos;
}

static void fillPosition(Position *pos){
    for(int i = 1; i <= pos->n; i++){
        for(int j = 1; j <= pos->n; j++){
            pos->arr[i][j] = '*';
        }
    }
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
                /// new cod begin -----------------------------------------------------------------
                if((i + 2 <= pos->n) && (1 <= j - 2)){
                    printf("      can move i+2 j-2");
                    if(((pos->arr[i+1][j-1] == 'w') || (pos->arr[i+1][j-1] == 'W')) &&
                        (pos->arr[i+2][j-2] == '*')) kol_hit++;
                }
                if((i + 2 <= pos->n) && (j + 2 <= pos->n)){
                    printf("      can move i-2 j+2 \n");
                    if(((pos->arr[i+1][j+1] == 'w') || (pos->arr[i+1][j+1] == 'W')) &&
                        (pos->arr[i+2][j+2] == '*')) kol_hit++;
                }
                /// new cod end -----------------------------------------------------------------
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
                /// new cod begin -----------------------------------------------------------------
                if((i + 2 <= pos->n) && (1 <= j - 2)){
                    printf("      can move i+2 j-2");
                    if(((pos->arr[i+1][j-1] == 'w') || (pos->arr[i+1][j-1] == 'W')) &&
                        (pos->arr[i+2][j-2] == '*')) kol_hit++;
                    if(kol_hit == k){
                        copy->arr[i+2][j-2] = copy->arr[i][j];
                        copy->arr[i][j] = copy->arr[i+1][j-1] = '*';
                        return copy;
                    }
                }
                if((i + 2 <= pos->n) && (j + 2 <= pos->n)){
                    printf("      can move i-2 j+2 \n");
                    if(((pos->arr[i+1][j+1] == 'w') || (pos->arr[i+1][j+1] == 'W')) &&
                        (pos->arr[i+2][j+2] == '*')) kol_hit++;
                    if(kol_hit == k){
                        copy->arr[i+2][j+2] = copy->arr[i][j];
                        copy->arr[i][j] = copy->arr[i+1][j+1] = '*';
                        return copy;
                    }
                }
                /// new cod end -----------------------------------------------------------------
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


void printPosition(Position* pos){
    qDebug() << "     12345678";
    for(int i = 1; i <= pos->n; i++){
        QString s;
        for(int j = 1; j <= pos->n; j++){
            s = s + pos->arr[i][j];
        }
        qDebug() << i << " " << s;
    }
}

char get_char(QString s){
    if(s == "*") return '*';
    if(s == "b") return 'b';
    if(s == "B") return 'B';
    if(s == "w") return 'w';
    if(s == "W") return 'W';
    return '*';
}

QString get_string(char s){
    if(s == '*') return "*";
    if(s == 'b') return "b";
    if(s == 'B') return "B";
    if(s == 'w') return "w";
    if(s == 'W') return "W";
    return "*";
}

//-------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_65_clicked()
{
    srand(time(NULL));
    Position* pos = new_Position(8);
        /// filling pos->arr[][] ---------------------------------------------------------------------
    qDebug() << " Start filling pos->arr " << '\n';
    fillPosition(pos);
    pos->arr[1][1] = get_char(ui->pushButton->text());
    pos->arr[1][2] = get_char(ui->pushButton_2->text());
    pos->arr[1][3] = get_char(ui->pushButton_3->text());
    pos->arr[1][4] = get_char(ui->pushButton_4->text());
    pos->arr[1][5] = get_char(ui->pushButton_5->text());
    pos->arr[1][6] = get_char(ui->pushButton_6->text());
    pos->arr[1][7] = get_char(ui->pushButton_7->text());
    pos->arr[1][8] = get_char(ui->pushButton_8->text());
    pos->arr[2][1] = get_char(ui->pushButton_9->text());
    pos->arr[2][2] = get_char(ui->pushButton_10->text());
    pos->arr[2][3] = get_char(ui->pushButton_11->text());
    pos->arr[2][4] = get_char(ui->pushButton_12->text());
    pos->arr[2][5] = get_char(ui->pushButton_13->text());
    pos->arr[2][6] = get_char(ui->pushButton_14->text());
    pos->arr[2][7] = get_char(ui->pushButton_15->text());
    pos->arr[2][8] = get_char(ui->pushButton_16->text());
    pos->arr[3][1] = get_char(ui->pushButton_17->text());
    pos->arr[3][2] = get_char(ui->pushButton_18->text());
    pos->arr[3][3] = get_char(ui->pushButton_19->text());
    pos->arr[3][4] = get_char(ui->pushButton_20->text());
    pos->arr[3][5] = get_char(ui->pushButton_21->text());
    pos->arr[3][6] = get_char(ui->pushButton_22->text());
    pos->arr[3][7] = get_char(ui->pushButton_23->text());
    pos->arr[3][8] = get_char(ui->pushButton_24->text());
    pos->arr[4][1] = get_char(ui->pushButton_25->text());
    pos->arr[4][2] = get_char(ui->pushButton_26->text());
    pos->arr[4][3] = get_char(ui->pushButton_27->text());
    pos->arr[4][4] = get_char(ui->pushButton_28->text());
    pos->arr[4][5] = get_char(ui->pushButton_29->text());
    pos->arr[4][6] = get_char(ui->pushButton_30->text());
    pos->arr[4][7] = get_char(ui->pushButton_31->text());
    pos->arr[4][8] = get_char(ui->pushButton_32->text());
    pos->arr[5][1] = get_char(ui->pushButton_33->text());
    pos->arr[5][2] = get_char(ui->pushButton_34->text());
    pos->arr[5][3] = get_char(ui->pushButton_35->text());
    pos->arr[5][4] = get_char(ui->pushButton_36->text());
    pos->arr[5][5] = get_char(ui->pushButton_37->text());
    pos->arr[5][6] = get_char(ui->pushButton_38->text());
    pos->arr[5][7] = get_char(ui->pushButton_39->text());
    pos->arr[5][8] = get_char(ui->pushButton_40->text());
    pos->arr[6][1] = get_char(ui->pushButton_41->text());
    pos->arr[6][2] = get_char(ui->pushButton_42->text());
    pos->arr[6][3] = get_char(ui->pushButton_43->text());
    pos->arr[6][4] = get_char(ui->pushButton_44->text());
    pos->arr[6][5] = get_char(ui->pushButton_45->text());
    pos->arr[6][6] = get_char(ui->pushButton_46->text());
    pos->arr[6][7] = get_char(ui->pushButton_47->text());
    pos->arr[6][8] = get_char(ui->pushButton_48->text());
    pos->arr[7][1] = get_char(ui->pushButton_49->text());
    pos->arr[7][2] = get_char(ui->pushButton_50->text());
    pos->arr[7][3] = get_char(ui->pushButton_51->text());
    pos->arr[7][4] = get_char(ui->pushButton_52->text());
    pos->arr[7][5] = get_char(ui->pushButton_53->text());
    pos->arr[7][6] = get_char(ui->pushButton_54->text());
    pos->arr[7][7] = get_char(ui->pushButton_55->text());
    pos->arr[7][8] = get_char(ui->pushButton_56->text());
    pos->arr[8][1] = get_char(ui->pushButton_57->text());
    pos->arr[8][2] = get_char(ui->pushButton_58->text());
    pos->arr[8][3] = get_char(ui->pushButton_59->text());
    pos->arr[8][4] = get_char(ui->pushButton_60->text());
    pos->arr[8][5] = get_char(ui->pushButton_61->text());
    pos->arr[8][6] = get_char(ui->pushButton_62->text());
    pos->arr[8][7] = get_char(ui->pushButton_63->text());
    pos->arr[8][8] = get_char(ui->pushButton_64->text());

    qDebug() << " finish filling pos->arr" << '\n';
        /// ---------- end filling pos->arr[][] -----------------------------------------------------

    printPosition(pos);

        /// -------- main algorithm of game -----------------------------------------------------------
        qDebug() << " @ Start main game algorithm ";
    int kol_hit_b = check_black_hit(pos);
    int kol_hit_B = check_Black_hit(pos);
    qDebug() << " kol_hit_b = " << kol_hit_b << '\n'
             << " kol_hit_B = " << kol_hit_B;
    if(kol_hit_b + kol_hit_B > 0){
        qDebug() << " I can beat ";
        while(kol_hit_b + kol_hit_B > 0){
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
            }
            printPosition(pos);
            kol_hit_b = check_black_hit(pos);
            kol_hit_B = check_Black_hit(pos);
            qDebug() << " kol_hit_b = " << kol_hit_b << '\n'
                     << " kol_hit_B = " << kol_hit_B;
        }
    }
    else {
        qDebug() << " I can't' beat ";
        int kol_move = check_bBlack_move(pos);
        qDebug() << " kol_move = " << kol_move;
        if(kol_move == 0) {
            qDebug() << " I can't move \n";
            return ;
        }
        pos = bBlack_move(pos, (rand() % kol_move) + 1);
    }
    qDebug() << " result position ";
    printPosition(pos);
        qDebug() << " @ End main game algorithm ";
        /// -------- end of main algorithm of game -----------------------------------------------------------

       /// ---------- Printing result to UI -----------------------------------------------------------------
       qDebug() << " @ Start Printing result to UI ";
    ui->pushButton->setText(get_string(pos->arr[1][1]));
    ui->pushButton_2->setText(get_string(pos->arr[1][2]));
    ui->pushButton_3->setText(get_string(pos->arr[1][3]));
    ui->pushButton_4->setText(get_string(pos->arr[1][4]));
    ui->pushButton_5->setText(get_string(pos->arr[1][5]));
    ui->pushButton_6->setText(get_string(pos->arr[1][6]));
    ui->pushButton_7->setText(get_string(pos->arr[1][7]));
    ui->pushButton_8->setText(get_string(pos->arr[1][8]));
    ui->pushButton_9->setText(get_string(pos->arr[2][1]));
    ui->pushButton_10->setText(get_string(pos->arr[2][2]));
    ui->pushButton_11->setText(get_string(pos->arr[2][3]));
    ui->pushButton_12->setText(get_string(pos->arr[2][4]));
    ui->pushButton_13->setText(get_string(pos->arr[2][5]));
    ui->pushButton_14->setText(get_string(pos->arr[2][6]));
    ui->pushButton_15->setText(get_string(pos->arr[2][7]));
    ui->pushButton_16->setText(get_string(pos->arr[2][8]));
    ui->pushButton_17->setText(get_string(pos->arr[3][1]));
    ui->pushButton_18->setText(get_string(pos->arr[3][2]));
    ui->pushButton_19->setText(get_string(pos->arr[3][3]));
    ui->pushButton_20->setText(get_string(pos->arr[3][4]));
    ui->pushButton_21->setText(get_string(pos->arr[3][5]));
    ui->pushButton_22->setText(get_string(pos->arr[3][6]));
    ui->pushButton_23->setText(get_string(pos->arr[3][7]));
    ui->pushButton_24->setText(get_string(pos->arr[3][8]));
    ui->pushButton_25->setText(get_string(pos->arr[4][1]));
    ui->pushButton_26->setText(get_string(pos->arr[4][2]));
    ui->pushButton_27->setText(get_string(pos->arr[4][3]));
    ui->pushButton_28->setText(get_string(pos->arr[4][4]));
    ui->pushButton_29->setText(get_string(pos->arr[4][5]));
    ui->pushButton_30->setText(get_string(pos->arr[4][6]));
    ui->pushButton_31->setText(get_string(pos->arr[4][7]));
    ui->pushButton_32->setText(get_string(pos->arr[4][8]));
    ui->pushButton_33->setText(get_string(pos->arr[5][1]));
    ui->pushButton_34->setText(get_string(pos->arr[5][2]));
    ui->pushButton_35->setText(get_string(pos->arr[5][3]));
    ui->pushButton_36->setText(get_string(pos->arr[5][4]));
    ui->pushButton_37->setText(get_string(pos->arr[5][5]));
    ui->pushButton_38->setText(get_string(pos->arr[5][6]));
    ui->pushButton_39->setText(get_string(pos->arr[5][7]));
    ui->pushButton_40->setText(get_string(pos->arr[5][8]));
    ui->pushButton_41->setText(get_string(pos->arr[6][1]));
    ui->pushButton_42->setText(get_string(pos->arr[6][2]));
    ui->pushButton_43->setText(get_string(pos->arr[6][3]));
    ui->pushButton_44->setText(get_string(pos->arr[6][4]));
    ui->pushButton_45->setText(get_string(pos->arr[6][5]));
    ui->pushButton_46->setText(get_string(pos->arr[6][6]));
    ui->pushButton_47->setText(get_string(pos->arr[6][7]));
    ui->pushButton_48->setText(get_string(pos->arr[6][8]));
    ui->pushButton_49->setText(get_string(pos->arr[7][1]));
    ui->pushButton_50->setText(get_string(pos->arr[7][2]));
    ui->pushButton_51->setText(get_string(pos->arr[7][3]));
    ui->pushButton_52->setText(get_string(pos->arr[7][4]));
    ui->pushButton_53->setText(get_string(pos->arr[7][5]));
    ui->pushButton_54->setText(get_string(pos->arr[7][6]));
    ui->pushButton_55->setText(get_string(pos->arr[7][7]));
    ui->pushButton_56->setText(get_string(pos->arr[7][8]));
    ui->pushButton_57->setText(get_string(pos->arr[8][1]));
    ui->pushButton_58->setText(get_string(pos->arr[8][2]));
    ui->pushButton_59->setText(get_string(pos->arr[8][3]));
    ui->pushButton_60->setText(get_string(pos->arr[8][4]));
    ui->pushButton_61->setText(get_string(pos->arr[8][5]));
    ui->pushButton_62->setText(get_string(pos->arr[8][6]));
    ui->pushButton_63->setText(get_string(pos->arr[8][7]));
    ui->pushButton_64->setText(get_string(pos->arr[8][8]));
       qDebug() << " @ End Printing result to UI ";
       /// -----------end of Printing result to UI -----------------------------------------------------------

}

void MainWindow::on_pushButton_66_clicked()
{

}

void MainWindow::on_pushButton_2_clicked(){
  if(ui->pushButton_2->text() == "0") ui->pushButton_2->setText("*");
  else if(ui->pushButton_2->text() == "*") ui->pushButton_2->setText("b");
  else if(ui->pushButton_2->text() == "b") ui->pushButton_2->setText("B");
  else if(ui->pushButton_2->text() == "B") ui->pushButton_2->setText("w");
  else if(ui->pushButton_2->text() == "w") ui->pushButton_2->setText("W");
  else if(ui->pushButton_2->text() == "W") ui->pushButton_2->setText("*");
}
void MainWindow::on_pushButton_3_clicked(){
  if(ui->pushButton_3->text() == "0") ui->pushButton_3->setText("*");
  else if(ui->pushButton_3->text() == "*") ui->pushButton_3->setText("b");
  else if(ui->pushButton_3->text() == "b") ui->pushButton_3->setText("B");
  else if(ui->pushButton_3->text() == "B") ui->pushButton_3->setText("w");
  else if(ui->pushButton_3->text() == "w") ui->pushButton_3->setText("W");
  else if(ui->pushButton_3->text() == "W") ui->pushButton_3->setText("*");
}
void MainWindow::on_pushButton_4_clicked(){
  if(ui->pushButton_4->text() == "0") ui->pushButton_4->setText("*");
  else if(ui->pushButton_4->text() == "*") ui->pushButton_4->setText("b");
  else if(ui->pushButton_4->text() == "b") ui->pushButton_4->setText("B");
  else if(ui->pushButton_4->text() == "B") ui->pushButton_4->setText("w");
  else if(ui->pushButton_4->text() == "w") ui->pushButton_4->setText("W");
  else if(ui->pushButton_4->text() == "W") ui->pushButton_4->setText("*");
}
void MainWindow::on_pushButton_5_clicked(){
  if(ui->pushButton_5->text() == "0") ui->pushButton_5->setText("*");
  else if(ui->pushButton_5->text() == "*") ui->pushButton_5->setText("b");
  else if(ui->pushButton_5->text() == "b") ui->pushButton_5->setText("B");
  else if(ui->pushButton_5->text() == "B") ui->pushButton_5->setText("w");
  else if(ui->pushButton_5->text() == "w") ui->pushButton_5->setText("W");
  else if(ui->pushButton_5->text() == "W") ui->pushButton_5->setText("*");
}
void MainWindow::on_pushButton_6_clicked(){
  if(ui->pushButton_6->text() == "0") ui->pushButton_6->setText("*");
  else if(ui->pushButton_6->text() == "*") ui->pushButton_6->setText("b");
  else if(ui->pushButton_6->text() == "b") ui->pushButton_6->setText("B");
  else if(ui->pushButton_6->text() == "B") ui->pushButton_6->setText("w");
  else if(ui->pushButton_6->text() == "w") ui->pushButton_6->setText("W");
  else if(ui->pushButton_6->text() == "W") ui->pushButton_6->setText("*");
}
void MainWindow::on_pushButton_7_clicked(){
  if(ui->pushButton_7->text() == "0") ui->pushButton_7->setText("*");
  else if(ui->pushButton_7->text() == "*") ui->pushButton_7->setText("b");
  else if(ui->pushButton_7->text() == "b") ui->pushButton_7->setText("B");
  else if(ui->pushButton_7->text() == "B") ui->pushButton_7->setText("w");
  else if(ui->pushButton_7->text() == "w") ui->pushButton_7->setText("W");
  else if(ui->pushButton_7->text() == "W") ui->pushButton_7->setText("*");
}
void MainWindow::on_pushButton_8_clicked(){
  if(ui->pushButton_8->text() == "0") ui->pushButton_8->setText("*");
  else if(ui->pushButton_8->text() == "*") ui->pushButton_8->setText("b");
  else if(ui->pushButton_8->text() == "b") ui->pushButton_8->setText("B");
  else if(ui->pushButton_8->text() == "B") ui->pushButton_8->setText("w");
  else if(ui->pushButton_8->text() == "w") ui->pushButton_8->setText("W");
  else if(ui->pushButton_8->text() == "W") ui->pushButton_8->setText("*");
}
void MainWindow::on_pushButton_9_clicked(){
  if(ui->pushButton_9->text() == "0") ui->pushButton_9->setText("*");
  else if(ui->pushButton_9->text() == "*") ui->pushButton_9->setText("b");
  else if(ui->pushButton_9->text() == "b") ui->pushButton_9->setText("B");
  else if(ui->pushButton_9->text() == "B") ui->pushButton_9->setText("w");
  else if(ui->pushButton_9->text() == "w") ui->pushButton_9->setText("W");
  else if(ui->pushButton_9->text() == "W") ui->pushButton_9->setText("*");
}
void MainWindow::on_pushButton_10_clicked(){
  if(ui->pushButton_10->text() == "0") ui->pushButton_10->setText("*");
  else if(ui->pushButton_10->text() == "*") ui->pushButton_10->setText("b");
  else if(ui->pushButton_10->text() == "b") ui->pushButton_10->setText("B");
  else if(ui->pushButton_10->text() == "B") ui->pushButton_10->setText("w");
  else if(ui->pushButton_10->text() == "w") ui->pushButton_10->setText("W");
  else if(ui->pushButton_10->text() == "W") ui->pushButton_10->setText("*");
}
void MainWindow::on_pushButton_11_clicked(){
  if(ui->pushButton_11->text() == "0") ui->pushButton_11->setText("*");
  else if(ui->pushButton_11->text() == "*") ui->pushButton_11->setText("b");
  else if(ui->pushButton_11->text() == "b") ui->pushButton_11->setText("B");
  else if(ui->pushButton_11->text() == "B") ui->pushButton_11->setText("w");
  else if(ui->pushButton_11->text() == "w") ui->pushButton_11->setText("W");
  else if(ui->pushButton_11->text() == "W") ui->pushButton_11->setText("*");
}
void MainWindow::on_pushButton_12_clicked(){
  if(ui->pushButton_12->text() == "0") ui->pushButton_12->setText("*");
  else if(ui->pushButton_12->text() == "*") ui->pushButton_12->setText("b");
  else if(ui->pushButton_12->text() == "b") ui->pushButton_12->setText("B");
  else if(ui->pushButton_12->text() == "B") ui->pushButton_12->setText("w");
  else if(ui->pushButton_12->text() == "w") ui->pushButton_12->setText("W");
  else if(ui->pushButton_12->text() == "W") ui->pushButton_12->setText("*");
}
void MainWindow::on_pushButton_13_clicked(){
  if(ui->pushButton_13->text() == "0") ui->pushButton_13->setText("*");
  else if(ui->pushButton_13->text() == "*") ui->pushButton_13->setText("b");
  else if(ui->pushButton_13->text() == "b") ui->pushButton_13->setText("B");
  else if(ui->pushButton_13->text() == "B") ui->pushButton_13->setText("w");
  else if(ui->pushButton_13->text() == "w") ui->pushButton_13->setText("W");
  else if(ui->pushButton_13->text() == "W") ui->pushButton_13->setText("*");
}
void MainWindow::on_pushButton_14_clicked(){
  if(ui->pushButton_14->text() == "0") ui->pushButton_14->setText("*");
  else if(ui->pushButton_14->text() == "*") ui->pushButton_14->setText("b");
  else if(ui->pushButton_14->text() == "b") ui->pushButton_14->setText("B");
  else if(ui->pushButton_14->text() == "B") ui->pushButton_14->setText("w");
  else if(ui->pushButton_14->text() == "w") ui->pushButton_14->setText("W");
  else if(ui->pushButton_14->text() == "W") ui->pushButton_14->setText("*");
}
void MainWindow::on_pushButton_15_clicked(){
  if(ui->pushButton_15->text() == "0") ui->pushButton_15->setText("*");
  else if(ui->pushButton_15->text() == "*") ui->pushButton_15->setText("b");
  else if(ui->pushButton_15->text() == "b") ui->pushButton_15->setText("B");
  else if(ui->pushButton_15->text() == "B") ui->pushButton_15->setText("w");
  else if(ui->pushButton_15->text() == "w") ui->pushButton_15->setText("W");
  else if(ui->pushButton_15->text() == "W") ui->pushButton_15->setText("*");
}
void MainWindow::on_pushButton_16_clicked(){
  if(ui->pushButton_16->text() == "0") ui->pushButton_16->setText("*");
  else if(ui->pushButton_16->text() == "*") ui->pushButton_16->setText("b");
  else if(ui->pushButton_16->text() == "b") ui->pushButton_16->setText("B");
  else if(ui->pushButton_16->text() == "B") ui->pushButton_16->setText("w");
  else if(ui->pushButton_16->text() == "w") ui->pushButton_16->setText("W");
  else if(ui->pushButton_16->text() == "W") ui->pushButton_16->setText("*");
}
void MainWindow::on_pushButton_17_clicked(){
  if(ui->pushButton_17->text() == "0") ui->pushButton_17->setText("*");
  else if(ui->pushButton_17->text() == "*") ui->pushButton_17->setText("b");
  else if(ui->pushButton_17->text() == "b") ui->pushButton_17->setText("B");
  else if(ui->pushButton_17->text() == "B") ui->pushButton_17->setText("w");
  else if(ui->pushButton_17->text() == "w") ui->pushButton_17->setText("W");
  else if(ui->pushButton_17->text() == "W") ui->pushButton_17->setText("*");
}
void MainWindow::on_pushButton_18_clicked(){
  if(ui->pushButton_18->text() == "0") ui->pushButton_18->setText("*");
  else if(ui->pushButton_18->text() == "*") ui->pushButton_18->setText("b");
  else if(ui->pushButton_18->text() == "b") ui->pushButton_18->setText("B");
  else if(ui->pushButton_18->text() == "B") ui->pushButton_18->setText("w");
  else if(ui->pushButton_18->text() == "w") ui->pushButton_18->setText("W");
  else if(ui->pushButton_18->text() == "W") ui->pushButton_18->setText("*");
}
void MainWindow::on_pushButton_19_clicked(){
  if(ui->pushButton_19->text() == "0") ui->pushButton_19->setText("*");
  else if(ui->pushButton_19->text() == "*") ui->pushButton_19->setText("b");
  else if(ui->pushButton_19->text() == "b") ui->pushButton_19->setText("B");
  else if(ui->pushButton_19->text() == "B") ui->pushButton_19->setText("w");
  else if(ui->pushButton_19->text() == "w") ui->pushButton_19->setText("W");
  else if(ui->pushButton_19->text() == "W") ui->pushButton_19->setText("*");
}
void MainWindow::on_pushButton_20_clicked(){
  if(ui->pushButton_20->text() == "0") ui->pushButton_20->setText("*");
  else if(ui->pushButton_20->text() == "*") ui->pushButton_20->setText("b");
  else if(ui->pushButton_20->text() == "b") ui->pushButton_20->setText("B");
  else if(ui->pushButton_20->text() == "B") ui->pushButton_20->setText("w");
  else if(ui->pushButton_20->text() == "w") ui->pushButton_20->setText("W");
  else if(ui->pushButton_20->text() == "W") ui->pushButton_20->setText("*");
}
void MainWindow::on_pushButton_21_clicked(){
  if(ui->pushButton_21->text() == "0") ui->pushButton_21->setText("*");
  else if(ui->pushButton_21->text() == "*") ui->pushButton_21->setText("b");
  else if(ui->pushButton_21->text() == "b") ui->pushButton_21->setText("B");
  else if(ui->pushButton_21->text() == "B") ui->pushButton_21->setText("w");
  else if(ui->pushButton_21->text() == "w") ui->pushButton_21->setText("W");
  else if(ui->pushButton_21->text() == "W") ui->pushButton_21->setText("*");
}
void MainWindow::on_pushButton_22_clicked(){
  if(ui->pushButton_22->text() == "0") ui->pushButton_22->setText("*");
  else if(ui->pushButton_22->text() == "*") ui->pushButton_22->setText("b");
  else if(ui->pushButton_22->text() == "b") ui->pushButton_22->setText("B");
  else if(ui->pushButton_22->text() == "B") ui->pushButton_22->setText("w");
  else if(ui->pushButton_22->text() == "w") ui->pushButton_22->setText("W");
  else if(ui->pushButton_22->text() == "W") ui->pushButton_22->setText("*");
}
void MainWindow::on_pushButton_23_clicked(){
  if(ui->pushButton_23->text() == "0") ui->pushButton_23->setText("*");
  else if(ui->pushButton_23->text() == "*") ui->pushButton_23->setText("b");
  else if(ui->pushButton_23->text() == "b") ui->pushButton_23->setText("B");
  else if(ui->pushButton_23->text() == "B") ui->pushButton_23->setText("w");
  else if(ui->pushButton_23->text() == "w") ui->pushButton_23->setText("W");
  else if(ui->pushButton_23->text() == "W") ui->pushButton_23->setText("*");
}
void MainWindow::on_pushButton_24_clicked(){
  if(ui->pushButton_24->text() == "0") ui->pushButton_24->setText("*");
  else if(ui->pushButton_24->text() == "*") ui->pushButton_24->setText("b");
  else if(ui->pushButton_24->text() == "b") ui->pushButton_24->setText("B");
  else if(ui->pushButton_24->text() == "B") ui->pushButton_24->setText("w");
  else if(ui->pushButton_24->text() == "w") ui->pushButton_24->setText("W");
  else if(ui->pushButton_24->text() == "W") ui->pushButton_24->setText("*");
}
void MainWindow::on_pushButton_25_clicked(){
  if(ui->pushButton_25->text() == "0") ui->pushButton_25->setText("*");
  else if(ui->pushButton_25->text() == "*") ui->pushButton_25->setText("b");
  else if(ui->pushButton_25->text() == "b") ui->pushButton_25->setText("B");
  else if(ui->pushButton_25->text() == "B") ui->pushButton_25->setText("w");
  else if(ui->pushButton_25->text() == "w") ui->pushButton_25->setText("W");
  else if(ui->pushButton_25->text() == "W") ui->pushButton_25->setText("*");
}
void MainWindow::on_pushButton_26_clicked(){
  if(ui->pushButton_26->text() == "0") ui->pushButton_26->setText("*");
  else if(ui->pushButton_26->text() == "*") ui->pushButton_26->setText("b");
  else if(ui->pushButton_26->text() == "b") ui->pushButton_26->setText("B");
  else if(ui->pushButton_26->text() == "B") ui->pushButton_26->setText("w");
  else if(ui->pushButton_26->text() == "w") ui->pushButton_26->setText("W");
  else if(ui->pushButton_26->text() == "W") ui->pushButton_26->setText("*");
}
void MainWindow::on_pushButton_27_clicked(){
  if(ui->pushButton_27->text() == "0") ui->pushButton_27->setText("*");
  else if(ui->pushButton_27->text() == "*") ui->pushButton_27->setText("b");
  else if(ui->pushButton_27->text() == "b") ui->pushButton_27->setText("B");
  else if(ui->pushButton_27->text() == "B") ui->pushButton_27->setText("w");
  else if(ui->pushButton_27->text() == "w") ui->pushButton_27->setText("W");
  else if(ui->pushButton_27->text() == "W") ui->pushButton_27->setText("*");
}
void MainWindow::on_pushButton_28_clicked(){
  if(ui->pushButton_28->text() == "0") ui->pushButton_28->setText("*");
  else if(ui->pushButton_28->text() == "*") ui->pushButton_28->setText("b");
  else if(ui->pushButton_28->text() == "b") ui->pushButton_28->setText("B");
  else if(ui->pushButton_28->text() == "B") ui->pushButton_28->setText("w");
  else if(ui->pushButton_28->text() == "w") ui->pushButton_28->setText("W");
  else if(ui->pushButton_28->text() == "W") ui->pushButton_28->setText("*");
}
void MainWindow::on_pushButton_29_clicked(){
  if(ui->pushButton_29->text() == "0") ui->pushButton_29->setText("*");
  else if(ui->pushButton_29->text() == "*") ui->pushButton_29->setText("b");
  else if(ui->pushButton_29->text() == "b") ui->pushButton_29->setText("B");
  else if(ui->pushButton_29->text() == "B") ui->pushButton_29->setText("w");
  else if(ui->pushButton_29->text() == "w") ui->pushButton_29->setText("W");
  else if(ui->pushButton_29->text() == "W") ui->pushButton_29->setText("*");
}
void MainWindow::on_pushButton_30_clicked(){
  if(ui->pushButton_30->text() == "0") ui->pushButton_30->setText("*");
  else if(ui->pushButton_30->text() == "*") ui->pushButton_30->setText("b");
  else if(ui->pushButton_30->text() == "b") ui->pushButton_30->setText("B");
  else if(ui->pushButton_30->text() == "B") ui->pushButton_30->setText("w");
  else if(ui->pushButton_30->text() == "w") ui->pushButton_30->setText("W");
  else if(ui->pushButton_30->text() == "W") ui->pushButton_30->setText("*");
}
void MainWindow::on_pushButton_31_clicked(){
  if(ui->pushButton_31->text() == "0") ui->pushButton_31->setText("*");
  else if(ui->pushButton_31->text() == "*") ui->pushButton_31->setText("b");
  else if(ui->pushButton_31->text() == "b") ui->pushButton_31->setText("B");
  else if(ui->pushButton_31->text() == "B") ui->pushButton_31->setText("w");
  else if(ui->pushButton_31->text() == "w") ui->pushButton_31->setText("W");
  else if(ui->pushButton_31->text() == "W") ui->pushButton_31->setText("*");
}
void MainWindow::on_pushButton_32_clicked(){
  if(ui->pushButton_32->text() == "0") ui->pushButton_32->setText("*");
  else if(ui->pushButton_32->text() == "*") ui->pushButton_32->setText("b");
  else if(ui->pushButton_32->text() == "b") ui->pushButton_32->setText("B");
  else if(ui->pushButton_32->text() == "B") ui->pushButton_32->setText("w");
  else if(ui->pushButton_32->text() == "w") ui->pushButton_32->setText("W");
  else if(ui->pushButton_32->text() == "W") ui->pushButton_32->setText("*");
}
void MainWindow::on_pushButton_33_clicked(){
  if(ui->pushButton_33->text() == "0") ui->pushButton_33->setText("*");
  else if(ui->pushButton_33->text() == "*") ui->pushButton_33->setText("b");
  else if(ui->pushButton_33->text() == "b") ui->pushButton_33->setText("B");
  else if(ui->pushButton_33->text() == "B") ui->pushButton_33->setText("w");
  else if(ui->pushButton_33->text() == "w") ui->pushButton_33->setText("W");
  else if(ui->pushButton_33->text() == "W") ui->pushButton_33->setText("*");
}
void MainWindow::on_pushButton_34_clicked(){
  if(ui->pushButton_34->text() == "0") ui->pushButton_34->setText("*");
  else if(ui->pushButton_34->text() == "*") ui->pushButton_34->setText("b");
  else if(ui->pushButton_34->text() == "b") ui->pushButton_34->setText("B");
  else if(ui->pushButton_34->text() == "B") ui->pushButton_34->setText("w");
  else if(ui->pushButton_34->text() == "w") ui->pushButton_34->setText("W");
  else if(ui->pushButton_34->text() == "W") ui->pushButton_34->setText("*");
}
void MainWindow::on_pushButton_35_clicked(){
  if(ui->pushButton_35->text() == "0") ui->pushButton_35->setText("*");
  else if(ui->pushButton_35->text() == "*") ui->pushButton_35->setText("b");
  else if(ui->pushButton_35->text() == "b") ui->pushButton_35->setText("B");
  else if(ui->pushButton_35->text() == "B") ui->pushButton_35->setText("w");
  else if(ui->pushButton_35->text() == "w") ui->pushButton_35->setText("W");
  else if(ui->pushButton_35->text() == "W") ui->pushButton_35->setText("*");
}
void MainWindow::on_pushButton_36_clicked(){
  if(ui->pushButton_36->text() == "0") ui->pushButton_36->setText("*");
  else if(ui->pushButton_36->text() == "*") ui->pushButton_36->setText("b");
  else if(ui->pushButton_36->text() == "b") ui->pushButton_36->setText("B");
  else if(ui->pushButton_36->text() == "B") ui->pushButton_36->setText("w");
  else if(ui->pushButton_36->text() == "w") ui->pushButton_36->setText("W");
  else if(ui->pushButton_36->text() == "W") ui->pushButton_36->setText("*");
}
void MainWindow::on_pushButton_37_clicked(){
  if(ui->pushButton_37->text() == "0") ui->pushButton_37->setText("*");
  else if(ui->pushButton_37->text() == "*") ui->pushButton_37->setText("b");
  else if(ui->pushButton_37->text() == "b") ui->pushButton_37->setText("B");
  else if(ui->pushButton_37->text() == "B") ui->pushButton_37->setText("w");
  else if(ui->pushButton_37->text() == "w") ui->pushButton_37->setText("W");
  else if(ui->pushButton_37->text() == "W") ui->pushButton_37->setText("*");
}
void MainWindow::on_pushButton_38_clicked(){
  if(ui->pushButton_38->text() == "0") ui->pushButton_38->setText("*");
  else if(ui->pushButton_38->text() == "*") ui->pushButton_38->setText("b");
  else if(ui->pushButton_38->text() == "b") ui->pushButton_38->setText("B");
  else if(ui->pushButton_38->text() == "B") ui->pushButton_38->setText("w");
  else if(ui->pushButton_38->text() == "w") ui->pushButton_38->setText("W");
  else if(ui->pushButton_38->text() == "W") ui->pushButton_38->setText("*");
}
void MainWindow::on_pushButton_39_clicked(){
  if(ui->pushButton_39->text() == "0") ui->pushButton_39->setText("*");
  else if(ui->pushButton_39->text() == "*") ui->pushButton_39->setText("b");
  else if(ui->pushButton_39->text() == "b") ui->pushButton_39->setText("B");
  else if(ui->pushButton_39->text() == "B") ui->pushButton_39->setText("w");
  else if(ui->pushButton_39->text() == "w") ui->pushButton_39->setText("W");
  else if(ui->pushButton_39->text() == "W") ui->pushButton_39->setText("*");
}
void MainWindow::on_pushButton_40_clicked(){
  if(ui->pushButton_40->text() == "0") ui->pushButton_40->setText("*");
  else if(ui->pushButton_40->text() == "*") ui->pushButton_40->setText("b");
  else if(ui->pushButton_40->text() == "b") ui->pushButton_40->setText("B");
  else if(ui->pushButton_40->text() == "B") ui->pushButton_40->setText("w");
  else if(ui->pushButton_40->text() == "w") ui->pushButton_40->setText("W");
  else if(ui->pushButton_40->text() == "W") ui->pushButton_40->setText("*");
}
void MainWindow::on_pushButton_41_clicked(){
  if(ui->pushButton_41->text() == "0") ui->pushButton_41->setText("*");
  else if(ui->pushButton_41->text() == "*") ui->pushButton_41->setText("b");
  else if(ui->pushButton_41->text() == "b") ui->pushButton_41->setText("B");
  else if(ui->pushButton_41->text() == "B") ui->pushButton_41->setText("w");
  else if(ui->pushButton_41->text() == "w") ui->pushButton_41->setText("W");
  else if(ui->pushButton_41->text() == "W") ui->pushButton_41->setText("*");
}
void MainWindow::on_pushButton_42_clicked(){
  if(ui->pushButton_42->text() == "0") ui->pushButton_42->setText("*");
  else if(ui->pushButton_42->text() == "*") ui->pushButton_42->setText("b");
  else if(ui->pushButton_42->text() == "b") ui->pushButton_42->setText("B");
  else if(ui->pushButton_42->text() == "B") ui->pushButton_42->setText("w");
  else if(ui->pushButton_42->text() == "w") ui->pushButton_42->setText("W");
  else if(ui->pushButton_42->text() == "W") ui->pushButton_42->setText("*");
}
void MainWindow::on_pushButton_43_clicked(){
  if(ui->pushButton_43->text() == "0") ui->pushButton_43->setText("*");
  else if(ui->pushButton_43->text() == "*") ui->pushButton_43->setText("b");
  else if(ui->pushButton_43->text() == "b") ui->pushButton_43->setText("B");
  else if(ui->pushButton_43->text() == "B") ui->pushButton_43->setText("w");
  else if(ui->pushButton_43->text() == "w") ui->pushButton_43->setText("W");
  else if(ui->pushButton_43->text() == "W") ui->pushButton_43->setText("*");
}
void MainWindow::on_pushButton_44_clicked(){
  if(ui->pushButton_44->text() == "0") ui->pushButton_44->setText("*");
  else if(ui->pushButton_44->text() == "*") ui->pushButton_44->setText("b");
  else if(ui->pushButton_44->text() == "b") ui->pushButton_44->setText("B");
  else if(ui->pushButton_44->text() == "B") ui->pushButton_44->setText("w");
  else if(ui->pushButton_44->text() == "w") ui->pushButton_44->setText("W");
  else if(ui->pushButton_44->text() == "W") ui->pushButton_44->setText("*");
}
void MainWindow::on_pushButton_45_clicked(){
  if(ui->pushButton_45->text() == "0") ui->pushButton_45->setText("*");
  else if(ui->pushButton_45->text() == "*") ui->pushButton_45->setText("b");
  else if(ui->pushButton_45->text() == "b") ui->pushButton_45->setText("B");
  else if(ui->pushButton_45->text() == "B") ui->pushButton_45->setText("w");
  else if(ui->pushButton_45->text() == "w") ui->pushButton_45->setText("W");
  else if(ui->pushButton_45->text() == "W") ui->pushButton_45->setText("*");
}
void MainWindow::on_pushButton_46_clicked(){
  if(ui->pushButton_46->text() == "0") ui->pushButton_46->setText("*");
  else if(ui->pushButton_46->text() == "*") ui->pushButton_46->setText("b");
  else if(ui->pushButton_46->text() == "b") ui->pushButton_46->setText("B");
  else if(ui->pushButton_46->text() == "B") ui->pushButton_46->setText("w");
  else if(ui->pushButton_46->text() == "w") ui->pushButton_46->setText("W");
  else if(ui->pushButton_46->text() == "W") ui->pushButton_46->setText("*");
}
void MainWindow::on_pushButton_47_clicked(){
  if(ui->pushButton_47->text() == "0") ui->pushButton_47->setText("*");
  else if(ui->pushButton_47->text() == "*") ui->pushButton_47->setText("b");
  else if(ui->pushButton_47->text() == "b") ui->pushButton_47->setText("B");
  else if(ui->pushButton_47->text() == "B") ui->pushButton_47->setText("w");
  else if(ui->pushButton_47->text() == "w") ui->pushButton_47->setText("W");
  else if(ui->pushButton_47->text() == "W") ui->pushButton_47->setText("*");
}
void MainWindow::on_pushButton_48_clicked(){
  if(ui->pushButton_48->text() == "0") ui->pushButton_48->setText("*");
  else if(ui->pushButton_48->text() == "*") ui->pushButton_48->setText("b");
  else if(ui->pushButton_48->text() == "b") ui->pushButton_48->setText("B");
  else if(ui->pushButton_48->text() == "B") ui->pushButton_48->setText("w");
  else if(ui->pushButton_48->text() == "w") ui->pushButton_48->setText("W");
  else if(ui->pushButton_48->text() == "W") ui->pushButton_48->setText("*");
}
void MainWindow::on_pushButton_49_clicked(){
  if(ui->pushButton_49->text() == "0") ui->pushButton_49->setText("*");
  else if(ui->pushButton_49->text() == "*") ui->pushButton_49->setText("b");
  else if(ui->pushButton_49->text() == "b") ui->pushButton_49->setText("B");
  else if(ui->pushButton_49->text() == "B") ui->pushButton_49->setText("w");
  else if(ui->pushButton_49->text() == "w") ui->pushButton_49->setText("W");
  else if(ui->pushButton_49->text() == "W") ui->pushButton_49->setText("*");
}
void MainWindow::on_pushButton_50_clicked(){
  if(ui->pushButton_50->text() == "0") ui->pushButton_50->setText("*");
  else if(ui->pushButton_50->text() == "*") ui->pushButton_50->setText("b");
  else if(ui->pushButton_50->text() == "b") ui->pushButton_50->setText("B");
  else if(ui->pushButton_50->text() == "B") ui->pushButton_50->setText("w");
  else if(ui->pushButton_50->text() == "w") ui->pushButton_50->setText("W");
  else if(ui->pushButton_50->text() == "W") ui->pushButton_50->setText("*");
}
void MainWindow::on_pushButton_51_clicked(){
  if(ui->pushButton_51->text() == "0") ui->pushButton_51->setText("*");
  else if(ui->pushButton_51->text() == "*") ui->pushButton_51->setText("b");
  else if(ui->pushButton_51->text() == "b") ui->pushButton_51->setText("B");
  else if(ui->pushButton_51->text() == "B") ui->pushButton_51->setText("w");
  else if(ui->pushButton_51->text() == "w") ui->pushButton_51->setText("W");
  else if(ui->pushButton_51->text() == "W") ui->pushButton_51->setText("*");
}
void MainWindow::on_pushButton_52_clicked(){
  if(ui->pushButton_52->text() == "0") ui->pushButton_52->setText("*");
  else if(ui->pushButton_52->text() == "*") ui->pushButton_52->setText("b");
  else if(ui->pushButton_52->text() == "b") ui->pushButton_52->setText("B");
  else if(ui->pushButton_52->text() == "B") ui->pushButton_52->setText("w");
  else if(ui->pushButton_52->text() == "w") ui->pushButton_52->setText("W");
  else if(ui->pushButton_52->text() == "W") ui->pushButton_52->setText("*");
}
void MainWindow::on_pushButton_53_clicked(){
  if(ui->pushButton_53->text() == "0") ui->pushButton_53->setText("*");
  else if(ui->pushButton_53->text() == "*") ui->pushButton_53->setText("b");
  else if(ui->pushButton_53->text() == "b") ui->pushButton_53->setText("B");
  else if(ui->pushButton_53->text() == "B") ui->pushButton_53->setText("w");
  else if(ui->pushButton_53->text() == "w") ui->pushButton_53->setText("W");
  else if(ui->pushButton_53->text() == "W") ui->pushButton_53->setText("*");
}
void MainWindow::on_pushButton_54_clicked(){
  if(ui->pushButton_54->text() == "0") ui->pushButton_54->setText("*");
  else if(ui->pushButton_54->text() == "*") ui->pushButton_54->setText("b");
  else if(ui->pushButton_54->text() == "b") ui->pushButton_54->setText("B");
  else if(ui->pushButton_54->text() == "B") ui->pushButton_54->setText("w");
  else if(ui->pushButton_54->text() == "w") ui->pushButton_54->setText("W");
  else if(ui->pushButton_54->text() == "W") ui->pushButton_54->setText("*");
}
void MainWindow::on_pushButton_55_clicked(){
  if(ui->pushButton_55->text() == "0") ui->pushButton_55->setText("*");
  else if(ui->pushButton_55->text() == "*") ui->pushButton_55->setText("b");
  else if(ui->pushButton_55->text() == "b") ui->pushButton_55->setText("B");
  else if(ui->pushButton_55->text() == "B") ui->pushButton_55->setText("w");
  else if(ui->pushButton_55->text() == "w") ui->pushButton_55->setText("W");
  else if(ui->pushButton_55->text() == "W") ui->pushButton_55->setText("*");
}
void MainWindow::on_pushButton_56_clicked(){
  if(ui->pushButton_56->text() == "0") ui->pushButton_56->setText("*");
  else if(ui->pushButton_56->text() == "*") ui->pushButton_56->setText("b");
  else if(ui->pushButton_56->text() == "b") ui->pushButton_56->setText("B");
  else if(ui->pushButton_56->text() == "B") ui->pushButton_56->setText("w");
  else if(ui->pushButton_56->text() == "w") ui->pushButton_56->setText("W");
  else if(ui->pushButton_56->text() == "W") ui->pushButton_56->setText("*");
}
void MainWindow::on_pushButton_57_clicked(){
  if(ui->pushButton_57->text() == "0") ui->pushButton_57->setText("*");
  else if(ui->pushButton_57->text() == "*") ui->pushButton_57->setText("b");
  else if(ui->pushButton_57->text() == "b") ui->pushButton_57->setText("B");
  else if(ui->pushButton_57->text() == "B") ui->pushButton_57->setText("w");
  else if(ui->pushButton_57->text() == "w") ui->pushButton_57->setText("W");
  else if(ui->pushButton_57->text() == "W") ui->pushButton_57->setText("*");
}
void MainWindow::on_pushButton_58_clicked(){
  if(ui->pushButton_58->text() == "0") ui->pushButton_58->setText("*");
  else if(ui->pushButton_58->text() == "*") ui->pushButton_58->setText("b");
  else if(ui->pushButton_58->text() == "b") ui->pushButton_58->setText("B");
  else if(ui->pushButton_58->text() == "B") ui->pushButton_58->setText("w");
  else if(ui->pushButton_58->text() == "w") ui->pushButton_58->setText("W");
  else if(ui->pushButton_58->text() == "W") ui->pushButton_58->setText("*");
}
void MainWindow::on_pushButton_59_clicked(){
  if(ui->pushButton_59->text() == "0") ui->pushButton_59->setText("*");
  else if(ui->pushButton_59->text() == "*") ui->pushButton_59->setText("b");
  else if(ui->pushButton_59->text() == "b") ui->pushButton_59->setText("B");
  else if(ui->pushButton_59->text() == "B") ui->pushButton_59->setText("w");
  else if(ui->pushButton_59->text() == "w") ui->pushButton_59->setText("W");
  else if(ui->pushButton_59->text() == "W") ui->pushButton_59->setText("*");
}
void MainWindow::on_pushButton_60_clicked(){
  if(ui->pushButton_60->text() == "0") ui->pushButton_60->setText("*");
  else if(ui->pushButton_60->text() == "*") ui->pushButton_60->setText("b");
  else if(ui->pushButton_60->text() == "b") ui->pushButton_60->setText("B");
  else if(ui->pushButton_60->text() == "B") ui->pushButton_60->setText("w");
  else if(ui->pushButton_60->text() == "w") ui->pushButton_60->setText("W");
  else if(ui->pushButton_60->text() == "W") ui->pushButton_60->setText("*");
}
void MainWindow::on_pushButton_61_clicked(){
  if(ui->pushButton_61->text() == "0") ui->pushButton_61->setText("*");
  else if(ui->pushButton_61->text() == "*") ui->pushButton_61->setText("b");
  else if(ui->pushButton_61->text() == "b") ui->pushButton_61->setText("B");
  else if(ui->pushButton_61->text() == "B") ui->pushButton_61->setText("w");
  else if(ui->pushButton_61->text() == "w") ui->pushButton_61->setText("W");
  else if(ui->pushButton_61->text() == "W") ui->pushButton_61->setText("*");
}
void MainWindow::on_pushButton_62_clicked(){
  if(ui->pushButton_62->text() == "0") ui->pushButton_62->setText("*");
  else if(ui->pushButton_62->text() == "*") ui->pushButton_62->setText("b");
  else if(ui->pushButton_62->text() == "b") ui->pushButton_62->setText("B");
  else if(ui->pushButton_62->text() == "B") ui->pushButton_62->setText("w");
  else if(ui->pushButton_62->text() == "w") ui->pushButton_62->setText("W");
  else if(ui->pushButton_62->text() == "W") ui->pushButton_62->setText("*");
}
void MainWindow::on_pushButton_63_clicked(){
  if(ui->pushButton_63->text() == "0") ui->pushButton_63->setText("*");
  else if(ui->pushButton_63->text() == "*") ui->pushButton_63->setText("b");
  else if(ui->pushButton_63->text() == "b") ui->pushButton_63->setText("B");
  else if(ui->pushButton_63->text() == "B") ui->pushButton_63->setText("w");
  else if(ui->pushButton_63->text() == "w") ui->pushButton_63->setText("W");
  else if(ui->pushButton_63->text() == "W") ui->pushButton_63->setText("*");
}
void MainWindow::on_pushButton_64_clicked(){
  if(ui->pushButton_64->text() == "0") ui->pushButton_64->setText("*");
  else if(ui->pushButton_64->text() == "*") ui->pushButton_64->setText("b");
  else if(ui->pushButton_64->text() == "b") ui->pushButton_64->setText("B");
  else if(ui->pushButton_64->text() == "B") ui->pushButton_64->setText("w");
  else if(ui->pushButton_64->text() == "w") ui->pushButton_64->setText("W");
  else if(ui->pushButton_64->text() == "W") ui->pushButton_64->setText("*");
}


