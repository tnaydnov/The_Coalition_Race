#include "Graph.h"
#include "Simulation.h"

Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges)
{
    // You can change the implementation of the constructor, but not the signature!
}

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}

int Graph::getNumVertices() const
{
    return mVertices.size();
}

const Party& Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}

Party& Graph::GetParty(int partyId)
{
    return mVertices[partyId];
}

const vector<Party>& Graph::getVertices() const
{
    return mVertices;
}

void Graph::setPartiesNeighbors()
{
    for (std::size_t i = 0; i < mVertices.size(); i++) 
    {
        for (std::size_t j = 0; j < mVertices.size(); j++) 
        {
            int weight = getEdgeWeight(mVertices[i].getId(), mVertices[j].getId());
            if (weight != 0) 
            {
                mVertices[i].addNeighbor(mVertices[j].getId(), weight);
            }
        }
    }
}

bool Graph::allJoined() const
{
    for (std::size_t i = 0; i < mVertices.size(); i++) 
    {
        if (mVertices[i].getState() != Joined) 
        {
            return false;
        }
    }
    return true;
}

void Graph::step(Simulation &s)
{
    for (std::size_t i = 0; i < mVertices.size(); i++) 
    {
            mVertices[i].step(s);
    }
}