add_library( toyslam SHARED
    frame.cpp
    mappoint.cpp
    map.cpp
    camera.cpp
    config.cpp
    feature.cpp
    frontend.cpp
    backend.cpp
    viewer.cpp
    VO.cpp
    dataset.cpp
)

target_link_libraries( toyslam
    ${THIRD_PARTY_LIBS}
)
