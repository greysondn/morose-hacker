---
layout: page
title: C++ 13 - Scope, Reference, and Mutability
permalink: /py/l13
published: false
---

Sometimes, all you need is a constant reference to make life not suck quite so hard. Or perhaps I meant a static variable. Oh well.

<a name="l13-srm"></a>Lesson 13: Scope, Reference, and Mutability
======================================================
Up to this point, we've largely breezed over some very basic concepts (and skipped some key ones that could have made your life easier). They were scope, reference, and mutability.

Scope covers the notion of where something is valid. The scope of a variable, for example, is the area where that variable is valid.

Reference covers the ability to pass a variable's scope about, more or less, so that the same variable is in scope elsewhere.

And mutability covers the ability to change whether or not something can change at all - and how it changes.

<a name="l13-scope"></a>Scope
=============================
Scope is the only absurdly easy one of the three, honestly.

*Typically, an identifer's scope is within the level its declared and any nested blocks of code under that level.* Special keywords exist to modify beyond this in some fashion or another.

A *global scope* is any scope that encompass what we would call "everything", typically the *main* namespace (the space that also contains the function `main()`) in a program but also *the functionally largest scope in a C++ file*. If all your code were in a namespace, we would think of any variable accessible to that namespace as being global *to that namespace*. 

Many people will call this global, abandoning the nuance; many other people will call this *a namespace variable*, abandoning the problems often associated with the term "global". Philosophies differ. You are to consider them global to that namespace for this course.

As a general rule, your first order citizen should be your only global identifier. At the present, functions are our first order citizens; later, objects will be our first order citizens.

Beyond that everything should be straightforward, even without examples.

<a name="l13-reference"></a>Reference
=====================================
*Any handle on a piece of data constitutes a reference to that data.* At first this seems straightforward, but consider the following:

{% highlight cpp linenos %}
#include <iostream>
using std::cout;
using std::endl;

void tryToChange(int thisInt)
{
    thisInt = thisInt + 1;
    cout << "During value: " << thisInt << endl;
}

int main()
{
    int anInt = 15;

    cout << "Before value: " << anInt << endl;
    tryToChange(anInt);
    cout << "After value:  " << anInt << endl;

    return 0;
}
{% endhighlight %}

Are you sure you know what this will do? Most importantly, is the "during" value equal to the "after" value?

{% highlight text %}
Before value: 15
During value: 16
After value:  15
{% endhighlight %}

Of course, this is somewhat good! The function's scope is well defined (and observed) and side-effects are minimized! But if we need two returns, suddenly this doesn't work. We need a tool to enable this (and other usecases).

The way that this variable has been passed in is called *pass-by-value*. The *value of a variable* - not a *handle on the variable itself* - has been passed. What you need is a *handle* - a *reference* to the underlying data. Take a look at this subtly different version.

{% highlight cpp linenos %}
#include <iostream>
using std::cout;
using std::endl;

void tryToChange(int &thisInt)
{
    thisInt = thisInt + 1;
    cout << "During value: " << thisInt << endl;
}

int main()
{
    int anInt = 15;

    cout << "Before value: " << anInt << endl;
    tryToChange(anInt);
    cout << "After value:  " << anInt << endl;

    return 0;
}
{% endhighlight %}

The subtle difference comes on line 5. Here is the value one on top of the new one.

{% highlight cpp %}
void tryToChange(int thisInt)
void tryToChange(int &thisInt)
{% endhighlight %}

With the addition of scare more than an ampersand, we completely change the way the function behaves:

{% highlight text %}
Before value: 15
During value: 16
After value:  16
{% endhighlight %}

We can now pass variables by their reference (*pass-by-reference*), which matters considerably more if you ever need multiple variables at once out of a key function.

{% highlight cpp linenos %}
#include <iostream>
using std::cout;
using std::endl;

/**
 * Calculate perimeter and area of a square with side length of side.
 *
 * @param side         length of a side of square
 * @param outPerimeter variable to output perimeter into
 * @param outArea      variable to output area into
 */
void calcPerimeterAndAreaOfSquare(float side, float &outPerimeter, float &outArea)
{
    outArea      = side * side;
    outPerimeter = side * 4;
}

/**
 * plain jane main
 *
 * @return typical return, probably zero, let's be honest
 */
int main()
{
    float sideLength = 4.2;
    cout << "for a square with side length " << sideLength << endl;
    
    float perimeter = 0.0;
    float area      = 0.0;

    calcPerimeterAndAreaOfSquare(sideLength, perimeter, area);

    cout << "perimeter: " << perimeter << endl;
    cout << "area: " << area << endl;

    return 0;
}
{% endhighlight %}

This, of course, requires you to document *that some of the variables will be changed as a side effect of the function*. See the above for an example of such documentation.

Most importantly, *passing a variable by reference allows you to change the scope of that variable by enabling you to pass it from one function or method to another, generally.*

<a name="l13-mutability"></a>Mutability
=======================================
Mutability, at its core, covers how much a variable may change and when it may do so.

In general, there is only one that you need to know right now, one to use freely as seems fit.

The one to use is `const`, short for *constant*. Anything that would normally be a variable, declared const, will refuse to change. Generally speaking, *a value that is used often, like pi, should be a named constant*, and *arguments that you don't intend to change inside a function should also be declared constant*.

When used to declare a "variable", we call that "variable" a "constant". Constants have the same rules as variables for names, but typically their names are in all capital letters.

{% highlight cpp %}
const float PI = 3.14;
const int NUMBER_OF_DAYS_IN_WEEK = 7;
{% endhighlight %}

When used on an argument to a function, capitalization is seen as inappropriate.

{% include infobox_head.html type="info" title="Constants Even When Not Actually Constant" %}
Remember that how you write code - and what you write - conveys data to other programmers.

In the programming language Python, there's no constants. Everything is a variable. One of the side effects is that there is a need for a way to declare something as "please don't touch" when it needs to be readily accessible and still not changable.

A common convention is to just name it in all caps, like we did here.

{% highlight python %}
# note that python has a different syntax from C++
PI = 3.14
NUMBER_OF_DAYS_IN_WEEK = 7
{% endhighlight %}

This, in fact, turns out to be true in basically any language - naming something in this way, in all capitals, conveys to other programmers that it's meant to be constant.
{% include infobox_tail.html %}

<a name="13-end"></a>Last Word
------------------------------
Guh, I'm tired, commit and forget for now.