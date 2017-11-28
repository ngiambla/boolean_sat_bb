#include "node.h"

void Node::init_node(Node * parent, int id, int uid, bool parent_truth_val) {
	this->parent 				=	parent;
	this->id 					=	id;
	this->uid 					= 	uid;
	this->parent_truth_val		=	parent_truth_val;
	this->left_child			=	NULL;
	this->right_child			=	NULL;
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

void Node::add_var_to_soln(unordered_map<int, bool> var) {
	soln=var;
} 

unordered_map<int, bool> Node::get_soln() {
	return soln;
}

void Node::set_lh_child(Node * left_child) {
	this->left_child=left_child;
}

void Node::set_rh_child(Node * right_child) {
	this->right_child=right_child;
}

void Node::whoami() {
	if(parent != NULL) {
		printf("\n[+] Node[%3d]~[%d]\n |--parent_id[%d]\n |--parent_truth_val: [%d]\n\n", uid, id, parent->get_id(), parent_truth_val);
	} else {	
		printf("\n[+] Node[%3d]~[%d]\n |--parent_id[NULL]\n |--parent_truth_val: [NULL]\n\n", uid, id);		
	}
}

int Node::get_id() {
	return id;
}

int Node::get_uid() {
	return uid;
}

bool Node::which_parent_side() {
	return parent_truth_val;
}

void Node::set_pos(int x, int y) {
	this->x=x;
	this->y=y;
}