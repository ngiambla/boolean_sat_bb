#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

#include "bbdefs.h"


class Expression {

	private:
		vector< vector<int> > expression;
	public:
		Expression(){};																		//to instantiate empty object;
		void init_expression(vector< vector<int> > expr);									//to add clauses
		int eval_expression(unordered_map<int, bool> vars);									//to eval the clauses.
		vector< vector<int> > get_vector_expression();										// get vec expression;
};


#endif