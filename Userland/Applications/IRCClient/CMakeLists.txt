serenity_component(
    IRCClient
    TARGETS IRCClient
)

compile_gml(IRCAppWindow.gml IRCAppWindowGML.h irc_app_window_gml)

set(SOURCES
    IRCAppWindow.cpp
    IRCAppWindowGML.h
    IRCChannel.cpp
    IRCChannelMemberListModel.cpp
    IRCClient.cpp
    IRCLogBuffer.cpp
    IRCQuery.cpp
    IRCWindow.cpp
    IRCWindowListModel.cpp
    main.cpp
)

serenity_app(IRCClient ICON app-irc-client)
target_link_libraries(IRCClient LibWeb LibGUI LibMain)
