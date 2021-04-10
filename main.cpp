//
//  main.cpp
//  Pop_sim
//
//  Created by Zach Karol on 3/31/21.
//

#include <stdio.h>
#include <gsl/gsl_randist.h>
#include <iostream>
#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <array>
#include <sys/time.h>
#include<iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

ostringstream oss;
float s;
int N_fix,i,M_f;
array<double,5> selection_coefficients=  {0,.01, .02, 0.04, 0.08};
double M,W,p_i,p_prime;


ofstream fout;
ostringstream dir;


int main(int argc, char* argv[0])
{
    if(argc != 4) {cout << "Wrong number of arguments.  Arguments are alpha, number of trials, and population size" << endl;
        cout<<argv<<endl;
        return 0;}

    dir << "/Users/" << getenv("USER") << "/Downloads/outputs";
    const char* directory= dir.str().c_str();
mkdir(directory, 0777);
chdir(directory);
    const double alpha = atof(argv[1]);
    const float num_trials = atof(argv[2]);
    const float N= atof(argv[3]);
    
    
    //low key not my code but like im citing it so thats fine right?
    const gsl_rng_type * T;
     gsl_rng *r;
     gsl_rng_env_setup();
     struct timeval tv; // Seed generation based on time
     gettimeofday(&tv,0);
     unsigned long mySeed = tv.tv_sec + tv.tv_usec;
     T = gsl_rng_default;
     r = gsl_rng_alloc (T);
    gsl_rng_set(r, mySeed);
    
    
    oss << "output" <<r << ".csv";
    fout.open(oss.str());
    fout<< "selection coeff"<< ","<< "fixation_rate"<<","<< "fixation_rate_error"<<","<<alpha<<endl;

    

    for(i; i< selection_coefficients.size(); i++){
        N_fix=0;
    for(int trial =0; trial < num_trials; trial++)
    {
         M_f= 1;
        M=1;
        while(0<M_f && M_f<N){
            s= selection_coefficients[i];
            M= abs(gsl_ran_levy(r,pow(M_f,(1.0/alpha)) , alpha));
            W= abs(gsl_ran_levy(r,pow(N-M_f,(1.0/alpha)), alpha));
            p_i =(M)/(M+W);
            p_prime = (p_i*(1+s))/((p_i*s)+1);
            M_f = gsl_ran_binomial(r, p_prime, N);
            if (M_f == N){ N_fix = N_fix+1;}
    }
    }
        cout<<N_fix/num_trials<<endl;
        if(!fout){cout<<"cant";}
        fout <<scientific;
        fout << s << "," << N_fix/num_trials << "," << pow(((N_fix/num_trials)*(1 - (N_fix/num_trials)))/num_trials, .5)<< endl;
    }
    fout.close();
    return 0;
}
