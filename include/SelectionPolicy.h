#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;
class Simulation;

class SelectionPolicy {
public:
	virtual int select(vector<pair<int, int>> neighbors, Simulation& s, vector<int> offeredTo) = 0;
	virtual SelectionPolicy* clone() = 0;

	virtual ~SelectionPolicy() = default;
};

class MandatesSelectionPolicy : public SelectionPolicy {
public:
	int select(vector<pair<int, int>> neighbors, Simulation& s, vector<int> offeredTo) override;
	SelectionPolicy* clone();
	bool isOffered(int partyID, vector<int> offeredTo); //Check if the partyId the agent chose already got an offer from him
};

class EdgeWeightSelectionPolicy : public SelectionPolicy {
public:
	int select(vector<pair<int, int>> neighbors, Simulation& s, vector<int> offeredTo) override;
	SelectionPolicy* clone();
	bool isOffered(int partyID, vector<int> offeredTo); //Check if the partyId the agent chose already got an offer from him
};