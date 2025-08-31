#pragma once
#include <mutex>
#include <thread>
#include <iostream>


template <class parameters, class variables>
class time_flow_program
{
protected:
    bool do_cycle = false; unsigned cycle_counter = 0;

public:
    std::ostream& logger_stream = std::cout;

    parameters p;
    variables  v;

    std::mutex variables_mutex; 


    //--- Используется для первичных задач, формирование исходного сигнала и т.п.

    //virtual void init(const parameters params) { p = params;};
    virtual void init() {};
    virtual void prepare() {};
    //--- Используется для исполнения параллельных задач (убрать private если нужно)
//private:
    std::thread loop_thread;
    virtual void cycle_function() = 0;
    virtual void loop_function()
    {
        try {
            while (do_cycle)
            {
                cycle_function();
                cycle_counter++;
            }
        } 
        catch (const std::exception& e) {
            logger_stream << "Error in time_flow_program: " << e.what() << std::endl;
        }
        
    };
    void start_loop()
    {
        cycle_counter = 0;
        do_cycle = true;
        v = variables();
        init();
        loop_thread = std::thread([this]{loop_function();});
    };

    void continue_loop()
    {
        do_cycle = true;
        loop_thread = std::thread([this]{loop_function();});
    }
    
    void stop_loop() {
      do_cycle = false;
      if (loop_thread.joinable())
      {
        loop_thread.join();
      }
      else {
        loop_thread.detach();
      }

    };

    unsigned get_cycle_counter() {return cycle_counter;};
    //---
public:
    bool running() {return do_cycle;}
    void clear() {v = {};};


    // time_flow_program(const time_flow_program&) = delete;
    // time_flow_program& operator=(const time_flow_program&) = delete;
    ~time_flow_program() {if (do_cycle) stop_loop();}
};


