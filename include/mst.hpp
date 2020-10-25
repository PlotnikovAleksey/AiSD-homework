#include <iostream>
#include <vector>
#include <unordered_set>

typedef std::vector<std::vector<double>> matrix;

class Graph {
private:
	matrix adjacency_matrix;
	size_t amount;
public:
	Graph() = default;

	~Graph() = default;

	void set(matrix& m) {
		adjacency_matrix = std::move(m);
		amount = adjacency_matrix.size();
	}

	void find_mst() {
		std::vector<double> min_weights = adjacency_matrix[0];
		std::vector<double> to_min(min_weights.size(), 0);
		std::unordered_set<size_t> used;
		used.insert(0);
		size_t j, i = 0;
		double weight_of_mst = 0;
		while (used.size() != amount) {
			double current = -1;
			size_t current_ind = 0;
			for (j = 0; j < amount; j++) {
				if (min_weights[j] == 0)
					continue;
				if ((used.count(j) == 0) && ((min_weights[j] < current) || (current == -1))) {
					current = min_weights[j];
					current_ind = j;
				}
			}
			std::cout << "[" << to_min[current_ind] << ' ' << current_ind << "] " << min_weights[current_ind] << '\n';
			weight_of_mst += min_weights[current_ind];
			used.insert(current_ind);
			for (size_t k = 0; k < amount; k++) {
				if ((adjacency_matrix[current_ind][k] < min_weights[k]) || (min_weights[k] == 0)) {
					min_weights[k] = adjacency_matrix[current_ind][k];
					to_min[k] = current_ind;
				}
			}
		}
		std::cout << "weight of MST = " << weight_of_mst;
	}
};