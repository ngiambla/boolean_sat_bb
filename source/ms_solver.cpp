#include "ms_solver.h"


void MS_Solver::init_solver(Expression expr, int num_of_clauses, int num_of_vars) {
	this->num_of_clauses=num_of_clauses;	//number of clauses
	this->num_of_vars=num_of_vars;			//number of vars;

	lb=0;
	ub=0;

	this->expr=expr;
	
	for(int i=1; i<=num_of_vars; ++i) {
		vars_to_vals_map[i]=false;
		vars_to_vals_map[-i]=!vars_to_vals_map[i];
	}

	LOG(INFO) << "We are here";
}


int MS_Solver::compute_lower_bound() {
	unordered_map<int, int> var_to_count_map;	//_t == temporary

	for(vector<int> clause : expr.get_vector_expression()){
		for(int var : clause) {
			if(var_to_count_map.count(var) > 0) {
				var_to_count_map[var]++;
			} else {
				var_to_count_map[var]=1;				
			}
		}
	}
	for(const auto& key : var_to_count_map) {
		LOG(INFO) << " Var [" << key.first << "] occurs: ["<< key.second <<"]";
	}
	return lb;
}


int MS_Solver::compute_upper_bound() {
	LOG(DEBUG) << " [computer_upper_bound] not yet implemented.";
	return ub;
}

void MS_Solver::update_lower_bound(int lb) {
	this->lb=lb;
}

void MS_Solver::update_upper_bound(int ub) {
	this->ub=ub;
}


void MS_Solver::search() {
	bool searching=true;

	//1. start somewhere
		compute_upper_bound();
		compute_lower_bound();
	
		Node * CUR = new Node;
		CUR->init_node(NULL, 0, 0, false);

		CUR->whoami();

	//2. begin expanding out.

		while(searching) {
			Node * new_left = new Node;
			Node * new_right = new Node;

			new_left->init_node(CUR, 0, 2, false);
			new_right->init_node(CUR, 1, 3, false);

			CUR->set_lh_child(new_left);
			CUR->set_rh_child(new_right);

			CUR=CUR->get_lh_child();
			CUR->whoami();

			CUR=CUR->get_parent();
			CUR->whoami();
			
			CUR=CUR->get_rh_child();
			CUR->whoami();
			break;
		}

	//3. check the nodes.

	//go to 2, until done;

	LOG(INFO) << "Maximum Number of True Clauses: " << expr.eval_expression(vars_to_vals_map)<<"/"<<num_of_clauses;

	LOG(INFO) << "?!";
}