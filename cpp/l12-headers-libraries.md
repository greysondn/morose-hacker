---
layout: page
title: C++ 12 - Headers and Libraries
permalink: /cpp/l12
---

Now for the part where life sucks less and you can start to make use of all the work you've done already instead of redoing it over and over again.

Of course we mean the part of libraries.

<a name="l12-hl"></a>Lesson 12: Headers and Libraries
======================================================
If you recall, one of the first things you learn is this:

{% highlight cpp linenos %}
#include <iostream>
using std::cout;
using std::endl;

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
{% endhighlight %}

At this point, you know enough about that to tell me what everything from the method declaration down does. However, to this point, we've largely breezed over everything above that. Literally we took this long to get to the last part of understanding what headers and libraries are, but you're finally ready to learn.

<a name="l12-headers-before"></a>Headers - Before the Beginning
===============================================================
There are several philosophies on how to do header files properly. Most of them require you to manually link in any files referenced by a header (that aren't part of the C++ standard libary) and deal with that. What a headache! Why we decided a standard should exist that made user-written code behave differently from standard libary code is beyond me, frankly.

In other languages, your inclusion is for more than just what is expected to be in a C++ header, traditionally - it's also the declarations of functions, variables, contexts, and so on. This is how the standard library largely behaves in C++ - when you include a library by name, it includes all the declarations

Therefore I would advise you of the following before continuing:

* First, that the way I am about to teach you headers isn't uncommon, but isn't, so to speak, the "C++" way, traditionally.

* Second, that headers cannot, under any circumstances, be compilable by themselves into a runnable program. If you write a header with a `main`, it will make your life miserable. Trust me.

The method we'll be learning is how to do headers - erm, how to do them in a way that leads to "header-only classes" later on down the line, a phrase you'll see often when you carouse for libraries to include.

<a name="l12-headers"></a>Headers
=================================
Your C++ files end in `.cpp`. Headers should end in `.h` or `.hpp`. Let's have an example of "Hello World!" broken into two files.

`hello.hpp`

{% highlight cpp linenos %}
// more on this later
#pragma once

// you can do your includes as usual
#include <iostream>

// namespace is new, please use it... with your own identifier
namespace morose
{
    // using goes inside the namespace, not outside of it
    using std::cout;
    using std::endl;

    // we can now define a function in the namespace if we'd like
    void hello()
    {
        cout << "Hello, world!" << endl;
    }
}
{% endhighlight %}

`hello.cpp`

{% highlight cpp linenos %}
// note the use of quotes for the path
#include "hello.hpp"

int main()
{
    // we could, for example, "using morose::hello" to shorten
    // this
    morose::hello();

    // return as usual
    return 0;
}
{% endhighlight %}

Save both of those files in the same folder, compile hello.cpp like normal, and run them.

Lo and behold, it runs! And you have now successfully written and included your first header file.

Unfortunately, now we have to break this down, bit by bit, all over again.

<a name="l12-pragma"></a>Pragma: Once
=====================================
Pragma isn't much of a word (in English), but if "being pragmatic" is "having a practical approach to doing things", then "pragma" must be that actual approach.

When we tell the preprocessor `#pragma once`, we are signalling to only include the file it is in one time. Why? if you think back, way back, to when you were told to not include all of the `std` namespace and instead select members, you will recall the warning that "you simply don't know all of the members of `std`, and a collision would cause an error".

We can cause such an error trivially:

{% highlight cpp linenos %}
#include <iostream>
using std::cout;
using std::endl;

// no problem here
void hello()
{
    cout << "Hello, world!" << endl;
}

// yes, do it again
void hello()
{
    cout << "Hello, world!" << endl;
}

// and now, the main event
int main()
{
    // which which is which?
    hello();

    // end
    return 0;
}
{% endhighlight %}

As you might imagine, it complains.

{% highlight text %}
morosehacker@hacketyhack:~$ g++ hello.cpp

hello.cpp: In function ‘void hello()’:
hello.cpp:12:6: error: redefinition of ‘void hello()’
 void hello()
      ^~~~~
hello.cpp:6:6: note: ‘void hello()’ previously defined here
 void hello()
      ^~~~~
{% endhighlight %}

As to what this has to do with that `#pragma` and our code - recall that the preprocessor *more-or-less* just puts the content of the file where the include statement is. If there were two, the compiler would see *something* defined, identically, twice like the above code does. Without that warning to the preprocessor to only include the file once, we'd have to be absolutely sure that the file is only included once, across the entire project, no matter what we need it for. And it has to be included exactly when and where it's needed.

This is absolutely doable for small projects. But once you start getting up into a few thousand lines of code, it starts to become quite hard to know what is done where, exactly. And do you really want to have to babysit your code that hard? Doesn't that defeat the purpose of letting a computer do bookkeeping where possible for you?

{% include infobox_head.html type="warning" title="Pragma Isn't Universal!" %}
You'd think that given how wonderful `#pragma` is, it'd be universally available in all compilers. Unfortunately, it's not part of the C++ specification as of yet, and it's not universally adopted as a side effect.

Given its high uptake, and how popular it is among people who want things to be simple, it's likely to become a part of the standard moving forwards. (This isn't unheard of in C++'s larger development process.) However, there is a method to do something similar that is universal called *header guards* that we did before `#pragma` existed.

A header guard works like this: Define something that doesn't happen if a preprocessor constant exists, then where it does happen define that constant so that it can't happen twice. (This basically is the Singleton pattern in a different form, which you'll learn later.)

{% highlight cpp linenos %}
#ifndef HELLO_HPP
#define HELLO_HPP
// ... contents of hello.hpp here ...
#endif
{% endhighlight %}

You are expected to use `#pragma once` in this course, but this may be useful if you find you have problems translating this knowledge to other tools.

Wikipedia lists a handy chart if you wonder where support is at right now:
[https://en.wikipedia.org/wiki/Pragma_once#Portability](https://en.wikipedia.org/wiki/Pragma_once#Portability)

{% include infobox_tail.html %}


<a name="l12-namespace"></a>Namespace
=====================================
{% highlight cpp %}
namespace morose
{
    // stuff here
}
{% endhighlight %}

As you might expect, something similar to this is how the namespace `std` is defined in the C++ standard library.

Nevertheless: **you should probably always namespace files you intend to be included in other code arbitrarily**.

Recall that when you import a member from `std` by name, it gets moved into your application's `main` namespace. Also recall the that C++ preprocessor basically drops files in where their includes are.

*If you don't namespace your code, it's directly dropped into an application's main namespace.* This would be similar to if the C++ standard library didn't namespace their code - would you know every symbol including a header dragged into `main`?

Incidentally, *just because it's namespaced doesn't mean it's not still a globalized value depending on how you use it*. Declaring a variable in namespace just so that you can access it anywhere in the namespace without effort is no better than a global the way most people rush to use it.

Also incidentally, *do not use `std` as the name of your namespace*. That is a reserved name for the C++ standard library. Typically your name or the name of the library the code is for is the preferred namespace.

<a name="l12-organization"></a>A Note on Organizing Code
========================================================
When organizing *functional code* (which is basically what you've mostly created to this point, you'll learn mostly *object-oriented* code "soon"), the typical habits are:

* To put closely related functions in one file, such as all random number generating functions in one file and all string searching code in another file.

* To put groups of related code in folders. You might put all code for interacting with strings (search, create, parse) in one folder and all code for handling ints (search, create, parse) in another folder, for example.

And that's largely the two major rules.

<a name="12-end"></a>Last Word
------------------------------
Nothing to speak of, honestly.