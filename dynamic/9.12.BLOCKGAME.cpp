/*
문제

시티빌과 비주얼드에 지친 진호와 현환이는 집에 굴러다니는 블럭들을 모아 새로운 게임을 하기로 했습니다. 5×5 크기의 게임판에서 시작해, 둘이 번갈아 가며 블럭을 하나씩 게임판에 내려놓습니다. 블럭은 L 모양으로 구성된 3칸짜리 블럭과 2칸짜리 블럭이 있으며, 항상 게임판에 있는 줄에 맞춰 내려놓아야 합니다. 블럭들은 서로 겹칠 수 없습니다. 다음 그림은 진행중인 게임판의 모습을 보여줍니다.



그림에서 보이는 바와 같이 각 블록은 자유롭게 뒤집거나 회전해서 올려놓을 수 있습니다. 두 사람이 번갈아가며 블록을 올려놓다가 더 올려놓을 수 없게 되면 마지막에 올려놓은 사람이 승리합니다. 진행 중인 게임판이 주어질 때 이번 차례인 사람이 승리할 수 있는 방법이 있는지를 판단하는 프로그램을 작성하세요.

입력

입력의 첫 줄에는 테스트 케이스의 수 C (C≤50)가 주어집니다. 각 테스트 케이스는 다섯 줄에 각 다섯 개의 문자로 구성되며, #는 이미 블록이 놓인 칸, 마침표(.)는 블록이 없는 칸을 의미합니다.

출력

각 테스트 케이스마다 한 줄을 출력합니다. 이번 차례인 사람이 항상 이길 수 있는 방법이 있다면 WINNING을, 항상 질 수밖에 없다면 LOSING을 출력합니다.

예제 입력

3
.....
.##..
##..#
#.###
..#..
.....
.....
.....
.....
.....
#..##
##.##
##.##
#...#
##.##
예제 출력

WINNING
LOSING
WINNING
*/
#include <iostream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

// 9.22 블록 게임 문제를 해결하는 동적 계획법 알고리즘 

vector<int> moves;
inline int cell (int y, int x) { return 1 << (y*5 + x); }

// 게임판에 놓을 수 있는 블록들의 위치를 미리 계산한다.
void precalc () {
    // 세 칸짜리 L자 모양 블록들을 계산한다.
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++)
        {
            // o o
            // o o
            // 좌표 값들을 cells에 저장한다.
            vector<int> cells;
            for (int dy = 0; dy < 2; dy++)
                for (int dx = 0; dx < 2; dx++)
                    cells.push_back(cell(y+dy,x+dx));

            // 4 가지 좌표값을 모두 더한다.
            int square = cells[0]+cells[1]+cells[2]+cells[3];

            // 전체에서 한개의 좌표를 빼준 값은 우리가 원하는 ㄴ자 모양 값이 된다.
            for (int i =0; i < 4; i++)
                moves.push_back(square-cells[i]);
        }

    // 두 칸짜리 블록들을 계산한다.
    for (int i = 0; i < 5; i ++)
        for (int j = 0; j < 4; j ++) {
            moves.push_back(cell(i,j) + cell(i,j+1));
            moves.push_back(cell(j,i) + cell(j+1,i));
        }
}

char cache [1<<25];

// 현재 게임판 상태가 board일 때 현재 차례인 사람이 승리할지 여부를 반환한다.
// (y,x) 칸에 블록이 있다. <=> (y*5 + x)번 비트가 켜져 있다.
char play (int board) {
    // 메모이제이션 
    char* ret = &cache[board];
    if (*ret != -1)
        return *ret;

    *ret = 0;
    // 모든 수를 고려한다.
    for (int i = 0; i < moves.size(); i++)
        // 이 수르 이 게임판에 놓을 수 있는가 확인 
        if ((moves[i] & board) == 0)
            if (!play(board | moves[i])) {
                *ret = 1;
                break;
            }

    return *ret;
}

int main (void)
{
    int testcase;
    int board;
    string temp;
    cin >> testcase;

    precalc();

    while(testcase--)
    {
        memset(cache,-1,sizeof(cache));
        board = 0;
        for (int i = 0; i < 5; i++)
        {
            cin >> temp;
            for (int j = 0; j < 5; j++)
                if (temp[j] == '#')
                    board += cell (i,j);
        }

        if (play(board))
        {
            cout << "WINNING" <<endl;
        }
        else 
        {
            cout << "LOSING" <<endl;
        }
    }
}


   
