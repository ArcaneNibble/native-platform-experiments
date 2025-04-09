add_executable(demo-dice)

ecm_add_qml_module(demo-dice
    URI
    com.arcanenibble.KDice
)

target_sources(demo-dice
    PRIVATE
    main.cpp
    backend.cpp
)

ecm_target_qml_sources(demo-dice
    SOURCES
    Main.qml
)

target_link_libraries(demo-dice
    PRIVATE
    Qt6::Quick
    Qt6::Qml
    Qt6::Gui
    Qt6::QuickControls2
    Qt6::Widgets
    KF6::I18n
    KF6::CoreAddons
    KF6::IconThemes
    KF6::ConfigCore
)

install(TARGETS demo-dice ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
