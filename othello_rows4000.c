#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define EMPTY 0
#define WALL 1
#define WHITE 2
#define BLACK 3
#define GUIDE 4
#define HU -3
#define SE 3
#define ZERO 0

int othello_AI(int n); //AIの関数
void othello_gl__xy_c(int ar_x[][40], int ar_y[][40], int ar_times);
void othello_gl__xy_c_r(int ar_x[][40], int ar_y[][40], int ar_times);
//void othello_gl_del_count_c(int ar_del_count_c[], int ar_times);
void othello_gl_del_count_c_r(int ar_del_count_c[], int ar_times);
void othello_mas_c(int c1_mas[][SIZE], int c2_mas[][SIZE], int ar_times);
void othello_mas_c_r(int c1_mas[][SIZE], int c2_mas[][SIZE], int ar_times);
void othello_min_max(int ar_jdg_REVERSE_num[][1000], int ar_jdg_GUIDE_num[][1000], int ar_first[], int ar_jdg_t_c[], int ar_times, int ar_EMPTY_count);
void othello_detail_min_max(int ar_first[], int ar_jdg_t_c[], int ar_jdg_count[], int ar_jdg_REVERSE_num[][1000], int ar_jdg_GUIDE_num[][1000], int ar_jdg_minmax_REVERSE_num[][100][1000], int ar_jdg_minmax_GUIDE_num[][100][1000], int ar_jdg_minmax_REVERSE_dual_num[][1000], int ar_jdg_minmax_GUIDE_dual_num[][1000], int ar_times, int ar_EMPTY_count);
int othello_est_total(int ar_jdg_total_REVERSE_dual_count[], int ar_jdg_minmax_REVERSE_dual_num[][1000], int ar_jdg_minmax_REVERSE_num[][100][1000], int ar_jdg_est_REVERSE_num[], int ar_jdg_total_GUIDE_dual_count[], int ar_jdg_minmax_GUIDE_dual_num[][1000], int ar_jdg_minmax_GUIDE_num[][100][1000], int ar_jdg_est_GUIDE_num[], int ar_jdg_count[], int ar_times, int ar_EMPTY_count);
void othello_dual_count(int ar_minmax_REVERSE_dual_num[][1000], int ar_jdg_total_REVERSE_dual_count[], int ar_minmax_GUIDE_dual_num[][1000], int ar_jdg_total_GUIDE_dual_count[], int ar_EMPTY_count);
void othello_index_reset(int ar_jdg_t_c[], int ar_first[], int ar_k[][100], int ar_jdg_REVERSE_num[][1000], int ar_jdg_GUIDE_num[][1000], int ar_jdg_count[]);
int othello_X_check(int ar_x[][40], int ar_y[][40], int ar_k[][100], int ar_jdg_count[], int ar_times);
int othello_coner_check(int ar_x[][40], int ar_y[][40], int ar_k[][100], int ar_jdg_count[], int ar_times);
int othello_next_to_coner_check(int ar_x[][40], int ar_y[][40], int ar_k[][100], int ar_jdg_count[], int ar_times);
int othello_edge_check(int ar_x[][40], int ar_y[][40], int ar_k[][100], int ar_jdg_count[], int ar_times, int n);
int othello_even_method(int ar_x[][40], int ar_y[][40], int ar_k[][100], int ar_jdg_count[], int ar_times);
void othello_est_entire(int ar_jdg_est_entire[], int ar_jdg_t_c[], int ar_times);
void othello_final_num(int ar_count, int ar_final_num[], int ar_jdg_est_entire[], int ar_jdg_est_REVERSE_num[], int ar_jdg_est_GUIDE_num[], int ar_jdg_t_c[], int ar_times, int ar_EMPTY_count);
int slc(void);      //先行後攻かを選択
void rep(void);     //masの表示
int E_cnt(void);    //EMPTYの数のカウント
int W_cnt(void);    //WHITEの数のカウント
int B_cnt(void);    //BLACKの数のカウント
void copy1(void);   //みんなのAIに渡すためのコピー版mas_sの作成~GUIDE付きコピー（del())前
void copy1_r(void); //copy1の逆
void copy2(void);   //GUIDE無しコピー（del())後
void copy2_r(void); //copy2の逆
void del(void);     //mas内のGUIDEの消去
int ins(int n);     //masに入力
int put1(int n);    //GUIDEの置ける場所の確認と配置
int put1_upl(int y, int x, int n);
int put1_up(int y, int x, int n);
int put1_upr(int y, int x, int n);
int put1_l(int y, int x, int n);
int put1_r(int y, int x, int n);
int put1_ll(int y, int x, int n);
int put1_un(int y, int x, int n);
int put1_lr(int y, int x, int n);
int put2(int n); //GUIDEの置ける場所の確認のみ
int put2_upl(int y, int x, int n);
int put2_up(int y, int x, int n);
int put2_upr(int y, int x, int n);
int put2_l(int y, int x, int n);
int put2_r(int y, int x, int n);
int put2_ll(int y, int x, int n);
int put2_un(int y, int x, int n);
int put2_lr(int y, int x, int n);
int check(int n); //正しい位置に置けるか否か
int check_upl(int n);
int check_up(int n);
int check_upr(int n);
int check_l(int n);
int check_r(int n);
int check_ll(int n);
int check_un(int n);
int check_lr(int n);
int cal(int n); //裏返しのデータをrev関数に送る
int cal_upl(int n);
int cal_up(int n);
int cal_upr(int n);
int cal_l(int n);
int cal_r(int n);
int cal_ll(int n);
int cal_un(int n);
int cal_lr(int n);
void rev(int x[], int y[], int n, int c); //実際に裏返す
void res(int j);                          //終了結果の表示

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
//コピー用１つ目
int c_mas1[SIZE][SIZE] = {
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
//コピー用２つ目
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

int gl_x, gl_y;
int gl__x[30] = {0}, gl__y[30] = {0};
int gl_count = 0; //for put関数
int gl_del_count;
int gl_j = 0;

int main(void)
{

    rep();

    int turn;
    int d = 1;
    int jdg = 1;
    int change;
    int a = 1, b = 1, c = 1;
    char ch;

    turn = slc();

    switch (turn)
    {
    case 0:
        turn = 1;
        d = 0;
        break;
    }

    put1(turn);

    switch (d)
    {
    case 0:
        turn = 0;
        break;
    }
    copy1();

    rep();
    del();

    copy2();
    //自分が黒の時
    if (turn == 0)
    {

        turn = 1;

        while (1)
        {

            switch (turn % 2)
            {
            case 1:
                printf("あなた(黒)の番です.\n>");
                break;
            case 0:
                printf("敵(白)の番です.\n>");
                break;
            }

            jdg = ins(turn);

            if (jdg == 0)
            {
                res(jdg);
                printf("終了しました.\n");
                break;
            }

            cal(turn);

            turn++;

            change = put1(turn);

            copy1();

            rep();
            del();

            copy2();

            a = E_cnt();
            b = W_cnt();
            c = B_cnt();

            if (a == 0)
            {
                res(a + 1); //for res関数
                break;
            }
            else if (b == 0)
            {
                res(b + 1);
                break;
            }
            else if (c == 0)
            {
                res(c + 1);
                break;
            }
            else if (gl_j == 2)
            {
                printf("お互いに打つことが出来ません. \n");
                res(gl_j - 1);
                break;
            }

            gl_j = 0;

            switch (change)
            {
            case 0:
                turn++;
                gl_j++;
                printf("打つところが無くなりました. 自動でパスします.\n");
                put1(turn);
                copy1();
                rep();
                del();
                break;
            }
        }
    }
    //自分が白の時
    else
    {
        while (1)
        {

            switch (turn % 2)
            {
            case 0:
                printf("あなた(白)の番です.\n>");
                break;
            case 1:
                printf("敵(黒)の番です.\n>");
                break;
            }

            jdg = ins(turn);

            if (jdg == 0)
            {
                res(jdg);
                printf("終了しました.\n");
                break;
            }

            cal(turn);

            turn++;

            change = put1(turn);

            copy1();

            rep();
            del();

            copy2();

            a = E_cnt();
            b = W_cnt();
            c = B_cnt();

            if (a == 0)
            {
                res(a + 1); //for res関数
                break;
            }
            else if (b == 0)
            {
                res(b + 1);
                break;
            }
            else if (c == 0)
            {
                res(c + 1);
                break;
            }
            else if (gl_j == 2)
            {
                printf("お互いに打つことが出来ません.\n");
                res(gl_j - 1);
                break;
            }

            gl_j = 0;

            switch (change)
            {
            case 0:
                turn++;
                gl_j++;
                printf("打つところが無くなりました. 自動でパスします.\n");
                put1(turn);
                copy1();
                rep();
                del();
                break;
            }
        }
    }
    return 0;
}

int othello_AI(int n)
{
    static int times = 0;                        //for添字
    int count = 0, counta = 0, countb = 0;       //for添字　tmpは並び替えの時に一時的に入れておくための変数。
    static int jdg_t_c[10] = {0};                //for添字
    static int first[10] = {0};                  //for添字
    static int k[10][100] = {{0}, {0}};          //for添字
    static int gl_del_count_c[10] = {0};         //for　gl_del_countのコピー
    static int gl__x_c[10][40], gl__y_c[10][40]; //for gl__x,gl__yのコピー
    static int jdg_count[10] = {0};              //for添字→ 関数の出入りの１かたまりの数をそれぞれ記録する。グループ分けとしての変数。
    int EMPTY_count = 0;                         //for　EMPTY_count=E_cnt()を序盤、中盤、終盤を分けるための判断材料

    static int jdg_GUIDE_num[10][1000] = {{0}, {0}};                    //for GUIDEの数
    static int jdg_REVERSE_num[10][1000] = {{0}, {0}};                  //for 返すことのできる駒の数
    static int jdg_minmax_GUIDE_dual_num[10][1000] = {{0}, {0}};        //for jdg_minmax_GUIDE_num[][][]が複数ある場合にその個数の保持する。
    static int jdg_minmax_REVERSE_dual_num[10][1000] = {{0}, {0}};      //for jdg_minmax_REVERSE_num[][][]が複数ある場合にその個数の保持する。
    int jdg_est_GUIDE_num[1000] = {0};                                  //for 各timesでのjdg_minmax_GUIDE_numの組み合わせたもの（評価）を入れる。
    int jdg_est_REVERSE_num[1000] = {0};                                //for 各timesでのjdg_minmax_REVERSE_numの組み合わせたもの（評価）を入れる。
    int jdg_total_GUIDE_dual_count[10] = {0};                           //for jdg_minmax_GUIDE_dual_num[][]の総和
    int jdg_total_REVERSE_dual_count[10] = {0};                         //for jdg_minmax_REVERSE_dual_num[][]の総和
    static int jdg_minmax_GUIDE_num[10][100][1000] = {{0}, {0}, {0}};   //for jdg_GUIDE_numの最大最小を入れておく。
    static int jdg_minmax_REVERSE_num[10][100][1000] = {{0}, {0}, {0}}; //for jdg_REVERSE_numの最大最小を入れておく。
    int guide = 0;
    int jdg_est_entire[40] = {0}; //偶数理論や角、X打ちなどのポイント
    int final_num[100] = {0};

    static int c1_mas[SIZE][SIZE] = {
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
    static int c2_mas[SIZE][SIZE] = {
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

    first[times] = jdg_t_c[times];

    //for　mas[SIZE][SIZE]のコピー
    othello_mas_c(c1_mas, c2_mas, times);
    //gl_del_countにGUIDEの個数をコピーするため。times==0の時はすでにもう入っている。
    switch (times)
    {
    case 0:
        EMPTY_count = E_cnt();
        break;
    default:
        del();
        EMPTY_count = E_cnt();
        break;
    }
    gl_del_count_c[times] = put2(n);
    //for mas[SIZE][SIZE]にコピーし直す。
    othello_mas_c_r(c1_mas, c2_mas, times);
    //for gl_del_count_cにgl_del_countをコピー
    //othello_gl_del_count_c(gl_del_count_c, times);
    //for gl__x[],gl__y[]の座標のコピー　これを行うには事前にdel()を呼び、gl_del_countにGUIDEの個数を入れておかなければならない。
    othello_gl__xy_c(gl__x_c, gl__y_c, times);
    //printf("jdg_t_c[times]==%d\n",jdg_t_c[times]);
    if (n % 2 == 0)
    {

        for (; jdg_t_c[times] - first[times] < gl_del_count_c[times]; jdg_t_c[times]++)
        {
            //printf("-%d-", mas[gl__y_c[times][k[times][jdg_count[times]]]][gl__x_c[times][k[times][jdg_count[times]]]]);
            //printf("jdg_t_c[times]==%d:gl_del_count_c[times]==%d\n",jdg_t_c[times],gl_del_count_c[times]);
            switch (mas[gl__y_c[times][k[times][jdg_count[times]]]][gl__x_c[times][k[times][jdg_count[times]]]])
            {
            case GUIDE:
                printf("W");
                //printf("jdg_t_c[times]==%d\n",jdg_t_c[times]);
                gl_x = gl__x_c[times][k[times][jdg_count[times]]];
                gl_y = gl__y_c[times][k[times][jdg_count[times]]];
                cal(n);
                //printf("jdg_t_c[times]==%d\n",jdg_t_c[times]);
                othello_gl_del_count_c_r(gl_del_count_c, times);
                othello_gl__xy_c_r(gl__x_c, gl__y_c, times);
                del();
                mas[gl__y_c[times][k[times][jdg_count[times]]]][gl__x_c[times][k[times][jdg_count[times]]]] = WHITE;

                if (times == 0 && EMPTY_count / 6 != 0)
                {
                    jdg_est_entire[jdg_t_c[times]] += 10; //マイナスで引いてもふにならないようにあらかじめ、大きな値を加えて置く。
                    jdg_est_entire[jdg_t_c[times]] += 100 * jdg_t_c[times] + othello_even_method(gl__x_c, gl__y_c, k, jdg_count, times);
                    //printf("通過しました");

                    //jdg_est_entire[jdg_t_c[times]] += 10;

                    jdg_est_entire[jdg_t_c[times]] += othello_X_check(gl__x_c, gl__y_c, k, jdg_count, times);
                    jdg_est_entire[jdg_t_c[times]] += othello_edge_check(gl__x_c, gl__y_c, k, jdg_count, times, n);
                    jdg_est_entire[jdg_t_c[times]] += othello_coner_check(gl__x_c, gl__y_c, k, jdg_count, times);
                    jdg_est_entire[jdg_t_c[times]] += othello_next_to_coner_check(gl__x_c, gl__y_c, k, jdg_count, times);

                    //printf("jdg_est_entire[jdg_t_c[times]]==%d\n", jdg_est_entire[jdg_t_c[times]]);
                }
                jdg_GUIDE_num[times][jdg_t_c[times]] = 10000 * jdg_t_c[times] + 100 * jdg_count[times] + put1(n + 1);
                if (times == 0 && EMPTY_count / 6 != 0)
                {
                    if (jdg_GUIDE_num[times][jdg_t_c[times]] % 100 == 0)
                    {
                        guide++;
                        break;
                    }
                }

                //printf("%d;%d*",jdg_t_c[times],jdg_count[times]);
                //printf("times==%d:%d\n",times,jdg_GUIDE_num[times][jdg_t_c[times]]);

                switch (times / 2)
                {
                case 0:
                    //printf("EMPTY==%d\n", EMPTY_count);
                    times++;
                    othello_AI(n + 1);
                    times--;
                    //printf("EMPTY==%d\n", EMPTY_count);

                    break;
                }

                othello_mas_c_r(c1_mas, c2_mas, times);

                break;
            }
            k[times][jdg_count[times]]++;
        }
    }
    else
    {

        for (; jdg_t_c[times] - first[times] < gl_del_count_c[times]; jdg_t_c[times]++)
        {
            //printf("-%d-", mas[gl__y_c[times][k[times][jdg_count[times]]]][gl__x_c[times][k[times][jdg_count[times]]]]);

            //printf("jdg_t_c[times]==%d:gl_del_count_c[times]==%d\n", jdg_t_c[times], gl_del_count_c[times]);
            switch (mas[gl__y_c[times][k[times][jdg_count[times]]]][gl__x_c[times][k[times][jdg_count[times]]]])
            {
            case GUIDE:
                printf("B");
                gl_x = gl__x_c[times][k[times][jdg_count[times]]];
                gl_y = gl__y_c[times][k[times][jdg_count[times]]];
                jdg_REVERSE_num[times][jdg_t_c[times]] = 10000 * jdg_t_c[times] + 100 * jdg_count[times] + cal(n);

                othello_gl_del_count_c_r(gl_del_count_c, times);
                othello_gl__xy_c_r(gl__x_c, gl__y_c, times);
                del();
                mas[gl__y_c[times][k[times][jdg_count[times]]]][gl__x_c[times][k[times][jdg_count[times]]]] = BLACK;

                //細かな条件を満たすことが出来か否かチェックする
                if (times == 0 && EMPTY_count / 6 != 0)
                {
                    jdg_est_entire[jdg_t_c[times]] += 10;
                    jdg_est_entire[jdg_t_c[times]] += 100 * jdg_t_c[times] + othello_even_method(gl__x_c, gl__y_c, k, jdg_count, times);
                    //printf("通過しました");

                    //jdg_est_entire[jdg_t_c[times]] += 10;
                    //printf("jdg_est_entire[jdg_t_c[times]]==%d", jdg_est_entire[jdg_t_c[times]]);
                    jdg_est_entire[jdg_t_c[times]] += othello_X_check(gl__x_c, gl__y_c, k, jdg_count, times);
                    jdg_est_entire[jdg_t_c[times]] += othello_edge_check(gl__x_c, gl__y_c, k, jdg_count, times, n);
                    jdg_est_entire[jdg_t_c[times]] += othello_coner_check(gl__x_c, gl__y_c, k, jdg_count, times);
                    jdg_est_entire[jdg_t_c[times]] += othello_next_to_coner_check(gl__x_c, gl__y_c, k, jdg_count, times);

                    //printf("jdg_est_entire[jdg_t_c[times]]==%d\n", jdg_est_entire[jdg_t_c[times]]);
                }
                jdg_GUIDE_num[times][jdg_t_c[times]] = 10000 * jdg_t_c[times] + 100 * jdg_count[times] + put1(n + 1);
                if (times == 0 && EMPTY_count / 6 != 0)
                {
                    if (jdg_GUIDE_num[times][jdg_t_c[times]] % 100 == 0)
                    {
                        guide++;
                        break;
                    }
                }
                //printf("times==%d:%d\n",times,jdg_GUIDE_num[times][jdg_t_c[times]]);
                switch (times / 2)
                {
                case 0:
                    //printf("EMPTY==%d\n", EMPTY_count);

                    times++;
                    othello_AI(n + 1);
                    times--;
                    //printf("EMPTY==%d\n", EMPTY_count);
                    break;
                }

                othello_mas_c_r(c1_mas, c2_mas, times);

                break;
            }
            k[times][jdg_count[times]]++;
        }
    }

    othello_min_max(jdg_REVERSE_num, jdg_GUIDE_num, first, jdg_t_c, times, EMPTY_count);
    othello_detail_min_max(first, jdg_t_c, jdg_count, jdg_REVERSE_num, jdg_GUIDE_num, jdg_minmax_REVERSE_num, jdg_minmax_GUIDE_num, jdg_minmax_REVERSE_dual_num, jdg_minmax_GUIDE_dual_num, times, EMPTY_count);

    jdg_count[times]++;

    switch (times)
    {
    case 0:
        othello_dual_count(jdg_minmax_REVERSE_dual_num, jdg_total_REVERSE_dual_count, jdg_minmax_GUIDE_dual_num, jdg_total_GUIDE_dual_count, EMPTY_count);
        /*for (counta = 0; counta < jdg_total_GUIDE_dual_count[times];counta++){
                printf("jdg_minmax_GUIDE_num[times][0][counta]==%d\n", jdg_minmax_GUIDE_num[times][0][counta]);
            }*/
        //printf("jdg_total_GUIDE_dual_count[0]==%d\n", jdg_total_GUIDE_dual_count[times]);
        //printf("%d:%d:%d\n", jdg_count[times], jdg_count[times + 1], jdg_count[times + 2]);

        count = othello_est_total(jdg_total_REVERSE_dual_count, jdg_minmax_REVERSE_dual_num, jdg_minmax_REVERSE_num, jdg_est_REVERSE_num, jdg_total_GUIDE_dual_count, jdg_minmax_GUIDE_dual_num, jdg_minmax_GUIDE_num, jdg_est_GUIDE_num, jdg_count, times, EMPTY_count);

        //othello_minmax_reset(jdg_minmax_GUIDE_num);
        //othello_t_c_first_reset(jdg_t_c_first);
        //printf("count==%d\n",count);
        //誤った返り値を送る場合は0にするため。
        for (counta = 0; gl__x[counta] != 0; counta++)
        {
            gl__x[counta] = 0;
            gl__y[counta] = 0;
        }
        //下のGUIDEの座標をglに代入するため。
        othello_mas_c_r(c1_mas, c2_mas, times);

        int t = 0;
        for (counta = 1; counta <= 8; counta++)
        {
            for (countb = 1; countb <= 8; countb++)
            {
                switch (mas[counta][countb])
                {
                case GUIDE:
                    gl__x[t] = countb;
                    gl__y[t] = counta;

                    t++;
                    break;
                }
            }
        }
        othello_est_entire(jdg_est_entire, jdg_t_c, times);
        othello_final_num(count, final_num, jdg_est_entire, jdg_est_REVERSE_num, jdg_est_GUIDE_num, jdg_t_c, times, EMPTY_count);

        printf("final_num[0]==%d\n", final_num[0]);

        othello_index_reset(jdg_t_c, first, k, jdg_REVERSE_num, jdg_GUIDE_num, jdg_count);
        break;
    }
    //jdg_est_REVERSE_numとjdg_est_GUIDE_numが同時に扱われることはない。
    switch (guide)
    {
    case 0:
        return 10 * gl__x[final_num[0] / 100] + gl__y[final_num[0] / 100];
        break;
    default:
        return 10 * gl__x[jdg_t_c[0]] + gl__y[jdg_t_c[0]];
        break;
    }

    //return 10 * gl__x[final_num[0] / 100] + gl__y[final_num[0] / 100];
}

void othello_gl__xy_c(int ar_x[][40], int ar_y[][40], int ar_times)
{

    int counta, countb;
    int t = 0;

    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            switch (mas[counta][countb])
            {
            case GUIDE:
                ar_x[ar_times][t] = countb;
                ar_y[ar_times][t] = counta;
                t++;
                break;
            }
        }
    }

    /*for (counta = 0; counta < gl_del_count; counta++)
        {
            ar_x[ar_times][counta] = gl__x[counta];
            ar_y[ar_times][counta] = gl__y[counta];
        }*/
}

void othello_gl__xy_c_r(int ar_x[][40], int ar_y[][40], int ar_times)
{

    int counta;

    for (counta = 0; counta < gl_del_count; counta++)
    {
        gl__x[counta] = ar_x[ar_times][counta];
        gl__y[counta] = ar_y[ar_times][counta];
    }
}
/*void othello_gl_del_count_c(int ar_del_count_c[], int ar_times)
{

    ar_del_count_c[ar_times] = gl_del_count;
}*/

void othello_gl_del_count_c_r(int ar_del_count_c[], int ar_times)
{

    gl_count = ar_del_count_c[ar_times];
}

void othello_mas_c(int c1_mas[][SIZE], int c2_mas[][SIZE], int ar_times)
{

    int counta, countb;

    switch (ar_times)
    {
    /*case 0:
            copy1();
            break;*/
    case 1:
        for (counta = 1; counta <= 8; counta++)
        {
            for (countb = 1; countb <= 8; countb++)
            {
                c1_mas[counta][countb] = mas[counta][countb];
            }
        }
        break;
    case 2:
        for (counta = 1; counta <= 8; counta++)
        {
            for (countb = 1; countb <= 8; countb++)
            {
                c2_mas[counta][countb] = mas[counta][countb];
            }
        }
        break;
    }
}

void othello_mas_c_r(int c1_mas[][SIZE], int c2_mas[][SIZE], int ar_times)
{

    int counta, countb;

    switch (ar_times)
    {
    case 0:
        copy1_r();
        break;
    case 1:
        for (counta = 1; counta <= 8; counta++)
        {
            for (countb = 1; countb <= 8; countb++)
            {
                mas[counta][countb] = c1_mas[counta][countb];
            }
        }
        break;
    case 2:
        for (counta = 1; counta <= 8; counta++)
        {
            for (countb = 1; countb <= 8; countb++)
            {
                mas[counta][countb] = c2_mas[counta][countb];
            }
        }
        break;
    }
}
//ok
void othello_min_max(int ar_jdg_REVERSE_num[][1000], int ar_jdg_GUIDE_num[][1000], int ar_first[], int ar_jdg_t_c[], int ar_times, int ar_EMPTY_count)
{

    int counta, countb;
    int tmp;

    switch (ar_EMPTY_count / 6)
    {

    case 0:
        //for jdg_REVERSE_num
        //グループごとのar_times%2==0の時（自分）Max-Max,ar_times%2==1の時（相手）Max-Minを調べるために、まずMaxが先頭にくるように入れ替える。
        //最大
        for (counta = ar_first[ar_times]; counta < ar_jdg_t_c[ar_times] - 1; counta++)
        {
            for (countb = counta + 1; countb < ar_jdg_t_c[ar_times]; countb++)
            {
                if (ar_jdg_REVERSE_num[ar_times][counta] % 100 < ar_jdg_REVERSE_num[ar_times][countb] % 100)
                {
                    tmp = ar_jdg_REVERSE_num[ar_times][counta];
                    ar_jdg_REVERSE_num[ar_times][counta] = ar_jdg_REVERSE_num[ar_times][countb];
                    ar_jdg_REVERSE_num[ar_times][countb] = tmp;
                }
            }
        }
        break;

    default:
        //for jdg_GUIDE_num
        //グループごとのar_times%2==0の時（あいてのGUIDE数）Min-Min,ar_times%2==1の時（じぶんのGUIDE数）Min-Maxを調べるために、まずMinが先頭にくるように入れ替える。
        for (counta = ar_first[ar_times]; counta < ar_jdg_t_c[ar_times] - 1; counta++)
        {
            for (countb = counta + 1; countb < ar_jdg_t_c[ar_times]; countb++)
            {
                if (ar_jdg_GUIDE_num[ar_times][counta] % 100 > ar_jdg_GUIDE_num[ar_times][countb] % 100)
                {
                    tmp = ar_jdg_GUIDE_num[ar_times][counta];
                    ar_jdg_GUIDE_num[ar_times][counta] = ar_jdg_GUIDE_num[ar_times][countb];
                    ar_jdg_GUIDE_num[ar_times][countb] = tmp;
                }
            }
        }

        break;
    }
}
//ok
void othello_detail_min_max(int ar_first[], int ar_jdg_t_c[], int ar_jdg_count[], int ar_jdg_REVERSE_num[][1000], int ar_jdg_GUIDE_num[][1000], int ar_jdg_minmax_REVERSE_num[][100][1000], int ar_jdg_minmax_GUIDE_num[][100][1000], int ar_jdg_minmax_REVERSE_dual_num[][1000], int ar_jdg_minmax_GUIDE_dual_num[][1000], int ar_times, int ar_EMPTY_count)
{

    int counta, countb = 0;

    switch (ar_EMPTY_count / 6)
    {

    case 0:
        for (counta = ar_first[ar_times]; counta < ar_jdg_t_c[ar_times]; counta++)
        {
            if (ar_jdg_REVERSE_num[ar_times][ar_first[ar_times]] % 100 == ar_jdg_REVERSE_num[ar_times][counta] % 100)
            {
                ar_jdg_minmax_REVERSE_num[ar_times][ar_jdg_count[ar_times]][countb] = ar_jdg_REVERSE_num[ar_times][counta];
                countb++;
                ar_jdg_minmax_REVERSE_dual_num[ar_times][ar_jdg_count[ar_times]] = countb;
            }
            else
            {
                break;
            }
        }
        break;
    default:

        for (counta = ar_first[ar_times]; counta < ar_jdg_t_c[ar_times]; counta++)
        {
            if (ar_jdg_GUIDE_num[ar_times][ar_first[ar_times]] % 100 == ar_jdg_GUIDE_num[ar_times][counta] % 100)
            {
                ar_jdg_minmax_GUIDE_num[ar_times][ar_jdg_count[ar_times]][countb] = ar_jdg_GUIDE_num[ar_times][counta];
                countb++;
                ar_jdg_minmax_GUIDE_dual_num[ar_times][ar_jdg_count[ar_times]] = countb;
            }
            else
            {
                break;
            }
        }
        break;
    }
}
//ok
int othello_est_total(int ar_jdg_total_REVERSE_dual_count[], int ar_jdg_minmax_REVERSE_dual_num[][1000], int ar_jdg_minmax_REVERSE_num[][100][1000], int ar_jdg_est_REVERSE_num[], int ar_jdg_total_GUIDE_dual_count[], int ar_jdg_minmax_GUIDE_dual_num[][1000], int ar_jdg_minmax_GUIDE_num[][100][1000], int ar_jdg_est_GUIDE_num[], int ar_jdg_count[], int ar_times, int ar_EMPTY_count)
{

    int count = 0;
    int counta, countb, countc, countd, counte;
    int tmp;

    switch (ar_EMPTY_count / 6)
    {

    case 0:
        switch (ar_EMPTY_count)
        {
        case 2:
            for (counta = 0; counta < ar_jdg_total_REVERSE_dual_count[ar_times]; counta++)
            {
                for (countb = counta; countb < ar_jdg_count[ar_times + 1]; countb++)
                {
                    for (countd = 0; countd < ar_jdg_minmax_REVERSE_dual_num[ar_times + 1][countb]; countd++)
                    {
                        if (ar_jdg_minmax_REVERSE_num[ar_times][0][counta] / 10000 == ar_jdg_minmax_REVERSE_num[ar_times + 1][countb][countd] / 100 % 100)
                        {
                            if (ar_jdg_minmax_REVERSE_num[ar_times][0][counta] % 100 - ar_jdg_minmax_REVERSE_num[ar_times + 1][countb][countd] % 100 < 0)
                            {
                                ar_jdg_est_REVERSE_num[count] = abs(ar_jdg_minmax_REVERSE_num[ar_times][0][counta] % 100 - ar_jdg_minmax_REVERSE_num[ar_times + 1][countb][countd] % 100);
                            }
                            else
                            {
                                ar_jdg_est_REVERSE_num[count] = (ar_jdg_minmax_REVERSE_num[ar_times][0][counta] % 100 - ar_jdg_minmax_REVERSE_num[ar_times + 1][countb][countd] % 100);
                            }
                            ar_jdg_est_REVERSE_num[count] += 100 * (ar_jdg_minmax_REVERSE_dual_num[ar_times][0] + ar_jdg_minmax_REVERSE_dual_num[ar_times + 1][countb]) + 10000 * (ar_jdg_minmax_REVERSE_num[ar_times][0][counta] / 10000);

                            count++;
                        }
                    }
                }
            }
            break;
        case 1:
            for (counta = 0; counta < ar_jdg_total_REVERSE_dual_count[ar_times]; counta++)
            {

                ar_jdg_est_REVERSE_num[count] = ar_jdg_minmax_REVERSE_num[ar_times][0][counta] % 100;

                ar_jdg_est_REVERSE_num[count] += 100 * ar_jdg_minmax_REVERSE_dual_num[ar_times][0] + 10000 * (ar_jdg_minmax_REVERSE_num[ar_times][0][counta] / 10000);

                count++;
            }
            break;

        default:
            for (counta = 0; counta < ar_jdg_total_REVERSE_dual_count[ar_times]; counta++)
            {
                for (countb = counta; countb < ar_jdg_count[ar_times + 1]; countb++)
                {
                    for (countc = countb; countc < ar_jdg_count[ar_times + 2]; countc++)
                    {
                        for (countd = 0; countd < ar_jdg_minmax_REVERSE_dual_num[ar_times + 1][countb]; countd++)
                        {
                            for (counte = 0; counte < ar_jdg_minmax_REVERSE_dual_num[ar_times + 2][countc]; counte++)
                            {

                                if (ar_jdg_minmax_REVERSE_num[ar_times][0][counta] / 10000 == ar_jdg_minmax_REVERSE_num[ar_times + 1][countb][countd] / 100 % 100 && ar_jdg_minmax_REVERSE_num[ar_times + 1][countb][countd] / 10000 == ar_jdg_minmax_REVERSE_num[ar_times + 2][countc][counte] / 100 % 100)
                                {
                                    if (ar_jdg_minmax_REVERSE_num[ar_times][0][counta] % 100 - ar_jdg_minmax_REVERSE_num[ar_times + 1][countb][countd] % 100 + ar_jdg_minmax_REVERSE_num[ar_times + 2][countc][counte] % 100 < 0)
                                    {
                                        ar_jdg_est_REVERSE_num[count] = abs(ar_jdg_minmax_REVERSE_num[ar_times][0][counta] % 100 - ar_jdg_minmax_REVERSE_num[ar_times + 1][countb][countd] % 100 + ar_jdg_minmax_REVERSE_num[ar_times + 2][countc][counte] % 100);
                                    }
                                    else
                                    {
                                        ar_jdg_est_REVERSE_num[count] = (ar_jdg_minmax_REVERSE_num[ar_times][0][counta] % 100 - ar_jdg_minmax_REVERSE_num[ar_times + 1][countb][countd] % 100 + ar_jdg_minmax_REVERSE_num[ar_times + 2][countc][counte] % 100);
                                    }
                                    ar_jdg_est_REVERSE_num[count] += 100 * (ar_jdg_minmax_REVERSE_dual_num[ar_times][0] + ar_jdg_minmax_REVERSE_dual_num[ar_times + 1][countb] + ar_jdg_minmax_REVERSE_dual_num[ar_times + 2][countc]) + 10000 * (ar_jdg_minmax_REVERSE_num[ar_times][0][counta] / 10000);

                                    count++;
                                }
                            }
                        }
                    }
                }
            }
            break;
        }

        for (counta = 0; counta < count - 1; counta++)
        {
            for (countb = counta + 1; countb < count; countb++)
            {
                if (ar_jdg_est_REVERSE_num[counta] % 100 <= ar_jdg_est_REVERSE_num[countb] % 100)
                {
                    tmp = ar_jdg_est_REVERSE_num[counta];
                    ar_jdg_est_REVERSE_num[counta] = ar_jdg_est_REVERSE_num[countb];
                    ar_jdg_est_REVERSE_num[countb] = tmp;
                }
            }
        }
        //d数の和が同じでも、dualの多い方を優先する
        for (counta = 0; counta < count - 1; counta++)
        {
            for (countb = counta + 1; countb < count; countb++)
            {
                if (ar_jdg_est_REVERSE_num[0] / 100 % 100 <= ar_jdg_est_REVERSE_num[counta] / 100 % 100 && ar_jdg_est_REVERSE_num[0] % 100 <= ar_jdg_est_REVERSE_num[counta] % 100)
                {
                    tmp = ar_jdg_est_REVERSE_num[counta];
                    ar_jdg_est_REVERSE_num[counta] = ar_jdg_est_REVERSE_num[countb];
                    ar_jdg_est_REVERSE_num[countb] = tmp;
                }
            }
        }

    default:
        for (counta = 0; counta < ar_jdg_total_GUIDE_dual_count[ar_times]; counta++)
        {
            for (countb = counta; countb < ar_jdg_count[ar_times + 1]; countb++)
            {
                for (countc = countb; countc < ar_jdg_count[ar_times + 2]; countc++)
                {
                    for (countd = 0; countd < ar_jdg_minmax_GUIDE_dual_num[ar_times + 1][countb]; countd++)
                    {
                        for (counte = 0; counte < ar_jdg_minmax_GUIDE_dual_num[ar_times + 2][countc]; counte++)
                        {

                            if (ar_jdg_minmax_GUIDE_num[ar_times][0][counta] / 10000 == ar_jdg_minmax_GUIDE_num[ar_times + 1][countb][countd] / 100 % 100 && ar_jdg_minmax_GUIDE_num[ar_times + 1][countb][countd] / 10000 == ar_jdg_minmax_GUIDE_num[ar_times + 2][countc][counte] / 100 % 100)
                            {
                                ar_jdg_est_GUIDE_num[count] += 20;
                                ar_jdg_est_GUIDE_num[count] = (-ar_jdg_minmax_GUIDE_num[ar_times][0][counta] % 100 + ar_jdg_minmax_GUIDE_num[ar_times + 1][countb][countd] % 100 - ar_jdg_minmax_GUIDE_num[ar_times + 2][countc][counte] % 100);
                                ar_jdg_est_GUIDE_num[count] += 100 * (ar_jdg_minmax_GUIDE_dual_num[ar_times][0] /*+ar_jdg_minmax_GUIDE_dual_num[ar_times + 1][countb]*/ + ar_jdg_minmax_GUIDE_dual_num[ar_times + 2][countc]) + 10000 * (ar_jdg_minmax_GUIDE_num[ar_times][0][counta] / 10000);

                                count++;
                            }
                        }
                    }
                }
            }
        }

        for (counta = 0; counta < count - 1; counta++)
        {
            for (countb = counta + 1; countb < count; countb++)
            {
                if (ar_jdg_est_GUIDE_num[counta] % 100 <= ar_jdg_est_GUIDE_num[countb] % 100)
                {
                    tmp = ar_jdg_est_GUIDE_num[counta];
                    ar_jdg_est_GUIDE_num[counta] = ar_jdg_est_GUIDE_num[countb];
                    ar_jdg_est_GUIDE_num[countb] = tmp;
                }
            }
        }
        for (counta = 0; counta < count - 1; counta++)
        {
            for (countb = counta + 1; countb < count; countb++)
            {
                if (ar_jdg_est_GUIDE_num[0] / 100 % 100 <= ar_jdg_est_GUIDE_num[counta] / 100 % 100 && ar_jdg_est_GUIDE_num[0] % 100 <= ar_jdg_est_GUIDE_num[counta] % 100)
                {
                    tmp = ar_jdg_est_GUIDE_num[counta];
                    ar_jdg_est_GUIDE_num[counta] = ar_jdg_est_GUIDE_num[countb];
                    ar_jdg_est_GUIDE_num[countb] = tmp;
                }
            }
        }
    }
    printf("count==%d\n", count);

    return count;
}
//ok    othello_est_total関数の最初のforの条件の右辺を[0][0]のやつで良いのでは。totalを使うのはtimesが0の時なのでtotalは正直いらないと感じた
void othello_dual_count(int ar_minmax_REVERSE_dual_num[][1000], int ar_jdg_total_REVERSE_dual_count[], int ar_minmax_GUIDE_dual_num[][1000], int ar_jdg_total_GUIDE_dual_count[], int ar_EMPTY_count)
{

    switch (ar_EMPTY_count / 6)
    {
    case 0:
        ar_jdg_total_REVERSE_dual_count[0] += ar_minmax_REVERSE_dual_num[0][0];
        break;
    default:
        ar_jdg_total_GUIDE_dual_count[0] += ar_minmax_GUIDE_dual_num[0][0];
        break;
    }
}
//多分ok
void othello_index_reset(int ar_jdg_t_c[], int ar_first[], int ar_k[][100], int ar_jdg_REVERSE_num[][1000], int ar_jdg_GUIDE_num[][1000], int ar_jdg_count[])
{

    int counta, countb;

    //ar_jdg_t_c[]
    for (counta = 0; counta < 3; counta++)
    {
        ar_jdg_t_c[counta] = 0;
    }
    //for ar_first[]
    for (counta = 0; counta < 3; counta++)
    {
        ar_first[counta] = 0;
    }
    //ar_k[][100]
    for (counta = 0; counta < 3; counta++)
    {
        for (countb = 0; ar_k[counta][countb] != 0; countb++)
        {
            ar_k[counta][countb] = 0;
        }
    }
    //int ar_jdg_REVERSE_num[][1000]
    for (counta = 0; counta < 3; counta++)
    {
        for (countb = 0; ar_jdg_REVERSE_num[counta][countb] != 0; countb++)
        {
            ar_jdg_REVERSE_num[counta][countb] = 0;
        }
    }
    //int ar_jdg_GUIDE_num[][1000]
    for (counta = 0; counta < 3; counta++)
    {
        for (countb = 0; ar_jdg_GUIDE_num[counta][countb] != 0; countb++)
        {
            ar_jdg_GUIDE_num[counta][countb] = 0;
        }
    }
    //ar_jdg_count[]
    for (counta = 0; counta < 3; counta++)
    {
        ar_jdg_count[counta] = 0;
    }
}

int othello_X_check(int ar_x[][40], int ar_y[][40], int ar_k[][100], int ar_jdg_count[], int ar_times)
{
    if (ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] == ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
    {
        switch (ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
        {
        case 2:
            return HU;
            break;
        case 14:
            return HU;
            break;
        }
    }
    else if (ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] == 8)
    {

        switch (abs(ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]))
        {
        case 5:
            return HU;
            break;
        }
    }

    return ZERO;
}

int othello_coner_check(int ar_x[][40], int ar_y[][40], int ar_k[][100], int ar_jdg_count[], int ar_times)
{

    switch (ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
    {
    case 2:
        return SE;
        break;
    case 16:
        return SE;
        break;
    }

    switch (ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
    {
    case 9:

        switch (abs(ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]))
        {
        case 7:
            return SE;
            break;
        }
    }

    return ZERO;
}

int othello_next_to_coner_check(int ar_x[][40], int ar_y[][40], int ar_k[][100], int ar_jdg_count[], int ar_times)
{
    switch (ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
    {
    case 3:
        return HU;
        break;
    case 8:
        switch (abs(ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]))
        {
        case 6:
            return HU;
            break;
        }
        break;
    case 10:
        switch (abs(ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]))
        {
        case 6:
            return HU;
            break;
        }
        break;
    case 15:
        return HU;
        break;
    }

    return ZERO;
}

int othello_edge_check(int ar_x[][40], int ar_y[][40], int ar_k[][100], int ar_jdg_count[], int ar_times, int n)
{

    int counta, countb;
    int w = 0;
    int p = 1;

    //ひとマス空きに置くかどうかの評価●□●の□についての評価
    switch (n % 2)
    {
    case 0:
        switch (ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
        {
        case 1:
            if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY && (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WALL || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == BLACK) && (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WALL || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == BLACK))
            {
                w++;
            }
            switch (ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
            {
            case 3:
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == BLACK && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + 2 * p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WHITE)
                {
                    w++;
                }
                break;
            case 6:
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - 2 * p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WHITE && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == BLACK)
                {
                    w++;
                }
                break;
            }
            /*if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY &&)
                    for (counta = 1; counta <= 8 - 2; counta++)
                    {
                        if (mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == mas[counta + 2][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] && mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == BLACK && mas[counta + 1][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == GUIDE)
                        {
                            w++;
                            break;
                        }
                    }
                for (counta = 1; counta <= 8; counta++)
                {
                    if (mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY || mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == GUIDE || mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WHITE)
                        ;
                    else
                    {
                        break;
                    }
                }*/
            break;
        case 8:
            if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY && (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WALL || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == BLACK) && (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WALL || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == BLACK))
            {
                w++;
            }
            switch (ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
            {
            case 3:
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == BLACK && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + 2 * p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WHITE)
                {
                    w++;
                }
                break;
            case 6:
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - 2 * p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WHITE && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == BLACK)
                {
                    w++;
                }
                break;
            }
            /*for (counta = 1; counta <= 8 - 2; counta++)
                {
                    if (mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == mas[counta + 2][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] && mas[counta + 1][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
                    {
                        w++;
                        break;
                    }
                }
                for (counta = 1; counta <= 8; counta++)
                {
                    if (mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY || mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == GUIDE || mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WHITE)
                        ;
                    else
                    {
                        break;
                    }
                }*/
            break;
        }
        switch (ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
        {
        case 1:
            if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY && (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p] == WALL || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p] == BLACK) && (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p] == WALL || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p] == BLACK))
            {
                w++;
            }
            switch (ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
            {
            case 3:
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p] == BLACK && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p] == EMPTY && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + 2 * p] == WHITE)
                {
                    w++;
                }
                break;
            case 6:
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - 2 * p] == WHITE && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p] == EMPTY && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p] == BLACK)
                {
                    w++;
                }
                break;
            }
            /*for (countb = 1; countb <= 8 - 2; countb++)
            {
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][countb] == mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][countb + 2] && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][countb + 1] == ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
                {
                    w++;
                    break;
                }
            }
            for (counta = 1; counta <= 8; counta++)
            {
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][counta] == EMPTY || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][counta] == GUIDE || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][counta] == WHITE)
                    ;
                else
                {
                    break;
                }
            }*/
            break;
        case 8:
            if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY && (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p] == WALL || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p] == BLACK) && (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p] == WALL || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p] == BLACK))
            {
                w++;
            }
            switch (ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
            {
            case 3:
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p] == BLACK && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p] == EMPTY && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + 2 * p] == WHITE)
                {
                    w++;
                }
                break;
            case 6:
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - 2 * p] == WHITE && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p] == EMPTY && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p] == BLACK)
                {
                    w++;
                }
                break;
            }
            /*for (countb = 1; countb <= 8 - 2; countb++)
            {
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][countb] == mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][countb + 2] && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][countb + 1] == ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
                {
                    w++;
                    break;
                }
            }
            for (counta = 1; counta <= 8; counta++)
            {
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][counta] == EMPTY || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][counta] == GUIDE || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][counta] == WHITE)
                    ;
                else
                {
                    break;
                }
            }*/
            break;
        }

    case 1:
        switch (ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
        {
        case 1:
            if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY && (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WALL || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WHITE) && (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WALL || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WHITE))
            {
                w++;
            }
            switch (ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
            {
            case 3:
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WHITE && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + 2 * p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == BLACK)
                {
                    w++;
                }
                break;
            case 6:
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - 2 * p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == BLACK && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WHITE)
                {
                    w++;
                }
                break;
            }
            /*if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY &&)
                    for (counta = 1; counta <= 8 - 2; counta++)
                    {
                        if (mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == mas[counta + 2][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] && mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WHITE && mas[counta + 1][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == GUIDE)
                        {
                            w++;
                            break;
                        }
                    }
                for (counta = 1; counta <= 8; counta++)
                {
                    if (mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY || mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == GUIDE || mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == BLACK)
                        ;
                    else
                    {
                        break;
                    }
                }*/
            break;
        case 8:
            if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY && (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WALL || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WHITE) && (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WALL || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WHITE))
            {
                w++;
            }
            switch (ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
            {
            case 3:
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WHITE && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + 2 * p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == BLACK)
                {
                    w++;
                }
                break;
            case 6:
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - 2 * p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == BLACK && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == WHITE)
                {
                    w++;
                }
                break;
            }
            /*for (counta = 1; counta <= 8 - 2; counta++)
                {
                    if (mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == mas[counta + 2][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] && mas[counta + 1][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
                    {
                        w++;
                        break;
                    }
                }
                for (counta = 1; counta <= 8; counta++)
                {
                    if (mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY || mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == GUIDE || mas[counta][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == BLACK)
                        ;
                    else
                    {
                        break;
                    }
                }*/
            break;
        }
        switch (ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
        {
        case 1:
            if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY && (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p] == WALL || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p] == WHITE) && (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p] == WALL || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p] == WHITE))
            {
                w++;
            }
            switch (ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
            {
            case 3:
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p] == WHITE && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p] == EMPTY && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + 2 * p] == BLACK)
                {
                    w++;
                }
                break;
            case 6:
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - 2 * p] == BLACK && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p] == EMPTY && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p] == WHITE)
                {
                    w++;
                }
                break;
            }
            /*for (countb = 1; countb <= 8 - 2; countb++)
            {
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][countb] == mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][countb + 2] && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][countb + 1] == ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
                {
                    w++;
                    break;
                }
            }
            for (counta = 1; counta <= 8; counta++)
            {
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][counta] == EMPTY || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][counta] == GUIDE || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][counta] == BLACK)
                    ;
                else
                {
                    break;
                }
            }*/
            break;
        case 8:
            if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] == EMPTY && (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p] == WALL || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p] == WHITE) && (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p] == WALL || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p] == WHITE))
            {
                w++;
            }
            switch (ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
            {
            case 3:
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p] == WHITE && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p] == EMPTY && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + 2 * p] == BLACK)
                {
                    w++;
                }
                break;
            case 6:
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - 2 * p] == BLACK && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p] == EMPTY && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p] == WHITE)
                {
                    w++;
                }
                break;
            }
            /*for (countb = 1; countb <= 8 - 2; countb++)
            {
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][countb] == mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][countb + 2] && mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][countb + 1] == ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]])
                {
                    w++;
                    break;
                }
            }
            for (counta = 1; counta <= 8; counta++)
            {
                if (mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][counta] == EMPTY || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][counta] == GUIDE || mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][counta] == BLACK)
                    ;
                else
                {
                    break;
                }
            }*/

            break;
        }
    }

    //自駒またはどの駒も置かれていないとき
    /*if (counta == 8 || countb == 8)
    {
        w++;
    }*/
    switch (w)
    {
    case 0:
        return ZERO;
        break;

    default:
        return SE;
        break;
    }
    //return w; //if文の条件を満たせば、最終的におそらくw==1で返り値として返される。満たさなければ、w==0である。はず
}
//多分ok
int othello_even_method(int ar_x[][40], int ar_y[][40], int ar_k[][100], int ar_jdg_count[], int ar_times)
{
    //これから先の処理はGUIDEマークが付いていないときの処理としたい（願望）
    int counta, countb;
    int even_method_mas[SIZE][SIZE] = {
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
    static int even_method_c_mas[SIZE][SIZE] = {

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
    //mas[][]の座標をint型のeven_masにコピー
    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            even_method_mas[counta][countb] = mas[counta][countb];
        }
    }

    //2マスごとの空きがあれば、値を下げて、その空きマスの座標にマークする。
    //X軸方向
    for (counta = 1; counta <= 8 - 1; counta++)
    {
        for (countb = 1; countb <= 8 - 1; countb++)
        {
            if ((even_method_mas[counta][countb - 1] != EMPTY && even_method_mas[counta][countb + 2] != EMPTY) && (even_method_mas[counta][countb] == even_method_mas[counta][countb + 1]) && even_method_mas[counta][countb] == EMPTY)
            {
                even_method_mas[counta][countb]--;
                even_method_mas[counta][countb + 1]--;
                countb++;
            }
        }
    }
    //Y軸方向
    for (counta = 1; counta <= 8 - 1; counta++)
    {
        {
            for (countb = 1; countb <= 8 - 1; countb++)
            {
                if ((even_method_mas[countb][counta - 1] != EMPTY && even_method_mas[countb][counta + 2] != EMPTY) && (even_method_mas[countb][counta] == even_method_mas[countb][counta + 1]) && even_method_mas[countb][counta] == EMPTY)
                {
                    even_method_mas[countb][counta]--;
                    even_method_mas[countb][counta + 1]--;
                    counta++;
                }
            }
        }
    }
    //-2が出てきたとき、つまり2マス空きがどこかで重なったとき、その周りの-1は一時的に-3に置き換える
    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            switch (even_method_mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]])
            {
                int p = 1;
            case -2:
                switch (even_method_mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]])
                {
                case -1:
                    even_method_mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] = -3;
                    break;
                }
                switch (even_method_mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p])
                {
                case -1:
                    even_method_mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] - p] = -3;
                    break;
                }
                switch (even_method_mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p])
                {
                case -1:
                    even_method_mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p] = -3;
                    break;
                }
                switch (even_method_mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]])
                {
                case -1:
                    even_method_mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]] + p][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]] = -3;
                    break;
                }
                break;
            }
        }
    }
    //前回-1だったところがBLACK or WHITEに置き換わっていて、空きマスの片方が上記で0になっている場合、その残った空きマス（奇数）は打つべきところであるので、優先するような値を代入する。少なくとも0以外の自然数を代入する。
    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            switch (even_method_c_mas[counta][countb])
            {
            case -1:
                switch (even_method_mas[counta][countb])
                {
                case 0:
                    even_method_mas[counta][countb] = -3;
                    break;
                }
            case -3:
                switch (even_method_mas[counta][countb])
                {
                case 0:
                    even_method_mas[counta][countb] = -3;
                    break;
                }
            }
        }
    }
    //前回比較をしたいので、コピー用にコピーする
    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            even_method_c_mas[counta][countb] = even_method_mas[counta][countb];
        }
    }
    switch (even_method_mas[ar_y[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]][ar_x[ar_times][ar_k[ar_times][ar_jdg_count[ar_times]]]])
    {
    case -1:
        return HU;
        break;
    case -2:
        return HU;
        break;
    case -3:
        return SE;
        break;
    }

    return ZERO;
}
//ok
void othello_est_entire(int ar_jdg_est_entire[], int ar_jdg_t_c[], int ar_times)
{

    int counta, countb;
    int tmp;

    for (counta = 0; counta < ar_jdg_t_c[ar_times] - 1; counta++)
    {
        for (countb = counta + 1; countb < ar_jdg_t_c[ar_times]; countb++)
        {
            if (ar_jdg_est_entire[counta] % 100 <= ar_jdg_est_entire[countb] % 100)
            {
                tmp = ar_jdg_est_entire[counta];
                ar_jdg_est_entire[counta] = ar_jdg_est_entire[countb];
                ar_jdg_est_entire[countb] = tmp;
            }
        }
    }
}

void othello_final_num(int ar_count, int ar_final_num[], int ar_jdg_est_entire[], int ar_jdg_est_REVERSE_num[], int ar_jdg_est_GUIDE_num[], int ar_jdg_t_c[], int ar_times, int ar_EMPTY_count)
{

    int count = 0;
    int counta, countb;
    int tmp;

    switch (ar_EMPTY_count / 6)
    {
    case 0:

        printf("ar_jdg_t_c[ar_times]==%d\nar_count==%d\n", ar_jdg_t_c[ar_times], ar_count);
        ar_final_num[count] = ar_jdg_est_REVERSE_num[count] % 100 /*+ ar_jdg_est_entire[countb] % 100*/;
        ar_final_num[count] += 100 * (ar_jdg_est_REVERSE_num[count] / 10000 /*ar_jdg_est_entire[countb]  / 100*/);
        count++;
        break;

    default:
        printf("ar_jdg_t_c[ar_times]==%d\nar_count==%d\n", ar_jdg_t_c[ar_times], ar_count);
        for (counta = 0; counta < ar_jdg_t_c[ar_times]; counta++)
        {

            for (countb = 0; countb < ar_count; countb++)
            {
                if (ar_jdg_est_entire[counta] / 100 == ar_jdg_est_GUIDE_num[countb] / 10000)
                {
                    ar_final_num[count] = -count + ar_jdg_est_entire[counta] % 100; //ar_jdg_est_REVERSE_num[counta]と違って、優先順位の低いar_jdg_est_GUIDE_num[counta]%100の値をそのまま使うのはよくないと思いました。添字の小さい方からその添字分を引いていく形にする。
                    ar_final_num[count] += 100 * (ar_jdg_est_entire[counta] / 100);

                    count++;
                    printf("count==%d\nar_jdg_est_entire==%d\nar_final_num[count]==%d\n", count, ar_jdg_est_entire[counta], ar_final_num[0]);
                    break;
                }
            }
            if (count == 1)
            {
                break;
            }
        }
        break;
    }

    //並び替え大きいものから
    /*for (counta = 0; counta < ar_jdg_t_c[ar_times] - 1; counta++)
    {
        for (countb = counta + 1; countb < ar_jdg_t_c[ar_times]; countb++)
        {
            if (ar_final_num[counta] % 100 <= ar_final_num[countb] % 100)
            {
                tmp = ar_final_num[counta];
                ar_final_num[counta] = ar_final_num[countb];
                ar_final_num[countb] = tmp;
            }
        }
    }*/
}

int slc(void)
{

    int fis;

    printf("0:先行(=黒)1:後攻(=白)を選んでください. >");
    scanf("%d", &fis);

    switch (fis % 2)
    {
    case 0:
        printf("\nあなたは先行(=黒)です.\n");
        fis = 0;
        break;
    case 1:
        printf("\nあなたは後攻(=白)です.\n");
        fis = 1;
        break;
    }

    return fis;
}

void rep(void)
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
                printf("□ ");
                break;
            case WHITE:
                printf("○ ");
                break;
            case BLACK:
                printf("● ");
                break;
            case GUIDE:
                printf("* ");
                break;
            }
        }
        printf("\n");
    }
    printf("\n");
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

void copy1(void)
{

    int counta, countb;

    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            c_mas1[counta][countb] = mas[counta][countb];
        }
    }
}

void copy1_r(void)
{

    int counta, countb;

    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            mas[counta][countb] = c_mas1[counta][countb];
        }
    }
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

void copy2_r(void)
{

    int counta, countb;

    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            mas[counta][countb] = c_mas2[counta][countb];
        }
    }
}

void del(void)
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

    gl_del_count = gl_count;

    gl_count = 0;
}

int ins(int n)
{

    int tnum;
    int x, y;
    int jdg1, jdg2;
    int ret = 1;
    char ch;

    while (1)
    {

        jdg2 = put2(n);

        if (jdg2 == 0)
        {
            gl_j++;
            printf("\n");
            break;
        }
        switch (n % 2)
        {
        case 0:
            scanf("%d", &tnum);
            break;
        default:
        tnum = othello_AI(n);
        break;
        }

        copy2_r();

        printf("%d\n", tnum);

        if (tnum == 0)
        {
            ret = 0;
            break;
        }

        x = tnum / 10;
        y = tnum % 10;

        gl_x = x;
        gl_y = y;

        jdg1 = check(n);

        if (jdg1 == 0)
        {
            scanf("%c", &ch);
            printf("その場所には打つことは出来ません.\n\n>");
            continue;
        }
        switch (n % 2)
        {
        case 0:
            mas[y][x] = WHITE;
            break;
        case 1:
            mas[y][x] = BLACK;
            break;
        }

        break;
    }

    return ret;
}

int put1(int n)
{

    int counta, countb;
    int jdg;
    int change = 0;

    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            if (mas[counta][countb] != EMPTY)
            {
                continue;
            }
            jdg = put1_upl(counta, countb, n);
            if (jdg == 0)
            {
                change++;
                continue;
            }
            jdg = put1_up(counta, countb, n);
            if (jdg == 0)
            {
                change++;
                continue;
            }
            jdg = put1_upr(counta, countb, n);
            if (jdg == 0)
            {
                change++;
                continue;
            }
            jdg = put1_l(counta, countb, n);
            if (jdg == 0)
            {
                change++;
                continue;
            }
            jdg = put1_r(counta, countb, n);
            if (jdg == 0)
            {
                change++;
                continue;
            }
            jdg = put1_ll(counta, countb, n);
            if (jdg == 0)
            {
                change++;
                continue;
            }
            jdg = put1_un(counta, countb, n);
            if (jdg == 0)
            {
                change++;
                continue;
            }
            jdg = put1_lr(counta, countb, n);
            if (jdg == 0)
            {
                change++;
                continue;
            }
        }
    }
    return change;
}

int put1_upl(int y, int x, int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[y - p][x - p] == EMPTY || mas[y - p][x - p] == WALL || mas[y - p][x - p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y - p][x - p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[y - p][x - p] == EMPTY || mas[y - p][x - p] == WALL || mas[y - p][x - p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y - p][x - p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    if (counta == 0)
    {
        return 1;
    }
    else
    {
        mas[y][x] = GUIDE;
        gl__x[gl_count] = x;
        gl__y[gl_count] = y;
        gl_count++;
        return 0;
    }
}

int put1_up(int y, int x, int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[y - p][x] == EMPTY || mas[y - p][x] == WALL || mas[y - p][x] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y - p][x] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[y - p][x] == EMPTY || mas[y - p][x] == WALL || mas[y - p][x] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y - p][x] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    if (counta == 0)
    {
        return 1;
    }
    else
    {
        mas[y][x] = GUIDE;
        gl__x[gl_count] = x;
        gl__y[gl_count] = y;
        gl_count++;
        return 0;
    }
}

int put1_upr(int y, int x, int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[y - p][x + p] == EMPTY || mas[y - p][x + p] == WALL || mas[y - p][x + p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y - p][x + p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[y - p][x + p] == EMPTY || mas[y - p][x + p] == WALL || mas[y - p][x + p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y - p][x + p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    if (counta == 0)
    {
        return 1;
    }
    else
    {
        mas[y][x] = GUIDE;
        gl__x[gl_count] = x;
        gl__y[gl_count] = y;
        gl_count++;
        return 0;
    }
}

int put1_l(int y, int x, int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[y][x - p] == EMPTY || mas[y][x - p] == WALL || mas[y][x - p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y][x - p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[y][x - p] == EMPTY || mas[y][x - p] == WALL || mas[y][x - p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y][x - p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    if (counta == 0)
    {
        return 1;
    }
    else
    {
        mas[y][x] = GUIDE;
        gl__x[gl_count] = x;
        gl__y[gl_count] = y;
        gl_count++;
        return 0;
    }
}

int put1_r(int y, int x, int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[y][x + p] == EMPTY || mas[y][x + p] == WALL || mas[y][x + p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y][x + p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[y][x + p] == EMPTY || mas[y][x + p] == WALL || mas[y][x + p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y][x + p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    if (counta == 0)
    {
        return 1;
    }
    else
    {
        mas[y][x] = GUIDE;
        gl__x[gl_count] = x;
        gl__y[gl_count] = y;
        gl_count++;
        return 0;
    }
}

int put1_ll(int y, int x, int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[y + p][x - p] == EMPTY || mas[y + p][x - p] == WALL || mas[y + p][x - p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y + p][x - p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[y + p][x - p] == EMPTY || mas[y + p][x - p] == WALL || mas[y + p][x - p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y + p][x - p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    if (counta == 0)
    {
        return 1;
    }
    else
    {
        mas[y][x] = GUIDE;
        gl__x[gl_count] = x;
        gl__y[gl_count] = y;
        gl_count++;
        return 0;
    }
}

int put1_un(int y, int x, int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[y + p][x] == EMPTY || mas[y + p][x] == WALL || mas[y + p][x] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y + p][x] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[y + p][x] == EMPTY || mas[y + p][x] == WALL || mas[y + p][x] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y + p][x] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    if (counta == 0)
    {
        return 1;
    }
    else
    {
        mas[y][x] = GUIDE;
        gl__x[gl_count] = x;
        gl__y[gl_count] = y;
        gl_count++;
        return 0;
    }
}

int put1_lr(int y, int x, int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[y + p][x + p] == EMPTY || mas[y + p][x + p] == WALL || mas[y + p][x + p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y + p][x + p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[y + p][x + p] == EMPTY || mas[y + p][x + p] == WALL || mas[y + p][x + p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y + p][x + p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    if (counta == 0)
    {
        return 1;
    }
    else
    {
        mas[y][x] = GUIDE;
        gl__x[gl_count] = x;
        gl__y[gl_count] = y;
        gl_count++;
        return 0;
    }
}

int put2(int n)
{

    int counta, countb;
    int jdg;
    int change = 0;

    for (counta = 1; counta <= 8; counta++)
    {
        for (countb = 1; countb <= 8; countb++)
        {
            if (mas[counta][countb] != EMPTY)
            {
                continue;
            }
            jdg = put2_upl(counta, countb, n);
            if (jdg == 0)
            {
                change++;
                continue;
            }
            jdg = put2_up(counta, countb, n);
            if (jdg == 0)
            {
                change++;
                continue;
            }
            jdg = put2_upr(counta, countb, n);
            if (jdg == 0)
            {
                change++;
                continue;
            }
            jdg = put2_l(counta, countb, n);
            if (jdg == 0)
            {
                change++;
                continue;
            }
            jdg = put2_r(counta, countb, n);
            if (jdg == 0)
            {
                change++;
                continue;
            }
            jdg = put2_ll(counta, countb, n);
            if (jdg == 0)
            {
                change++;
                continue;
            }
            jdg = put2_un(counta, countb, n);
            if (jdg == 0)
            {
                change++;
                continue;
            }
            jdg = put2_lr(counta, countb, n);
            if (jdg == 0)
            {
                change++;
                continue;
            }
        }
    }
    return change;
}

int put2_upl(int y, int x, int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[y - p][x - p] == EMPTY || mas[y - p][x - p] == WALL || mas[y - p][x - p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y - p][x - p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[y - p][x - p] == EMPTY || mas[y - p][x - p] == WALL || mas[y - p][x - p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y - p][x - p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    switch (counta)
    {
    case 0:
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

int put2_up(int y, int x, int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[y - p][x] == EMPTY || mas[y - p][x] == WALL || mas[y - p][x] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y - p][x] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[y - p][x] == EMPTY || mas[y - p][x] == WALL || mas[y - p][x] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y - p][x] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    switch (counta)
    {
    case 0:
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

int put2_upr(int y, int x, int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[y - p][x + p] == EMPTY || mas[y - p][x + p] == WALL || mas[y - p][x + p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y - p][x + p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[y - p][x + p] == EMPTY || mas[y - p][x + p] == WALL || mas[y - p][x + p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y - p][x + p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    switch (counta)
    {
    case 0:
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

int put2_l(int y, int x, int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[y][x - p] == EMPTY || mas[y][x - p] == WALL || mas[y][x - p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y][x - p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[y][x - p] == EMPTY || mas[y][x - p] == WALL || mas[y][x - p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y][x - p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    switch (counta)
    {
    case 0:
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

int put2_r(int y, int x, int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[y][x + p] == EMPTY || mas[y][x + p] == WALL || mas[y][x + p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y][x + p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[y][x + p] == EMPTY || mas[y][x + p] == WALL || mas[y][x + p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y][x + p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    switch (counta)
    {
    case 0:
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

int put2_ll(int y, int x, int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[y + p][x - p] == EMPTY || mas[y + p][x - p] == WALL || mas[y + p][x - p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y + p][x - p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[y + p][x - p] == EMPTY || mas[y + p][x - p] == WALL || mas[y + p][x - p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y + p][x - p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    switch (counta)
    {
    case 0:
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

int put2_un(int y, int x, int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[y + p][x] == EMPTY || mas[y + p][x] == WALL || mas[y + p][x] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y + p][x] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[y + p][x] == EMPTY || mas[y + p][x] == WALL || mas[y + p][x] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y + p][x] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    switch (counta)
    {
    case 0:
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

int put2_lr(int y, int x, int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[y + p][x + p] == EMPTY || mas[y + p][x + p] == WALL || mas[y + p][x + p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y + p][x + p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[y + p][x + p] == EMPTY || mas[y + p][x + p] == WALL || mas[y + p][x + p] == GUIDE)
            {
                counta = 0;
                break;
            }
            else if (mas[y + p][x + p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    switch (counta)
    {
    case 0:
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

//置けるかどうかの判定
int check(int n)
{

    if (mas[gl_y][gl_x] == WHITE || mas[gl_y][gl_x] == BLACK)
    {
        return 0;
    }

    int check_num = 0;

    check_num += check_upl(n);
    check_num += check_up(n);
    check_num += check_upr(n);
    check_num += check_l(n);
    check_num += check_r(n);
    check_num += check_ll(n);
    check_num += check_un(n);
    check_num += check_lr(n);

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

int check_upl(int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[gl_y - p][gl_x - p] == EMPTY || mas[gl_y - p][gl_x - p] == WALL)
            {
                counta = 0;
                break;
            }
            else if (mas[gl_y - p][gl_x - p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[gl_y - p][gl_x - p] == EMPTY || mas[gl_y - p][gl_x - p] == WALL)
            {
                counta = 0;
                break;
            }
            else if (mas[gl_y - p][gl_x - p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    return counta;
}

int check_up(int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[gl_y - p][gl_x] == EMPTY || mas[gl_y - p][gl_x] == WALL)
            {
                counta = 0;
                break;
            }
            else if (mas[gl_y - p][gl_x] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[gl_y - p][gl_x] == EMPTY || mas[gl_y - p][gl_x] == WALL)
            {
                counta = 0;
                break;
            }
            else if (mas[gl_y - p][gl_x] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    return counta;
}

int check_upr(int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[gl_y - p][gl_x + p] == EMPTY || mas[gl_y - p][gl_x + p] == WALL)
            {
                counta = 0;
                break;
            }
            else if (mas[gl_y - p][gl_x + p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[gl_y - p][gl_x + p] == EMPTY || mas[gl_y - p][gl_x + p] == WALL)
            {
                counta = 0;
                break;
            }
            else if (mas[gl_y - p][gl_x + p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    return counta;
}

int check_l(int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[gl_y][gl_x - p] == EMPTY || mas[gl_y][gl_x - p] == WALL)
            {
                counta = 0;
                break;
            }
            else if (mas[gl_y][gl_x - p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[gl_y][gl_x - p] == EMPTY || mas[gl_y][gl_x - p] == WALL)
            {
                counta = 0;
                break;
            }
            else if (mas[gl_y][gl_x - p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    return counta;
}

int check_r(int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[gl_y][gl_x + p] == EMPTY || mas[gl_y][gl_x + p] == WALL)
            {
                counta = 0;
                break;
            }
            else if (mas[gl_y][gl_x + p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[gl_y][gl_x + p] == EMPTY || mas[gl_y][gl_x + p] == WALL)
            {
                counta = 0;
                break;
            }
            else if (mas[gl_y][gl_x + p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    return counta;
}

int check_ll(int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[gl_y + p][gl_x - p] == EMPTY || mas[gl_y + p][gl_x - p] == WALL)
            {
                counta = 0;
                break;
            }
            else if (mas[gl_y + p][gl_x - p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[gl_y + p][gl_x - p] == EMPTY || mas[gl_y + p][gl_x - p] == WALL)
            {
                counta = 0;
                break;
            }
            else if (mas[gl_y + p][gl_x - p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    return counta;
}

int check_un(int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[gl_y + p][gl_x] == EMPTY || mas[gl_y + p][gl_x] == WALL)
            {
                counta = 0;
                break;
            }
            else if (mas[gl_y + p][gl_x] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[gl_y + p][gl_x] == EMPTY || mas[gl_y + p][gl_x] == WALL)
            {
                counta = 0;
                break;
            }
            else if (mas[gl_y + p][gl_x] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    return counta;
}

int check_lr(int n)
{

    int p = 1;
    int counta = 0;

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[gl_y + p][gl_x + p] == EMPTY || mas[gl_y + p][gl_x + p] == WALL)
            {
                counta = 0;
                break;
            }
            else if (mas[gl_y + p][gl_x + p] == WHITE)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[gl_y + p][gl_x + p] == EMPTY || mas[gl_y + p][gl_x + p] == WALL)
            {
                counta = 0;
                break;
            }
            else if (mas[gl_y + p][gl_x + p] == BLACK)
            {
                break;
            }

            counta++;
            p++;
        }
    }
    return counta;
}

int cal(int n)
{

    int c_mas1ount = 0;

    c_mas1ount += cal_upl(n);
    c_mas1ount += cal_up(n);
    c_mas1ount += cal_upr(n);
    c_mas1ount += cal_l(n);
    c_mas1ount += cal_r(n);
    c_mas1ount += cal_ll(n);
    c_mas1ount += cal_un(n);
    c_mas1ount += cal_lr(n);

    return c_mas1ount;
}

int cal_upl(int n)
{

    int p = 1;
    int counta = 0;
    int ar_rev_x[20], ar_rev_y[20];

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[gl_y - p][gl_x - p] == EMPTY || mas[gl_y - p][gl_x - p] == WALL || mas[gl_y - p][gl_x - p] == GUIDE)
            {
                break;
            }
            else if (mas[gl_y - p][gl_x - p] == BLACK)
            {
                ar_rev_x[counta] = gl_x - p;
                ar_rev_y[counta] = gl_y - p;
            }
            else
            {
                rev(ar_rev_x, ar_rev_y, n, counta);
                break;
            }
            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[gl_y - p][gl_x - p] == EMPTY || mas[gl_y - p][gl_x - p] == WALL || mas[gl_y - p][gl_x - p] == GUIDE)
            {
                break;
            }
            else if (mas[gl_y - p][gl_x - p] == WHITE)
            {
                ar_rev_x[counta] = gl_x - p;
                ar_rev_y[counta] = gl_y - p;
            }
            else
            {
                rev(ar_rev_x, ar_rev_y, n, counta);
                break;
            }

            counta++;
            p++;
        }
    }

    return counta;
}

int cal_up(int n)
{

    int p = 1;
    int counta = 0;
    int ar_rev_x[20], ar_rev_y[20];

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[gl_y - p][gl_x] == EMPTY || mas[gl_y - p][gl_x] == WALL || mas[gl_y - p][gl_x] == GUIDE)
            {
                break;
            }
            else if (mas[gl_y - p][gl_x] == BLACK)
            {
                ar_rev_x[counta] = gl_x;
                ar_rev_y[counta] = gl_y - p;
            }
            else
            {
                rev(ar_rev_x, ar_rev_y, n, counta);
                break;
            }
            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[gl_y - p][gl_x] == EMPTY || mas[gl_y - p][gl_x] == WALL || mas[gl_y - p][gl_x] == GUIDE)
            {
                break;
            }
            else if (mas[gl_y - p][gl_x] == WHITE)
            {
                ar_rev_x[counta] = gl_x;
                ar_rev_y[counta] = gl_y - p;
            }
            else
            {
                rev(ar_rev_x, ar_rev_y, n, counta);
                break;
            }
            counta++;
            p++;
        }
    }

    return counta;
}

int cal_upr(int n)
{

    int p = 1;
    int counta = 0;
    int ar_rev_x[20], ar_rev_y[20];

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[gl_y - p][gl_x + p] == EMPTY || mas[gl_y - p][gl_x + p] == WALL || mas[gl_y - p][gl_x + p] == GUIDE)
            {
                break;
            }
            else if (mas[gl_y - p][gl_x + p] == BLACK)
            {
                ar_rev_x[counta] = gl_x + p;
                ar_rev_y[counta] = gl_y - p;
            }
            else
            {
                rev(ar_rev_x, ar_rev_y, n, counta);
                break;
            }
            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[gl_y - p][gl_x + p] == EMPTY || mas[gl_y - p][gl_x + p] == WALL || mas[gl_y - p][gl_x + p] == GUIDE)
            {
                break;
            }
            else if (mas[gl_y - p][gl_x + p] == WHITE)
            {
                ar_rev_x[counta] = gl_x + p;
                ar_rev_y[counta] = gl_y - p;
            }
            else
            {
                rev(ar_rev_x, ar_rev_y, n, counta);
                break;
            }

            counta++;
            p++;
        }
    }

    return counta;
}

int cal_l(int n)
{

    int p = 1;
    int counta = 0;
    int ar_rev_x[20], ar_rev_y[20];

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[gl_y][gl_x - p] == EMPTY || mas[gl_y][gl_x - p] == WALL || mas[gl_y][gl_x - p] == GUIDE)
            {
                break;
            }
            else if (mas[gl_y][gl_x - p] == BLACK)
            {
                ar_rev_x[counta] = gl_x - p;
                ar_rev_y[counta] = gl_y;
            }
            else
            {
                rev(ar_rev_x, ar_rev_y, n, counta);
                break;
            }
            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[gl_y][gl_x - p] == EMPTY || mas[gl_y][gl_x - p] == WALL || mas[gl_y][gl_x - p] == GUIDE)
            {
                break;
            }
            else if (mas[gl_y][gl_x - p] == WHITE)
            {
                ar_rev_x[counta] = gl_x - p;
                ar_rev_y[counta] = gl_y;
            }
            else
            {
                rev(ar_rev_x, ar_rev_y, n, counta);
                break;
            }

            counta++;
            p++;
        }
    }

    return counta;
}

int cal_r(int n)
{

    int p = 1;
    int counta = 0;
    int ar_rev_x[20], ar_rev_y[20];

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[gl_y][gl_x + p] == EMPTY || mas[gl_y][gl_x + p] == WALL || mas[gl_y][gl_x + p] == GUIDE)
            {
                break;
            }
            else if (mas[gl_y][gl_x + p] == BLACK)
            {
                ar_rev_x[counta] = gl_x + p;
                ar_rev_y[counta] = gl_y;
            }
            else
            {
                rev(ar_rev_x, ar_rev_y, n, counta);
                break;
            }
            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[gl_y][gl_x + p] == EMPTY || mas[gl_y][gl_x + p] == WALL || mas[gl_y][gl_x + p] == GUIDE)
            {
                break;
            }
            else if (mas[gl_y][gl_x + p] == WHITE)
            {
                ar_rev_x[counta] = gl_x + p;
                ar_rev_y[counta] = gl_y;
            }
            else
            {
                rev(ar_rev_x, ar_rev_y, n, counta);
                break;
            }

            counta++;
            p++;
        }
    }

    return counta;
}

int cal_ll(int n)
{

    int p = 1;
    int counta = 0;
    int ar_rev_x[20], ar_rev_y[20];

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[gl_y + p][gl_x - p] == EMPTY || mas[gl_y + p][gl_x - p] == WALL || mas[gl_y + p][gl_x - p] == GUIDE)
            {
                break;
            }
            else if (mas[gl_y + p][gl_x - p] == BLACK)
            {
                ar_rev_x[counta] = gl_x - p;
                ar_rev_y[counta] = gl_y + p;
            }
            else
            {
                rev(ar_rev_x, ar_rev_y, n, counta);
                break;
            }
            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[gl_y + p][gl_x - p] == EMPTY || mas[gl_y + p][gl_x - p] == WALL || mas[gl_y + p][gl_x - p] == GUIDE)
            {
                break;
            }
            else if (mas[gl_y + p][gl_x - p] == WHITE)
            {
                ar_rev_x[counta] = gl_x - p;
                ar_rev_y[counta] = gl_y + p;
            }
            else
            {
                rev(ar_rev_x, ar_rev_y, n, counta);
                break;
            }

            counta++;
            p++;
        }
    }

    return counta;
}

int cal_un(int n)
{

    int p = 1;
    int counta = 0;
    int ar_rev_x[20], ar_rev_y[20];

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[gl_y + p][gl_x] == EMPTY || mas[gl_y + p][gl_x] == WALL || mas[gl_y + p][gl_x] == GUIDE)
            {
                break;
            }
            else if (mas[gl_y + p][gl_x] == BLACK)
            {
                ar_rev_x[counta] = gl_x;
                ar_rev_y[counta] = gl_y + p;
            }
            else
            {
                rev(ar_rev_x, ar_rev_y, n, counta);
                break;
            }
            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[gl_y + p][gl_x] == EMPTY || mas[gl_y + p][gl_x] == WALL || mas[gl_y + p][gl_x] == GUIDE)
            {
                break;
            }
            else if (mas[gl_y + p][gl_x] == WHITE)
            {
                ar_rev_x[counta] = gl_x;
                ar_rev_y[counta] = gl_y + p;
            }
            else
            {
                rev(ar_rev_x, ar_rev_y, n, counta);
                break;
            }
            counta++;
            p++;
        }
    }

    return counta;
}

int cal_lr(int n)
{

    int p = 1;
    int counta = 0;
    int ar_rev_x[20], ar_rev_y[20];

    if (n % 2 == 0)
    {
        while (1)
        {
            if (mas[gl_y + p][gl_x + p] == EMPTY || mas[gl_y + p][gl_x + p] == WALL || mas[gl_y + p][gl_x + p] == GUIDE)
            {
                break;
            }
            else if (mas[gl_y + p][gl_x + p] == BLACK)
            {
                ar_rev_x[counta] = gl_x + p;
                ar_rev_y[counta] = gl_y + p;
            }
            else
            {
                rev(ar_rev_x, ar_rev_y, n, counta);
                break;
            }
            counta++;
            p++;
        }
    }
    else
    {
        while (1)
        {
            if (mas[gl_y + p][gl_x + p] == EMPTY || mas[gl_y + p][gl_x + p] == WALL || mas[gl_y + p][gl_x + p] == GUIDE)
            {
                break;
            }
            else if (mas[gl_y + p][gl_x + p] == WHITE)
            {
                ar_rev_x[counta] = gl_x + p;
                ar_rev_y[counta] = gl_y + p;
            }
            else
            {
                rev(ar_rev_x, ar_rev_y, n, counta);
                break;
            }

            counta++;
            p++;
        }
    }

    return counta;
}

void rev(int x[], int y[], int n, int c)
{

    int t = 0;

    if (n % 2 == 0)
    {
        while (t < c)
        {
            mas[y[t]][x[t]] = WHITE;
            t++;
        }
    }
    else
    {
        while (t < c)
        {
            mas[y[t]][x[t]] = BLACK;
            t++;
        }
    }
}

void res(int j)
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

    printf("黒(%d) 白(%d)\t", black, white);

    switch (j)
    {
    case 1:
        if (black > white)
        {
            printf("黒の勝利です.\n");
        }
        else if (black < white)
        {
            printf("白の勝利です.\n");
        }
        else
        {
            printf("引き分けです.\n");
        }
        break;
    }
}
