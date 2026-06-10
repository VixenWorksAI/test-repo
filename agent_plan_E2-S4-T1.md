# Agent Plan — E2-S4-T1

_Generated: 2026-06-10T04:15:24.048Z_

## Ticket analysis
This task requires designing the Division UI within a Qt 6.10/C++ desktop calculator application. Two NumberInputFields and a DivideButton (labeled '/') must be created and integrated into the existing CalculatorUI layout. Input validation must restrict entries to numeric values only, and the DivideButton must visually reflect an active/pressed state. The wiring points to two existing files — app/layout.tsx and components/CalculatorUI.tsx — which appear to be TypeScript/React-style path aliases carried over from the task spec, but the actual implementation must be in C++/Qt idioms consistent with the architecture.

## Orientation
The repo has 0 total files currently tracked in the repo map, but prior agent commits show a pattern of building Qt C++ calculator components incrementally (Addition, Subtraction, Multiplication sprints). The declared wiring files (app/layout.tsx and components/CalculatorUI.tsx) use web-style naming conventions but reside in a Qt C++ project context — prior tasks suggest these map to Qt source files such as src/CalculatorUI.h, src/CalculatorUI.cpp, and a main.cpp or similar app entry. Given the prior agent files and commit history referencing multiplication UI design (E2-S3-T1), the division UI should follow the same pattern: extend CalculatorUI with division-specific QLineEdit inputs and a QPushButton for divide.

## Files to create
- components/CalculatorUI.h
- components/CalculatorUI.cpp
- app/main.cpp

## Files to modify
- app/layout.tsx
- components/CalculatorUI.tsx

## Files to read (before editing)
- app/layout.tsx
- components/CalculatorUI.tsx
- components/CalculatorUI.h
- components/CalculatorUI.cpp
- app/main.cpp

## Implementation order
1. 1. Read app/layout.tsx and components/CalculatorUI.tsx to understand any existing structure and conventions established by prior sprint tasks.
2. 2. Read components/CalculatorUI.h and components/CalculatorUI.cpp (if they exist) to understand current widget declarations and layout slots used for prior operations (add, subtract, multiply).
3. 3. Extend components/CalculatorUI.h to declare two QLineEdit members (divisionInput1, divisionInput2) with QDoubleValidator for numeric-only input, a QPushButton member (divideButton) labeled '/', and any active-state styling signals/slots.
4. 4. Extend components/CalculatorUI.cpp to initialize the two QLineEdit fields with QDoubleValidator applied, initialize the divideButton with '/' label, apply distinct stylesheet for the divide button and its active/pressed state (using Qt stylesheets with :pressed pseudo-state), and integrate all three widgets into the existing CalculatorUI layout section for division.
5. 5. Update app/layout.tsx (used as app entry/shell descriptor) to reflect that the division section is now part of the CalculatorUI layout.
6. 6. Update components/CalculatorUI.tsx (used as the UI component descriptor or Qt .ui equivalent) to include division row with two input fields and a divide button.
7. 7. Verify that the DivideButton emits a clicked() signal connected to a division slot placeholder (to be wired in a later task), and that the active state stylesheet is visually distinct.

## Acceptance criteria mapping
- AC: AC1: Division UI components are well-defined and integrated. → Step 4 — divisionInput1, divisionInput2, and divideButton are added and laid out within the CalculatorUI widget in CalculatorUI.cpp, and steps 5-6 update the layout/shell descriptors.
- AC: AC2: Input fields restrict entries exclusively to numeric inputs. → Step 4 — QDoubleValidator is applied to both divisionInput1 and divisionInput2, preventing non-numeric characters from being accepted.
- AC: AC3: Division button reflects active state appropriately. → Step 4 — divideButton is styled with a Qt stylesheet that includes a :pressed and :focus pseudo-state to visually distinguish the active state during user interaction.

## Out of scope (do NOT do)
- Implementing the actual division arithmetic logic (belongs to a later task, e.g., E2-S4-T2).
- Wiring the divideButton clicked() signal to a fully functional division backend slot.
- Writing unit, integration, or E2E test files for this task (test requirements say 'none' for unit/integration; E2E is descriptive).
- Creating any microservice, server, or cloud-connected component.
- Modifying CMakeLists.txt or build system files unless strictly required by file creation.
- Adding authentication or session management.
- Changing any existing addition, subtraction, or multiplication UI components.

## Rationale
The wiring list names app/layout.tsx and components/CalculatorUI.tsx, which are the authoritative files to extend. Because the project is a Qt 6.10/C++ desktop app, these files either serve as project-level descriptors or were bootstrapped with web-style names for agent tooling purposes — the implementation must produce valid Qt C++ code within them or in their paired .h/.cpp counterparts. filesToCreate includes CalculatorUI.h, CalculatorUI.cpp, and main.cpp only because the repo map shows 0 existing tracked files, meaning they likely need to be scaffolded for the first time in this sprint cycle; these are the idiomatic Qt source file locations. No parallel directory trees or React-style structures are introduced. The plan is conservative: only division UI elements are added, deferring all logic to subsequent tasks.
