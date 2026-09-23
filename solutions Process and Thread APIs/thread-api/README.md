# Thread API — Homework (Code): 5 of 9 questions, using helgrind

Source: `threads-api.pdf`, "Interlude: Thread API", Homework (Code)
section (the assignment says "answer 5 questions of your choice").

Chosen questions: **1, 2, 4, 6, 9** (spanning all 5 provided programs:
the race, both deadlock programs, and both signaling programs).

## Files

The four programs the *unmodified* questions run against
(`main-race.c`, `main-deadlock.c`, `main-deadlock-global.c`,
`main-signal.c`, `main-signal-cv.c`, and their shared `mythreads.h`)
already exist in this repo at
[`../../HW-Threads-RealAPI/`](../../HW-Threads-RealAPI/) — that's the
provided homework skeleton, so they aren't duplicated here.

This folder adds the three *new* files Question 2 asks for (modified
copies of `main-race.c`):

- `main-race-removed-line.c` — one of the two racing updates deleted
- `main-race-locked-one.c` — a lock added around only one update (still buggy)
- `main-race-locked-both.c` — a lock added around both updates (fixed)

Build with `make` (needs `-pthread`); each needs `gcc ... -pthread`,
same as the original Makefile in `HW-Threads-RealAPI/`.

## Tools

This machine didn't have `valgrind` installed; it was added with:

```
prompt> apt-get install -y valgrind
```

All helgrind output below is real, from
`valgrind --tool=helgrind ./<program>` on Ubuntu 22.04 / valgrind 3.18.1.

See `ANSWERS.md` for the full write-up. For the submitted report, add a
terminal screenshot of each `make`/`valgrind` invocation next to its
answer.
