#include <iostream>
#include <string>
#include <vector>

using namespace std;

void dfs(vector<vector<int>>& arr, int idx, int row, int col, int dir);

const int RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3;

vector<vector<int>> solution(int n) {
    vector<vector<int>> answer;
    
    //형식에 맞게 n*n 크기로 재배열
    answer.resize(n, vector<int>(n, 0));
    //우-하-좌-상 우선순위의 DFS 시작
    dfs(answer, 1, 0, 0, RIGHT);
    return answer;
}

void dfs(vector<vector<int>>& arr, int idx, int row, int col, int dir){
    //우-하-좌-상 우선순위로 탐색
    if(arr[row][col] == 0) arr[row][col] = idx;
    //우측 탐색 : 갈 수 있고 빈칸이며, 현재 방향이 우측이면 이동
    if(col + 1 < arr.size() && arr[row][col+1] == 0 && dir == RIGHT){
        dfs(arr, idx+1, row, col+1, RIGHT);
    } else {
        //어떤 이유로건 우측으로 이동 불가하면 아래로 이동
        dir = DOWN;
    }
    //하단 탐색 : 조건은 동일
    if(row + 1 < arr.size() && arr[row+1][col] == 0 && dir == DOWN){
        dfs(arr, idx+1, row+1, col, DOWN);
    } else {
        //어떤 이유로건 하단으로 이동 불가하면 좌측으로 이동
        dir = LEFT;
    }
    //좌측 탐색 : 조건은 동일
    if(col - 1 >= 0 && arr[row][col-1] == 0 && dir == LEFT){
        dfs(arr, idx+1, row, col-1, LEFT);
    } else {
        //어떤 이유로건 좌측으로 이동 불가하면 상단으로 이동
        dir = UP;
    }
    //상단 탐색 : 조건은 동일
    if(row - 1 >= 0 && arr[row-1][col] == 0 && dir == UP){
        dfs(arr, idx+1, row-1, col, UP);
    } else {
        //어떤 이유로건 상단으로 이동 불가하면 우측으로 이동
        dir = RIGHT;
        if(col + 1 < arr.size() && arr[row][col+1] == 0 && dir == RIGHT){
        dfs(arr, idx+1, row, col+1, RIGHT);
        }
    }
}