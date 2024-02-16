class State:
    def _init_(self, missionaries, cannibals, boat_position):
        self.missionaries = missionaries
        self.cannibals = cannibals
        self.boat_position = boat_position

    def is_valid(self):
        if (
            0 <= self.missionaries <= 3
            and 0 <= self.cannibals <= 3
            and 0 <= self.boat_position <= 1
        ):
            if (
                self.missionaries == 0
                or self.missionaries == 3
                or self.missionaries >= self.cannibals
            ):
                return True
        return False

    def is_goal(self):
        return self.missionaries == 0 and self.cannibals == 0 and self.boat_position == 0

    def _eq_(self, other):
        return (
            self.missionaries == other.missionaries
            and self.cannibals == other.cannibals
            and self.boat_position == other.boat_position
        )

    def _hash_(self):
        return hash((self.missionaries, self.cannibals, self.boat_position))


def generate_next_states(current_state):
    next_states = []
    moves = [(1, 0), (2, 0), (0, 1), (0, 2), (1, 1)]

    for m, c in moves:
        if current_state.boat_position == 1:
            new_state = State(
                current_state.missionaries - m,
                current_state.cannibals - c,
                0,
            )
        else:
            new_state = State(
                current_state.missionaries + m,
                current_state.cannibals + c,
                1,
            )

        if new_state.is_valid():
            next_states.append(new_state)

    return next_states


def dfs_search():
    start_state = State(3, 3, 1)
    goal_state = State(0, 0, 0)

    stack = [(start_state, [])]
    visited = set()

    while stack:
        current_state, path = stack.pop()

        if current_state.is_goal():
            return path

        if current_state not in visited:
            visited.add(current_state)

            next_states = generate_next_states(current_state)
            for next_state in next_states:
                if next_state not in visited:
                    stack.append((next_state, path + [current_state]))

    return None


def print_state_description(state):
    left_shore = f"{state.missionaries} Missionaries and {state.cannibals} Cannibals on the Left Shore"
    right_shore = f"{3 - state.missionaries} Missionaries and {3 - state.cannibals} Cannibals on the Right Shore"

    print(f"{left_shore}, {right_shore}\n")


if _name_ == "_main_":
    solution_path = dfs_search()

    if solution_path:
        print("Solution Path:")
        for i, state in enumerate(solution_path):
            print(f"Step {i + 1}:")
            print_state_description(state)

    else:
        print("No solution found.")
