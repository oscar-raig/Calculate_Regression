[![Build Status](https://travis-ci.org/oscar-raig/Calculate_Regression.svg?branch=master)](https://travis-ci.org/oscar-raig/Calculate_Regression)

Calculate_Regression
====================


1. STEP 1
Calculate regression coefficient.
The regression coefficient indicates how well linear regression fits to the original data.

2. STEP 2
The program removes some data numbers if the coefficient regression get worst, with these numbers.

Then, you get "clean data", without points that generate the bad coefficient.

Example:

Pairs (1,1) (2,2) ( 3,3 ) (4,7) (5,5) (6,6)

Should delete (4,7)


Design Patterns:
	
	- Command , undo Command

SOLID principles:
	- Dependency Injection

Continous Integration:
	- Travis, Coveralls

Testing:
	- Valgrind: memory leaks
	- Unit testing with google test

Technology:
	- Docker, c++
