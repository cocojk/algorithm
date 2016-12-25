
// 조합 게임(combinatorial game)
// 동적 계획법의 또 다른 사용처 
// 체스나 바둑, 오목처럼 두 사람의 참가자가 하는 게임을 가리킨다.
// 이런 게임을 '해결'한다는 말은 게임의 상태가 주어졌을 때 완벽한 한 수를 찾아내는 알고리즘을 만든다는 뜻.

// 게임트리 
// 게임의 모든 상태를 트리의 형태로 그린 것 (DAG)
// 완벽한 게임트리가 주어질 때 우리는 어떤 게임도 완벽하게 풀 수 있다.
// 그 방법은 맨 아래쪽, 최종 상태에서부터 거슬러 올라가는 것. 
// 맨 아래줄의 상태들에서는 항상 게임이 끝나고, 어느 쪽이 이길지 승부가 난다고 하면 
// 마지막 수를 두는 참가자는 항상 (그런 수가 있다면) 자신이 이길 수 있는 수를 둘 겁니다. 
// 마지막 수를 두는 참가자가 지는 경우느 어떤 수를 두더라도 질 수 밖에 없는 상태뿐입니다. 
// 그러므로 마지막에서 두 번째 줄에 있는 모든 상태들에 대해 어느 쪽이 이길지를 판단할 수 있습니다. 
// 그러고나면 한 단계 위로 올라가 아까와 같은 작업을 다른 참가자에 대해 반복할 수 있습니다. 
// 예를 들어, 한 턴에 사용자가 둘 수 있는 방법이 최대 3개인 게임에서는 
// 현재 사용자가 black이라고 하면, 각각의 방법을 둔 경우 white 승, black 승, black 승으로 구성될 경우 black은 black승으로 둘 것이고,
// white 승, white 승, white승으로 구성될 경우에만 black이 질 것이다.

// bottom up 
// 위 방법처럼 게임 트리 전체를 그린 후 밑에서부터 승패를 판단하면서 올라가는 것은 직관적이지만 구현하기가 까다롭다. 
// 실제 게임트리에서는 상태가 예시처럼 예쁘게 구분되지 않을 수도 있고, 맨 아래줄에서 게임이 일제히 종료되는 것이 아니라 그 전에 승부가 날 수도 있고,
// 메모리도 많이 차지한다. (맨 아랫단계 전체에 대해서 계산한 후 올라가야 하기 때문에) 

// top down 
// winner (state, player) = 현재 게임의 상태가 state이고, player가 수를 둘 차례일 때 어느 쪽이 최종적으로 이길까?
// 오목이나 바둑의 경우에는 항상 검은 돌이 먼저 두기 때문에 이런 정보를 전달할 필요가 없지만, 게임의 상태만 가지고는 누가 둘 차례인지 알 수 없는 
// 게임들의 경우에는 이 정보가 필요하다. 
// canWin (state) = 게임의 현재 상태가 state 일 때, 이번에 수를 둘 차례인 참가자가 이길 까? 로 변경가능 (더 직관적) 
// 경우의 수를 하나하나씩 순환하면서, 해당 수를 둔 후의 상태 state`에 대해 canWin()을 호출하고, 만약, canWin(state`)=false를 반환하는 것이 하나라도 있으면 현재 나는 이길 수 있음을 알 수 있다. 반면 하나라도 존재하지 않으면 무조건 지는 것을 알 수 있다. 

// 한 정점에 도달할 수 있는 경로가 여러가지 이기 때문에 메모이제이션을 활용하자. 

/*
   문제

   틱택토는 3x3 크기의 게임판에서 하는 3목 게임입니다. 두 명이 번갈아가며 o와 x를 게임판의 빈 칸에 쓰되, 먼저 같은 글자를 가로, 세로 혹은 대각선으로 3개 쓰이도록 하는 쪽이 이깁니다. 예를 들어, 다음 게임판은 x가 이긴 게임판입니다.

   xoo
   .x.
   ..x
   게임은 항상 x부터 시작합니다.

   틱택토 게임판의 현재 상태가 주어집니다. 두 사람 모두 최선을 다한다고 가정할 때, 어느쪽이 이길지 판단하는 프로그램을 작성하세요.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 C(<= 50)가 주어집니다. 각 테스트 케이스는 세 줄에 각 세 글자로 게임판의 각 위치에 쓰인 글자가 주어집니다. 글자가 없는 칸은 마침표(.)로 표현합니다.

   출력

   각 테스트 케이스마다 한 줄을 출력합니다. 두 사람이 모두 최선을 다할 경우 비긴다면 TIE를, 아닌 경우 이기는 사람의 글자를 출력합니다.

   예제 입력

   3
   ...
   ...
   ...
   xx.
   oo.
   ...
   xox
   oo.
   x.x
   예제 출력

   TIE
   x
   o
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 코드 9.20 틱택토를 해결하는 동적 계획법 알고리즘 

// turn이 한 줄을 만들었는지를 반환한다. 
bool isFinished (const vector<string>& board, char turn)
{
    int y, x;

    // horizontal
    for (y = 0; y < 3; y ++)
    {
        for (x = 0; x < 3; x++)
        {
            if (board[y][x] != turn)
                break;
        }

        if (x == 3)
            return true;
    }


    // vertical
    for (x = 0; x < 3; x++)
    {
        for (y = 0; y < 3; y ++)
        {
            if (board[y][x] != turn)
                break;
        }

        if (y == 3)
            return true;
    }

    // digonal
    for (x = 0; x < 3; x++)
        if (board[x][x] != turn)
            break;

    if (x == 3)
        return true;

    for (x = 0; x < 3; x++)
        if (board[x][2-x] != turn)
            break;

    if (x == 3)
        return true;

    return false;
} 

// 틱택토 게임판이 주어질 때 [0,19682] 범위의 정수로 변환한다.
int bijection (const vector<string>& board) {
    int ret = 0;
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 3; x++)
        {
            ret = ret *3;
            if(board[y][x] == 'o') 
                ++ret;
            else if (board[y][x] == 'x')
                ret += 2;
        }

    return ret;
}

// cache[]는 -2로 초기화한다.
int cache[19683];
// 내가 이길 수 있으면 1을 비길 수 있으면 0을 지면 -1을 리턴한다.
int canWin (vector<string>& board, char turn) {
    // base case : 마지막에 상대가 둬서 한 줄이 만들어진 경우 
    if (isFinished(board,'o'+'x'-turn))
        return -1;
    int* ret = &cache[bijection(board)];
    if (*ret != -2)
        return *ret;
    // 모든 반환 값의 min을 취하자.
    int minValue = 2;
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 3; x++)
            if (board[y][x] == '.') 
            {
                board[y][x] = turn;
                minValue = min(minValue,canWin(board,'o'+'x'-turn));
                board[y][x] = '.';
            }

    // 플레이 ㅎ할 수 없거나, 어떻게 해도 비기는 것이 최선인 경우 
    if (minValue == 2 || minValue == 0)
        return *ret = 0;
    // 최선이 상대가 이기는 거라면 난 무조건 지고, 상대가 지는 거라면 난 이긴다.
    return *ret = -minValue;
}

int nextTurn (vector<string>& board)
{
    int numX = 0;
    int numO = 0;

    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 3; x++)
        { 
            if (board[y][x] == 'x') 
                numX++;
            else if (board[y][x] == 'o')
                numO++;
        }

    if (numX > numO)
        return 1;

    return 0;
}

int main (void)
{
    int testcase;
    char turn[2];
    int next,result;
    string temp;
    vector<string> board;
    cin >> testcase;
    turn[0] = 'x';
    turn[1] = 'o';

    while(testcase--)
    {
        board.clear();
        for (int i = 0; i < 19683; i++)
            cache[i] = -2;
            

        for (int i = 0; i < 3; i ++)
        {
            cin >> temp;
            board.push_back(temp);
        }
        
        next = nextTurn(board);
        switch(canWin(board,turn[next]))
        {
            case -1:
                cout << turn[next^1]<<endl;
                break;

            case 0:
                cout <<"TIE"<<endl;
                break;

            case 1:
                cout << turn[next]<<endl;
                break;
        }
    }

}


