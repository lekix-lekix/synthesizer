#!/usr/bin/env python3
import sys

data = []
for line in sys.stdin:
    line = line.strip()
    if line:
        try:
            data.append(float(line))
        except ValueError:
            pass

if len(data) < 2:
    print("Error: need at least 2 numeric values on stdin")
    sys.exit(1)

WIDTH = 60
HEIGHT = 20

min_val = min(data)
max_val = max(data)
val_range = max_val - min_val

if val_range == 0:
    print("Error: all values are identical")
    sys.exit(1)

# Build grid
grid = [[' ' for _ in range(WIDTH)] for _ in range(HEIGHT)]

# Plot and connect points
for i, val in enumerate(data):
    x = int(i * (WIDTH - 1) / (len(data) - 1))
    y = HEIGHT - 1 - int((val - min_val) / val_range * (HEIGHT - 1))
    grid[y][x] = '●'

for i in range(len(data) - 1):
    x1 = int(i * (WIDTH - 1) / (len(data) - 1))
    x2 = int((i + 1) * (WIDTH - 1) / (len(data) - 1))
    y1 = HEIGHT - 1 - int((data[i] - min_val) / val_range * (HEIGHT - 1))
    y2 = HEIGHT - 1 - int((data[i + 1] - min_val) / val_range * (HEIGHT - 1))

    steps = max(abs(x2 - x1), abs(y2 - y1))
    for s in range(1, steps):
        x = int(x1 + s * (x2 - x1) / steps)
        y = int(y1 + s * (y2 - y1) / steps)
        if grid[y][x] == ' ':
            dx = x2 - x1
            dy = y2 - y1
            if abs(dx) > abs(dy) * 2:
                grid[y][x] = '─'
            elif abs(dy) > abs(dx) * 2:
                grid[y][x] = '│'
            elif (dx > 0 and dy < 0) or (dx < 0 and dy > 0):
                grid[y][x] = '╱'
            else:
                grid[y][x] = '╲'

# Zero line row
zero_row = None
if min_val <= 0 <= max_val:
    zero_row = HEIGHT - 1 - int((0 - min_val) / val_range * (HEIGHT - 1))

print()
for r in range(HEIGHT):
    val_at_row = max_val - r * val_range / (HEIGHT - 1)
    if r == 0 or r == HEIGHT - 1 or r == zero_row:
        label = f"{val_at_row:8.4f} │"
    else:
        label = "         │"

    if r == zero_row:
        row_str = ''.join('·' if c == ' ' else c for c in grid[r])
    else:
        row_str = ''.join(grid[r])

    print(label + row_str)

print("         └" + "─" * WIDTH)
print(f"          0{' ' * (WIDTH//2 - 3)}index{' ' * (WIDTH//2 - 3)}{len(data)-1}")
print(f"\n  min: {min_val:.7f}   max: {max_val:.7f}   n={len(data)}")
print()
