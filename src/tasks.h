typedef struct task_t
{
   int executionTime; // millisecs of execution
   int periodTime; // period value
   double u; // utilization factor
} task_t;

typedef struct execution_data
{
    int RM;
    int EDF;
    int LLF;
    int Slides;
    int count;
    double Up;
    double Un;
    int timeUnits;
    int *RM_Table;
    int *EDF_Table;
    int *LLF_Table;
    task_t *tasks;

} execution_data;

struct execution_data CurrentExecution;