---
layout: page
title: Python Problem 07 - Cipher
permalink: /py/p07
---

{% include infobox_head.html type="caution" title="The Ravages of Time" %}
This lesson was written before the inclusion of type hints as a core Python language feature, and therefore may include code and advice absent it.

My position on type hints is that they're great, use them! However, a text older than that should be expected to not know them.
{% include infobox_tail.html %}

{% include infobox_head.html type="caution" title="Writing in Progress" %}
This lesson was rapidly adapted via copy+paste and patchwork from the related C++ lesson. As a side effect, some things may have been missed or may still refer to their C++ counterparts.
{% include infobox_tail.html %}

Va gur jbeqf bs [gur zragbe](http://phrack.org/issues/7/3.html): "Lbh znl fgbc guvf vaqvivqhny,
ohg lbh pna'g fgbc hf nyy... nsgre nyy, jr'er nyy nyvxr."

<a name="p07-cipher"></a>Problem 07:Cipher
==========================================

This problem assumes you understand up to Lesson 8 (Loops) of the Python series.

Create a program that will take a lowercase string and output the same string again as lowercase letters encoded using the ROT13 cipher (or any other valid substitution cipher). There are two pieces of data that may help you do this:

First, `string` has a length. This tells you how many characters are in the string. You can read it by calling `len(someString)` in your code.

Second, you can read entire lines of input from the user at once. This is doable using `input()`. Nothing really changes as far as I know, the user just hits `enter` to end their input.

<a name="p07-assumptions"></a>Assumptions
-----------------------------------------
You are allowed to assume the following.

* The user will only input a single line, consisting of lowercase letters and spaces, terminated with a standard line feed (or whatever the `enter` key provides on their system). (Python should *chomp* this - remove it - if you're using the `input` function.)

* The user will only use the characters from a through z in their statement

* The user will not use any punctuation

* The user only needs to input one line when they run the program

* There are at least two ways perfectly within your ability to do this task. Just because there is a certain way you've seen me do it doesn't mean that's the best or only way to do it.