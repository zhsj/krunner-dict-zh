project(DictZhRunner)

cmake_minimum_required(VERSION 2.8.12)

include(FeatureSummary)

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set (CMAKE_MODULE_PATH
     ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_MODULE_PATH}
)

find_package (Qt5 REQUIRED CONFIG COMPONENTS Core Network Widgets)
find_package (KF5 REQUIRED COMPONENTS I18n Runner)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)

include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   )

set(runner_SRCS
    src/dict_zh_runner.cpp
    src/youdao.cpp)

add_library(krunner_dict_zh MODULE ${runner_SRCS})

target_link_libraries(krunner_dict_zh
                      Qt5::Widgets
                      Qt5::Network
                      KF5::I18n
                      KF5::Runner)

install(TARGETS krunner_dict_zh
        DESTINATION ${PLUGIN_INSTALL_DIR})

install (FILES plasma-runner-dict-zh.desktop
         DESTINATION ${SERVICES_INSTALL_DIR}
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
