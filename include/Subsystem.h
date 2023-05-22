#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

#include "AbstractState.h"
#include "UDPInterface.h"
#include "TCPInterface.h"
#include "UARTInterface.h"
#include "Commanding.h"
#include "Parameters.h"
// #include <boost/asio.hpp>
#include <vector>
#include <map>
#include <queue>

class TransportLayerMachine {
    public:
        boost::asio::ip::udp::socket local_udp_sock;
        boost::asio::ip::tcp::socket local_tcp_sock;

        boost::asio::ip::udp::endpoint remote_udp_endpoint;
        boost::asio::ip::tcp::endpoint remote_tcp_endpoint;

        std::vector<char> downlink_buff;
        std::vector<char> uplink_buff;
        std::vector<char> command_pipe;
        std::queue<char> ground_pipe;

        CommandDeck commands;

        STATE_ORDER active_state;
        SUBSYSTEM_ORDER active_subsys;

    public:
        TransportLayerMachine(boost::asio::io_context& context);
        TransportLayerMachine(
            std::string local_ip,
            std::string remote_tcp_ip,
            std::string remote_udp_ip,
            unsigned short local_port,
            unsigned short remote_tcp_port,
            unsigned short remote_udp_port,
            boost::asio::io_context& context
        );
        TransportLayerMachine(
            boost::asio::ip::udp::endpoint local_udp_end,
            boost::asio::ip::tcp::endpoint local_tcp_end,
            boost::asio::ip::udp::endpoint remote_udp_end,
            boost::asio::ip::tcp::endpoint remote_tcp_end,
            boost::asio::io_context& context
        );

        void update(SUBSYSTEM_ORDER new_subsys, STATE_ORDER new_state);

        void add_commands(CommandDeck& new_commands);

        void handle_recv();
        void recv_tcp_fwd_udp();
        void recv_udp_fwd_tcp();
        void recv_udp_fwd_tcp_cmd();
        void send_tcp();
        void send_udp();

        void print_udp_basic();

        void handle_cmd();
};

#endif