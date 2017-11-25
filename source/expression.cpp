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