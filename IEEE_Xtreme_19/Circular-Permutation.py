// Circular Permutation (100% Acceptance)
// Time limit: 2500 ms Memory limit: 256 MB
// Josh is organizing a party and has invited N of his friends. The friends are numbered in increasing order of their heights (1 is the shortest, 2 is the second shortest, ..., N is the tallest). The setup of the party requires the N friends to seat at a round table, in increasing order of their heights, either clockwise or anti-clockwise.
// Unfortunately, when the friends arrived they chose to sit in an arbitrary way. Josh will ask some of them to move to other seats, in order to satisfy the setup of the party. Each friend will move around the table from their initial seat to the designated seat either clockwise or anti- clockwise, whichever route is shorter. Josh would like to minimize the longest distance travelled by any of his friends.
// Standard input
// The first line contains a single integer N.
// The second line contains a permutation of size N, representing the initial seating of Josh's friends.
// Standard output
// Print a single integer, representing the minimum longest distance travelled by any of Josh's friends, in order to get a correct seating configuration.
// Constraints and notes
// .3≤ N ≤ 105
// Input
// Output
// Explanation
// The guests are already seated in a valid order.
// 5 m
// 0
// 3 2 1 5 4
// 7
// 4 2 7 1 5 6 3
// 1
// 4
// 10
// 10 1 9 2 8 3 7 4 5 6
// The final configuration will be:
// 3217654

import sys

def solve():
    # Read N
    try:
        n_str = sys.stdin.readline()
        if not n_str:
            return  # Handle EOF
        N = int(n_str)
    except EOFError:
        return
    except Exception as e:
        return

    # Read the permutation
    P = list(map(int, sys.stdin.readline().split()))

    # 1. Create initial_pos array
    # initial_pos[j] = seat of friend j
    initial_pos = [0] * (N + 1)
    for i in range(N):
        initial_pos[P[i]] = i

    # 2. Create point sets for clockwise and anti-clockwise cases
    d_points = []  # Clockwise
    e_points = []  # Anti-clockwise

    for j in range(1, N + 1):
        # Clockwise: d_j = (initial_pos[j] - j + 1) % N
        d_j = (initial_pos[j] - j + 1 + N) % N
        d_points.append(d_j)

        # Anti-clockwise: e_j = (initial_pos[j] + j - 1) % N
        e_j = (initial_pos[j] + j - 1) % N
        e_points.append(e_j)

    # 3. Define the 1-center problem solver
    def solve_1_center(points):
        n = len(points)
        
        # Sort the points
        points.sort()

        # Create the doubled array
        doubled_points = points + [p + n for p in points]

        # Find the minimum covering arc length (min_length)
        min_length = N  # Max possible length
        for i in range(n):
            length = doubled_points[i + n - 1] - doubled_points[i]
            min_length = min(min_length, length)

        # The answer is ceil(min_length / 2)
        return (min_length + 1) // 2

    # 4. Calculate answers for both cases
    ans_cw = solve_1_center(d_points)
    ans_acw = solve_1_center(e_points)

    # 5. Print the minimum of the two
    print(min(ans_cw, ans_acw))

# Call the solve function to run the program
solve()