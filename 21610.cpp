#include<iostream>
#include<vector>
using namespace std;
int n, m;
int a[51][51];
int check[51][51];
int dx[] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int dy[] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
vector<pair<int, int> > cloud;

int total_water(){
    int ans = 0;
    for(int i = 1; i <=n; ++i){
        for(int j = 1; j <= n; ++j){
            ans += a[i][j];
        }
    }
    return ans;
}

void action1(int d, int s){
    for(int i = 0; i < cloud.size(); ++i){
        int x = cloud[i].first;
        int y = cloud[i].second;

        for(int j = 0; j < s; ++j){
            x = x + dx[d];
            y = y + dy[d];
            if(x == 0) x = n;
            if(y == 0) y = n;
            if(x == n+1) x = 1;
            if(y == n+1) y = 1;
        }
        cloud[i].first = x;
        cloud[i].second = y;
    }
}

void action2(){
    for(int i = 0; i < cloud.size(); ++i){
        int x = cloud[i].first;
        int y = cloud[i].second;
        a[x][y]++;
        check[x][y] = 1;
    }
}

void action4(){
    int ddx[] = {-1, -1, 1, 1};
    int ddy[] = {-1, 1, -1, 1};
    for(int i = 0, x, y; i < cloud.size(); ++i){
        x = cloud[i].first;
        y = cloud[i].second;
        int cnt = 0;
        for(int j = 0, nx, ny; j < 4; ++j){
            nx = x + ddx[j];
            ny = y + ddy[j];
            if(nx <= 0 || ny <= 0 || nx > n || ny > n) continue;
            if(a[nx][ny] >= 1) cnt++;
        }
        a[x][y] += cnt;
    }
}

void action5(){
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            if(a[i][j] >= 2 && check[i][j] == 0){
                a[i][j] -= 2;
                cloud.push_back(make_pair(i, j));
            }
            else if(check[i][j] == 1){
                check[i][j] = 0;
            }
        }
    }
}

// void print(){
//     for(int i = 1; i <=n; ++i){
//         for(int j = 1; j <= n; ++j){
//             printf("%d ", a[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }

int main(void){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <=n; ++i){
        for(int j = 1; j <= n; ++j){
            scanf("%d", &a[i][j]);
        }
    }
    cloud.push_back(make_pair(n,1));
    cloud.push_back(make_pair(n,2));
    cloud.push_back(make_pair(n-1,1));
    cloud.push_back(make_pair(n-1,2));
    int ans = 0;
    for(int i = 0, d, s; i < m; ++i){
        scanf("%d %d", &d, &s);
        action1(d, s);
        action2();
        action4();
        cloud.clear();
        action5();

    }

    printf("%d\n", total_water());
    return 0;
}