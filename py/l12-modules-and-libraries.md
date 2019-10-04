---
layout: page
title: Python 12 - Modules and Libraries
permalink: /py/l12
---

Now for the part where life sucks less and you can start to make use of all the work you've done already instead of redoing it over and over again.

Of course we mean the part of libraries.

{% include infobox_head.html type="caution" title="Writing in Progress" %}
This lesson was rapidly adapted via copy+paste and patchwork from the related C++ lesson. As a side effect, some things may have been missed or may still refer to their C++ counterparts.
{% include infobox_tail.html %}

<a name="l12-hl"></a>Lesson 12: Modules and Packages
=====================================================
At this point, it's safe to say you've learned something like this.

{% highlight python linenos %}
from random import randrange

def main():
    print(str(roll(20)))

def roll(sides):
    return (randrange(sides) + 1)

if __name__ == "__main__":
    main()
{% endhighlight %}

At this point, you should be able to tell me what the two function declarations do clearly.

However - althought you can likely articulate that line 1 imports `randrange` from the `random` module, it's a phrase said with no tangible comprehension of what that means. A module seems like this magical place that code is stored with no real meaning behind the phrase.

And likewise, with lines 9 and 10 - perhaps you know that it's a python main guard, but you don't know any case where it's actually useful, only that it's something that's been drilled into you to make use of. An explanation was given, likely in passing, if I'm doing my job properly, but no concrete explanation was given for what goes on here.

And this is where we begin - with two aspects of this code which have largely been treated like black magic that you just need to believe in for it to work out well. This is the lesson where belief should (hopefully) become some degree of knowledge. (It's almost as though my primary goal is to eliminate all the secrets and make your faith be replaced by actual knowledge or something.)

<a name="l12-before"></a>Rethinking Code Execution - Before the Beginning
=========================================================================
In order to understand the notions that are about to be exposed to you, it's important to reframe how you're expected to think about source files.

In many languages that are **not** Python, such as C++, you have *source code* which is given to a *compiler* which transforms it into a *runnable binary*. The *source code* may request other code (typically in the form of *libraries*) which the *compiler* will arrange in some way to make everything work.

{% include photoplasty.html img="/py/l12/01-compiled-model.png" caption="A visual of this basic model of compiled languages" %}

This model for understanding compiled languages is incomplete and simple, and glosses over details, but is functional enough for what you need to know to understand Python's model.

...

In interpreted languages, the *source code* (which many people call a *script*, whether or not it's correct) is translated into commands for the computer and ran directly. The interpreter maintains a *context*, where it loads any additional *source files* requested by the *source code*, and then executes the *source code* in that *context*.


{% include photoplasty.html img="/py/l12/02-interpreted-model.png" caption="A visual of this basic model of intpreted languages" %}

Like before, this is a very glossy, simple model for how such languages work.

...

The important distinction between the two of these is that one is assembled into directions for the computer in advance (compiled languages) and the other is assembled into directions for the computer when it's ran (interpreted languages). This distinction carries many positive and negative factors - it's a tradeoff - but the main one which comes just from when that step is located is that *interpreted languages are typically slower because they need to interpret the code as its running*.

Several techniques have arisen over time to help close that gap up somewhat. 

One of them in particular, *interpreter virtual machines* (IVM, here, for short), compile the code to an *intermediary bytecode* which is subsequently executed by the IVM. It's not too important to even have a model of this clear in your head - what is important is that the IVM is part of the interpreter's context, and that adding a compilation step means that certain optimizations that would only be available to compiled languages become available to the interpreter through use of this technique.

The modern use of IVMs has somewhat blurred the lines between "interpreted" and "compiled" languages. Typically, it's true that a language is interpreted even if it has an IVM, but this leads to really murky areas around lanugages such as *Java*, which has the *Java Virtual Machine* (JVM) and yet is not interpreted in anything near the same way as most interpreted langages are (to the extent that it is widely considered and agreed to be a compiled language).

...

This leads us to Python. Python is an interpreted language using an IVM. If you're importing a module, you'll even find the intermediary version alongside the original source, in a `pycache` directory.

And now we're ready to address the immediate question, which is "what is a module?"


<a name="l12-modules"></a>Modules
=================================
{% include infobox_head.html type="info" title="About Some File Path Conventions" %}
It is important that from here forwards the first comment in example source files is intended as the filename. If the comment reads `bar.py`, then if all the files were inside a folder named `foo`, the file would be at `foo/bar.py`.

The "real", literal file path doesn't matter. Only where the files are relative to each other.

Generally, you're not expected to do the same. It's provided for your benefit.
{% include infobox_tail.html %}

So the real meat and bones of this comes down to something simple but probably baffling: Python doesn't make any real distinction between modules and normal source files. **Your source files are already modules**.

Consider the following:

{% highlight python linenos %}
# moduleExample.py 
'''
A contrived module example.
'''
def input2(prompt):
    '''
    Provides a 2 line prompt for input. I noticed I tend
    to write one anyway, every time I write something.
    
    args:
        prompt  str     first line of prompt.
        
    return:
        object  whatever the user puts in.
    '''
    print(prompt)
    return(input("$> "))

def input2Int(prompt):
    '''
    prompts the user for an integer.
    
    args:
        prompt  str     text for prompt.
    
    return
        int     whatever the user puts in
    '''
    return(int(input2(prompt)))

def printName():
    '''
    Prints the value of the __name__ metavar.
    '''
    print(__name__)

# standard pythonic main guard
if __name__ == "__main__":
    # no main, as it'd be a one-liner anyway.
    printName()
{% endhighlight %}

Running that directly (as you have for everything so far) will output the value of `__name__`, which shouldn't surprise you.

{% highlight text %}
C:\Users\Dorian Greyson\py11>python moduleExample.py
__main__
{% endhighlight %}

Let's make a second file which includes that function.

{% highlight python linenos %}
# namechange.py
'''
There's really nothing in this, it's just to show that imported
modules have a different __name__.
'''
from moduleExample import printName

if __name__ == "__main__":
    printName()
{% endhighlight %}

There's some commentary to be had here, but let's just run it first. The outcome might surprise you.

{% highlight text %}
C:\Users\Dorian Greyson\py11>python namechange.py
moduleExample
{% endhighlight %}

Remember that `printName()` is part of `moduleExample`, but we didn't run it by asking Python to run the file directly. We instead imported that function and called it from another script. Doing so changed the `__name__` variable's contents. The `__name__` variable for a module *is largely dependent on the context in which it is checked from*. In general, it should be the module's name, with the exception of it being `__main__` for the module used as the main entry point of your Python application.

This is the purpose of the main guard. It enables you to use a module as an importable source *and* and executable script. In other words, you can *selectively reuse part of the code if you find a use for it*, with minimal effort.

<a name="l12-pycache"></a>Pycache
=================================
Incidentally, there are side effects you may not expect from that.

{% highlight text %}
C:\Users\Dorian Greyson\py11>dir
 Directory of C:\Users\Dorian Greyson\py11

03-Oct-19  21:58               158 01.py
03-Oct-19  22:40               854 moduleExample.py
03-Oct-19  22:48               210 namechange.py
03-Oct-19  22:49    <DIR>          __pycache__
               3 File(s)          1,222 bytes
               3 Dir(s)  52,260,556,800 bytes free

C:\Users\Dorian Greyson\py11>dir __pycache__
 Directory of C:\Users\Dorian Greyson\py11\__pycache__

03-Oct-19  22:49             1,028 moduleExample.cpython-37.pyc
               1 File(s)          1,028 bytes
               2 Dir(s)  52,260,556,800 bytes free
{% endhighlight %}

Let's take a look at that file, shall we? I could list the directory's contents, but I don't want to put garbage in my web page... So I'm going to use a hex editor. Here's the view `hexcurse` presents, with an explanation of what's where.

{% highlight text %}
+- Left Hand UI boundary, you can ignore it
|
|+- First address in row, so that you can index it by rows. Counted in hexadecimal.
||
||        +- Bytes in the row. These go on two characters a piece for a ways.
||        |
||        |                                                                  +- scrollbar in the ui
||        |                                                                  |
||        |                                                                  | +- ASCII view of bytes
||        |                                                                  | |
||        |                                                                  | |         Ui Boundary-+
||        |                                                                  | |                     |
VV        V                                                                  V V                     V 
│00000000 42 0D 0D 0A 00 00 00 00 26 B1 96 5D 56 03 00 00 E3 00 00 00 00 00 │▒│B.......&..]V.........│
│00000016 00 00 00 00 00 00 00 02 00 00 00 40 00 00 00 73 2E 00 00 00 64 00 │▒│...........@...s....d.│
│0000002C 5A 00 64 01 64 02 84 00 5A 01 64 03 64 04 84 00 5A 02 64 05 64 06 │▒│Z.d.d...Z.d.d...Z.d.d.│
│00000042 84 00 5A 03 65 04 64 07 6B 02 72 2A 65 03 83 00 01 00 64 08 53 00 │▒│..Z.e.d.k.r*e.....d.S.│
│00000058 29 09 7A 1D 0A 41 20 63 6F 6E 74 72 69 76 65 64 20 6D 6F 64 75 6C │▒│).z..A contrived modul│
│0000006E 65 20 65 78 61 6D 70 6C 65 2E 0A 63 01 00 00 00 00 00 00 00 01 00 │▒│e example..c..........│
│00000084 00 00 02 00 00 00 43 00 00 00 73 10 00 00 00 74 00 7C 00 83 01 01 │▒│......C...s....t.|....│
│0000009A 00 74 01 64 01 83 01 53 00 29 02 7A F2 0A 20 20 20 20 50 72 6F 76 │▒│.t.d...S.).z..    Prov│
│000000B0 69 64 65 73 20 61 20 32 20 6C 69 6E 65 20 70 72 6F 6D 70 74 20 66 │▒│ides a 2 line prompt f│
│000000C6 6F 72 20 69 6E 70 75 74 2E 20 49 20 6E 6F 74 69 63 65 64 20 49 20 │▒│or input. I noticed I │
│000000DC 74 65 6E 64 0A 20 20 20 20 74 6F 20 77 72 69 74 65 20 6F 6E 65 20 │▒│tend.    to write one │
│000000F2 61 6E 79 77 61 79 2C 20 65 76 65 72 79 20 74 69 6D 65 20 49 20 77 │▒│anyway, every time I w│
│00000108 72 69 74 65 20 73 6F 6D 65 74 68 69 6E 67 2E 0A 20 20 20 20 0A 20 │▒│rite something..    . │
│0000011E 20 20 20 61 72 67 73 3A 0A 20 20 20 20 20 20 20 20 70 72 6F 6D 70 │▒│   args:.        promp│
│00000134 74 20 20 73 74 72 20 20 20 20 20 66 69 72 73 74 20 6C 69 6E 65 20 │▒│t  str     first line │
│0000014A 6F 66 20 70 72 6F 6D 70 74 2E 0A 20 20 20 20 20 20 20 20 0A 20 20 │▒│of prompt..        .  │
│00000160 20 20 72 65 74 75 72 6E 3A 0A 20 20 20 20 20 20 20 20 6F 62 6A 65 │▒│  return:.        obje│
│00000176 63 74 20 20 77 68 61 74 65 76 65 72 20 74 68 65 20 75 73 65 72 20 │▒│ct  whatever the user │
│0000018C 70 75 74 73 20 69 6E 2E 0A 20 20 20 20 7A 03 24 3E 20 29 02 DA 05 │▒│puts in..    z.$> )...│
│000001A2 70 72 69 6E 74 DA 05 69 6E 70 75 74 29 01 DA 06 70 72 6F 6D 70 74 │▒│print..input)...prompt│
│000001B8 A9 00 72 04 00 00 00 FA 2D 43 3A 5C 55 73 65 72 73 5C 44 6F 72 69 │▒│..r.....-C:\Users\Dori│
│000001CE 61 6E 20 47 72 65 79 73 6F 6E 5C 70 79 31 31 5C 6D 6F 64 75 6C 65 │▒│an Greyson\py11\module│
│000001E4 45 78 61 6D 70 6C 65 2E 70 79 DA 06 69 6E 70 75 74 32 05 00 00 00 │▒│Example.py..input2....│
│000001FA 73 04 00 00 00 00 0B 08 01 72 06 00 00 00 63 01 00 00 00 00 00 00 │▒│s........r....c.......│
│00000210 00 01 00 00 00 03 00 00 00 43 00 00 00 73 0C 00 00 00 74 00 74 01 │▒│.........C...s....t.t.│
│00000226 7C 00 83 01 83 01 53 00 29 01 7A 9C 0A 20 20 20 20 70 72 6F 6D 70 │▒│|.....S.).z..    promp│
│0000023C 74 73 20 74 68 65 20 75 73 65 72 20 66 6F 72 20 61 6E 20 69 6E 74 │▒│ts the user for an int│
│00000252 65 67 65 72 2E 0A 20 20 20 20 0A 20 20 20 20 61 72 67 73 3A 0A 20 │▒│eger..    .    args:. │
│00000268 20 20 20 20 20 20 20 70 72 6F 6D 70 74 20 20 73 74 72 20 20 20 20 │▒│       prompt  str    │
│0000027E 20 74 65 78 74 20 66 6F 72 20 70 72 6F 6D 70 74 2E 0A 20 20 20 20 │▒│ text for prompt..    │
│00000294 0A 20 20 20 20 72 65 74 75 72 6E 0A 20 20 20 20 20 20 20 20 69 6E │▒│.    return.        in│
│000002AA 74 20 20 20 20 20 77 68 61 74 65 76 65 72 20 74 68 65 20 75 73 65 │▒│t     whatever the use│
│000002C0 72 20 70 75 74 73 20 69 6E 0A 20 20 20 20 29 02 DA 03 69 6E 74 72 │▒│r puts in.    )...intr│
│000002D6 06 00 00 00 29 01 72 03 00 00 00 72 04 00 00 00 72 04 00 00 00 72 │▒│....).r....r....r....r│
│000002EC 05 00 00 00 DA 09 69 6E 70 75 74 32 49 6E 74 13 00 00 00 73 02 00 │▒│......input2Int....s..│
│00000302 00 00 00 0A 72 08 00 00 00 63 00 00 00 00 00 00 00 00 00 00 00 00 │▒│....r....c............│
│00000318 02 00 00 00 43 00 00 00 73 0C 00 00 00 74 00 74 01 83 01 01 00 64 │▒│....C...s....t.t.....d│
│0000032E 01 53 00 29 02 7A 33 0A 20 20 20 20 50 72 69 6E 74 73 20 74 68 65 │▒│.S.).z3.    Prints the│
│00000344 20 76 61 6C 75 65 20 6F 66 20 74 68 65 20 5F 5F 6E 61 6D 65 5F 5F │▒│ value of the __name__│
│0000035A 20 6D 65 74 61 76 61 72 2E 0A 20 20 20 20 4E 29 02 72 01 00 00 00 │▒│ metavar..    N).r....│
│00000370 DA 08 5F 5F 6E 61 6D 65 5F 5F 72 04 00 00 00 72 04 00 00 00 72 04 │▒│..__name__r....r....r.│
│00000386 00 00 00 72 05 00 00 00 DA 09 70 72 69 6E 74 4E 61 6D 65 1F 00 00 │▒│...r......printName...│
│0000039C 00 73 02 00 00 00 00 04 72 0A 00 00 00 DA 08 5F 5F 6D 61 69 6E 5F │▒│.s......r......__main_│
│000003B2 5F 4E 29 05 DA 07 5F 5F 64 6F 63 5F 5F 72 06 00 00 00 72 08 00 00 │▒│_N)...__doc__r....r...│
│000003C8 00 72 0A 00 00 00 72 09 00 00 00 72 04 00 00 00 72 04 00 00 00 72 │▒│.r....r....r....r....r│
│000003DE 04 00 00 00 72 05 00 00 00 DA 08 3C 6D 6F 64 75 6C 65 3E 04 00 00 │▒│....r......<module>...│
│000003F4 00 73 0A 00 00 00 04 01 08 0E 08 0C 08 07 08 02                   │▒│.s..............      │
{% endhighlight %}

It's not overly important to understand this byte for byte. Mostly I wanted you to have a chance to see what is here so you could hopefully grasp that this is what the interpreter is "really" working with. You can see that quite a bit of stuff that we wrote - and quite a bit we didn't *seem* to write - wound up in the cached intermediary file. It's quite unlikely I'll ever speak of it again - such matters are rarely something programmers should have to concern themselves with.

This should be the bytecode that is given to the Python interpreter. This is also why it's a sort of debated topic whether languages with an IVM are interpreted or compiled. After all, this file is basically a compilation of the module source we provided. It's going to be ran by the interpreter no different than the JVM runs compiled Java, and we call that a compiled language.

I don't have the answers to these questions, and while I can't speak for everyone, I don't think anyone has an answer that we can all agree on. The truth is the lines are blurry and if we draw a solid line someone would make something as an exception to that solid line just to make the conversation chaotic again because that's just how we are, as programmers.

To me, Python is an interpreted language. It is however a proper language, not merely a scripting language. Articulating that distinction is hard, especially since python can be used for scripting.

<a name="l12-packages"></a>Packages
===================================
While it's good to group your related code and functions together into *modules*, there comes a time when you have to ask "what do I do with related *modules*? How do I keep things organized on my file system?"

In most languages, we'd say to "organize your souce code into libraries". In Python, we say "organize your modules into *packages*". What this really means is to sort them into folders with some instruction on how to locate things for the interpreter.

This sounds far worse than it really is. Consider the following files. Note that they're inside folders. Also note that I'm using the same base folder I've been using thus far for thise lesson.



...

{% highlight python linenos %}
# morose/input.py
'''
Collection of reusable input functions, morose hacker flavored.
'''
def input2(prompt):
    '''
    Provides a 2 line prompt for input. I noticed I tend
    to write one anyway, every time I write something.
    
    Yes, this is defined in two separate modules. The example is
    definitely contrived, no doubt about that.

    args:
        prompt  str     first line of prompt.
        
    return:
        object  whatever the user puts in.
    '''
    print(prompt)
    return(input("$> "))
{% endhighlight %}

{% highlight python linenos %}
# morose/fib.py
'''
Collection of reusable input functions, morose hacker flavored.
'''
def fibIter(index):
    '''
    defines an fibonacci number generator based on iteration.

    args:
        index       uint >= 1       which fibonacci number you want.
        
    return:
        int fibonnacci number index.
    '''
    first = 1
    second = 1
    ret = 0
    
    if ((index == 1) or (index == 2)):
        ret = 1
    else:
        for i in range(index - 2):
            ret    = second + first
            first  = second
            second = ret
    
    return ret
{% endhighlight %}

{% highlight python linenos %}
# libraryExample.py
'''
Quick and dirty example of library usage.
Asks user for which fibonacci number they want and
calculates it and outputs it.
'''
from morose.fib import fibIter
from morose.input import input2

def main():
    index = int(input2("Please input index of fibonacci number you want."))
    fNum = fibIter(index)
    
    print("")
    print(f"That would be {fNum}")

if __name__ == "__main__":
    main()
{% endhighlight %}

Oh no! It's the dot notation! (And I should remove this joke when I don't have a student that joke applies to!)

Line 7 features a dot, as does line 8. The dot can be thought of as an indicator for hierarchies (structures of things one on top of another, or one under another). For example, you know that the `fib` module part of the `morose` package, so `morose.fib` is its name. And this works for any package. If you had a module `zap` as part of the `baz` package as part of the `bar` package as part of the `foo` package, its name would be `foo.bar.baz.zap`. No matter how deep it goes.

So if you run this libraryExample, here is what happens.

{% highlight text %}
C:\Users\Dorian Greyson\py11>python libraryExample.py
Please input index of fibonacci number you want.
$> 15

That would be 610
{% endhighlight %}

Lo and behold, you now know how to create and import some libraries!

<a name="l12-tricks"></a>Tricks of the Trade
============================================
***You can just import the module and use the dot notation to access specific functions.***

{% highlight text %}
C:\Users\Dorian Greyson\py11>python
Python 3.7.2rc1 (tags/v3.7.2rc1:75a402a217, Dec 11 2018, 23:05:39) [MSC v.1916 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license" for more information.
>>> import morose.fib
>>> morose.fib.fibIter(10)
55
{% endhighlight %}

***You can alias imports using the `as` keyword to help save some keystrokes***

{% highlight text %}
C:\Users\Dorian Greyson\py11>python
Python 3.7.2rc1 (tags/v3.7.2rc1:75a402a217, Dec 11 2018, 23:05:39) [MSC v.1916 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license" for more information.
>>> import morose.fib as cake
>>> cake.fibIter(11)
89
{% endhighlight %}

***You can import all members of a module by using an asterisk. `*` ***

{% highlight text %}
C:\Users\Dorian Greyson\py11>python
Python 3.7.2rc1 (tags/v3.7.2rc1:75a402a217, Dec 11 2018, 23:05:39) [MSC v.1916 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license" for more information.
>>> from moduleExample import *
>>> input2("Input some trash")
Input some trash
$> some trash
'some trash'
>>> # remember it's the module's name
...
>>> printName()
moduleExample
{% endhighlight %}

"And more!", but you'll learn those on your own, over time.

{% include infobox_head.html type="info" title="Ain't Nobody Got Time For Copy and Paste" %}
What would be really great is if you had some way to put these files somewhere you could always find them, no matter where you try to import them.

Yep.

Over in the [Python docs](https://docs.python.org/3/tutorial/modules.html#the-module-search-path), you can find out that the following locations are checked for modules on import:
* the directory containing the input script, or else the directory the python interpreter was invoked from.
* the `PYTHONPATH` system variable.
* some installation dependent default path.

Yep.

In windows you can open a terminal and type `echo %PYTHONPATH%` to see its contents. In linux, this becomes `echo $PYTHONPATH`. In both cases it's likely they're uninitialized. Creating new system variables is an exercise left to the reader; however, I would recommend picking a new folder and adding that folder to `$PYTHONPATH` for working directories full of modules that are not fit or prepared for distribution to other people. In theory, only one is likely to be necessary - so long as you keep everything organized properly in that folder. In practice... hard to know. I've never needed such a folder.
{% include infobox_tail.html %}

<a name="l12-the-last-word"></a>The Last Word
=============================================
Nothing comes to mind, although it's a good time to reorganize your code into reusable, sensible modules and get ready to be expected to have code built up to help you deal with anything that is thrown at you. Very soon you will learn some new theoretical tools to make this even better, but also harder. We're almost out of things to cover in terms of tools for functional programming in python.

If you need a challenge, try implementing *Nim*, with an AI that exhibits perfect play.