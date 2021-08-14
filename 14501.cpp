#include<iostream>
using namespace std;
int n, ans;
int t[16];
int p[16];

void dfs(int idx, int cnt){
    if(idx+t[idx] > n) return;
    if(idx >= n) return;

    ans = max(ans, cnt);
    for(int i = idx+t[idx]; i < n; ++i){
        dfs(i, cnt+p[i]);
    }
}

int main(void){
    scanf("%d", &n);
    for(int i = 0, a, b; i < n; ++i){
        scanf("%d %d", &a, &b);
        t[i] = a;
        p[i] = b;
    }

    for(int i = 0; i < n; ++i){
        dfs(i, p[i]);
    }

    printf("%d\n", ans);
}