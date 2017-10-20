
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

class Simulation;

class Gillespie;

void Gillespie::Simulate() {
	double time = 0.0;
	int index;
	Reaction toperform;
	vector<double> propensities(reactionlist.size());
	transform(reactionlist.begin(), reactionlist.end(), propensities.begin(), [this](Reaction r) {return r.propensity(this->specieslist); });
	while (time < finaltime) {
		cout << time << "\t";
		for_each(specieslist.begin(), specieslist.end(), [](Species s) {cout << s.nmols << "\t"; });
		cout << endl;
		time += exprnd(sum(propensities));
		toperform = reactionlist[RandomFromVector(propensities)];
		for_each(specieslist.begin(), specieslist.end(), [&toperform](Species &s) {s.ApplyReaction(toperform); });
		transform(reactionlist.begin(), reactionlist.end(), propensities.begin(), [this](Reaction r) {return r.propensity(this->specieslist); });
	}
}