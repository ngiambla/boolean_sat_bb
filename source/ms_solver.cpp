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
	return lb;
}


int MS_Solver::compute_upper_bound() {
	return ub;
}

void MS_Solver::update_lower_bound(int lb) {
	this->lb=lb;
}

void MS_Solver::update_upper_bound(int ub) {
	this->ub=ub;
}


void MS_Solver::search() {
	//1. start somewhere
		compute_upper_bound();
		compute_lower_bound();
	
		

	//2. begin expanding out.

	//3. check the nodes.

	//go to 2, until done;

	LOG(INFO) << "Maximum Number of True Clauses: " << expr.eval_expression(vars_to_vals_map)<<"/"<<num_of_clauses;
}