#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>


#define BOARD_SIZE 8
#define EMPTY -1
#define BLACK 0
#define WHITE 1
#define GUIDE 5

#define DIRECTION_SIZE 8
#define INPUT_SIZE 30
#define SLEEP_TIME 0.5 * 1000000

// Search
// 20がおそらく限界
#define REST_BOARD_TO_SWITCH_Search 16
#define WIN 2
#define DRAW 1
#define LOSE 0

//何手先まで読むか
#define FUTURE_MOVE_COUNT 6

int opponentSearch();
int canPutCorner();
int searchNotLose();
void displaySearchResult();
int searchCanPutDiscCnt();
// Search

void displayGameExplanation();
void play();
void selectPlayFirstSecond();
void structBoardInit();
void addCanPutGuide();
bool isOutBoard();
bool isEndGame();
void displayBoard();
void setDisc();
void putDiscOnBoard();
void displayResult();

struct turn{
    int count;
    // my move, not oppenent move
    int myDiscColor;
};
struct board{
    int board[BOARD_SIZE + 1][BOARD_SIZE + 1];
    int blackDiscCnt;
    int whiteDiscCnt;
    int guideCnt;
    bool isAlreadySkiped;
    void (*_init)();
};

char discName[2][5] = {"黒","白"};
// direction
int dy[DIRECTION_SIZE]={-1, -1, -1, 0, 0, 1, 1, 1};
int dx[DIRECTION_SIZE]={-1, 0, 1, -1, 1, -1, 0 ,1};

int main(void){

    displayGameExplanation();
    play();

    return 0;
}

void displayGameExplanation(){
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
}

void play(){
    struct turn turn;
    turn.count = 0;
    // 色を決める→先攻は黒，後攻は白という決まりがある
    selectPlayFirstSecond(&turn);

    struct board bd;
    bd._init = structBoardInit;
    bd._init(&bd);

    bool isEndGameFlag = false;
    while(!isEndGameFlag){
        // 黒→白の順
        for(int discColor = 0; discColor < 2; discColor++){
            turn.count++;
            addCanPutGuide(discColor, &bd);
            displayBoard(&bd);
            if(isEndGame(&bd)){
                isEndGameFlag = true;
                break;
            }
            setDisc(&bd, discColor, &turn);
        }
    }

    //結果出力
    displayResult(turn.myDiscColor, &bd);
}

void selectPlayFirstSecond(struct turn *turn){
    char firstOrSecond[INPUT_SIZE];
    while(1){
        printf("先攻(黒石) 後攻(白石)を決めてください．先攻→ f , 後攻→ s を入力 > ");
        scanf("%s", firstOrSecond);
        // printf("%s", firstOrSecond);

        if((firstOrSecond[0] == 'f' || firstOrSecond[0] == 's') && firstOrSecond[1] == '\0')break;
        printf("入力が正しくありません\n");
    }

    if(firstOrSecond[0] == 'f')turn->myDiscColor=BLACK;
    else turn->myDiscColor=WHITE;
}

void structBoardInit(struct board *bd){
    /* 以下の並びが初期配置
        白黒
        黒白
    */
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            bd->board[i][j] = -1;
        }
    }
    bd->board[(BOARD_SIZE-1)/2][BOARD_SIZE/2] = bd->board[BOARD_SIZE/2][(BOARD_SIZE-1)/2] = BLACK;
    bd->board[(BOARD_SIZE-1)/2][(BOARD_SIZE-1)/2] = bd->board[BOARD_SIZE/2][BOARD_SIZE/2] = WHITE;

    bd->blackDiscCnt = bd->whiteDiscCnt = 2;
    bd->guideCnt = 0;
    bd->isAlreadySkiped = false;
}

void addCanPutGuide(int myDisc, struct board *bd){
    bd->guideCnt = 0;
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(bd->board[i][j] == GUIDE)bd->board[i][j] = EMPTY;
            if(bd->board[i][j] == EMPTY){
                bool isCanPutFlag = false;
                //8方向について調べる
                for(int k = 0; k < DIRECTION_SIZE; k++){
                    int sy = i + dy[k], sx = j + dx[k];
                    if(isOutBoard(sy, sx))continue;
                    if(bd->board[sy][sx] == !myDisc){

                        for(int _ = 0; _ < BOARD_SIZE -2 ; _++){
                            sy += dy[k], sx += dx[k];
                            if(isOutBoard(sy, sx))break;
                            if(bd->board[sy][sx] == EMPTY || bd->board[sy][sx] == GUIDE)break;

                            if(bd->board[sy][sx] == myDisc){
                                bd->board[i][j] = GUIDE;
                                bd->guideCnt++;
                                isCanPutFlag = true;
                                break;
                            }
                        }

                        if(isCanPutFlag)break;
                    }
                }
            }
        }
    }
}

bool isOutBoard(int y, int x){
    if((y < 0 || y >= BOARD_SIZE) || (x < 0 || x >= BOARD_SIZE))return true;

    return false;
}

//終了条件：両者どこも置けなくなった場合（盤面全てに石を置いたとき，盤面は空いているが両者置けないとき）
bool isEndGame(struct board *bd){
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(bd->board[i][j] == GUIDE){
                bd->isAlreadySkiped = false;
                return false;
            }
        }
    }

    if(bd->blackDiscCnt + bd->whiteDiscCnt != BOARD_SIZE * BOARD_SIZE){
        if(!bd->isAlreadySkiped){
            bd->isAlreadySkiped = true;
            return false;
        }
        // printf("両者置けないため");
    }
    // printf("試合終了\n");

    return true;
}

void displayBoard(struct board *bd){
    printf("  ");
    for(int i = 0; i < BOARD_SIZE; i++)printf("%2d", i + 1);
    printf("\n");
    for(int i = 0; i < BOARD_SIZE; i++){
        printf("%d ", i + 1);
        for(int j = 0; j < BOARD_SIZE; j++){
            printf("\x1b[42m"); /* 背景色を緑に */
            switch (bd->board[i][j]){
                case EMPTY:
                    printf("□ ");
                    break;
                case BLACK:
                    printf("\x1b[30m"); /* 前景色を黒に */
                    printf("● ");
                    break;
                case WHITE:
                    printf("\x1b[37m"); /* 前景色を白に */
                    printf("○ ");
                    break;
                case GUIDE:
                    printf("\x1b[35m"); /* 前景色をマゼンタに */
                    printf("※ ");
                    break;
            }
            printf("\x1b[39m"); /* 前景色をデフォルトに戻す */
            printf("\x1b[49m"); /* 背景色をデフォルトに戻す */
        }
        printf("\n");
    }
    // usleep(SLEEP_TIME);
}

void setDisc(struct board *bd, int disc, struct turn *_turn){

    if(bd->guideCnt == 0){
        printf("置く場所がありません．手番が相手に移ります\n");
        return;
    }
    int y, x;
    // 石を置く位置を決める
    if(disc == _turn->myDiscColor){
        // ユーザ入力
        char inputCoordinate[INPUT_SIZE];
        while(1){
            printf("%s石をどこに置きますか？ > ", discName[_turn->myDiscColor]);
            scanf("%s", inputCoordinate);
            if(isdigit(inputCoordinate[0]) &&  isdigit(inputCoordinate[1]) && inputCoordinate[2] == '\0'){

                x = (inputCoordinate[0] - '0') - 1;
                y = (inputCoordinate[1] - '0') - 1;
                if(bd->board[y][x]==GUIDE){
                    break;
                }
                printf("(%d, %d)は置くことが出来ない場所です\n", x + 1, y + 1);
            }else printf("入力が正しくありません\n");
        }
        printf("\n");

        //敵がコマをランダムに置く(デバッグ用)
        // int canPutSize=0;
        // int X[30],Y[30];
        // for(int i = 0; i < BOARD_SIZE; i++){
        //     for(int j = 0; j < BOARD_SIZE; j++){
        //         if(bd->board[i][j]==GUIDE){
        //             X[canPutSize]=j;
        //             Y[canPutSize]=i;
        //             canPutSize++;
        //         }
        //     }
        // }
        // srand(time(NULL));
        // int num = rand() % canPutSize;
        // x = X[num], y = Y[num];

        // 敵がコマを探索結果で置く(デバッグ用)
        // struct board sBd = *bd;
        // int coordinate = opponentSearch(&sBd,disc);
        // x = coordinate / 10;
        // y = coordinate % 10;
        // printf("\n");
        // printf("コンピュータは(%d, %d)に置きました\n", x + 1, y + 1);
    }else{
        //敵がコマを置く
        struct board sBd = *bd;
        int coordinate = opponentSearch(&sBd,disc);
        x = coordinate / 10;
        y = coordinate % 10;

        printf("\n");
        printf("コンピュータは(%d, %d)に置きました\n", x + 1, y + 1);
    }

    putDiscOnBoard(disc, bd, x, y);

    printf("黒石:%d, 白石:%d\n", bd->blackDiscCnt, bd->whiteDiscCnt);

}

void putDiscOnBoard(int disc,struct board *bd, int x, int y){
    bd->board[y][x] = disc;
    if(disc == BLACK)bd->blackDiscCnt++;
    else bd->whiteDiscCnt++;

    // 石を置き裏返す処理
    for(int i = 0; i < DIRECTION_SIZE; i++){
        int sy = y, sx = x;
        for(int j = 1; j < BOARD_SIZE; j++){
            sy += dy[i], sx += dx[i];
            if(isOutBoard(sy, sx))break;
            if(bd->board[sy][sx] == EMPTY || bd->board[sy][sx] == GUIDE)break;

            if(bd->board[sy][sx] == disc){
                for(int k = j; k > 1; k--){
                    sy -= dy[i], sx -= dx[i];
                    bd->board[sy][sx] = disc;
                    if(disc == BLACK){
                        bd->blackDiscCnt++;
                        bd->whiteDiscCnt--;
                    }else{
                        bd->whiteDiscCnt++;
                        bd->blackDiscCnt--;
                    }
                }
                break;
            }
        }
    }
}

void displayResult(int myDisc, struct board *bd){
    printf("黒石 %d, 白石 %d\n",bd->blackDiscCnt, bd->whiteDiscCnt);
    if(bd->blackDiscCnt > bd->whiteDiscCnt){
        if(myDisc == BLACK)printf("勝ち\n");
        else printf("負け\n");
    }
    else if( bd->blackDiscCnt < bd->whiteDiscCnt){
        if(myDisc == WHITE)printf("勝ち\n");
        else printf("負け\n");
    }
    else {
        printf("引き分け\n");
    }

}


//TODO: 過去探索した盤面の再利用
int opponentSearch(struct board *bd, int disc){
    int depth = 0;

    int corner = canPutCorner(bd);
    if(corner >= 0)return corner;

    // true: DFS(depth-first search），
    // false:  REST_BOARD_TO_SWITCH_Search手先の相手が置ける石の数の最大値が最小 + (開放度理論)
    if(BOARD_SIZE * BOARD_SIZE - (bd->blackDiscCnt + bd->whiteDiscCnt) <= REST_BOARD_TO_SWITCH_Search){
        printf("深さ優先探索モード\n");
        return searchNotLose(bd, disc, depth);
    }else{
        // pass by value
        return searchCanPutDiscCnt(bd, disc, depth);
    }
}

int searchNotLose(struct board *bd, int myDisc, int depth){
    depth ++;
    // 全マス埋まったときの処理
    if(isEndGame(bd)){
        if(myDisc == BLACK){
            if(bd->blackDiscCnt > bd->whiteDiscCnt)return WIN;
            else if(bd->blackDiscCnt < bd->whiteDiscCnt)return LOSE;
            else return DRAW;
        }else{
            if(bd->whiteDiscCnt > bd->blackDiscCnt)return WIN;
            else if(bd->whiteDiscCnt < bd->blackDiscCnt)return LOSE;
            else return DRAW;
        }
    }

    int disc = (depth % 2 == 1 ? myDisc:!myDisc);
    // skipした場合一つターンを飛ばす
    if(bd->guideCnt == 0){
        depth++;
        disc = (depth % 2 == 1 ? myDisc:!myDisc);
        addCanPutGuide(disc, bd);
        // displayBoard(bd);
    }
    // skipしたがターンが移った先でも置けない場合は終了
    if(isEndGame(bd)){
        if(myDisc == BLACK){
            if(bd->blackDiscCnt > bd->whiteDiscCnt)return WIN;
            else if(bd->blackDiscCnt < bd->whiteDiscCnt)return LOSE;
            else return DRAW;
        }else{
            if(bd->whiteDiscCnt > bd->blackDiscCnt)return WIN;
            else if(bd->whiteDiscCnt < bd->blackDiscCnt)return LOSE;
            else return DRAW;
        }
    }

    int myAttackRes = -1, opponentAttackRes=10;
    int notLoseX = 0, notLoseY = 0;
    int asdf=0;
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(bd->board[i][j] == GUIDE){
                // asdf++;
                struct board sBd = *bd;
                putDiscOnBoard(disc, &sBd, j, i);
                addCanPutGuide(!disc, &sBd);
                // displayBoard(&sBd);
                int tempResult = searchNotLose(&sBd, myDisc, depth);
                if(disc == myDisc){
                    //WIN→DRAW→LOSEの優先度で返す
                    if(myAttackRes < tempResult){
                        myAttackRes = tempResult;
                        notLoseX = j, notLoseY = i;
                        asdf++;
                    }
                    if(myAttackRes == WIN){
                        if(depth == 1){
                            displaySearchResult(myAttackRes);
                            return 10 * notLoseX + notLoseY;
                        }
                        return myAttackRes;
                    }
                }else{
                    //LOSE→DRAW→WINの優先度で返す
                    if(opponentAttackRes > tempResult)opponentAttackRes = tempResult;
                    if(opponentAttackRes == LOSE)return opponentAttackRes;
                }
            }
        }
        // asdf++;
    }

    if(depth == 1){
        displayBoard(bd);
        displaySearchResult(myAttackRes);
        return 10 * notLoseX + notLoseY;
    }

    if(disc == myDisc)return myAttackRes;
    else return opponentAttackRes;
}

void displaySearchResult(int res){
    if(res == WIN)printf("予測：コンピュータの勝ち\n");
    else if(res == LOSE)printf("予測：コンピュータの負け\n");
    else printf("予測：引き分け\n");
}

int searchCanPutDiscCnt(struct board *bd,int myDisc, int depth){
    depth ++;
    if(depth == FUTURE_MOVE_COUNT){
        return bd->guideCnt;
    }

    int whenMinX,whenMinY;
    int min =1000;
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(bd->board[i][j] == GUIDE){
                int disc = (depth % 2 == 1 ? myDisc:!myDisc);

                struct board sBd = *bd;
                putDiscOnBoard(disc, &sBd, j, i);
                addCanPutGuide(!disc, &sBd);
                int tempMinGuideCnt = searchCanPutDiscCnt(&sBd, myDisc, depth);
                if(tempMinGuideCnt <= min){
                    min = tempMinGuideCnt;
                    whenMinX = j, whenMinY = i;
                }
            }
        }
    }

    if(depth == 1){
        //TODO:①角優先的に置く
        //TODO:角の周辺の優先度を下げる
        /*NOTE: 各min, whenMinX,whenMinYを配列で保存．
            - minで昇順ソート
            - 値が同じだが，角周辺を避ける

            ＋α 探索時も角優先で探索し，処理時間・メモリの軽減
        */
        return 10 * whenMinX + whenMinY;
    }
    if(depth % 2 == 0 && min == 1000)return bd->guideCnt;

    return min;

}

int canPutCorner(struct board *bd){
    if(bd->board[0][0] == GUIDE)return 0;
    if(bd->board[0][BOARD_SIZE - 1] == GUIDE)return 10 * (BOARD_SIZE - 1);
    if(bd->board[BOARD_SIZE - 1][0] == GUIDE)return BOARD_SIZE - 1;
    if(bd->board[BOARD_SIZE - 1][BOARD_SIZE - 1] == GUIDE)return 10 * (BOARD_SIZE - 1) + (BOARD_SIZE - 1);

    return -1;
}