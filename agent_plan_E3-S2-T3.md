# Agent Plan — E3-S2-T3

_Generated: 2026-06-10T14:47:11.734Z_

## Ticket analysis
Task E3-S2-T3 requires implementing real-time display update logic in the calculator app's C++ code. Specifically, Qt's signal and slot mechanism must be used to bind calculation results to the UI display, ensuring that after every input (digit, operator, equals, clear) the result label/display widget is updated immediately and accurately. This involves extending the existing calculation_logic.cpp with a signal that emits the current display string whenever state changes, and connecting that signal to the UI's display slot so that no manual polling or deferred refresh is needed.

## Orientation
The repo has a single app directory with one known file, app/calculation_logic.cpp, established through prior tasks (E3-S2-T1 for button click handlers, E3-S2-T2 for visual feedback). The project is a monolithic Qt 6.10 C++ desktop calculator. Prior commits indicate that calculation_logic.cpp, a header (calculation_logic.h), and a main window class (main_window.cpp / main_window.h) likely exist or are co-located in app/. The wiring list points exclusively to app/calculation_logic.cpp as the file to extend. Headers and companion UI files are expected to be adjacent and will need reading/modification to wire the signal-slot correctly.

## Files to create
- tests/test_calculation_logic_realtime.cpp

## Files to modify
- app/calculation_logic.cpp
- app/calculation_logic.h
- app/main_window.cpp
- app/main_window.h

## Files to read (before editing)
- app/calculation_logic.cpp
- app/calculation_logic.h
- app/main_window.cpp
- app/main_window.h
- app/main.cpp
- REPO_MAP.md

## Implementation order
1. 1. Read all existing files: app/calculation_logic.h, app/calculation_logic.cpp, app/main_window.h, app/main_window.cpp, app/main.cpp, REPO_MAP.md to understand current state.
2. 2. Modify app/calculation_logic.h: add Q_OBJECT macro if missing, declare a Qt signal `displayUpdated(const QString &text)` in the signals section, and ensure all public input-processing methods (digit input, operator input, equals, clear) are declared.
3. 3. Modify app/calculation_logic.cpp: after every state mutation (digit appended, operator stored, result computed, clear performed) emit `displayUpdated(currentDisplayString)` so the UI is notified immediately without polling.
4. 4. Modify app/main_window.h: declare a public slot `updateDisplay(const QString &text)` that sets the display label/line-edit text.
5. 5. Modify app/main_window.cpp: in the constructor (or initUI method), call QObject::connect(&calculationLogic, &CalculationLogic::displayUpdated, this, &MainWindow::updateDisplay) to wire the signal to the display slot; implement updateDisplay to set the display widget text.
6. 6. Create tests/test_calculation_logic_realtime.cpp: write unit tests (Qt Test / QTest framework) verifying that displayUpdated signal is emitted for every operation (digit input, operator, equals, clear) and that the emitted string matches expected display state; add integration-level test confirming signal-slot wiring produces correct display value.

## Acceptance criteria mapping
- AC: AC1: Result display updates immediately after any input or operation. → Steps 2-5: emit displayUpdated signal after every state mutation in CalculationLogic and connect it to MainWindow::updateDisplay slot, ensuring synchronous Qt direct connection updates the display widget on the same thread without delay.

## Out of scope (do NOT do)
- Do not introduce a separate backend service or network layer.
- Do not add new third-party dependencies or modify build system dependency files.
- Do not refactor the entire UI layout or create new UI screens beyond wiring the existing display widget.
- Do not implement features beyond real-time display update (e.g., history, theming).
- Do not duplicate existing signal-slot connections already present in prior task implementations.
- Do not create a parallel directory structure outside of app/ and tests/.

## Rationale
app/calculation_logic.cpp is the declared wiring target and is the natural place to emit the displayUpdated signal after each state change. app/calculation_logic.h must be modified to declare the signal (Q_OBJECT requirement). app/main_window.h and app/main_window.cpp must be modified to add the updateDisplay slot and the connect() call — without this wiring the signal would never reach the UI, making the AC impossible to satisfy. The test file tests/test_calculation_logic_realtime.cpp is justified by the task's explicit unit, integration, and E2E test requirements; it is placed in tests/ following idiomatic Qt project layout and does not duplicate existing test files.
