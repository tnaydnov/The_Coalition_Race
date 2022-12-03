#pragma once

#include <vector>
#include <iostream>
#include <iterator>
#include <map>
#include "Graph.h"
#include "Agent.h"
#include "Coalition.h"

using namespace std;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    const Graph& getGraph() const;
    const vector<Agent>& getAgents() const;
    const Party& getParty(int partyId) const;
    Agent* getAgent(int agentID);
    Party& GetParty(int partyId);
    Coalition* getCoalition(int coalitionID);
    const vector<vector<int>> getPartiesByCoalitions() const;

    void step();
    bool shouldTerminate() const;

    void clone(int joinedAgentID, int joinedPartyID); //Clone an agent

private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<Coalition> mCoalitions;
    bool over61() const; //Function to determine if there is a coalition with >= 61 mandates
};