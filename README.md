# NFA to DFA Conversion

This project implements the conversion of a Non-deterministic Finite Automaton (NFA) into a Deterministic Finite Automaton (DFA) using C++. It takes an NFA's states, transitions, and alphabet as input, computes the epsilon-closure, and constructs the corresponding DFA.

## Features

- Computes epsilon-closure for each state.
- Handles epsilon transitions (represented by `$`).
- Outputs the number of unique DFA states generated from the NFA.

## How It Works

1. **Epsilon-closure (ε-closure)**: For each state, the program computes the set of all states that can be reached via epsilon transitions.
2. **Move Function**: For each state and symbol in the alphabet, the move function is calculated to determine which states are reachable based on the current input symbol.
3. **Recursion**: The program recursively computes the epsilon-closures and stores the results to track visited states.
4. **State Labeling**: Each newly discovered set of states is assigned a label, and the process continues until all states are processed.

## Input Format

The program expects the following input format:

1. Number of states
2. List of state names
3. Number of symbols in the alphabet
4. Alphabet symbols
5. Number of final states
6. List of final states
7. Number of transitions
8. Transitions in the format: `state,symbol,destination`

### Example Input

```bash
3 q0 q1 q2 2 a b 1 q2 4 q0,$,q1 q1,a,q2 q2,b,q0 q0,a,q2
```


### Explanation of the Input

- **States**: `q0`, `q1`, `q2`
- **Alphabet**: `a`, `b`
- **Final State**: `q2`
- **Transitions**:
  - `q0` on `$` moves to `q1` (epsilon transition)
  - `q1` on `a` moves to `q2`
  - `q2` on `b` moves to `q0`
  - `q0` on `a` moves to `q2`

## Output

The program outputs the number of DFA states that have been constructed from the NFA.

## How to Run

1. Compile the C++ code:
   ```bash
   g++ -o nfa_to_dfa nfa_to_dfa.cpp
Run the program and provide input.
Enter the input in the expected format.

## Dependencies
- **C++ Standard Library**: Uses standard C++ libraries such as <iostream>, <vector>, <unordered_map>, <set>, and <sstream>.

## Project Structure
- *main()* function handles input processing and sets up the NFA.
- *dfs()* and dfs2() compute epsilon closures.
- *movefunc()* processes the transitions for each state and computes the DFA states.
- The program tracks visited states and their transitions, ensuring the DFA is fully generated.

## Future Improvements
- Add visualization of DFA states and transitions.
- Optimize for larger NFAs with more states and transitions.
