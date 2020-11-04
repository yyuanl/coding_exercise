#include <iostream>
#include <vector>
using namespace std;
/*
f({a0, a1,a2...an}) --> {{}, {},...,{}}
a0加入到f({a1,...,an})的每个排列
...
an加到f({a0,...an-1})的每个排列
*/
vector<int> remove_x(vector<int>&v, int e) {
	vector<int>result;
	for (auto x : v) {
		if (x != e) {
			result.push_back(x);
		}
	}
	return result;
}
vector<vector<int>> permutation(vector<int>v) {
	if (v.empty()) {
		vector<vector<int>>res;
		return res;
	}
	vector<vector<int>>r;
	for (auto e:v) {
		vector<vector<int>>temp = permutation(remove_x(v, e));
		if (temp.empty()) {
			vector<int>one;
			one.push_back(e);
			r.push_back(one);
			continue;
		}
		for (auto t : temp) {
			t.insert(t.begin(),e);
			r.push_back(t);
		}
	}
	return r;
}
int main() {
	vector<int>vtor = {1,2,3,4};
	vector<vector<int>>res = permutation(vtor);
	for (auto e : res) {
		for (auto x : e) {
			cout << x<<" ";
		}
		cout << endl;
	}

	return 0;
}