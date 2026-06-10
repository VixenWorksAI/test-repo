# Agent Plan — E3-S1-T1

_Generated: 2026-06-10T14:25:42.652Z_

## Ticket analysis
Task E3-S1-T1 requires creating the main window UI layout for a Qt 6.10 C++ desktop calculator application. The layout must be defined as a Qt Designer .ui file containing three distinct sections organized in a grid layout: an input display area, operation buttons panel, and a result display area. The layout must adapt to various screen sizes using proper Qt grid layout constraints. The wiring references 'app/layout.tsx' which is a Next.js convention file that does not belong in a C++ Qt project — the real deliverable is a Qt .ui XML file and a corresponding C++ main window class.

## Orientation
The repo is nearly empty (0 total files reported in repoMapSummary, only the 'app' directory touched). The declared wiring file 'app/layout.tsx' is a Next.js artifact that should not exist in a C++ Qt desktop project — it appears to be a project scaffolding artifact. The prior agent branch has no prior agent files. The project is a monolithic C++ Qt 6.10 calculator app for Linux. The correct idiomatic Qt structure uses src/ for C++ source, and ui/ or src/ for .ui files, with a CMakeLists.txt or .pro build file at root. Since no existing Qt structure exists, we must create the foundational layout files.

## Files to create
- src/mainwindow.ui
- src/mainwindow.h
- src/mainwindow.cpp
- src/main.cpp
- CMakeLists.txt
- tests/test_mainwindow.cpp

## Files to modify
- app/layout.tsx

## Files to read (before editing)
- app/layout.tsx

## Implementation order
1. 1. Read app/layout.tsx to confirm its current content and update it with a placeholder note redirecting to the Qt .ui layout file.
2. 2. Create CMakeLists.txt at project root configuring Qt 6.10, enabling automoc/autouic/autorcc, and adding the calculator executable target with all source files.
3. 3. Create src/mainwindow.ui as a Qt Designer XML file defining a QMainWindow with a central widget using QGridLayout, containing: a QLineEdit for input display (row 0, spanning full width), a QGridLayout sub-section for operation buttons (rows 1-4, numeric and arithmetic: 0-9, +, -, *, /, =, C, .), and a QLabel/QLineEdit for result display (last row, spanning full width, read-only). Set minimum sizes and size policies to enable responsive scaling.
4. 4. Create src/mainwindow.h declaring the MainWindow class inheriting QMainWindow with Ui::MainWindow pointer, constructor/destructor, and private slots for button interactions.
5. 5. Create src/mainwindow.cpp implementing the MainWindow constructor that sets up the UI via setupUi(), applies grid layout constraints, and sets minimum window size for cross-resolution support.
6. 6. Create src/main.cpp with QApplication entry point instantiating and showing MainWindow.
7. 7. Create tests/test_mainwindow.cpp implementing a QTest-based unit test that loads the MainWindow in isolation, verifies all three UI sections (inputDisplay, buttonGrid area, resultDisplay) are present and non-null, and checks layout type is QGridLayout.

## Acceptance criteria mapping
- AC: AC1: The UI layout is created and saved in the project directory. → 3. Create src/mainwindow.ui as a Qt Designer XML file saved in the project's src/ directory.
- AC: AC2: All designated sections are present and organized into a grid. → 3. The .ui file defines input display, operation buttons panel, and result display all placed within a QGridLayout with proper row/column spans and size policies for responsiveness.

## Out of scope (do NOT do)
- Do NOT implement arithmetic logic or signal/slot connections beyond UI setup in this task.
- Do NOT add cloud, authentication, or database components.
- Do NOT create a Next.js or React project structure — this is a C++ Qt desktop app.
- Do NOT use app/layout.tsx as the actual UI definition; it is only noted as wiring and will receive a redirect comment.
- Do NOT implement division-by-zero handling or input validation logic (belongs in later tasks).
- Do NOT add CI/CD pipeline files beyond what already exists.
- Do NOT introduce Python, Java, or any language other than C++ and Qt XML.

## Rationale
The wiring file 'app/layout.tsx' is a Next.js convention artifact that conflicts with the C++ Qt project architecture; it will be acknowledged with a note but the real layout work is in Qt-idiomatic files under src/. New files src/mainwindow.ui (Qt Designer XML), src/mainwindow.h, src/mainwindow.cpp, src/main.cpp are all required to deliver a working Qt UI layout as demanded by AC1 and AC2. CMakeLists.txt is required because without a build file the Qt uic tool cannot process the .ui file and no executable can be produced — this is the idiomatic Qt 6 build entry point. tests/test_mainwindow.cpp is required by the unit test requirement to verify the layout loads without errors. All files are justified by the acceptance criteria and test requirements; no speculative files are added.
