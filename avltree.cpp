#include<iostream>
using namespace std;

struct AVLNode {
	int data;
	AVLNode* left;
	AVLNode* right;
	int height;
};

struct AVLTree {
	AVLNode* root;
	int count;
};

AVLNode* CreateNewNode(int data);
void NLR(AVLNode* root);
void LNR(AVLNode* root);
void LRN(AVLNode* root);
bool findNode(AVLNode* root, int data);
int getHeightNode(AVLNode* root);
AVLNode* rightRotate(AVLNode* p);
AVLNode* leftRotate(AVLNode* p);
int getBalance(AVLNode* p);
AVLNode* InsertNode(AVLNode*& root, int data);
AVLNode* findMaxValueNode_Left(AVLNode* p);
AVLNode* DeleteNode(AVLNode* root, int data);

AVLNode* CreateNewNode(int data) {
	AVLNode* p = new AVLNode;
	p->data = data;
	p->height = 1;
	p->left = NULL;
	p->right = NULL;
	return p;
}

void NLR(AVLNode* root) {
	if (root == NULL)return;
	cout << root->data << " ";
	NLR(root->left);
	NLR(root->right);
}

void LNR(AVLNode* root) {
	if (root == NULL)return;
	LNR(root->left);
	cout << root->data << " ";
	LNR(root->right);
}

void LRN(AVLNode* root) {
	if (root == NULL)return;
	LRN(root->left);
	LRN(root->right);
	cout << root->data << " ";
}

bool findNode(AVLNode* root, int data) {
	if (root == NULL)return false;
	if (data < root->data)return findNode(root->left, data);
	else if (data > root->data) return findNode(root->right, data);
	else return true;
	return false;
}

int getHeightNode(AVLNode* root) {
	if (root == NULL)return 0;
	return 1 + max(getHeightNode(root->left), getHeightNode(root->right));
}

AVLNode* rightRotate(AVLNode* p) {
	AVLNode* x = p->left;
	p->left = x->right;
	x->right = p;
	p->height = getHeightNode(p);
	x->height = getHeightNode(x);
	return x;
}

AVLNode* leftRotate(AVLNode* p) {
	AVLNode* y = p->right;
	p->right = y->left;
	y->left = p;
	p->height = getHeightNode(p);
	y->height = getHeightNode(y);
	return y;
}

int getBalance(AVLNode* p) {
	if (p == NULL)
		return 0;
	return getHeightNode(p->left) - getHeightNode(p->right);
}

AVLNode* InsertNode(AVLNode*& root, int data) {
	if (root == NULL) {
		AVLNode* p = CreateNewNode(data);
		return p;
	}
	if (data > root->data) root->right = InsertNode(root->right, data);
	else if (data < root->data) root->left = InsertNode(root->left, data);
	else return root;
	root->height = getHeightNode(root);
	int delta = getBalance(root);
	//left left
	if (delta > 1 && data < root->left->data) return rightRotate(root);
	//right right
	if (delta<-1 && data > root->right->data) return leftRotate(root);
	//left right
	if (delta > 1 && data > root->left->data) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	//right left
	if (delta < -1 && data < root->right->data) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

AVLNode* findMaxValueNode_Left(AVLNode* p) {
	AVLNode* tmp = p;
	while (tmp->right != NULL) {
		tmp = tmp->right;
	}
	return tmp;
}

AVLNode* DeleteNode(AVLNode* root, int data) {
	if (root == NULL)return root;
	if (data < root->data) {
		root->left = DeleteNode(root->left, data);
	}
	else if (data > root->data) {
		root->right = DeleteNode(root->right, data);
	}
	else {
		if ((root->left == NULL) || (root->right == NULL)) {
			AVLNode* tmp = (root->left) ? (root->left) : (root->right);
			if (tmp == NULL) { // nếu không có con nào
				tmp = root;
				root = NULL;
			}
			else { //nếu có 1 con
				*root = *tmp;
			}
			delete[] tmp;
		}
		else { //nếu có 2 con
			AVLNode* tmp = findMaxValueNode_Left(root->left);
			root->data = tmp->data;
			root->left = DeleteNode(root->left, tmp->data);
		}
	}

	if (root == NULL)return root;
	root->height = getHeightNode(root);
	int delta = getBalance(root);
	//Left Left Case
	if (delta > 1 && getBalance(root->left) >= 0) {
		return rightRotate(root);
	}
	//Left Right Case
	if (delta > 1 && getBalance(root->left) < 0) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	//Right Right Case
	if (delta < -1 && getBalance(root->right) <= 0) {
		return leftRotate(root);
	}
	//Right Left Case
	if (delta < -1 && getBalance(root->right) > 0) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

int main() {
	int i = 0;
	AVLTree a;
	a.count = 0;
	a.root = NULL;
	a.root = InsertNode(a.root, 10);
	a.root = InsertNode(a.root, 20);
	a.root = InsertNode(a.root, 5);
	a.root = InsertNode(a.root, 7);
	a.root = InsertNode(a.root, 9);
	a.root = InsertNode(a.root, 8);
	a.root = DeleteNode(a.root, 9);
	NLR(a.root);
	return 0;
}