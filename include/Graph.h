#pragma once
#include <vector>
#include "Party.h"
#include <string>

using std::vector;

class Simulation;

class Graph
{
public:
    Graph(vector<Party> vertices, vector<vector<int>> edges);
    int getMandates(int partyId) const;
    int getEdgeWeight(int v1, int v2) const;
    int getNumVertices() const;
    const Party& getParty(int partyId) const;
    Party& GetParty(int partyId);
    const vector<Party>& getVertices() const;
    void setPartiesNeighbors(); //Set every party's weightedNeighbors field

    bool allJoined() const; //Function to determine if all parties are in Joined State

    void step(Simulation & s); //The parties' steps

private:
    vector<Party> mVertices; 
    vector<vector<int>> mEdges;
};
