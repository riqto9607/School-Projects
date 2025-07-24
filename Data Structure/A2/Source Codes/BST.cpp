#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

//Qb
bool BST::deepestNodes() {

	BTNode* cur;
	Queue q;
	int height = 1;
	int treeheight = treeHeight(root);

	//base case
	if (empty()) {
		cout << "Cannot print in empty tree.\n\n";
		return false;
	}

	q.enqueue(root); // Insert root node into queue

	cout << "Student ID in deepest nodes:\n";

	while (!q.empty()) {

		int nodesinCurrentLevel = q.size(); // Everytime loop will reload queue size

		for (int i = 0; i < nodesinCurrentLevel; i++) { // Loop level-by-level

			q.dequeue(cur); // Remove the first node in queue and store it into 'cur'

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);

			if (height == treeheight)
				cout << cur->item.id << " ";

		}

		height++;

	}
	cout << "\n\n";
	return true;
}

int BST::treeHeight(BTNode* cur) {

	if (cur == NULL)
		return 0;

	int leftHeight = treeHeight(cur->left);
	int rightHeight = treeHeight(cur->right);

	return max(leftHeight, rightHeight) + 1;
	// If left and right node is NULL, return 1
	// Else if left or right node is exist, return n+1

}

//Qc
bool BST::display(int order, int source) {
	Student student;	//declarations
	ofstream out;

	if (empty()) {		//special case 
		cout << "\n[Empty tree] Please try again later...\n";
		return false;
	}

	switch (source) {
	case 1:	//print to screen
		if (order == 1) {	//print in ascending order
			if (root != NULL) printAsc(cout, root);
			cout << "Successfully display output.\n";
			return true;
		}
		if (order == 2) {	//print in descending order
			if (root != NULL) printDesc(cout, root);
			cout << "Successfully display output.\n";
			return true;
		}
		else cout << "Invalid option!\n";
		break;

	case 2:	//print to file
		out.open("student-info.txt");
		cout << "\n\n";
		if (order == 1) {	//print in ascending order
			if (root != NULL) printAsc(out, root);
			cout << "Successfully print to file.\n";
			return true;
		}

		if (order == 2) {	//print in descending order
			if (root != NULL) printDesc(out, root);
			cout << "Successfully print to file.\n";
			return true;
		}
		else cout << "Invalid option!\n";
		out.close();
		break;

	default:
		cout << "Invalid option!\n";
	}
	//cout << "\n\n\n";
	return true;
}

void BST::printAsc(ostream& out, BTNode* cur) {		//left to right
	if (cur == NULL) return;	//Base case
	printAsc(out, cur->left);	//Recursively print the left subtree in ascending order
	cur->item.print(out);		//Print the current BST node's item
	printAsc(out, cur->right);	//Recursively print the right subtree in ascending order
}

void BST::printDesc(ostream& out, BTNode* cur) {	//right to left
	if (cur == NULL) return;	//Base case
	printDesc(out, cur->right);	//Recursively print the right subtree in descending order
	cur->item.print(out);		//Print the current BST node's item
	printDesc(out, cur->left);	//Recursively print the left subtree in descending order
}

//Question d
bool BST::CloneSubtree(BST t1, type item) {
	BTNode* cur = t1.root;
	BST t2;

	if (t1.root == NULL) {
		cout << "Cannot clone subtree.\n";
		return false;
	}

	// Find the node with the specified item.id in t1
	while (cur != NULL) {
		if (cur->item.id == item.id) {
			break;
		}
		else if (cur->item.id > item.id) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}

	if (cur != NULL) {
		cout << "\n***************************PreOrder Print of T1*******************************\n\n";
		t1.preOrderPrint();
		cout << "\n***************************PreOrder Print of T2*******************************\n\n";
		cloneSubtree(cur, t2);			// Clone the subtree rooted at 'cur' into 't2'
		t2.preOrderPrint();
	}
	else {
		cout << "Cannot clone subtree.\n";
		return false;
	}

	return true;
}

void BST::cloneSubtree(BTNode* cur, BST& t2) {
	if (cur == NULL) {
		return;
	}

	t2.insert(cur->item); // Create a new node in t2 and copy data
	cloneSubtree(cur->left, t2);  // Clone left subtree
	cloneSubtree(cur->right, t2); // Clone right subtree
}

//Qe
bool BST::printLevelNodes() {
	Queue q;
	BTNode* cur;
	int level = 1;

	if (root == nullptr) {
		cout << "The tree is empty." << endl;
		return false; //Return false for an empty tree
	}

	//Enqueue the root node to start the traversal
	q.enqueue(root);

	while (!q.empty()) {
		int nodesAtCurrentLevel = q.size(); //Get the number of nodes at the current level
		cout << "Level " << level << " nodes: ";

		for (int i = 0; i < nodesAtCurrentLevel; ++i) {
			q.dequeue(cur);

			// Print the student id of the current node
			cout << cur->item.id << " ";

			//Enqueue the left and right children of the current node if exist
			if (cur->left != NULL)
				q.enqueue(cur->left);
			if (cur->right != NULL)
				q.enqueue(cur->right);
		}

		cout << endl;
		level++;
	}

	return true; // Return true after processing all levels
}

//Question f
bool BST::printPath() {
	int path[50]; //  creates an array to store path from the root to leaf node.

	if (root == NULL) {
		cout << "The tree is empty.\n";
		return false;
	}
	cout << "\nBelow are all the external paths for the tree:\n";
	if (root->left == NULL && root->right == NULL)// checks if root has left and right leaf nodes
	{
		cout << root->item.id << endl;
		return true;
	}

	else {
		printPath2(root, path, 0); // Call the recursive helper function to print paths starting from the root
		return true;
	}
}

void BST::printPath2(BTNode* cur, int path[], int pathnum) {

	if (cur == NULL)
		return;

	path[pathnum] = cur->item.id;  // Store the ID of the current student in the path array and increment the path counter
	pathnum++;

	if (cur->left == NULL && cur->right == NULL) {
		for (int i = 0; i < pathnum; i++) {
			cout << path[i] << " ";
		}
		cout << endl;
	}

	printPath2(cur->left, path, pathnum); // explores the leaf on the left side
	printPath2(cur->right, path, pathnum); // explores the leaf on right side
}





