---
layout: page
title: Python 10 - Standard Doc Comments
permalink: /py/l10
---

Now for the part where you learn to start hating me if you haven't learned already - the most boring part of any job.

Documentation.

{% include infobox_head.html type="caution" title="Writing in Progress" %}
This lesson was rapidly adapted via copy+paste and patchwork from the related C++ lesson. As a side effect, some things may have been missed or may still refer to their C++ counterparts.
{% include infobox_tail.html %}

<a name="l10-sdc"></a>Lesson 10: Standard Doc Comments
======================================================
To now, if I wanted you to document something, I just asked you to quickly throw a line comment at it so I had a gist of what was going on. There was no need for me to be able to generate documentation for your work or anything like that.

We are steadily approaching a point where that will change, and the best thing to do is to beat into your head some good practices so that you can work with other people. This also will give you some understanding of how other people have written their documentation, so that when you see it you can interpret it quickly and easily.

There are several syntaxes for standard documentation in source code. Normally I'd teach you Javadoc syntax, but python is largely its own beast and has its own syntax. So we're going to learn pythonic doc comments instead.

You may want to keep in the back of your head that Javadoc syntax is pretty standard, and it's going to be good to learn if you want to learn any language that's not Python. On a future date.

<a name="l10-toolkit"></a>Toolkit
=================================

Python comes "batteries included". One of the quirky side effects of this property is that Python ships with its own documentation browsers. Today we'll learn how to document to read with the `help()` command in the interactive python interpreter; later we'll learn how to go from this to actually reading them using the online browser.

However, the online browser is quite useful, don't get me wrong. This is the [pydoc module](https://docs.python.org/3/library/pydoc.html) (or, if you prefer it how I write when it's not linked, the `pydoc` module).

{% include infobox_head.html type="behold" title="A Case for Main Guards" %}
Recall that when you run a python script or import it, the interpreter basically runs it *almost* the same as though you had typed it in line by line.

So we use main guards to enable us to import things. That's that funny `if __name__ == "__main__"` bit I've said to write and not lose sleep over.

Here we see one point for use of this in the Pydoc documentation.

> Note In order to find objects and their documentation, pydoc imports the module(s) to be documented. Therefore, any code on module level will be executed on that occasion. Use an `if __name__ == '__main__':` guard to only execute code when a file is invoked as a script and not just imported.

It never hurts to have some showing that the instructor didn't just make something up.

{% include infobox_tail.html %}

From the terminal, the online browser usually be ran via `python3 -m pydoc -b`. I am aware of a way to start the browser from inside the interpreter existing, but not what that way is.

However, one can always call `help(object)` to read an object's pydoc inside the interpreter. And either way it would be the easiest way to do so for now because you're still missing some key constructs for the online browser to work the way you likely expect if you've looked at it.

<a name="l10-syntax"></a>Basic Syntax
=====================================

Python's syntax and conventions for documentation strings is part of [PEP-257](https://www.python.org/dev/peps/pep-0257/). What follows is mostly just a reiteration of the PEP-257 standard with other notes. There are other standards; for those coming from a Javadoc (and compatible) background, Doxygen offers a compatible format that may be of more interest.

Strings can be triple quoted. This is the first fact you need to know to write docstrings in python.

{% highlight python %}
# double quotes
"""This is a valid string."""

# single quotes
'''This is also a valid string.'''

# newlines, even
'''this
is
also
valid'''
{% endhighlight %}

The second fact you need to know is that a literal in isolation evaluates to itself, and if there's no context to return to that has output, the literal (apparently, I never quite understood this) just falls into the ether.

{% highlight python %}
def sayHello():
    # this literal just sorta disappears
    """this example of a string just disappears when ran"""
    
    # yes, other literals would too
    42
    
    # but the hello still prints
    print("Hello!")

if __name__ == "__main__":
    sayHello()
{% endhighlight %}

With those two facts in mind, we have a place we can put something specific to document code!

*Docstrings* in python are precisely what they say - strings which document something. In the present tense, they document functions. A docstring is a triple-double-quoted (triple ***double*** quoted, the double quotation character `"`) string immediately after the start of a function.

{% highlight python %}
def sayHello():
    """this is where a docstring goes"""

    print("Hello!")

if __name__ == "__main__":
    sayHello()
{% endhighlight %}

PEP-257 specifies that a blank line should not follow a function docstring, as I've put here; I would personally prefer the blank line for readability, but note it's a matter of conventions on the point. The only mandatory part is the triple double quoted string.

That may have confused you, so compare this PEP-257 compliant version (on the specific point in question) with the above.

{% highlight python %}
def sayHello():
    """this is where a docstring goes"""
    print("Hello!")

if __name__ == "__main__":
    sayHello()
{% endhighlight %}

Just because van Rossum found it readable doesn't mean I do.

...

Docstrings may be a single line or multiple lines in length.

If they are a single line, as above, the open and close are on the same line.

If they are multiple lines, then the first line is assumed to be a summary, with subsequent lines expected to be a long description and specific data points. Indent lines to the same level as the opening quotes, and put the closing quotes on their own line.

{% highlight python %}
def sayHello():
    """Says hello.

    This horribly contrived example just exists to show off how
    we do things in Python world. It doesn't even follow the spacing
    guidelines for PEP-257!
    """

    print("Hello!")

if __name__ == "__main__":
    sayHello()
{% endhighlight %}

<a name="l10-where"></a>Where?
==============================

So these docstrings, as far as what you know, only can go two places.

The first is at the start of a standalone script. If it's there, it's expected to document what the script does in a format that makes it compliant with asking that docstring for invokation (how to run the script; eg what you get if you type `-h` after many program names in the terminal). I would prefer you simply omitted this or used line comments - there are better ways to go about such things for standalone scripts, most notably via the `argparse` library which we will eventually get to. Instead, use that space for a very quick blurb and just move on, so that the documentation parser is happy you said something but you're not wasting time. One sentence saying what it does is plenty enough for me.

The second is immediately after a function's declaration, but before the first line of its definition (the first line inside the function's body). At that place, it's expected anything you say has to do with the *function*. This I do care about.

The documentation should only cover the *interface* of everything. Nobody needs to know *how things are implemented (the implementation details) in doc comments.* This is true of every language.

Documenting a simple `roll()` function from before might look like this with what you know so far:

{% highlight python %}
from random import randrange

def roll(sides):
    """Rolls a die and returns the outcome.

    An ordinary die, by definition, starts at 1 and ends
    at a number equal to the number of sides.
    """
    
    return randrange(1, sides)
{% endhighlight %}

The extended definition is a bit much, but indicates intent clearly. Most people familiar with dice would work just fine with:

{% highlight python %}
from random import randrange

def roll(sides):
    """Rolls a die and returns the outcome."""
    
    return randrange(1, sides)
{% endhighlight %}

Either is mostly sane here.

<a name="l10-block"></a>Documenting Cold Hard Data
==================================================
You may have noticed that we didn't really document anything about the return or the parameters. We just gave a good description.

You'd probably think this is fine but... it's not, honestly.

In most documentation formats, there is a tag specifically to document the return and the arguments. There are only conventions in python docstrings.

*Keyword arguments* are arguments that have a name. If you typed a name in for the argument, then it's a *keyword argument*. It's typical to list them out and indent them, with expected type. As python has no type safety for the generator to infer, it may be of value to go ahead and ***deliberately state the type of an argument in the documentation comments if it matters*** (You might prefer [Google's docstring standards](https://github.com/google/styleguide/blob/gh-pages/pyguide.md#383-functions-and-methods) for this over both mine and bare PEP-257 if you're looking for something both widely accepted and well documented.)

{% highlight python %}
from random import randrange

def roll(sides):
    """Rolls a die and returns the outcome.

    Keyword arguments:
    sides -- uint -- number of sides on the die, must be greater than 0
    """
    
    return randrange(1, sides)
{% endhighlight %}

Google is slightly more readable, and closer to what I do:

{% highlight python %}
from random import randrange

def roll(sides):
    """Rolls a die and returns the outcome.

    Args:
       sides: uint - number of sides on the die, must be greater than 0
    """
    
    return randrange(1, sides)
{% endhighlight %}

Returns aren't specified as part of PEP-257, but are basically the same as a keyword argument without a name.

{% highlight python %}
from random import randrange

def roll(sides):
    """Rolls a die and returns the outcome.

    Args:
       sides: uint - number of sides on the die, must be greater than 0

    Returns:
        uint - the result of rolling a die with given sides
    """
    
    return randrange(1, sides)
{% endhighlight %}


Because that's now very redundant, we can now clean this up:

{% highlight python %}
from random import randrange

def roll(sides):
    """Rolls a die.

    Args:
       sides: uint - number of sides on the die, must be greater than 0

    Returns:
        uint - the result of rolling a die with given sides
    """
    
    return randrange(1, sides)
{% endhighlight %}

{% include infobox_head.html type="caution" title="Python Is Its Own Beast" %}
As I said a few times, Python has its own conventions around documentation. Javadoc is far better IMHO, and perhaps something could be done but it would require not writing docstrings, which can't be taught to you in good faith and claim I'm teaching you Python.

The alternative that is pretty standard for Python, and offers comparable features to Javadoc, is Restructured Text for documentation. You're welcome to use it, but it's an exercise left to you. I don't know it and don't have any ability to check or support it.
{% include infobox_tail.html %}

{% include infobox_head.html type="curiousity" title="How I'd Prefer to Document That" %}
Speaking of, here's something much closer to my ideal. I wonder - is there a way to parse this, granting it's not PEP-257 compliant?

{% highlight python %}
from random import randrange

##
# Rolls a die.
# 
# @param sides    uint     number of sides on the die,
#                          must be greater than 0
#
# @return    uint    the result of rolling a die with given sides
def roll(sides):    
    return randrange(1, sides)
{% endhighlight %}
{% include infobox_tail.html %}


<a name="l10-building"></a>Reading the Documentation
====================================================

You can read the documentation by importing your file in the Python interpreter and typing `help(function)`. For example, if I start in the same folder as my source file, and my source file is named `rollin.py`...

{% highlight text %}
Python 3.6.7 (default, Oct 22 2018, 11:32:17)
[GCC 8.2.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import rollin
>>> help (rollin)
{% endhighlight %}

It then pulls up a help browser with the documentation strings in it.

{% highlight text %}
Help on module rollin:

NAME
    rollin

FUNCTIONS
    roll(sides)
        Rolls a die.

        Args:
           sides: uint - number of sides on the die, must be greater than 0

        Returns:
            uint - the result of rolling a die with given sides

FILE
    /mnt/c/Users/Dorian Greyson/Documents/path/to/rollin.py
{% endhighlight %}

Students who have tried booting the online browser from the module have had mixed results reading their file at this time. For the same reason, I'm hesitant to include directions to generate HTML documentation because it may give spotty results. However, we are very near when it will be covered, on the bright side.

<a name="l08-end"></a>Last Word
-------------------------------
At this point, you're ready to do 
[Problem 08: Hangman]({{ site.url }}/py/p08)