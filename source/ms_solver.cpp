#include <algorithm>
#include "ms_solver.h"

//~ Helper Function:


void MS_Solver::init_solver(Expression expr, int num_of_clauses, int num_of_vars) {
	this->num_of_clauses=num_of_clauses;	//number of clauses
	this->num_of_vars=num_of_vars;			//number of vars;

	lb=0;
	ub=0;

	this->expr=expr;

	for(int i=1; i<=num_of_vars; ++i) {
		vars_used_map[i]  = false;
	}
}


int MS_Solver::select_start() {
	int cur_lb 		= 	10000;
	int index 		=	1;				//default case;
	unordered_map<int, bool> curr_soln;

	for(int i = 1; i<=num_of_vars; ++i) {
		curr_soln[i]=true;
		curr_soln[-i]=false;
	}

	LOG(INFO) << "~ Selecting Start ~";
	for(int i = 1 ; i<=num_of_vars; ++i) {
		unordered_map<int, bool> var_to_bool_map=curr_soln;

		var_to_bool_map[i]	=	true;
		var_to_bool_map[-i]	=	false;

		if(expr.eval_expression_neg(var_to_bool_map)<cur_lb) {
			cur_lb=expr.eval_expression_neg(var_to_bool_map);
			index=i;
		}

		var_to_bool_map[i]	=	false;
		var_to_bool_map[-i]	=	true;

		if(expr.eval_expression_neg(var_to_bool_map)<cur_lb) {
			cur_lb=expr.eval_expression_neg(var_to_bool_map);
			index=i;
		}
	}

	lb=cur_lb;

	LOG(INFO) << "~ * + Found";
	LOG(INFO) << "    |--Lower Bound: ["<<lb<<"]";
	LOG(INFO) << "    |--Index: ["<<index<<"]";
	return index;
}

double compute_variance(vector< vector<int> > clauses, int num_of_vars) {
	unordered_map<int, int> var_count;
	for(vector<int> clause : clauses) {
		for(int var: clause) {
			if(var < 0) {
				int tvar=var*-1;
				if(var_count.count(tvar)>0) {
					var_count[tvar]++;
				} else {
					var_count[tvar]=1;
				}
			} else {
				if(var_count.count(var)>0) {
					var_count[var]++;
				} else {
					var_count[var]=1;
				}
			}
		}
	}
	double avg=0;
	for(const auto& key : var_count) {
		avg+=key.second;
	}
	avg=avg/num_of_vars;
	double variance=0;
	for(const auto& key : var_count) {
		variance+=pow(key.second,2);
	}	
	variance=variance/num_of_vars - avg;
	return pow(variance, 0.5);
}

void MS_Solver::solve() {
	bool searching		=	true;		// signifies if we can finish exploring the tree.
	bool high_variance	=	false;
	int cur_lvl			=	0; 			// holds the current level during exploration.
	int cur_uid 		= 	1; 			// holder for unique id per node.
	int NODES_REQ		= 	8192;		// Number of Same nodes per level.
	int THRESHOLD;

	auto start = std::chrono::system_clock::now();	// starting timer.

	double variance = compute_variance(expr.get_vector_expression(), num_of_vars);
	LOG(STATS) << "Standard Deviation: " << variance;

	if((double)variance/num_of_vars < 0.5) {
		high_variance=false;
	} else {
		high_variance=true;
	}

	THRESHOLD=max(10, 2+ THRESHOLD_T - (+num_of_vars - THRESHOLD_T));
	LOG(STATS) << " * Initializing Timer *";

	LOG(INFO) << " ~ THRESHOLD: "<< THRESHOLD;
	vector< vector<Node *> > tree;	

	unordered_map<int, int>	id_per_lvls;
	unordered_map<int, int> uid_per_lvls;
	unordered_map<int, int> best_per_lvl;
	unordered_map<int, bool> skip_id;

	for(int i=1; i<num_of_vars; ++i) {
		skip_id[i]=false;
	}

	int head_id=select_start();


	Node * HEAD 	= 	new Node;

	unordered_map<int, bool> curr_soln;

	for(int i = 1; i<=num_of_vars; ++i) {
		curr_soln[i]=true;
		curr_soln[-i]=false;
	}

	HEAD->init_node(NULL, head_id, cur_uid++,false);
	if(!high_variance){
		HEAD->add_var_to_soln(curr_soln);
	}
	lb=expr.eval_expression_neg(curr_soln);


	vector<Node *> root;
	root.push_back(HEAD);
	tree.push_back(root);
	vars_used_map[head_id]=true;

	while(searching) {
		vector<Node *> next_lvl;
		int next_id=0;
		int cost;

		for(const auto& key : vars_used_map) {
			if(!key.second && !skip_id[key.first]) {
				next_id=key.first;
				break;
			}
		}

		id_per_lvls[cur_lvl]=next_id;
		uid_per_lvls[cur_lvl]=cur_uid;

		if(cur_lvl<num_of_vars) {
			if(cur_lvl<=THRESHOLD) {
				LOG(INFO) << " ~ - Using THRESHOLD @ LVL-"<<cur_lvl;
			} else {
				LOG(INFO) << " ~ * Burning Tree    @ LVL-"<<cur_lvl;
			}

			for(Node * n: tree[cur_lvl]) {
				unordered_map<int, bool> var_map=n->get_soln();
				var_map[n->get_id()]=true;
				var_map[-n->get_id()]=false;
				cost = expr.eval_expression_neg(var_map);
				if(cost < lb) {
					lb=cost;
					best_per_lvl[cur_lvl]=cost;
				}
					
		

				var_map=n->get_soln();
				var_map[-n->get_id()]=true;
				var_map[n->get_id()]=false;
				cost = expr.eval_expression_neg(var_map);
				if(cost < lb) {
					lb=cost;
					best_per_lvl[cur_lvl]=cost;
				}

			}

			for(Node * n: tree[cur_lvl]) {
				unordered_map<int, bool> var_map=n->get_soln();
				
				var_map[-(n->get_id())]=false;
				var_map[n->get_id()]=true;
				cost = expr.eval_expression_neg(var_map);

				Node * right_child = new Node;

				if(cur_lvl<=THRESHOLD || (cost <= lb && (int) next_lvl.size() <=NODES_REQ)) {				
					right_child->init_node(n, next_id, cur_uid++, true);
					right_child->add_var_to_soln(var_map);					
					n->set_rh_child(right_child);
					next_lvl.push_back(right_child);
				}

				var_map=n->get_soln();

				var_map[n->get_id()]=false;
				var_map[-(n->get_id())]=true;
				cost = expr.eval_expression_neg(var_map);
				
				Node * left_child = new Node;

				if( cur_lvl<=THRESHOLD || (cost <= lb && (int) next_lvl.size() <=NODES_REQ)) {
					left_child->init_node(n, next_id, cur_uid++, false);
					left_child->add_var_to_soln(var_map);					
					n->set_lh_child(left_child);
					next_lvl.push_back(left_child);
				}
			}
			if(high_variance && cur_lvl>THRESHOLD) {
				LOG(INFO) << "..-* [done]";
				for(Node * n: tree[cur_lvl]) {
					unordered_map<int, bool> var_map=n->get_soln();
					
					var_map[-(n->get_id())]=false;
					var_map[n->get_id()]=true;
					cost = expr.eval_expression_neg(var_map);

					Node * right_child = new Node;

					if(cur_lvl<=THRESHOLD || ((cost+1 >= lb ) && (int) next_lvl.size() <=NODES_REQ)) {				
						right_child->init_node(n, next_id, cur_uid++, true);
						right_child->add_var_to_soln(var_map);					
						n->set_rh_child(right_child);
						next_lvl.push_back(right_child);
					}

					var_map=n->get_soln();

					var_map[n->get_id()]=false;
					var_map[-(n->get_id())]=true;
					cost = expr.eval_expression_neg(var_map);
					
					Node * left_child = new Node;

					if( cur_lvl<=THRESHOLD || ((cost+1 >= lb  ) && (int) next_lvl.size() <=NODES_REQ)) {
						left_child->init_node(n, next_id, cur_uid++, false);
						left_child->add_var_to_soln(var_map);					
						n->set_lh_child(left_child);
						next_lvl.push_back(left_child);
					}
				}				
			}
		}
		
		if(cur_lvl==num_of_vars) {
			LOG(INFO) << "Exiting Search..";
			searching=false;
		} else {
			//if(next_lvl.size() > 0 ) {
				tree.push_back(next_lvl);
				if(NODES_REQ>=128 && cur_lvl>THRESHOLD){
					NODES_REQ/=2;
				}
				++cur_lvl;
				vars_used_map[next_id]=true;
				for(const auto& key : skip_id) {
					skip_id[key.first]=false;
				}
			//} else {
			//	skip_id[next_id]=true;
			//}
		}
	}

	LOG(INFO) << "Tree Found";
	auto end = std::chrono::system_clock::now();	
	
	int max=0;
	int index=0;
	for(int i=0; i< (int)tree[cur_lvl].size(); ++i) {
		if(expr.eval_expression(tree[cur_lvl][i]->get_soln()) > max && (int) tree[cur_lvl][i]->get_soln().size() == num_of_vars) {
			max=expr.eval_expression(tree[cur_lvl][i]->get_soln());
			index=i;
		}
	}
	LOG(INFO) << "Satisfied Clauses: "<<expr.eval_expression(tree[cur_lvl][index]->get_soln())<<"/"<<num_of_clauses;
	for(const auto& key : tree[cur_lvl][index]->get_soln()) {
		if(key.first > 0){
			if(key.second) {
				printf("Var [%d] = TRUE\n", key.first);
			} else {
				printf("Var [%d] = FALSE\n", key.first);
			}
		}
	}

	int nodes_visited=0;
	for(int i = 0; i < (int)tree.size(); ++i) {
		for(int j = 0; j < (int)tree[i].size(); ++j) {
			++nodes_visited;
			delete tree[i][j];
		}
	}

	LOG(STATS) << "Visited: "<<nodes_visited<< "/"<<pow(2, num_of_vars);
	chrono::duration<double> elapsed_seconds = end-start;
	LOG(STATS) << "Time Elapsed: " << elapsed_seconds.count() << " seconds.";
}


