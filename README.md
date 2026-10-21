# Mealy Machine C-Style Comment Recognizer

This project is a C program that implements a finite state machine (FSM) using the Mealy machine format. It evaluates a string of characters and determines if it perfectly fits the criteria of a C-style comment (strictly starting with `/*` and ending with `*/`).

## Features
*   **Interactive Input:** Continuously prompts the user for text to evaluate.
*   **Detailed FSM Tracing:** Displays the exact sequence of state transitions ($S_0 \rightarrow S_1 \dots$) the machine goes through.
*   **Mealy Machine Output:** Shows the output (0 or 1) for each step, outputting `1` only when the closing `*/` is successfully recognized.
*   **Strict Evaluation:** Ensures the string starts with `/*` and ends exactly with `*/`, dropping into a Dead State if the start is invalid.

## Requirements
*   A C compiler (like GCC / MinGW).

## How to Compile and Run

1. Open your terminal in the project directory.
2. Compile the C file using GCC:
   ```bash
   gcc mealy_pacot.c -o mealy_pacot.exe
