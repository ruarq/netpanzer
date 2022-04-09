project(np_core)
add_library(np_core common.hpp platform.hpp Net/Socket.cpp Net/Socket.hpp Net/TcpSocket.cpp Net/TcpSocket.hpp Buffer.hpp Buffer.cpp Net/UdpSocket.cpp Net/UdpSocket.hpp Net/SocketSet.cpp Net/SocketSet.hpp)
