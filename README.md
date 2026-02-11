# TO-DO

**Version 1.0**  
Simple TUI-based daily task tracking application written in **C**

A minimal, terminal-only to-do list program.  
No external libraries. Just standard C.

Tasks are stored in plain text files and shown with this style:
- [[3]]   Finish math assignment
- [[7]]   Buy groceries before 8 PM
- [[x]]   Water the plants
- [[x]]   Call dentist
text - `[[x]]` → completed task  
- `[[number]]` → pending task (use the number with `done` / `delete`)

## Commands
1. add "task description"          →  add new task
2. done <number>                   →  mark task as done
3. delete <number>                 →  remove incomplete task
4. clear                           →  remove all completed tasks
5. delete all                      →  delete everything (confirmation needed?)
6. show task                       →  show all tasks (default)
7. show incomplete                 →  show only pending tasks
8. show complete   /  show done    →  show only completed tasks
9. help                            →  show this help
10. exit                            →  save & quit
textType `help` inside the program to see the command list.

## Project File Structure
```
TO-DO
├── README.md              # this file
├── main.c                 # main source code
├── main                   # compiled binary (gitignored or not committed)
├── incomplete.txt         # pending tasks
├── complete.txt           # finished tasks
└── help.txt               # help text shown by help command
```
textData is kept in two separate files:
- `incomplete.txt` — tasks that are not yet done
- `complete.txt`   — tasks marked as done

This separation makes `clear` very fast (just truncate `complete.txt`).

## Build & Run

```bash
# clone
git clone https://github.com/tanvir-techbro/TO-DO.git

#get in the folder
cd TO-DO

# Run
./todo
```

## Features / Design Notes:

- Very small binary size.
- No ncurses / no curses dependency.
- Human-readable plain text storage.
- Completed tasks are preserved until you run clear.
- Simple numbered reference system.
- Runs in any terminal (even very basic ones).

All contributions are welcome. Fork it and contribute to it as much as you wish.

License
MIT License
