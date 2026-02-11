**TO-DO**, version 1.0.
TUI based simple daily task tracking application.
Commands are defined internally type `help` to see the list.
Completed tasks have **[[x]]** in front of them. Completed tasks can not be individually deleted.
Incomplete tasks have **[[(task number)]]** in front of them. Incomplete tasks can be individually deleted.

*Commands :-*

`add` - Adds new task. [add "task you need to add"]
`done` - Marks a task as done. [done (task number, for example 1)]
`clear` - Deletes all the done tasks. [clear]
`delete` - Deletes an incomplete task. [delete (task number, for example 1)]
`delete all` - Deletes all complete and incomplete tasks. [delete all]

`show task` - Shows all complete and incomplete tasks. [show task]
`show incomplete` - Shows all incomplete tasks. [show incomplete]
`show complete/done` - shows all Completed/Done tasks. [show done], [show complete]

`exit` - Saves changes and exits app. [exit]
