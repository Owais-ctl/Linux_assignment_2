# Question 5: Vi/Vim Failure Recovery Analysis

## Evaluation of Recovery Mechanisms

| Mechanism | Description | Survival Across Crash |
| :--- | :--- | :--- |
| **Swap Files (`.swp`)** | Hidden pointer files tracking uncommitted buffer changes at the block level. | **Yes** |
| **Undo History (`undodir`)** | Disk-persisted change history across editing sessions. | **Yes** |
| **Volatile Registers** | In-memory scratchpads used for copy (`yank`) and delete buffers. | **No** |
| **Backup Files (`~`)** | Pre-session file duplicates generated prior to write actions. | **Partial** (Lacks latest delta) |

---

## Proposed Optimal Strategy

The **Swap File Recovery Strategy (`vi -r filename`)** remains the most resilient mechanism for recovering uncommitted changes following a power loss or crash event.

### Key Justifications
1. **Real-Time Block Writes:** Unlike standard backup routines triggered only during explicit saving events (`:w`), `.swp` structures update dynamically on keystrokes and timer intervals.
2. **Delta Capture:** Captures modified buffer delta states present only in RAM prior to the crash, ensuring minimal work loss upon system restart.