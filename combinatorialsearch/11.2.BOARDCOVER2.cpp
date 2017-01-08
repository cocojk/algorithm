/*
   문제

   H×W 크기의 게임판과 한 가지 모양의 블록이 여러 개 있습니다. 게임판에 가능한 많은 블록을 올려놓고 싶은데, 게임판은 검은 칸과 흰 칸으로 구성된 격자 모양을 하고 있으며 이 중에서 흰 칸에만 블록을 올려놓을 수 있습니다. 이때 블록들은 자유롭게 회전해서 놓을 수 있지만, 서로 겹치거나, 격자에 어긋나게 덮거나, 검은 칸을 덮거나, 게임판 밖으로 나가서는 안 됩니다.



   위 그림은 예제 게임판과 L 자 모양의 블록으로 이 게임판을 덮는 방법을 보여줍니다. 게임판에는 15개의 흰 칸이 있고, 한 블록은 네 칸을 차지하기 때문에 그림과 같이 최대 세 개의 블록을 올려놓을 수 있지요. 게임판과 블록의 모양이 주어질 때 최대 몇 개의 블록을 올려놓을 수 있는지 판단하는 프로그램을 작성하세요.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 T (T≤100)가 주어집니다. 각 테스트 케이스의 첫 줄에는 게임판의 크기 H, W (1≤H, W≤10), 그리고 블록의 모양을 나타내는 격자의 크기 R, C (1≤R, C≤10)가 주어집니다. 다음 H줄에는 각각 W 글자의 문자열로 게임판의 정보가 주어집니다. 문자열의 각 글자는 게임판의 한 칸을 나타내며, #은 검은 칸, 마침표는 흰 칸을 의미합니다. 다음 R줄에는 각 C 글자의 문자열로 블록의 모양이 주어집니다. 이 문자열에서 #은 블록의 일부, 마침표는 빈 칸을 나타냅니다.

   각 게임판에는 최대 50개의 흰 칸이 있으며, 각 블록은 3개 이상 10개 이하의 칸들로 구성됩니다. 변을 맞대고 있는 두 변이 서로 연결되어 있다고 할 때, 블록을 구성하는 모든 칸들은 서로 직접적 혹은 간접적으로 연결되어 있습니다.

   출력

   각 테스트 케이스마다 게임판에 놓을 수 있는 최대의 블록 수를 출력합니다.

   예제 입력

   2
   4 7 2 3
##.##..
#......
#....##
#..####
###
#..
5 10 3 3
..........
..........
..........
..........
..........
.#.
###
..#
예제 출력

3
8
*/
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int callnum;
// 게임판의 정보 
int boardH, boardW;
vector<string> board;
// 게임판의 각 칸이 덮였는지를 나타낸다. 1이면 검은 칸이거나 이미 덮은 칸, 0이면 빈칸
int covered[10][10];
// 지금까지 찾은 최적해 
int best;
// 남은 블록의 수 
int remain;

// 블록의 각 회전된 형태를 상대 좌표의 목록으로 저장해 둔다.
vector<vector<pair<int,int> > > rotations;
// 블록의 크기 
int blockSize;
// 2차원 배열 arr을 시계방향으로 90도 돌린 결과를 반환한다.
vector<string> rotate (const vector<string>& arr) {
    vector<string> ret (arr[0].size() , string(arr.size(),' '));
    for (int i = 0; i < arr.size(); i++)
        for (int j = 0; j < arr[0].size(); j++)
            ret[j][arr.size()-i-1] = arr[i][j];
    return ret;
}

// block의 네 가지 회전 형태를 만들고 이들을 상대 좌표의 목록으로 변환한ㄷ.
void generateRotations (vector<string> block) {
    rotations.clear();
    rotations.resize(4);
    for (int rot = 0; rot < 4; rot++) {
        int originY = -1, originX = -1;
        for (int i = 0; i < block.size(); i++)
            for (int j = 0; j < block[i].size(); j++)
                if (block[i][j] == '#') {
                    if (originY == -1) {
                        // 가장 윗줄 맨 왼쪽에 있는 칸이 '원점'이 된다.
                        originY = i;
                        originX = j;
                    }

                    // 각 칸의 위치를 원점으로부터의 상대좌표로 표현한다.
                    rotations[rot].push_back(make_pair(i-originY,j-originX));
                }

        // 블록을 시계 방향으로 90도 회전한다.
        block = rotate(block);
    }

    // 네 가지 회전 형태 중 중복이 있을 경우 이를 제거한다.
    sort(rotations.begin(), rotations.end());
    rotations.erase(unique(rotations.begin(),rotations.end()),rotations.end());
    // 블록이 몇 칸 짜리인지 저장해 둔다.
    blockSize = rotations[0].size();
}

// board의 (y,x)를 type번 방법으로 덮거나, 덮었던 블록을 없앤다.
// delta = 1이면 덮고, -1이면 덮었던 블록을 없앤다.
// 만약 블록이 제대로 덮이지 않은 경우 (게임판 밖으로 나가거나, 겹치거나, 검은판을 덮을 때) false를 반환한다.
bool set (int y,int x,const vector<pair<int,int> >& block,int delta) {
    bool ok = true;
    for (int i = 0; i < block.size(); i++) {
        const int ny = y + block[i].first;
        const int nx = x + block[i].second;
        if(ny < 0 || ny >= boardH || nx < 0 || nx >= boardW)
            ok = false;
        else if ((covered[ny][nx] += delta) > 1)
            ok = false;
    }

    return ok;
}

// placed : 지금까지 높은 블록의 수 
void search (int placed) {

    // 아직 채우지 못한 빈 칸 중 가장 윗줄 왼쪽에 있는 칸을 찾는다.
    int y = -1, x = -1;
    for (int i = 0; i < boardH; i++) {
        for (int j = 0; j < boardW; j++) 
            if (covered[i][j] == 0) {
                y = i;
                x = j;
                break;
            }

        if (y != -1)
            break;
    }

    // base case 
    if (y == -1) {
        best = max (best,placed);
        return;
    }

    if ( best >= (placed + remain/blockSize))
        return;

    // 이 칸을 덮는다.
    for (int i = 0; i < rotations.size(); i++) {
        if (set(y,x,rotations[i],1))
        { remain -= blockSize;
            search(placed+1);

        }
        set(y,x,rotations[i],-1);
        remain += blockSize;
    }

    // 이 칸을 덮지 않고 막아 둔다.
    covered[y][x] = 1;
    remain -= 1;
    search(placed);
    covered[y][x] = 0;
    remain += 1;

}

int solve (){
    best = 0;
    remain = 0;
    callnum = 0;
    // covered 배열을 초기화한다.
    for (int i = 0; i < boardH; i++) {
        for (int j = 0; j < boardW; j++)
        {

            covered[i][j] = (board[i][j] == '#' ? 1:0);
            remain += (1-covered[i][j]);
        }
    }

    search(0);
    return best;
}



int main() {

    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
        int blockH, blockW;
        cin >> boardH >> boardW >> blockH >> blockW;
        board.resize(boardH);
        vector<string> block(blockH);

        for(int i = 0; i < boardH; i++)
            cin >> board[i];
        for(int i = 0; i < blockH; i++)
            cin >> block[i];
        generateRotations(block);
        cout << solve() << endl;
        cout << callnum << endl;
    }
}
