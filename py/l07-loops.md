---
layout: page
title: Python 07 - Loops
permalink: /py/l07
---

{% include infobox_head.html type="caution" title="Writing in Progress" %}
This lesson was rapidly adapted via copy+paste and patchwork from the related C++ lesson. As a side effect, some things may have been missed or may still refer to their C++ counterparts.
{% include infobox_tail.html %}

Does it ever feel like groundhog day - you just keep repeating yourself? Let's help the computer get that same feeling, shall we?

<a name="l07-loops"></a>Lesson 07: Loops
=================

There are two basic loop structures in C++. They are `while` and `for`.

It's best to wrap your head around them in that order.

<a name="l07-while"></a>While
-----------------------------

A *while* loop takes the form

{% highlight python linenos %}
while (condition):
    # body
{% endhighlight %}

{% include photoplasty.html img="/res/py/l07/uml-while.png" caption="UML flowchart of a while loop" %}

When running, it will do the following:

* Check to make sure `True == condition`
  * If `true`...
    * Run the code inside the loop
    * Return to start
  * If `false`...
    * don't run the loop, just move forwards in code

It's important to note that *this means that you cannot necessarily guarantee that a while loop will run*. That is, it may run zero or more times.

Typically state for the while loop is either defined as some function that may change, or some state outside of it. For example, the oldschool way of doing *all* loops was with a while loop, and looked like this:

{% highlight python linenos %}
def main():
    # programmers start counting with zero
    # this is because it's the lowest value for our machines
    # we call this "zero-based indexing", for reasons that will
    # make waaaaaaay more sense later.
    counter = 0

    # less-than means we'll run ten times. Think about it.
    while (counter < 10):
        print(f"Current count: {counter}"}
        counter = counter + 1

if (__name__ == "__main__"):
    main()
{% endhighlight %}

That does this:

{% highlight plaintext %}
C:\Users\Dorian Greyson\python>python example.py
Current count: 0
Current count: 1
Current count: 2
Current count: 3
Current count: 4
Current count: 5
Current count: 6
Current count: 7
Current count: 8
Current count: 9
{% endhighlight %}

Each time the loop runs is called an ***iteration***.

I'll repeat that. It's important.

Each time the loop runs is called an ***iteration***.

It seems like we'd have a common nomenclature for counting off iterations like this, right - if we we needed to, say, *increment* or *decrement* something?

There's a compound operator for both of those. Incrementation in Python is `+=`, while decrementation is `-=`.

We can rewrite that code up above like this. It means the same thing to the interpreter; the key difference is on line 10.

{% highlight python linenos %}
def main():
    # programmers start counting with zero
    # this is because it's the lowest value for our machines
    # we call this "zero-based indexing", for reasons that will
    # make waaaaaaay more sense later.
    counter = 0

    # less-than means we'll run ten times. Think about it.
    while (counter < 10):
        print(f"Current count: {counter}"}
        counter += 1

if (__name__ == "__main__"):
    main()
{% endhighlight %}

Because my brain is stupid and takes a minute to parse that, you will not see me use it, but you should. It's the standard way of writing that in Python, and other languages have their own increment and decrement operators.

Anyway, this is kind of stupid, right? I mean, why am I managing state for just counting up a number? That seems like it has to be very, very common. Well, it is... and here is where things get much more powerful.

<a name="l07-for"></a>For
-------------------------
A *for* loop takes the form

{% highlight python linenos %}
for foo in iterable:
    body
{% endhighlight %}

[TODO: Flowchart of for loop, somehow.]

When running, it does the following.

* perform *initializer*
  * check if there is more to the iterable.
    * if `true`...
      * get the next element of the iterable
      * run the code inside the loop
    * if `false`
      * don't run the code, just move forwards in the program

It's important to notice that *for loops, like while loops, may never run the code inside of them*, namely if iterable has a size of zero.

I know, I know, "what's an iterable?". In the simplest terms, an *iterable* is something that can be *iterated* over.

You're scratching your head.

I am only going to teach you one iterable right now. That is the builtin `range()` function. `range` takes up to three arguments and acts as a lazy iterable (it yields values that it creates on the spot each time the `for` loop iterates and asks its state, without storing them.)

`range` is really `range(start=0, end, step=1)`, where:

  * `start` is optional, defaults to `0`, and is the value to start with.
  * `end` is mandatory, and is some value. We typically end at a value `x` such that `x = end - 1`. So if you input a `10` for `end`, the typical last value `range` will yield is `9`.
  * `step` is optional, defaults to `1`, and is the amount to increment by each time a value is yielded. It is allowed to be negative; if so, then start and end follow very nearly the same rules, execpt that the last yielded value should be expected to be `end + 1` instead of `end - 1`.

Given all that, we can rewrite the example used for the `while` loop like this:

{% highlight python linenos %}
def main():
    # remember: range has defaults. So this is the same as saying:
    # for counter in range(0, 10, 1)
    for counter in range(10):
        print(f"Current count: {counter}"}

if (__name__ == "__main__"):
    main()
{% endhighlight %}

<a name="l07-typical"></a>Typical Uses
--------------------------------------
There's really only a little to know about typical usage patterns for these two.

The most common use for a `while` loop is a main program loop.

{% highlight python linenos %}
def main():
    # we'll do a little "nag for right answer" thing
    guessedPassword = False

    # note that it reads close to english this way
    while (not guessedPassword):
        # here, an empty line to make things look nicer.
        print("")

        # ask user to guess each time
        print("Tell me the correct password and I'll let you go!")
        guess = input("> ")
 
        # here, we put an empty line just so things look nicer.
        print("")

        # check, our password is "spuds"
        if ("spuds" == guess):
            # user guessed it, so fix our variable
            guessedPassword = True

            # and give the user a little feedback
            print("Okay. I guess you can go.")

        else:
            # user didn't guess it. Give them feedback,
            # let the while loop handle repeating the rest.
            print("That's not the password!")


    # To get to here, the user must have entered "spuds" to exit the
    # while loop, so we just do a small piece of post-program cleanup
    print("")

if (__name__ == "__main__"):
    main()
{% endhighlight %}

That looks like this when you run it twice:

{% highlight plaintext %}
C:\Users\Dorian Greyson\python>python example.py

Tell me the correct password and I'll let you go!
> spuds

Okay. I guess you can go.


C:\Users\Dorian Greyson\python>python example.py

Tell me the correct password and I'll let you go!
> password

That's not the password!

Tell me the correct password and I'll let you go!
> bork

That's not the password!

Tell me the correct password and I'll let you go!
> spuds

Okay. I guess you can go.
{% endhighlight %}

A `for` loop shows up when we know (or can obtain) a number of iterations for our code... and when we want to iterate over an iterable. The above example - of counting up to 10 - is an example of this.

{% highlight python linenos %}
def main():
    # remember: range has defaults. So this is the same as saying:
    # for counter in range(0, 10, 1)
    for counter in range(10):
        print(f"Current count: {counter}"}

if (__name__ == "__main__"):
    main()
{% endhighlight %}

<a name="l07-end"></a>Last Word
-------------------------------
You are now ready to do [Problem #06: High or Low]({{ site.url }}/py/p06).