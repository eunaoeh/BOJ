// https://www.acmicpc.net/problem/16236
// BFS

#include<iostream>
#include<queue>
#include<cstring>
#include<vector>
using namespace std;
struct shark{
    int x;
    int y;
    int size;
    int eat;
} shark;
int n, ans;
int map[25][25];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};
vector<pair<int, pair<int, int> > > eat;

void bfs(int x, int y){
    int visited[25][25];
    memset(visited, -1, sizeof(visited));

    queue<pair<int, int> > q;
    q.push(make_pair(x, y));
    visited[x][y] = 0;
    eat.clear();
    int distance = 1e9;
    while(!q.empty()){
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();


        for(int i = 0; i < 4; ++i){
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if(nx < 0 || ny < 0 || nx >= n || ny >= n || visited[nx][ny] > -1) continue;
            if(map[nx][ny] > shark.size) continue;

            visited[nx][ny] = visited[cx][cy] + 1;
            q.push(make_pair(nx, ny));
            if (map[nx][ny] < shark.size && map[nx][ny] > 0) {
                eat.push_back(make_pair(visited[nx][ny], make_pair(nx, ny)));

                if(distance > visited[nx][ny]){
                    distance = visited[nx][ny];
                }
            }
        }
    }
}

int main(void){
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            scanf("%d", &map[i][j]);
            if(map[i][j] == 9){
                shark.x = i;
                shark.y = j;
                shark.size = 2;
                shark.eat = 0;
                map[i][j] = 0;
            }
        }
    }
    while(true){
        // ans++;
        bfs(shark.x, shark.y);
        
        if(eat.empty()){
            break;
        } else{
            sort(eat.begin(), eat.end());
            ans += eat[0].first;

            shark.eat++;
            map[eat[0].second.first][eat[0].second.second] = 0;
            shark.x = eat[0].second.first;
            shark.y = eat[0].second.second;

            if(shark.eat == shark.size){
                shark.eat = 0;
                ++shark.size;
            }
        } 
    }
    printf("%d\n", ans);
}
