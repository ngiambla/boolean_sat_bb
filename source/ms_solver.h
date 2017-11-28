#ifndef __MS_SOLVER_H__
#define __MS_SOLVER_H__

#include "expression.h"
#include "node.h"

class MS_Solver {
	private:

		unordered_map<int, bool> vars_used_map;

		Expression expr;

		int num_of_clauses;
		int num_of_vars;

		int lb;			//lower bound

		int select_start();

	public:
		MS_Solver(){};
		
		void init_solver(Expression expr, int num_of_clauses, int num_of_vars);
		void solve();

};

#endif