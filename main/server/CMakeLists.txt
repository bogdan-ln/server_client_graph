add_executable(server
    graph_server.cpp
    main.cpp
)

target_include_directories(server PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(server
    sfml-system
    sfml-window 
    sfml-graphics 
    sfml-audio
    $<$<PLATFORM_ID:Darwin>:${Boost_SYSTEM_LIBRARY}>
    $<$<NOT:$<PLATFORM_ID:Darwin>>:Boost::system>
)