#include <stdio.h>
#include <omp.h>

static long num_steps = 100000;
double step;

#define NUM_THREADS 2
int main ()
{
  // I am guessing that everything that is outside the pragam struct
  // is store on the heap and is available to all threads in the process
  int i, nthreads;
  double pi, sum[NUM_THREADS];
    
  // Here we are dividing the x value 1.0 
  // by the number steps
  step = 1.0/(double) num_steps;

  omp_set_num_threads(NUM_THREADS);
  #pragma omp parallel
  {
    // We are able to redefine the variables 
    // because they are in a different scope
    int i, ID, nthrds;
    double x;

    ID = omp_get_thread_num();
    nthrds = omp_get_num_threads();

    // We need to be able to know how many threads there are 
    // outside of this parallel block
    if (ID == 0) nthreads = nthrds;

    //Round Robin-Dealing-Cyclical ~
    for (i=ID, sum[ID]=0.0; i<num_steps; i=i+nthrds){
      // This systematically gets the middle of each step
      x = (i+0.5)*step;
      // This uses that x value and finds the y value at that point
      // and adds it to the sum
      sum[ID] += 4.0/(1.0+x*x);
    }

  }

  for (i=0,pi=0.0; i < nthreads; i++) {
    pi += step*sum[i];
  }

  printf("final pi: %f\n", pi);
}


// |  -  |   -   |   -   |   -   |
// 0   .125     0.25
//  0 + 0.5 * .25
