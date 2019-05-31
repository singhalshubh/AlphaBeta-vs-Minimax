#include<bits/stdc++.h>
using namespace std;
//the values that are allocated are because the checkwin() condition should not be true for non allocated space in game
int a[3][3]={2,3,4,5,6,7,8,9,10};
//vsisited is for ensuring that how many turns are left and what all are allocated.
int visited[3][3] = {0,0,0,0,0,0,0,0,0};
string win = "win";
string win1 = "win1";
string draw = "draw";
// -1 denotes the comp win and 1 denotes the player win.
int checkWin() {
	if((a[1][1] == 1) && (a[2][2] == 1) && a[3][3] == 1)
		return 1;
	for(int i=0;i<3;i++) {
		if(a[i][0] == 1 && a[i][1] == 1 && a[i][2] == 1)
			return 1;
	}
	for(int i=0;i<3;i++) {
		if(a[0][i] == 1 && a[1][i] ==1 && a[2][i] == 1)
			return 1;
	}
	if((a[1][1] == -1) && (a[2][2] == -1) && a[3][3] == -1)
		return -1;
	for(int i=0;i<3;i++) {
		if(a[i][0] == -1 && a[i][1] == -1 && a[i][2] == -1)
			return -1;
	}
	for(int i=0;i<3;i++) {
		if(a[0][i] == -1 && a[1][i] == -1 && a[2][i] == -1)
			return -1;
	}
	return 0;
}

int board_is_full() {
	for(int i=0;i<3;i++) {
		for(int j=0;j<3;j++) {
			if(a[i][j] >= 2)
				return 0;
		}
	}
	return 1;
}

pair<pair<int,int>,int> Alphabeta(int state ,int temp[3][3], int v[3][3], int depth, int alpha, int beta) {
	pair<int, int> best_mov = make_pair(-1, -1);
	int best = (state == -1)? -1:1;
	int y;
	if (board_is_full())
	{
		best = checkWin();
		return make_pair(best_mov, best);
	}
	for(int i=0;i<3;i++) {
		for(int j=0;j<3;j++) {
			if(v[i][j] == 0) {
				y = temp[i][j];
				temp[i][j] = state;
				pair<int, int> curr_mov = make_pair(i,j);
				v[i][j] = 1;
				if(state == -1) {
					int value = Alphabeta(state+2, temp, v, depth+1, alpha , beta).second;
						best_mov = curr_mov;  
						alpha = max(alpha, best);
						if(alpha>=beta) {
							cout<<"Pruning has occured"<<endl;
							break;
					}
				}
				else {
					
					int value = Alphabeta(state-2, temp, v, depth+1, alpha , beta).second;
						best_mov = curr_mov;  
						beta = min(beta, best);
						temp[i][j] = y;
						if(alpha>=beta) {
							cout<<"Pruning has occured"<<endl;
							break;
					}
				}
				temp[i][j] = y;

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
	int temp[3][3] ,v[3][3];
	while(n<=9) {
		cout<<"Player : "<< endl;
		cout<<"Whats the row position"<<endl;
		cin>>rw;
		cout<<"Whats the col position"<<endl;
		cin>>cl;
		a[rw][cl] = 1;
		visited[rw][cl] = 1; //indicates that it is visited
		if(checkWin() == 1) {
			cout<<"Player wins"<<endl;
			break;
		}
		if(checkWin() == -1) {
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
		pair<pair<int,int>,int> mov = Alphabeta(-1,temp,v,0,INT_MIN,INT_MAX);
		rw = mov.first.first;
		cl = mov.first.second;
		cout<<rw<<cl<<endl;
		a[rw][cl] = -1;
		visited[rw][cl] = 1;
		if(checkWin() == -1) {
			cout<<"Comp wins"<<endl;
		}
		if(checkWin() == 1) {
			cout<<"Player wins"<<endl;
			break;
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