# Agent Plan — E2-S3-T3

_Generated: 2026-06-10T03:51:27.998Z_

## Ticket analysis
Task E2-S3-T3 requires integrating the MultiplicationUI with the multiplyNumbers logic inside CalculatorController. Specifically, an onMultiplyButtonClick event handler must be wired up to collect values from NumberInputFields, invoke the multiplyNumbers function, and display the result via the ResultDisplay component. The integration must follow MVVM principles using Qt's signal/slot mechanism, handle invalid input visually, and be covered by unit, integration, and E2E tests.

## Orientation
The repo has three relevant directories: components/, controllers/, and build_tests/. Prior commits established the Multiplication UI (E2-S3-T1) and Multiplication Logic (E2-S3-T2), and analogous work was done for Addition (E2-S1) and Subtraction (E2-S2). The wiring list identifies controllers/CalculatorController.tsx and components/ResultDisplay.tsx as the files to extend. The project is a Qt 6.10 / C++ monolith desktop app but the wiring uses .tsx extensions suggesting these are pseudo-paths used as logical identifiers in this repo. The priorAgentFiles show no new source files were created for T2 beyond the plan documents, so the implementation files likely need to be created/extended now.

## Files to create
- components/MultiplicationUI.h
- components/MultiplicationUI.cpp
- models/MultiplicationModel.h
- models/MultiplicationModel.cpp
- build_tests/test_multiplication_integration.cpp
- build_tests/test_multiplication_e2e.cpp

## Files to modify
- controllers/CalculatorController.tsx
- components/ResultDisplay.tsx
- build_tests/test_multiplication_unit.cpp

## Files to read (before editing)
- controllers/CalculatorController.tsx
- components/ResultDisplay.tsx
- build_tests/test_multiplication_unit.cpp
- REPO_MAP.md

## Implementation order
1. 1. Read REPO_MAP.md and existing files (CalculatorController.tsx, ResultDisplay.tsx, test_multiplication_unit.cpp) to understand current structure and conventions established by Addition and Subtraction slices.
2. 2. Create components/MultiplicationUI.h – declare QWidget-derived MultiplicationUI class with two QLineEdit NumberInputFields, a QPushButton for multiply, and signals/slots declarations.
3. 3. Create components/MultiplicationUI.cpp – implement MultiplicationUI constructor, layout setup, and emit a multiplyRequested(double, double) signal on button click with input validation (emit inputError(QString) on invalid input).
4. 4. Create models/MultiplicationModel.h – declare MultiplicationModel with multiplyNumbers(double, double) returning double and an error signal for invalid states.
5. 5. Create models/MultiplicationModel.cpp – implement multiplyNumbers with edge-case handling (e.g., overflow guard) and error emission.
6. 6. Modify controllers/CalculatorController.tsx – add MultiplicationUI instance and MultiplicationModel instance; wire MultiplicationUI::multiplyRequested to a new slot onMultiplyButtonClick that calls MultiplicationModel::multiplyNumbers, then calls ResultDisplay::showResult with the result; wire MultiplicationUI::inputError to ResultDisplay::showError.
7. 7. Modify components/ResultDisplay.tsx – ensure showResult(double) and showError(QString) slots/methods exist and display output correctly (extend if missing, following existing Addition/Subtraction pattern).
8. 8. Create build_tests/test_multiplication_integration.cpp – integration test verifying that invoking onMultiplyButtonClick with valid inputs produces correct output in ResultDisplay.
9. 9. Create build_tests/test_multiplication_e2e.cpp – E2E test simulating UI button click with two numeric inputs and asserting the displayed result matches expected multiplication output.
10. 10. Modify build_tests/test_multiplication_unit.cpp – add/confirm unit test that onMultiplyButtonClick triggers multiplyNumbers with correct arguments (mock/spy pattern).

## Acceptance criteria mapping
- AC: AC1: Multiplication initiated through UI inputs returns expected results. → Step 6 – CalculatorController.onMultiplyButtonClick collects inputs, calls MultiplicationModel::multiplyNumbers, and passes result to ResultDisplay::showResult. Verified by integration test in step 8 and E2E test in step 9.
- AC: AC2: Errors due to incorrect input are flagged and handled visually. → Step 3 – MultiplicationUI validates input and emits inputError; Step 6 – CalculatorController wires inputError to ResultDisplay::showError; Step 7 – ResultDisplay::showError displays the error message. Verified by unit test in step 10.

## Out of scope (do NOT do)
- Do not modify or duplicate Addition or Subtraction UI/logic files.
- Do not introduce a division or any other arithmetic operation.
- Do not change the build system (CMakeLists.txt or .pro files) unless they already exist and need a one-line addition for new .cpp files.
- Do not introduce cloud, authentication, or network code.
- Do not refactor existing Addition/Subtraction controller wiring.
- Do not rename or move existing files.

## Rationale
MultiplicationUI.h/.cpp are new files justified by E2-S3-T1 (Design Multiplication UI task) which established the UI component – they need to be created if not yet present. MultiplicationModel.h/.cpp are justified by E2-S3-T2 (Multiplication Logic task) to encapsulate the multiplyNumbers function in the MVVM model layer. The test files are required by the task's test requirements (unit, integration, E2E). CalculatorController.tsx and ResultDisplay.tsx are the declared wiring targets and must be extended to connect the UI and logic per MVVM. The .tsx extension is treated as the repo's naming convention for these logical files.
