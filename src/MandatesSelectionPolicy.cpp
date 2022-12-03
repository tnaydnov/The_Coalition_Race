#include "SelectionPolicy.h"
#include "Simulation.h"

int MandatesSelectionPolicy::select(vector<pair<int, int>> neighbors, Simulation& s, vector<int> offeredTo)
{
    //The function will return -1 if: there are no other parties to offer to (all Joined / offered to all / no edges)
    if (neighbors.size() != 0) 
    {
        std::size_t firstIndex = 0;
        while (firstIndex < neighbors.size() && s.GetParty(neighbors[firstIndex].first).getState() == Joined && !isOffered(neighbors[firstIndex].first, offeredTo)) 
        {
            firstIndex++;
        }
        if (firstIndex == neighbors.size()) 
        {
            return -1;
        }
        int maxMandatesID = (s.GetParty(neighbors[firstIndex].first)).getId();
        for (std::size_t i = firstIndex; i < neighbors.size(); i++) 
        {
            if (s.GetParty(neighbors[i].first).getState() != Joined && !isOffered(neighbors[i].first, offeredTo)) 
            {
                int max = s.GetParty(maxMandatesID).getMandates();
                int current = (s.GetParty(neighbors[i].first)).getMandates();
                if (current > max) 
                {
                    maxMandatesID = (s.GetParty(neighbors[i].first)).getId();
                }
            }
        }
        return maxMandatesID;
    }
    return -1;
}

SelectionPolicy* MandatesSelectionPolicy::clone() 
{
    return new MandatesSelectionPolicy();
}

bool MandatesSelectionPolicy::isOffered(int partyID, vector<int> offeredTo) 
{
    for(std::size_t i = 0; i < offeredTo.size(); i++) 
    {
        if (offeredTo[i] == partyID) 
        {
            return true;
        }
    }
    return false;
}