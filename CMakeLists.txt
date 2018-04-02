cmake_minimum_required(VERSION 3.9)
cmake_policy(VERSION 3.9)

project("gossip"
    LANGUAGES
        CXX
    VERSION
        0.1.0
)

include(GNUInstallDirs)

enable_testing()

option(GOSSIP_BUILD_TESTS "Build gossip's test suite" ON)

if(GOSSIP_BUILD_TESTS)
    find_package(GTest REQUIRED)
    function(create_test test_name)
        add_executable(${test_name} ${ARGN})
        target_link_libraries(${test_name} PUBLIC
            gossip
        )
        target_link_libraries(${test_name} PRIVATE
            GTest::GTest
            GTest::Main
        )
        add_test(NAME ${test_name}
            COMMAND ${test_name} "--gtest_output=xml:${CMAKE_CURRENT_BINARY_DIR}/${test_name}_results.xml"
        )
    endfunction()
else()
    function(create_test test_name)
    endfunction()
endif()

add_library(gossip SHARED)
set_target_properties(gossip PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION}
)
target_include_directories(gossip PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(gossip PUBLIC
    cxx_std_14
)

add_library(gossip-static STATIC)
set_target_properties(gossip-static PROPERTIES
    OUTPUT_NAME gossip
)
target_include_directories(gossip-static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(gossip-static PUBLIC
    cxx_std_14
)

function(add_public_lib_sources)
    target_sources(gossip PUBLIC ${ARGN})
    target_sources(gossip-static PUBLIC ${ARGN})
endfunction()
function(add_private_lib_sources)
    target_sources(gossip PRIVATE ${ARGN})
    target_sources(gossip-static PRIVATE ${ARGN})
endfunction()

add_private_lib_sources(dispatcher.cpp)
add_public_lib_sources(
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/gossip/dispatcher.hpp>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/gossip/dispatcher.hpp>
)

create_test(dispatcher_test
    dispatcher_test.cpp
)

install(TARGETS
        gossip
        gossip-static
    EXPORT GossipConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gossip/dispatcher.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/gossip
)
export(TARGETS
        gossip
        gossip-static
    NAMESPACE Gossip::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/GossipConfig.cmake"
)
install(EXPORT
        GossipConfig
    DESTINATION "${CMAKE_INSTALL_DATADIR}/Gossip/cmake"
    NAMESPACE Gossip::
)
