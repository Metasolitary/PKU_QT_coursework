#include<stdio.h>
#include<iostream>
#include<memory.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
using namespace std;
struct POSITION {
    int x = 0; int y = 0;
};
struct Move {
    int x = 0; int y = 0;
} move;
char checkerboard[10][10] = { '\0' };//����
int value[3] = { 0 };//�����ֵ
const char chessman[3] = { '#','*','%' };//���ӷ���
int qi[10][10] = { 0 };//���ݹ�����
int x = 0; int y = 0;//����
bool ValidMove[3][10][10] = { false };//�Ϸ��������飬[���][x][y]
int row = 9;
int whiteflag = 0;
int tempmovex; int tempmovey;
const int MaxDepth = 3;
POSITION gameRecord[100][100];
int gameCount = 0;
int stopFlag = 0;
int withdrawFlag = 0;
int getFlag = 0;
int turn = 0;
int rotation = 0;
void draw();
void ApplyMove(int player, int x, int y);
int evaluate(int player);
int opponent(int player);
void GetMove();
bool Qi(int x, int y, int player);
int NegaMax(int player, int depth, int a, int b);
void CancelMove(int x, int y);
void printf_blue(const char s);
void printf_red(const char s);
bool judge(int x, int y, int player);
void menu();
void getPlayer(int* p);
void getNum(char* p);
void NoGo(int player);
void readRecord(int n);
void memset_checkerboard();
void printChessman_turn(int i);
int main() {

    while (1) {
        system("cls");
        menu();
    }




    return 0;
}
//��������Ҫ
// һ����ֵ����
// �ۼ������ͷ��ۼ�����
//minimax����negamax���㷨
// ��Ӯ�ж�������û�кϷ��ֵ�ʱ�򣬾�����
// �Ϸ����ж���
//#�ǿյأ�*��player 1��%��player 2


//judge���������ڱ߽Ǵ���һЩbug

//��Ҫһ��menu����
//NoGo��Ҫһ����Ӯ�ж���
// ÿһ��Ҫ��¼��������
//������Ҫ�����˳������ص��˵�����



//��Ҫһ�����õı�������



//���ݻغϴ�ӡ����
void printChessman_turn(int i) {
    if (i % 2 == 0) {
        printf_red('*');
    }
    else {
        printf_blue('*');
    }
}
//���̳�ʼ����
void memset_checkerboard() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            checkerboard[i][j] = chessman[0];
        }
    }
}
//�Ⱥ��ֻ�ȡ��
void getPlayer(int* p) {
    char text[100] = { '\0' };
    cin >> text;
    cin.ignore
    (std::numeric_limits
        < streamsize >::
        max(), '\n');
    *p = atoi(text);
    switch (*p) {
    case(1):break;
    case(2):break;
    default:cout << "�������룬��������һ�顣" << endl;
        getPlayer(p);
        break;
    }
}
//���̻�ȡ��
void getNum(char*p) {
    cin >> p;
    cin.ignore
    (std::numeric_limits
        < streamsize >::
        max(), '\n');
    if (atoi(p) <= gameCount && atoi(p)>0) {
        return;
    }
    else {
        cout << "invalid input" << endl;
        getNum(p);
    }
}
//������
void readRecord(int n) {
    turn = 0;
    int flag = 0;
    memset_checkerboard();
    system("cls");
    printf("����չʾ��%d����\n", n);
    system("pause");
    for (turn = 0;; turn++) {
        flag = 0;
        if (gameRecord[n][turn].x == 99
            && gameRecord[n][turn].y == 99)
            break;
        ApplyMove(turn % 2 + 1,
            gameRecord[n][turn].x,
            gameRecord[n][turn].y);
        system("cls");
        printf("��%d��\n ", turn + 1);
        printChessman_turn(turn);
        cout << "\t";
        printf("(%d,%d)\n",
            gameRecord[n][turn].x + 1,
            gameRecord[n][turn].y + 1);
        draw();
        printf("���� c ��������\n����start�ӵ�ǰ���濪ʼ����\n");
        string text;

        while (flag == 0) {
            cin >> text;
            if (text == "c") flag = 1;
            if (text == "start") flag = 2;
            if (flag == 0) {
                cout << "����������" << endl;
                cin.ignore
                (std::numeric_limits
                    < streamsize >::
                    max(), '\n');
            }
        }
        if (flag == 2) {
            gameCount++;
            for (int i = 0; i <= turn; i++) {
                gameRecord[gameCount][i] =
                    gameRecord[n][i];
            }
            x = gameRecord[n][turn].x;
            y = gameRecord[n][turn].y;
            turn++;
            NoGo(turn % 2 + 1);
            break;
        }

    }
    if (flag != 2) {
        cout << "���̽���" << endl;
        system("pause");
    }

}
//�˵�
void menu() {
    cout << "----------�˵�----------" << endl;
    cout << "����Ϸ---------->enter 1" << endl;
    cout << "����------------>enter 2" << endl;
    cout << "�رճ���-------->enter 3" << endl;
    char command;
    cin >> command;
    cin.ignore
    (std::numeric_limits
        < streamsize >::
        max(), '\n');
    switch (command) {
    case('1'):
        rotation = 0;
        turn = 0;
        gameCount++;
        memset_checkerboard();
        system("cls");
        cout << "�������Ϊ��x y\n����x��������y������,x��y֮���ÿո�տ�" << endl;
        cout << "��ʼ��Ϸ������stop������ֹ���ζԾ֣����׽�����" << endl;
        cout << "����withdraw���Ի���" << endl;
        cout << "��ѡ������or����" << endl;
        cout << "���� enter 1������ enter 2" << endl;
        {int player = 0;
        getPlayer(&player);
        NoGo(player);
        }
        break;
    case('2'):
        system("cls");
        {
            if (gameCount == 0) {
                cout << "һ�̶�û���أ�" << endl;
                menu();
            }
            else {
                cout << "�Ѿ�������" << gameCount << "��" << endl;
                cout << "��ѡ��Ҫ��ȡ����" << endl;
                char n[100] = { '\0' };
                getNum(n);
                readRecord(atoi(n));
            }

        }
        break;
    case('3'):
        exit(0);
        break;
    default:system("cls");
        cout << "�������룬���ٴ�����" << endl;
        menu();
        break;
    }
}


//������Χ��
void NoGo(int player) {
    whiteflag = 0;
    system("cls");
    draw();
    for (;; turn++) {
        if (turn % 2 + 1 == player) {
            system("cls");
            draw();
            if (turn >= 1)
                printf("AI���ˣ�%d,%d��\n", x + 1, y + 1);
            getFlag = 0;
            stopFlag = 0;
            withdrawFlag = 0;
            while (getFlag != 2 && stopFlag == 0 && withdrawFlag == 0) {
                GetMove();
                if (getFlag != 2 && stopFlag == 0 && withdrawFlag == 0) {
                    cin.ignore
                    (std::numeric_limits
                        < streamsize >::
                        max(), '\n');
                    cout << "����������" << endl;
                }
            }
            if (stopFlag == 1) {
                gameRecord[gameCount][turn].x = 99;
                gameRecord[gameCount][turn].y = 99;
                printf("\033[m\033[1;31m%s\033[m", "The game is ended.\n");
                system("pause");
                break;
            }
            if (getFlag == 2) {
                gameRecord[gameCount][turn].x = x;
                gameRecord[gameCount][turn].y = y;
                if (judge(x, y, player)) {
                    ApplyMove(turn % 2 + 1, x, y);
                    system("cls");
                    draw();
                }
                else {
                    gameRecord[gameCount][turn + 1].x = 99;
                    gameRecord[gameCount][turn + 1].y = 99;
                    printf("\033[m\033[1;31m%s\033[m", "YOU LOSE!\n");
                    system("pause");
                    break;
                }
            }
            if (withdrawFlag == 1) {
                if (turn >= 2) {
                    CancelMove
                    (gameRecord[gameCount][turn - 1].x
                        , gameRecord[gameCount][turn - 1].y);
                    CancelMove(
                        gameRecord[gameCount][turn - 2].x
                        , gameRecord[gameCount][turn - 2].y);
                    system("cls");
                    x = gameRecord[gameCount][turn - 3].x;
                    y = gameRecord[gameCount][turn - 3].y;
                    turn -= 3;
                }
                else {
                    turn = -1;
                }
                continue;
            }

        }
        else {
            rotation++;
            NegaMax(turn % 2 + 1, 0, -1000000, 1000000);
            gameRecord[gameCount][turn].x = x;
            gameRecord[gameCount][turn].y = y;
            system("cls");
            draw();

            if (whiteflag == 1) {
                gameRecord[gameCount][turn + 1].x = 99;
                gameRecord[gameCount][turn + 1].y = 99;
                printf("\033[m\033[1;31m%s\033[m", "YOU WIN!\n");
                system("pause");
                break;
            }

        }
        //һ��������Щ�����µĴ���
        /*    GetMove();
          ApplyMove(i % 2 + 1, x, y);
          system("cls");
          draw();
          for (int k = 0; k < row; k++) {
              for (int j = 0; j < row; j++) {
                  if (judge(k, j, i % 2 + 1)) {
                      cout << '(' << k+1 << ',' << j+1 << ')'<<' ';
                  }
                  else {
                      cout << "      ";
                  }
              }
              cout << endl;
          }*/
    }
}
//����to����
int ChessmanToPlayer(char a) {
    if (a == chessman[1]) {
        return 1;
    }if (a == chessman[2]) {
        return 2;
    }
    return 1;
}
//�Ϸ����ж���
bool judge(int x, int y, int player) {//�ǵ�memset������
    if (checkerboard[x][y] != '#') {
        return false;
    }
    ApplyMove(player, x, y);

    bool temp;
    bool temp1, temp2, temp3, temp4;

    temp = Qi(x, y, player);
    memset(qi, 0, sizeof(qi));
    if (checkerboard[x + 1][y] == chessman[player]
        || checkerboard[x + 1][y] == chessman[0]) {
        temp1 = true;
    }
    else {
        temp1 = Qi(x + 1, y, opponent(player));
        memset(qi, 0, sizeof(qi));
    }

    if (checkerboard[x - 1][y] == chessman[player]
        || checkerboard[x - 1][y] == chessman[0]) {
        temp2 = true;
    }
    else {
        temp2 = Qi(x - 1, y, opponent(player));
        memset(qi, 0, sizeof(qi));
    }

    if (checkerboard[x][y + 1] == chessman[player]
        || checkerboard[x][y + 1] == chessman[0]) {
        temp3 = true;
    }
    else {
        temp3 = Qi(x, y + 1, opponent(player));
        memset(qi, 0, sizeof(qi));
    }

    if (checkerboard[x][y - 1] == chessman[player]
        || checkerboard[x][y - 1] == chessman[0]) {
        temp4 = true;
    }
    else {
        temp4 = Qi(x, y - 1, opponent(player));
        memset(qi, 0, sizeof(qi));
    }
    if (x + 1 >= row)
        temp1 = true;
    if (x - 1 < 0)
        temp2 = true;
    if (y + 1 >= row)
        temp3 = true;
    if (y - 1 < 0)
        temp4 = true;
    CancelMove(x, y);
    return temp && temp1 && temp2 && temp3 && temp4;
}
//�ж��Ƿ�����
bool SmallQi(int x, int y, int player) {
    if (qi[x][y] == 1) return false;
    qi[x][y] = 1;
    if (checkerboard[x][y]
        == chessman[opponent(player)]) {
        return false;
    }
    if (checkerboard[x][y]
        == chessman[player]) {
        return
            Qi(x + 1, y, player) || Qi(x - 1, y, player)
            || Qi(x, y + 1, player) || Qi(x, y - 1, player);
    }
    if (checkerboard[x][y] == chessman[0]) {
        return true;
    }

    return false;
}
bool Qi(int x, int y, int player) {
    if (x < 0 || y < 0 || x >= row || y >= row) {
        return false;
    }
    bool temp = SmallQi(x, y, player);
    qi[x][y] = 1;
    return temp;
}
//վ��player�ǶȵĹ�ֵ����
int evaluate(int player) {
    memset(value, 0, sizeof(value));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {

            if (judge(i, j, player) == true
                && judge(i, j, opponent(player)) == false) {
                value[player]++;
            }
            if (judge(i, j, opponent(player)) == true
                && judge(i, j, player) == false) {
                value[opponent(player)]++;
            }
        }
    }
    return value[player] - value[opponent(player)];
    /* FakeEyes(player);
     eyes(player);
     FakeEyes(opponent(player));
     eyes(opponent(player));
     return value[player] - value[opponent(player)];*/
}
//ת��player
int opponent(int player) {
    return (player % 2 + 1);
}
/*//ͳ��ĳplayer�ļ�����

void FakeEyes(int player) {
    //ͳ���Ľǵļ���
    if (checkerboard[0][0] == chessman[player]) {
        if (checkerboard[0][1] == chessman[opponent(player)]
            || chessman[opponent(player)] == checkerboard[1][0]) {
            value[player]++;
        }
    }
    if (checkerboard[row - 1][row - 1] == chessman[player]) {
        if (checkerboard[row - 1][row - 2] == chessman[opponent(player)]
            || chessman[opponent(player)] == checkerboard[row - 2][row - 1]) {
            value[player]++;
        }
    }
    if (checkerboard[0][row - 1] == chessman[player]) {
        if (checkerboard[0][row - 2] == chessman[opponent(player)] ||
            checkerboard[1][row - 1] == chessman[opponent(player)]) {
            value[player]++;
        }
    }
    if (checkerboard[row - 1][0] == chessman[player]) {
        if (checkerboard[row - 1][1] == chessman[opponent(player)] ||
            checkerboard[row - 2][0] == chessman[opponent(player)]) {
            value[player]++;
        }
    }
    //ͳ���ıߵļ���
    for (int i = 1; i <= row - 2; i++) {
        if (checkerboard[0][i] == chessman[player]) {
            if (checkerboard[0][i + 1] == chessman[opponent(player)]
                + checkerboard[0][i - 1] == chessman[opponent(player)]
                + checkerboard[1][i] == chessman[opponent(player)]
                == 2) {
                value[player]++;
            }
        }
    }
    for (int i = 1; i <= row - 2; i++) {
        if (checkerboard[row - 1][i] == chessman[player]) {
            if (checkerboard[row - 1][i + 1] == chessman[opponent(player)]
                + checkerboard[row - 2][i - 1] == chessman[opponent(player)]
                + checkerboard[row - 2][i] == chessman[opponent(player)]
                == 2) {
                value[player]++;
            }
        }
    }
    for (int i = 1; i <= row - 2; i++) {
        if (checkerboard[i][0] == chessman[player]) {
            if (checkerboard[i + 1][0] == chessman[opponent(player)]
                + checkerboard[i - 1][0] == chessman[opponent(player)]
                + checkerboard[i][1] == chessman[opponent(player)]
                == 2) {
                value[player]++;
            }
        }
    }
    for (int i = 1; i <= row - 2; i++) {
        if (checkerboard[i][row - 1] == chessman[player]) {
            if (checkerboard[i + 1][row - 1] == chessman[opponent(player)]
                + checkerboard[i - 1][row - 1] == chessman[opponent(player)]
                + checkerboard[i][row - 2] == chessman[opponent(player)]
                == 2) {
                value[player]++;
            }
        }
    }
    //ͳ���ڲ��ļ���
    for (int i = 1; i <= row - 2; i++) {
        for (int j = 1; j <= row - 2; j++) {
            if (checkerboard[i][j] == chessman[player]) {
                if (checkerboard[i + 1][j] == chessman[opponent(player)] +
                    checkerboard[i - 1][j] == chessman[opponent(player)] +
                    checkerboard[i][j + 1] == chessman[opponent(player)] +
                    checkerboard[i][j - 1] == chessman[opponent(player)]
                    == 3) {
                    value[player]++;
                }
            }
        }
    }
}
//ͳ��ĳplayer������
void eyes(int player) {
    //�ж��ĸ���������
    if (checkerboard[0][0] == '#') {
        if (checkerboard[0][1] == chessman[player]
            && checkerboard[1][0] == chessman[player]) {
            value[player]++;
        }
    }
    if (checkerboard[0][row - 1] == '#') {
        if (checkerboard[0][row - 2] == chessman[player]
            && checkerboard[1][row - 1] == chessman[player]) {
            value[player]++;
        }
    }
    if (checkerboard[row - 1][0] == '#') {
        if (checkerboard[row - 1][1] == chessman[player]
            && checkerboard[row - 2][0] == chessman[player]) {
            value[player]++;
        }
    }
    if (checkerboard[row - 1][row - 1] == '#') {
        if (checkerboard[row - 1][row - 2] == chessman[player]
            && checkerboard[row - 2][row - 1] == chessman[player]) {
            value[player]++;
        }
    }
    //�ж��ı���û����
    for (int i = 1; i <= row - 2; i++) {
        if (checkerboard[0][i] == '#' &&
            checkerboard[0][i - 1] == chessman[player] &&
            checkerboard[0][i + 1] == chessman[player] &&
            checkerboard[1][i] == chessman[player])
            value[player]++;
    }
    for (int i = 1; i <= row - 2; i++) {
        if (checkerboard[row - 1][i] == '#' &&
            checkerboard[row - 1][i - 1] == chessman[player] &&
            checkerboard[row - 1][i + 1] == chessman[player] &&
            checkerboard[row - 2][i] == chessman[player])
            value[player]++;
    }
    for (int i = 1; i <= row - 2; i++) {
        if (checkerboard[i][0] == '#' &&
            checkerboard[i - 1][0] == chessman[player] &&
            checkerboard[i + 1][0] == chessman[player] &&
            checkerboard[i][1] == chessman[player])
            value[player]++;
    }
    for (int i = 1; i <= row - 2; i++) {
        if (checkerboard[i][row - 1] == '#' &&
            checkerboard[i - 1][row - 1] == chessman[player] &&
            checkerboard[i + 1][row - 1] == chessman[player] &&
            checkerboard[i][row - 2] == chessman[player])
            value[player]++;
    }
    //�ж������ڲ��Ƿ�����
    for (int i = 1; i <= row - 2; i++) {
        for (int j = 1; j <= row - 2; j++) {
            if (checkerboard[i][j] == '#' &&
                checkerboard[i - 1][j] == chessman[player] &&
                checkerboard[i + 1][j] == chessman[player] &&
                checkerboard[i][j + 1] == chessman[player] &&
                checkerboard[i][j - 1] == chessman[player])
                value[player]++;
        }
    }
}*/
//Ӧ������
void ApplyMove(int player, int x, int y) {
    checkerboard[x][y] = chessman[player];
}
//������
void draw() {
    cout << "  ";
    for (int i = 0; i <= row - 1; i++) {
        cout << i + 1 << ' ';
    }
    cout << endl;
    for (int i = 0; i <= row - 1; i++) {
        cout << i + 1 << ' ';
        for (int j = 0; j <= row - 1; j++) {
            switch (checkerboard[i][j]) {
            case('#'):
                cout << checkerboard[i][j] << ' ';
                break;
            case('*'):
                printf_red(chessman[1]);
                cout << ' ';
                break;

            case('%'):
                printf_blue(chessman[1]);
                cout << ' ';
                break;
            }
        }
        cout << endl;
    }
    cout << endl;
}
//��ȡ��ҵ�����
void GetMove() {
    stopFlag = 0;
    withdrawFlag = 0;
    getFlag = 0;
    string s1;
    cin >> s1;
    if (s1.length() == 1 && s1[0] <= '9' && s1[0] > '0') {
        tempmovex = s1[0] - '0';
        getFlag++;
    }
    else {
        if (s1 == "stop") {
            stopFlag = 1;
            cin.ignore
            (std::numeric_limits
                < streamsize >::
                max(), '\n');
            return;
        }
        if (s1 == "withdraw") {
            if (turn == 1 || turn == 0) {
                cout << "һ����û����" << endl;
                cin.ignore
                (std::numeric_limits
                    < streamsize >::
                    max(), '\n');
                GetMove();
                return;
            }
            withdrawFlag = 1;
            cin.ignore
            (std::numeric_limits
                < streamsize >::
                max(), '\n');
            return;
        }

    }
    if (getFlag != 1) {
        cout << "����������" << endl;
        cin.ignore
        (std::numeric_limits
            < streamsize >::
            max(), '\n');
        GetMove();
        return;
    }
    string s2;
    cin >> s2;
    if (s2.length() == 1 && s2[0] <= '9' && s2[0] > '0') {
        tempmovey = s2[0] - '0';
        getFlag++;
    }
    else {
        if (s2 == "stop") {
            stopFlag = 1;
            cin.ignore
            (std::numeric_limits
                < streamsize >::
                max(), '\n');
            return;
        }
        if (s2 == "withdraw") {
            withdrawFlag = 1;
            cin.ignore
            (std::numeric_limits
                < streamsize >::
                max(), '\n');
            return;
        }
    }
    if (getFlag != 2) {
        cout << "����������" << endl;
        cin.ignore
        (std::numeric_limits
            < streamsize >::
            max(), '\n');
        GetMove();
        return;
    }
    x = tempmovex - 1; y = tempmovey - 1;
    if (checkerboard[x][y] != chessman[0]) {
        cout << "����������" << endl;
        cin.ignore
        (std::numeric_limits
            < streamsize >::
            max(), '\n');
        GetMove();
    }
}

//��������
void CancelMove(int x, int y) {
    checkerboard[x][y] = '#';
}
//Negamax�㷨
int NegaMax(int player, int depth, int a, int b) {//ʹ��alpha-beta��֦�㷨
    if (depth >= MaxDepth) {
        return evaluate(player);
    }
    int flag = 0;
    int BestMoveX = 0; int BestMoveY = 0;
    int temp = 0;
    switch (rotation % 4) {
    case(0):
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < row; j++) {
                if (judge(i, j, player)) {
                    ApplyMove(player, i, j);
                    flag = 1;
                    temp
                        = -NegaMax(opponent(player), depth + 1, -b, -a);
                    CancelMove(i, j);
                    if (temp > a) {
                        BestMoveX = i; BestMoveY = j;
                        a = temp;
                    }
                    if (a >= b && depth != 0) {
                        return b;
                    }
                    if (a >= b && depth == 0) {
                        goto end0;
                    }
                }
                else {
                    continue;
                }
            }
        }

    end0:
        if (depth == 0) {
            if (a != -1000000) {
                x = BestMoveX; y = BestMoveY;
                ApplyMove(player, BestMoveX, BestMoveY);
            }
            else
            {
                for (int i = 0; i < row; i++) {
                    for (int j = 0; j < row; j++) {
                        if (judge(i, j, player)) {
                            ApplyMove(player, i, j);
                            x = i; y = j;
                            return a;
                        }
                    }
                }
                whiteflag = 1;
                for (int i = 0; i < row; i++) {
                    for (int j = 0; j < row; j++) {
                        if (checkerboard[i][j] == chessman[0]) {
                            ApplyMove(player, i, j);
                            x = i; y = j;
                            return a;
                        }
                    }
                }
            }
        }
        if (flag == 0) return -1000000;
        return a;
        break;
    case(1):
        for (int i = row - 1; i >= 0; i--) {
            for (int j = row - 1; j >= 0; j--) {
                if (judge(i, j, player)) {
                    ApplyMove(player, i, j);
                    flag = 1;
                    temp
                        = -NegaMax(opponent(player), depth + 1, -b, -a);
                    CancelMove(i, j);
                    if (temp > a) {
                        BestMoveX = i; BestMoveY = j;
                        a = temp;
                    }
                    if (a >= b && depth != 0) {
                        return b;
                    }
                    if (a >= b && depth == 0) {
                        goto end1;
                    }
                }
                else {
                    continue;
                }
            }
        }

    end1:
        if (depth == 0) {
            if (a != -1000000) {
                x = BestMoveX; y = BestMoveY;
                ApplyMove(player, BestMoveX, BestMoveY);
            }
            else
            {
                for (int i = 0; i < row; i++) {
                    for (int j = 0; j < row; j++) {
                        if (judge(i, j, player)) {
                            ApplyMove(player, i, j);
                            x = i; y = j;
                            return a;
                        }
                    }
                }
                whiteflag = 1;
                for (int i = 0; i < row; i++) {
                    for (int j = 0; j < row; j++) {
                        if (checkerboard[i][j] == chessman[0]) {
                            ApplyMove(player, i, j);
                            x = i; y = j;
                            return a;
                        }
                    }
                }
            }
        }
        if (flag == 0) return -1000000;
        return a;
        break;
    case(2):
        for (int i = 0; i < row; i++) {
            for (int j = row - 1; j >= 0; j--) {
                if (judge(i, j, player)) {
                    ApplyMove(player, i, j);
                    flag = 1;
                    temp
                        = -NegaMax(opponent(player), depth + 1, -b, -a);
                    CancelMove(i, j);
                    if (temp > a) {
                        BestMoveX = i; BestMoveY = j;
                        a = temp;
                    }
                    if (a >= b && depth != 0) {
                        return b;
                    }
                    if (a >= b && depth == 0) {
                        goto end2;
                    }
                }
                else {
                    continue;
                }
            }
        }

    end2:
        if (depth == 0) {
            if (a != -1000000) {
                x = BestMoveX; y = BestMoveY;
                ApplyMove(player, BestMoveX, BestMoveY);
            }
            else
            {
                for (int i = 0; i < row; i++) {
                    for (int j = 0; j < row; j++) {
                        if (judge(i, j, player)) {
                            ApplyMove(player, i, j);
                            x = i; y = j;
                            return a;
                        }
                    }
                }
                whiteflag = 1;
                for (int i = 0; i < row; i++) {
                    for (int j = 0; j < row; j++) {
                        if (checkerboard[i][j] == chessman[0]) {
                            ApplyMove(player, i, j);
                            x = i; y = j;
                            return a;
                        }
                    }
                }
            }
        }
        if (flag == 0) return -1000000;
        return a;
        break;
    case(3):
        for (int i = row - 1; i >= 0; i--) {
            for (int j = 0; j < row; j++) {
                if (judge(i, j, player)) {
                    ApplyMove(player, i, j);
                    flag = 1;
                    temp
                        = -NegaMax(opponent(player), depth + 1, -b, -a);
                    CancelMove(i, j);
                    if (temp > a) {
                        BestMoveX = i; BestMoveY = j;
                        a = temp;
                    }
                    if (a >= b && depth != 0) {
                        return b;
                    }
                    if (a >= b && depth == 0) {
                        goto end3;
                    }
                }
                else {
                    continue;
                }
            }
        }

    end3:
        if (depth == 0) {
            if (a != -1000000) {
                x = BestMoveX; y = BestMoveY;
                ApplyMove(player, BestMoveX, BestMoveY);
            }
            else
            {
                for (int i = 0; i < row; i++) {
                    for (int j = 0; j < row; j++) {
                        if (judge(i, j, player)) {
                            ApplyMove(player, i, j);
                            x = i; y = j;
                            return a;
                        }
                    }
                }
                whiteflag = 1;
                for (int i = 0; i < row; i++) {
                    for (int j = 0; j < row; j++) {
                        if (checkerboard[i][j] == chessman[0]) {
                            ApplyMove(player, i, j);
                            x = i; y = j;
                            return a;
                        }
                    }
                }
            }
        }
        if (flag == 0) return -1000000;
        return a;
        break;
    }
}
//��ɫ���
void printf_red(char s) {
    printf("\033[m\033[1;31m%c\033[m", s);
}
void printf_blue(char s) {
    printf("\033[m\033[1;34m%c\033[m", s);
}


