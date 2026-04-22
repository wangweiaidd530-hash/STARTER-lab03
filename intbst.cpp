// intbst.cpp
#include "intbst.h"
// Implements class IntBST
// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
    root = nullptr;
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n == nullptr) {
    	return;
    }
    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (root == nullptr) {
        root = new Node(value);
        return true;
    }
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info) {
        return false;
    }
    if (value < n->info) {
        if (n->left == nullptr) {
            n->left = new Node(value);
            n->left->parent = n;
            return true;
        } else {
            return insert(value, n->left);
        }
    } else {
        if (n->right == nullptr) {
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        } else {
            return insert(value, n->right);
        }
    }
}
// print tree info pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n == nullptr) {
	return;
    }
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree info in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if (n == nullptr) {
        return;
    }
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);

}

// prints tree info post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (n == nullptr) {
    	return;
    }
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (n == nullptr) {
        return 0;
    }
    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (n == nullptr) {
        return 0;
    }
    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (n == nullptr) {
        return nullptr;
    }
    if (n->info == value) {
        return n;
    }
    if (n->info < value) {
        return getNodeFor(value, n->right);
    }
    else {
        return getNodeFor(value, n->left);
    }
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    IntBST::Node* resultNode = getNodeFor(value, root);
    if (resultNode == nullptr) {
        return false;
    }
    else {
        return true;
    }
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* resultNode = getNodeFor(value, root);
    if (resultNode == nullptr) {
        return nullptr;
    }
    if (resultNode->left != nullptr) {
        Node* smallNode = resultNode->left;
	while (smallNode->right != nullptr) {
	    smallNode = smallNode->right;
	}
	return smallNode;
    }
    else {
        Node* sN = resultNode;
        while (sN->parent != nullptr && sN == sN->parent->left) {
            sN = sN->parent;
        }
        return sN->parent;
    }
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* resultNode = getPredecessorNode(value);
    if (resultNode == nullptr) {
        return 0;
    }
    else {
        return resultNode->info;
    }
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* resultNode = getNodeFor(value, root);
    if (resultNode == nullptr) {
        return nullptr;
    }
    if (resultNode->right != nullptr) {
        Node* smallNode = resultNode->right;
        while (smallNode->left != nullptr) {
            smallNode = smallNode->left;
        }
        return smallNode;
    }
    else {
        Node* sN = resultNode;
        while (sN->parent != nullptr && sN == sN->parent->right) {
            sN = sN->parent;
        }
        return sN->parent;
    }
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* resultNode = getSuccessorNode(value);
    if (resultNode == nullptr) {
        return 0;
    }
    else {
        return resultNode->info;
    }
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node* node = getNodeFor(value, root);
    if (node == nullptr) return false;
    if (!node->left && !node->right) {
        if (node->parent == nullptr) {
            root = nullptr;
        } else if (node->parent->left == node) {
            node->parent->left = nullptr;
        } else {
            node->parent->right = nullptr;
        }
        delete node;
    }
    else if (!node->left || !node->right) {
        Node* child = (node->left) ? node->left : node->right;

        if (node->parent == nullptr) {
            root = child;
        } else if (node->parent->left == node) {
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }

        child->parent = node->parent;
        delete node;
    }
    else {
        Node* succ = getSuccessorNode(value);
        node->info = succ->info;
        remove(succ->info);
    }
    return true;
}
