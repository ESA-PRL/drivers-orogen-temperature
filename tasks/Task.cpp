#include "Task.hpp"

using namespace temperature;

Task::Task(std::string const& name)
    : TaskBase(name)
{
    driver = NULL;
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine)
    : TaskBase(name, engine)
{
    driver = NULL;
}

Task::~Task()
{

}

bool Task::configureHook()
{
    if(!TaskBase::configureHook())
    {
        return false;
    }
    
    // Read in the sensor names
    sensor_names = _sensor_names.get();
    
    if(sensor_names.size() == 0)
    {
        fprintf(stderr, "Temperature: No sensors selected, enter sensor names in the configuration\n");
        return false;
    }
    
    // Instantiate the driver
    driver = new temperature::Temperature(sensor_names.size());
    
    /*for(unsigned int i = 0; i < sensor_names.size(); i++)
    {
        temperatures.push_back(base::Temperature());
    }*/
    
    if(!driver->openSerial(_port.value(), _baudrate.value()))
    {
        fprintf(stderr, "Temperature: Cannot initialize driver\n");
        return false;
    }
    
    return true;
}

bool Task::startHook()
{
    if(!TaskBase::startHook())
    {
        return false;
    }
    
    // Mandatory for a FD driven component
    RTT::extras::FileDescriptorActivity* activity = getActivity<RTT::extras::FileDescriptorActivity>();
    if(activity)
    {
        activity->watch(driver->getFileDescriptor());
        // Set the timeout to 2 seconds
        activity->setTimeout(2000);
    }
    else
    {
        fprintf(stderr, "Temperature: File descriptor error\n");
        return false;
    }
    
    return true;
}

void Task::updateHook()
{
    TaskBase::updateHook();
    
    RTT::extras::FileDescriptorActivity* activity = getActivity<RTT::extras::FileDescriptorActivity>();
    if(activity)
    {
        if(activity->hasError())
        {
            fprintf(stderr, "Temperature: IO error\n");
        }
        
        if(activity->hasTimeout())
        {
            fprintf(stderr, "Temperature: Timeout\n");
        }
    }
    else
    {
        fprintf(stderr, "Temperature: No RTT activity\n");
        return;
    }
    
    float temp[sensor_names.size()];
    if(!driver->update(temp))
    {
        fprintf(stderr, "Temperature: Error reading device\n");
    }
    else
    {
        temperature::samples::Temperature tempSensor;
        tempSensor.time = base::Time::now();
        tempSensor.resize(sensor_names.size());
    
        // Update all the temperature values
        for(unsigned int i = 0; i < sensor_names.size(); i++)
        {
            tempSensor.temp[i] = base::Temperature::fromCelsius(temp[i]);
        }
        
        // Write the array to output
        _temperature_samples.write(tempSensor);
    }
}

void Task::errorHook()
{
    TaskBase::errorHook();
}

void Task::stopHook()
{
    TaskBase::stopHook();
    
    //driver->close();
}

void Task::cleanupHook()
{
    TaskBase::cleanupHook();

    if(driver != NULL)
    {
        driver->close();
        delete driver;
        driver = NULL;
    }
}

