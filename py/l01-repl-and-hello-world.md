---
layout: page
title: Python 01 - REPL and Hello World!
permalink: /py/l01
---

I feel like you're talking in a language I don't speak - and you're talking it to me.

<a name="l01-repl"></a>Lesson 01: REPL and Hello World!
=======================================================

During lessons in C++ (which you should have up to lesson 15-ish if you're learning with me before starting Python at all), I often stressed that there were other ways and other languages. I may have even mentioned that there are some freelance sites which rank me as one of the top programmers in the world for Python.

This lesson is about Python. It assumes you've done, at an absolute minimum, a "Hello, World!" in C++.

Before we begin, I want you to start by shuffling what you know from C++ to the back of your mind. We will make comparisons. They will be dodgy up until the point that I explain why one or the other. For now the comparisons are largely of syntax and ease of use. Just be aware that not everything is golden in the land of Python.

Which Python?
=============

Chances are the system you're on has multiple versions of Python installed. We will be using Python 3. Python 2 is in legacy support and officially deprecated for new code. (Knowing how slow things work, we'll probably be stuck with it for a few more years.)

In order to check which python interpreter you're running, you can run the following in a terminal.

{% highlight text %}
python --version
{% endhighlight %}

My windows terminal, CMD, says the following:

{% highlight text %}
C:\Users\Dorian Greyson>python --version
Python 3.7.2rc1
{% endhighlight %}

That should work well enough. However, my WSL terminal, running Ubuntu with BASH as a terminal says this:

{% highlight text %}
greysondn@LAPTOP-27D4Q1U4:~$ python --version
Python 2.7.15rc1
{% endhighlight %}

If you get any version that starts with 2, please try `python3 --version` instead.

{% highlight text %}
greysondn@LAPTOP-27D4Q1U4:~$ python3 --version
Python 3.6.7
{% endhighlight %}

If your command prompt only says python 3.x if you type `python3 --version`, then you will have to remember to put a 3 at the end for every command that starts with `python` in these lessons.

{% include infobox_head.html type="warning" title="Don't change your default Python interpreter!" %}
Do not try to change your default python interpreter in Linux or OSX by changing which one the name `python` points to! (It isn't that hard to remember to type a 3, geez.)

Typically Python is tightly married to the system and the default version is selected to run your OS. Doing so can break your installation in ways that are a pain to recover from.
{% include infobox_tail.html %}

Short Test Drive
================

So... pop open `python` in a terminal.

Just type some garbage.

{% highlight text %}
greysondn@LAPTOP-27D4Q1U4:~$ python3
Python 3.6.7 (default, Oct 22 2018, 11:32:17)
[GCC 8.2.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> some garbage
  File "<stdin>", line 1
    some garbage
               ^
SyntaxError: invalid syntax
>>>
{% endhighlight %}

Huh. How about some simple math? What's 2+2? Other operations?

{% highlight text %}
>>> 2 + 2
4
>>> 3*4
12
>>> 4/5
0.8
>>> 7-18
-11
{% endhighlight %}

Well, that's apparently not invalid syntax anyway. How about a divide by zero?

{% highlight text %}
>>> 42/0
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
ZeroDivisionError: division by zero
{% endhighlight %}

Huh. Neat. It's not too dense. Can it do parentheticals?

{% highlight text %}
>>> 4 / 4 * 4 - 4
0.0
>>> 4 / 4 + 4 - 4
1.0
>>> 4 - (4 + 4) / 4
2.0
>>> (4 * 4 - 4) / 4
3.0
>>> 4 + 4 * (4 - 4)
4
>>> (4 * 4 + 4) / 4
5.0
{% endhighlight %}

Neat. Okay, so Python can do basic math... but what is this wizardry that doesn't exist in C++, anyway?

REPL: Read, Execute, Print Loop
===============================
Python's terminal interface to its interpreter acts as a REPL - a read, execute, print loop. In psudeocode, you could envision it as running something like this:

{% highlight cpp %}
while(true)
{
    userInput = read();
    output    = execute(userInput);
    print(output);
}
{% endhighlight %}

The interpreter **reads** input from the user, **executes** that input, **prints** the result, and then waits for the next input.

{% include infobox_head.html type="note" title="The Most Useful and Most Often Forgotten Tool" %}
Never forget the REPL is available at a keystroke. You can use it to test any python code you can conceive of - and sometimes that means you can use it to test if a package is installed... or write and execute a quick one-liner instead of writing a script for it... or just do some quick number crunching in the terminal if needbe...

In the realm of uses I never conceived of needing, we once played yahtzee with the python interpreter on a slow day in the labs by programming a die roller and then just keeping track of our own dice on a sheet of paper.
{% include infobox_tail.html %}

REPL: Hello, World!
===================
This leads us to the shortest "Hello, World!" that I know.

{% highlight text %}
>>> "Hello, World!"
'Hello, World!'
{% endhighlight %}

However, this isn't the pythonic way. The pythonic way is to use a proper `print`. So that becomes...

{% highlight text %}
>>> print("Hello, World!")
Hello, World!
{% endhighlight %}

`print` is a function that takes a single string, or anything that can be coerced to a string, and prints it to the primary output stream.

That's literally it. No headers, no tricks, nothing to expand on.

To exit the python interpreter, execute `quit()`.

Code files
==========

Python source code is executed by the interpreter in a manner that is *very nearly* the same as typing into the interpreter yourself. The standard extension for python is `.py`.

Please create and open a new file named `hello.py` and insert the following into it.

{% highlight python linenos %}
print("Hello, World!")
{% endhighlight %}

Save and exit the file, and then run `python hello.py` in your terminal.

{% highlight text %}
greysondn@LAPTOP-27D4Q1U4:~$ vim hello.py
greysondn@LAPTOP-27D4Q1U4:~$ python3 hello.py
Hello, World!
{% endhighlight %}

"Proper" Code files
===================

As soon as you see that, you're likely afraid that we're about to talk about headers, includes, security, and whatnot.

No. Just a main guard. And it's not hard.

Python is very sensitive to whitespace. You don't have to match my indents in the following code, but you do have to make sure your indentation levels line up. I would recommend using either 2 spaces or 4 spaces. I would NEVER recommend tab. (If you care about actual, strict Pythonic standards for code formatting, look up PEP-8.)

{% highlight python linenos %}
def main():
    print("Hello, World!")

if __name__ == "__main__":
    main()
{% endhighlight %}

if you run that, you're going to find out... it does the exact same thing as before. So why the guard then?

To explain that, I need to explain what's really going on here.

`def` tells python that we are about to define a function. The name follows (`main`, but it could be literally anything) along with its arguments (all none of them). The colon tells python to expect a block of code.

We then indent and provide our print statement. To end the block of code, we de-indent.

Below this, we have a conditional. The `if ___ == ___ :` should already make sense, it's the two things in those blanks that may not.

Python has metavariables that are set when the interpreter is invoked. One of those is `__name__`. For whatever python source file is the first one to be invoked (the one called at the terminal by the user, presumably), this is set to `__main__`. For every other one, its typically their fully qualified package name.

At the present time, this doesn't matter much beyond helping to scope your variables properly - it's just a good habit to pick up. On a future date, what this means is that you can have files which are both programs and libraries - if they're called directly, they execute a program, but if they're imported to use in another python program you can use functions and classes defined inside of them without invoking the program portion.

In my C++ lessons, I have an entire lesson on salvage that simply gets to be skipped in python because if you use a main guard - and it's literally as easy as the last two lines and a function that contains your main program body, along with proper code structure beyond this - you never need to go through and extract code just to salvage a library from it. It's already doubling as a library.

And believe it or not, that's it. That's the entire lesson.

<a name="l01-end"></a>Last Word
-------------------------------
You could do "Goodbye, World!"... but I'm just going to skip it for now.