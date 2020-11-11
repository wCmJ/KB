file structure:
    treenode_project.structure

src files:
    - monitor
    - net
    - util

    create:
        - create klink object: 
            construct:
                - keep weak host_
                - create config_
                - create queue_
                    - start thread(Queue::run())
                - create dirty_work_queue_
                    - start thread(Queue::run())
                - create server_clock_
                - create sm_
                    - execute on_entry:
                        - FailAllCachedTransaction(); OnShutdown();
                        - StartOrContinueRace();
                        - Unregister();
                        - StopRace(); Heartbeat("heartbeat"); OnOnline();
            init:
                - create monitor object 
                - create access_point_manager_ object
                - create connection_generator_ object
                    - create connection_factory_
                    - create protocol_connection_faactory_
                    - keep delegate_(klink) and klink_(klink)
                    - start thread(io_context.run())
            
    StartOrContinueRace：
        - create horses
            - LATEST({ipv4, ipv6},{quic, tcp})/ 
              OPTIMAL({ipv4, ipv6},{quic, tcp})/ 
              FALLBACK({ipv4, ipv6},{quic, tcp})
        - one horse
            - create tcp_connection
            - tcp_connection connect(asyc_connect)
            - create protocol_connection when connect complete
            - protocol_connection handshake
                - construct transaction and set complete handle
                - create stream and init with tcp_connection(tcp_connection will startReceive)
                - tcp_connection send message
                - when receive response, select from transactioins_ and invoke Complete()
            - 



            - create protocol_connection if connect successfully
                - protocol_connection object contains tcp_connection object
            - protocol_connection handshake

        - connection ready, keep protocol_connection to klink_



android:
    input: 
        - *.java 
        - jni_java_*.cc
        - jni_java_*.h
        - *_internal.cc
        - *_internal.h
        - build.gradle
        - settings.gradle
        - include/
        - srcs/
    output:
        - android_project_output*.md
    


    



ios:
    input:
        - CMakeLists.txt
        - cmake/
    output:
        - ios_project_output*.md



- CMakeLists.txt of root dir
    - add_compile_options(-Wall)
    - add_definitions(-Dvariable)
    - find_program(PB_COMPILER protoc REQUIRED)
    - execute_process(COMMAND )
    - 









