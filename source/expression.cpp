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
					init=!init;
				} else {
					res=res || vals[var]; 
				}
			} else {
				LOG(INFO) << "Found outlier: "<< var;
			}
		}
		LOG(INFO)<<"Clause: "<< res;		
	}
}