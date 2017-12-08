#include <fstream>
#include <iostream>
#include <string.h>
#include "graphics.h"
#include "ms_solver.h"

char cmd_list[]="Usage ./ms_util -file [filename] -opt [y|n]";

Expression expr;
MS_Solver mss;
vector< vector<Node *> > tree_plot;

// function references for graphics.
void drawscreen(void);
void act_on_button_press (float x, float y);
void act_on_mouse_move (float x, float y);
void act_on_key_press (char c);

void read_in_expression(char * filename) {
	FILE *fp;
	char line[128];
	bool first_line_read	=	false;
	short delim_count		=	0;
	
	int num_of_clauses=0;
	int num_of_vars=0;
	
	vector< vector<int> > clauses;

	fp=fopen(filename, "r");
	LOG(INFO) << "Attempting to open file ["<< filename<<"]";


	if(fp) {
		LOG(INFO) << "Reading file.";
		
		while(fgets(line,128,fp) != NULL) {
				char * token = strtok(line, " ");
				vector<int> current_clause;

				while(token != NULL) {
					if(!first_line_read && delim_count < 2) {
						if(delim_count==1) {
							num_of_clauses=atoi(token);
							LOG(INFO) << "Number of clauses:     --> ["<<num_of_clauses<<"]";
							
							first_line_read=true;

						} else {
							num_of_vars=atoi(token);
							LOG(INFO) << "Number of variables:   --> ["<<num_of_vars<<"]";
						}
					} else {
						if(atoi(token)==0) {
							clauses.push_back(current_clause);
						} else {
							current_clause.push_back(atoi(token));
						}
					}
					delim_count++;
					token = strtok(NULL, " ");
				}
		}

		fclose(fp);
	} else {
		LOG(ERROR) << "File does not exist.";
		exit(-1);
	}

	LOG(INFO) << "Forming into expression.";

	expr.init_expression(clauses);
	
	LOG(INFO) << "Initializing Solver.\n";

	mss.init_solver(expr, num_of_clauses, num_of_vars);

}


int main(int argc, char * argv[]) {

	char file[128];
	bool opt_on=false;

	if (argc < 5) {
		printf("%s\n", cmd_list);
		return FAIL;
	}

	if(strcmp(argv[1], "-file") != 0) {
		printf("%s\n", cmd_list);
		return FAIL;		
	}

	if(strcmp(argv[3], "-opt") != 0) {
		printf("%s\n", cmd_list);
		return FAIL;
	}

	if(strcmp(argv[4], "y") == 0 || strcmp(argv[4], "Y") == 0 || strcmp(argv[4], "n") == 0 || strcmp(argv[4], "N") == 0) {
		if(strcmp(argv[4], "y") == 0 || strcmp(argv[4], "Y") == 0){
			opt_on=true;
		}
	} else {
		printf("%s\n", cmd_list);
		return FAIL;
	}

	strcpy(file, "../inputs/");
	strcat(file, argv[2]);

	read_in_expression(file);
	mss.set_optimal(opt_on);
	mss.solve();

	tree_plot = mss.grab_soln_tree();

	init_graphics("MS_Solver", WHITE);

	init_world(0,0, 2000, 4000);
	
	destroy_button("Proceed");
	destroy_button("PostScript");

	clearscreen();

	update_message("--- Solution Tree ---");
	drawscreen();
  	event_loop(act_on_button_press, NULL, NULL, drawscreen); 

	mss.cut_tree();

	return SUCCESS;
}

void drawscreen(void) {

	char buf[128];

	set_draw_mode (DRAW_NORMAL);
	clearscreen();
	setlinewidth (2);
	setlinestyle (SOLID);

	setcolor(DARKGREY);
	for(int i=1; i< (int)tree_plot.size(); ++i) {
		for(int j=0; j< (int)tree_plot[i].size(); ++j) {
			for(Node *n : tree_plot[i-1]){
				if(n->get_uid()==tree_plot[i][j]->get_parent()->get_uid()) {
					drawline(tree_plot[i][j]->get_x(), tree_plot[i][j]->get_y(), n->get_x(), n->get_y());
				}
			}
		}
	}

	for(int i=0; i< (int)tree_plot.size(); ++i) {
		bool is_set=false;
		for(int j=0; j< (int)tree_plot[i].size(); ++j) {
			if(tree_plot[i][j]->get_id() != 0) {
				if(!is_set) {
					setcolor(BLACK);
					sprintf(buf, "[%d]", tree_plot[i][j]->get_id());
					drawtext(tree_plot[i][j]->get_x()+100, tree_plot[i][j]->get_y(), buf, 100);
					is_set=true;
				}
				setcolor(BLUE);
				drawarc(tree_plot[i][j]->get_x(), tree_plot[i][j]->get_y(), 6, 0, 360);	
				setcolor(MAGENTA);
				fillarc(tree_plot[i][j]->get_x(), tree_plot[i][j]->get_y(), 6.3, 0, 360);
			} else {
				setcolor(CYAN);
				fillrect(tree_plot[i][j]->get_x()-4, tree_plot[i][j]->get_y()-4, tree_plot[i][j]->get_x()+4, tree_plot[i][j]->get_y()+4);
			}

		}
	}

	Node * CUR=tree_plot[mss.get_soln_lvl()][mss.get_soln_idx()];
	while(CUR != NULL) {
			setcolor(RED);
			if(CUR->get_parent() != NULL) {
				drawline(CUR->get_x(), CUR->get_y(), CUR->get_parent()->get_x(), CUR->get_parent()->get_y());
			}
			if(CUR->get_id() != 0){
				setcolor(GREEN);
				fillarc(CUR->get_x(), CUR->get_y(), 7, 0, 360);
			} else {
				setcolor(CYAN);
				fillrect(CUR->get_x()-4, CUR->get_y()-4, CUR->get_x()+4, CUR->get_y()+4);
			}
			CUR=CUR->get_parent();	
	}


}

void act_on_button_press (float x, float y) {


}
