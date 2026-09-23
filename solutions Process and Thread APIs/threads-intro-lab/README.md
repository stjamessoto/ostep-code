# Introduction to Threads — Simulator Lab (10 questions)

Source: `threads-intro.pdf`, "Concurrency: An Introduction", Homework
(Simulation) section.

This lab is not compiled C code — it's a set of runs against the
`x86.py` instruction-level thread simulator and its `.s` assembly
snippets, which already live in this repo at
[`../../HW-ThreadsIntro/`](../../HW-ThreadsIntro/) (`x86.py`, `loop.s`,
`looping-race-nolock.s`, `wait-for-me.s`, `simple-race.s`,
`README-race`). Nothing here needs to be duplicated; `ANSWERS.md` in
this folder documents each of the 10 questions with the exact command
run and the real captured output.

**Important:** `x86.py` is written for Python 2 (it uses the old
`print` statement). On this machine that meant installing Python 2:

```
prompt> apt-get install -y python2
```

All commands below were run from `HW-ThreadsIntro/` as:

```
prompt> python2 x86.py ...
```

(swap in plain `python` if your system's default `python` is Python 2).
For the submitted report, add a terminal screenshot of each command
next to its answer.

See `ANSWERS.md` for the full write-up.
