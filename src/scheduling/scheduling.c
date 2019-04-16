#include "scheduling.h"

/**
 * Returns the greatest common divisor
 * to calculate the hyperperiod
 */
int gcd(int a, int b) {
  int gcd = 0;
  for (int i = 1; i <= a && i <= b; ++i) {
    if (a % i == 0 && b % i == 0)
      gcd = i;
  }
  return gcd;
}

/**
 * Returns least common multiple
 * using Euclidean algorithm
 */
int lcm(int a, int b) { return (a * b) / gcd(a, b); }

/**
 * Verifies if a task missed its deadline
 */
int missedDeadline(int clock, int period, int remTasks) {
  if (clock > 0 && clock % period == 0 && remTasks > 0) {
    return 1;
  }
  return 0;
}

/**
 * Rate Monotonic Simulation
 */
int RateMonotonic(execution_data *execution) {
  int orderedIndexes[execution->count];
  int remainingExecutions[execution->count];
  int readyQueue[execution->count];
  int failureTime = 0;
  // Set up an array with ordered indexes
  for (int i = 0; i < execution->count; i++) {
    orderedIndexes[i] = i;
  }
  // Order according the period times
  int aux = 0;
  for (int i = 0; i < execution->count; ++i) {
    for (int j = i + 1; j < execution->count; ++j) {
      if (execution->tasks[i].periodTime > execution->tasks[j].periodTime) {
        aux = orderedIndexes[i];
        orderedIndexes[i] = orderedIndexes[j];
        orderedIndexes[j] = aux;
      }
    }
  }
  /**Executing RM Algorithm */
  int clock = 0;
  while (clock <= execution->timeUnits) {
    for (int i = 0; i < execution->count; i++) {
      task_t currentTask = execution->tasks[orderedIndexes[i]];
      if (missedDeadline(clock, currentTask.periodTime,
                         remainingExecutions[orderedIndexes[i]])) {
        failureTime = clock;
      }
      if (clock % currentTask.periodTime == 0) {
        readyQueue[orderedIndexes[i]] = 1;
        remainingExecutions[orderedIndexes[i]] = currentTask.executionTime;
      }
    }
    for (int i = 0; i < execution->count; i++) { 
      if (clock == execution->timeUnits) {
        break;
      }
      if (readyQueue[orderedIndexes[i]] == 1) {
        (execution->RM_Table[orderedIndexes[i] * execution->timeUnits + clock]) = 1;
        remainingExecutions[orderedIndexes[i]]--;
        if (remainingExecutions[orderedIndexes[i]] == 0) {
          readyQueue[orderedIndexes[i]] = 0;
        }
        break;
      }
    }
    /*If a failure has ocurred */
    if (failureTime == clock && clock != 0) {
      clock = execution->timeUnits; 
    }
    clock++;
  }
  return failureTime;
}

/**
 * Earliest Deadline First Simulation
 */
int EarliestDeadlineFirst(execution_data *execution){
  int orderedIndexes[execution->count];
  int remainingExecutions[execution->count];
  int deadlines[execution->count];
  int readyQueue[execution->count];
  for (int i = 0; i < execution->count; i++) {
    deadlines[i] = 0;
    readyQueue[i] = 0;
  }
  int ed = execution->timeUnits;
  int next = 0;
  int failureTime = 0;
  int clock = 0;
  while(clock <= execution->timeUnits){
    for (int i = 0; i < execution->count; i++) {
      task_t currentTask = execution->tasks[i];
      if (missedDeadline(clock, currentTask.periodTime,
                         remainingExecutions[i])) {
        failureTime = clock;
      }
      if(clock % currentTask.periodTime == 0){
        readyQueue[i] = 1;
        remainingExecutions[i] = currentTask.executionTime;
        deadlines[i] += currentTask.periodTime;
        if((deadlines[i] <= ed) && readyQueue[i] == 1){
            ed = deadlines[i];
            next = i;
        }
      }
    }
    if(clock != execution->timeUnits){      
        (execution->EDF_Table[next*execution->timeUnits + clock]) = readyQueue[next];
    }
    remainingExecutions[next]--;
    if(remainingExecutions[next] == 0){
        readyQueue[next] = 0;
        ed = execution->timeUnits;
        for(int i = 0; i < execution->count; i++){    
          if((deadlines[i] <= ed) && readyQueue[i] == 1){
            ed = deadlines[i];
            next = i;
          }
        }    
    }
    if(failureTime == clock && clock != 0){
        clock = execution->timeUnits;
    }
    clock++;
  }
  return failureTime;
}

/**
 * Execute the expected algorithms
 */
void execute_Scheduling(execution_data execution) {
  double Up = 0.0;   // Total processor utilization factor
  int timeUnits = 1; // Required time units to run the algorithms
  for (size_t i = 0; i < execution.count; i++) {
    execution.tasks[i].u = (float)execution.tasks[i].executionTime /
                           (float)execution.tasks[i].periodTime;
    Up += execution.tasks[i].u;
    timeUnits = lcm(timeUnits, execution.tasks[i].periodTime);
  }
  execution.timeUnits = timeUnits;
  int rm_table[execution.count][timeUnits];
  memset(rm_table, 0, sizeof rm_table );
  execution.RM_Table = rm_table;
  int f = RateMonotonic(&execution);
  printf("Failure at: %d", f);
  int edf_table[execution.count][timeUnits];
  memset(edf_table, 0, sizeof edf_table );
  execution.EDF_Table = edf_table;
  int e = EarliestDeadlineFirst(&execution);
  printf("Failure at: %d", e);

}
