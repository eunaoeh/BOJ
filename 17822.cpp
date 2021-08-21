#include<iostream>
#include<cstring>
using namespace std;
int n, m, t;
int a[51][51];
bool del[51][51];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void print(){
    printf("\n------\n");
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void turn_clockwise(int idx){
    int tmp = a[idx][m];
    for(int i = m; i >= 2; --i){
        a[idx][i] = a[idx][i-1];
    }
    a[idx][1] = tmp;
}

void turn_counter_clockwise(int idx){
    int tmp = a[idx][1];
    for(int i = 1; i <= m-1; ++i){
        a[idx][i] = a[idx][i+1];
    }
    a[idx][m] = tmp;
}

bool check(int x, int y){
    bool flag = false;
    for(int i = 0; i < 4; ++i){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx <= 0) continue;
        if(nx > n) continue;
        if(ny <= 0) ny = m;
        if(ny > m) ny = 1;

        if(a[nx][ny] == a[x][y]){
            del[x][y] = true;
            del[nx][ny] = true;
            flag = true;
        }
    }
    return flag;
}

void remove(){
    int sum = 0;
    int cnt = 0;
    bool flag = false;
    memset(del, false, sizeof(del));

    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            if(a[i][j] == -1) continue;
            if(del[i][j]) continue;
            sum += a[i][j];
            cnt++;
            check(i, j);
            
        }
    }
    
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            if(del[i][j]){
                a[i][j] = -1;
                flag = true;
            }
        }
    }

    if(!flag) {
        double num = (double)sum / (double)cnt;
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= m; ++j){
                if(a[i][j] == -1) continue;
                if((double) a[i][j] > num){
                    a[i][j]--;
                }
                else if((double) a[i][j] < num){
                    a[i][j]++;
                }
            }
        }
    }
}

void solve(){
    while(t--){
        int x, d, k;
        scanf("%d %d %d", &x, &d, &k);
        if(d == 0){
            for(int i = x; i <= n; i+=x){
                for(int j = 0; j < k; ++j){
                    turn_clockwise(i);
                }               
            }
        }
        else if (d == 1){
            for(int i = x; i <= n; i+=x){
                for(int j = 0; j < k; ++j){
                    turn_counter_clockwise(i);
                }
            }
        }
        remove();
    }
}

int count_total(){
    int ans = 0;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            if(a[i][j] == -1) continue;
            ans += a[i][j];
        }
    }
    return ans;
}

int main(void){
    scanf("%d %d %d", &n, &m, &t);
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            scanf("%d", &a[i][j]);
        }
    }
    solve();
    printf("%d\n", count_total());
}