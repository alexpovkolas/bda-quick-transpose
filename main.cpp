#include <vector>
#include <iostream>
#include <algorithm>


#define __PROFILE__
#ifdef __PROFILE__

#include <chrono>

#endif


using namespace std;

void transpose(vector<int> &source, int initial_rank, int i_min, int j_min, int rank) {

    for (int i = 0; i < rank; ++i) {
        for (int j = i + 1; j < rank; ++j) {
            int position = (i + i_min) * initial_rank + j + j_min;
            int new_position = (j + i_min) * initial_rank + i + j_min;

            swap(source[position], source[new_position]);

            // 15% slower than swap
//            int temp = source[position];
//            source[position] = source[new_position];
//            source[new_position] = temp;

            //- twice time slower than swap
//            iter_swap(source.begin() + position, source.begin() + new_position);
        }
    }
}

void transpose2(vector<int> &m, size_t n, int i_min, int j_min, int rank) {
    int block = 0, size = 16;


    for (block = 0; block + size - 1 < rank; block += size) {
        for (int i = block; i < block + size; ++i) {
            for (int j = i + 1; j < block + size; ++j) {
                swap(m[(i + i_min) * n + j + j_min], m[(j + i_min) * n + i + j_min]);
            }
        }
        for (int i = block + size; i < rank; ++i) {
            for (int j = block; j < block + size; ++j) {
                swap(m[(i + i_min) * n + j + j_min], m[(j + i_min) * n + i + j_min]);
            }
        }
    }

    for (int i = block; i < rank; ++i) {
        for (int j = i + 1; j < rank; ++j) {
            swap(m[(i + i_min) * n + j + j_min], m[(j + i_min) * n + i + j_min]);
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

long long get_hash(const vector<int> &d) {
    const long long MOD = 987654321054321LL;
    const long long MUL = 179;

    long long result_value = 0;
    for (size_t i = 0; i < d.size(); ++i)
        result_value = (result_value * MUL + d[i]) & MOD;
    return result_value;
}

int main() {

    int n = 0;
    int seed = 0;
    int rows_count = 0;
    cin >> n >> seed >> rows_count;
    vector<vector<int>> params(0);
    for (int i = 0; i < rows_count; ++i) {
        vector<int> items(3);
        cin >> items[0] >> items[1] >> items[2];
        params.push_back(items);
    }

#ifdef __PROFILE__
    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
#endif

    vector<int> source = generate_input(n, seed);

    for (auto &sub_matrix : params) {
        //transpose(source, n, sub_matrix[0], sub_matrix[1], sub_matrix[2]);
        transpose2(source, n, sub_matrix[0], sub_matrix[1], sub_matrix[2]);
    }

#ifdef __PROFILE__
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << " Time difference = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << std::endl;
#endif


    long long result = get_hash(source);

    cout << result << std::endl;



    return 0;
}


