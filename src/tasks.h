typedef struct task_t
{
   int executionTime; // millisecs of execution
   int periodTime; // period value
   double u; // utilization factor
} task_t;

typedef struct execution_data
{
    int RM;
    int RM_Fail;
    int RM_Fail_Task;
    int EDF;
    int EDF_Fail;
    int EDF_Fail_Task;
    int LLF;
    int LLF_Fail;
    int LLF_Fail_Task;
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