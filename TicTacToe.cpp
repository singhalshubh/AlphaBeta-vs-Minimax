#include<bits/stdc++.h>
using namespace std;
//the values that are allocated are because the checkwin() condition should not be true for non allocated space in game
char a[3][3] = {'-', '-', '-','-','-','-','-','-','-'};
//vsisited is for ensuring that how many turns are left and what all are allocated.
int visited[3][3] = {0,0,0,0,0,0,0,0,0};

int equal1(char a,char b ,char c) {
    if(a==b && b==c) {
        return 1;
    }
    else
        return 0;
}

// -1 denotes the comp win and 1 denotes the player win.
char checkWin() {
    if(equal1(a[0][0],a[1][1],a[2][2])) {
        if(a[0][0] == 'x')
            return 'x';
        if(a[0][0] == 'o')
            return 'o';
    }
    
    for(int i=0;i<3;i++) {
        if(equal1(a[i][0] ,a[i][1],a[i][2])) {
            if(a[i][0] == 'x')
                return 'x';
            if(a[i][0] == 'o')
                return 'o';
        }
    }

    for(int i=0;i<3;i++) {
        if(equal1(a[0][i] ,a[1][i],a[2][i])) {
            if(a[0][i] == 'x')
                return 'x';
            if(a[0][i] == 'o')
                return 'o';
        }
    }
    
    return '-';
}

int board_is_full() {
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(a[i][j] == '-')
                return 0;
        }
    }
    return 1;
}


pair<pair<int,int>,int> Alphabeta(char state ,char temp[3][3], int v[3][3], int depth, int alpha, int beta) {
    pair<int, int> best_mov = make_pair(-1, -1);
    int best = (state == 'x')? -10:10;
    if (board_is_full())
    {
        best = checkWin();
        return make_pair(best_mov, best);
    }
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(v[i][j] == 0) {
                temp[i][j] = state;
                pair<int, int> curr_mov = make_pair(i,j);
                v[i][j] = 1;
                if(state == 'o') {
                    int value = Alphabeta('x', temp, v, depth+1, alpha , beta).second;
                        best_mov = curr_mov;  
                        alpha = max(alpha, best);
                        if(alpha>=beta) {
                            cout<<"Pruning has occured"<<endl;
                            break;
                    }
                }
                else {
                    
                    int value = Alphabeta('o', temp, v, depth+1, alpha , beta).second;
                        best_mov = curr_mov;  
                        beta = min(beta, best);
                        temp[i][j] = '-';
                        if(alpha>=beta) {
                            cout<<"Pruning has occured"<<endl;
                            break;
                    }
                }
                temp[i][j] = '-';

            }
        }

    }
    return make_pair(best_mov, best);
}

int main() {
    //-1 is for oval and 1 is for cross(Player)
    //n is the number of turns
    int n = 0;
    int rw,cl;
    char temp[3][3];
    int v[3][3];
    while(n<=9) {
        cout<<"Player : "<< endl;
        cout<<"Whats the row position"<<endl;
        cin>>rw;
        cout<<"Whats the col position"<<endl;
        cin>>cl;
        a[rw][cl] = 'x';
        visited[rw][cl] = 1; //indicates that it is visited
        if(checkWin() == 'x') {
            cout<<"Player wins"<<endl;
            break;
        }
        if(checkWin() == 'o') {
            cout<<"Comp wins"<<endl;
        }
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                temp[i][j] = a[i][j];
            }
        }
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                v[i][j] = visited[i][j];
            }
        }
        pair<pair<int,int>,int> mov = Alphabeta('o',temp,v,0,INT_MIN,INT_MAX);
        rw = mov.first.first;
        cl = mov.first.second;
        cout<<rw<<cl<<endl;
        a[rw][cl] = 'o';
        visited[rw][cl] = 1;
        if(checkWin() == 'x') {
            cout<<"Player wins"<<endl;
            break;
        }
        if(checkWin() == 'o') {
            cout<<"Comp wins"<<endl;
        }

        for(int i=0;i<3;i++) {
            cout<<endl;
            for(int j=0;j<3;j++) {
                    cout<<a[i][j]<<" ";
            }
        }
        n = n-2;
    }
    if(n==9) {
        cout<<"DRAW"<<endl;
    }

}