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
double s;
double N_fix,M_f;
int i;
array<double,5> selection_coefficients=  {0,.01, .02, 0.04, 0.08};
double M,W,p_i,p_prime;


ofstream fout;
ostringstream dir;


int main()
{
    dir << "/Users/" << getenv("USER") << "/Downloads/outputs";
    const char* directory= dir.str().c_str();
mkdir(directory, 0777);
chdir(directory);
    double alpha = 1.2;
    double num_trials = 1e6;
    double N= 1e6;
    
    
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
//    fout.open(oss.str());
    fout<< "selection coeff"<< ","<< "fixation_rate"<<","<< "fixation_rate_error"<<","<<alpha<<endl;

    

    for(i; i< 1; i++){
        N_fix=0;
    for(int trial =0; trial < num_trials; trial++)
    {
         M_f=1;
        while(0<M_f && M_f<N){
            s= selection_coefficients[i];
            M= abs(gsl_ran_levy(r,pow(M_f,(1.0/alpha)) , alpha));
            W= abs(gsl_ran_levy(r,pow(N-M_f,(1.0/alpha)), alpha));
            p_i =(M)/(M+W);
            p_prime = (p_i*(1+s))/((p_i*s)+1);
            M_f = gsl_ran_binomial(r, p_prime, N);
            if (M_f >= N){ N_fix = N_fix+1;}
    }
    }
        cout<<scientific;
        cout<<N_fix/num_trials<<endl;
        if(!fout){cout<<"cant"<<endl;}
        fout <<scientific;
        fout << s << "," << N_fix/num_trials << "," << pow(((N_fix/num_trials)*(1 - (N_fix/num_trials)))/num_trials, .5)<< endl;
    }
    fout.close();
    return 0;
}

