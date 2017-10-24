#pragma once
using namespace std;
std::vector<int> ones(int);
std::vector <double> zeros(int);

template<class T>
std::vector<T> ElementwiseProduct(vector<T> v1, vector<T> v2) {
	vector<T> v3(v1.size());
	transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), multiplies<T>());
	return v3;
}

template<class T>
std::vector<T>VectorPlusScalar(vector<T> v, T s) {
	vector<T> v2(v.size());
	transform(v.begin(), v.end(), v2.begin(), [&s](T t) {return t + s; });
	return v2;
}

template<class T>
std::vector<double>VectorTimesScalar(vector<T> v, double s) {
	vector<double> v2(v.size());
	transform(v.begin(), v.end(), v2.begin(), [&s](T t) {return (double)t*s; });
	return v2;
}

vector<double> cumsum(vector<double> vec);

double sum(vector<double> vec);

double doublesum(vector<vector<double>> vec);

vector<double> internalsum(vector<vector<double>> vec);