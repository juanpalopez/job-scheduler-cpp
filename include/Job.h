//
// Created by Juan Lopez Guzman on 14/11/2023.
//

#ifndef JOBSCHEDULER_JOB_H
#define JOBSCHEDULER_JOB_H

#include <string>
#include <chrono>
#include <utility>
#include <iostream>

namespace job_scheduler {
    using namespace std::chrono;

    enum JobStatus {
        PENDING,
        RUNNING,
        COMPLETED,
        FAILED
    };

//    using JobCallback = std::function<void(const Job&)>;

    template<typename T>
    class Job {
    public:
        using JobCallback = std::function<void(const Job&)>;
        Job(unsigned int id, std::string name, JobCallback callback, T jobData, time_point<system_clock>  scheduleTs);
        Job(unsigned int id, std::string name, JobCallback callback, T jobData);

        JobStatus getStatus() const;
        time_point<system_clock> getSchedule() const;
        void setSchedule(time_point<system_clock> schedule);

        void run();

        T data;
    private:
        unsigned int id_{};
        std::string name_{};
        JobCallback callback_{};
        time_point<system_clock> scheduleTs_{};
        JobStatus status_{JobStatus::PENDING};
    };

    template<typename T>
    JobStatus Job<T>::getStatus() const{
        return status_;
    }

    template<typename T>
    void Job<T>::setSchedule(time_point<system_clock> scheduleTs) {
        scheduleTs_ = scheduleTs;
    }

    template<typename T>
    time_point<system_clock> Job<T>::getSchedule() const {
        return scheduleTs_;
    }


    template<typename T>
    Job<T>::Job(unsigned int id,
                std::string name,
                JobCallback callback,
                T jobData,
                time_point<system_clock> scheduleTs):
            id_(id),
            name_(std::move(name)),
            callback_(std::move(callback)),
            data(jobData),
            scheduleTs_(scheduleTs){};


    template<typename T>
    Job<T>::Job(unsigned int id,
                std::string name,
                JobCallback callback,
                T jobData): Job(id,
                                std::move(name),
                                std::move(callback),
                                jobData,
                                system_clock::now()
                                ){};


    template<typename T>
    void Job<T>::run() {
        std::printf("Trying to run Job - id: %i - name: %s\n", id_, name_.c_str());
        try{
            status_ = JobStatus::RUNNING;
            callback_(*this);
            status_ = JobStatus::COMPLETED;
        } catch (std::exception& err) {
            std::cout << "A std::exception occurred: " << err.what() << std::endl;
            status_ = JobStatus::FAILED;
        }

    }


}



#endif //JOBSCHEDULER_JOB_H
