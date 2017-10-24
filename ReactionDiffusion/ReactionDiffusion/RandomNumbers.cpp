#include "stdafx.h"
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include "VectorStuff.h"

using namespace std;

void set_seed() {
	srand(time(NULL));
}

double unifrnd(double a=0.0,double b=1.0) {
	double u = a + (b - a)*(((double)rand()) / ((double)RAND_MAX));
	while (u <= a || u >= b) {
		u = a + (b - a)*(((double)rand()) / ((double)RAND_MAX));
	}
	return u;
}

double exprnd(double l = 1.0) {
	return -log(unifrnd()) / l;
}



int RandomFromVector(vector<double> vec) {
	vector<double> cvec = cumsum(vec);
	double r = unifrnd(0.0, sum(vec));
	auto i = find_if(cvec.begin(), cvec.end(), [&r](double d) {return (d >= r); });
	auto j = cvec.begin();
	i - j;
	return ((int) (i - j));
}

vector<int> RandomFromDoubleVector(vector<vector<double>> vec) {
	int reactionindex = RandomFromVector(internalsum(vec));
	int voxelindex = RandomFromVector(vec[reactionindex]);
	return { reactionindex,voxelindex };
}


vector<int> MultinomialRnd(int N, int Nvox) {
	vector<int> vec(Nvox);
	for (int i = 0; i < N; i++) {
		vec[rand() % Nvox] += 1;
	}
	return vec;
}
