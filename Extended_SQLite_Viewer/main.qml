import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

import SQliteModel 1.0
import SQliteTableList 1.0
import QHexConvertor 1.0
import RAWDataTable 1.0



Window {
    id: window
    visible: true
    width: 800

    minimumHeight: 480
    minimumWidth: 800

    height: 480
    color: "#feffe0"
    title: qsTr("SQLite Viewer")



    Button {
        id: mainMenuButton
        x: 22
        y: 5


        text: "Menu"
        background: Rectangle {
            implicitWidth: 150
            implicitHeight: 30
            color: "#80b1dd"
            border.width: control.activeFocus ? 2 : 1
            border.color: "#888"
            radius: 4
        }
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
        color: window.color
        width: 150
        height: 410
       // property string activeTable: ""

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
                    //Font.bold: display == activeTable

                    background: Rectangle {
                        color: mouseArea.containsMouse ? "#CEDCDD" : "#cedcec"
                    }
                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked:{

                           tableDataTabButton.text = display

                           if(bar.currentIndex == 0)
                           {
                               tablelContentMode.setDataBase(tableDataTabButton.text)
                           }

                           if(bar.currentIndex == 1)
                           {
                               //tablelContentMode.setDataBase(display)
                               rawTablelContentModel.setDataBase(urlToPath(fileDialog.fileUrls.toString()),tableDataTabButton.text)
                           }

                           if(bar.currentIndex == 2)
                           {
                               hexText.text = hexConvertor.getHexData(urlToPath(fileDialog.fileUrls.toString()),tableDataTabButton.text);
                           }
                        }
                    }
                }
            }
        }

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

    Rectangle {
        id: tableColumns
        x: 185
        y: 5
        width: 429
        height: 20
        color: window.color
        TabBar {
            id: bar
            width: parent.width
            height: parent.height

            TabButton {
                id: tableDataTabButton
                height: parent.height
                text: qsTr("TableData")
                onClicked: {
                   tablelContentMode.setDataBase(tableDataTabButton.text)
                }
            }
            TabButton {
                height: parent.height
                text: qsTr("Formated RAW data")
                onClicked: {
                   tablelContentMode.setDataBase(tableDataTabButton.text)
                }
            }
            TabButton {
                height: parent.height
                text: qsTr("hex")
                QHexConvertor {
                    id: hexConvertor
                }
                onClicked: {
                  hexText.text = hexConvertor.getHexData(urlToPath(fileDialog.fileUrls.toString()),tableDataTabButton.text);
                }
            }

            onCurrentIndexChanged: {
                  switch (currentIndex)
                  {
                  case 0:
                      tableContentFields.visible = true;
                      rawDataField.visible = false;
                      hexDataField.visible = false;
                      break;
                  case 1:
                      tableContentFields.visible = false;
                      rawDataField.visible = true;
                      hexDataField.visible = false;
                      break;
                  case 2:
                      tableContentFields.visible = false;
                      rawDataField.visible = false;
                      hexDataField.visible = true;
                      break;
                  }
             }
         }
    }


    Rectangle {
        id: tableContentFields
        visible: true
        x: 185
        y: 40
        width: window.width - tableListField.width - 40;
        height:window.height - 35;
        color: "#feffe0"

        TableView {
            id: mainTableView
            height: 20
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 1
            topMargin: columnsHeader.implicitHeight
            leftMargin: rowsHeader.implicitWidth + 1
            anchors.fill: parent
            columnSpacing: 1
            rowSpacing: 1
            clip: true
            model: SQliteModel {
                id: tablelContentMode
            }

            delegate: Rectangle {
                id: tableRowTextField
                color: "#CEDCDD"
                implicitWidth: 150
                implicitHeight: 20
                width: 150
                height: 20
                Text {
                    id: tableColumn
                    text: display
                }
            }

            Row {
                id: columnsHeader
                y: mainTableView.contentY
                z: 3

                Repeater {
                    model: mainTableView.columns
                    Label {
                        width: 151
                        height: 26
                        text: tablelContentMode.headerData(modelData, Qt.Horizontal)
                        color: '#333333'
                        padding: 10
                        verticalAlignment: Text.AlignVCenter

                        background: Rectangle { color: "#aaaaaa" }
                    }
                }
            }
            Column {
                id: rowsHeader
                x: mainTableView.contentX
                z: 2
                Repeater {
                    model: mainTableView.rows
                   Button {
                       width: 10
                       height: 21
                        onClicked: {
                            tablelContentMode.removeRow(modelData);
                        }
                       Text {
                           id: delBtnText
                           text: qsTr("X")
                           color: "#ff0000"
                           anchors.centerIn: parent
                       }
                   }
                }
            }
        }
    }

    Rectangle {
        id: rawDataField
        visible: false
        x: 185
        y: 40
        width: window.width - tableListField.width - 40;
        height:window.height - 35;
        color: "#feffe0"
        TableView {
            id: rawDataTableView
            height: 20
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 1
//            topMargin: rawDataColumnsHeader.implicitHeight
            anchors.fill: parent
            columnSpacing: 1
            rowSpacing: 1
            clip: true
            model: RAWDataTable {
                id: rawTablelContentModel
            }

            delegate: Rectangle {
                id: rawTableRowTextField
                color: "#CEDCDD"
                implicitWidth: 150
                implicitHeight: 20
                width: 150
                height: 20
                Text {
                    id: rawTableColumn
                    text: display
                }
            }

            Row {
                id: rawDataColumnsHeader
                y: mainTableView.contentY
                z: 3

                Repeater {
                    model: rawDataTableView.columns
                    Label {
                        width: 151
                        height: 26
                        text: rawTablelContentModel.headerData(modelData, Qt.Horizontal)
                        color: '#333333'
                        padding: 10
                        verticalAlignment: Text.AlignVCenter

                        background: Rectangle { color: "#aaaaaa" }
                    }
                }
            }
        }
   }

    Rectangle {
        id: hexDataField
        visible: false
        x: 185
        y: 40
        width: 1000 - tableListField.width - 40;
        height:window.height - 35;
        color: "#feffe0"
        ScrollView {
            id: view
            anchors.fill: parent
            clip: true
            TextArea {
                id: hexText
                readOnly: true
                font: fixedFont
                text: "HEX DATA FIELD"
            }
        }
   }

    // на лінухі і вінді по різному визначається url
    function urlToPath(urlString) {
        var s;
        if (urlString.startsWith("file:///")) {
            var k = urlString.charAt(9) === ':' ? 8 : 7;
            s = urlString.substring(k)
        } else {
            s = urlString
        }
        return decodeURIComponent(s);
    }
}
