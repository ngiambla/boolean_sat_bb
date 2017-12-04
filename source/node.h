#ifndef __NODE_H__
#define __NODE_H__

#include "bbdefs.h"
#include "expression.h"


class Node {

	private:
		Node * left_child;
		Node * right_child;
		Node * parent;
		
		int id;						// variable id for node.
		int uid; 					// unique id for node.
		float x; 						// x coord
		float y;						// y coord
		bool parent_truth_val;		// parent val;

		unordered_map<int, bool> soln;

	public:

		Node(){};

		void init_node(Node * parent, int id, int uid, bool parent_truth_val); 	// sets node characteristics.

		void set_pos(float x, float y); 										   	// sets node pos (for graphic disp)
		float get_x();
		float get_y();

		Node * get_lh_child(); 
		Node * get_rh_child();
		Node * get_parent();

		void set_lh_child(Node * left_child);
		void set_rh_child(Node * right_child);

		unordered_map<int, bool> get_soln();
		void add_var_to_soln(unordered_map<int, bool> var);

		void whoami();
		int get_id();
		int get_uid();

		bool which_parent_side();
};

#endif