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
double N_fix,i,M_f;
array<double,5> selection_coefficients=  {0,.01, .02, 0.04, 0.08};
double M,W,p_i,p_prime,s,K;
double a,b;
double PI= 3.1415;
int sum_extinct_gens, generation;


ofstream fout;
ostringstream dir;


int main(int argc, char* argv[0])
{
    if(argc != 4) {cout << "Wrong number of arguments.  Arguments are alpha, number of trials, and population size" << endl;
        cout<<argv<<endl;
        return 0;}

    dir << "/Users/" << getenv("USER") << "/Downloads/selection";
    const char* directory= dir.str().c_str();
mkdir(directory, 0777);
chdir(directory);
    const double alpha = atof(argv[1]);
    const double num_trials = atof(argv[2]);
    const double N= atof(argv[3]);
    
    
    //Not my code
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
    fout<< "alpha" << "," << "average extinction"<< ","<< "fixation_rate"<<","<< "fixation_rate_error"<<endl;

    
    for(i; i< selection_coefficients.size(); i++){
        N_fix=0;
        sum_extinct_gens= 0;

    for(int trial =0; trial < num_trials; trial++)
    {
         M_f= N*.01;
        K= M_f;
        generation=0;
        s= selection_coefficients[i];
        while(M_f>0 && M_f<N){
            generation=generation+1;
            if (alpha==-1){
           // wright fischer
            M=M_f;
            W=N-M_f;
            }
            if( alpha==2){
                //does not work currently but juse use WF instead
                M= gsl_ran_gaussian(r, pow(2, .5)* M_f);
                W= gsl_ran_gaussian(r, (N-M_f)*pow(2,.5));
            }
            
            
            //alpha <1
            if(alpha<1&& alpha>0){
                
            b= pow(PI*M_f/(2*tgamma(alpha)*sin(PI*alpha/2)),1/alpha);
            M=(b*gsl_ran_levy_skew(r,1,alpha,1));
            b= pow(PI*(N-M_f)/(2*tgamma(alpha)*sin(PI*alpha/2)),1/alpha);
            W=(b*gsl_ran_levy_skew(r,1,alpha,1));
                }
            
            if(alpha>1 && alpha<2){
                a =  M_f*alpha/(alpha-1);
                b= pow(PI*M_f/(2*tgamma(alpha)*sin(PI*alpha/2)),1/alpha);
                M=(a+b*gsl_ran_levy_skew(r,1,alpha,1));
                a =  (N-M_f)*alpha/(alpha-1);
                b= pow(PI*(N-M_f)/(2*tgamma(alpha)*sin(PI*alpha/2)),1/alpha);
                W=(a+b*gsl_ran_levy_skew(r,1,alpha,1));
            }
            
            p_i =(M)/(M+W);
            p_prime = (p_i*(1+s))/(p_i*(1+s)+(1-p_i));
         M_f= gsl_ran_binomial(r, p_prime, N); //I think this is the source of the issue for alpha<2
            if(M_f==0){
                sum_extinct_gens+= generation; //all the generation code just gets extinction time
            }
          
            if (M_f >= N){ N_fix = N_fix+1;}
    }

    }
        double fix  = N_fix/(num_trials*K);
        cout<<scientific;
        cout<<N_fix/(num_trials*K)<<endl;
        cout<<sum_extinct_gens/(num_trials-N_fix)<<endl;
        fout <<scientific;
        fout << alpha<< "," << sum_extinct_gens/(num_trials-N_fix) << "," << fix<< "," << pow((fix*(1 -fix))/num_trials, .5)<< endl;
    }
    if(!fout){cout<<"cant"<<endl;}
    fout.close();
    return 0;
}

