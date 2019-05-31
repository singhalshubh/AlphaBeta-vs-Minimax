#include<bits/stdc++.h>
#define INF 200
#define MINF -200
using namespace std;


struct node {
	int data;
	int lalpha;
	int ralpha;
	int lbeta;
	int rbeta;
	int height;
	struct node *left;
	struct node *right;
	struct node *parent;
};
struct node *root;

struct node* create_node(int idata, struct node *nn,int height) {
	nn = new node;
	nn->lalpha = nn->ralpha =  INF;
	nn->lbeta = nn->rbeta = MINF;
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

int height;

int alphabeta(struct node *nn) {
	if(nn->left->data!=-1 && nn->right->data !=-1) {
		if(nn->height %2 == height %2) {
			nn->data = max(nn->left->data , nn->right->data);
		}
		if(nn->height %2 != height %2) {
			nn->data = min(nn->left->data , nn->right->data);
		}
		return nn->data;
	}
	if(nn->left->data==-1 || nn->right->data ==-1) {
		if(nn->height %2 == height %2) {
			nn->data = max(alphabeta(nn->left), alphabeta(nn->right));
		}
		if(nn->height %2 != height %2) {
			nn->data = min(alphabeta(nn->left), alphabeta(nn->right));
		}
		return nn->data;
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
	height = ceil(log(n)/log(2.0));
	cout<<"Height is:"<< height<<endl;
	//creating the root node
	root = create_tree(height,root);
	alphabeta(root);
	cout<<"The max value is :"<<root->data;

}