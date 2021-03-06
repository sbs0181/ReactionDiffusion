#include "stdafx.h"
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include "Multiset.h"
#include "SpeciesReaction.h"
#include "VectorStuff.h"
#include "RandomNumbers.h"

using namespace std;
int fallingpower(int x, int y) {
	switch (y) {
	case 0:
		return 1;
		break;
	case 1:
		return x;
		break;
	case 2:
		return x*(x - 1);
		break;
	default:
		return 1;
		break;
	}
}

vector<int> fallingpower(vector<int> x, int y) {
	switch (y) {
	case 0:
		return ones(x.size());
		break;
	case 1:
		return x;
		break;
	case 2:
		return ElementwiseProduct<int>(x,VectorPlusScalar<int>(x,-1));
		break;
	default:
		return ones(x.size());
		break;
	}
}

bool Species::operator==(Species &y) {
	if (y.name == name) {
		return true;
	}
	else {
		return false;
	}
}

void Species::ApplyReaction(Reaction react) {
	nmols += react.stoichiometry().multiplicity(*this);
}

void Species::ApplyReaction(Reaction react, int voxindex) {
	nmolsRDME[voxindex] += react.stoichiometry().multiplicity(*this);
}

void Species::ApplyDiffusion(int voxindex) {
	nmolsRDME[voxindex] -=1;
	double r = unifrnd();
	if (r < 0.5) {
		if (voxindex == 0) {
			nmolsRDME[nmolsRDME.size() - 1] += 1;
		}
		else {
			nmolsRDME[voxindex-1] += 1;
		}
	}
	else {
		if (voxindex == (nmolsRDME.size()-1)) {
			nmolsRDME[0] += 1;
		}
		else {
			nmolsRDME[voxindex + 1] += 1;
		}
	}
}

vector<double> Species::diffusionpropensity() {
	double RDMErate = 2.0*difc*((double)pow(nmolsRDME.size(), 2));

	return VectorTimesScalar<int>(nmolsRDME, RDMErate);
}

Species::Species(string str, double d, int nm) {
	name = str; difc = d; nmols = nm;
}

Species::Species(string str, double d, int nm,int Nv) {
	nmolsRDME = MultinomialRnd(nm, Nv);
	difc = d;
	name = str;
	nmols = nm;
}



Multiset<Species> Reaction::stoichiometry() {
	Multiset<Species> stoich;
	vector<Tuple<Species, int>> stoichm(reactants.mset.size());
	transform(reactants.mset.begin(), reactants.mset.end(), products.mset.begin(), stoichm.begin(), [](Tuple<Species, int> r, Tuple<Species, int>p) {Tuple<Species, int> s(r.first, p.second - r.second); return s; });
	stoich.mset = stoichm;
	return stoich;
}

double Reaction::NSpropensity(vector<Species> specvec){
	vector<int> powers(specvec.size());
	transform(specvec.begin(), specvec.end(), reactants.mset.begin(), powers.begin(), [](Species s, Tuple<Species, int>t) {return fallingpower(s.nmols, t.second); });
	return rate*accumulate(powers.begin(), powers.end(), 1, multiplies<int>());
}

vector<double> Reaction::RDMEpropensity(vector<Species> specvec) {
	vector<vector<int>> powers(specvec.size());
	transform(specvec.begin(), specvec.end(), reactants.mset.begin(), powers.begin(), [](Species s, Tuple<Species, int>t) {return fallingpower(s.nmolsRDME, t.second); });
	return VectorTimesScalar<int>(accumulate(powers.begin(), powers.end(), ones(powers[0].size()), [](vector<int> v1, vector<int> v2) {return ElementwiseProduct<int>(v1, v2); }), rate);
}

Reaction::Reaction(string str, double k, vector<Species> specvec) {
	rate = k;
	ptrdiff_t pos;
	vector<string> vectorofnames(specvec.size());
	transform(specvec.begin(), specvec.end(), vectorofnames.begin(), [](Species s) {return s.name; });
	Multiset<Species> re(specvec);
	Multiset<Species> pr(specvec);
	int arrow = str.find(">");
	string left = str.substr(0, arrow);
	string right = str.substr(arrow + 1, (str.size() - arrow) - 1);
	if (arrow == 0) {
		//do nothing
	}
	else if (left.find("+") == string::npos) {
		pos = find(vectorofnames.begin(), vectorofnames.end(), left) - vectorofnames.begin();
		re.mset[pos].second += 1;
	}
	else {
		string firstr = left.substr(0, left.find("+"));
		string secondr = left.substr(left.find("+") + 1, (left.size() - left.find("+")) - 1);
		pos = find(vectorofnames.begin(), vectorofnames.end(), firstr) - vectorofnames.begin();
		re.mset[pos].second += 1;
		pos = find(vectorofnames.begin(), vectorofnames.end(), secondr) - vectorofnames.begin();
		re.mset[pos].second += 1;
	}
	if (right.size() == 0) {
		//do nothing
	}
	else if (right.find("+") == string::npos) {
		pos = find(vectorofnames.begin(), vectorofnames.end(), right) - vectorofnames.begin();
		pr.mset[pos].second += 1;
	}
	else {
		string firstp = right.substr(0, right.find("+"));
		string secondp = right.substr(right.find("+") + 1, (right.size() - right.find("+")) - 1);
		pos = find(vectorofnames.begin(), vectorofnames.end(), firstp) - vectorofnames.begin();
		pr.mset[pos].second += 1;
		pos = find(vectorofnames.begin(), vectorofnames.end(), secondp) - vectorofnames.begin();
		pr.mset[pos].second += 1;
	}
	reactants = re;
	products = pr;

}
