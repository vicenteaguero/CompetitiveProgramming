#include <bits/stdc++.h>
using namespace std;

int N;
double minim {0};
double maxim {0};
double len {0};
vector<vector<double>> dataSet;

// https://www.geeksforgeeks.org/bit-tricks-competitive-programming/
int log2(int x) {
    int res = 0;
    while (x >>= 1) {
        res++;
    }
    return res;
}

bool collides(double time) {
    double currentPositive;
    bool done = false;
    for (int i = 0; i < N; i++) {
        double newPos = dataSet[i][0] + dataSet[i][1] * time;
        if (dataSet[i][1] > 0) {
            if (!done || newPos > currentPositive) {
                currentPositive = newPos;
                done = true;
            }
        } else if (done && newPos <= currentPositive) {
            return true;
        }
    }
    return false;
}

double binarySearch() {
    double first = 0;
    double last = len/2;
    int n = log2(len / 0.000000001);
    for (int i = 0; i < n; i++) {
        double mid = (last + first) / 2;
        if (collides(mid)) {
            last = mid;
        } else {
            first = mid;
        }
    }
    if (collides(last)) {
        return (first + last) / 2.0;
    }
    return -1.0;
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        double pos, vel;
        cin >> pos >> vel;
        dataSet.push_back({pos, vel});
        if (pos > maxim) {
            maxim = pos;
        }
        if (pos < minim) {
            minim = pos;
        }
    }
    len = maxim - minim;
    cout << setprecision(10) << binarySearch() << '\n';
}