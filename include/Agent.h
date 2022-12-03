#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "SelectionPolicy.h"

using namespace std;

class Simulation;
class Party;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy* selectionPolicy);

    //Getters & Setters:
    int getId() const;
    void setId(int agentId);
    int getPartyId() const;
    void setPartyId(int partyId);
    int getCoalitionId();
    void setCoalition(int coalitionId);

    void step(Simulation& s);

    //RULE OF 5:
    virtual ~Agent(); //Destructor
    Agent(const Agent& other); //Copy Constructor
    Agent& operator=(const Agent& other); //Copy Assignment
    Agent(Agent&& other); //Move Constructor
    Agent& operator=(Agent&& other); //Move Assignment

private:
    int mAgentId; //Agent's ID
    int mPartyId; //Party's ID
    SelectionPolicy* mSelectionPolicy; //Agent's Selection Policy
    int mCoalitionId; //Coalition's ID
    vector<int> offeredTo; //Parties' IDs the agent selected already
};
