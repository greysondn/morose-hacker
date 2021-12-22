---
layout: page
title: Python Extra 02 - Cows and Bulls
permalink: /py/x02
---

{% include infobox_head.html type="caution" title="The Ravages of Time" %}
This lesson was written before the inclusion of type hints as a core Python language feature, and therefore may include code and advice absent it.

My position on type hints is that they're great, use them! However, a text older than that should be expected to not know them.
{% include infobox_tail.html %}

I don't have anything clever for this one. I should fix that.

<a name="x02-cows-and-bulls"></a>Extra 02: Cows and Bulls
=========================================================

This task assumes you understand up to Lesson 9 (Functions) of the Python series.

Create a program to play the game ~~Mastermind~~ Cows and Bulls. There must, at minimum, be vs CPU play. The number for CPU play must be randomly generated, and be four digits (with numbers less than 1000 having zeros in front of the first digit to pad them out). (The game, in any event, is typically played with a four digit number.)

For a guide on how Cows and Bulls is played, see Wikipedia:
https://en.wikipedia.org/wiki/Bulls_and_Cows

Unlike assignments, there are no strict requirements for this task. That is because it was given as something to do upon request, not an actual assignment. Consequently, I won't be grading it. I'm willing to do code reviews on it and help, but I'm not concerned about you getting it any particular way or any particular lesson in it. (With the exception of my usual provision that you cannot use global or static variables.)

There are some general guidelines that will make the player's life less miserable.

The first is to show the game's state after every guess. This includes how many guesses are remaining and the outcome of the previous guess.

The second is to break this down into functions that help with specific tasks. Remember that the strength of functions is that they have parameters - parametric tasks work well as a side effect (tasks where only the inputs change).

The third is to keep a clean record of outcomes so the player can scroll back over their guesses and think about what is being told to them. This is critical to the game's central mental puzzle.

I'm going to do the rest of this like normal, but just be aware it's more "what I'd be looking for" and less "what you must do". I would discourage over-reaching yourself, however.

<a name="p08-assumptions"></a>Assumptions
=========================================

You are allowed to assume the following.

* The user will only input a four digit number (including front-padding numbers of less than 4 digits) for their guess, followed immediately by a press of the `enter` key.

* The user will only use the characters from 0 through 9 in their guess

* The user only wishes to play once when they run your program. If they wish to play again, they will open the program again.

<a name="p08-hints"></a>Hints
=============================

There was the additional brief on `string.zfill()`. `zfill` will left-pad a string with zeroes until the desired length is input.

`str(69).zfill(4) ` is `"0069"`, for example. This is true of any string; `"why".zfill(6)` is `"000why"`, for example. It just happens to be especially useful when dealing with numbers converted into strings.

A short snippet to generate a number and convert it to a string was provided.

{% highlight python linenos %}
from random import randrange

def getTargetNumber():
    num = randrange(0, 9999)
    ret = str(num)
    return ret.zfill(4)
{% endhighlight %}

Although documentation isn't required, it is required in assignments and would be good practice to include. As usual, I would leave it until you're sure functions are finalized or until last.