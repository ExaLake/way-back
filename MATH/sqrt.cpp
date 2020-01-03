#include <iostream.h>
#include <math.h>
#include <classlib\dlistimp.h>

double abs(double x)
{
 return (x>= 0) ? x : -x;
}


double ma_sqrt(double x)
{
 const double TOLERANCE = 1.0e-7;
 double temp = x / 2;
 do {
	  temp = (temp + x /temp) /2;

	  } while (abs(temp*temp - x) > TOLERANCE);

  return temp;
 }

 main()
 {
  double x,y;

  cout << "Entrez un nombre: ";
  cin >> x;

  cout << "Racine de x: " << ma_sqrt(x) << "\n";
  cout << "Log10(x): " << log10(x) << "\n";
  cout << "Log2(x): " << log(x)/log(2);
  }


