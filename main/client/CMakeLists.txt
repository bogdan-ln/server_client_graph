add_executable(client
    graph_client.cpp
    main.cpp
)

target_include_directories(client PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(client
    sfml-system
    sfml-window 
    sfml-graphics 
    sfml-audio
    $<$<PLATFORM_ID:Darwin>:${Boost_SYSTEM_LIBRARY}>
    $<$<NOT:$<PLATFORM_ID:Darwin>>:Boost::system>
)