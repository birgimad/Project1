#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#include <iomanip>
#include "time.h"
#include "armadillo"
using namespace arma;

using std::setw;

ofstream ofile;


double func(double i, double h) //function f(x)
{
    double fx = 100*exp(-10*(i+1)*h);   //x=(i+1)*h in which h is the steplength
    return fx;
}


int main()
{

    int n;


    cout << "Please enter value of n:\n>";
    cin >> n;
    cout << "n = " << n << endl;
    double h = 1.0/(n+1); //step length


    //We define f as h^2*f(i)
    vec f(n);
    for (int i=0 ; i<n ; i++)
    {
        f(i) = h*h*func(i,h);
    }


    mat A(n,n);
    mat L, U, P;
    A.zeros(); // a zero matrix
    A.eye();   // an identity matrix
    A=A*2;     // matrix with all diagonal elements equals 2



    for(int i=0; i<n-1; i++)
    {
        A(i,i+1) = -1;
    }
    for(int i=1; i<n; i++)
    {
        A(i,i-1) = -1;
    }
    clock_t start , finish;// declare start and final time
    start = clock();


    lu(L, U, A); // performs LU decomposition

    vec y = solve(L,f);
    vec V = solve(U,y);

    finish =clock();
    double CLK = ((finish-start)/((double) CLOCKS_PER_SEC));

    cout << "Elapsed time = " << CLK << endl;
    cout << "i" << setw(15) << "x" << setw(15) << "V" <<endl;
    for(int i=0; i<n; i++)
    {
        cout << i << setw(15)<< (i+1)*h<< setw(15)<<V(i)<<endl;
    }
    //cout << start<< setw(15) << finish << setw(15) << CLK << endl;


      //Printing results to file
        ofstream myfile ("Resultsarma1000.txt"); //Creates output file
          if (myfile.is_open())           //checkes whether the output file is open.
                                          //if open, the following things are put in the output file
          {
              myfile << "n = " << n << endl;
               myfile << "time elapsed = " << CLK << endl;
              myfile << "i" << setw( 15 ) << "x" << setw( 15 )
                     << "V" <<  endl;
              for ( int j = 0; j < n; j++ )
              {
                   myfile << j << setw( 15 ) << (j+1)*h << setw( 15 )
                          << V(j) << endl;
              }
          myfile.close();
          }
          else cout << "Unable to open file";


    return 0;
}
