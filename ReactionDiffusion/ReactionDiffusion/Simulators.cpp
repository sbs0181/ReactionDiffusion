
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

class Simulation;

class Gillespie;

class RDME;

void Gillespie::Simulate() {
	double time = 0.0;
	Reaction toperform;
	vector<double> propensities(reactionlist.size());
	transform(reactionlist.begin(), reactionlist.end(), propensities.begin(), [this](Reaction r) {return r.NSpropensity(this->specieslist); });
	while (time < finaltime) {
		cout << time << "\t";
		for_each(specieslist.begin(), specieslist.end(), [](Species s) {cout << s.nmols << "\t"; });
		cout << endl;
		time += exprnd(sum(propensities));
		toperform = reactionlist[RandomFromVector(propensities)];
		for_each(specieslist.begin(), specieslist.end(), [&toperform](Species &s) {s.ApplyReaction(toperform); });
		transform(reactionlist.begin(), reactionlist.end(), propensities.begin(), [this](Reaction r) {return r.NSpropensity(this->specieslist); });
	}
}


void RDME::Simulate() {
	ofstream myfile;
	myfile.open(filename);


	double time = 0.0;
	double difftime;
	vector<int> indices;
	double totreaction;
	double totdiffusion;
	Reaction rtoperform;
	Species stoperform;
	vector<vector<double>> reactionPropensities(reactionlist.size());
	vector<vector<double>> diffusionPropensities(specieslist.size());
	vector<double> meanspecies = zeros(specieslist.size());
	transform(reactionlist.begin(), reactionlist.end(), reactionPropensities.begin(), [this](Reaction r) {return r.RDMEpropensity(this->specieslist); });
	transform(specieslist.begin(), specieslist.end(), diffusionPropensities.begin(), [](Species s) {return s.diffusionpropensity(); });
	while (time < finaltime) {
		myfile << time << "\t";

		myfile << endl;
		totreaction = doublesum(reactionPropensities);
		totdiffusion = doublesum(diffusionPropensities);
		difftime = exprnd(totreaction + totdiffusion);
		
		/*
		if (isinf<double>(difftime)) {
			//dosomething
			break;
		}
		*/
		time += difftime;

		for (int i = 0; i < specieslist.size(); i++) {
			meanspecies[i] += ((double)specieslist[i].nmolsRDME[0])*(difftime / finaltime);
			cout << "t="<<time<<"\t"<<"mean="<<meanspecies[i] << endl;
		}

		for_each(specieslist.begin(), specieslist.end(), [&myfile](Species s) {
			for (int i = 0; i < s.nmolsRDME.size(); i++) { 
				myfile << s.nmolsRDME[i] << "\t"; 
			}
		});


		if (RandomFromVector({ totreaction,totdiffusion }) == 0) { //Reaction
			indices = RandomFromDoubleVector(reactionPropensities);
			rtoperform = reactionlist[indices[0]];
			for_each(specieslist.begin(), specieslist.end(), [&indices, &rtoperform](Species &s) {s.ApplyReaction(rtoperform, indices[1]); });
		}
		else { //Diffusion
			indices = RandomFromDoubleVector(diffusionPropensities);
			stoperform = specieslist[indices[0]];
			specieslist[indices[0]].ApplyDiffusion(indices[1]);
		}
		transform(reactionlist.begin(), reactionlist.end(), reactionPropensities.begin(), [this](Reaction r) {return r.RDMEpropensity(this->specieslist); });
		transform(specieslist.begin(), specieslist.end(), diffusionPropensities.begin(), [](Species s) {return s.diffusionpropensity(); });
	}

	myfile.close();
	cout << "\t" << meanspecies[0] << endl;
}