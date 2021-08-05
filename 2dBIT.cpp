#include <iostream>
#include <vector>
using namespace std;

#define LSB(S) (S & (-S))
typedef vector<vector<int>> vii;
typedef vector<int> vi;

class FenwickTree{
private:
    vii ft;

public:

    int query(int x, int y){
        int sum = 0;
        for(int i = x; i > 0; i = i - LSB(i)){
            for(int j = y; j > 0; j = j - LSB(j)){
                sum = sum + ft[i][j];
            }
        }
        return sum;
    }

    int query(int x1, int y1, int x2, int y2){
        return (query(x2, y2) - query(x2, y1-1) - query(x1-1, y2) + query(x1 - 1, y1 - 1));
    }

    void update(int x, int y, int value){
        for(int i = x; i < ft.size(); i = i + LSB(i)){
            for(int j = y; j < ft[0].size(); j = j + LSB(j)){
                ft[i][j] += value;
            }
        }
    }

    FenwickTree(vector<vector<int>> matrix){
        int n = matrix.size(), m = matrix[0].size();
        ft.assign(n + 1, vector<int> (m + 1, 0));
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j)
                update(i + 1, j + 1, matrix[i][j]);
        }
    }
};

int main(){
    vii matrix = {vi({1, 1, 2, 2}),
                  vi({3, 3, 4, 4}),
                  vi({5, 5, 6, 6}),
                  vi({7, 7, 8, 8})};

    FenwickTree ft(matrix);
    cout << "Matrix is\n";
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j)
            cout << matrix[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
    cout << "Sum of submatrix ((2, 2), (4, 4)) is " << ft.query(2, 2, 4, 4) << '\n';

    cout << "After changing 3 at (2, 2) to 10, matrix is\n";
    matrix[2 - 1][2 - 1] += 7;
    ft.update(2, 2, 7);
    cout << "Matrix is\n";
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j)
            cout << matrix[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
    cout << "Sum of submatrix ((2, 1), (4, 4)) is " << ft.query(2, 1, 4, 4) << '\n';
    cout << "Sum of submatrix ((2, 1), (3, 3)) is " << ft.query(2, 1, 3, 3) << '\n';
    cout << "Sum of submatrix ((2, 1), (2, 2)) is " << ft.query(2, 1, 2, 2) << '\n';
    cout << "Sum of submatrix ((1, 1), (2, 2)) is " << ft.query(1, 1, 2, 2) << '\n';
    cout << "Sum of submatrix ((1, 1), (4, 4)) is " << ft.query(1, 1, 4, 4) << '\n';

    return 0;
}