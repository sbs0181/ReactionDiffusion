#pragma once

using namespace std;
class Simulation {
public:
	double finaltime;
	vector<Species> specieslist;
	vector<Reaction> reactionlist;
};

class Gillespie : public Simulation {
public:
	void Simulate();
};