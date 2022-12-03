#include "SelectionPolicy.h"
#include "Simulation.h"

int EdgeWeightSelectionPolicy::select(vector<pair<int, int>> neighbors, Simulation& s, vector<int> offeredTo)
{
    //The function will return -1 if: there are no other parties to offer to (all Joined / offered to all / no edges)
    if (neighbors.size() != 0) 
    {
        std::size_t firstIndex = 0;
        while (firstIndex < neighbors.size() && (isOffered(neighbors[firstIndex].first, offeredTo) || s.GetParty(neighbors[firstIndex].first).getState() == Joined)) 
        {
            firstIndex++;
        }
        if (firstIndex == neighbors.size() || isOffered(neighbors[firstIndex].first, offeredTo)) 
        {
            return -1;
        }
        int maxWeightPartyID = (s.GetParty(neighbors[firstIndex].first)).getId();
        int maxWeight = neighbors[firstIndex].second;
        for(std::size_t i = firstIndex; i < neighbors.size(); i++) 
        {
            if (neighbors[i].second > maxWeight && s.GetParty(neighbors[i].first).getState() != Joined && !isOffered(neighbors[i].first, offeredTo)) 
            {
                maxWeightPartyID = (s.GetParty(neighbors[i].first)).getId();
                maxWeight = neighbors[i].second;
            }
        }
        return maxWeightPartyID;
    }
    return -1;
}

SelectionPolicy* EdgeWeightSelectionPolicy::clone() 
{
    return new EdgeWeightSelectionPolicy();
}

bool EdgeWeightSelectionPolicy::isOffered(int partyID, vector<int> offeredTo) {
    for(std::size_t i = 0; i < offeredTo.size(); i++) {
        if (offeredTo[i] == partyID) {
            return true;
        }
    }
    return false;
}