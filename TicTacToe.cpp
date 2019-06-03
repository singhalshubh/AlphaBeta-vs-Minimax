#include<bits/stdc++.h>
using namespace std;
//the values that are allocated are because the checkwin() condition should not be true for non allocated space in game
char a[3][3] = {'-', '-', '-','-','-','-','-','-','-'};
//vsisited is for ensuring that how many turns are left and what all are allocated.
int visited[3][3] = {0,0,0,0,0,0,0,0,0};

int equal1(char a,char b, char c) {
    if(a==b && b==c) {
        return 1;
    }
    else
        return 0;
}

// -1 denotes the comp win and 1 denotes the player win.
char checkWin() {
    if(equal1(a[0][0],a[1][1],'x') || equal1(a[2][2],a[1][1],'x')  || equal1(a[0][0],a[2][2],'x') ) {
            return 'x';
        }
        if(equal1(a[0][0],a[1][1],'o') || equal1(a[2][2],a[1][1],'o')  || equal1(a[0][0],a[2][2],'o') ) {
            return 'o';
        }
    
    for(int i=0;i<3;i++) {
        if(equal1(a[i][1],a[i][2],'x') || equal1(a[i][0] ,a[i][2],'x') || equal1(a[i][0] ,a[i][1],'x'))
                return 'x';
        if(equal1(a[i][1],a[i][2],'o') || equal1(a[i][0] ,a[i][2],'o') ||equal1(a[i][0] ,a[i][1],'o'))
                return 'o';
        

    for(int i=0;i<3;i++) {
        if(equal1(a[0][i] ,a[2][i],'x') || equal1(a[0][i] ,a[1][i],'x') || equal1(a[1][i],a[2][i],'x') )
                return 'x';
        if(equal1(a[0][i] ,a[2][i],'o') || equal1(a[0][i] ,a[1][i],'o') || equal1(a[1][i],a[2][i],'o') )
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

char IsWin(char a[][3], char state) {
    if(equal1(a[0][0],a[1][1],a[2][2])) {
        if(a[0][0] == state)
            return 'W';
        if(a[0][0] != state && a[0][0]!='-')
            return 'L';
    }
    
    for(int i=0;i<3;i++) {
        if(equal1(a[i][0] ,a[i][1],a[i][2])) {
            if(a[i][0] == state)
                return 'W';
            if(a[i][0] != state && a[i][0]!='-')
                return 'L';
        }
    }

    for(int i=0;i<3;i++) {
        if(equal1(a[0][i] ,a[1][i],a[2][i])) {
            if(a[0][i] == state)
                return 'W';
            if(a[0][i] != state && a[0][i]!='-')
                return 'L';
        }
    }
    
    return '-';
}

int print_state(char a[][3]) {
        for(int i=0;i<3;i++) {
            cout<<endl;
            for(int j=0;j<3;j++) {
                    cout<<a[i][j]<<" ";
            }
            cout<<endl;
        }
}

pair<pair<int,int>,int> Alphabeta(char state ,char temp[3][3], int v[3][3], int depth, int alpha, int beta) {
    pair<int, int> best_mov = make_pair(-1, -1);
    int best = 0;
    state == 'o'? best = -1000: best = 1000;
    if (board_is_full() || IsWin(temp,state)!='-' )
    {   cout<<"Leaf Reached";
        print_state(temp);
        if(IsWin(temp,state) == 'L')
            best = -1000;
        if(IsWin(temp,state) == 'W')
            best = 1000;
        return make_pair(best_mov, best);
    }
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(v[i][j] == 0) {
                temp[i][j] = state;
                pair<int, int> curr_mov = make_pair(i,j);
                v[i][j] = 1;
                print_state(temp);
                if(state == 'o') {
                    int value = Alphabeta('x', temp, v, depth+1, alpha , beta).second;
                    cout<<best<<" "<<value<<endl;
                        if(best<value) {
                            best = value - depth * 10;
                            best_mov = curr_mov;
                            alpha = max(alpha, best);
                            if(alpha>=beta) {
                                cout<<"Pruning has occured"<<endl;
                                break;
                        }
                    }
                }
                if(state == 'x') {
                    
                    int value = Alphabeta('o', temp, v, depth+1, alpha , beta).second;
                    print_state(temp);
                        if(best>value) {
                            best = value + depth * 10;
                            best_mov = curr_mov;  
                            beta = min(beta, best);
                            if(alpha>=beta) {
                                cout<<"Pruning has occured"<<endl;
                                break;
                        }
                    }
                }
                temp[i][j] == '-';

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
        if(IsWin(a,'x') == 'W') {cout<<"Player Wins"; break;}
        if(IsWin(a,'o') == 'W') {cout<<"Comp Wins"; break;}
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
        a[rw][cl] = 'o';
        visited[rw][cl] = 1;
        if(IsWin(a,'x') == 'W') {cout<<"Player Wins"; break;}
        if(IsWin(a,'o') == 'W') {cout<<"Comp Wins"; break;}
        for(int i=0;i<3;i++) {
            cout<<endl;
            for(int j=0;j<3;j++) {
                    cout<<a[i][j]<<" ";
            }
            cout<<endl;
        }
        n = n-2;
    }
    if(n==9) {
        cout<<"DRAW"<<endl;
    }

}