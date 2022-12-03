#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Coalition
{
public:
    Coalition(int id);

    //Getters & Setters:
    int getID();
    int getMandates() const;
    int GetMandates();
    void setMandates(int mandates);
    vector<int> getParties() const;

    void addParty(int partyId, int mandates); //Update the partyIdList field

private:
    int mId; //Coalition's ID
    int mMandates; //Coalition's Mandates
    vector<int> partyIdList; //List of the coalition's parties IDs
};