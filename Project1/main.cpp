#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#include <iomanip>
using std::setw;
#include "time.h"

ofstream ofile;

double func(double i, double h) //function f(x)
{
    double fx = 100*exp(-10*(i+1)*h);   //x=(i+1)*h in which h is the steplength
    return fx;
}
// We have named the approximation u (u[i]) and the closed-form solution v (v[i])
int main()
{

    int n;
    cout << "Please enter value of n:\n>";
    cin >> n;
    cout << "n = " << n << endl;
    double h = 1.0/(n+1); //step length

    //We define vector a, b and c which make up matrix A:
    double b[ n ];
    for (int i=0 ; i<n ; i++)
    {
        b[i] = 2;
    }

    double ac = -1.0;
    //since the entrances of a and c (apart from the 1st in a and n'th in c) = -1,
    //we do not define a and c as vectors but as numbers with the value -1

    double u[ n ];
    //We define f as h^2*f(i)
    double f[n];
    for (int i=0 ; i<n ; i++)
    {
        f[i] = h*h*func(i,h);
    }

clock_t start , finish;
start = clock();

    // Forward substitution

    double abtemp[n];
    double btemp = b[0];

    for (int i=1 ; i<n ; i++)
    {
        abtemp[i] = ac/btemp;
        btemp = b[i] - ac*abtemp[i];
        f[i] = f[i] - f[i-1]*abtemp[i];
        b[i]=btemp;
    }

    // Back substitution

    u[n-1] = f[n-1]/b[n-1];

    for(int i=n-2 ; i>= 0; i--)
    {
        u[i] = (f[i]-ac*u[i+1])/b[i];
    }

finish = clock();

    //computing the closed-form solution
    double v[n];
    for (int i=0 ; i<n ; i++)
    {
        v[i] = 1-(1-exp(-10))*(1+i)*h-exp(-10*(1+i)*h);
    }

    //Computing the relative error
    double relativererror[n];
    double errortemp;

    for(int i=0 ; i< n; i++)
    {
        errortemp = abs((u[i]-v[i])/v[i]);
        relativererror[i] = log10 (errortemp);
    }

    //Printing time
    cout << "time=" << ((finish - start)/CLOCKS_PER_SEC) << endl;

    //Printing results
    cout << "i" << setw(20) << "x" << setw(20) << "u" << setw(25) << "closed-form solution" << setw(25) << "error" << endl;

    for (int i=0; i<n ; i++)
    {
         cout << i << setw(20) << (i+1)*h << setw(20) << u[i] << setw(20) << v[i] << setw(20) << relativererror[i] << endl;
    }


/*
    //Printing results to file
    ofstream myfile ("Results.txt"); //Creates output file
      if (myfile.is_open())           //checkes whether the output file is open.
                                      //if open, the following things are put in the output file
      {
          myfile << "n = " << n << endl;
          myfile << "i" << setw( 15 ) << "x" << setw( 15 )
                 << "u" << setw( 15 ) << "rel error" <<  endl;
          for ( int j = 0; j < n; j++ )
          {
               myfile << j << setw( 15 ) << (j+1)*h << setw( 15 )
                      << u[j] << setw( 15 ) << relativererror[j] << endl;
          }
      myfile.close();
      }
      else cout << "Unable to open file";
*/
    return 0;
}

