#pragma once

using namespace std;
template<class T, class U>
class Tuple {
public:
	T first;
	U second;
	Tuple(T f, U s) { first = f; second = s; };
	Tuple() {};
};

template<class T>
class Multiset {
public:
	vector<Tuple<T, int>> mset;
	int multiplicity(T obj);
	Multiset(vector<T> vec);
	Multiset() {};
};

template<class T>
int Multiset<T>::multiplicity(T obj) {
	return accumulate(mset.begin(), mset.end(), 0, [&obj](int counter, Tuple<T, int> t) {return t.first == obj ? (counter + t.second) : counter; });
}

template<class T>
Multiset<T>::Multiset(vector<T> vec) {
	vector<Tuple<T, int>> newvec(vec.size());
	transform(vec.begin(), vec.end(), newvec.begin(), [](T t) {Tuple<T, int> x(t, 0); return x; });
	mset = newvec;
}