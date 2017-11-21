#include "expression.h"


void Expression::init_expression(vector< vector<int> > expr) {
	expression=expr;
}



void Expression::eval_expression(unordered_map<int, bool> vals) {
	for(vector<int> c : expression) {
		bool init=true;
		bool res;
		for(int var : c) {
			if(vals.count(var)>0) {
				if(init) {
					res=vals[var];
				} else {
					res=res || vals[var]; 
				}
			}
		}
		LOG(INFO)<<"Clause: "<< res;		
	}
}