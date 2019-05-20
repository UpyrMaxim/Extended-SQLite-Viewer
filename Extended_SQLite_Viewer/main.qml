import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls 1.4 as Old
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

import SQliteModel 1.0
import SQliteTableList 1.0



Window {
    id: window
    visible: true
    width: 640

    height: 480
    title: qsTr("SQLite Viewer")


    Button {
        id: mainMenuButton
        text: "Menu"
        x: 8
        y: 6
        implicitWidth: 150
        implicitHeight: 30

        onClicked: mainMenu.open();
    }

    Menu {
        id: mainMenu
        y: mainMenuButton.height  + mainMenuButton.y + 1
        x: 5
        MenuItem {
            text: "Choose DB file"
            onClicked: fileDialog.open();
        }

        MenuItem {
            text: "About"
        }

        MenuItem {
            text: "Exit"
             onClicked: Qt.quit();
        }
    }

    Rectangle {
        id: tablesName
        x: 22
        y: mainMenuButton.height  + mainMenuButton.y + 5
        width: 150
        color: "#ececec"
        implicitWidth: parent.width
        implicitHeight: 20
        Text {
            text: "Tables:"
        }
    }

    Rectangle {
        id: tableListField
        x: 22
        y: tablesName.height  + tablesName.y
        width: 150
        height: parent.height

        ListView{
            anchors.fill: parent

            clip: true
            model: SQliteTableList {
                id: tableListModel
            }

            delegate: RowLayout{
                width: parent.width

                TextField {
                    readOnly: true
                    text: display
                    Layout.fillWidth: true

                    MouseArea {
                        anchors.fill: parent
                        onClicked:{
                           tablelContentMode.setDataBase(display)
                        }
                    }
                }
            }
        }
//        TableView {
//            id: mainTableView
//            height: 20
//            anchors.fill: parent
//            columnSpacing: 1
//            rowSpacing: 1
//            clip: true

//            model: SQliteModel {
//                id: myModel
//            }

//            delegate: Rectangle {
//                color: "#CEDCDD"
//                implicitWidth: 150
//                implicitHeight: 20
//                Text {
//                    text: display
//                }
//            }
//         }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        nameFilters: ["DB files (*.sqlite)"]
        selectExisting: true
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls);
            console.log("converted to : " + urlToPath(fileDialog.fileUrls.toString()));

            tableListModel.setDataBase(urlToPath(fileDialog.fileUrls.toString()));
        }
        onRejected: {
            console.log("Canceled")
        }
    }

//    Rectangle {
//        id: tablesName1
//        x: 185
//        y: 41
//        width: 429
//        height: 20
//        color: "#ececec"
//        Text {
//            text: "Table data:"
//        }
//        implicitHeight: 20
//        implicitWidth: 150
//    }

    Rectangle {
        id: tableColumns
        x: 185
        y: tablesName1.y + tablesName1.height +1
        width: 429
        height: 20
        color: "#cedcec"
        Text {
            text: "Table data:"
        }
        implicitHeight: 20
        implicitWidth: 150
    }

    Rectangle {
        id: tableContentFields
        x: 185
        y: tableColumns.y + tableColumns.height +1
        width: 429
        height: parent.height
//        TableView {
//            height: 20
//            model: mainTableView.model
//            rowSpacing: 1
//            anchors.fill: parent
//            clip: true
//            columnSpacing: 1
//            delegate: Rectangle {
//                color: "#cedcdd"
//                Text {
//                    text: display
//                }
//                implicitHeight: 20
//                implicitWidth: parent.width
//            }
//        }
        TableView {
            id: mainTableView
            height: 20
            anchors.fill: parent
            columnSpacing: 1
            rowSpacing: 1
            clip: true

            model: SQliteModel {
                id: tablelContentMode
            }

            delegate: Rectangle {
                color: "#CEDCDD"
                implicitWidth: 150
                implicitHeight: 20
                Text {
                    text: display
                }
            }
         }
    }

    // на лінухі і вінді по різному визначається url
    function urlToPath(urlString) {
        let s
        if (urlString.startsWith("file:///")) {
            let k = urlString.charAt(9) === ':' ? 8 : 7
            s = urlString.substring(k)
        } else {
            s = urlString
        }
        return decodeURIComponent(s);
    }
}








/*##^## Designer {
    D{i:1;anchors_height:19;anchors_width:19;anchors_x:0;anchors_y:0}
}
 ##^##*/
