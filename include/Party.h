#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "JoinPolicy.h"

using namespace std;

class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy*);

    //Getters & Setters:
    State getState() const;
    void setState(State state);
    int getMandates() const;
    const string& getName() const;
    int getId();
    vector<pair<int, int>>& getNeighbors();

    void addToOffered(int agentId, int coalitionId); //Update the offered field
    void addNeighbor(int neighborPartyId, int weight); //Update the neighbors field

    void step(Simulation& s);
    
    
    //RULE OF 5:
    virtual ~Party(); //Destructor
    Party(const Party& other); //Copy Constructor
    Party& operator=(const Party& other); //Copy Assignment
    Party(Party&& other); //Move Constructor
    Party& operator=(Party&& other); //Move Assignment

private:
    int mId; //Party's ID
    string mName; //Party's Name
    int mMandates; //Party's Mandates
    JoinPolicy* mJoinPolicy; //Party's Join Policy
    State mState; //Party's State
    int timer; //Party's timer after turning 'CollectingOffer'
    vector<pair<int, int>> offered; //first - agentId, second - coalitionId
    vector<pair<int, int>> weightedNeighbors; //first - partyId, second - edgeWeight
};