@GUI::Widget {
    fill_with_background_color: true

    layout: @GUI::VerticalBoxLayout {
        spacing: 0
    }

    @GUI::ToolbarContainer {
        name: "toolbar_container"

        @GUI::Toolbar {
            name: "toolbar"
        }
    }

    @GUI::Widget {
        name: "outer_container"
        
        layout: @GUI::VerticalBoxLayout {
            margins: [0, 2, 2]
        }

        @GUI::HorizontalSplitter {
            name: "horizontal_container"

            @GUI::TableView {
                name: "window_list"
            }

            @GUI::StackWidget {
                name: "container"
            }
        }
    }
}
