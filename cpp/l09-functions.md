---
layout: page
title: C++ 09 -Functions
permalink: /cpp/l09
---

{% comment %}
Did you know that "Conjunction junction, what's your function?" can be reasonably replaced with the words "function function function function"? Sadly, I couldn't work out a clever line for the conductor or this intro gag would have been so many levels of awesome I would have had to have published it on a different blog.
{% endcomment %}

In today's lesson, you'll learn one of the main ways to code your way out of a paper bag. It is, of course, `exitPaperBag(oneself)`.

<a name="l09-functions"></a>Lesson 9:Functions
==============================================
Up to this point, if you wanted to reuse code, the only way to do so was to copy and paste it. Well...

{% include infobox_head.html type="caution" title="Anti-Pattern: Copy and Paste Coding" %}

For the first time, we can talk constructively about what a bad pattern for writing code, an *anti-pattern*, is.

Copy and pasting code isn't a great way to work on a way of reusing it precisely because as you get more and more instances of the code, it becomes monstrous to maintain. A bug fixed in one copy of a code that has been copied and pasted eight times must - itself - be copy and pasted eight times.

Instead of doing this inefficient and wasteful way about it, we have many ways to reuse code properly. You're learning functions now; later on you'll learn headers (for breaking your code into multiple files), classes (for another way to break your code into related parts), and all the neat tools that go with these things.
{% include infobox_tail.html %}

... needless to say that's not how we're going to do it in the future. We can make better tools!

<a name="l09-syntax"></a>Syntax
===============================

If you recall learning variables, you will recall they have the format of:

{% highlight cpp %}
type name;
{% endhighlight %}

functions are comparable, but they have a new format:

{% highlight cpp %}
returnType name(arguments)
{
    // statements
}
{% endhighlight %}

Where...

`returnType` is any valid type to return (which we'll talk about in a moment), like you learned earlier, plus `void` which just means we won't be returning anything.

`name` is any valid name for the function, with the same basic rules as `variable` identifiers.

`arguments` are what you need given to the function so it can do its magic.

`statements` are any valid lines in C++.

<a name="l09-syntax"></a>Name Conventions
=========================================
A typical naming convention for functions is:

* Start the name with a lowercase letter, such as in `hello`. If there's more than one word in the name, capitalize the first letter of each word - as in `helloWorld`;

* Generally try to name functions as an action. That is, we would prefer `getName` over `name`. (And `sayHello` over `hello`.)

* Generally try to name functions for what they do clearly. That is, it is probably `calculateArea` or `calcArea` (or `getArea`), not `findArea` because you didn't perform a search.

* Functions can also be named for questions they answer; for example, you might write `isOdd` for a function that determines if a number is odd or not (and returns a `bool`), or `hasWeapon` for a method that checks if something has a weapon (and returns a `bool`).

* You can use underscores and numbers in a function name. It is generally discouraged. A number may not be the first character.

<a name="l09-rettype"></a>Return Types
======================================

Whatever your `returnType` is, you **must** return some value matching it. The keyword to tell the computer what you want to return is, predictably `return`.

{% highlight cpp linenos %}
// includes and whatnot stuff before

// could just be a literal
float returnPi()
{
    return 3.14;
}

// can also do it with a variable of the type
float returnPiVar()
{
    float pi = 3.14;
    return pi;
}
{% endhighlight %}

If your return type is `void`, you will return nothing.

{% highlight cpp linenos %}
// inclides and whatnot stuff before

void sayHello()
{
    cout << "Hello!" << endl;
}
{% endhighlight %}

<a name="l09-arguments"></a>Arguments
=====================================
Arguments have multiple names. You will most often hear them call "parameters" and "inputs". In general, these terms are synonymous with each other. There may be other terms.

The general syntax of an argument is: `type name`, precisely the same as a variable. If you have more than argument you want your function to have, separate them with commas. `type name, type name`. You can have as many arguments as you like, but limiting the number is generally preferred.

In a function, it looks like this.

{% highlight cpp linenos %}
// includes etc before

float calcRectArea(float length, float width)
{
    // we can access the arguments from inside the function
    return (length * width);
}

// later on, when we call that, we have to give it two floats
// this line is just an example, it's not in the right place.
float rectArea = calcRectArea(3, 12); // rectArea will be 36
{% endhighlight %}

<a name="l09-inteface"></a>Interfaces
=====================================

You may have noticed that there's a very simple property that can be shown with just the first line of a function. Ponder what you would think if you see the following line in code, with nothing else.

{% highlight cpp %}
float calcCircleArea(float radius)
{% endhighlight %}

I imagine you can tell me:

* what this function most likely does (it's named for what it does, `calcCircleArea`)

* what it expects you to give it and what it thinks it will be (a `float` it thinks will be a `radius`)

* what it returns to you (a `float`, which based on the name is probably the area of a `circle` with `radius`).

You can tell me all this *without looking into the functions innards*. You have zero clue what the lines of code in this function look like. But if you think about it, you don't *really* know the innards of, for example, `cout` or `endl`. You just know what you've been told they do.

That first line has two names. To the C++ compiler, it's the function's *declaration* - the part that defines what what a function will look like and promises that it's coming later. To programmers, in general, it's the *interface*.

An *interface* forms a contract between pieces of code. It says "if you give me this, I will give you that". Obviously, a programmer could write the above method to spit out a random number - however, that would be useless and make a programmer's job harder. In general, programmers try to make the contracts be honest.

*Soon*, you will learn one more tool - *documentation comments*. It's important to realize that documentation comments largely explain *interfaces*. Our entire ability to write and document code in nice formats like API documentation pages is based on this contract premise.

<a name="l09-where"></a>Where
=============================

Functions must be *declared* before they're used. They may be *defined* at any point.

A very normal form is to just declare and define them at once:

{% highlight cpp linenos %}
#include <iostream>
using std::cout;
using std::endl;

float calcTriangleArea(float base, float height)
{
    return ((base*height)/2.0);
}

int main()
{
    cout << calcTriangleArea(18, 7) << endl;
    return 0;
}
{% endhighlight %}

However, most people prefer to try to get `main` early in their code so that it's easier to locate. So another normal thing is to declare every method and then define them all after `main`.

{% highlight cpp linenos %}
#include <iostream>
using std::cout;
using std::endl;

float calcTriangleArea(float base, float height);

int main()
{
    cout << calcTriangleArea(12, 7) << endl;
    return 0;
}

float calcTriangleArea(float base, float height)
{
    return ((base*height)/2.0);
}
{% endhighlight %}

There is a different benefit to the second format: *you can put things in any order because you've told the compiler they're coming*. In the first format, you have to put them in the order you'll need them to exist.

In general, prefer the second format.

<a name="l08-end"></a>When
==========================

With all this, you may be wondering: *when* should I break some code out into a function?

As a general rule, the answer turns out to be:

*When you find yourself copying the same few lines of code to solve a related problem and either there are no inputs or the inputs could be parameterized.* ("Could be parameterized" just means "could be made into parameters".)

Consider the following example program.


{% highlight cpp linenos %}
#include <iostream>
using std::cout;
using std::endl;

#include <random>
using std::default_random_engine;
using std::uniform_int_distribution;

#include <chrono>


int main()
{
    // still using that starter I have yet to understand
    // TODO: learn how to do this properly (still) and fix this
    unsigned rngSeed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(rngSeed);

    // probably what struck you when you first saw that was
    // to go ahead and do every single distribution for
    // major dice.
    uniform_int_distribution<int> d2(1, 2);
    uniform_int_distribution<int> d4(1, 4);
    uniform_int_distribution<int> d6(1, 6);
    uniform_int_distribution<int> d10(1, 10);
    uniform_int_distribution<int> d12(1, 12);
    uniform_int_distribution<int> d20(1, 20);
    uniform_int_distribution<int> d100(1, 100);

    // let's roll each one just once
    cout << "d2: " << d2(generator) << endl;
    cout << "d4: " << d4(generator) << endl;
    cout << "d6: " << d6(generator) << endl;
    cout << "d10: " << d10(generator) << endl;
    cout << "d12: " << d12(generator) << endl;
    cout << "d20: " << d20(generator) << endl;
    cout << "d100: " << d100(generator) << endl;

    // end
    return 0;
}
{% endhighlight %}

I mean, this works. Just not well. And you can't use a loop here because things are slightly changing. Clearly a slightly different tact is needed.

What if instead of all these variables that are so close to the same we just *abstract* them away? Hide them in a method?

{% highlight cpp linenos %}
#include <iostream>
using std::cout;
using std::endl;

#include <random>
using std::default_random_engine;
using std::uniform_int_distribution;

#include <chrono>

// notice again you can guess this with nothing more
// than what it's going to look like - the interface
int roll(int sides);

int main()
{
    // let's roll each one just once
    cout << "d2: " << roll(2) << endl;
    cout << "d4: " << roll(4) << endl;
    cout << "d6: " << roll(6) << endl;
    cout << "d10: " << roll(10) << endl;
    cout << "d12: " << roll(12) << endl;
    cout << "d20: " << roll(20) << endl;
    cout << "d100: " << roll(100) << endl;

    // end
    return 0;
}

int roll(int sides)
{
    // it's good to have a singular return point
    // so if push comes to shove
    // make a variable to store your return value in
    // try to give it a distinct default value -
    // preferably one your function should never return
    // so you can tell if something goes horribly wrong
    int ret = -1;

    // later on we'll learn a way to use the same RNG
    // but in order to have random numbers work here for
    // now, we need to go ahead and just create it in
    // the function. If you think "static" is the answer,
    // just know you're dangerously wrong.
    unsigned rngSeed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(rngSeed);

    // now the meat and potatoes
    uniform_int_distribution<int> die(1, sides);
    ret = die(generator);

    // yes that's really it. Disregard comments and it took
    // only 6 lines
    return ret;
}
{% endhighlight %}

If you compile and run that you get... the same output. Just more readable (minus my comments) and easier to work with.

We can make this one more step easier on ourselves; here is what I would propose as a rock solid final version of that same code scrap with what you know so far.

{% highlight cpp linenos %}
#include <iostream>
using std::cout;
using std::endl;

#include <random>
using std::default_random_engine;
using std::uniform_int_distribution;

#include <chrono>

int roll(int sides);
void rollAndPrint(int sides);

int main()
{
    // let's roll each one just once
    rollAndPrint(2);
    rollAndPrint(4);
    rollAndPrint(6);
    rollAndPrint(10);
    rollAndPrint(12);
    rollAndPrint(20);
    rollAndPrint(100);

    // end
    return 0;
}

// note that because I declared all functions above,
// I can define them in any order -
// try removing declarations up above and see what happens

void rollAndPrint(int sides)
{
    // just print it, geez
    cout << "d" << sides << ": " << roll(sides) << endl;
}

int roll(int sides)
{
    // eventual return
    int ret = -1;

    // seed RNG
    unsigned rngSeed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(rngSeed);

    // roll
    uniform_int_distribution<int> die(1, sides);
    ret = die(generator);

    // return
    return ret;
}
{% endhighlight %}

As you might imagine, that will give you... the same output!

By now I'd hope you learned two things.

First, that there are several ways to do the same task in code.

Second, *that use of reusable functions can make your code easier to understand, maintain, and reuse.*

<a name="l08-end"></a>Last Word
-------------------------------
As far as I'm concerned, there's nothing else to say.