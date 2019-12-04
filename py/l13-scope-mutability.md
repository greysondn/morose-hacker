---
layout: page
title: Python 13 - Scope, Reference, and Mutability
permalink: /py/l13
---

Sometimes, all you need is a constant reference to make life not suck quite so hard. Or perhaps I meant a static variable. Oh well.

{% include infobox_head.html type="caution" title="Writing in Progress" %}
This lesson was rapidly adapted via copy+paste and patchwork from the related C++ lesson. As a side effect, some things may have been missed or may still refer to their C++ counterparts.
{% include infobox_tail.html %}

<a name="l13-srm"></a>Lesson 13: Scope, Reference, and Mutability
======================================================
Up to this point, we've largely breezed over some very basic concepts (and skipped some key ones that could have made your life easier). They were scope, reference, and mutability.

Scope covers the notion of where something is valid. The scope of a variable, for example, is the area where that variable is valid.

Reference covers the ability to pass a variable's scope about, more or less, so that the same variable is in scope elsewhere.

And mutability covers the ability to change whether or not something can change at all - and how it changes.

<a name="l13-scope"></a>Scope
=============================

*Typically, an identifer's scope is within the level its declared and any nested blocks of code under that level.* Special keywords exist to modify beyond this in some fashion or another.

Using global variables is bad because the scope isn't clear in a way that allows you to decide who changed them when. Global variables can be accessed from *anywhere* and changed from *anywhere*. This makes following their changes hard. And that assumes they don't generate a name conflict on something like `from module import *`, mind you, which is another issue in itself.

Python works a little strangely here due to a property not present in most languages - namely that a Python script and a python module are often the same file. This wouldn't be so bad, but what we mean by a global variable typically applies to a script and not a module; modules are allowed to have module level vars (the module itself is the scope). Because you can execute a module as a script at any time, this implies the two are not semantically distinct.

As a rule, the solution to this is to not use any module-level variables. However, that's not always pragmatic, for several reasons. Constants (which we're going to cover later in this lesson), for example, are typically defined at the module level. So then as a general rule it becomes "avoid module level variables." (We will cover wrapper classes and other mechanisms such as variable mangling which help mitigate the rest of this in the near future.)

Beyond this it's not quite so bad. Consider the following.

{% highlight python linenos %}
def foo(bar):
    bar = bar + 5
    print(f"Inside value: {bar}")

def main():
    bar = 5
    foo(bar)
    print(f"Outside value: {bar}")

if "__main__" == __name__:
    main()
{% endhighlight %}

The output of that should make perfect sense.

{% highlight text %}
$> python first.py
Inside value: 10
Outside value: 5
{% endhighlight %}

{% include infobox_head.html type="behold" title="Closures" %}
What is in this infobox is something that would be criminal not to mention, but that I would prefer my students not get caught up in for several reasons while studying with me. In short, ***this is something I think you need to know, but please don't do this in work you submit to me.***

One of the weird implied quirks of this scoping is that any identifier can work anywhere for scoping, actually, which clues you in that maybe you can define a function inside another function.

As it turns out, Python does permit this.

{% highlight python linenos %}
def foo(baz):
    # "wait, what the-?"
    def bar(baz):
        baz = baz + 5
        print(f"Bar: {baz}")
    
    # "... you're kidding, right?"
    baz = baz + 5
    bar(baz)
    print(f"foo: {baz}")

def main():
    baz = 5
    foo(baz)
    print(f"main: {baz}")

if "__main__" == __name__:
    main()
{% endhighlight %}

It's not a joke.

{% highlight text %}
$> python second.py
Bar: 15
foo: 10
main: 5
{% endhighlight %}

Function is also a type in python.

{% highlight text %}
$> python
>>> def foo():
...     pass
...
>>> type(foo)
<class 'function'>
{% endhighlight %}

Which means we can return it.

{% highlight python linenos %}
def foo(baz):
    def bar(baz):
        baz = baz + 5
        print(f"Bar: {baz}")
    
    baz = baz + 5
    print(f"foo: {baz}")

    return(bar)

def main():
    baz = 5
    zap = foo(baz)
    zap(baz)
    print(f"main: {baz}")

if "__main__" == __name__:
    main()
{% endhighlight %}

{% highlight text %}
foo: 10
Bar: 10
main: 5
{% endhighlight %}

(Yes, that's correct, because it was called from main instead of from inside foo.)

This last bit is the most interesting. Because scope is valid within the confines of any internal scopes, we can use this as a ***closure*** over the returned function. (Specifically, a closure is a function stored with its environment, which is what this gives us, as you'll see momentarily.)

{% highlight python linenos %}
def foo(name, x):
    def bar(y):
        out = x + y
        print(f"{name} : {out}")

    return bar

def main():
    # we'll need some value
    aValue = 0
    print(f"Main: {aValue}")

    # let's define two separate functions this way
    baz = foo("baz", 5)
    zap = foo("zap", 10)

    # what do you think happens?
    baz(aValue)
    zap(aValue)

    # how about now?
    foo("???", 15)(aValue)
    foo("???", 20)(aValue)

if "__main__" == __name__:
     main()
{% endhighlight %}

{% highlight text %}
$> python fourth.py
Main: 0
baz : 5
zap : 10
??? : 15
??? : 20
{% endhighlight %}

For most people, the first time they see this, they struggle to process what has just happened. The last two instances are especially noteworthy - *they're anonymous*. Most people I've talked to struggle to wrap their heads around this notion.

There are better uses, but this is an illustrative case of closures. It is a language feature, and provides one more thing you could, conceivably do. Please don't in these lessons. It's best applied in a purely functional programming paradigm, which we won't be needing.

In the list of things that won't be taught in these lessons are the [lambda calculus][wp-lambda-calculus] (which is the most natural use for closures) and the `lambda` keyword (which creates a closure on the spot).
{% include infobox_tail.html %}

&nbsp;

{% include infobox_head.html type="info" title="Lambda and the Church-Turing Thesis" %}
One of the most important questions to the history of computing is "What can we compute?" This question was answered by two men almost simultaneously, in two different ways.

One of those men was Alan Turing. His way of illustrating it was via Turing Machines. He's the one we generally credit with the matter... *However*...

The other man to illustrate this was Alonzo Church, using the lambda calculus. It is known that the lambda calculus is able to compute anything computable. (We call this feature *Turing completeness*.)

These two men and their work combine into what is known as the *Church–Turing thesis*. Stated simply, the thesis says a function is computable if - and only if - it is capable of being solved with a Turing Machine. Quite literally, ***this is the thesis that defines and proves what a computer can and can not do***.

And that is why it's criminal to not include a brief on closures in any language that has them - because it finishes out functional programming and provides the functional programming side of the Church-Turing thesis. {% include infobox_tail.html %}

<a name="l13-reference"></a>Reference
=====================================
*Any handle on a piece of data constitutes a reference to that data.* At first this seems straightforward, but consider the following:

{% highlight python linenos %}
def tryToChange(aValue):
    aValue = aValue + 5
    print(f"During: {aValue}")

def main():
    aValue = 5
    print(f"Before: {aValue}")
    tryToChange(aValue)
    print(f"After: {aValue}")

if __name__ == "__main__":
    main()
{% endhighlight %}

Are you sure you know what this will do? Most importantly, is the "during" value equal to the "after" value?

{% highlight text %}
$> python fifth.py
Before: 5
During: 10
After: 5
{% endhighlight %}

Of course, this is somewhat good! The function's scope is well defined (and observed) and side-effects are minimized! Python even allows two returns, so this isn't the end of the world like it can be in some other languages.

The way that this variable has been passed in is called *pass-by-value*. The *value of a variable* - not a *handle on the variable itself* - has been passed. What you need is a *handle* - a *reference* to the underlying data. Take a look at this subtly different version.

{% highlight python linenos %}
def tryToChange(aValue):
    aValue.append(4)
    print(f"During: {aValue}")

def main():
    aValue = [1, 2, 3]
    print(f"Before: {aValue}")
    tryToChange(aValue)
    print(f"After: {aValue}")

if __name__ == "__main__":
    main()
{% endhighlight %}

The subtle difference is that now we're using - and modifying - a list. *Are you sure you know what this is going to do here?* I mean, surely a change as simple as that isn't that big of a deal... right?

{% highlight text %}
Before: [1, 2, 3]
During: [1, 2, 3, 4]
After: [1, 2, 3, 4]
{% endhighlight %}

What th- why? Why did we suddenly get a handle to the underlying data instead of the value we passed in? And more importantly, how do we predict which one Python will pick when we give it an input?

And the answer is "mutability".

{% include infobox_head.html type="hacker" title="About that..." %}
I'm lying through my teeth to make this easier to understand, and most Python programmers - even at an expert level - would never realize it.

Python can't pass by value *at all*. It can only pass by reference.

Idiomatically, a variable is really just a name pointing to a value. And I don't mean that in the "easier to understand way" - Python takes this quite literally, apparently.

If that value is immutable, then attempts to reassign that variable simply change the value it points to. Functionally speaking, a variable is a *pointer*, not an actual *value*, and *dereference* happens in the process of resolution.

Of course, we will still say "primitives are passed by value, compounds are passed by reference". Because it's easier to wrap our heads around and understand.
{% include infobox_tail.html %}

Incidentally, if there are side effects as a consequence like this, this requires you to document *that some of the variables will be changed as a side effect of the function*.

Most importantly, *passing a variable by reference allows you to change the scope of that variable by enabling you to pass it from one function or method to another, generally.*

<a name="l13-mutability"></a>Mutability
=======================================
Mutability, at its core, covers how much a variable may change and when it may do so.

&nbsp;

We start with two simple terms.

If something is *mutable it's able to be changed.

If something is *immutable*, it's unable to be changed.

You can imagine "mutable means able to mutate" if you'd prefer. If it's not accurate it's clearly a related term anyway. ("Im-" means "not".)

&nbsp;

There are a few factors that you need to know involving this, as it's something that python is a little strange about. In no particular best order.

&nbsp;

Naming conventions for variables are related to other languages. Recall that you were told that it would be very bad to name a variable in `ALL_CAPS`. The reason given is that this means something else. What it means is that the variable is meant to be treated like a *constant*.

In other languages, you can declare something constant. It's a keyword. If it's a constant than any attempt to assign a new value to it is an error. In other words, declaring something constant means it's now immutable.

Python does not observe this behavior. There are no constants.

Instead, constants are observed by programming conventions. By naming something in all capital letters, you declare it to be a constant value, and that means that nobody should assign to it. (This includes yourself!)

Can they? Absolutely. Will they? ... Most programmers will obey conventions, so it turns out in Python projects with many collaborators this works extremely well as a standard. 

So if you name what would otherwise be a variable in all capitals, you never change it's value, and you're telling other people to never change it, either.

&nbsp;

The second is the mutability of certain values.

To put it simply, primitive literals cannot be changed. Ever.

An object composed of primitives (known as a *compound object*) can be changed, however. Just fine.

The reason the example at the end of the previous section works, or rather the discriminating factor, is that *lists are compound* but *ints are primitive*.

The types that cannot be changed "like that" in Python - that functionally are pass-by value - are short and easy to memorize. They are: Boolean, Integer, Float, and String. It's a very easy list to memorize.

Lists, on the other hand, can be modified like that all day. As can all sequence types - tuple, for example.

<a name="13-end"></a>Last Word
------------------------------
Guh, I'm tired all over again, commit and forget for now.

[wp-lambda-calculus]: https://en.wikipedia.org/wiki/Lambda_calculus