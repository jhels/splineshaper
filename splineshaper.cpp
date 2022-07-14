#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/Polynomials>


using namespace Eigen;
using namespace std;

int main()
{
	int n = 5;	// Number of polynomials
	int d = 10; // Maximum degree of polynomials
	

	double HI = 10.0;	 // Maximum coefficient of polynomials
	double LO = -10.0;	 // Minimum coefficient of polynomials
	double range = HI - LO;

	srand(6);			 // Set random seed here

	MatrixXd polys = MatrixXd::Random(n, d);						// Populate polynomial
	polys = (polys + MatrixXd::Constant(n, d, 1.)) * range / 2.;	// coefficient matrix
	polys = (polys + MatrixXd::Constant(n, d, LO));					// with random numbers

	cout << "Polynomial Coefficients:\n" << polys << "\n" << endl;

	VectorXd joins = VectorXd::Random(n - 1);			// Create vector of intervals [j0,...,j{n-1}]
	sort(joins.data(), joins.data() + joins.size());	// where polynomials are spliced

	cout << "Joins:\n" << joins << "\n Output: \n \n" << endl;

	for (int i = 0; i < n - 1; i++) {
		polys(i + 1, 0) += poly_eval(polys(i, all), joins(i)) - poly_eval(polys(i + 1, all), joins(i)); // Adjust f{i+1} so fi(ji) = f{i+1}(ji)
	}
	
	float sample = 0.3; // Input sample in range [-1,1]

	int segment;					// Determines which segment out of
	for (int i = 0; i < n; i++) {	// {[-1,j0], [j0,j1], ..., [j(n-1),1]}
		if (sample < joins(i)) {	// sample lies in.
			segment = i;			// (0-indexed)
			break;					//
		}
	}
	float output = poly_eval(polys(segment, all), sample);

	cout << sample << "\t" << output << endl;
	
}

// This works now - just have to normalise curve so output is between -1 and 1. Then hook it up to JUCE.