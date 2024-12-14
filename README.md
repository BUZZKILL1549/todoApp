# ToDo App
It's a C++-based console To-Do app. It's just a little project I wanted to do to kinda refresh my C++ knowledge.
It uses SQLite3 under the hood for several reasons:
- SQLite3 is pre-installed
- SQLite3 is easy-to-use (for me, cuz I'm not very good at C++)

For instructions on running the app:
~~~
$ ./todo -h
~~~
will present a nice little page with instructions on finer commands, but basically, it goes like this:
~~~
$ ./todo <command> [options]
~~~
where <command> is one of 3 (add, list, delete)
and options is one of 2 (-h, -p) where -p stands for priority.
You can set priorities when you add a task:
~~~
$ ./todo add <taskName> -p 1
~~~
As for the priorities, use whatever convention you want (0 - 5, 1 - 5, etc.).

This:
~~~
$ ./todo list
~~~
just lists all the stored tasks and doesn't need any additional arguments.

To delete a task:
~~~
$ ./todo delete <taskNum>
~~~
where <taskNum> is obtained by using the list command.
