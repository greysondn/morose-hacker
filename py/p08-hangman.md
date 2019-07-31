---
layout: page
title: Python Problem 08 - Hangman
permalink: /py/p08
---

I'd like to hang with you and all, but this guy keeps guessing what's on my mind.

{% include infobox_head.html type="caution" title="Writing in Progress" %}
This lesson was rapidly adapted via copy+paste and patchwork from the related C++ lesson. As a side effect, some things may have been missed or may still refer to their C++ counterparts.
{% include infobox_tail.html %}

<a name="p08-hangman"></a>Problem 08: Hangman
=============================================

This problem assumes you understand up to Lesson 9 (Functions) of the Python series. It may be prudent to also do Lesson 10 (Standard Doc Comments) as well.

Create a program to play the game hangman. There cannot be two players; it is one player against the computer's chosen word. the word must be randomly selected from a list of words. A list of ten possible words is the minimum. Blank spaces should be shown where the player hasn't guessed a letter yet. (You *may* - but *are not required to* - show a list of letters the player has guessed as well.)

You are required to provide the state of the hangman after each guess. You may derive it from this ASCII art if you'd like; however, ASCII art is not required if you'd just like to list the number of parts or wrong guesses remaining (or something to that general effect).


```
   __
  |  |
  |  0
  | -|-
  | / \
-----
```

You are required to use functions to construct this program. You are also required to document those functions. The documentation must be able to be read via pythons `help` builtin without any changes. You will also be required to provide the source code for this program.

You may not use any global or static variables for this task.

<a name="p08-assumptions"></a>Assumptions
=========================================

You are allowed to assume the following.

* The user will only input a single character, in lowercase, for their guess, followed immediately by a press of the `enter` key.

* The user will only use the characters from a through z in their guess

* The user only wishes to play once when they run your program. If they wish to play again, they will open the program again.

<a name="p08-hints"></a>Hints
=============================
* Functions are often used to break problems into simpler tasks. The functions I can tell you just looking at my own problem definition that I would create are:
  * a function to ask for the user's input
  * a function to choose a random word from my list
  * a function to output the ascii art hangman's current status
  * a function to output the current word's progress
* Documentation for this will likely take a minute. I'd leave it until last and just keep my names sane and write it up once the program is done and running.
* You don't need any secrets or anything to make this one work.

Just because I say something is how I'd do it just looking at it from the outset doesn't mean that's the correct way to do it or that it's the only way to do it. Notable here is that this is the set of hints for what I'd do in C++, which may not apply in Python.

But remember that you do need to break this out into functions.