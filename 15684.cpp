#include<iostream>
#include<algorithm>
using namespace std;
int n, m, h, ans;
int bridge[31][11];

bool check(){
    for(int i = 1; i <= n; ++i){
        int pos = i;
        for(int j = 1; j <=h; ++j){
            if(bridge[j][pos] == 1) pos++;
            else if(bridge[j][pos-1] == 1) pos--;
        }
        if(i!=pos){
            return false;
        }
    }
    return true;
}

void dfs(int depth, int k){
    if(ans != 5) return;

    if(depth > k){
        if(check()) ans = k;
        return;
    }

    for(int j = 1; j < n; ++j){
        
        for(int i = 1; i <= h; ++i){
            if(bridge[i][j+1] || bridge[i][j] || bridge[i][j-1]) continue;

            bridge[i][j] = 1;
            dfs(depth+1, k);
            bridge[i][j] = 0;
            while (i < h) {
				if (bridge[i][j - 1] || bridge[i][j + 1]) break;
				i++;
			}
            
        }
    }
}


int main(void){
    scanf("%d %d %d", &n, &m, &h);
    for(int i = 0; i < m; ++i){
        int a, b;
        scanf("%d %d", &a, &b);
        bridge[a][b] = 1;
    }
    ans = 5;
    for(int i = 0; i <= 3; ++i){
        dfs(1, i);
        if(ans != 5){
            printf("%d\n", ans);
            return 0;
        }
    }
    printf("-1\n");
}