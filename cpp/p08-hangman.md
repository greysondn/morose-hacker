---
layout: page
title: C++ Problem 08 - Hangman
permalink: /cpp/p08
---

I'd like to hang with you and all, but this guy keeps guessing what's on my mind.

<a name="p08-hangman"></a>Problem 08: Hangman
=============================================

This problem assumes you understand up to Lesson 9 (Functions) of the C++ series. It may be prudent to also do Lesson 10 (Standard Doc Comments) as well.

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

You are required to use functions to construct this program. You are also required to document those functions. The documentation must be able to be generated into a browsable document using doxygen with no changes. (You are not required to provide a Doxyfile.) You will also be required to provide the source code for this program.

***UNDER NO CIRCUMSTANCES MAY YOU USE GLOBAL OR STATIC VARIABLES.*** Pass things around and get creative with your returns. Use `main()` to manage the game logic and bring your functions together.

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
