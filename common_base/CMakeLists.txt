add_library(common
    connection_lost_exception.cpp connection_lost_exception.h
    liberror.cpp liberror.h
    network_channel.cpp network_channel.h
    protocol_consts.h
    queue.h
    resolver.cpp resolver.h
    resolvererror.cpp resolvererror.h
    socket.cpp socket.h
    thread.h
)

target_include_directories(common PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/"
)
