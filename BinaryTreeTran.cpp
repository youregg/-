#include <iostream>
#include <stack>
#include <vector>
#include<queue>

using namespace std;

struct TreeNode
{
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {
	}
};

void preOrder(TreeNode* root);
void preOrderRe(TreeNode* root);
void order(TreeNode* root);
void orderRe(TreeNode* root);
void Morris(TreeNode* root);
void postOrder(TreeNode* root);
void postOrder2(TreeNode* root);
void postOrderRe(TreeNode* root);
void BroadOrder(TreeNode* root);


void initTree(TreeNode* node, int num);

void initTree(TreeNode *node, int value) {
	if (value <= node->val) {
		if (!node->left) {
			node->left = new TreeNode(value);
		}
		else {
			initTree(node->left, value);
		}
	}
	else {
		if (!node->right) {
			node->right = new TreeNode(value);
		}
		else {
			initTree(node->right, value);
		}
	}
}

//层次遍历
void BroadOrder(TreeNode* root) {
	queue<TreeNode* > q;
	if (root != NULL) { q.push(root); }
	while (!q.empty()){
		cout<<q.front()->val;
		if (q.front()->left != NULL) { q.push(q.front()->left); }
		if (q.front()->right != NULL) { q.push(q.front()->right); }
		q.pop();
	}
}

//前序遍历的递归写法
void preOrderRe(TreeNode* root) {	
	if (root == NULL) { return; }
	cout << root->val;
	preOrderRe(root->left);
	preOrderRe(root->right);
}
//中序遍历的递归写法
void orderRe(TreeNode * root)
{
	if (root) {
		orderRe(root->left);
		cout << root->val;
		orderRe(root->right);
	}
}
void Morris(TreeNode * root){
	if (root == NULL) { return;}
	stack <TreeNode* > morS;
	morS.push(root);
	TreeNode* cur = root;
	TreeNode* pre = NULL;
	while (cur!=NULL) {	
		//cout << cur->val;
		if (cur->left == NULL) {
			cout << cur->val;
			cur = cur->right;
		}
		else{
			TreeNode* p = cur->left;
			TreeNode* tmp = p;
			while (p->right != NULL && p->right != cur) {
				p = p->right;
			}
			if (p->right == NULL) {
				p->right = cur;
				cur = tmp;
			}
			else if (p->right == cur) {
				p->right = NULL;
				cout << cur->val;
				cur = cur->right;
			}
		}
	}
}
//后序遍历的递归写法
void postOrderRe(TreeNode * root)
{
	if (root) {
		postOrderRe(root->left);
		postOrderRe(root->right);
		cout << root->val;
	}
}
//前序遍历的非递归写法
void preOrder(TreeNode* root) {
	if (root == NULL) { return; }
	stack <TreeNode*> preS;
	preS.push(root);
	while (!preS.empty()) {
		TreeNode* tmp = preS.top();
		cout << tmp->val;
		preS.pop();
		if (tmp->right) {
			preS.push(tmp->right);
		}
		if (tmp->left) {
			preS.push(tmp->left);
		}
	}
}

//中序遍历非递归
void order(TreeNode * root){
	if (root == NULL) { return; }
	stack<TreeNode*> inS;
	TreeNode* tmp = root;
	while (!inS.empty()|| tmp !=	NULL){
		if (tmp != NULL) {
			inS.push(tmp);
			tmp = tmp->left;
		}
		else {
			tmp = inS.top();
			inS.pop();
			cout << tmp->val;
			tmp = tmp->right;
		}
	}
}

//后序遍历非递归--双栈法
void postOrder(TreeNode * root){
	if (root == NULL) { return; }
	stack<TreeNode*> postS1,postS2;
	postS1.push(root);
	while (!postS1.empty()) {
		TreeNode *tmp = postS1.top();
		postS1.pop();
		postS2.push(tmp);
		if (tmp->left)
			postS1.push(tmp->left);
		if (tmp->right)
			postS1.push(tmp->right);
	}
	while (!postS2.empty()){
		cout << postS2.top()->val;
		postS2.pop();
	}
}

//非双栈法的后序非递归遍历
void postOrder2(TreeNode * root)
{
	if (root == NULL) { return; }
	TreeNode* cur = root;
	TreeNode* pre = NULL;
	stack<TreeNode*> postS;
	while (!postS.empty() || cur != NULL) {
		while (cur != NULL) {
			postS.push(cur);
			cur = cur->left;
		}
		cur = postS.top();
		if (cur->right == NULL || cur->right == pre) {
			cout << cur->val;
			pre = cur;
			postS.pop();
			cur = NULL;
		}
		else {
			cur = cur->right;
		}
	}
}



int main() {
	int n;
	cin >> n;
	n--;
	int value;
	cin >> value;
	TreeNode* root = new TreeNode(value);
	while (n--) {
		int newValue;
		cin >> newValue;
		initTree(root, newValue);
	}
	/*cout << "层次遍历结果：" ;
	BroadOrder(root);
	cout << endl;

	cout << "前序遍历递归结果：" ;
	preOrderRe(root);
	cout << ' ';
	cout << "前序遍历非递归结果：" ;
	preOrder(root);
	cout << endl;*/

	/*cout << "中序遍历递归结果：";
	orderRe(root);
	cout << ' ';
	cout << "中序遍历非递归结果：";
	order(root);
	cout << ' ';*/

	cout << "中序遍历Morris结果：";
	Morris(root);
	cout << endl;

	/*cout << "后序遍历递归结果：";
	postOrderRe(root);
	cout << ' ';
	cout << "后序遍历非递归结果：";
	postOrder(root);*/

}
