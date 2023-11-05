add_library(common
    Networking/socket_connection_lost_error.cpp 
    Networking/socket_connection_lost_error.h 
    Networking/net_buffer.cpp 
    Networking/net_buffer.h 
    Networking/net_protocol_interpreter.cpp 
    Networking/net_protocol_interpreter.h

    liberror.cpp liberror.h
    network_channel.cpp network_channel.h
    protocol_consts.h
    queue.h
    resolver.cpp resolver.h
    resolvererror.cpp resolvererror.h
    socket.cpp socket.h
    thread.h
    
    Networking/Messages/net_message.cpp
    Networking/Messages/net_message.h
    Networking/Messages/net_message_factory.cpp
    Networking/Messages/net_message_factory.h
    Networking/Messages/net_message_test.h
    Networking/Messages/net_message_chat.cpp
    Networking/Messages/net_message_chat.h
    Networking/Messages/net_message_leave.cpp
    Networking/Messages/net_message_leave.h
    Networking/Messages/net_message_inform_id.cpp
    Networking/Messages/net_message_inform_id.h
    
    Networking/Messages/net_message_behaviour.h

    Networking/net_channel.cpp 
    Networking/net_channel.h 

    networking.h 
)

target_include_directories(common PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/"
)
