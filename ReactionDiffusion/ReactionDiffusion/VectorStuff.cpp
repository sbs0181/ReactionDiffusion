#include "stdafx.h"
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> ones(int n) {
	vector<int> vec;
	for (int i = 0; i < n; i++) {
		vec.push_back(1);
	}
	return vec;
}

vector<double> zeros(int n) {
	vector<double> vec;
	for (int i = 0; i < n; i++) {
		vec.push_back(0.0);
	}
	return vec;
}

vector<double> cumsum(vector<double> vec) {
	vector<double> csum(vec.size());
	partial_sum(vec.begin(), vec.end(), csum.begin());
	return csum;
}

double sum(vector<double> vec) {
	return accumulate(vec.begin(), vec.end(), 0.0);
}

double doublesum(vector<vector<double>> vec) {
	vector<double> v2(vec.size());
	transform(vec.begin(), vec.end(), v2.begin(), [](vector<double> v) {return sum(v); });
	return accumulate(v2.begin(), v2.end(), 0.0);
}

vector<double> internalsum(vector<vector<double>> vec) {
	vector<double> v2(vec.size());
	transform(vec.begin(), vec.end(), v2.begin(), [](vector<double> v) {return sum(v); });
	return v2;
}