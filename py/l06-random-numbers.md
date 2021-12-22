---
layout: page
title: "Python 06 - Random Numbers"
permalink: /py/l06
---

According to Randall Monroe, [the reference fairly chosen random number is 4](https://xkcd.com/221/). He apparently rolled a die to obtain it.

<a name="l06-random-numbers"></a>Lesson 06: Random Numbers
=======

The primary focus of this text is towards making games and small interactible toys. It's very, very hard to make most games without dice.

Right?

In order to make dice, you need a random number generator. Python has one! ... but you have to learn how to pull it in so that you can use it first.

So first and foremost, let's talk about packages and modules.

<a name="l06-packages-and-modules"></a>Packages and Modules
-------------------------------

Python ships a [massive standard library](https://docs.python.org/3/library/) full of what it calls *packages* and *modules*. For now, we're going to accept a very simple view of these things and cover them in more detail later on, in [lesson 12]({{ site.url }}/py/l12).

A *package* is sort of like a folder of *modules*. A *module* is a grouping of bits of useful, related pieces of code, including *functions* and *classes*, which is what we're starting to touch on here and now and will cover in more detail as we go along.

In order to use code in a *module*, we must either be in the same file as that module was defined, or *import* it.

<a name="l06-import"></a>Import
-------------------------------

The `import` statement takes as many as three parts. The typical places for import statements is at the top of your file, before any other code.

In the most basic form, you just `import` whatever you want this only works on packages and modules as a whole. Separate packages and modules inside them with a dot when doing this.

Anything you need inside those modules will have to be referenced by the name of the module followed by a dot followed by whatever you want.

{% highlight python linenos %}
import foo
import bar.baz

def main():
    foo.zap()
    bar.baz.bork()

if (__name__ == "__main__"):
    main()
{% endhighlight %}

This is rather tedious, especially when you only want one *function* from a library. So that gets us to the second format - `from`. To use this one, you specify where you want to import something from - the package and module - and then what it is you're importing.

{% highlight python linenos %}
from foo import zap
from bar.baz import bork

def main():
    zap()
    bork()

if (__name__ == "__main__"):
    main()
{% endhighlight %}

It may be that we want a shorter name or a different name. In both cases, we can `import` something `as` a name of our choosing. To do that, you write the normal import statement... and then follow it with `as` and the name you'd like to use for it. (Remember to use standard naming rules, insofar as you know them.)

{% highlight python linenos %}
from foo import zap as zzz
import bar.baz as bb

def main():
    zzz()
    bb.bork()

if (__name__ == "__main__"):
    main()
{% endhighlight %}

Believe it or not, that's everything. You can now import large chunks of the code in the python standard library and make use of it. (You are still missing an explanation of anything which is a `class`.

{% include infobox_head.html type="info" title="Belonging To - the Dot" %}
If you followed up on the whole thing about `help()` and using it on normal objects, you are now ready to learn how to read more of that documentation and use it.

The dot - `.` - indicates a hierarchial relationship. The thing to the right of the dot belongs to the thing on the left of it. In Python, everything is an *object*; an *object* is an instance of a *class*. *Classes* have functions of their own generally called *methods*. Some belong to the class itself, some belong to individual instances - objects of that class. (Read: if `Human` is a class, then each individual person is an object, an instance of `Human`. We'll go over this better and deeper later.)

The important takeaway here is that **if you could just see the methods for an object, you could follow the object with a dot and make use of them.** The `help()` function does exactly this.

Consider the following.

{% highlight python linenos %}
C:\Users\Dorian Greyson>python
Python 3.10.1 (tags/v3.10.1:2cd268a, Dec  6 2021, 19:10:37) [MSC v.1929 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license" for more information.
>>> foo = "test string"
>>> help(foo)
No Python documentation found for 'test string'.
Use help() to get the interactive help utility.
Use help(str) for help on the str class.

>>> help(str)
{% endhighlight %}

Python spits back all the documentation for the `str` class - the class representing strings.

We can tell this because it starts like this:

{% highlight plaintext linenos %}
Help on class str in module builtins:
{% endhighlight %}

Way, way down, way down in this, we come across some potentially useful functions, the ones that don't start with two underscores. In particular, we see functions like this:

{% highlight plaintext linenos %}
 |  replace(self, old, new, count=-1, /)
 |
 |        count
 |          Maximum number of occurrences to replace.
 |          -1 (the default value) means replace all occurrences.
 |
 |      replaced.
{% endhighlight %}

This is telling you how to use this!

You can ignore the `self` argument - just pretend it doesn't exist if you see it for now, and we can explain it later.

This says if you have some string `foo`, then `foo(old, new, count)` does some work - and `count` could be ignored if you're okay with the default value being used.

What happens if we use that on our test string from before?

{% highlight python linenos %}
>>> foo.replace("test", "magic")
'magic string'
>>> foo
'test string'
>>> foo = foo.replace("test", "magic")
>>> foo
'magic string'
{% endhighlight %}

It's healthy to know how to ask the python interpreter itself for help, but there are standard documents for this on the python website. For example, here's the `str` class documentation: [link](https://docs.python.org/3/library/stdtypes.html#text-sequence-type-str).

Knowing how to find, search, and read standard documents is valuable, too. Nobody is going to tell you everything something can do - it's up to you to ask a question and then read the documentation for yourself to try to answer it.

{% include infobox_tail.html %}

{% include infobox_head.html type="hacker" title="RTFM" %}
You will often hear hackers and senior programmers both respond tersely to a question with "RTFM", often times followed by an HTML link or page number. What is going on here? What could these magical letters mean?

You have just been told to "read the fucking manual". The assumption is that if documentation exists, it is meant to be read; and also that questions asked of experts should not be on material you could learn by reading a manual yourself.

Believe it or not, this hard knocks lesson is actually them trying to equip you to seek out and understand information on your own. Nobody is being as mean as they often seem from the outside looking in. The cultural ethos of "curiousity" and "experimentation" is pervasive everywhere - including in how new information should be (primarily) obtained.

Well, almost nobody. There is a certain category of antisocial hacker that just doesn't want to be bothered with questions, and will direct you to the manual regardless. You can spot them by checking the manual, politely informing them that you don't see it in there (if it isn't in there), and observing if they proceed to insult you or deny what you're saying. After all, if it's in the manual and you can't find it, they could show you where it is if you tried and couldn't find it yourself, right?

Do not waste senior developers' time asking for page numbers when they say to RTFM the first time. Actually search the manual dilligently. There is a certain type of student that just wants spoonfed everything - and there is no hacker who wants to be responsible for hoisting someone else on their shoulders and making them feel accomplished. The world is full of fascinating problems waiting to be tackled... and that's not one of them. Those who wish to teach write documents like this or start tutoring.
{% include infobox_tail.html %}

<a name="l06-random"></a>Random
-------------------------------

Now we finally get to where we wanted to be when we started. The `random` python module, which is documented [here](https://docs.python.org/3/library/random.html).

If you want to role a die, you just need one function from the `random` module, which is `randint()`. It takes a min value and a max value and returns a random integer between those two values. Most dice will have a min value of `1` and a max value of whatever the number in their name is - for example, a d20 has a max value of `20`.

You will need more functions later on for different types of randomness.

Let's see this in action.

{% highlight python linenos %}
from random import randint

def main():
    # we'll talk about a better way to do something 10 times later on.
    print(randint(1, 20))
    print(randint(1, 20))
    print(randint(1, 20))
    print(randint(1, 20))
    print(randint(1, 20))
    print(randint(1, 20))
    print(randint(1, 20))
    print(randint(1, 20))
    print(randint(1, 20))
    print(randint(1, 20))

if (__name__ == "__main__"):
    main()
{% endhighlight %}

Saving this file as `rolld20.py` and running it a handful of times is interesting, somewhat.

{% highlight python linenos %}
C:\Users\Dorian Greyson\python>python rolld20.py
4
9
1
10
20
5
16
5
15
2

C:\Users\Dorian Greyson\python>python rolld20.py
17
4
19
2
17
13
18
8
8
18

C:\Users\Dorian Greyson\python>python rolld20.py
18
6
13
6
20
19
11
4
9
19
{% endhighlight %}

So we know that it's to all appearances random, and that it's different each time we run it. Good! That's good enough to print, right?

{% include infobox_head.html type="curiousity" title="How Random Number Generators Work" %}
We've skipped a lot of details on how this works. But essentially, the random number generator needs a value to start with, and then does math to go from value to value. Because the values are not truly random - they're derived from previous values or some inputs - we call this a *psudeo-random number generator*, or PRNG for short.

You probably can specify the *seed* for the PRNG (the documentation for the `random` module will tell you about that). The seed is the value that the PRNG starts with. Very normal seed values are the time when the program is started, some specific chosen value, or some number derived from user inputs.

Values may be generated somewhat better from user inputs. A normal thing to do is to gather user input into what is called an *entropy pool*. A lot of old video games used one or two variables as an entropy pool, which changed on user inputs. This meant that if you could just rewind time and press slightly different buttons, you could change dice rolls in the game - a thing which is well known as "[luck manipulation](http://tasvideos.org/LuckManipulation.html)" to tool-assisted speedrunners.

This topic runs far and deep, including insight on specific games, mathematical analysis of different formulas, and questions like "what is randomness, really?" While it's important to cryptography, video games, and various other things, this is about as deep as we'll go here and now. I will however leave you on the interesting aside [that lava lamps are responsible for much of the security  online today (video)](https://www.youtube.com/watch?v=1cUUfMeOijg).
{% include infobox_tail.html %}

<a name="l06-end"></a>Last Word
-------------------------------
You probably already realized this lesson was mostly about importing and the expansion of the ability to read documentation. There's not much else to observe, just the unsly nod and wink that, yes, I know.