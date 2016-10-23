
/*
   문제


   H*W 크기의 게임판이 있습니다. 게임판은 검은 칸과 흰 칸으로 구성된 격자 모양을 하고 있는데 이 중 모든 흰 칸을 3칸짜리 L자 모양의 블록으로 덮고 싶습니다. 이 때 블록들은 자유롭게 회전해서 놓을 수 있지만, 서로 겹치거나, 검은 칸을 덮거나, 게임판 밖으로 나가서는 안 됩니다. 위 그림은 한 게임판과 이를 덮는 방법을 보여줍니다.

   게임판이 주어질 때 이를 덮는 방법의 수를 계산하는 프로그램을 작성하세요.

   입력

   력의 첫 줄에는 테스트 케이스의 수 C (C <= 30) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 2개의 정수 H, W (1 <= H,W <= 20) 가 주어집니다. 다음 H 줄에 각 W 글자로 게임판의 모양이 주어집니다. # 은 검은 칸, . 는 흰 칸을 나타냅니다. 입력에 주어지는 게임판에 있는 흰 칸의 수는 50 을 넘지 않습니다.

   출력

   한 줄에 하나씩 흰 칸을 모두 덮는 방법의 수를 출력합니다.

   예제 입력

   3 
   3 7 
#.....# 
#.....# 
##...## 
3 7 
#.....# 
#.....# 
##..### 
8 10 
########## 
#........# 
#........# 
#........# 
#........# 
#........# 
#........# 
########## 
예제 출력

0
2
1514
*/

// 게임판 덮기 문제를 해결하는 재귀 호출 알고리즘 

// 주어진 칸을 덮을 수 있는 네 가지 방법 
// 블록을 구성하는 세 칸의 상대적 위치 (dy,dx)의 목록 
const int coverType[4][3][2] = { 
    { {0,0}, {1,0}, {0,1} },
    { {0,0}, {0,1}, {1,1} },
    { {0,0}, {1,0}, {1,1} },
    { {0,0}, {1,0}, {1,-1}} };
// board의 (y,x)를 type번 방법으로 덮거나, 덮었던 블록을 없앤다.
// delta = 1이면 덮고, -1이면 덮었던 블록을 없앤다.
// 만약 블록이 제대로 덮이지 않은 경우 (게임판 밖으로 나가거나, 겹치거나, 검은판을 덮을 때) false를 반환한다.
bool set(vector<vector<int> >& board,int y,int x,int type,int delta) {
    bool ok = true;
    for (int i = 0; i < 3; i++) {
        const int ny = y + coverType[type][i][0];
        const int nx = x + coverType[type][i][i];
        if(ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size())
            ok = false;
        else if ((board[ny][nx] += delta) > 1)
            ok = false;
    }

    return ok;
}

// board의 모든 빈칸을 덮을 수 있는 방법의 수를 반환한다.
// board[i][j] = 1 이미 덮인 칸 혹은 검은 판 
// board[i][j] = 0 아직 덮이지 않은 칸 
int cover(vector<vector<int> >&board) {
    // 아직 채우지 못한 칸 중 가장 윗줄 왼쪽에 있는 칸을 찾는ㄷ.
    int y = -1, x = -1;
    for(int i = 0; i < board.size(); i ++) {
        for(int j = 0; j < board[i].size(); j++) 
            if(board[i][j] == 0) {
                y = i;
                x = j;
                break;
            }

        if(y != -1) break;
    }

    // base case : 모든 칸을 채웠으면 1을 반환한ㄷ.
    if(y == -1) return 1;
    int ret = 0;
    for(int type = 0; type < 4; type++) {
        // 만약 board[y][x]를 type 형태로 덮을 수 있으면 재귀 호출한다.
        if(set(board,y,x,type,1))
            ret += cover(board);
        // 덮었던 블록을 치운다.
        set(board,y,x,type,-1);
    }

    return ret;
}

