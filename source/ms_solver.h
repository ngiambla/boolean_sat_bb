#ifndef __MS_SOLVER_H__
#define __MS_SOLVER_H__

class MS_Solver {
	private:
		vector< vector<int> > expression;
		// to fill with a tree structure?

	public:
		MS_Solver(){};
		
		void init_solver(vector< vector<int> > expression);

		int compute_upper_bound();
		int compute_lower_bound();

		void update_upper_bound();
		void update_lower_bound();

		void search();

};
#endif