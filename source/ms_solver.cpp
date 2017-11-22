#include "ms_solver.h"


void MS_Solver::init_solver(Expression expr, int num_of_clauses, int num_of_vars) {
	this->num_of_clauses=num_of_clauses;	//number of clauses
	this->num_of_vars=num_of_vars;			//number of vars;

	lb=0;
	ub=0;

	this->expr=expr;

	for(int i=1; i<=num_of_vars; ++i) {
		vars_used_map[i]  = false;
		vars_used_map[-i] = false;
	}
}

int MS_Solver::select_start() {
	int cur_lb = 0;
	int index=1;			//default case.

	LOG(INFO) << "~ Selecting Start ~";
	for(int i = 1 ; i<=num_of_vars; ++i) {
		unordered_map<int, bool> var_to_bool_map; 
		var_to_bool_map[i]=true;
		if(expr.eval_expression(var_to_bool_map)>cur_lb) {
			cur_lb=expr.eval_expression(var_to_bool_map);
			index=i;
		}
		var_to_bool_map[i]=false;
		if(expr.eval_expression(var_to_bool_map)>cur_lb) {
			cur_lb=expr.eval_expression(var_to_bool_map);
			index=i;
		}
	}

	for(int i = -num_of_vars ; i>=-1; ++i) {
		unordered_map<int, bool> var_to_bool_map; 
		var_to_bool_map[i]=true;
		if(expr.eval_expression(var_to_bool_map)>cur_lb) {
			cur_lb=expr.eval_expression(var_to_bool_map);
			index=i;
		}
		var_to_bool_map[i]=false;
		if(expr.eval_expression(var_to_bool_map)>cur_lb) {
			cur_lb=expr.eval_expression(var_to_bool_map);
			index=i;
		}
	}

	lb=cur_lb;
	LOG(INFO) << "~ * [+] Found * ~";
	LOG(INFO) << "    [-] >> Lower Bound: ["<<lb<<"]";
	LOG(INFO) << "    [-] >> Index: ["<<index<<"]";

	return index;
}


int MS_Solver::compute_lower_bound() {
	int cur_lb = 0;

	for(int i = 1 ; i<=num_of_vars; ++i) {
		unordered_map<int, bool> var_to_bool_map; 
		var_to_bool_map[i]=true;
		if(expr.eval_expression(var_to_bool_map)>cur_lb) {
			cur_lb=expr.eval_expression(var_to_bool_map);
		}
		var_to_bool_map[i]=false;
		if(expr.eval_expression(var_to_bool_map)>cur_lb) {
			cur_lb=expr.eval_expression(var_to_bool_map);
		}
	}

	for(int i = -num_of_vars ; i>=-1; ++i) {
		unordered_map<int, bool> var_to_bool_map; 
		var_to_bool_map[i]=true;
		if(expr.eval_expression(var_to_bool_map)>cur_lb) {
			cur_lb=expr.eval_expression(var_to_bool_map);
		}
		var_to_bool_map[i]=false;
		if(expr.eval_expression(var_to_bool_map)>cur_lb) {
			cur_lb=expr.eval_expression(var_to_bool_map);
		}
	}

	lb=cur_lb;

	return lb;
}


int MS_Solver::compute_upper_bound() {
	LOG(DEBUG) << " [compute_upper_bound] not yet implemented.";
	return ub;
}

void MS_Solver::update_lower_bound(int lb) {
	this->lb=lb;
}

void MS_Solver::update_upper_bound(int ub) {
	this->ub=ub;
}


void MS_Solver::construct_and_check(Node * node) {
	if(node != NULL) {
		LOG(INFO) << "Checking Node.";
		node->whoami();		
	} else {
		LOG(ERROR) << "Fatal Error. Exiting.\n";
	}
}

void MS_Solver::solve() {

	vector< vector<Node *> > tree;

	bool searching 	=	true;
	int cur_lvl 	=	0;

	//1. start somewhere
	LOG(INFO) << "Starting to Solve.";

	unordered_map<int, int> var_to_level;
	int id=select_start();

	var_to_level[id]=cur_lvl;


	Node * HEAD  = new Node;

	HEAD->init_node(NULL, 0, id, false);
	HEAD->whoami();

	//2. begin expanding out.
	vector<Node *> root;	//define the root of the tree
	root.push_back(HEAD);	//add HEAD to the root.
	tree.push_back(root);	//Add root to the tree.

	while(searching) {
		vector<Node *> new_lvl;
		int new_id;

		for(Node * n: tree[cur_lvl]) {
			for(const auto& key : vars_used_map) {
				if(!key.second) {
					new_id=key.first;
				}
			}
			Node * left_child;
			unordered_map<int, bool> var_map;
			var_map[]
			left_child.init_node(n, n->get_partial_expression().eval_expression(), key.first, false);

			Node * right_child;
			right_child.init_node(n, n->get_partial_expression().eval_expression(), key.first, false);
			break;
		}
		vars_used_map[]
		++cur_lvl;
	}

		// while(searching) {
		// 	CUR_P=CUR;
		// 	for(const auto& key : vars_used_map) {
		// 		if(!key.second) {
		// 			Node * left_child = new Node;
		// 			left_child->init_node(CUR_P, 1, key.first, false);
		// 			left_child->whoami();

		// 			Node * right_child = new Node;
		// 			right_child->init_node(CUR_P, 1, key.first, true);
		// 			right_child->whoami();

		// 			CUR_P->set_rh_child(right_child);
		// 			CUR_P->set_lh_child(left_child);
		// 			vars_used_map[key.first]=true;
		// 			break;
		// 		}
		// 	}
		// 	break;
		// }

	//3. check the nodes.

	//go to 2, until done;
	LOG(INFO) << "Maximum Number of True Clauses: " << expr.eval_expression(vars_to_vals_map)<<"/"<<num_of_clauses;
}