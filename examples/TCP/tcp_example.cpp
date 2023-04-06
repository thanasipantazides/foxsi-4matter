
#include "TCPInterface.h"
#include <boost/asio.hpp>
#include <iostream>

int main() {
    boost::asio::io_context context;

    // boost::asio::ip::address address(boost::asio::ip::make_address(GSE_IP));
    // boost::asio::ip::tcp::endpoint endpoint(address, 9000);
    // TCPServer server(endpoint, context);

    TCPInterface tcpif(LOCAL_IP, LOCAL_PORT, GSE_IP, GSE_PORT, context);

    context.run();

    return 0;
}