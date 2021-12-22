---
layout: page
title: Python Extra 01 - Cram Session!
permalink: /py/x01
---

{% include infobox_head.html type="caution" title="The Ravages of Time" %}
This lesson was written before the inclusion of type hints as a core Python language feature, and therefore may include code and advice absent it.

My position on type hints is that they're great, use them! However, a text older than that should be expected to not know them.
{% include infobox_tail.html %}

This lesson slams together all of what should be lessons  2 through 8 into one rapid lesson meant for me to improvise on the spot.

This is more to provide visual aids for things that don't come through well in spoken words than anything else.

<a name="l02-repl"></a>Lesson 02: Simple variables
==================================================

Don't need initialization. You can set them at any time with

`name = value`

The absence of type is deliberate. We'll get to it momentarily.

Name conventions are about what you should expect:

*  The name can contain lowercase, uppercase, numbers, and underscores
*  The first character for a variable **should** always be lowercase.
    *  ... however it **may** be an underscore, uppercase letter, or lowercase letter.
*  If there are multiple words in the variable's name, you can either uppercase the first letter of each word after the first (camelCase) or put an underscore in between them.
    * In these lessons, I will be using camelCase.
*  Numbers are generally discouraged but not unallowed.

`value` can be any valid value in python. (Types are part of lesson 3.)

So you can do something like:

{% highlight python linenos %}
# comments in python start with a hash mark
# being said...
def main():
    a = 3
    b = 4
    areaOfSquare = a*b

    # we have to coerce numbers to strings in python 3
    # str(value) returns string form of value.
    # generally value.toStr()
    print("Area = " + str(areaOfSquare))

if __name__ == "__main__":
    main()
{% endhighlight %}

Aside: Python is not Type Safe
==============================
In C++, if you tried to assign the wrong type of value to a variable, the compiler or the runtime would catch you and complain. Python doesn't waste time doing this.

What this means is that you can not guarantee the type of a variable at any time. Python tries to do what makes the most sense when assigning a value to a variable, and it also tries to just trust you know what you're doing when you read from one.

{% highlight python linenos %}
def main():
    # this is a string now...
    tst = "string"
    print(tst)
    
    # but now... it's not.
    tst = 3.14
    print(tst) # error, must be a string

if __name__ == "__main__":
    main()
{% endhighlight %}

The solution to problems is to refrain from making assumptions that could be dangerous and act like you don't need the runtime to hold your hand. Python is very much a "you're an adult, act like one" environment in this sense.

{% highlight python linenos %}
def main():
    tst = "string"
    print(str(tst)) # if you always coerce to string...
    
    tst = 3.14
    print(str(tst)) # ... then it's never a problem

if __name__ == "__main__":
    main()
{% endhighlight %}

There are even better ways to format input into strings, for example inline substitution does work in Python 3 (You won't see me use it much because I learned Python 2, but you should totally use it.)

{% highlight python linenos %}
def main():
    tst = "string"
    # note the f before the start of the string, telling python this
    # is a special string
    # also note that we input the variable by wrapping its name
    # in curly braces
    print(f"value is {tst}") 

    # this is fairly robust
    tst = 3.14
    print(f"value is {tst}")

if __name__ == "__main__":
    main()
{% endhighlight %}

<a name="muismu"></a>Lesson 03: Types and Maths
===============================================

You can get the type of a value with `type(value)` in python.

{% highlight text %}
>>> type(1)
<class 'int'>

>>> type(1.1)
<class 'float'>

>>> type("word")
<class 'str'>

>>> type('word')
<class 'str'>

>>> type(f"word")
<class 'str'>

>>> type(True)
<class 'bool'>

>>> type(None)
<class 'NoneType'>
{% endhighlight %}

From this, we get that basic types in Python are:

* int - Integer - a whole number with no decimal point, positive or negative
* float - Floating Point Number - a number with a decimal point, positive or negative
* str - String - of any length of characters, delimited by multiple means, not the least of which can be double quotes, triple single quotes, or single single quotes
* a bool - Boolean values - `True` or `False` in Python
* a None - python's version of `Null`, which these lessons don't require you to know but is useful to know the name for in various languages.

It is rare, but you can check the type of a variable if for some reason you need to guarantee it. More often than not, users of python behave, and programmers do, too. It's only when things may be unexpected but should still be handled that type checking is typically used. (The more common route is to throw an error for the input, as it is invalid and wasn't expected. You may notice that Python does what we expect it to here as the behavioral standard.)

...

Insofar as math; there are extensive math functions in python without adding anything to it.

The first four are easy - operators `+`, `-`, `\`, and `*` are for addition , subtraction, division, and multiplication.

There's also modulo division, with `%`.

In addition, python3 has the following builtins:

* `abs()` - gets the absolute value of its input
* `divmod()` - will return a two-member tuple consisting of integer dividend and remainder (if for some reason you need both)
* `max()` - returns the largest value of its inputs
* `min()` - returns the lowest value of its inputs
* `pow()` - raises its first input to the power indicated by its second input. (If the inputs are `x` and `y`, it raises x to the power of y).
* `round()` - rounds its first input to (optional) decimal points precision indicated by its (again, optional) second input.

As you can see, a fairly complete mathematical set for basic maths. Would be nice to have `sqrt()` but you can't win them all; I'm sure its in the standard library but that's not the present topic at any rate.

<a name="muismu"></a>Lesson 04: If, Elif, Else, and Truth Tables
================================================================

Python denotes blocks of code through indentation. Do not use curly braces. In order to indicate that a block of code follows, end a line with a colon. Python's syntax only expects colons after certain keywords anyway.

This is a good time to learn a new keyword. `pass` indicates to python that you're aware that it expects something here but you didn't put anything here for now, just move along. It's most often used to leave in progress blocks of code unwritten in conditional chains (and so forth). It's also often used - as I will use it here - in example code where a body is expected.

The three main control flow syntaxes are:

{% highlight python %}
# first, just an if
if condition:
    pass

# second, an if and an else
if condition:
    pass
else:
    pass

# third, a short chain
if condition:
    pass
elif condition:
    pass
else:
    pass
{% endhighlight %}

`elif` is the pythonic keyword for "else if". Many languages include such constructs.

This also basically eliminates the need for a switch statement, provided no fallthrough was intended. As a result, python has no switch statements.

If you need a lesson on truth tables again, I can't help you and I wonder why I'm spending my time. What may be interesting to you, however, is that you should just write `not`, `or`, and `and` and - yes - it really works in python.

{% highlight text %}
>>> not True
False
>>> True and False
False
>>> True and True
True
>>> False and False
False
>>> True or False
True
>>> False or False
False
>>> not(False or False)
True
{% endhighlight %}

The symbols you're likely used to by now for those three words won't work in Python.

<a name="muismu"></a>Lesson 05: Keyboard Input
==============================================

Stupid easy in Python 3. Just use `input()`. Be sure to coerce it to type afterwards if you need something other than a string. If you want to provide a prompt for `input`, provide it as an argument. Python will handle the pretty-printing for you.

Literally it.

Type coercion functions you probably care about are...

`float()` to convert input into a floating point number.

`int()` to convert input into an integer.

`bool()` to convert input into a boolean.

<a name="muismu"></a>Lesson 06: Random Numbers
==============================================

This is now been pulled out to its own lesson. Here: [06 - Random Numbers]({{ site.url }}/py/l06)

<a name="muismu"></a>Lesson 07: Lists and Tuples
================================================

A handful of disjoint values is called a tuple. In python, we indicate a tuple with parenthesis and commas.

{% highlight python %}
myTuple = (0, 1, 2)
myTuple[0] = 0 # no change occurs
len(myTuple)   # 3
{% endhighlight %}

This is often useful for returning multiple values from functions, which we'll cover "soon".

Jointed values, on the other hand, are called lists. Think of lists like the array class for python - they're meant to be used much the same way. (Note, however, that lists don't necessarily have to be comprised of only one type - they're just meant to be.)

Lists are denoted with square brackets and commas.

{% highlight python %}
# start at a tuple...
myList = [0, 1, 2]
myList[0] = 0 # no change occurs
len(myList)   # 3

# ... what's this? ... WHAT, A STACK!?!?
myList.append(3) # adds 3 as a new element on the end
len(myList)      # 4 now
myList.pop()     # removes and returns last element from the list
len(myList)      # 3 now

# what else you got?
myList.sort()    #sort the list in place
myList.reverse() # reverse order of the list itself

# there's way more but we can't spend all day on this, you know.
# basically, your goto sequentail data type in python for everything
# but a return of multiple disjoint values will be the list.
{% endhighlight %}

So, yeah.

<a name="muismu"></a>Lesson 08: Loops
=====================================

This is now been pulled out to its own lesson. Here: [07 - Loops]({{ site.url }}/py/l07)

<a name="muismu"></a>Problem ??: Higher or Lower
================================================
You should have enough now to do it in Python. Give it a shot.

<a name="l01-end"></a>Last Word
-------------------------------
Anyone else need time to let their brain stop being numb? No? Just me? Okay.