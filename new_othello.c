#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10
#define EMPTY 0
#define WALL 1
#define WHITE 2
#define BLACK 3
#define GUIDE 4
#define PLUS 1
#define MINUS -1
#define ZERO 0

void disp_masAI(int mass[SIZE][SIZE]);
int result_AI(int mass[SIZE][SIZE]);
void turn_change(int *ar_turn);
int othelloAI(void);
int othello_AI_check1(int *ar_turn, int mass[100][SIZE][SIZE]);
int check_AI(int *ar_turn, int mass[SIZE][SIZE], int y, int x);
int put2_check_AI(int mass[SIZE][SIZE], int y, int x, int dy, int dx);
int E_cnt_AI(int mass[SIZE][SIZE]);
void calculationai(int mass[SIZE][SIZE]);
void calculation_AI(int mass[SIZE][SIZE], int dy, int dx);
void reverseai(int mass[SIZE][SIZE], int x[], int y[], int c);
int W_cnt_AI(int mass[SIZE][SIZE]);
int B_cnt_AI(int mass[SIZE][SIZE]);
int othello_AI_check3(int *ar_turn, int mass[20][SIZE][SIZE], int mkcount[], int okcount[]);

int mas_evaluation(int ar_i);
int kaihoudo(int x, int y, int mass[SIZE][SIZE]);
void kaihoudo_check1(int x, int y, int dy, int dx, int ar_kaihoudo_mas[][SIZE]);
void kaihoudo_check2(int ar_kaihoudo_mas[][SIZE], int y, int x);
int min_return(int ar_i, int ar_array[]);
int max_return(int ar_i, int ar_array[]);

void disp_mas(void); //masの表示
int E_cnt(void);     //EMPTYの数のカウント
int W_cnt(void);     //WHITEの数のカウント
int B_cnt(void);     //BLACKの数のカウント
void copy1(void);    //みんなのAIに渡すためのコピー版mas_sの作成~GUIDE付きコピー（delete())前
void copy2(void);    //GUIDE無しコピー（delete())後
void delete (void);  //mas内のGUIDEの消去
int insort(void);    //masに入力
void put1(void);     //GUIDEの置ける場所の確認と配置
int put1_check(int y, int x, int dy, int dx);
int put2(void); //GUIDEの置ける場所の確認のみ
int put2_check(int y, int x, int dy, int dx);
int check(void); //正しい位置に置けるか否か
int num_check(int dy, int dx);
int calculation(void); //裏返しのデータをrev関数に送る
int calculation_check(int dy, int dx);
void reverse(int x[], int y[], int c); //実際に裏返す
void result(int j);                    //終了結果の表示

int mas[SIZE][SIZE] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 2, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 3, 2, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};
//コピー用２つ目GUIDE無し
int c_mas2[SIZE][SIZE] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int turn = 0;
int my_color = BLACK, opponent_color = WHITE;
int gl_x, gl_y;
int gl__x[30] = {0}, gl__y[30] = {0};
int gl_count = 0; //for put関数
int gl_delete_count;
int gl_j = 0;

int result_AI(int mass[SIZE][SIZE])
{
    int my_color_count = 0, opponent_color_count = 0;
    
    if (turn % 2 == 0)
    { //黒の時
        my_color = BLACK;
        opponent_color = WHITE;
    }
    else
    {
        my_color = WHITE;
        opponent_color = BLACK;
    }
    
    for (int counta = 1; counta <= 8; counta++)
    {
        for (int countb = 1; countb <= 8; countb++)
        {
            if (mass[counta][countb] == my_color)
            {
                my_color_count++;
            }
            else if (mass[counta][countb] == opponent_color)
            {
                opponent_color_count++;
            }
        }
    }
    if (my_color_count > opponent_color_count)
        return 1; //勝利
    else
        return 0; //引き分け・敗北
}

void turn_change(int *ar_turn)
{
    
    if (*ar_turn % 2 == 0)
    {
        my_color = WHITE;
        opponent_color = BLACK;
    }
    else
    {
        my_color = BLACK;
        opponent_color = WHITE;
    }
}

int othelloAI(void)
{
    int *t;
    int x = 0;
    t = &x;
    int ans;
    int rest_mass=20;//深さ優先探索アルゴリズムに切り替える時の残りマス
    
    if (E_cnt() <= rest_mass)
    {
        int mass[100][SIZE][SIZE];
        memcpy(mass[*t], c_mas2, sizeof(mass[*t]));
        ans = othello_AI_check1(t, mass);
    }else
    {
        for (int i = 0; i < gl_delete_count; i++)
        {
            if (mas_evaluation(i) == 120)
                return 10 * gl__x[i] + gl__y[i];
        }
        int masp[20][SIZE][SIZE];
        memcpy(masp[*t], c_mas2, sizeof(masp[*t]));
        //int pcount[20] = {0};
        int mkcount[20] = {0}, okcount[20] = {0};
        ans = othello_AI_check3(t, masp, mkcount, okcount);
        int plus_count[20] = {0};
        for (int i = 0; i < ans; i++)
        {
            plus_count[i] = mkcount[i] + okcount[i];
            //printf("%d:%d + %d==%d\n", i, mkcount[i], okcount[i], plus_count[i]);
        }
        int k = 0;
        int ult[20] = {0};
        int count = 0;
        int l;
        int skip_c = 0;
        while (1)
        {
            count = 0;
            
            k = min_return(ans, plus_count);
            l = plus_count[k];
            
            for (int i = 0; i < ans; i++)
            {
                if (l == plus_count[i])
                {
                    if (mas_evaluation(i) == -40)
                    {
                        plus_count[i]++;
                        continue;
                    }
                    ult[i] = mas_evaluation(i);
                    count++;
                }
            }
            
            int aaa;
            aaa = max_return(ans, ult);
            if (ult[aaa] != -40) //
            {
                ans = 10 * gl__x[aaa] + gl__y[aaa];
                break;
            }
            else
            {
                if (skip_c == 10)
                {
                    ans = 10 * gl__x[aaa] + gl__y[aaa];
                    break;
                }
                skip_c++;
            }
        }
    }
    printf("＜計算結果＞\n");
    printf("コンピュータは %d に打ちました。\n\n", ans);
    return ans;
}
int othello_AI_check1(int *ar_turn, int mass[100][SIZE][SIZE])
{
    static int counta[100];
    static int countb[100];
    static int eva_count[100];
    static int skip_count = 0;
    
    //_____________________________________________________________マスが全部埋まった時
    if (E_cnt_AI(mass[*ar_turn]) == 0 || W_cnt_AI(mass[*ar_turn]) == 0 || B_cnt_AI(mass[*ar_turn]) == 0)
    {
        skip_count = 0; //連続してパスはなかったのでリセットする
        if (result_AI(mass[*ar_turn]) == 1)
        { //
            //printf("勝利\n");
            return 1;
        }
        else
        { //
            //printf("敗北\n");
            return ZERO;
        }
    }
    //_____________________________________________________________処理終了
    
    eva_count[*ar_turn] = 0; //初期化する。他の変数はfor文などで初期化されている
    
    turn_change(ar_turn);
    
    if (*ar_turn % 2 == 0)
    {
        for (counta[*ar_turn] = 1; counta[*ar_turn] <= 8; counta[*ar_turn]++)
        {
            for (countb[*ar_turn] = 1; countb[*ar_turn] <= 8; countb[*ar_turn]++)
            {
                
                if (check_AI(ar_turn, mass[*ar_turn], counta[*ar_turn], countb[*ar_turn]) == 1)
                {
                    
                    skip_count = 0;
                    memcpy(mass[*ar_turn + 1], mass[*ar_turn], sizeof(mass[*ar_turn]));
                    mass[*ar_turn + 1][counta[*ar_turn]][countb[*ar_turn]] = my_color;
                    gl_y = counta[*ar_turn];
                    gl_x = countb[*ar_turn];
                    calculationai(mass[*ar_turn + 1]);
                    
                    // printf("%d ", *ar_turn);
                    // //disp_masAI(mass[*ar_turn]);
                    (*ar_turn)++;
                    if (othello_AI_check1(ar_turn, mass) != 0) //自分の時、返り値が1の時それ以降は調べる必要がなくなる。また相手の時も同様に返り値が0の時それ以降は調べる必要がなくなる。
                    {
                        (*ar_turn)--;
                        
                        return 10 * countb[*ar_turn] + counta[*ar_turn];
                    }
                    
                    (*ar_turn)--;
                    
                    turn_change(ar_turn);
                    eva_count[*ar_turn]++;
                }
            }
        }
        
        //___________________________________________________共通部分始め
        
        if (eva_count[*ar_turn] == 0) //置く所がなかった(パスの時)
        {
            if (skip_count == 1) //両方打てなくなった時(スキップが二回続いた時)
            {
                skip_count = 0;
                if (result_AI(mass[*ar_turn]) == 1)
                {
                    return 1;
                }
                else
                {
                    return ZERO;
                }
            }
            else
            {
                skip_count = 0; //連続してパスはなかったのでリセットする
                skip_count++;
                memcpy(mass[*ar_turn + 1], mass[*ar_turn], sizeof(mass[*ar_turn]));
                (*ar_turn)++;
                int k;
                k = othello_AI_check1(ar_turn, mass);
                (*ar_turn)--;
                return k;
            }
        }
        //___________________________________________________共通部分終わり
        
        //______________________________________________異なるところはじめ
        else //置くところはあったが返り値が全て0であった場合
        {
            skip_count = 0; //連続してパスはなかったのでリセットする
            return ZERO;
        }
        //______________________________________________異なるところ終わり
    }
    
    else
    {
        for (counta[*ar_turn] = 1; counta[*ar_turn] <= 8; counta[*ar_turn]++)
        {
            for (countb[*ar_turn] = 1; countb[*ar_turn] <= 8; countb[*ar_turn]++)
            {
                if (check_AI(ar_turn, mass[*ar_turn], counta[*ar_turn], countb[*ar_turn]) == 1)
                {
                    
                    skip_count = 0;
                    memcpy(mass[*ar_turn + 1], mass[*ar_turn], sizeof(mass[*ar_turn]));
                    mass[*ar_turn + 1][counta[*ar_turn]][countb[*ar_turn]] = my_color;
                    gl_y = counta[*ar_turn];
                    gl_x = countb[*ar_turn];
                    calculationai(mass[*ar_turn + 1]);
                    
                    // printf("%d ", *ar_turn);
                    // //disp_masAI(mass[*ar_turn]);
                    
                    (*ar_turn)++;
                    
                    if (othello_AI_check1(ar_turn, mass) == ZERO)
                    {
                        (*ar_turn)--;
                        return ZERO;
                    }
                    (*ar_turn)--;
                    turn_change(ar_turn);
                    eva_count[*ar_turn]++;
                }
            }
        }
        
        if (eva_count[*ar_turn] == 0) //置く所がなかった(パスの時)
        {
            
            if (skip_count == 1)
            { //両方打てなくなった時(スキップが二回続いた時)
                
                skip_count = 0;
                if (result_AI(mass[*ar_turn]) == 1)
                {
                    //     printf("勝利");
                    return 1;
                }
                else
                {
                    //     printf("敗北");
                    return ZERO;
                }
            }
            else
            {
                skip_count = 0; //連続してパスはなかったのでリセットする
                skip_count++;
                memcpy(mass[*ar_turn + 1], mass[*ar_turn], sizeof(mass[*ar_turn]));
                
                (*ar_turn)++;
                int k;
                k = othello_AI_check1(ar_turn, mass);
                (*ar_turn)--;
                
                return k;
            }
        }
        else
        {                 //置くところはあったが返り値が全て1であった場合
            skip_count = 0; //連続してパスはなかったのでリセットする
            
            return 1;
        }
    }
    return 0;
}

int othello_AI_check3(int *ar_turn, int mass[20][SIZE][SIZE], int mkcount[], int okcount[])
{
    static int counta[20];
    static int countb[20];
    static int eva_count[20];
    
    eva_count[*ar_turn] = 0; //初期化する。他の変数はfor文などで初期化されている
    
    turn_change(ar_turn);
    
    for (counta[*ar_turn] = 1; counta[*ar_turn] <= 8; counta[*ar_turn]++)
    {
        for (countb[*ar_turn] = 1; countb[*ar_turn] <= 8; countb[*ar_turn]++)
        {
            if (check_AI(ar_turn, mass[*ar_turn], counta[*ar_turn], countb[*ar_turn]) == 1)
            {
                mkcount[eva_count[0]] = kaihoudo(countb[*ar_turn], counta[*ar_turn], mass[*ar_turn]);
                memcpy(mass[*ar_turn + 1], mass[*ar_turn], sizeof(mass[*ar_turn]));
                mass[*ar_turn + 1][counta[*ar_turn]][countb[*ar_turn]] = my_color;
                gl_y = counta[*ar_turn];
                gl_x = countb[*ar_turn];
                calculationai(mass[*ar_turn + 1]);
                (*ar_turn)++;
                turn_change(ar_turn);
                for (int i = 1; i <= 8; i++)
                {
                    for (int j = 1; j <= 8; j++)
                    {
                        if (check_AI(ar_turn, mass[*ar_turn], i, j) == 1)
                        {
                            memcpy(mass[*ar_turn + 1], mass[*ar_turn], sizeof(mass[*ar_turn]));
                            mass[*ar_turn + 1][i][j] = my_color;
                            gl_y = i;
                            gl_x = j;
                            calculationai(mass[*ar_turn + 1]);
                            if (W_cnt_AI(mass[*ar_turn + 1]) == 0)
                            {
                                okcount[eva_count[0]] += 30;
                            }
                            if (kaihoudo(j, i, mass[*ar_turn]) <= 1)
                            {
                                okcount[eva_count[0]]++;
                            }
                        }
                    }
                }
                (*ar_turn)--;
                turn_change(ar_turn);
                
                eva_count[*ar_turn]++;
            }
        }
    }
    
    return eva_count[0];
}
int check_AI(int *ar_turn, int mass[SIZE][SIZE], int y, int x)
{
    if (mass[y][x] != EMPTY)
        return ZERO;
    if (put2_check_AI(mass, y, x, MINUS, MINUS) == 1)
        return 1;
    if (put2_check_AI(mass, y, x, MINUS, ZERO) == 1)
        return 1;
    if (put2_check_AI(mass, y, x, MINUS, PLUS) == 1)
        return 1;
    if (put2_check_AI(mass, y, x, ZERO, MINUS) == 1)
        return 1;
    if (put2_check_AI(mass, y, x, ZERO, PLUS) == 1)
        return 1;
    if (put2_check_AI(mass, y, x, PLUS, MINUS) == 1)
        return 1;
    if (put2_check_AI(mass, y, x, PLUS, ZERO) == 1)
        return 1;
    if (put2_check_AI(mass, y, x, PLUS, PLUS) == 1)
        return 1;
    
    return ZERO;
}
int put2_check_AI(int mass[SIZE][SIZE], int y, int x, int dy, int dx)
{
    
    int counta = 0;
    int fx = dx, fy = dy;
    
    while (1)
    {
        if (mass[y + fy][x + fx] == EMPTY || mass[y + fy][x + fx] == WALL || mass[y + fy][x + fx] == GUIDE)
        {
            counta = 0;
            break;
        }
        else if (mass[y + fy][x + fx] == my_color)
            break;
        
        counta++;
        fy += dy;
        fx += dx;
    }
    switch (counta)
    {
        case 0: //置く場所が１つもない
            return ZERO;
            break;
        default: //置く場所が少なくとも１つはある
            return 1;
            break;
    }
}

int E_cnt_AI(int mass[SIZE][SIZE])
{
    int empty = 0;
    int counta, countb;
    
    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            switch (mass[counta][countb])
            {
                case EMPTY:
                    return 1;
                    empty++;
                    break;
            }
        }
    }
    return empty;
}

void calculationai(int mass[SIZE][SIZE])
{
    calculation_AI(mass, MINUS, MINUS);
    calculation_AI(mass, MINUS, ZERO);
    calculation_AI(mass, MINUS, PLUS);
    calculation_AI(mass, ZERO, MINUS);
    calculation_AI(mass, ZERO, PLUS);
    calculation_AI(mass, PLUS, MINUS);
    calculation_AI(mass, PLUS, ZERO);
    calculation_AI(mass, PLUS, PLUS);
}

void calculation_AI(int mass[SIZE][SIZE], int dy, int dx)
{
    int counta = 0;
    int reverse_x[20], reverse_y[20];
    int fx = dx, fy = dy;
    
    while (1)
    {
        if (mass[gl_y + fy][gl_x + fx] == opponent_color)
        {
            reverse_x[counta] = gl_x + fx;
            reverse_y[counta] = gl_y + fy;
            
            counta++;
        }
        else
            break;
        
        fy += dy;
        fx += dx;
    }
    
    if (counta > 0 && mass[gl_y + fy][gl_x + fx] == my_color)
    {
        reverseai(mass, reverse_x, reverse_y, counta);
    }
}
void reverseai(int mass[SIZE][SIZE], int x[], int y[], int c)
{
    for (int t = 0; t < c; t++)
        mass[y[t]][x[t]] = my_color;
}
int W_cnt_AI(int mass[SIZE][SIZE])
{
    
    int white = 0;
    int counta, countb;
    
    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            switch (mass[counta][countb])
            {
                case WHITE:
                    white++;
                    break;
            }
            if (white == 1)
            {
                break;
            }
        }
        if (white == 1)
        {
            break;
        }
    }
    return white;
}

int B_cnt_AI(int mass[SIZE][SIZE])
{
    
    int black = 0;
    int counta, countb;
    
    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            switch (mass[counta][countb])
            {
                case BLACK:
                    black++;
                    break;
            }
            if (black == 1)
            {
                break;
            }
        }
        if (black == 1)
        {
            break;
        }
    }
    return black;
}

int mas_evaluation(int ar_i)
{
    int evaluation[SIZE][SIZE] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 120, -20, 20, 5, 5, 20, -20, 120, 0},
        {0, -20, -40, 2, 2, 2, 2, -40, -20, 0},
        {0, 20, 2, 15, 3, 3, 15, 2, 20, 0},
        {0, 5, 2, 3, 3, 3, 3, 2, 5, 0},
        {0, 5, 2, 3, 3, 3, 3, 2, 5, 0},
        {0, 20, 2, 15, 3, 3, 15, 2, 20, 0},
        {0, -20, -40, 2, 2, 2, 2, -40, -20, 0},
        {0, 120, -20, 20, 5, 5, 20, -20, 120, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    
    return evaluation[gl__y[ar_i]][gl__x[ar_i]];
}

int kaihoudo(int x, int y, int mass[SIZE][SIZE]) //開放度理論
{
    static int kaihoudo_mas[SIZE][SIZE];
    int kaihoudo_num = 0;
    int counta, countb;
    
    memcpy(kaihoudo_mas, mass, sizeof(kaihoudo_mas));
    
    kaihoudo_check1(x, y, MINUS, MINUS, kaihoudo_mas);
    kaihoudo_check1(x, y, MINUS, ZERO, kaihoudo_mas);
    kaihoudo_check1(x, y, MINUS, PLUS, kaihoudo_mas);
    kaihoudo_check1(x, y, ZERO, MINUS, kaihoudo_mas);
    kaihoudo_check1(x, y, ZERO, PLUS, kaihoudo_mas);
    kaihoudo_check1(x, y, PLUS, MINUS, kaihoudo_mas);
    kaihoudo_check1(x, y, PLUS, ZERO, kaihoudo_mas);
    kaihoudo_check1(x, y, PLUS, PLUS, kaihoudo_mas);
    
    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            if (kaihoudo_mas[counta][countb] < 0)
            {
                kaihoudo_num++;
            }
        }
    }
    
    //printf("開放度は%d\n", kaihoudo_num - 1);
    
    return kaihoudo_num - 1;
}
void kaihoudo_check1(int x, int y, int dy, int dx, int ar_kaihoudo_mas[][SIZE])
{
    int counta = 0;
    int kaihoudo_x[20], kaihoudo_y[20];
    int fx = dx, fy = dy;
    int i;
    
    while (1)
    {
        if (ar_kaihoudo_mas[y + fy][x + fx] == opponent_color)
        {
            kaihoudo_x[counta] = x + fx;
            kaihoudo_y[counta] = y + fy;
            
            counta++;
        }
        else
            break;
        
        fy += dy;
        fx += dx;
    }
    
    if (counta > 0 && ar_kaihoudo_mas[y + fy][x + fx] == my_color)
    {
        for (i = 0; i < counta; i++)
        {
            kaihoudo_check2(ar_kaihoudo_mas, kaihoudo_y[i], kaihoudo_x[i]);
            //printf("%d%d", kaihoudo_x[i], kaihoudo_y[i]);
        }
    }
}
void kaihoudo_check2(int ar_kaihoudo_mas[][SIZE], int y, int x)
{
    
    //printf("%d%d", x, y);
    int counta, countb;
    //置く位置に対しても-1しているので注意。
    for (counta = -1; counta <= 1; counta++)
    {
        for (countb = -1; countb <= 1; countb++)
        {
            if (ar_kaihoudo_mas[y + counta][x + countb] == 0)
            {
                ar_kaihoudo_mas[y + counta][x + countb]--;
            }
        }
    }
}

int min_return(int ar_i, int ar_array[])
{
    int a = ar_i - 1;
    int tentative_num;
    
    tentative_num = ar_array[ar_i - 1];
    for (int counta = 0; counta < ar_i - 1; counta++)
    {
        if (tentative_num > ar_array[counta])
        {
            tentative_num = ar_array[counta];
            a = counta;
        }
    }
    return a;
}
int max_return(int ar_i, int ar_array[])
{
    int a = ar_i - 1;
    int tentative_num;
    
    tentative_num = ar_array[ar_i - 1];
    for (int counta = 0; counta < ar_i - 1; counta++)
    {
        if (tentative_num < ar_array[counta])
        {
            tentative_num = ar_array[counta];
            a = counta;
        }
    }
    
    return a;
}

int main(void)
{
    printf("\x1b[40m"); /* 背景色を黒に */
    printf("＜オセロゲームの説明＞\n\n");
    printf("・打つことの出来る箇所には、 ");
    printf("\x1b[35m"); /* 前景色をマゼンタに */
    printf("※");
    printf("\x1b[39m"); /* 前景色をデフォルトに戻す */
    printf(" の印をつけています。\n\n");
    printf("・駒（コマ）を置く際の方法は、");
    printf("例えば、下図の左上の ");
    printf("\x1b[35m"); /* 前景色をマゼンタに */
    printf("※");
    printf("\x1b[39m"); /* 前景色をデフォルトに戻す */
    printf(" に打つときは、右（x）方向に 4 下（y）方向に 3 なので、43 と入力します。\n");
    printf(" つまり、x方向を10の位、y方向を1の位として合わせて入力してください。\n");
    printf("説明は以上です。\n\n");
    printf("\x1b[49m"); /* 背景色をデフォルトに戻す */
    
    //disp_mas();
    //slc();
    printf("あなたが黒（＝先攻）です\n");
    
    for (turn = 0;; turn++)
    {
        if (insort() == 0)
        {
            result(1);
            printf("終了しました.\n");
            break;
        }
        
        calculation();
        
        if (E_cnt() == 0) //全マスが埋まる（EMPTYがなくなる）
        {
            result(1);
            break;
        }
        else if (B_cnt() == 0) //黒マスが0
        {
            result(1);
            break;
        }
        else if (W_cnt() == 0) //白マスが0
        {
            result(1);
            break;
        }
    }
    
    return 0;
}

void disp_mas(void)
{
    
    int counta, countb;
    
    printf("   ");
    for (counta = 1; counta <= 8; counta++)
    {
        printf("%d ", counta);
    }
    
    printf("\n");
    
    for (counta = 0; counta < 10; counta++)
    {
        if (counta >= 1 && counta <= 8)
        {
            printf("%d", counta);
        }
        for (countb = 0; countb < 10; countb++)
        {
            switch (mas[counta][countb])
            {
                case WALL:
                    printf("  ");
                    break;
                case EMPTY:
                    printf("\x1b[42m"); /* 背景色を緑に */
                    //printf("\x1b[32m"); /* 前景色を緑に */
                    printf("□ ");
                    break;
                case WHITE:
                    printf("\x1b[42m"); /* 背景色を緑に */
                    printf("\x1b[37m"); /* 前景色を白に */
                    printf("● ");
                    break;
                case BLACK:
                    printf("\x1b[42m"); /* 背景色を緑に */
                    printf("\x1b[30m"); /* 前景色を黒に */
                    printf("● ");
                    break;
                case GUIDE:
                    printf("\x1b[42m"); /* 背景色を緑に */
                    printf("\x1b[35m"); /* 前景色をマゼンタに */
                    printf("※ ");
                    break;
            }
            printf("\x1b[39m"); /* 前景色をデフォルトに戻す */
            printf("\x1b[49m"); /* 背景色をデフォルトに戻す */
        }
        printf("\n");
    }
}

//マスが全て埋まる
int E_cnt(void)
{
    
    int empty = 0;
    int counta, countb;
    
    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            switch (mas[counta][countb])
            {
                case EMPTY:
                    empty++;
                    break;
            }
        }
    }
    return empty;
}
//白が全部無くなった時
int W_cnt(void)
{
    
    int white = 0;
    int counta, countb;
    
    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            switch (mas[counta][countb])
            {
                case WHITE:
                    white++;
                    break;
            }
            if (white == 1)
            {
                break;
            }
        }
        if (white == 1)
        {
            break;
        }
    }
    return white;
}
//黒が全部無くなった時
int B_cnt(void)
{
    
    int black = 0;
    int counta, countb;
    
    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            switch (mas[counta][countb])
            {
                case BLACK:
                    black++;
                    break;
            }
            if (black == 1)
            {
                break;
            }
        }
        if (black == 1)
        {
            break;
        }
    }
    return black;
}

void copy2(void)
{
    
    int counta, countb;
    
    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            c_mas2[counta][countb] = mas[counta][countb];
        }
    }
}

void delete (void)
{
    int t = 0;
    
    do
    {
        switch (mas[gl__y[t]][gl__x[t]])
        {
            case GUIDE:
                mas[gl__y[t]][gl__x[t]] = EMPTY;
                break;
        }
        
        t++;
        
    } while (t < gl_count);
    
    gl_delete_count = gl_count;
    
    gl_count = 0;
}

int insort(void)
{
    int tnum;
    int x, y;
    char ch;
    
    while (1)
    {
        if (gl_j == 2)
        {
            printf("お互いに打つことが出来ません. \n");
            return 0;
        }
        
        switch (turn % 2)
        {
            case 0:
                printf("(黒)の番です\n");
                my_color = BLACK;
                opponent_color = WHITE;
                break;
            default:
                printf("(白)の番です\n");
                my_color = WHITE;
                opponent_color = BLACK;
                break;
        }
        
        put1();
        //copy1();
        disp_mas();
        delete ();
        copy2();
        
        if (put2() == 0)
        {
            printf("打つところがありません. 自動でパスします.\n");
            gl_j++;
            turn++;
            continue;
        }
        
        gl_j = 0;
        
        switch (turn % 2)
        {
            case 0:
                //scanf("%d", &tnum);
                srand(time(NULL));
                int i = rand() % gl_delete_count;
                tnum = 10 * gl__x[i] + gl__y[i];
                printf("%d", tnum);
                break;
            default:
                printf("計算中.....\n\n");
                tnum = othelloAI();
                if (turn % 2 == 0)
                { //黒の時
                    my_color = BLACK;
                    opponent_color = WHITE;
                }
                else
                {
                    my_color = WHITE;
                    opponent_color = BLACK;
                }
                break;
        }
        
        if (tnum == 0)
            return 0;
        
        x = tnum / 10;
        y = tnum % 10;
        
        gl_x = x;
        gl_y = y;
        
        if (check() == 0 || tnum > 88 || tnum < 11) //置ける場所がないまたはマスの座標外
        {
            printf("その場所には打つことは出来ません.\n\n>");
            continue;
        }
        
        mas[y][x] = my_color;
        
        break;
    }
    
    return 1;
}

void put1(void)
{
    int counta, countb;
    int change = 0;
    
    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            if (mas[counta][countb] != EMPTY)
                continue;
            if (put1_check(counta, countb, MINUS, MINUS) == 0)
                continue; //左上
            if (put1_check(counta, countb, MINUS, ZERO) == 0)
                continue; //上
            if (put1_check(counta, countb, MINUS, PLUS) == 0)
                continue; //右上
            if (put1_check(counta, countb, ZERO, MINUS) == 0)
                continue; //左
            if (put1_check(counta, countb, ZERO, PLUS) == 0)
                continue; //右
            if (put1_check(counta, countb, PLUS, MINUS) == 0)
                continue; //左下
            if (put1_check(counta, countb, PLUS, ZERO) == 0)
                continue; //下
            if (put1_check(counta, countb, PLUS, PLUS) == 0)
                continue; //右下
        }
    }
}

int put1_check(int y, int x, int dy, int dx)
{
    int counta = 0;
    int fx = dx, fy = dy;
    
    while (1)
    {
        if (mas[y + fy][x + fx] == EMPTY || mas[y + fy][x + fx] == WALL || mas[y + fy][x + fx] == GUIDE)
        {
            counta = 0;
            break;
        }
        else if (mas[y + fy][x + fx] == my_color)
            break;
        
        counta++;
        fy += dy;
        fx += dx;
    }
    
    if (counta == 0)
        return 1;
    else
    {
        mas[y][x] = GUIDE;
        gl__x[gl_count] = x;
        gl__y[gl_count] = y;
        gl_count++;
        return 0;
    }
}

int put2(void)
{
    
    int counta, countb;
    int change = 0;
    
    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            if (mas[counta][countb] != EMPTY)
                continue;
            if (put2_check(counta, countb, MINUS, MINUS) == 0)
            {
                change++;
                continue;
            }
            if (put2_check(counta, countb, MINUS, ZERO) == 0)
            {
                change++;
                continue;
            }
            if (put2_check(counta, countb, MINUS, PLUS) == 0)
            {
                change++;
                continue;
            }
            if (put2_check(counta, countb, ZERO, MINUS) == 0)
            {
                change++;
                continue;
            }
            if (put2_check(counta, countb, ZERO, PLUS) == 0)
            {
                change++;
                continue;
            }
            if (put2_check(counta, countb, PLUS, MINUS) == 0)
            {
                change++;
                continue;
            }
            if (put2_check(counta, countb, PLUS, ZERO) == 0)
            {
                change++;
                continue;
            }
            if (put2_check(counta, countb, PLUS, PLUS) == 0)
            {
                change++;
                continue;
            }
        }
    }
    return change;
}
//置けるかどうかの判定
int put2_check(int y, int x, int dy, int dx)
{
    
    int counta = 0;
    int fx = dx, fy = dy;
    
    while (1)
    {
        if (mas[y + fy][x + fx] == EMPTY || mas[y + fy][x + fx] == WALL || mas[y + fy][x + fx] == GUIDE)
        {
            counta = 0;
            break;
        }
        else if (mas[y + fy][x + fx] == my_color)
            break;
        
        counta++;
        fy += dy;
        fx += dx;
    }
    switch (counta)
    {
        case 0: //置く場所が１つもない
            return 1;
            break;
        default: //置く場所が少なくとも１つはある
            return 0;
            break;
    }
}
//裏返すことの出来る駒の枚数
int check(void)
{
    int check_num = 0;
    
    if (mas[gl_y][gl_x] == WHITE || mas[gl_y][gl_x] == BLACK)
        return 0;
    
    check_num += num_check(MINUS, MINUS);
    check_num += num_check(MINUS, ZERO);
    check_num += num_check(MINUS, PLUS);
    check_num += num_check(ZERO, MINUS);
    check_num += num_check(ZERO, PLUS);
    check_num += num_check(PLUS, MINUS);
    check_num += num_check(PLUS, ZERO);
    check_num += num_check(PLUS, PLUS);
    
    switch (check_num)
    {
        case 0:
            return 0;
            break;
        default:
            return 1;
            break;
    }
}
int num_check(int dy, int dx)
{
    int counta = 0;
    int fx = dx, fy = dy;
    
    while (1)
    {
        if (mas[gl_y + fy][gl_x + fx] == EMPTY || mas[gl_y + fy][gl_x + fx] == WALL || mas[gl_y + fy][gl_x + fx] == GUIDE)
        {
            counta = 0;
            break;
        }
        else if (mas[gl_y + fy][gl_x + fx] == my_color)
            break;
        
        counta++;
        fy += dy;
        fx += dx;
    }
    return counta;
}

int calculation(void)
{
    int c_mas1ount = 0;
    
    c_mas1ount += calculation_check(MINUS, MINUS);
    c_mas1ount += calculation_check(MINUS, ZERO);
    c_mas1ount += calculation_check(MINUS, PLUS);
    c_mas1ount += calculation_check(ZERO, MINUS);
    c_mas1ount += calculation_check(ZERO, PLUS);
    c_mas1ount += calculation_check(PLUS, MINUS);
    c_mas1ount += calculation_check(PLUS, ZERO);
    c_mas1ount += calculation_check(PLUS, PLUS);
    
    return c_mas1ount;
}

int calculation_check(int dy, int dx)
{
    int counta = 0;
    int reverse_x[20], reverse_y[20];
    int fx = dx, fy = dy;
    
    while (1)
    {
        if (mas[gl_y + fy][gl_x + fx] == opponent_color)
        {
            reverse_x[counta] = gl_x + fx;
            reverse_y[counta] = gl_y + fy;
            
            counta++;
        }
        else
            break;
        
        fy += dy;
        fx += dx;
    }
    
    if (counta > 0 && mas[gl_y + fy][gl_x + fx] == my_color)
    {
        reverse(reverse_x, reverse_y, counta);
        return counta;
    }
    
    return 0;
}

void reverse(int x[], int y[], int c)
{
    for (int t = 0; t < c; t++)
        mas[y[t]][x[t]] = my_color;
}

void result(int j)
{
    
    int counta, countb;
    int black = 0, white = 0;
    
    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            if (mas[counta][countb] == BLACK)
            {
                black++;
            }
            else if (mas[counta][countb] == WHITE)
            {
                white++;
            }
        }
    }
    
    disp_mas();
    
    printf("黒(%d) 白(%d)\t", black, white);
    
    switch (j)
    {
        case 1:
            if (black > white)
            {
                printf("黒 の勝利です.\n");
                printf("お見事です.\n");
            }
            else if (black < white)
            {
                printf("白 の勝利です.\n");
            }
            else
            {
                printf("引き分けです.\n");
            }
            break;
    }
}

