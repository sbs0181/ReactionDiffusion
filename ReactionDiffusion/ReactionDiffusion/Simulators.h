#pragma once

using namespace std;
class Simulation {
public:
	double finaltime;
	string filename;
	vector<Species> specieslist;
	vector<Reaction> reactionlist;
};

class Gillespie : public Simulation {
public:
	void Simulate();
};


class RDME : public Simulation {
public:
	void Simulate();
};

