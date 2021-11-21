# Okada_small_alpha_simulation
IF LOOKING AT CODE PLEASE READ README.

Note this code will create folder in download. 

Hello, 
This code in C++ is a simulation of a population using a levy-stable distrubution. It runs using command lines in terminal so if you want to compile code use code on line 9. The non commandline will also create a folder but must run in Xcode or something similar. 

g++ file_path -lgsl -o output //use for commandline

Then use 
./output alpha, number of trials, population size

This will then print the fixation probailty and a folder will be created in your downloads containing a file with the results. 

The results file will be a CSV with output+ r where r is the random "seed". Using the same same r and going back in code will yield same results. 


Also this should only work for mac and linux and please reach out if you have any questions! 

