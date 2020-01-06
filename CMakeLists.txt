cmake_minimum_required(VERSION 3.5)

project(Kompozitor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Widgets QuickControls2 REQUIRED)
if (APPLE)
    find_package(SFML COMPONENTS audio REQUIRED)
endif()


add_executable(Kompozitor
        src/main.cpp
        qml.qrc
        src/ui_model/main_model.cpp src/ui_model/main_model.hpp
        src/playback/playback.cpp src/playback/playback.hpp
        src/playback/sound_manager.cpp src/playback/sound_manager.hpp
        src/ui_model/track_note.cpp src/ui_model/track_note.hpp
        src/playback/record_manager.cpp src/playback/record_manager.hpp
        src/ui_model/tracks_list_model.cpp src/ui_model/tracks_list_model.hpp
        src/ui_model/track.hpp
        src/ui_model/note_track.hpp
        src/ui_model/sample_track.hpp
        src/playback/microphone_recorder.cpp src/playback/microphone_recorder.hpp)


target_include_directories(Kompozitor PRIVATE src)

target_compile_definitions(Kompozitor
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(Kompozitor
  PRIVATE   Qt5::Core
            Qt5::Quick
            Qt5::Widgets
            Qt5::QuickControls2
            sfml-audio
            pthread)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# These variables must use CACHE, otherwise QtCreator won't see them.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android" CACHE INTERNAL "")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so CACHE INTERNAL "")
#    endif()
#endif()
