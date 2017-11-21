#ifndef __NODE_H__
#define __NODE_H__

#include "bbdefs.h"

class Node {

	private:
		Node * left_child;			//sort of like a linked list.
		Node * right_child;			//
		Node * parent;				//

		int cost;
		
		int id;						//
		bool truth_val;


	public:

		Node(){};

		void init_node(Node * parent, int cost, int id, bool truth_val);

		Node * get_lh_child();
		Node * get_rh_child();
		Node * get_parent();

		void set_lh_child(Node * left_child);
		void set_rh_child(Node * right_child);

		void whoami();

};

#endif