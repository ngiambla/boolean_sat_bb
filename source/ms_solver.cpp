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
	int index 		=	1;				//default case.

	LOG(INFO) << "~ Selecting Start ~";
	for(int i = 1 ; i<=num_of_vars; ++i) {
		unordered_map<int, bool> var_to_bool_map; 

		var_to_bool_map[i]	=	true;
		var_to_bool_map[-i]	=	false;

		if(expr.eval_expression(var_to_bool_map)<cur_lb) {
			cur_lb=expr.eval_expression(var_to_bool_map);
			index=i;
		}

		var_to_bool_map[i]	=	false;
		var_to_bool_map[-i]	=	true;

		if(expr.eval_expression(var_to_bool_map)<cur_lb) {
			cur_lb=expr.eval_expression(var_to_bool_map);
			index=i;
		}
	}

	lb=cur_lb;

	LOG(INFO) << "~ * + Found";
	LOG(INFO) << "    |--Lower Bound: ["<<lb<<"]";
	LOG(INFO) << "    |--Index: ["<<index<<"]";
	return index;
}


void MS_Solver::solve() {
	bool searching	=	true;
	int cur_lvl		=	0;
	int cnt_hold	= 	0;
	bool hanging 	= 	false;
	vector< vector<Node *> > tree;	

	unordered_map<int, int>	id_per_lvls;
	unordered_map<int, int>	lvl_to_lb;

	int head_id=select_start();

	Node * HEAD 	= 	new Node;

	HEAD->init_node(NULL, head_id, false);

	vector<Node *> root;
	root.push_back(HEAD);
	tree.push_back(root);
	vars_used_map[head_id]=true;

	while(searching) {
		vector<Node *> next_lvl;
		int next_id=0;
		int cost;

		for(const auto& key : vars_used_map) {
			if(!key.second) {
				next_id=key.first;
				break;
			}
		}

		lvl_to_lb[cur_lvl]=lb;
		id_per_lvls[cur_lvl]=next_id;

		if(cur_lvl<num_of_vars) {
			LOG(INFO) << "~~~~~~~~~~ LVL ["<<cur_lvl<<"] ~~~~~~~~~~";
			for(Node * n: tree[cur_lvl]) {

				n->whoami();

				unordered_map<int, bool> var_map=n->get_soln();
				
				var_map[-(n->get_id())]=false;
				var_map[n->get_id()]=true;

				cost = expr.eval_expression(var_map);

				LOG(INFO) << " [RH] Satisfied Clauses: "<<cost;
				
				if(cost >= lb || cur_lvl<=THRESHOLD) {
					Node * right_child = new Node;
					
					if(cur_lvl<=THRESHOLD || hanging) {
						LOG(INFO)<<"Adding -Right [SPECIAL]";
						right_child->init_node(n, next_id, true);						
						right_child->add_var_to_soln(var_map);					
						n->set_rh_child(right_child);
						next_lvl.push_back(right_child);						
						if(cost > lb) {
							lb=cost;
						}
					} else if(cost > lb && !hanging) {
						LOG(INFO)<<"Adding -Right";
						right_child->init_node(n, next_id, true);
						right_child->add_var_to_soln(var_map);					
						n->set_rh_child(right_child);
						next_lvl.push_back(right_child);
						lb=cost;
					}
				}

				var_map=n->get_soln();

				var_map[n->get_id()]=false;
				var_map[-(n->get_id())]=true;

				cost = expr.eval_expression(var_map);

				LOG(INFO) << " [LH] Satisfied Clauses: "<<cost;

				if(cost >=lb || cur_lvl<=THRESHOLD) {
					Node * left_child = new Node;

					if(cur_lvl<=THRESHOLD || hanging ) {
						LOG(INFO)<<"Adding -Left [SPECIAL]";
						left_child->init_node(n, next_id, false);
						left_child->add_var_to_soln(var_map);					
						n->set_lh_child(left_child);
						next_lvl.push_back(left_child);
						if(cost > lb) {
							lb=cost;
						}
					} else if(cost> lb && !hanging) {
						LOG(INFO)<<"Adding -Left";
						left_child->init_node(n, next_id, false);
						left_child->add_var_to_soln(var_map);					
						n->set_lh_child(left_child);
						next_lvl.push_back(left_child);
						lb=cost;

					}
				}
			} 
		}
		

		if(cnt_hold==0){
			hanging=false;	
		}	
		
		if(cur_lvl==num_of_vars) {
			LOG(INFO) << "Exiting Search..";
			searching=false;
		} else {
			if(next_lvl.size() > 0) {
				tree.push_back(next_lvl);
				if(cnt_hold>0){
					cnt_hold-=1;
				}
				++cur_lvl;
				vars_used_map[next_id]=true;
			} else {
				LOG(INFO) << "Hanging... forcing add.";

				LOG(INFO) << "~ Deleting Last (1) Tree Entries.";
				for(int i=0; i<1 ; ++i) {
					tree.erase(tree.end());
				}
				cur_lvl-=1;
				LOG(INFO) << "~ Resetting Lower Bound.";
				lb=lvl_to_lb[cur_lvl];
				vars_used_map[id_per_lvls[cur_lvl]]=false;
				hanging=true;
				cnt_hold+=1;
				LOG(INFO) << "+-- reverting.";
			}
		}
	}

	LOG(INFO) << "Tree Found";	
	int max=0;
	int index=0;
	for(int i=0; i<tree[cur_lvl].size(); ++i) {
		if(expr.eval_expression(tree[cur_lvl][i]->get_soln()) > max) {
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
}


