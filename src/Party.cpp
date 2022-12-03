#include "Party.h"
#include "Simulation.h"


Party::Party(int id, string name, int mandates, JoinPolicy* jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), timer(-1), offered(), weightedNeighbors()
{}

//Getters & Setters
State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string& Party::getName() const
{
    return mName;
}

int Party::getId()
{
    return mId;
}

vector<pair<int, int>>& Party::getNeighbors()
{
    return weightedNeighbors;
}


void Party::addToOffered(int agentId, int coalitionId) 
{
    offered.push_back(pair<int,int>(agentId, coalitionId));
}

void Party::addNeighbor(int neighborPartyId, int edgeWeight)
{
    weightedNeighbors.push_back(pair<int,int>(neighborPartyId, edgeWeight));
}

//RULE OF 5:
Party::~Party()
{
    if (mJoinPolicy) delete mJoinPolicy;
}

Party::Party(const Party& other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy->clone()), mState(other.mState), timer(other.timer), offered(other.offered), weightedNeighbors(other.weightedNeighbors)
{}

Party& Party::operator=(const Party& other)
{
    if (this != &other) 
    {
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        if (mJoinPolicy) delete mJoinPolicy;
        mJoinPolicy = other.mJoinPolicy->clone();
        mState = other.mState;
        timer = other.timer;
        offered = other.offered;
        weightedNeighbors = other.weightedNeighbors;
    }
    return *this;
}

Party::Party(Party&& other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState), timer(other.timer), offered(other.offered), weightedNeighbors(other.weightedNeighbors)
{
    other.mJoinPolicy = nullptr;
}

Party& Party::operator=(Party&& other)
{
    if (this != &other) {
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        if (mJoinPolicy) delete mJoinPolicy;
        mJoinPolicy = other.mJoinPolicy;
        mState = other.mState;
        timer = other.timer;
        offered = other.offered;
        weightedNeighbors = other.weightedNeighbors;
        other.mJoinPolicy = nullptr;
    }
    return *this;
}

void Party::step(Simulation& s)
{
    if (mState == CollectingOffers) 
    {
        if (timer >= 2) 
        {
            int chosenAgentID = mJoinPolicy->join(offered, s);
            s.getCoalition((s.getAgent(chosenAgentID))->getCoalitionId())->addParty(mId, mMandates);
            setState(Joined);
            s.clone(chosenAgentID, mId);
        }
        timer++;
    }
}