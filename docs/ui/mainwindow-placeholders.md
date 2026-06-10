# MainWindow Placeholder Standard (E1-S3-T4)

This document describes the placeholder contract used in `forms/mainwindow.ui` to
mark UI elements that are reserved for future logic from the Arithmetic
Operations epic (E2). It is consumed by the E2 epic to know exactly which
widgets to wire and how the data flow is expected to behave.

## Marker convention

Placeholders are tagged with Qt Designer XML comments in the form:

```
<!-- TODO(E2): <intent> -->
```

The comment is placed directly above the `<widget>` element it documents, so
Qt Designer preserves it when the file is re-opened or re-saved. The `(E2)`
epic tag lets the future epic locate its integration points with a single
search (`grep "TODO(E2)" forms/mainwindow.ui`).

## Tagged placeholders

| Widget         | Role in E2                                       | Expected signal           | Expected slot target       |
|----------------|--------------------------------------------------|---------------------------|----------------------------|
| `displayEdit`  | Result channel (read-only line edit)             | value updates via `setText(QString)` | `MainWindow::onDisplayChanged` (or equivalent) |
| `buttonAdd`    | Addition operator                                | `clicked()`               | `MainWindow::onAddClicked` |
| `buttonSubtract` | Subtraction operator                          | `clicked()`               | `MainWindow::onSubtractClicked` |
| `buttonMultiply` | Multiplication operator                        | `clicked()`               | `MainWindow::onMultiplyClicked` |
| `buttonDivide` | Division operator                                | `clicked()`               | `MainWindow::onDivideClicked` |
| `buttonEquals` | Evaluation / result trigger                      | `clicked()`               | `MainWindow::onEqualsClicked` |

Numeric input buttons (`button0`..`button9`, `buttonDot`, `buttonSign`,
`buttonBackspace`, `buttonClear`, `buttonClearAll`) and the memory column
(`buttonMC`, `buttonMR`, `buttonMS`, `buttonMPlus`, `buttonMMinus`) are not
tagged: their interaction protocols are fully resolved inside MainWindow and
do not require E2 coordination.

## Data flow expectation

The E2 epic must conform to the following assumptions that are already baked
into the placeholder contract:

1. `displayEdit` is the single source of truth for the visible numeric state.
   Logic writes results back to it through `setText`; logic never reads from
   the widget's `text()` to recover state.
2. The `MainWindow` class owns the slot methods that the E2 epic will connect
   to each operator's `clicked()` signal. E2 should not introduce new QObject
   subclasses for slot hosting.
3. Operator and equals buttons are pure event sources: their `checkable`
   property is unused and they do not retain state. E2 logic lives in the
   `MainWindow` slots, not in the buttons.
4. The placeholder tags remain in the file until E2 lands the corresponding
   slot and removes the marker. A marker is removed only when the wiring
   (signal-to-slot connection) is in place, not when the slot body is written.

## Removing a marker

When E2 wires a placeholder, delete the `<!-- TODO(E2): ... -->` line that
sits immediately above that widget in `forms/mainwindow.ui`. Do not move the
marker to a different file and do not replace it with a different comment
style: the convention above is the contract.
