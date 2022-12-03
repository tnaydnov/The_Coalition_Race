#include "JoinPolicy.h"
#include "Simulation.h"

int LastOfferJoinPolicy::join(vector<pair<int,int>> offered, Simulation& s)
{
	return offered.back().first;
}

JoinPolicy* LastOfferJoinPolicy::clone() 
{
    return new LastOfferJoinPolicy();
}