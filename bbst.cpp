//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define RED 1
#define BLACK 2

ifstream fs;
int num = 0;

struct node {	//structure of the nodes for the red black trees
	int id;
	int count;
	struct node *left, *right, *p;
	int color;
};

typedef struct node *p_node;
struct node fool;
p_node n_ptr = &fool;

void insert(p_node *root, int ip, int cou);		//function definition
void delnode(p_node *root, int ip);		//function definition

p_node search(p_node root, int id) {	//searches for the given id recursively
	if (root == n_ptr || root->id == id)	//returns nullptr if not present
		return root;
	if (id < root->id)
		return search(root->left, id);
	else
		return search(root->right, id);
}

p_node min(p_node root) {	//finds the leftmost node of the tree rooted at root and returns it
	while (root->left != n_ptr)
		root = root->left;
	return root;
}

int Count(p_node root, int id) {	//searches for the node with given id and returns the count of that node
	p_node temp = search(root, id);
	if (temp == n_ptr) {
		return 0;
	}
	return temp->count;
}

p_node max(p_node root) {	//returns the right most node of the tree rooted at root
	while (root->right != n_ptr)
		root = root->right;
	return root;
}

void increase(p_node root, int id, int m) {		//increase function to increase the count value of the node of the given id
	p_node temp = search(root, id);		//search is called to know if the id is present
	if (temp == n_ptr) {
		insert(&root, id, m);		//if the id is not present, it is inserted
		cout << m << endl;
	}
	else {		//if the id is present the count is incremented and printed
		temp->count += m;
		cout << temp->count << endl;
	}
}

void decrease(p_node root, int id, int m) {		//reduce function to decrease the count value of the node of the given id
	p_node temp = search(root, id);		//searches to find if id is present
	if (temp->count - m <= 0) {		//if the difference goes below 0, the node is deleted and 0 is printed
		delnode(&root, id);
		cout << "0" << endl;
	}
	else {
		temp->count -= m;		//otherwise, the count is decremented and printed
		cout << temp->count << endl;
	}
}

p_node next(p_node root, int id) {		//next function to find the next node of the node with the given id
	p_node t = search(root, id);		//searches to find if the id is present
	if (t == n_ptr) {					//if the id is not present, searches to find the closest node
		p_node trv;
		trv = root;
		int flag = 0;
		while (flag != 1) {
			if (trv->id < id) {
				if (trv->right != n_ptr) {
					trv = trv->right;
				}
				else
					flag = 1;
			}
			else if (trv->id > id) {
				if (trv->left != n_ptr) {
					trv = trv->left;
				}
				else
					flag = 1;
			}
		}
		if (trv->id < id)		//if the reached node's id is less than the given id, the next node is found
			return next(root, trv->id);
		else if (trv->id > id)	//else the pointer to the reached node is returned
			return trv;
	}
	else {		//if the node is present, finds the next node
		if (t->right != n_ptr)	//if there is a right subtree, the leftmost node is returned
			return min(t->right);
		p_node temp = t->p;
		while (temp != n_ptr && t == temp->right) {
			t = temp;
			temp = temp->p;
		}
		return temp;	//the appropriate next node is found and returned
	}
}

p_node previous(p_node root, int id) {	//previous function to find the previous node of the node with the given id
	p_node t = search(root, id);	//searches to find if the id is present
	if (t == n_ptr) {		//if the id is not present, searches to find the closest node
		p_node trv;
		trv = root;
		int flag = 0;
		while (flag != 1) {
			if (trv->id < id) {
				if (trv->right != n_ptr) {
					trv = trv->right;
				}
				else
					flag = 1;
			}
			else if (trv->id > id) {
				if (trv->left != n_ptr) {
					trv = trv->left;
				}
				else
					flag = 1;
			}
		}
		if (trv->id < id)	//if the reached nodes id is less  than the given id, return the reached node
			return trv;
		else if (trv->id > id)	//else find the previous node of the reached node and return it
			return previous(root, trv->id);
	}
	else {	// if the id is present, finds the previous node
		if (t->left != n_ptr)
			return max(t->left);	//if there is a left subtree, finds the rightmost node of the subtree
		p_node temp = t->p;
		while (temp != n_ptr && t == temp->left) {
			t = temp;
			temp = temp->p;		//else finds the appropriate node
		}
		return temp;			//and returns it
	}
}

void leftrot(p_node *root, p_node ip) {	//left rotate
	p_node temp = ip->right;
	ip->right = temp->left;
	if (temp->left != n_ptr)
		temp->left->p = ip;		
	temp->p = ip->p;
	if (ip->p == n_ptr)
		*root = temp;
	else if (ip->p->left == ip)
		ip->p->left = temp;
	else
		ip->p->right = temp;
	temp->left = ip;
	ip->p = temp;
}

void rightrot(p_node *root, p_node ip) {	//right rotate
	p_node temp = ip->left;
	ip->left = temp->right;
	if (temp->right != n_ptr)
		temp->right->p = ip;
	temp->p = ip->p;
	if (ip->p == n_ptr)
		*root = temp;
	else if (ip->p->left == ip)
		ip->p->left = temp;
	else
		ip->p->right = temp;
	temp->right = ip;
	ip->p = temp;
}

void insertfix(p_node *root, p_node ip) {	//insertfix function to fix the anamolies caused due to insert
	while (ip->p->color == RED) {
		if (ip->p == ip->p->p->left) {	// if the parent of the input is the left child of its parent
			p_node y = ip->p->p->right;		//consider the right subtree
			if (y->color == RED) {//if ips parents color is black
				ip->p->color = BLACK;
				y->color = BLACK;
				ip->p->p->color = RED;
				ip = ip->p->p;
			}
			else {	//if ips parents color is black
				if (ip == ip->p->right) {	//if ip is the right child of its parent
					ip = ip->p;
					leftrot(root, ip);
				}
				ip->p->color = BLACK;
				ip->p->p->color = RED;
				rightrot(root, ip->p->p);
			}
		}
		else {		//if the parent of the input is the right child of its parent
			p_node y = ip->p->p->left;	//consider the left subtree
			if (y->color == RED) {	//fix if the color is red
				ip->p->color = BLACK;
				y->color = BLACK;
				ip->p->p->color = RED;
				ip = ip->p->p;
			}
			else {	//if the color is black
				if (ip == ip->p->left) {	//if ip is the left child of its parent
					ip = ip->p;
					rightrot(root, ip);
				}
				ip->p->color = BLACK;
				ip->p->p->color = RED;
				leftrot(root, ip->p->p);
			}
		}
	}
	(*root)->color = BLACK;
}

void insert(p_node *root, int ip, int cou) {	//insert function to insert a node
	p_node temp = new node;
	temp->id = ip;
	temp->count = cou;
	p_node check = n_ptr;
	p_node troot = *root;
	while (troot != n_ptr) {	//reaching the position to insert the node
		check = troot;
		if (temp->id < troot->id)
			troot = troot->left;
		else
			troot = troot->right;
	}
	temp->p = check;
	if (check == n_ptr)
		*root = temp;
	else if (temp->id < check->id)
		check->left = temp;
	else
		check->right = temp;
	temp->left = n_ptr;
	temp->right = n_ptr;
	temp->color = RED;
	insertfix(root, temp);	//calling the insert fix function
}

void transplant(p_node *root, p_node a, p_node b) {	//transplant function
	if (a->p == n_ptr)
		*root = b;
	else if (a == a->p->left)
		a->p->left = b;
	else
		a->p->right = b;
	b->p = a->p;
}

void deletefix(p_node *root, p_node ip) {	//deletefix to fix the anamolies after deleting a node
	while (ip != *root && ip->color == BLACK) {
		if (ip == ip->p->left) {		//if ip is the left child of its parent
			p_node par = ip->p->right;
			if (par->color == RED) {
				par->color = BLACK;
				ip->p->color = RED;
				leftrot(root, ip->p);
				par = ip->p->right;
			}
			if (par->left->color == BLACK && par->right->color == BLACK) {
				par->color = RED;
				ip = ip->p;
			}
			else {
				if (par->right->color == BLACK) {
					par->left->color = BLACK;
					par->color = RED;
					rightrot(root, par);
					par = ip->p->right;
				}
				par->color = ip->p->color;
				ip->p->color = BLACK;
				par->right->color = BLACK;
				leftrot(root, ip->p);
				ip = *root;
			}
		}
		else {		//if ip is the right child of its parent
			p_node par = ip->p->left;
			if (par->color == RED) {
				par->color = BLACK;
				ip->p->color = RED;
				rightrot(root, ip->p);
				par = ip->p->left;
			}
			if (par->left->color == BLACK && par->right->color == BLACK) {
				par->color = RED;
				ip = ip->p;
			}
			else {
				if (par->left->color == BLACK) {
					par->right->color = BLACK;
					par->color = RED;
					leftrot(root, par);
					par = ip->p->left;
				}
				par->color = ip->p->color;
				ip->p->color = BLACK;
				par->left->color = BLACK;
				rightrot(root, ip->p);
				ip = *root;
			}
		}
	}
	ip->color = BLACK;
}

void delnode(p_node *root, int ip) {	//delete the node with the given id
	p_node trv = search(*root, ip);	//searches to find if ip is present
	if (trv == n_ptr) {
		return;
	}
	p_node next = trv;
	int color = next->color;
	p_node temp;
	if (trv->left == n_ptr) {
		temp = trv->right;
		transplant(root, trv, trv->right);
	}
	else if (trv->right == n_ptr) {
		temp = trv->left;
		transplant(root, trv, trv->left);
	}
	else {
		next = min(trv->right);
		color = next->color;
		temp = next->right;
		if (next->p == trv)
			temp->p = next;
		else {
			transplant(root, next, next->right);
			next->right = trv->right;
			next->right->p = next;
		}
		transplant(root, trv, next);
		next->left = trv->left;
		next->left->p = next;
		next->color = trv->color;
	}
	if (color == BLACK)
		deletefix(root, temp);	//calling deletefix function if the node is black
}

void inrange(p_node root, int id1, int id2) {	//inrange function to give the count of nodes in the ranges of given ids
	if (root == n_ptr)
		return;
	if (id1 < root->id)
		inrange(root->left, id1, id2);	//recursively calling the inrange function
	if (id1 <= root->id && id2 >= root->id)
		++num;	//if inrange increment the variable(global)
	if (id2 > root->id)
		inrange(root->right, id1, id2);
}

int main(int argc, char *argv[])
{
	int nos = 0, id = 0, count = 0;
	p_node tree = n_ptr;
	fool.color = BLACK;
	fool.left = fool.right = fool.p = n_ptr;
	fs.open(argv[1]);
	fs >> nos;
	for (int i = 0; i < nos; ++i) {
		fs >> id >> count;
		insert(&tree, id, count);
	}
	string command;
	int v_id, v_m;
	while (1) {
		cin >> command;		//taking the command since the first input is a string
		if (command.compare("quit") == 0)
			break;
		v_id = 0; v_m = 0;
		if (command.compare("increase") == 0) {	//to call increase function
			cin >> v_id;
			cin >> v_m;
			increase(tree, v_id, v_m);
		}
		else if (command.compare("reduce") == 0) {	//to call decrease function
			cin >> v_id;
			cin >> v_m;
			decrease(tree, v_id, v_m);
		}
		else if (command.compare("count") == 0) {	//to call count function
			cin >> v_id;
			cout << Count(tree, v_id) << endl;
		}
		else if (command.compare("inrange") == 0) {	//to call inrange function
			cin >> v_id; cin >> v_m; num = 0;
			inrange(tree, v_id, v_m); cout << num << endl;
		}
		else if (command.compare("next") == 0) {	//to call next function
			cin >> v_id;
			cout << next(tree, v_id)->id << endl;
		}
		else if (command.compare("previous") == 0) {		//to call previous function
			cin >> v_id;
			cout << previous(tree, v_id)->id << endl;
		}
	}
	return 0;
}
