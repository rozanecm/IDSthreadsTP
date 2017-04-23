cmake_minimum_required(VERSION 3.6)
project(Proyecto)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Assembler.cpp
        Assembler.h
        AssemblerMonitor.cpp
        AssemblerMonitor.h
        IPPacket.cpp
        IPPacket.h
        Lock.cpp
        Lock.h
        Rule.cpp
        Rule.h
        Sniffer.cpp
        Sniffer.h
        Thread.cpp
        Thread.h
        ThreatDetector.cpp
        ThreatDetector.h
        ThreatDetectorMonitor.cpp
    ThreatDetectorMonitor.h
    tp.cpp)

add_executable(Proyecto ${SOURCE_FILES})