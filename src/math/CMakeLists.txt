add_library(math INTERFACE
        bounding_box.h)
target_sources(math INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/vector.h
    ${CMAKE_CURRENT_SOURCE_DIR}/point.h
    ${CMAKE_CURRENT_SOURCE_DIR}/line.h
)