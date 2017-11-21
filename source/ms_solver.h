#ifndef __MS_SOLVER_H__
#define __MS_SOLVER_H__

#include "expression.h"

class MS_Solver {
	private:
		//vector< vector<int> > expression;	//hold expression
		unordered_map<int, bool> vars_to_vals_map;		// to be used for the treee structure;

		Expression expr;

		int num_of_clauses;
		int num_of_vars;

		int lb;			//lower bound
		int ub;			//upper bound


	public:
		MS_Solver(){};
		
		void init_solver(Expression expr, int num_of_clauses, int num_of_vars);

		int compute_upper_bound();
		int compute_lower_bound();

		void update_upper_bound(int lb);
		void update_lower_bound(int ub);

		void search();

};

#endif