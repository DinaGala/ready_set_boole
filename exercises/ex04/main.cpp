#include <bits/stdc++.h>
#include "../../inc/rsb.hpp"
using namespace std;

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string formula;
    if (argc > 1) {
        formula = argv[1];
    } else {
        // read whole stdin (first line or entire input)
        if (!getline(cin, formula)) {
            cerr << "Usage: " << argv[0] << " <formula-in-RPN>\n";
            return 1;
        }
    }

    if (formula.empty()) {
        cerr << "Empty formula\n";
        return 1;
    }

    print_truth_table(&formula);
    return 0;
}