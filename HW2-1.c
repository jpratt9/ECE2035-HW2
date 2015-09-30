/*    When Harry Met Sally

This program finds the earliest year in which Harry and Sally live in the same
city.

9/9/15	               John Pratt   */

#include <stdio.h>
#include <stdlib.h>

/* City IDs used in timelines. */
enum Cities{ London, Boston, Paris, Atlanta, Miami, 
             Tokyo, Metz, Seoul, Toronto, Austin };

int main(int argc, char *argv[]) {
  int	HarryTimeline[10];
  int	SallyTimeline[10];
  int	NumNums, Year=0;
  int  Load_Mem(char *, int *, int *);

  if (argc != 2) {
    printf("usage: ./HW2-1 valuefile\n");
    exit(1);
  }
  NumNums = Load_Mem(argv[1], HarryTimeline, SallyTimeline);
  if (NumNums != 20) {
    printf("valuefiles must contain 20 entries\n");
    exit(1);
  }

   /* Your program goes here */
  /* The basic approach here is to convert the sparse vector representation 
     into a discrete timeline, with an element for each year the two are alive
     Then, we iterate through these discrete timelines and find the first 
     instance in which the two lived in the same city. */
  int i;                // iterator inside HarryTimeline & SallyTimeline
  int jH = HarryTimeline[0]-1986;           // iterator inside HarryPlaces
  int jS = SallyTimeline[0]-1986;           // iterator inside SallyPlaces
  int jH_i, jS_i;                           // copy of jH, jS to restore them to their values before discrete timeline manipulation
  int HarryDiscreteTimeline[30], SallyDiscreteTimeline[30];  // array of cities for each year for Harry, Sally
  int yeardiffH, yeardiffS;    // difference in years for Harry's current city's move-in and the next's

  /* we'll need to put something inside years before Harry/Sally 
     were born to differentiate these from the cities, so I chose -1 */
  for(i = 0; i < 30; i++){
    HarryDiscreteTimeline[i] = -1;
    SallyDiscreteTimeline[i] = -1;
  }
   
   /* we're going to loop through both timelines, 
      but they're the same size so we can do it in one loop */
  for(i = 0; i<sizeof(HarryTimeline)/sizeof(HarryTimeline[0]); i+=2){ 
    if(i <= 6){ //this methodology only works for the first 4 cities, we'll have to modify it slightly for the last one
      yeardiffH = HarryTimeline[i+2] - HarryTimeline[i];
      yeardiffS = SallyTimeline[i+2] - SallyTimeline[i];
    }
    else{
      yeardiffH = 2016 - HarryTimeline[i];
      yeardiffS = 2016 - SallyTimeline[i];
    }
    jH_i = jH;
    // loop to fill in appropriate spots in Harry's discrete timeline
    do{
      HarryDiscreteTimeline[jH] = HarryTimeline[i+1];
      jH++;
    } while(jH < jH_i + yeardiffH);

    jS_i = jS;
    // loop to fill in appropriate spots in Sally's discrete timeline
    do{
      SallyDiscreteTimeline[jS] = SallyTimeline[i+1];
      jS++;
    } while(jS < jS_i + yeardiffS);  
  }
  /* prints out contents of both discrete timelines (for testing purposes)
  for(i = 0; i < 30; i++){
    printf("%d:  %d | %d\n", i+1986, HarryDiscreteTimeline[i], SallyDiscreteTimeline[i]);
  }*/
  for(i = 0; i < 30; i++){
    if(HarryDiscreteTimeline[i] == SallyDiscreteTimeline[i] && HarryDiscreteTimeline[i] != -1){
      Year = 1986 + i;
      break;
    }
  }
  printf("Earliest year in which both lived in the same city: %d\n", Year);
  exit(0);
}

/* This routine loads in up to 20 newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray1[], int IntArray2[]) {
  int	N, Addr, Value, NumVals;
  FILE	*FP;

  FP = fopen(InputFileName, "r");
  if (FP == NULL) {
    printf("%s could not be opened; check the filename\n", InputFileName);
    return 0;
  } else {
    for (N=0; N < 20; N++) {
      NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
      if (NumVals == 2)
	      if (N < 10)
	        IntArray1[N] = Value;
	      else
          IntArray2[N-10] = Value;
      else
        break;
    }
    fclose(FP);
    return N;
  }
}
