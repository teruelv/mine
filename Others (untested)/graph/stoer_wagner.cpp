/*
	Tested: ZOJ 2753
	Complexity: O(n^3)
*/

template<typename T>
pair<T, vector<int>> stoer_wagner(vector<vector<T>> &weights)
{
	int n = weights.size();
	vector<int> used(n), cut, best_cut;
	T best_weight = -1;

	for (int phase = n - 1; phase >= 0; --phase)
	{
		vector<T> w = weights[0];
		vector<int> added = used;
		int prev, last = 0;

		for (int i = 0; i < phase; ++i)
		{
			prev = last;
			last = -1;
			for (int j = 1; j < n; ++j)
				if (!added[j] && (last == -1 || w[j] > w[last]))
					last = j;

			if (i == phase - 1)
			{
				for (int j = 0; j < n; ++j)
					weights[prev][j] += weights[last][j];
				for (int j = 0; j < n; ++j)
					weights[j][prev] = weights[prev][j];

				used[last] = true;
				cut.push_back(last);

				if (best_weight == -1 || w[last] < best_weight)
				{
					best_cut = cut;
					best_weight = w[last];
				}
			}
			else
			{
				for (int j = 0; j < n; j++)
					w[j] += weights[last][j];
				added[last] = true;
			}
		}
	}

	return make_pair(best_weight, best_cut);
}
