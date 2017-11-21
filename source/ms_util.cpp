#include <fstream>
#include <iostream>
#include <string.h>
#include "graphics.h"
#include "expression.h"

char * cmd_list="Usage ./ms_util -file [filename]";

Expression expr;

void read_in_expression(char * filename) {
	FILE *fp;
	char line[128];
	bool first_line_read	=	false;
	short delim_count		=	0;
	
	int num_of_clauses;
	int num_of_vars;
	
	vector< vector<int> > clauses;

	fp=fopen(filename, "r");
	LOG(INFO) << "Attempting to open file ["<< filename<<"]";


	if(fp) {
		LOG(INFO) << "Reading. --Generating Boolean Expression.";
		
		while(fgets(line,128,fp) != NULL) {
				char * token = strtok(line, " ");
				vector<int> current_clause;

				while(token != NULL) {
					if(!first_line_read && delim_count < 2) {
						if(delim_count==1) {
							num_of_clauses=atoi(token);
							LOG(INFO) << "Number of clauses["<<num_of_clauses<<"]";
							
							first_line_read=true;

						} else {
							num_of_vars=atoi(token);
							LOG(INFO) << "Number of variables["<<num_of_vars<<"]";
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

	LOG(INFO) << "Confirming file read was successful: ";
	for(vector<int> v : clauses ) {
		LOG(INFO) << "Clause: ";
		for(int var : v) {
			LOG(INFO) << "["<<var<<"]";
		}
		printf("\n");
	}
	LOG(INFO) << "Inserting into expression.";
	expr.init_expression(clauses);

	LOG(INFO) << "Testing...";
	unordered_map<int, bool> vals;

	bool flip=true;
	for(int i=1; i<= num_of_vars; ++i) {
		vals[i]= flip;
		flip=!flip;
		vals[-i]=!vals[i];
	}

	expr.eval_expression(vals);


}


int main(int argc, char * argv[]) {

	char file[128];

	if (argc < 3) {
		printf("%s\n", cmd_list);
		return FAIL;
	}

	if(strcmp(argv[1], "-file")!=0) {
		printf("%s\n", cmd_list);
		return FAIL;		
	}

	strcpy(file, "../inputs/");
	strcat(file, argv[2]);

	read_in_expression(file);
	

	return SUCCESS;
}
