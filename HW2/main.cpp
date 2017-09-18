//
//  main.cpp
//  CS-776-HW-2
//
//  Created by Nicholas Zerbel on 9/17/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "hillclimber.hpp"

double eval(int *v);

int main() {
    hillclimber h;
    srand( time(NULL) );
    int iterations = 1000000;
	int stat_runs = 1;
    
    ofstream myfile;
    myfile.open("best-fitness.txt"); //Records best fitness found

	ofstream sol;
	sol.open("array.txt"); //Records initial array and best array at the end
    
	for(int s = 0; s < stat_runs; s++){
    	h.create_vec();

    	h.best_fit = eval(h.best_vec); //assign initial fitness
		myfile << h.best_fit << "\t";
    	for(int i = 0; i < iterations; i++){
			if(i % 100000 == 0){
				cout << "iteration: " << i << endl;
			}
    	    h.mutate();
    	    h.fitness = eval(h.vec); //Fitness for mutating vector
			h.r_fitness = eval(h.r_vec); //Fitness for completely random vector
    	    h.evaluate();
    	    myfile << h.best_fit << "\t"; //Record best fitness
    	}
		myfile << endl;
    
    	myfile.close();
    
		sol << "Final Array:" << "\n";
    	for(int i = 0; i < 150; i++){
    	    sol << h.best_vec[i] << "\t";
    	}
		sol << endl;
    	sol.close();
    
		cout << "Best Fitness: " << h.best_fit << endl;
	}

    return 0;
}
