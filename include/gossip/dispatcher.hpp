#ifndef GOSSIP_DISPATCHER_HPP
#define GOSSIP_DISPATCHER_HPP 1

#include <thread>
#include <vector>

namespace gossip
{
    class Dispatcher
    {
    public:
        Dispatcher();

        ~Dispatcher() noexcept;

    private:
        std::thread my_sendThread;
    };
}

#endif
