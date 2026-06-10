# Agent Plan — E2-S3-T4

_Generated: 2026-06-10T04:04:44.216Z_

## Ticket analysis
Task E2-S3-T4 requires developing a comprehensive test suite for the multiplication feature of a Qt/C++ calculator desktop application. The tests must cover three layers: unit tests validating multiplication correctness including edge cases (large values, overflow, zero, negative numbers), integration tests confirming the multiplication logic connects properly to the Qt UI via signals/slots, and end-to-end tests simulating the full user interaction path through the UI. All three test files are pre-declared in the wiring list and must be extended (not created from scratch if they already exist, though the repo map shows 0 total files, suggesting they need to be created).

## Orientation
The repo map reports 0 total files but lists directories including test/unit, test/integration, test/e2e, and tests. Prior commits show E2-S3-T3 wired multiplication UI and logic, and E2-S3-T2 implemented the multiplication logic. The wiring declares three specific test files that must be the sole targets. The prior agent branch files include a Calculator directory suggesting source files exist there. Since totalFiles is 0 in the map, the declared wiring files likely do not exist yet and need to be created. The testing framework is described as 'JUnit 8 for Qt-compatible C++' which in practice means Qt Test (QTest) framework used in a JUnit-compatible manner.

## Files to create
- test/unit/ArithmeticOperationsTest.cpp
- test/integration/MultiplicationIntegrationTest.cpp
- test/e2e/MultiplicationE2ETest.cpp

## Files to modify
- (none)

## Files to read (before editing)
- Calculator/ArithmeticOperations.h
- Calculator/ArithmeticOperations.cpp
- Calculator/MainWindow.h
- Calculator/MainWindow.cpp
- Calculator/MultiplicationLogic.h
- Calculator/MultiplicationLogic.cpp
- Calculator/CMakeLists.txt
- CMakeLists.txt

## Implementation order
1. 1. Read existing Calculator source files (ArithmeticOperations.h/cpp, MainWindow.h/cpp, any multiplication-specific headers) to understand the API surface and signal/slot structure.
2. 2. Read project build files (CMakeLists.txt) to understand how tests are compiled and linked.
3. 3. Create test/unit/ArithmeticOperationsTest.cpp: implement QTest-based unit tests for multiplication covering normal cases (positive integers, decimals), zero multiplication, negative operands, identity (multiply by 1), large values near overflow/LLONG_MAX/DBL_MAX, and floating-point precision edge cases.
4. 4. Create test/integration/MultiplicationIntegrationTest.cpp: implement QTest-based integration tests that instantiate the MainWindow or relevant UI widget, trigger the multiplication operation via the widget's public slots or UI interaction helpers (QTest::mouseClick / QTest::keyClick), and verify that the display/output reflects correct multiplication results.
5. 5. Create test/e2e/MultiplicationE2ETest.cpp: implement QTest-based end-to-end tests that simulate a complete user session — launching the app widget, entering operands via simulated button clicks or key events, pressing the multiply operator and equals, and asserting the displayed result matches expected output for multiple scenarios.
6. 6. Verify all three files use QTEST_MAIN or are structured for inclusion in the test harness consistent with the project's existing test conventions.

## Acceptance criteria mapping
- AC: AC1: Multiplication tests verify function's correctness across all expected scenarios. → Steps 3, 4, and 5 together implement unit, integration, and E2E tests covering normal inputs, edge cases (zero, negatives, overflow, floating-point precision), UI integration via signals/slots, and full end-to-end user interaction simulation.

## Out of scope (do NOT do)
- Do not modify any Calculator source files (ArithmeticOperations.cpp, MainWindow.cpp, etc.) — tests only.
- Do not create any new directories beyond the declared test/unit, test/integration, test/e2e paths.
- Do not add or modify CMakeLists.txt or build files unless strictly required to register the test targets (read first to determine if already configured).
- Do not implement tests for any operation other than multiplication (addition, subtraction, division are out of scope for this task).
- Do not introduce mock frameworks or third-party testing libraries beyond Qt Test.
- Do not create any files under tests/ (the other directory seen in the repo) — use only the declared wiring paths.

## Rationale
All three files are explicitly declared in the wiring list and the repo map shows 0 existing files, confirming they must be created. No additional files are needed as the task is purely about writing tests for an already-implemented feature. The filesToModify list is empty because no existing shared files require updating for test addition. CMakeLists.txt is listed in filesToRead only — it will be modified only if inspection reveals the test targets are not yet registered, which is a conditional action to be decided by the implementer after reading.
