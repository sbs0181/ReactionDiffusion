#pragma once

using namespace std;
class Species;
class Reaction;
int fallingpower(int x, int y);
vector<int> fallingpower(vector<int> x, int y);

class Species {
public:
	string name;
	double difc;
	int nmols;
	vector<int> nmolsRDME;

	bool operator==(Species &y);
	void ApplyReaction(Reaction react);// Non-spatial
	void ApplyReaction(Reaction react, int voxindex); // RDME

	void ApplyDiffusion(int voxindex);
	vector<double> diffusionpropensity();


	Species(string str, double d, int nm); // Non-spatial constructor
	Species(string str, double d, int nm, int Nv); //RDME constructor
	Species() {}; //Default
};

class Reaction {
public:
	double rate;
	Multiset<Species> reactants;
	Multiset<Species> products;
	Multiset<Species> stoichiometry();
	double NSpropensity(vector<Species> specvec); //Non-spatial
	vector<double> RDMEpropensity(vector<Species> specvec); //RDME

	Reaction(string str, double k, vector<Species> specvec);
	Reaction() {};
};



