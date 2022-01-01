/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "IRCAppWindow.h"
#include "IRCClient.h"
#include <LibCore/System.h>
#include <LibGUI/Application.h>
#include <LibGUI/MessageBox.h>
#include <LibMain/Main.h>
#include <stdio.h>

ErrorOr<int> serenity_main(Main::Arguments arguments)
{
    if (getuid() == 0) {
        warnln("Refusing to run as root");
        return 1;
    }
 
    TRY(Core::System::pledge("stdio inet unix recvfd sendfd cpath rpath wpath"));

    auto app = GUI::Application::construct(arguments);
    
    TRY(Core::System::unveil("/tmp/portal/webcontent", "rw"));
    TRY(Core::System::unveil("/tmp/portal/lookup", "rw"));
    TRY(Core::System::unveil("/res", "r"));
    TRY(Core::System::unveil("/etc/passwd", "r"));
    TRY(Core::System::unveil("/etc/ca_certs.ini", "r"));
    TRY(Core::System::unveil(nullptr, nullptr));

    URL url = "";
    bool secure = false;
    if (app->args().size() >= 1) {
        url = URL::create_with_url_or_path(app->args()[0]);

        if (url.host().is_empty()) {
            warnln("Invalid URL");
            return 1;
        }
        
        auto protocol = url.protocol().to_lowercase();
        if (protocol != "irc" && protocol != "ircs") {
            warnln("Unsupported protocol");
            return 1;
        }

        if (protocol == "ircs") {
            secure = true;
        }
    }

    auto app_window = IRCAppWindow::construct(url.host(), url.port_or_default(), secure);
    app_window->show();
    return app->exec();
}
