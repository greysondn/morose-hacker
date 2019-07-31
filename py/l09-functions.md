---
layout: page
title: Python 09 - Functions
permalink: /py/l09
---

In today's lesson, you'll learn one of the main ways to code your way out of a paper bag. It is, of course, `exitPaperBag(oneself)`.

{% include infobox_head.html type="caution" title="Writing in Progress" %}
This lesson was rapidly adapted via copy+paste and patchwork from the related C++ lesson. As a side effect, some things may have been missed or may still refer to their C++ counterparts.
{% include infobox_tail.html %}

<a name="l09-functions"></a>Lesson 9:Functions
==============================================
Up to this point, if you wanted to reuse code, the only way to do so was to copy and paste it. Well...

{% include infobox_head.html type="caution" title="Anti-Pattern: Copy and Paste Coding" %}

For the first time, we can talk constructively about what a bad pattern for writing code, an *anti-pattern*, is.

Copy and pasting code isn't a great way to work on a way of reusing it precisely because as you get more and more instances of the code, it becomes monstrous to maintain. A bug fixed in one copy of a code that has been copied and pasted eight times must - itself - be copy and pasted eight times.

Instead of doing this inefficient and wasteful way about it, we have many ways to reuse code properly. You're learning functions now; later on you'll learn modules (for breaking your code into multiple files), packages (the same), classes (for another way to break your code into related parts), and all the neat tools that go with these things.
{% include infobox_tail.html %}

... needless to say that's not how we're going to do it in the future. We can make better tools!

<a name="l09-syntax"></a>Syntax
===============================

functions are comparable, but they have a new format:

{% highlight python %}
def name(arguments):
    pass
{% endhighlight %}

Where...

`def` is always `def`, the keyword for function definition.

`name` is any valid name for the function, with the same basic rules as `variable` identifiers.

`arguments` are names for what you need given to the function so it can do its magic, separated by commas.

`pass` can be replaced by any valid series of statements in python, with matching indentation.

...

If you want to return data from a function (so you could use it later), the last statement is a return.

{% highlight python %}
def name(arguments):
    # ... statements...
    return value
{% endhighlight %}

Where...

`return` is `return`, the return keyword.

`value` is the value you wish to return.

{% include infobox_head.html type="info" title="Polyglot notes: C++" %}
If you're learning C++ side by side with this, it probably seems quite strange. Unlike C++, Python's type safety is basically a "on request" or "blatantly painful"... and not much else.

One of the countless quirky properties of this is that the types aren't strongly declared for everything. So we can't even offer recycled syntaxes.
{% include infobox_tail.html %}

<a name="l09-syntax"></a>Name Conventions
=========================================
A typical naming convention for functions is:

* Start the name with a lowercase letter, such as in `hello`. If there's more than one word in the name, capitalize the first letter of each word - as in `helloWorld` (camelCase).

* Generally try to name functions as an action. That is, we would prefer `getName` over `name`. (And `sayHello` over `hello`.)

* Generally try to name functions for what they do clearly. That is, it is probably `calculateArea` or `calcArea` (or `getArea`), not `findArea` because you didn't perform a search.

* Functions can also be named for questions they answer; for example, you might write `isOdd` for a function that determines if a number is odd or not (and returns a `bool`), or `hasWeapon` for a method that checks if something has a weapon (and returns a `bool`).

* You can use underscores and numbers in a function name. It is generally discouraged to use underscores in Python, especially at the start and end of a function name (and may have unintended side effects). A number may not be the first character.

<a name="l09-rettype"></a>Return Shenanigans
======================================

Python doesn't overly care what you return, so long as you return a valid value.

The keyword, as stated previously, is `return`.

{% highlight python linenos %}
# could just be a literal
def returnPi():
    return 3.14

# could also be a variable
def returnPiVar():
    pi = 3.14
    return pi
{% endhighlight %}

It's okay to not return anything. Just don't use the `return` keyword.

{% highlight python linenos %}
def sayHello():
    print("Hello!")
{% endhighlight %}

To return multiple values, just wrap them as a tuple:

{% highlight python linenos %}
def getMeSomeLuckyNumbers():
    return (3, 7, 64)
{% endhighlight %}

You can assign those on return by using variable names separated by commas if that's a concern.

{% highlight python linenos %}
def getMeSomeLuckyNumbers():
    return (3, 7, 64)

three, seven, sixtyfour = getMeSomeLuckyNumbers()
{% endhighlight %}

<a name="l09-arguments"></a>Arguments
=====================================
Arguments have multiple names. You will most often hear them call "parameters" and "inputs". In general, these terms are synonymous with each other. There may be other terms.

The general syntax of an argument is: `name`. If you have more than argument you want your function to have, separate them with commas. `name, name`. You can have as many arguments as you like, but limiting the number is generally preferred.

In a function, it looks like this.

{% highlight python linenos %}
def calcRectArea(length, width):
    # we can access the arguments from inside the function
    return (length * width)

# later on, when we call that, we have to give it two numbers.
rectArea = calcRectArea(3, 12)
print(f"{rectArea}") # 36
{% endhighlight %}

<a name="l09-inteface"></a>Interfaces
=====================================

You may have noticed that there's a very simple property that can be shown with just the first line of a function. Ponder what you would think if you see the following line in code, with nothing else.

{% highlight python %}
def calcCircleArea(radius):
{% endhighlight %}

I imagine you can tell me:

* what this function most likely does (it's named for what it does, `calcCircleArea`)

* what it expects you to give it (a `radius`)

* you would probably guess it gives you a value given context (an area, probably of a circle, ostensibly - and hopefully actually - with radius `radius`)

You can tell me all this *without looking into the function's innards*. You have zero clue what the lines of code in this function look like. But if you think about it, you don't *really* know the innards of, for example, `print` or `range`. You just know what you've been told they do.

That first line has two names. To the python interpreter, it's the function's *declaration* - the part that declares what a function would take to call. To programmers, in general, it's the *interface*.

An *interface* typically forms a contract between pieces of code. It says "if you give me this, I will give you that". Obviously, a programmer could write the above method to spit out a random number or even nothing - however, that would be useless and make a programmer's job harder. In general, programmers try to make the contracts be honest.

*Soon*, you will learn one more tool - *documentation comments*. It's important to realize that documentation comments largely explain *interfaces*. Our entire ability to write and document code in nice formats like API documentation pages is based on this contract premise.

<a name="l09-where"></a>Where
=============================
Functions must be *declared* before they're used.

In python, the *declaration* preceeds the *definition* of a function directly. This reflects a standard behavior in other languages - normally you just declare and define functions at the same time anyway.

{% highlight python linenos %}
def calcTriangleArea(base, height):
    # due to the way python does
    # types, might want to corece
    # those to floats first
    baseFl = float(base)
    heightFl = float(height)
    return ((base*height)/2.0)

def main():
    print(str(calcTriangleArea(18, 7)))

if __name__ == "__main__":
    main()
{% endhighlight %}

However, most people prefer to try to get `main` early in their code so that it's easier to locate. So in most languages you'd define `main` first.

{% highlight python linenos %}
def main():
    print(str(calcTriangleArea(18, 7)))

def calcTriangleArea(base, height):
    # due to the way python does
    # types, might want to corece
    # those to floats first
    baseFl = float(base)
    heightFl = float(height)
    return ((base*height)/2.0)

if __name__ == "__main__":
    main()
{% endhighlight %}

In python, there's no real benefit to one over the other. There is, however, benefit to wrapping your main program in a `main` function so that you can call it after everything is defined in the main guard at the bottom.

Insofar as what I'd advise in general, I'd prefer the second format, personally.

<a name="l08-end"></a>When
==========================

With all this, you may be wondering: *when* should I break some code out into a function?

As a general rule, the answer turns out to be:

*When you find yourself copying the same few lines of code to solve a related problem and either there are no inputs or the inputs could be parameterized.* ("Could be parameterized" just means "could be made into parameters".)

Consider the following example program.


{% highlight python linenos %}
from random import randrange

# due to how much nicer python can be for certain tasks,
# this example is admittedly contrived. I should come up
# with a better one.

def main():
    # let's roll a standard dice kit, once each die
    d2   = randrange(1,   2)
    d4   = randrange(1,   4)
    d6   = randrange(1,   6)
    d10  = randrange(1,  10)
    d12  = randrange(1,  12)
    d20  = randrange(1,  20)
    d100 = randrange(1, 100)
    
    # print each one nicely
    print(f"  d2: {d2}")
    print(f"  d4: {d4}")
    print(f"  d6: {d6}")
    print(f" d10: {d10}")
    print(f" d12: {d12}")
    print(f" d20: {d20}")
    print(f"d100: {d100}")

if __name__ == "__main__":
    main()
{% endhighlight %}

I mean, this works. Just tediously. And you can't use a loop here because things are slightly changing. Clearly a slightly different tact is needed.

What if instead of all these variables that are so close to the same we just sort of *abstract* them away? Hide them in a method?

{% highlight python linenos %}
from random import randrange

# as far as names go, excessive but at least clear
# there are undoubtedly better options
def rollDieAndPrint(sides):
    roll = randrange(1, sides)
    print(f"d{sides}: {roll}")

def main():
    # now we've wrapped it together in a parameterized function
    rollDieAndPrint(  2)
    rollDieAndPrint(  4)
    rollDieAndPrint(  6)
    rollDieAndPrint( 10)
    rollDieAndPrint( 12)
    rollDieAndPrint( 20)
    rollDieAndPrint(100)

if __name__ == "__main__":
    main()
{% endhighlight %}

If you run that you get... the same output. Just more readable (minus my comments) and easier to work with.

By now I'd hope you learned two things.

First, that there are several ways to do the same task in code.

Second, *that use of reusable functions can make your code easier to understand, maintain, and reuse.*

<a name="l08-end"></a>Last Word
-------------------------------
As far as I'm concerned, there's nothing else to say.