---
layout: page
title: Python Problem 06 - High or Low
permalink: /py/p06
---

There's a interactive-fiction game that includes the following line before starting a minigame. It goes like this:

> I'm forced to assume that you enjoy performing meaningless tasks.
> If this is the case, then you're in luck:
> [I have one for you](https://www.kongregate.com/games/2darray/you-find-yourself-in-a-room).

The task here is to program that minigame, with considerably less profanity. 

We hope.

<a name="p06-high-or-low"></a>Problem 06: High or Low
==========================================

This problem assumes you understand up to Lesson 7 (Loops) of the Python series.

Create a program that will play the game "High or Low". The rules are given below.

The computer will pick a random number between 1 and 100,000. That number must be guessed by the player. Each guess the player makes, the computer will tell them if their guess was too high or too low. When the player finally guesses the correct number, they have won and the game ends.

You may need to know the following extra data for this task:

* The `input()` function returns a string. In order to convert that to an integer, you need to wrap it in `int()` - eg: `int(input("> "))`. The inverse works as well to convert an int to a string: `str(foo)`.

<a name="p07-assumptions"></a>Assumptions
-----------------------------------------
You are allowed to assume the following.

* The user will only input unbroken strings, consisting of digits and nothing else.

* The user will only input integers between 1 and 100,000 - including 1 and including 100,000.