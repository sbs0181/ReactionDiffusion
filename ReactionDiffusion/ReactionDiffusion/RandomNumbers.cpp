#include "stdafx.h"
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>

using namespace std;

void set_seed() {
	srand(time(NULL));
}

double unifrnd(double a=0.0,double b=1.0) {
	return a + (b - a)*(((double)rand()) / ((double)RAND_MAX));
}

double exprnd(double l = 1.0) {
	return -log(unifrnd()) / l;
}

vector<double> cumsum(vector<double> vec) {
	vector<double> csum(vec.size());
	partial_sum(vec.begin(), vec.end(), csum.begin());
	return csum;
}

double sum(vector<double> vec) {
	return accumulate(vec.begin(), vec.end(), 0.0);
}

int RandomFromVector(vector<double> vec) {
	vector<double> cvec = cumsum(vec);
	double r = unifrnd(0.0, sum(vec));

	auto i = find_if(cvec.begin(), cvec.end(), [&r](double d) {return (d > r); });
	auto j = cvec.begin();
	i - j;
	return ((int) (i - j));
}
