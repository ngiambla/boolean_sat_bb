#include "node.h"

void Node::init_node(Node * parent, int cost, int id, bool truth_val) {
	this->parent=parent;
	this->cost=cost;
	this->id=id;
	this->truth_val=truth_val;
}

Node * Node::get_lh_child() {
	LOG(INFO) << "Getting Left Child";
	return left_child;
}

Node * Node::get_rh_child() {
	LOG(INFO) << "Getting Right Child";
	return right_child;
}

Node * Node::get_parent() {
	return parent;
}


void Node::set_lh_child(Node * left_child) {
	this->left_child=left_child;
}

void Node::set_rh_child(Node * right_child) {
	this->right_child=right_child;
}

void Node::whoami() {
	printf("+ Node[%02x]:[%02x]\n+----isTrue: [%d]\n\n", id, cost, truth_val);
}