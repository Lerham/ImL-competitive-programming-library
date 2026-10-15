// Source: https://github.com/Lerham/ImL-competitive-programming-library/blob/39ddc0957ddf60ecc625564c55c1d7e568b1a8d7/300/run_length_encoding.cpp
vector<pair<char, int>> rle(const string& S) {
    vector<pair<char, int>> res;
    for (char c : S) {
        if (res.empty() || res.back().first != c) {
            res.push_back({c, 1});
        } else {
            res.back().second++;
        }
    }
    return res;
}

int main() {
    string S = "aaabbcccc";
    auto v = rle(S);

    // v = {{'a', 3}, {'b', 2}, {'c', 4}}
}