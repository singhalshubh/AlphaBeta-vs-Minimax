#include<bits/stdc++.h>
using namespace std;


struct node {
	int data;
	int alpha;
	int beta;
	int height;
	struct node *left;
	struct node *right;
	struct node *parent;
};
struct node *root;

struct node* create_node(int idata, struct node *nn,int height) {
	nn = new node;
	nn->alpha =INT_MIN;
	nn->beta = INT_MAX;
	nn->left = NULL;
	nn->right = NULL;
	nn->parent = NULL;
	nn->data = idata;
	nn->height = height;
	return nn;
}
int array_index = 0;
vector<int>a;

struct node* create_tree(int height,struct node *n) {
	if(height == 1) {
		n = create_node(-1,n,height);
		n->left = create_node(a[array_index],n->left,0);
		n->left->parent = n;
		n->right = create_node(a[array_index+1],n->right,0);
		n->right->parent = n;
		array_index+=2;
	}
	else if(height > 1) {
		n = create_node(-1,n,height);
		height--;
		n->left = create_tree(height, n->left);
		n->left->parent = n;
		n->right = create_tree(height, n->right);
		n->right->parent = n;
	}
	return n;
}

int print_tree(struct node *nn) {
	if(nn!=NULL) {
	print_tree(nn->left);
	cout<<nn->data;
	print_tree(nn->right);
	}
}

int h;

int alphabeta(struct node *nn) {
	if(nn->height == 0) {
		return nn->data;
	}
	if(nn->height %2 == h%2) {
		int value = INT_MIN;
		value = max(value,alphabeta(nn->left));
		nn->alpha = max(nn->alpha,value);
		if(nn->alpha >= nn->beta) {
			cout<<"Pruning can be seen B-cut"<<endl;
		}
		else {
			value = max(value,alphabeta(nn->right));
			nn->alpha = max(nn->alpha,value);
			if(nn->alpha >= nn->beta) {
				cout<<"Pruning can be seen B-cut"<<endl;
			}
		}
		return value;
	}

	else {

		int value = INT_MAX;
		value = min(value,alphabeta(nn->left));
		nn->beta = min(nn->beta,value);
		if(nn->alpha >= nn->beta) {
			cout<<"Pruning can be seen A-cut"<<endl;
		}
		else {
			value = min(value,alphabeta(nn->right));
			nn->beta = min(nn->beta,value);
			if(nn->alpha >= nn->beta) {
				cout<<"Pruning can be seen A-cut"<<endl;
			}
		}
		return value;
	}
}


int main()
{
	int n;
	// -1 indicates that the node has no value and also indicates that it is not a leaf node
	//n is the number of nodes as leaves in the problem statement
	cin>>n;
	int value = 0;
	for(int i=0;i<n;i++) {
		cin>>value;
		a.push_back(value);
	}
	int height = ceil(log(n)/log(2.0));
	h = height;
	cout<<"Height is:"<< height<<endl;
	//creating the root node
	root = create_tree(height,root);
	cout<<"The max value is :"<<alphabeta(root)<<endl;

}