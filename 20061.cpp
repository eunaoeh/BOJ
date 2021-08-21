#include<iostream>
using namespace std;
int n, ans;
int green[6][4], blue[4][6];

void green_block1(int idx){
    for(int i = 1; i < 6 ; ++i){
        if(green[i][idx] == 1){
            green[i-1][idx] = 1;
            return;
        }
    }
    green[5][idx] = 1;
}

void blue_block1(int idx){
    for(int i = 1; i < 6; ++i){
        if(blue[idx][i] == 1){
            blue[idx][i-1] = 1;
            return;
        }
    }
    blue[idx][5] = 1;
}

void green_block2(int idx){
    for(int i = 1; i < 6; ++i){
        if(green[i][idx] == 1 || green[i][idx+1] == 1){
            green[i-1][idx] = 1;
            green[i-1][idx+1] = 1;
            return;
        }
    }
    green[5][idx] = 1;
    green[5][idx+1] = 1;
}

void blue_block2(int idx){
    for(int i = 2; i < 6; ++i){
        if(blue[idx][i] == 1){
            blue[idx][i-1] = 1;
            blue[idx][i-2] = 1;
            return;
        }
    }
    blue[idx][5] = 1;
    blue[idx][4] = 1;
}

void green_block3(int idx){
    for(int i = 2; i < 6; ++i){
        if(green[i][idx] == 1){
            green[i-1][idx] = 1;
            green[i-2][idx] = 1;
            return;
        }
    }
    green[5][idx] = 1;
    green[4][idx] = 1;
}

void blue_block3(int idx){
    for(int i = 1; i < 6; ++i){
        if(blue[idx][i] == 1 || blue[idx+1][i] == 1){
            blue[idx][i-1] = 1;
            blue[idx+1][i-1] = 1;
            return;
        }
    }
    blue[idx][5] = 1;
    blue[idx+1][5] = 1;
}

void green_move(int idx){
    for(int i = idx; i >= 1; --i){
        for(int j = 0; j < 4; ++j){
            green[i][j] = green[i-1][j];
        }
    }
    for(int i = 0; i < 4; ++i){
        green[0][i] = 0;
    }
}

void green_check(){
    int i = 5;
    while(i >= 2){
        bool flag = true;
        for(int j = 0; j < 4; ++j){
            if(green[i][j] == 0){
                flag = false;
            }
        }
        if(flag){
            ++ans;
            green_move(i);
        } else {
            --i;
        }
    }
    i = 1;
    while(i >= 0){
        bool flag = false;
        for(int j = 0; j < 4; ++j){
            if(green[i][j] == 1){
                flag = true;
            }
        }
        if(flag){
            green_move(5);
        } else {
            --i;
        }
    }
}

void blue_move(int idx){
    for(int i = idx; i >= 1; --i){
        for(int j = 0; j < 4; ++j){
            blue[j][i] = blue[j][i-1];
        }
    }
    for(int i = 0; i < 4; ++i){
        blue[i][0] = 0;
    }
}

void blue_check(){
    int i = 5;
    while(i >= 2){
        bool flag = true;
        for(int j = 0; j < 4; ++j){
            if(blue[j][i] == 0){
                flag = false;
            }
        }
        if(flag){
            ++ans;
            blue_move(i);
        } else {
            --i;
        }
    }
    i = 1;
    while(i >= 0){
        bool flag = false;
        for(int j = 0; j < 4; ++j){
            if(blue[j][i] == 1){
                flag = true;
            }
        }
        if(flag){
            blue_move(5);
        } else{
            --i;
        }
    }
}

int total_block(){
    int blue_cnt = 0;
    int green_cnt = 0;
    for(int i = 2; i < 6; ++i){
        for(int j = 0; j < 4; ++j){
            if(green[i][j] == 1) green_cnt++;
            if(blue[j][i] == 1) blue_cnt++;
        }
    }
    return green_cnt+blue_cnt;
}

int main(void){
    scanf("%d", &n);
    while(n--){    
        int t, x, y;
        scanf("%d %d %d", &t, &x, &y);

        if(t == 1){
            green_block1(y);
            blue_block1(x);
        }
        else if(t == 2){
            // 2x1
            green_block2(y);
            blue_block2(x);
        }
        else if(t == 3){
            // 1x2
            green_block3(y);
            blue_block3(x);
        }
        green_check();
        blue_check();
    }
    printf("%d\n%d\n", ans, total_block());
}