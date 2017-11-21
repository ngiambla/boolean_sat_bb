#include "expression.h"


void Expression::init_expression(vector< vector<int> > expr) {
	expression=expr;
}



int Expression::eval_expression(unordered_map<int, bool> vals) {
	int how_many_are_true=0;

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
				LOG(ERROR) << "Found outlier: "<< var;
				exit(-1);
			}
		}
		LOG(INFO)<<"Clause: "<< res;
		if(res) {
			how_many_are_true++;
		}
	}
	return how_many_are_true;
}