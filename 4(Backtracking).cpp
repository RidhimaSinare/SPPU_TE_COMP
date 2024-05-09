#include<iostream>
#include<vector>
using namespace std;

bool isSafe(int row, int col, int **board, int n)
{
    for(int i=0;i<n;i++)
    {
        if(board[row][i]==1 || board[i][col]==1)return false;
    }

    int i=row, j=col;
    while(i>=0 && j>=0)
    {
        if(board[i][j]==1) return false;
        i--;
        j--;
    }

    i=row; j=col;
    while(i<n && j>=0)
    {
        if(board[i][j]==1) return false;
        i++;
        j--;
    }

    i=row; j=col;
    while(i>=0 && j<n)
    {
        if(board[i][j]==1) return false;
        i--;
        j++;
    }
    
    i=row; j=col;
    while(i<n && j<n)
    {
        if(board[i][j]==1) return false;
        i++;
        j++;
    }

    return true;
}// end of bool safe

bool solveNQueens(int **board, int col, int n)
{
    if(col>=n) return true;

    for(int i=0;i<n;i++)
    {
        if(isSafe(i, col, board, n))
        {
            board[i][col] = 1;

            if(solveNQueens(board, col+1, n))
            {
                return true;
            }

            board[i][col]=0;
        }//end if if
    }// end if for

    return false;
}//end of solveNQueens

void printSolution(int **board, int n)
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}//end if print

int main()
{
    int n;
    cout << "Enter the board size (n): ";
    cin >> n;

    int **board = new int* [n];
    for(int i=0;i<n;i++)
    {
        board[i] = new int[n];
    }

    for(int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            board[i][j] = 0;
        }
    }

    if(solveNQueens(board,0,n))
    {
        cout<<"Solution exists: "<<endl;
        printSolution(board, n);
    }
    else
    {
        cout<<"No solution"<<endl;
    }

    return 0;
}
