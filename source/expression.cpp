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

int Expression::eval_expression_neg(unordered_map<int, bool> vals) {
	int how_many_are_false=0;
	for(vector<int> c : expression) {
		bool isFalse=true;
		for(int var : c) {
			if(vals.count(var)>0) {
				if(vals[var]) {
					isFalse=false;
				}
			} else {
				isFalse=false;
				break;
			}
		}
		if(isFalse) {
			++how_many_are_false;
		}
	}
	return how_many_are_false;	
}

vector< vector<int> > Expression::get_vector_expression() {
	return expression;
}