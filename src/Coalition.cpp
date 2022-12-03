#include "Coalition.h"

Coalition::Coalition(int id) : mId(id), mMandates(), partyIdList()
{}

//Getters & Setters:
int Coalition::getID()
{
	return mId;
}

int Coalition::getMandates() const
{
	return mMandates;
}

int Coalition::GetMandates()
{
	return mMandates;
}

void Coalition::setMandates(int mandates) 
{
	mMandates = mandates;
}

vector<int> Coalition::getParties() const
{
	return partyIdList;
}


void Coalition::addParty(int partyId, int mandates)
{
	partyIdList.push_back(partyId);
	mMandates = mMandates + mandates;
}





