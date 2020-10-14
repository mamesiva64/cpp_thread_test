//  https://paiza.io/projects/ntEA3iObeNcCsGZA7N3Zyw?language=cpp

#include <iostream>
#include <list>
#include <vector>
#include <thread>
#include <memory>


class WorkerBase {
public:
    virtual bool init() {
        std::cout << "init" << std::endl;
        return true;
    }
    virtual bool update() {
        std::cout << "update" << std::endl;
        return false;
    }
    virtual bool release() {
        std::cout << "release" << std::endl;
        return true;
    }
    void thread_function() {
        init();
        while(true) {
            if(!update()) {
                break;
            }
        }
        release();
    }
};

int main(void){
    
    std::vector<std::shared_ptr<WorkerBase>> workers;
    workers.push_back(std::make_shared<WorkerBase>());
    workers.push_back(std::make_shared<WorkerBase>());
    workers.push_back(std::make_shared<WorkerBase>());

    for (auto &worker : workers) {
        worker->init();
    }

    for (auto &worker : workers) {
        worker->update();
    }

    for (auto &worker : workers) {
        worker->release();
    }

    //  thread
    std::cout << "----------- thread --------------" << std::endl;
    std::vector<std::thread> worker_threads;
    for (auto &worker : workers) {
        worker_threads.emplace_back(([&worker]() { worker->thread_function(); }));
//      worker_threads.emplace_back( &WokerBase::thread_function, worker.get());
    }
    for (auto &thread : worker_threads) {
        thread.join();
    }
    std::cout << "----------- thread.end --------------" << std::endl;
}
