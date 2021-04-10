# Okada_small_alpha_simulation
IF LOOKING AT CODE PLEASE READ README.

Note this code will create folder in download. 

Hello, 
This code in C++ is a simulation of a population using a levy-stable distrubution. It runs using command lines in terminal so if you want to compile code use

g++ file_path -lgsl -o output

Then use 
./output alpha(should be less than 1 so its fast), number of trials, population size

This will then print the fixation probailty and a folder will be created in your downloads containing a file with the results. 

The results file will be a CSV with output+ r where r is the random "seed". Using the same same r and going back in code will yield same results. 

Lastly there seems to maybe be an issue with the output and I think it might be the binomial function and the low probabilty as I tried to simulate with a normal distrubution and alpha=2 but the results were still non-sensical especially for selection coeffcient of 0. 

This read_me might be a little bit of a mess but I will clean this up once I find the bug and finalize code. Also this should only work for mac and linux and please reach out if you have any questions! 

