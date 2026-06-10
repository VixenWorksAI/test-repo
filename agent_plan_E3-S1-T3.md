# Agent Plan — E3-S1-T3

_Generated: 2026-06-10T14:34:42.621Z_

## Ticket analysis
Task E3-S1-T3 requires enhancing the existing Qt UI layout in app/main_window.ui to be fully responsive across different window sizes. The goal is to leverage Qt 6.10 layout managers (QGridLayout, QVBoxLayout, QHBoxLayout, size policies, stretch factors, and minimum/maximum size constraints) so that all calculator UI components — display, buttons, and any groupings — resize gracefully from minimum to maximum window dimensions without overlap, truncation, or loss of functionality. The acceptance criteria demand that the UI maintains integrity and usability at all reasonable screen sizes.

## Orientation
The repository contains a single app directory with one tracked file: app/main_window.ui, which was created and wired into the main application in tasks E3-S1-T1 and E3-S1-T2 (committed ~10–25 seconds ago). There are no other source files listed in the repo map (totalFiles: 1). The project is a monolithic C++/Qt 6.10 desktop calculator app for Linux. No guardrail path denies are active, and no dependency block actions apply. The only file requiring modification to satisfy the responsive-layout acceptance criteria is app/main_window.ui.

## Files to create
- (none)

## Files to modify
- app/main_window.ui

## Files to read (before editing)
- app/main_window.ui

## Implementation order
1. 1. Read app/main_window.ui to understand the current widget hierarchy, layout types, and size constraints already in place.
2. 2. Modify app/main_window.ui: set the top-level QMainWindow/QWidget to use a QVBoxLayout as its central widget layout with no fixed size, removing any hardcoded width/height on the root widget beyond a sensible minimumSize (e.g., 240×320).
3. 3. Ensure the display widget (QLineEdit or QLabel) has a QSizePolicy of Expanding/Fixed (horizontal Expanding, vertical Fixed or Minimum) so it stretches horizontally with the window.
4. 4. Wrap the button grid in a QGridLayout with uniform column and row stretch factors (setColumnStretch / setRowStretch equal values for each column/row) so buttons scale proportionally.
5. 5. Set each button's QSizePolicy to Expanding/Expanding so they fill available space in both dimensions.
6. 6. Set the centralWidget QSizePolicy to Expanding/Expanding and remove any fixed-size constraints on intermediate container widgets.
7. 7. Add layout spacing and margin properties (layoutSpacing, layoutLeftMargin, etc.) using Qt's contentsMargins to maintain visual breathing room at all sizes.
8. 8. Verify the XML is well-formed and valid Qt .ui format after edits.

## Acceptance criteria mapping
- AC: AC1: UI maintains integrity and usability across different window sizes. → Steps 2–7: Removing fixed sizes, applying Expanding size policies to display and buttons, using uniform stretch factors in the grid layout, and setting appropriate margins ensures the layout scales cleanly from minimum to maximum window sizes without overlapping or non-functional elements.

## Out of scope (do NOT do)
- Creating new C++ source files (.cpp/.h) — all responsive changes are declarative inside the .ui file.
- Adding new widgets or calculator features beyond layout responsiveness.
- Modifying CMakeLists.txt or any build files.
- Writing automated test files — test infrastructure for this task is outside the single wiring file scope.
- Introducing CSS/QSS stylesheet files or external resource files.
- Dynamic runtime layout adjustments in C++ code (no new .cpp changes needed for basic Qt layout responsiveness).

## Rationale
The wiring list specifies exactly one file: app/main_window.ui. All acceptance criteria for responsive design in a Qt .ui-based desktop app can be fully satisfied by modifying layout manager properties, size policies, and stretch factors within that single XML file — no new files are warranted. Qt's declarative layout system (QGridLayout with stretch, QSizePolicy::Expanding) is the idiomatic mechanism for responsiveness in Qt 6.10 and does not require companion C++ changes for basic resizing behavior.
