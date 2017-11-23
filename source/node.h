#ifndef __NODE_H__
#define __NODE_H__

#include "bbdefs.h"
#include "expression.h"


class Node {

	private:
		Node * left_child;			//sort of like a linked list.
		Node * right_child;			//
		Node * parent;				//

		bool cost_set;				//to speed up processing.
		int cost;
		
		int id;						//	id for node.
		bool parent_truth_val;		//	

		bool was_visited_t;			// to check for freshness.
		Expression expr;

	public:

		Node(){};

		void init_node(Node * parent, int cost, int id, bool parent_truth_val);

		Node * get_lh_child();
		Node * get_rh_child();
		Node * get_parent();

		void set_lh_child(Node * left_child);
		void set_rh_child(Node * right_child);

		void set_partial_expression(Expression expr);
		Expression get_partial_expression();

		void whoami();
		int get_id();

		void visit_node();
		
		bool was_visited();
		bool get_parent_truth();

		int update_cost(unordered_map<int, bool> var);
		int get_parent_cost();
};

#endif