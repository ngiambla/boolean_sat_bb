#include "expression.h"


void Expression::init_expression(vector< vector<int> > expr) {
	expression=expr;
}



int Expression::eval_expression(unordered_map<int, bool> vals) {
	int how_many_are_true=0;

	for(vector<int> c : expression) {
		for(int var : c) {
			if(vals.count(var)>0) {
				if(vals[var]) {
					how_many_are_true++;
					break;
				}
			}
		}
	}
	return how_many_are_true;
}


vector< vector<int> > Expression::get_vector_expression() {
	return expression;
}


Expression Expression::eval_and_reduce(unordered_map<int, bool> vals) {
	vector< vector<int> > new_expr;
	Expression expr_red;

	for(vector<int> c : expression) {
		bool add_clause=true;
		for(int var : c) {
			if(vals.count(var)>0) {
				if(vals[var]) {
					add_clause=false;
					break;
				}
			}
		}
		if(add_clause) {
			new_expr.push_back(c);
		}
	}
	expr_red.init_expression(new_expr);
	return expr_red;
}