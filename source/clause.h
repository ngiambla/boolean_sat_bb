#ifndef __CLAUSE_H__
#define __CLAUSE_H__

#include "bbdefs.h"

class Clause {
	private:
		unordered_map<int, bool> clause;

	public:
		Clause();

		add_to_clause();
};

#endif