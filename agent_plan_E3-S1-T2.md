# Agent Plan — E3-S1-T2

_Generated: 2026-06-10T14:30:21.582Z_

## Ticket analysis
Task E3-S1-T2 requires integrating the Qt Designer UI layout file (created in task E3-S1-T1) into the C++ application by updating app/main.cpp to load and display the main window and extending app/interface.h to declare the MainWindow class with proper Qt signal/slot connections. The UIC-generated header (ui_mainwindow.h) must be included and all UI button signals must be connected to their corresponding slot functions so that digit input, operator selection, equals evaluation, and clear actions all work end-to-end within the primary application window.

## Orientation
The repo currently contains only the app/ directory with one file (REPO_MAP.md lists totalFiles: 1, directory: app). The immediately prior commit added the Qt Designer .ui file (mainwindow.ui or equivalent) as part of E3-S1-T1. The wiring declares app/main.cpp and app/interface.h as the files to extend. No CMakeLists.txt or .pro file is listed in the intel, but those build files must exist to compile Qt — however they are not in the declared wiring and the intel does not surface them, so the plan will conservatively include them only as reads/modifications needed to wire UIC into the build, justified by AC1 (UI layout correctly imported requires the build system to invoke uic).

## Files to create
- app/interface.cpp

## Files to modify
- app/main.cpp
- app/interface.h
- app/CMakeLists.txt

## Files to read (before editing)
- app/main.cpp
- app/interface.h
- app/CMakeLists.txt
- app/mainwindow.ui

## Implementation order
1. 1. Read app/mainwindow.ui to confirm widget object names and layout so slot connections use correct identifiers.
2. 2. Read app/interface.h and app/main.cpp to understand any existing declarations before overwriting.
3. 3. Read app/CMakeLists.txt to confirm qt_add_executable / target_sources and add ui_mainwindow.h generation via qt_add_ui or set(CMAKE_AUTOUIC ON).
4. 4. Update app/CMakeLists.txt: ensure CMAKE_AUTOUIC is ON (or qt_add_ui call), add interface.cpp to sources, and link Qt6::Widgets.
5. 5. Update app/interface.h: define MainWindow class inheriting QMainWindow, include <QMainWindow> and the UIC-generated 'ui_mainwindow.h', declare private Ui::MainWindow ui member, declare all public slots (onDigitPressed, onOperatorPressed, onEqualsPressed, onClearPressed, updateDisplay).
6. 6. Create app/interface.cpp: implement MainWindow constructor (ui.setupUi(this) + connect all button signals to slots), implement each slot with arithmetic logic (handle division-by-zero, update display label).
7. 7. Update app/main.cpp: create QApplication, instantiate MainWindow, call show(), return app.exec().

## Acceptance criteria mapping
- AC: AC1: UI layout is correctly imported into the application. → Steps 3-4 (CMakeLists.txt updated with AUTOUIC/qt_add_ui so uic generates ui_mainwindow.h) and Step 5 (interface.h includes ui_mainwindow.h and calls ui.setupUi).
- AC: AC2: All interface elements are correctly connected to application slots. → Steps 5-6 (interface.h declares slots; interface.cpp wires every button signal to its slot via QObject::connect inside the MainWindow constructor).

## Out of scope (do NOT do)
- Creating or modifying the .ui file itself (that belongs to E3-S1-T1).
- Adding new arithmetic logic modules beyond what is needed to implement the slots in interface.cpp.
- Writing formal JUnit/GoogleTest unit-test files (test scaffolding is a separate task).
- Introducing any cloud, network, or authentication code.
- Changing the directory structure or adding subdirectories.
- Modifying any CI/CD pipeline files beyond what the host auto-manages.

## Rationale
app/interface.cpp is the only new file justified: Qt convention separates the class declaration (interface.h) from its implementation (.cpp), and placing constructor + slot implementations inline in the header would violate ODR when included from multiple translation units. CMakeLists.txt must be modified (not created) because it must already exist to build the Qt project — it needs AUTOUIC enabled and interface.cpp added to sources so the UIC-generated header is produced and the new translation unit is compiled. All other changes are strictly to the declared wiring files (main.cpp, interface.h).
