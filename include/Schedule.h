//
// Created by Juan Lopez Guzman on 16/11/2023.
//

#ifndef JOBSCHEDULER_SCHEDULE_H
#define JOBSCHEDULER_SCHEDULE_H

#include <queue>
#include "Job.h"

namespace job_scheduler {
    template<typename T>
    struct Comparator{
        bool operator()(const Job<T>&jobA, const Job<T>&jobB){
            return jobA.getSchedule() > jobB.getSchedule();
        }
    };

    template<typename T>
    class Schedule {
    public:
        Schedule();

        void scheduleIn(Job<T>& job, uint64_t inSeconds);
//        void scheduleAt(Job<T>& job, uint64_t scheduleTs);

        void runPending();
    private:
       std::priority_queue<Job<T>, std::vector<Job<T>>, Comparator<T>> jobs_;
        void addJob_(Job<T>& job);
    };

    template<typename T>
    void Schedule<T>::scheduleIn(Job<T> &job, uint64_t  inSeconds) {
        auto now = system_clock::now();
        auto scheduleTs = now + std::chrono::seconds(inSeconds);
        job.setSchedule(scheduleTs);
        addJob_(job);
    }

    template<typename T>
    void Schedule<T>::runPending() {
        std::cout << "Running Jobs...\n" ;
        while (!jobs_.empty()){
            auto now = system_clock::now();
            auto curJob = jobs_.top();
            if (curJob.getSchedule() <= now && curJob.getStatus() == JobStatus::PENDING ) {
                curJob.run();
                jobs_.pop();
            }
        }
    }

    template<typename T>
    void Schedule<T>::addJob_(Job<T>& job) {
        jobs_.push(job);
    }

    template<typename T>
    Schedule<T>::Schedule() = default;


}

#endif //JOBSCHEDULER_SCHEDULE_H
