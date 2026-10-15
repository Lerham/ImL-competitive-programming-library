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