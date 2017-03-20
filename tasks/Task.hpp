#ifndef TEMPERATURE_TASK_TASK_HPP
#define TEMPERATURE_TASK_TASK_HPP

#include "temperature/TaskBase.hpp"
#include <temperature/Temperature.hpp>
#include <rtt/extras/FileDescriptorActivity.hpp>
#include <base/Temperature.hpp>

namespace temperature
{
    class Task : public TaskBase
    {
	friend class TaskBase;
    protected:
        temperature::Temperature *driver;
        
        std::vector<std::string> sensor_names;
        temperature::samples::Temperature temperatures;
    public:
        Task(std::string const& name = "temperature::Task");
        Task(std::string const& name, RTT::ExecutionEngine* engine);
	    ~Task();
        bool configureHook();
        bool startHook();
        void updateHook();
        void errorHook();
        void stopHook();
        void cleanupHook();
    };
}

#endif

