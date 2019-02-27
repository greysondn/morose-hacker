---
layout: page
title: C++ 08 - Arrays
permalink: /cpp/l08
---

I've got a love bunch of data points, doodle-de-doo, there they are a standing in a row...

<a name="l08-arrays"></a>Lesson 08:Arrays
=========================================

Imagine we want to store - or work with - a collection of data we know the length of ahead of time. It might be, for example, the set of channels in a color (there's three of them) or a list of characters (there's a ridiculous number, but let's say there's 26 to keep ourselves sane.)

We could just use three ints.

{% highlight cpp linenos %}
int red = 0;
int green = 0;
int blue = 0;
{% endhighlight %}

But, ideally, we'd want something that reflects that these three objects go together. That's where arrays come in. (Later on, you'll learn many other ways to store data, many of which may make more sense for certain tasks. For now, this is the answer we have!)

<a name="l08-declaring"></a>The Basics of Array
===============================================
An array is a variable type. It takes the form:

{% highlight cpp %}
type identifier[length];
{% endhighlight %}

Where...

* *type* is the data type to be stored in the array. (Arrays must only store one data type per array.)
* the *identifier* is any valid variable name.
* the *length* is an unsigned integer which indicates how many elements will be stored in the array.

To assign values to initialize your array, include them - comma separated - inside curly braces.

{% highlight cpp %}
int color[3] = {0, 1, 2};
{% endhighlight %}

You can also set each cell of the array by hand. The first cell is `0` (this is called *zero-based indexing*) and each cell after that is one cell higher.

The accessor takes the form:

{% highlight cpp linenos %}
arrayIdentifier[cellNumber];
{% endhighlight %}

That particular bit of code doesn't really do anything, but it provides the syntax for the following:

{% highlight cpp linenos %}
int color[3];

color[0] = 68;
color[1] = 42;
color[2] = 255;
{% endhighlight %}

If you have a large array, a typical way to initialize it is to use the *length* in a *for* loop.

{% highlight cpp linenos %}
int namesOfBeersIKeepOnMyWall[99];

for(int i = 0; i < 99; i++)
{
    namesOfBeersIKeepOnMyWall[i] = 0;
}
{% endhighlight %}

Like all variables, it's a good idea to either initialize the value of each cell of your array *or* never read the value before you can be absolutely sure something has been placed there.

<a name="l08-accessor"></a>The Accessor
----------------------------------------
This should be your first time seeing the *accessor* syntax so far in studying with me. (The square brackets used to access certain elements of the array.)

I would encourage you to commit that syntax to memory; we'll see it a lot as we move forwards, for anything that's basically a collection of data with specific entries to reach in for.

You've already learned a little bit about one data type that supports the *accessor*, incidentally, before this.

{% highlight cpp linenos %}
#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

int main()
{
    // string of some chars we need to sing a song.
    string songChars = "ABCDE";

    // This is just a silly song. The words don't mean a thing.
    cout << songChars[1] << " " << songChars[0] << " - bay!" << endl;
    cout << songChars[1] << " " << songChars[4] << " - be! << endl;

    return 0;
}
{% endhighlight %}

<a name="l08-limitations"></a>A Note on the Length of Arrays
------------------------------------------------------------
It may be wise to note that *arrays must have a fixed length when they are declared*. This means you should (generally) know the length as you're writing the code itself.

One side effect of this property is that arrays don't support any *easy* way to obtain their length. (There is a method using pointer arithmetic, but as soon as I said "pointer" your first impulse should have been to politely decline the opportunity.)

{% include infobox_head.html type="info" title="Death, Death to Magic Numbers Everywhere!" %}

As a general rule, for short code, your intentions are clear enough and this is a non-issue. But for longer code, imagine you declared an array with a length of `191` and later on used that value `191` without much warning.

People are going to look at that and scratch their heads. "Where'd this random, *magic number* that seems to make things work come from?"

The solution is to create a named variable (or constant) with the length of your array in it, and then to use that when you need to work wtih your array.

The earlier snippet of code is better written as:

{% highlight cpp linenos %}
int namesOfBeersIKeepOnMyWall_length = 99;
int namesOfBeersIKeepOnMyWall[namesOfBeersIKeepOnMyWall_length];

for(int i = 0; i < namesOfBeersIKeepOnMyWall_length; i++)
{
    namesOfBeersIKeepOnMyWall[i] = 0;
}
{% endhighlight %}

Of course most variable names will be much more succinct than my humorous examples often are.

{% highlight cpp linenos %}
int beers_length = 99;
int beers[beers_length];

for(int i = 0; i < beers_length; i++)
{
    beers[i] = 0;
}
{% endhighlight %}

{% include infobox_tail.html %}

<a name="l08-end"></a>Last Word
-------------------------------
You are now ready to do [Problem #07: Cipher]({{ site.url }}/cpp/p07).