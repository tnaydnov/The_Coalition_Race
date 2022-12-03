#include "Agent.h"
#include "Simulation.h"


Agent::Agent(int agentId, int partyId, SelectionPolicy* selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy), mCoalitionId(), offeredTo()
{}

//Getters & Setters:

int Agent::getId() const
{
    return mAgentId;
}

void Agent::setId(int agentId) 
{
    mAgentId = agentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::setPartyId(int partyId)
{
    mPartyId = partyId;
}

int Agent::getCoalitionId()
{
    return mCoalitionId;
}

void Agent::setCoalition(int coalitionId)
{
    mCoalitionId = coalitionId;
}


void Agent::step(Simulation& sim)
{
    int selectedPartyId = mSelectionPolicy->select(sim.GetParty(mPartyId).getNeighbors(), sim, offeredTo);
    if (selectedPartyId != -1) 
    {
        if ((sim.GetParty(selectedPartyId)).getState() == Waiting) 
        {
            (sim.GetParty(selectedPartyId)).setState(CollectingOffers);
        }
        (sim.GetParty(selectedPartyId)).addToOffered(mAgentId,mCoalitionId);
        offeredTo.push_back(selectedPartyId);
    }
}

//RULE OF 5:

Agent::~Agent()
{
    delete mSelectionPolicy;
}

Agent::Agent(const Agent& other)  : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy->clone()), mCoalitionId(other.mCoalitionId), offeredTo(other.offeredTo)
{}

Agent& Agent::operator=(const Agent& other)
{
    if (this != &other) {
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        if (mSelectionPolicy) delete mSelectionPolicy;
        mSelectionPolicy = other.mSelectionPolicy->clone();
        mCoalitionId = other.mCoalitionId;
        offeredTo = other.offeredTo;
    }
    return *this;
}

Agent::Agent(Agent&& other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy), mCoalitionId(other.mCoalitionId), offeredTo(other.offeredTo)
{
    other.mSelectionPolicy = nullptr;
}

Agent& Agent::operator=(Agent&& other)
{
    if (this != &other) {
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        if (mSelectionPolicy) delete mSelectionPolicy;
        mSelectionPolicy = other.mSelectionPolicy;
        mCoalitionId = other.mCoalitionId;
        offeredTo = other.offeredTo;
        other.mSelectionPolicy = nullptr;
    }
    return *this;
}
