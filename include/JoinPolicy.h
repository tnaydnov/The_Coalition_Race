#pragma once
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Simulation;

class JoinPolicy {
public:
	virtual int join(vector<pair<int,int>> offered, Simulation& s) = 0;
	virtual JoinPolicy* clone() = 0;

	virtual ~JoinPolicy() = default;
};

class MandatesJoinPolicy : public JoinPolicy {
public:
	int join(vector<pair<int,int>> offered, Simulation& s);
	JoinPolicy* clone();
};

class LastOfferJoinPolicy : public JoinPolicy {
public:
	int join(vector<pair<int,int>> offered, Simulation& s);
	JoinPolicy* clone();
};