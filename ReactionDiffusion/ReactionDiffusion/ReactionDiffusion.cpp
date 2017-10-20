// ReactionDiffusion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

#include "Multiset.h"
#include "SpeciesReaction.h"
#include "RandomNumbers.h"
#include "Simulators.h"

using namespace std;

class RDME : public Simulation {

};

int main()
{
	set_seed();
	Species E("E", 0.0, 3);
	Species S("S", 0.0, 10);
	Species C("C", 0.0, 0);
	vector<Species> SpeciesList = { E,S,C };
	Reaction kf("E+S>C", 1.0,SpeciesList);
	Reaction kr("C>E+S", 1.0, SpeciesList);
	Reaction kcat("C>E", 1.0, SpeciesList);
	Reaction kin(">S", 1.0, SpeciesList);

	Gillespie g;
	g.finaltime = 10.0;
	g.reactionlist = { kf,kr,kcat,kin };
	g.specieslist = SpeciesList;
	g.Simulate();
	
	system("pause");
    return 0;
}

