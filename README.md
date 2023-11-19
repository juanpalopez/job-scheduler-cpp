# Job Scheduler in CPP

This is an exploratory project for learning more about
c++ std library, templates and concurrency.

# Example usage

```c++
#include <iostream>
#include "Job.h"
#include "Schedule.h"

using namespace job_scheduler;
int main() {
    std::cout << "Welcome to Job Scheduler" << "\n";

    auto myFunction = [](Job<int> job)  {
        auto jobUnixTime = duration_cast<seconds>(job.getSchedule().time_since_epoch()).count();
        std::cout << "Job function: " << jobUnixTime  << "\n";
    };
    Job<int> job1{1, "MyFirstJob", myFunction, 10 };
    Job<int> job2{2, "AnotherJob",myFunction, 20};
    Job<int> job3{3, "ThirdJob",myFunction, 50};

    Schedule<int> newSchedule;
    newSchedule.scheduleIn(job1, 5); # in seconds
    newSchedule.scheduleIn(job2,2);
    newSchedule.scheduleIn(job3,10);


    newSchedule.runPending();


    return EXIT_SUCCESS;
}
```
