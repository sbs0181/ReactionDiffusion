#pragma once

using namespace std;
class Species;
class Reaction;
int fallingpower(int x, int y);

class Species {
public:
	string name;
	double difc;
	int nmols;

	bool operator==(Species &y);
	void ApplyReaction(Reaction react);
	Species(string str, double d, int nm);
	Species() {};
};

class Reaction {
public:
	double rate;
	Multiset<Species> reactants;
	Multiset<Species> products;
	Multiset<Species> stoichiometry();
	double propensity(vector<Species> specvec);
	Reaction(string str, double k, vector<Species> specvec);
	Reaction() {};
};

