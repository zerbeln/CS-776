//
//  tree.hpp
//  CS 776 HW 0 Part 0
//
//  Created by Nicholas Zerbel on 8/30/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#ifndef tree_hpp
#define tree_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class node{
public:
    int action; //Numerical integer representing possible action
    int n_number; //Node Number
    int p_number; //Parent Node Number
    
};

class level{
    friend class node;
public:
    vector <node> level_vec;
    
};

class tree{
    friend class level;
public:
    vector <level> tree_vec; //The tree is represented as a vector of levels, each level is a vector of nodes
    
    void create_level();
    void create_node(int lev, int n_nodes, int a, int n_n, int p_n);
    void print_tree();
};

#endif /* tree_hpp */
