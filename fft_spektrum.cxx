#include "fftw3.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>
//-------------------------------
using namespace std;
//-------------------------------
void writeData(const fftw_complex* const f, const int N, const double L,const char* const fname);

//-------------------------------

int main(int argc, char** argv){

	if(argc != 3){ // != bedeutet ungleich
		cout << "Usage: " << argv[0] << " input_file \t output_file" << endl;
		exit(1);
	}

	char *in_file  = argv[1]; //gibt an, welche Argumente noch mit dem Hauptprogram mitgezaehlt wird
	char *out_file = argv[2];

	const int N = 16384;
	double L;
	double temp;
	// Allocate memory
	fftw_complex* f = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (N/2+1)); // malloc und free = new und delete
	double* inR  = (double*) malloc(sizeof(double)*N);

  // Create plan
	fftw_plan FW  = fftw_plan_dft_r2c_1d(N, inR, f, FFTW_ESTIMATE);
	
	
	// Call function which reads the data from
	// the input file into the array inR
	//const string filename = "i.txt";
	ifstream in(in_file);
	// ofstream out("text2.txt");
	for(int i=0; i<N;i++){
	  in>>temp;
	  in>>inR[i];
	 
	  cout << temp<<endl;
	}
	in.close();
	//out.close();
	L = temp;
	
	


  // Calculate FFT
  fftw_execute(FW);

  // write output file
  writeData(f, N,  L, out_file);

  // Clean up
	fftw_destroy_plan(FW); 
  fftw_free(f);
  free(inR);

	return 0;
}
//-------------------------------
void writeData(const fftw_complex* const f, const int N, const double L,const char* const fname){
	ofstream out(fname);
	const double dk = 2*M_PI/L;
	double pk;

	for(int i=0; i<=N/2; i++){
		pk = sqrt(f[i][0]*f[i][0] + f[i][1]*f[i][1])/N;
		out << i*dk << "\t" << pk << "\t" << f[i][0] << "\t" << f[i][1] << endl;
	}

	out.close();
}
//-------------------------------
