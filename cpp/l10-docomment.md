---
layout: page
title: C++ 10 - Standard Doc Comments
permalink: /cpp/l10
---

Now for the part where you learn to start hating me if you haven't learned already - the most boring part of any job.

Documentation.

<a name="l10-sdc"></a>Lesson 10: Standard Doc Comments
======================================================
To now, if I wanted you to document something, I just asked you to quickly throw a line comment at it so I had a gist of what was going on. There was no need for me to be able to generate documentation for your work or anything like that.

We are steadily approaching a point where that will change, and the best thing to do is to beat into your head some good practices so that you can work with other people. This also will give you some understanding of how other people have written their documentation, so that when you see it you can interpret it quickly and easily.

There are several syntaxes for standard documentation in source code. The one I plan to teach you - *JavaDoc style* - originates in the Java programming language and the tool for documentation there, JavaDoc.

"But!" - I hear you cry - "This isn't Java! This is C++!" ... and you know what? You're absolutely right. However, if I can pick a robust syntax to do documentation in that you can find a parser for in almost any language, JavaDoc will be it. (Notably, any language I can teach you that's non-esoteric is documentable in this format.) So, that's the syntax we're learning.

<a name="l10-toolkit"></a>Toolkit
=================================

"But!" - I hear you cry - "There's no CPPDoc!"

And you're absolutely right. We're going to use a parser that can work for this well. We're going to use... doxygen.

{% highlight bash %}
# update package cache
sudo aptitude update

# if you don't have aptitude, just use apt-get
sudo apt-get update

# doxygen
sudo aptitude install doxygen

# we also want graphviz
sudo aptitude install graphviz
{% endhighlight %}

Later versions of these lesson plans will include this in the earlier part, when everything was supposed to be installed at step zero.

<a name="l10-syntax"></a>Basic Syntax
=====================================

The reason I didn't introduce *block comments* up to this point - despite the fact you may have seen othe tutorials and what not cover them alongside - is that *block comments* are used to do documentation comments for most documentation parsers.

A block comment starts with a forward slash and an asterisk - `/*` - and ends with an asterisk and a forward slash `*/`. Everything between the two is a comment.

{% highlight cpp %}
/* everything between is a comment */

/* you can
   use line
   breaks */

/* most people will use a much
 * easier to spot
 * notation however
 */
{% endhighlight %}

Specifically, a doc comment starts with a forward slash followed by ***two*** astersisks - `/**`.

{% highlight cpp %}
/**
 * This is kinda how you will see standard doc
 * comments laid out.
 */
{% endhighlight %}

Generally speaking, the first sentence or the first line is
considered the short description (should be just a few words long if possible); the rest is the long description. Generally people will separate the two with a line break.

{% highlight cpp %}
/**
 * This is a short description.
 *
 * There was a lot more that could be said that
 * was useful, but the idea is to make the short
 * description enough to to be useful and provide
 * more if it's likely to be needed. You may, in
 * fact, find that short descriptions are usually
 * just fine for your work.
 */
{% endhighlight %}

But that's not something to just toss anywhere.

<a name="l10-where"></a>Where?
==============================

Doc comments, as far as what you know, only can go two places.

The first is at the start of your source code. At that place, it's expected anything you say relates to the *entire source file*. I am not overly concerned about this (right now or ever, really, in my experience), but you can look into it if you'd like. (There is one tag, however, I'll talk about here in a minute because of how doxygen works.)

The second is immediately before a function's **declaration**. At that place, it's expected anything you say has to do with the *function*. This I do care about.

The documentation should only cover the *interface* of everything. Nobody needs to know *how things are implemented (the implementation details) in doc comments.*

Documenting `roll()` from before might look like this with what you know so far:

{% highlight cpp %}
/**
 * Rolls a die with some number of sides.
 */
int roll(int sides);
{% endhighlight %}

<a name="l10-block"></a>Block Level Tags
========================================
You may have noticed that we didn't really document anything about the return or the parameters. We just gave a good description.

You'd probably think this is fine but... it's not, honestly.

Block level tags cover specific aspects of what you're documenting with your comment. They go at the end of the doc comment.

For now, I want you to worry only about three of them.

At the top of a file, `@file` provides the name of a file and forces doxygen to document it if it's missing certain features that doxygen looks specifically for.

Before a function, `@param` explains a parameter. It should be followed by the name of the paramter and then what it is. The type can be inferred by the documentation generator, so you don't have to worry about that.

Before a fucntion, `@return` explains the function's return. It should be followed by a description of what it is. Once again, the type can be inferred by the documentation generator, so you don't have to worry about it.

With these last two together, remember that you don't need to repeat yourself, which may let you make the brief description even briefer.

{% highlight cpp %}
/**
 * Rolls a die.
 *
 * @param sides number of sides on the die
 *
 * @return side the die landed on
 */
int roll(int sides);
{% endhighlight %}

<a name="l10-building"></a>Building the Documentation
=====================================================

You can build the documentation with doxygen. Perhaps the easiest thing is to generate an empty configuration file and then just run doxygen. (This makes doxygen happy.)

{% highlight bash %}
# generate empty config file
doxygen -g

# generate documentation after the above
doxygen
{% endhighlight %}

{% include infobox_head.html type="info" title="Slightly Better-than Defaults" %}

You may wish to change some of Doxyfile's default values. I would encourage searching them out in the file and changing them as opposed to any alternative.

If you don't need latex output, you can set `GENERATE_LATEX` to `NO`.

You may wish to set `OUTPUT_DIRECTORY` to some container directory. A perfectly normal value would be `"doc"`.

{% include infobox_tail.html type="info" title="Slightly Better-than Defaults" %}

<a name="l10-Together"></a>Putting it Together
==============================================

You can now put this all together. Remember to put `@file name.cpp` in a doc comment at the top of your file to force doxygen to document that file's contents for now.

{% highlight cpp linenos %}
/**
 * file doctest.cpp
 */

#include <iostream>
using std::cout;
using std::endl;

#include <random>
using std::default_random_engine;
using std::uniform_int_distribution;

#include <chrono>

int roll(int sides);
void rollAndPrint(int sides);

/**
 * Standard main.
 *
 * @return value to give calling shell
 */
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

/**
 * roll a die and print result
 *
 * @param sides number of sides die has
 */
void rollAndPrint(int sides)
{
    // just print it, geez
    cout << "d" << sides << ": " << roll(sides) << endl;
}

/**
 * roll a die
 *
 * @param sides number of sides on die
 *
 * @return side die landed on
 */
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

If you save that as "doctest.cpp" and run doxygen as advised above, you will end up with an html folder. Opening the index will show you the same as my generated version.

[This is a link to that.]({{site.url }}/cpp/l10/doc)

At first that may seem empty, but if you browse files, you'll find that the file has indeed been documented.

Specifically to the student I have as I write this - Doxygen will only really document files with the `@file` marker as we're writing them right now, so you could conceivably document your entire folder at once the way you've been working on it, and not include any files you don't care (or need) to have documented.

<a name="l08-end"></a>Last Word
-------------------------------
At this point, you're ready to do 
[Problem 08: Hangman]({{ site.url }}/cpp/p08)