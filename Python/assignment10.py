import tkinter as tk
import heapq
import time

# --- Configuration ---
CELL_SIZE = 25
DELAY = 10  # Milliseconds delay for visualization
BG_COLOR = "#2c3e50"
EMPTY_COLOR = "#ecf0f1"
WALL_COLOR = "#34495e"
START_COLOR = "#2ecc71"
GOAL_COLOR = "#e74c3c"
PATH_COLOR = "#f1c40f"
OPEN_SET_COLOR = "#3498db"
CLOSED_SET_COLOR = "#95a5a6"

# --- Maze Definition ---
# 0: Walkable Path, 1: Wall, 'S': Start, 'G': Goal
STATIC_MAZE = [
    ['S', 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
    [1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0],
    [0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0],
    [0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0],
    [0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0],
    [0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0],
    [0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0],
    [1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1],
    [0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0],
    [0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0],
    [0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0],
    [1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 'G'],
]

class Node:
    """A node class for A* Pathfinding"""
    def __init__(self, parent=None, position=None):
        self.parent = parent
        self.position = position  # Tuple (row, col)

        self.g = 0  # Cost from start to current node
        self.h = 0  # Heuristic cost from current node to end
        self.f = 0  # Total cost (g + h)

    def __eq__(self, other):
        return self.position == other.position

    def __lt__(self, other):
        return self.f < other.f

    def __hash__(self):
        return hash(self.position)

class MazeSolverApp:
    def __init__(self, root, maze):
        self.root = root
        self.root.title("AI Maze Solver (A*)")
        self.root.configure(bg=BG_COLOR)
        
        self.maze = [row[:] for row in maze] # Make a mutable copy
        self.rows = len(self.maze)
        self.cols = len(self.maze[0])
        self.is_solving = False

        self.canvas = tk.Canvas(root, 
                                width=self.cols * CELL_SIZE, 
                                height=self.rows * CELL_SIZE, 
                                bg=BG_COLOR, 
                                highlightthickness=0)
        self.canvas.pack(pady=20, padx=20)
        self.canvas.bind("<Button-1>", self.toggle_wall)

        self.controls_frame = tk.Frame(root, bg=BG_COLOR)
        self.controls_frame.pack(pady=10)

        self.solve_button = tk.Button(self.controls_frame, text="Solve Maze", command=self.solve_maze, font=("Helvetica", 12))
        self.solve_button.pack(side=tk.LEFT, padx=10)
        
        self.reset_button = tk.Button(self.controls_frame, text="Reset", command=self.reset_maze, font=("Helvetica", 12))
        self.reset_button.pack(side=tk.LEFT, padx=10)

        self.status_label = tk.Label(root, text="Click 'Solve Maze' to find the path.", bg=BG_COLOR, fg="white", font=("Helvetica", 10))
        self.status_label.pack(pady=5)
        
        self.draw_maze()

    def draw_maze(self, path=None, open_set=None, closed_set=None):
        """Draws the entire maze grid on the canvas."""
        self.canvas.delete("all")
        for row in range(self.rows):
            for col in range(self.cols):
                x1, y1 = col * CELL_SIZE, row * CELL_SIZE
                x2, y2 = x1 + CELL_SIZE, y1 + CELL_SIZE
                
                cell_type = self.maze[row][col]
                color = EMPTY_COLOR

                if cell_type == 1: color = WALL_COLOR
                elif cell_type == 'S': color = START_COLOR
                elif cell_type == 'G': color = GOAL_COLOR
                
                pos = (row, col)
                if closed_set and pos in closed_set: color = CLOSED_SET_COLOR
                if open_set and pos in open_set: color = OPEN_SET_COLOR
                if path and pos in path: color = PATH_COLOR
                
                # Redraw start and goal over path/sets
                if cell_type == 'S': color = START_COLOR
                if cell_type == 'G': color = GOAL_COLOR

                self.canvas.create_rectangle(x1, y1, x2, y2, fill=color, outline=BG_COLOR)
        self.root.update_idletasks()

    def reset_maze(self):
        """Resets the maze to its initial state."""
        if self.is_solving:
            return
        self.maze = [row[:] for row in STATIC_MAZE]
        self.status_label.config(text="Maze reset. Click on cells to add/remove walls.")
        self.draw_maze()

    def toggle_wall(self, event):
        """Allows user to add/remove walls in the maze (dynamic aspect)."""
        if self.is_solving:
            return
        col = event.x // CELL_SIZE
        row = event.y // CELL_SIZE

        if 0 <= row < self.rows and 0 <= col < self.cols:
            cell = self.maze[row][col]
            if cell == 0:
                self.maze[row][col] = 1
            elif cell == 1:
                self.maze[row][col] = 0
            # Cannot change Start or Goal
            
            self.draw_maze()
            self.status_label.config(text="Maze updated. Click 'Solve Maze' to find the new path.")

    def solve_maze(self):
        """Initiates the A* search algorithm."""
        if self.is_solving:
            return
            
        self.is_solving = True
        self.solve_button.config(state=tk.DISABLED)
        self.reset_button.config(state=tk.DISABLED)
        self.status_label.config(text="Solving...")
        
        start_pos, goal_pos = None, None
        for r in range(self.rows):
            for c in range(self.cols):
                if self.maze[r][c] == 'S': start_pos = (r, c)
                if self.maze[r][c] == 'G': goal_pos = (r, c)
        
        if not start_pos or not goal_pos:
            self.status_label.config(text="Error: Start or Goal not found in maze.")
            self.is_solving = False
            return

        self.a_star_visual(start_pos, goal_pos)

    def a_star_visual(self, start, end):
        """A* search algorithm with visualization hooks."""
        start_node = Node(None, start)
        end_node = Node(None, end)
        
        open_list = []
        closed_set = set()
        
        heapq.heappush(open_list, start_node)
        
        def process_step():
            if not open_list:
                self.status_label.config(text="No path found!")
                self.is_solving = False
                self.solve_button.config(state=tk.NORMAL)
                self.reset_button.config(state=tk.NORMAL)
                return

            current_node = heapq.heappop(open_list)
            closed_set.add(current_node.position)
            
            # Draw current state of open and closed sets
            open_set_pos = {node.position for node in open_list}
            self.draw_maze(open_set=open_set_pos, closed_set=closed_set)

            if current_node == end_node:
                path = []
                current = current_node
                while current is not None:
                    path.append(current.position)
                    current = current.parent
                path = path[::-1] # Reverse path
                self.draw_maze(path=path)
                self.status_label.config(text=f"Path found! Length: {len(path)}")
                self.is_solving = False
                self.solve_button.config(state=tk.NORMAL)
                self.reset_button.config(state=tk.NORMAL)
                return

            children = []
            for new_position in [(0, -1), (0, 1), (-1, 0), (1, 0)]: # Neighbors
                node_position = (current_node.position[0] + new_position[0],
                                 current_node.position[1] + new_position[1])

                if not (0 <= node_position[0] < self.rows and 0 <= node_position[1] < self.cols):
                    continue
                if self.maze[node_position[0]][node_position[1]] == 1:
                    continue
                if node_position in closed_set:
                    continue
                
                new_node = Node(current_node, node_position)
                children.append(new_node)
            
            for child in children:
                child.g = current_node.g + 1
                child.h = ((child.position[0] - end_node.position[0]) ** 2) + \
                          ((child.position[1] - end_node.position[1]) ** 2) # Euclidean distance
                child.f = child.g + child.h

                if any(child == open_node and child.g > open_node.g for open_node in open_list):
                    continue

                heapq.heappush(open_list, child)
            
            self.root.after(DELAY, process_step)
        
        # Start the recursive visualization loop
        process_step()
        
        
root = tk.Tk()
app = MazeSolverApp(root, STATIC_MAZE)
root.mainloop()