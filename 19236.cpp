#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
struct Fish{
    int x;
    int y;
    int dir;
};

int ans; 
int map[4][4];
struct Fish fish[17];
struct Fish shark;
int dx[] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 0, -1, -1, -1, 0, 1, 1, 1};

void swap_fish(int idx1, int idx2){
    struct Fish tmp = fish[idx1];
    fish[idx1].x = fish[idx2].x;
    fish[idx1].y = fish[idx2].y;
    fish[idx2].x = tmp.x;
    fish[idx2].y = tmp.y;
}

void move_fish(){
    for(int i = 1; i <= 16; ++i){
        if(fish[i].x == -1 && fish[i].y == -1){
            continue;
        }

        int x = fish[i].x;
        int y = fish[i].y;
        int d = fish[i].dir;
        int nx = x + dx[d];
        int ny = y + dy[d];

        bool flag = false;
        if(nx >= 0 && ny >= 0 && nx < 4 && ny < 4 && map[nx][ny] != -1){
            if(map[nx][ny] == 0){
                fish[i].x = nx;
                fish[i].y = ny;
                map[nx][ny] = i;
                map[x][y] = 0;
                flag = true;
            } else {
                swap_fish(i, map[nx][ny]);
                swap(map[x][y], map[nx][ny]);
                flag = true;
            }
        }

        if(!flag){
            int nd = d+1;
            if(nd == 9) nd = 1;
            int nx = x + dx[nd];
            int ny = y + dy[nd];

            while(nd != d){
                if(nx >= 0 && ny >= 0 && nx < 4 && ny < 4 && map[nx][ny] != -1){
                    if(map[nx][ny] == 0){
                        fish[i].x = nx;
                        fish[i].y = ny;
                        map[nx][ny] = i;
                        map[x][y] = 0;
                        fish[i].dir = nd;
                        break;
                    } else {
                        swap_fish(i, map[nx][ny]);
                        swap(map[x][y], map[nx][ny]);
                        fish[i].dir = nd;
                        break;
                    }
                }

                nd++;
                if(nd == 9) nd = 1;
                nx = x + dx[nd];
                ny = y + dy[nd];
            }
        }
    }
}

void move_shark(int total){

    int cx = shark.x;
    int cy = shark.y;
    int d = shark.dir;
    // no more fishes
    ans = max(ans, total);

    int original_map[4][4];
    struct Fish original_fish[17];
    struct Fish original_shark;
    memcpy(original_map, map, sizeof(map));
    memcpy(original_fish, fish, sizeof(original_fish));
    original_shark = shark;

    for(int i = 1; i < 4; ++i){
        int nx = cx + dx[d]*i;
        int ny = cy + dy[d]*i;

        if(nx < 0 || ny < 0 || nx >= 4 || ny >= 4) continue;
        if(map[nx][ny] == -1) continue;

        if(map[nx][ny] >= 1){
            int idx = map[nx][ny];
            map[nx][ny] = -1;
            fish[idx].x = -1;
            fish[idx].y = -1;
            map[cx][cy] = 0;
            shark.x = nx; shark.y = ny; shark.dir = fish[idx].dir;

            move_fish();
            move_shark(total+idx);

            memcpy(map, original_map, sizeof(original_map));
            memcpy(fish, original_fish, sizeof(original_fish));
            shark = original_shark;
        }
    }
}

int main(void){
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            int a, b;
            scanf("%d %d", &a, &b);
            map[i][j] = a;
            fish[a].x = i;
            fish[a].y = j;
            fish[a].dir = b;
        }
    }
    // 일단 0번 먼저 먹음
    int idx = map[0][0];
    ans += idx;
    shark.x = 0;
    shark.y = 0;
    shark.dir = fish[idx].dir;
    fish[idx].x = -1;
    fish[idx].y = -1; 
    map[0][0] = -1;
    move_fish();
    move_shark(idx);
    printf("%d\n", ans);
}