#pragma once

void set_seed();

double unifrnd(double a = 0.0, double b = 1.0);

double exprnd(double l = 1.0);

int RandomFromVector(vector<double> vec);

vector<int> RandomFromDoubleVector(vector<vector<double>> vec);

vector<int> MultinomialRnd(int N, int Nvox);