// ReactionDiffusion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "Multiset.h"
#include "SpeciesReaction.h"
#include "RandomNumbers.h"
#include "Simulators.h"
#include "VectorStuff.h"

using namespace std;


int main()
{
	set_seed();
	Species e("e", 0.1, 30, 3);
	vector<Species> SpeciesList = { e };
	Reaction k1(">e", 100.0, SpeciesList);
	Reaction k2("e+e>", 1.0, SpeciesList);
	RDME g;
	g.finaltime = 10.0;
	g.reactionlist = { k1,k2 };
	
	//for (int i = -3; i < 3; i++) {
	int i = 2;
		cout << i;
		e.difc= pow(10.0, (double)i);
		g.filename = ("example" + to_string(i) + ".tsv");
		g.specieslist = { e };
		g.Simulate();
	//}

	system("pause");
    return 0;
}

