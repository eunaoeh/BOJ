#include<iostream>
#include<queue>
#define endl "\n"
using namespace std;
int n, m;
char map[11][11];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
queue<pair<int, int> > q[2];
queue<int> cnt;
// bool visit[11][11][11][11];

void bfs(){
    cnt.push(0);
    while(!q[0].empty() || !q[1].empty()){
        int rx = q[0].front().first;
        int ry = q[0].front().second;
        int bx = q[1].front().first;
        int by = q[1].front().second;
        int cur_cnt = cnt.front();
        cnt.pop();
        q[0].pop();
        q[1].pop();
        if(cur_cnt >= 10){
            printf("-1\n");
            return;
        }
        for(int i = 0; i < 4; ++i){
            int nrx = rx, nry = ry, nbx = bx, nby = by;
            bool rflag = false;
            bool bflag = false;
            bool rfinish = false;
            bool bfinish = false;

            while(map[nrx+dx[i]][nry+dy[i]] != '#'){
                nrx += dx[i];
                nry += dy[i];
                if(nrx == bx && nry == by){
                    rflag = true;
                    // break;
                }
                if(map[nrx][nry] == 'O'){
                    rfinish = true;
                    break;
                }
            }

            while(map[nbx+dx[i]][nby+dy[i]] != '#'){
                nbx += dx[i];
                nby += dy[i];
                if(nbx == rx && nby == ry){
                    bflag = true;
                    // break;
                }
                if(map[nbx][nby] == 'O'){
                    bfinish = true;
                    break;
                }
            }
            if(bfinish) continue;
            if(rfinish) {
                printf("%d\n", cur_cnt+1);
                return;
            }

            if(rflag){
                nrx = nbx - dx[i];
                nry = nby - dy[i];
            }
            if(bflag){
                nbx = nrx - dx[i];
                nby = nry - dy[i];
            }
            
            q[0].push(make_pair(nrx, nry));
            q[1].push(make_pair(nbx, nby));
            cnt.push(cur_cnt+1);
        }
    }
}

int main(void){

    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++){
        scanf("%s", map[i]);
        for(int j = 0; j < m; j++){
            if(map[i][j] == 'R'){
                q[0].push(make_pair(i, j));
                map[i][j] = '.';
            }
            else if(map[i][j] == 'B'){
                q[1].push(make_pair(i, j));
                map[i][j] = '.';
            }
        }
    }
    bfs();
}