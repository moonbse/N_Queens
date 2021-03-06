#include <bits/stdc++.h>
// #include <iostream>
// #include <ctime>
#include <math.h>
#include "WriteCSV.h"
using namespace std;
#define FO(i, n) for (LI i = 0; i < n; i++)
#define size 80
#define LI long int
#define S S
#define endl "\n"
#define LLI long long int
#define mp make_pair
#define pb push_back
#define fastIO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define mod 1000000007
#define V_int(v) vector <int> v 
map<int,double> mapp;
// Function for printing the 2d matrix.
void print_matrix(LI matrix[][size])
{

    FO(i, size)
    {
        cout << " ";
        FO(j, size)
        {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

// Function to set up the initial matrix and print it..
void configure_Randomly(LI matrix[][size], LI *S)
{
    srand(time(0));
    FO(i, size)
    {
        S[i] = rand() % size;
        matrix[S[i]][i] = 1;
    }
    cout << "Initial state : \n\n";
    print_matrix(matrix);
    cout << endl;
}

// Function for printing the array "state"
void print_S(LI *S)
{
    FO(i, size)
    {
        cout << " " << S[i] << " ";
    }
    cout << endl;
}

// Function for comparing two states ie state_1 and state_2
bool compare_S(LI *S_1, LI *S_2)
{
    FO(i, size)
    {
        if (S_1[i] != S_2[i])
        {
            return false;
        }
    }
    return true;
}

// Function to fill matrix array with "value"
void fill(LI matrix[][size], LI value)
{
    FO(i, size)
    {
        FO(j, size)
        {
            matrix[i][j] = value;
        }
    }
}

// Function to calculate the objective value of the State(queens attacking each other) using the matrix.
LI calc_Objective(LI matrix[][size], LI *S)
{
    // For each queen in a column, we check for other queens falling in the line of our current queen and if found, any, then we increment the variable attacking count.
    // Set the number of queen attacking each other initially to 0.
    LI attacking = 0;

    // index variable to particular row and column
    LI row, column;
    FO(i, size)
    {
        // At each column 'i' from 0 to size-1, the queen is placed at row 'S[i]'.
        row = S[i], column = i - 1;
        while (column >= 0 && matrix[row][column] != 1)
        {
            column--;
        }
        if (column >= 0 && matrix[row][column] == 1)
        {
            attacking++;
        }

        row = S[i], column = i + 1;
        while (column < size && matrix[row][column] != 1)
        {
            column++;
        }
        if (column < size && matrix[row][column] == 1)
        {
            attacking++;
        }

        // right principle diagonal
        row = S[i] - 1, column = i - 1;
        while (column >= 0 && row >= 0 && matrix[row][column] != 1)
        {
            column--;
            row--;
        }
        if (column >= 0 && row >= 0 && matrix[row][column] == 1)
        {
            attacking++;
        }

        //  left principle diagonal
        row = S[i] + 1, column = i + 1;
        while (column < size && row < size && matrix[row][column] != 1)
        {
            column++;
            row++;
        }
        if (column < size && row < size && matrix[row][column] == 1)
        {
            attacking++;
        }

        // Diagonally to the left down
        row = S[i] + 1, column = i - 1;
        while (column >= 0 && row < size && matrix[row][column] != 1)
        {
            column--;
            row++;
        }
        if (column >= 0 && row < size && matrix[row][column] == 1)
        {
            attacking++;
        }

        // Diagonally to the right up
        row = S[i] - 1, column = i + 1;
        while (column < size && row >= 0 && matrix[row][column] != 1)
        {
            column++;
            row--;
        }
        if (column < size && row >= 0 && matrix[row][column] == 1)
        {
            attacking++;
        }
    }
    return (LI)(attacking / 2);
}

// Function to generate a matrix with given state..
void generate_matrix(LI matrix[][size], LI *S)
{
    fill(matrix, 0);
    FO(i, size)
    {
        matrix[S[i]][i] = 1;
    }
}

// Function to copy contents of S_2 to S_1.
void copy_S(LI *S_1, LI *S_2)
{
    FO(i, size)
    {
        S_1[i] = S_2[i];
    }
}

// Function to get the neighbour of the current State having the least objective value amongst all possible state
void get_Neighbour(LI matrix[][size], LI *S)
{
    // Initializing the optimal matrix and optimal State with the current matrix and the current state as the starting point.

    LI opmatrix[size][size];
    LI opS[size];

    copy_S(opS, S);
    generate_matrix(opmatrix, opS);

    // Initializing the optimal objective value
    LI opObjective = calc_Objective(opmatrix, opS);

    // Initializing the temp matrix and temporary state for the purpose of computation.
    LI neighbour_matrix[size][size];
    LI neighbour_S[size];

    copy_S(neighbour_S, S);
    generate_matrix(neighbour_matrix, neighbour_S);

    // Iterating through all possible neighbour_State of the matrix.
    FO(i, size)
    {
        FO(j, size)
        {
            // Condition for skipping the current State

            if (j != S[i])
            {
                // Initializing temp neighbour with the current neighbour.
                neighbour_S[i] = j;
                neighbour_matrix[neighbour_S[i]][i] = 1;
                neighbour_matrix[S[i]][i] = 0;

                // Calc the objective value of the neighbour.
                LI temp = calc_Objective(neighbour_matrix, neighbour_S);

                // Comparing temporary and optimal objective value of the neighbour and updating it when required
                if (temp <= opObjective)
                {
                    opObjective = temp;
                    copy_S(opS, neighbour_S);
                    generate_matrix(opmatrix, opS);
                }

                // Backtracking to the original configuration for the next iteration.
                neighbour_matrix[neighbour_S[i]][i] = 0;
                neighbour_S[i] = S[i];
                neighbour_matrix[S[i]][i] = 1;
            }
        }
    }
    // Copying the optimal matrix and optimal State to the current matrix and,current State as they are not defined as global variable
    copy_S(S, opS);
    fill(matrix, 0);
    generate_matrix(matrix, S);
}

void hill_Climbing(LI matrix[][size], LI *S)
{ 
    clock_t startTime = clock();
    LI neighbour_matrix[size][size] = {};
    LI neighbour_S[size];
    copy_S(neighbour_S, S);
    generate_matrix(neighbour_matrix, neighbour_S);
    int count{0};
    do
    {    
        count++;
        copy_S(S, neighbour_S);
        generate_matrix(matrix, S);
        // Getting the optimal neighbour
        get_Neighbour(neighbour_matrix, neighbour_S);

        if (compare_S(S, neighbour_S))
        {
            // If neighbour and current are equal,then no optimal neighbour exists and therefore print the result and break the loop.
            cout<<"Final state : \n\n";
            print_matrix(matrix);
            clock_t stopTime = clock();
            double Runtime = (float) (stopTime - startTime) / 1000000 ;
            cout << "Runtime: " <<  Runtime << " seconds" << endl;
            int nn = size;
            mapp.clear();
            mapp.insert(make_pair(nn, Runtime));
            WriteCSV("HillClimbingWithRandomRestart.csv", mapp);
            break;
        }
        else if (calc_Objective(matrix, S) == calc_Objective(neighbour_matrix, neighbour_S))
        {
            // If neighbour and current are not equal but their objectives are equal then we are approaching a local optimum, in any case,  apply random restate
            neighbour_S[rand() % size] = rand() % size;
            generate_matrix(neighbour_matrix, neighbour_S);
        }
        cout << "failed iteration count " << count << "\n";
    } while (true);
}

// Driver code
int main()
{
    LI S[size] = {};
    LI matrix[size][size] = {};
    // Setting a starting point by randomly placing the queen
    configure_Randomly(matrix, S);
    // Hill climbing with random restart algorithm
    hill_Climbing(matrix, S);
    return 0;
}
