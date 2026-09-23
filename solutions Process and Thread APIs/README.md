# Solutions — Process and Thread APIs (CS375 A5)

Maps to the three sections of the assignment (`09 - CS375 - A5 -
Process and Thread APIs`):

| Assignment section | Solution folder | What's in it |
|---|---|---|
| Introduction to Threads — lab (10 questions) | [`threads-intro-lab/`](threads-intro-lab/) | `ANSWERS.md`: all 10 questions answered against the real `x86.py` simulator in [`../HW-ThreadsIntro/`](../HW-ThreadsIntro/) |
| Process API — questions 1–6 | [`process-api/`](process-api/) | `question1.c`–`question6.c` (compiled, run, verified) + `REPORT.md` |
| Thread API — 5 questions of your choice | [`thread-api/`](thread-api/) | 3 new `main-race-*.c` variants (Q2) + `ANSWERS.md` covering Q1, 2, 4, 6, 9, run against helgrind on the provided programs in [`../HW-Threads-RealAPI/`](../HW-Threads-RealAPI/) |

## How this maps to the chapters

- **Introduction to Threads** (`threads-intro.pdf`) — its homework is
  the `x86.py` instruction-level simulator, not code you compile, so
  `threads-intro-lab/ANSWERS.md` documents each of the 10 questions
  with the actual command run and the real simulator output/trace.
- **Process API** (`cpu-api.pdf`) — its "Homework (Code)" section has 8
  questions; the assignment asks for questions 1–6, which are the
  `fork()`/`wait()`/`exec()` programs in `process-api/`.
- **Thread API** (`threads-api.pdf`) — its "Homework (Code)" section
  has 9 questions, all built around `helgrind` and 5 provided programs
  (`main-race.c`, `main-deadlock.c`, `main-deadlock-global.c`,
  `main-signal.c`, `main-signal-cv.c`, from the `HW-Threads-RealAPI`
  download). The assignment asks for 5 of your choice; `thread-api/`
  answers **1, 2, 4, 6, 9**, which together exercise all 5 programs.

## Tools that had to be installed in this environment

- `python2` — `x86.py` is Python-2-only (old `print` syntax).
- `valgrind` — provides `helgrind`, used for the Thread API questions.
- `make` — wasn't installed either; needed for every folder's Makefile
  (including the ones already in this repo, e.g. `cpu-api/`,
  `threads-api/`, `threads-intro/`).

All three were installed with `apt-get install -y <pkg>`.

## For the report (PDF) you submit on Canvas

Per the assignment's "Submission Requirements": submit each `.c` file
individually (not zipped), plus a PDF report with your answers,
**screenshots of compiling and running each program**, and
explanations. The `REPORT.md` / `ANSWERS.md` files in each folder below
already have the verified output and explanations written out — when
building the PDF, re-run each `make` / program / `valgrind` command
yourself and paste in a terminal screenshot next to the matching
section, since the assignment specifically asks for screenshots (which
can't be produced here).
