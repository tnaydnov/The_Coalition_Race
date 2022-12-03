#include "JoinPolicy.h"
#include "Simulation.h"

int MandatesJoinPolicy::join(vector<pair<int,int>> offered, Simulation& s)
{
    int maxMandatesAgent = offered[0].first;
    for (std::size_t i = 0; i < offered.size(); i++) 
    {
        if(s.getCoalition(s.getAgent(maxMandatesAgent)->getCoalitionId())->GetMandates() < s.getCoalition(s.getAgent(offered[i].first)->getCoalitionId())->GetMandates()) 
        {
            maxMandatesAgent = offered[i].first;
        }
    }
	return maxMandatesAgent;
}

JoinPolicy* MandatesJoinPolicy::clone() 
{
    return new MandatesJoinPolicy();
}