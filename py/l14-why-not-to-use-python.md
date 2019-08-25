---
layout: page
title: Python 14 - Why Not to Use Python
permalink: /py/l14
published: false
---

Did you know? The reticulated python is the only animal verified to have consumed a human whole. Good luck sleeping tonight.

<a name="l14-why"></a>Lesson 14: Why Not To Use Python
======================================================
It's rare I feel a need to include a chapter on why to dislike a language, but the simple truth of the matter is that it cannot be ignored that Python is one of those bizzarrely controversial languages when it comes to teaching it.

There are those who think we should teach Python first, that it's a great language to learn and can never steer you wrong.

There are those who think we should teach Python, but not teach it first. It's a great language, but it doesn't teach certain things we'd prefer a first language teach.

There are those who hate it, thinking it's useless, ugly, and frankly a blight on Linux that it's included by default in most distros.

And then there's people like me - I love python, but I also know python.

So here are all the reasons up to this intermission to not use python.

<a name="l14-type"></a>Type Safety
==================================
Python doesn't guarantee to maintain the type of a variable. Variables are inherently type unsafe. (Opt-in type safety does exist, but will be covered on a later date.)

Most prominently, this means that a variable that is a string at the start of an application may be an integer by the end.

<a name="l14-do-while"></a>Do-While
===================================
There is no do-while in python. The preferred construct is instead to either just do it manually once before running a while loop (as part of initialization)... or to rewrite it so that it works with a for or a while.

<a name-"l14-string">Strings Are Not Character Arrays
=====================================================
While running this for the first time, it was discovered that although strings have an accessor for individual characters, individual characters in strings cannot be written to via the accessor.

I considered writing a function to slice and rewrite a single character in a string. In the end I found this too absurd to dignify.

<a name="13-end"></a>Last Word
------------------------------
Guh, I'm tired, commit and forget for now.