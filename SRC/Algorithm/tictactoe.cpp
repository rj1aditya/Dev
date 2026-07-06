class TicTacToe {
    vector<int> rows, cols;
    int diag, antiDiag;
    int n;

public:
    TicTacToe(int n) {
        this->n = n;
        rows.assign(n, 0);
        cols.assign(n, 0);
        diag = 0;
        antiDiag = 0;
    }

    int move(int row, int col, int player) {
        int val = (player == 1) ? 1 : -1;

        rows[row] += val;
        cols[col] += val;

        if (row == col)
            diag += val;

        if (row + col == n - 1)
            antiDiag += val;

        if (abs(rows[row]) == n ||
            abs(cols[col]) == n ||
            abs(diag) == n ||
            abs(antiDiag) == n)
            return player;

        return 0;
    }
};