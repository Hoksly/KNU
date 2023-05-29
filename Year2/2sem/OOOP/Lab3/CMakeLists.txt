cmake_minimum_required(VERSION 3.10)
project(Lab3)

set(CMAKE_CXX_STANDARD 17)

set(Qt5_DIR "/home/hoksly/Qt5.7.0/5.7/gcc_64/lib/cmake/Qt5")
find_package(Qt5Widgets REQUIRED)

include_directories(antAlgorithms)
include_directories(ants)
include_directories(antsGUI)
include_directories(chooseBestRootStrategies)
include_directories(chooseNextNodeStrategies)
include_directories(colonies)
include_directories(maps)
include_directories(updateFeromoneStrategies)


add_executable(Lab3
        antAlgorithms/antAlgorithm.h
        antAlgorithms/basicAntAlgotiyhm.h
        ants/ant-test.cpp
        ants/ant.h
        ants/basicAnt.h
        ants/feromoneAnt.h
        chooseBestRootStrategies/chooseBestFeromoneRoot.h
        chooseBestRootStrategies/chooseBestRoot.h
        chooseNextNodeStrategies/chooseStrategy.h
        colonies/colony.h
        maps/map.h
        updateFeromoneStrategies/basicFeromoneDecayStrategy.h
        updateFeromoneStrategies/updateFeromoneStrategy.h

        main-GUI.cpp)
target_link_libraries(Lab3 Qt5::Core Qt5::Widgets boost_context)
