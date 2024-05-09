#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

bool is_safe(const vector<int>& board, int row, int col) {
    for (int i = 0; i < row; ++i) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

int objective_func(const vector<int>& board, int n) {
    int cost = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (board[i] == board[j] || abs(board[j] - board[i]) == j - i) {
                cost += 1;
            }
        }
    }
    return cost;
}

void solve(int n) {
    vector<int> board(n, -1);
    priority_queue<pair<int, vector<int>>> pq;
    pq.push({objective_func(board, n), board});
    bool flag = false;

    while (!pq.empty()) {
        auto curr_node = pq.top();
        pq.pop();
        vector<int> curr_board = curr_node.second;

        int row = 0;
        while (row < n && curr_board[row] != -1) {
            row++;
        }

        if (row == n) {
            cout << "The final positions of queens are as follows..." << endl;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (curr_board[i] == j) {
                        cout << 'Q' << " ";
                    } else {
                        cout << ". ";
                    }
                }
                cout << endl;
            }
            cout << endl;
            flag = true;
            return;
        }

        for (int col = 0; col < n; ++col) {
            if (is_safe(curr_board, row, col)) {
                vector<int> new_board = curr_board;
                new_board[row] = col;
                int new_cost = objective_func(new_board, n);
                pq.push({new_cost, new_board});
            }
        }
    }

    if (!flag) {
        cout << "Solution doesn't exist for n = " << n << endl;
    }
}

int main() {
    int n;
    cout << "Enter no of queens: ";
    cin >> n;
    solve(n);
    return 0;
}
