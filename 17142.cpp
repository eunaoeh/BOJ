#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
int n, m, ans, empty_place;
int a[51][51];
vector<pair<int, int> > v;
vector<pair<int, int> > vq;
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

void check(){
    queue<pair<int, int> > q;
    int time[51][51];
    memset(time, -1, sizeof(time));
    for(int i = 0; i < vq.size(); ++i){
        q.push(vq[i]);
        time[vq[i].first][vq[i].second] = 0;
    }
    int spread = 0;
    int t = 0;

    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for(int i = 0; i < 4; ++i){
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if(a[nx][ny] != 1 && time[nx][ny] == -1){
                time[nx][ny] = time[x][y] + 1;
                if(a[nx][ny] == 0){
                    spread++;
                    t = time[nx][ny];
                }
                q.push(make_pair(nx, ny));
            }
        }
    }

    if(spread == empty_place) {
        ans = min(ans, t);
    }
}

void dfs(int idx){
    if(vq.size() == m){
        check();
        return;
    }
    
    for(int i = idx; i < v.size(); ++i){
        vq.push_back(v[i]);
        dfs(i+1);
        vq.pop_back();
    }
}

int main(void){
    ans = 1e9;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            scanf("%d", &a[i][j]);
            if(a[i][j] == 2){
                v.push_back(make_pair(i, j));
            }
            if(a[i][j] == 0) empty_place++;
        }
    }

    dfs(0);
    if(ans == 1e9){
        printf("-1\n");
    }
    else {
        printf("%d\n", ans);
    }
}