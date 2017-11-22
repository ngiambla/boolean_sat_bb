#include "node.h"

void Node::init_node(Node * parent, int cost, int id, bool parent_truth_val) {
	this->parent 			=	parent;
	this->cost 				=	cost;
	this->id 				=	id;
	this->parent_truth_val	=	parent_truth_val;
	this->was_visited_t		=	false;
	this->left_child		=	NULL;
	this->right_child		=	NULL;
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
	if(parent != NULL) {
		printf("\n[+] Node[%02x]\n |--Cost[%02x]\n |--parent_id[%02x]\n |--parent_truth_val: [%02x]\n\n", id, cost, parent_truth_val, parent->get_id());
	} else {	
		printf("\n[+] Node[%02x]\n |--Cost[%02x]\n |--parent_id[NULL]\n |--parent_truth_val: [NULL]\n\n", id, cost);		
	}
}

void Node::set_partial_expression(Expression expr) {
	unordered_map<int, bool> var;
	var[parent->get_id()]=parent_truth_val;
	this->expr = expr.eval_and_reduce(var);
}

Expression Node::get_partial_expression() {
	return expr;

}

int Node::get_id() {
	return id;
}

void Node::visit_node() {
	was_visited_t=true;
}

bool Node::was_visited() {
	return was_visited_t;
}