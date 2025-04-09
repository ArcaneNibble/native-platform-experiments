add_executable(kde-dice)

ecm_add_qml_module(kde-dice
    URI
    com.arcanenibble.KDice
)

target_sources(kde-dice
    PRIVATE
    main.cpp
    backend.cpp
)

ecm_target_qml_sources(kde-dice
    SOURCES
    Main.qml
)

target_link_libraries(kde-dice
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

install(TARGETS kde-dice ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
