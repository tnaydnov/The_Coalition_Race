#include "Simulation.h"
#include "Party.h"


Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), mCoalitions()
{
    for (std::size_t i = 0; i < mAgents.size(); i++) {
        Coalition coalition(mAgents[i].getId());
        coalition.addParty(mAgents[i].getPartyId(), GetParty(mAgents[i].getPartyId()).getMandates());
        mCoalitions.push_back(coalition);
        mAgents[i].setCoalition(mAgents[i].getId());
    }
    mGraph.setPartiesNeighbors();
}

const Graph& Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent>& Simulation::getAgents() const
{
    return mAgents;
}

const Party& Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

Party& Simulation::GetParty(int partyId)
{
    return mGraph.GetParty(partyId);
}

Agent* Simulation::getAgent(int agentID)
{
    for(std::size_t i = 0; i < mAgents.size(); i++) 
    {
        if(agentID == mAgents[i].getId()) 
        {
            return &mAgents[i];
        }
    }
    return nullptr;
}

Coalition* Simulation::getCoalition(int coalitionID)
{
    for(std::size_t i = 0; i < mCoalitions.size(); i++) 
    {
        if(mCoalitions[i].getID() == coalitionID) 
        {
            return &mCoalitions[i];
        } 
    }
    return nullptr;
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> output;
    for (std::size_t i = 0; i < mCoalitions.size(); i++) 
    {
        output.push_back(mCoalitions[i].getParties());
    }
    return output;
}

void Simulation::step()
{
    for (std::size_t i = 0; i < mAgents.size(); i++) {
        mAgents[i].step(*this);
    }
    mGraph.step(*this);
}

bool Simulation::shouldTerminate() const
{
    return mGraph.allJoined() || over61();
}

void Simulation::clone(int joinedAgentID, int joinedPartyID)
{
    Agent agent(*(getAgent(joinedAgentID)));
    agent.setPartyId(joinedPartyID);
    agent.setId(mAgents.size());
    mAgents.push_back(agent);
    agent.step(*this);
}

bool Simulation::over61() const
{
    for (std::size_t i = 0; i < mCoalitions.size(); i++) 
    {
        if (mCoalitions[i].getMandates() >= 61) 
        {
            return true;
        }
    }
    return false;
}