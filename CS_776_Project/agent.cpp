//
//  agent.cpp
//  MAMCTS
//
//  Created by Nick Zerbel on 5/25/17.
//  Copyright © 2017 Nick Zerbel. All rights reserved.
//

#include "agent.hpp"

//AGENT FUNCTIONS-----------------------------------------------------------------------------------------------
void multi_agent::create_agent_vec(int n, int xd, int yd){
    double x, y;
    agent a;
    xdim = xd; ydim = yd;
    n_agents = n;
    
    for(int i = 0; i < n_agents; i++){
        agent_vec.push_back(a);
        agent_vec.at(i).agent_x = -1;
        agent_vec.at(i).agent_y = -1;
    }
    
    
    //Create Coordinates
    for(int i = 0; i < n_agents; i++){
        x = (double)(rand() % xdim);
        y = (double)(rand() % ydim);
        check_agent_coordinates(i, x, y);
        while(unique_pos == false){
            x = (double)(rand() % xdim);
            y = (double)(rand() % ydim);
            check_agent_coordinates(i, x, y);
        }
        agent_vec.at(i).agent_x = x;
        agent_vec.at(i).agent_y = y;
    }
    
    //Check to make sure no agents are stacked
    for(int i = 0; i < n_agents; i++){
        x = agent_vec.at(i).agent_x;
        y = agent_vec.at(i).agent_y;
        check_agent_coordinates(i, x ,y);
        assert(unique_pos == true);
    }
}

void multi_agent::assign_agent_coordinates(int n){
    n_agents = n; double x, y;
    agent_vec = agent_start_pos;
    //Check to make sure no agents are stacked
    for(int i = 0; i < n_agents; i++){
        x = agent_vec.at(i).agent_x;
        y = agent_vec.at(i).agent_y;
        check_agent_coordinates(i, x ,y);
        assert(unique_pos == true);
    }
}

void multi_agent::agent_move(int n, int act){ //Agent Number, Action
    double ax, ay;
    ax = agent_vec.at(n).agent_x;
    ay = agent_vec.at(n).agent_y;
    assert(act <= 4);
    assert(act >= 0);
    
    if(act == 0){
        ax--;
    }
    if(act == 1){
        ay++;
    }
    if(act == 2){
        ay--;
    }
    if(act == 3){
        ax++;
    }
    if(act == 4){
        ax = agent_vec.at(n).agent_x;
        ay = agent_vec.at(n).agent_y;
    }
    agent_vec.at(n).agent_x = ax;
    agent_vec.at(n).agent_y = ay;
}

void multi_agent::check_agent_coordinates(int n, double x, double y){
    unique_pos = true;
    for(int i = 0; i < n_agents; i++){ //Check agent coordinates against other agent coordinates
        if(i != n){
            if(x == agent_vec.at(i).agent_x && y == agent_vec.at(i).agent_y){
                unique_pos = false;
                break;
            }
        }
    }
}

void multi_agent::check_agent_status(int an){ //Checks if agent is at  goal
    double x, y;
    x = agent_vec.at(an).agent_x;
    y = agent_vec.at(an).agent_y;
    
    agent_in_play = true;
    for(int i = 0; i < n_agents; i++){
        if(x == goal_vec.at(i).goal_x && y == goal_vec.at(i).goal_y){ //If agent is at a goal, it is no longer in play
            agent_in_play = false;
            break;
        }
    }
}

//GOAL FUNCTIONS----------------------------------------------------------------------------------------------------
void multi_agent::create_goal_vec(){
    goal g;
    double x, y;
    
    for(int i = 0; i < n_agents; i++){
        goal_vec.push_back(g);
        goal_vec.at(i).goal_x = -1;
        goal_vec.at(i).goal_y = -1;
    }
    
    //Create Coordinates
    for(int i = 0; i < n_agents; i++){
        x = (double)(rand() % xdim);
        y = (double)(rand() % ydim);
        check_goal_coordinates(i, x, y);
        while(unique_pos == false){
            x = (double)(rand() % xdim);
            y = (double)(rand() % ydim);
            check_goal_coordinates(i, x ,y);
        }
        goal_vec.at(i).goal_x = x;
        goal_vec.at(i).goal_y = y;
    }
    
    //Check to make sure no goals are stacked
    for(int i = 0; i < n_agents; i++){
        x = goal_vec.at(i).goal_x;
        y = goal_vec.at(i).goal_y;
        check_goal_coordinates(i, x, y);
        assert(unique_pos == true);
    }
}

void multi_agent::assign_goal_coordinates(){
    double x, y;
    goal_vec = goal_start_pos;
    //Check to make sure no goals are stacked
    for(int i = 0; i < n_agents; i++){
        x = goal_vec.at(i).goal_x;
        y = goal_vec.at(i).goal_y;
        check_goal_coordinates(i, x, y);
        assert(unique_pos == true);
    }
}

void multi_agent::check_goal_coordinates(int n, double xc, double yc){ //Goal number, goal_x, goal_y
    unique_pos = true;
    for(int i = 0; i < n_agents; i++){ //Check goal coordinates against other goal coordinates and agent coordinates
        if(i != n){
            if(xc == goal_vec.at(i).goal_x && yc == goal_vec.at(i).goal_y){
                unique_pos = false;
                break;
            }
        }
        if(xc == agent_vec.at(i).agent_x && yc == agent_vec.at(i).agent_y){ //Goal cannot start out at same position as agent
            unique_pos = false;
            break;
        }
    }
}

void multi_agent::check_goal_status(int gn){
    double gx, gy;
    gx = goal_vec.at(gn).goal_x;
    gy = goal_vec.at(gn).goal_y;
    goal_in_play = true;
    for(int i = 0; i < n_agents; i++){
        if(gx == agent_vec.at(i).agent_x && gy == agent_vec.at(i).agent_y){
            goal_in_play = false;
        }
    }
}

void multi_agent::create_config_list(int max_a, int xd, int yd, int nconfigs){
    for(int j = 0; j < nconfigs; j++){ //Maximum number of configurations
        create_agent_vec(max_a, xd, yd);
        create_goal_vec();
        for(int k = 0; k < max_a; k++){ //Maximum number of agents
            agent_list.push_back(agent_vec.at(k));
            goal_list.push_back(goal_vec.at(k));
        }
        agent_vec.clear();
        goal_vec.clear();
    }
    agent a; goal g;
    for(int i = 0; i < max_a; i++){ //Create start pos vectors
        agent_start_pos.push_back(a);
        goal_start_pos.push_back(g);
    }
}
