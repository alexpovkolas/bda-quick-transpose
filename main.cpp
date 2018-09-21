#include <vector>
#include <fstream>
#include <algorithm>


using namespace std;

inline void transpose(vector<int>& source, int initial_rank, int i_min, int j_min, int rank) {
    for (int i = 0; i < rank; ++i) {
        for (int j = i + 1; j < rank; ++j) {
            int position = (i + i_min) * initial_rank + j + j_min;
            int new_position = (j + i_min) * initial_rank + i + j_min;
            swap(source[position], source[new_position]);
        }
    }
}

vector<int> generate_input(int n, int seed) {
    vector<int> d(n * n);
    for (size_t i = 0; i < d.size(); ++i) {
        d[i] = seed;
        seed = ((long long) seed * 197 + 2017) & 987654;
    }
    return d;
}

long long get_hash(const vector<int>& d) {
    const long long MOD = 987654321054321LL;
    const long long MUL = 179;

    long long result_value = 0;
    for (size_t i = 0; i < d.size(); ++i)
        result_value = (result_value * MUL + d[i]) & MOD;
    return result_value;
}

int main() {

    ifstream input("input", ios::in);
    int n = 0;
    int seed = 0;
    int rows_count = 0;
    input >> n >> seed >> rows_count;
    vector<vector<int>> params(0);
    for (int i = 0; i < rows_count; ++i) {
        vector<int> items(3);
        input >> items[0] >> items[1] >> items[2];
        params.push_back(items);
    }

    vector<int> source = generate_input(n, seed);

    for (auto &sub_matrix : params) {
        transpose(source, n, sub_matrix[0], sub_matrix[1], sub_matrix[2]);
    }

    long long result = get_hash(source);

    ofstream output("output", ios_base::out | ios_base::trunc);
    output << result;


    return 0;
}

