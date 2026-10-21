#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Define the Mealy machine states
typedef enum { S0, S1, S2, S3, S4, S_DEAD } State;

// Helper function to convert State enum to a string for printing
const char* getStateName(State s) {
    switch (s) {
        case S0: return "S0";
        case S1: return "S1";
        case S2: return "S2";
        case S3: return "S3";
        case S4: return "S4";
        case S_DEAD: return "S_Dead";
        default: return "Unknown";
    }
}

void check_start_and_end_comment() {
    char user_input[1024];

    printf("=== Start '/*' and End '*/' Recognizer ===\n");
    printf("Type 'exit' or 'quit' to stop.\n\n");

    while (true) {
        printf("Enter text to check: ");

        // Read input and check for EOF
        if (fgets(user_input, sizeof(user_input), stdin) == NULL) {
            break;
        }

        // Remove trailing newline character left by fgets
        size_t len = strlen(user_input);
        if (len > 0 && user_input[len - 1] == '\n') {
            user_input[len - 1] = '\0';
            len--;
        }

        // Convert to lowercase to check for exit/quit
        char lower_input[1024];
        for (size_t i = 0; i <= len; i++) {
            lower_input[i] = tolower((unsigned char)user_input[i]);
        }

        if (strcmp(lower_input, "exit") == 0 || strcmp(lower_input, "quit") == 0) {
            break;
        }

        if (len == 0) {
            printf("REJECTED: Empty input.\n\n");
            continue;
        }

        State current_state = S0;
        State states_visited[1024];
        int outputs[1024];
        int step = 0;

        // Record the initial state
        states_visited[step] = current_state;
        step++;

        // Process each character
        for (size_t i = 0; i < len; i++) {
            char c = user_input[i];
            char in_type;

            if (c == '/') in_type = '/';
            else if (c == '*') in_type = '*';
            else in_type = 'O'; // Other

            int output = 0;

            // FSM Logic
            switch (current_state) {
                case S0:
                    if (in_type == '/') current_state = S1;
                    else current_state = S_DEAD;
                    break;
                case S1:
                    if (in_type == '*') current_state = S2;
                    else current_state = S_DEAD;
                    break;
                case S2:
                    if (in_type == '*') current_state = S3;
                    else current_state = S2;
                    break;
                case S3:
                    if (in_type == '/') {
                        current_state = S4;
                        output = 1; // Valid ending sequence found
                    }
                    else if (in_type == '*') current_state = S3;
                    else current_state = S2;
                    break;
                case S4:
                    if (in_type == '*') current_state = S3;
                    else current_state = S2;
                    break;
                case S_DEAD:
                    current_state = S_DEAD;
                    break;
            }

            states_visited[step] = current_state;
            outputs[step - 1] = output;
            step++;
        }

        // Evaluate acceptance
        const char* remarks;
        if (current_state == S4) {
            remarks = "ACCEPTED: Started with /* and ended with */.";
        } else if (current_state == S_DEAD) {
            remarks = "REJECTED: Did not start with /*.";
        } else {
            remarks = "REJECTED: Started with /* but did not end with */.";
        }

        // Print results
        printf("\n--- Results ---\n");
        printf("Input   : %s\n", user_input);

        printf("States  : ");
        for (int i = 0; i < step; i++) {
            printf("%s", getStateName(states_visited[i]));
            if (i < step - 1) printf(" -> ");
        }
        printf("\n");

        printf("Outputs : ");
        if (step > 1) {
            for (int i = 0; i < step - 1; i++) {
                printf("%d", outputs[i]);
                if (i < step - 2) printf(", ");
            }
        } else {
            printf("None");
        }
        printf("\n");

        printf("Remarks : %s\n", remarks);
        printf("--------------------------------------------------\n\n");
    }
}

int main() {
    check_start_and_end_comment();
    return 0;
}