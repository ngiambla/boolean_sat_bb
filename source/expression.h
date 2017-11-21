#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

#include "bbdefs.h"


class Expression {

	private:
		bool is_true;
		vector< vector<int> > expression;
	public:
		Expression(){};												//to instantiate empty object;
		void init_expression(vector< vector<int> > expr);						//to add clauses
		void eval_expression(unordered_map<int, bool> vars);		//to eval the clauses.
};


#endif