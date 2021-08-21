#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
int n;
int ans;
int map[25][25];

void up(){
    for(int j = 0; j < n; ++j){
        int k = 0;
        for(int i = 1; i < n; ++i){
            if(map[i][j] == 0) continue;
            else if(map[i][j] != 0){
                int tmp = map[i][j];
                map[i][j] = 0;
                if(tmp==map[k][j]){
                    map[k][j] = tmp*2;
                    k++;
                }
                else if(map[k][j] == 0){
                    map[k][j] = tmp;
                }
                else {
                    k++;
                    map[k][j] = tmp;
                }
            } 
        }
    }
}

void down(){
    for(int j = n-1; j >= 0; --j){
        int k = n-1;
        for(int i = n-2; i >= 0; --i){
            if(map[i][j] == 0) continue;
            else if(map[i][j] != 0){
                int tmp = map[i][j];
                map[i][j] = 0;
                if(tmp==map[k][j]){
                    map[k][j] = tmp*2;
                    k--;
                }
                else if(map[k][j] == 0){
                    map[k][j] = tmp;
                }
                else {
                    k--;
                    map[k][j] = tmp;
                }
            }
        }
    }
}

void left(){
    for(int i = 0; i < n; ++i){
        int k = 0; // 기준점
        for(int j = 1; j < n; ++j){
            if(map[i][j] == 0) continue;
            else if(map[i][j] != 0){
                int tmp = map[i][j];
                map[i][j] = 0;
                if(tmp==map[i][k]){
                    map[i][k] = tmp*2;
                    k++;
                }
                else if(map[i][k] == 0){
                    map[i][k] = tmp;
                }
                else{
                    k++;
                    map[i][k] = tmp;
                }
            } 
        }
    }
}

void right(){
    for(int i = n-1; i >= 0; --i){
        int k = n-1; // 기준점
        for(int j = n-2; j >= 0; --j){
            if(map[i][j] == 0) continue;
            else if(map[i][j] != 0){
                int tmp = map[i][j];
                map[i][j] = 0;
                if(tmp==map[i][k]){
                    map[i][k] = tmp*2;
                    k--;
                }
                else if(map[i][k] == 0){
                    map[i][k] = tmp;
                }
                else{
                    k--;
                    map[i][k] = tmp;
                }
            } 
        }
    }
}

void move(int type){
    switch (type)
    {
    case 0:
        up();
        break;
    case 1:
        down();
        break;
    case 2:
        left();
        break;
    case 3:
        right();
        break;
    }
}

void dfs(int t){
    if(t==5){
        for(int i = 0 ; i< n; ++i){
            for(int j = 0; j<n; ++j){
                ans = max(ans, map[i][j]);
            }
        }
        return;
    }
    int original_map[25][25];
    memcpy(original_map, map, sizeof(map));
    
    for(int i = 0; i < 4; ++i){
        move(i);
        dfs(t+1);
        memcpy(map, original_map, sizeof(original_map));

    }
}

int main(void){
    scanf("%d", &n);
    ans = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            scanf("%d", &map[i][j]);
        }
    }
    if(n==1) printf("%d\n", map[0][0]);
    else {
        dfs(0);
        printf("%d\n", ans);
    }
}