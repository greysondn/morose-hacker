---
layout: page
title: C++ 11 - Recursion
permalink: /py/l11
published: false
---

In order to do this lesson, please see the lesson on [recursion]({{site.url }}/cpp/l11).

<a name="l11-recursion"></a>Lesson 11: Recursion
================================================

This is one of those lessons where what I have to say is very short and to the point, but very hard to really wrap your head around.

A *recursive function* is a function that calls itself in order to solve a problem.

That's it.

<a name="l11-fibonacci"></a>Fibonacci
=====================================

The traditional assignment and case for recursion is caculation of the fibonacci numbers. The fibonnaci series (which the numbers are part of) is a series that starts with `1, 1`... and then every number after that is the sum of the two preceeding it.

`1, 1, 2, 3, 5, 8, 12, 20, 32, 52, 84 ...` and this carries on forever. You can find the series [OEIS listing](https://oeis.org/A000045/list) here if you're interested or need it to check against it for some reason.

If I ask you for the 23rd fibonnaci number, how would you calculate it? Take a moment to really think about this question before moving along.

{% highlight cpp linenos %}
/**
 * @file fibLoop.cpp
 */
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/**
 * Calculates a fibonnaci number using loops
 *
 * @param index the index of the fibonnaci number to calculate, starting with 1
 * 
 * @return the fibonacci number at index. If you gave too large an index or a
 *              bad one, odds are good you're getting back a negative number.
 */
int fibLoop(int index)
{
    // can never be a negative 
    int ret = -42;
    
    // we need two numbers
    int first = 1;
    int second = 1;
    
    // check for special cases
    if (index <= 0)
    {
        // just return as is, user's an idiot
    }
    else if ((1 == index) || (2 == index))
    {
        // Those are both 1
        ret = 1;
    }
    else
    {
        // actually calculate for index.
        // next value
        int next = -1;
        
        for (int current=2; current < index; current++)
        {
            next = first + second;
            first = second;
            second = next;
        }
        
        // current is tracking where second is, so that will be our return
        ret = second;
    }
    
    // return
    return ret;
}

/**
 * main program entry point
 */
int main()
{
    int userIndex = -1;
    
    cout << endl <<
    "Hi! This calculates a fibonacci number using loops. Please" << endl <<
    "input the index you'd like to have the number for! The index" << endl <<
    "must be greater than or equal to 1, and due to how this is" << endl <<
    "programmed I can only do to the 23rd index accurately." << endl << endl <<
    "> ";
    
    cin >> userIndex;
    
    cout << "The fibonnacci number for index " << userIndex << " is:" << endl <<
         fibLoop(userIndex) << endl;
}
{% endhighlight %}

I imagine your solution would have come out something like this. And this isn't wrong! It solves the problem, after all. It's just that the fibonacci series is elegantly doable via recursion.

<a name="l10-syntax"></a>Fibonacci, Recursively
===============================================

So here's the recursive version of that same program.

{% highlight cpp linenos %}
/**
 * @file fibRecurse.cpp
 */
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/**
 * Calculates a fibonnaci number using recursion
 *
 * @param index the index of the fibonnaci number to calculate, starting with 1
 * 
 * @return the fibonacci number at index. If you gave too large an index or a
 *              bad one, odds are good you're getting back a negative number.
 */
int fibRecurse(int index)
{
    // bad default deliberately
    int ret = -42;
    
    if (index <= 0)
    {
        // still pass, user's still an idiot
    }
    else if ((index == 1) || (index == 2))
    {
        // still handle first two the same way
        ret = 1;
    }
    else
    {
        // here's where it gets interesting
        // a fibonacci number is just the sum of the preceeding two fibonacci
        // numbers... right? So then we can just add those together.
        ret = (fibRecurse(index -1) + fibRecurse(index -2));
    }
    
    // end
    return ret;
}

/**
 * main program entry point
 */
int main()
{
    int userIndex = -1;
    
    cout << endl <<
    "Hi! This calculates a fibonacci number using recursion. Please" << endl <<
    "input the index you'd like to have the number for! The index" << endl <<
    "must be greater than or equal to 1, and due to how this is" << endl <<
    "programmed I can only do to the 23rd index accurately." << endl << endl <<
    "> ";
    
    cin >> userIndex;
    
    cout << "The fibonnacci number for index " << userIndex << " is:" << endl <<
         fibRecurse(userIndex) << endl;
}
{% endhighlight %}

The magic - and headache - comes at line 36. It can be hard for people to see where this ends and why it doesn't just keep asking for the next one down again.

The magic that prevents that is that each time we call it, the indexes we ask for get smaller and smaller until eventually we're asking for indexes 1 and 2. And it just so happens we wrote a special case for indexes 1 and 2 (line 26) which doesn't call the function itself again and instead does determine at least *something* to return. This is the secret of how this doesn't go forever.

Just to give an illustrative case, let's see what happens when we call for the 5th fibonacci number - large enough to be non-direct, small enough to not require a novel.

The tracing of ***just the function calls*** for that code will come out something like this.

{% highlight text %}
fibRecurse(5)
├─ fibRecurse(4)
│  ├─ fibRecurse(3)
│  │  ├─ fibRecurse(2)
│  │  └─ fibRecurse(1)
│  └─ fibRecurse(2)
└─ fibRecurse(3)
   ├─ fibRecurse(2)
   └─ fibRecurse(1)
{% endhighlight %}

&nbsp;

{% include photoplasty.html img="/res/cpp/l11/graph-fibonacci.png" caption="You can also visualize this call graph as a tree structure." %}

&nbsp;

This is one of those things to really slow down and take in. Make sure you understand what is being said.

<a name="l11-loop-or-recurse"></a>Loop or Recurse?
==================================================

The two versions of fibonacci presented here were no mistake - they were presented to help you notice that (some) recursion can be re-expressed as a loop. So the natural question should arise as to when to use a loop and when to recurse.

As a rule, you should prefer loops at all times, except:

* when self-similarity exists

  * when smaller portions of the problem can be expressed as the same problem (Fibonnaci, many sorting algorithms, many search algorithms)

  * when dealing with a self-similar structure or a self-similar approach to a structure (many search algorithms on sequential containers, tree-like structures)

* When the problem cannot be expressed as a loop

  * Wait, what? That's the next section.

People who tell you to rewrite loops as recursions just to do it are unaware that their code is unreadable and they are making messes for other people who come along. Just because something is *shorter* doesn't mean it's better.



<a name="l11-trivial-nontrivial"></a>Trivial and Non-Trivial Recursion
======================================================================

The main type of recursion that people always get taught is known as *trivial recursion*. Trivial recursion lends itself to being re-expressed as a loop, so if you can do something like the above fibonacci, it's good odds it's trivial.

Non-trivial recursion, however, is... deeply complex and rare. Odds are good that you'll never encounter it, but it irritated me that I wasn't taught that it even exists in school, so here it is in the form of the Ackermann Function.


{% highlight cpp linenos %}
/**
 * @file ackermann.cpp
 */
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/**
 * Ackermann's function.
 *
 * @param m M see ackermann's function elsewhere
 * @param n N see ackermann's function elsewhere
 *
 * @return A(m, n)
 */
unsigned long ackermann(unsigned long m, unsigned long n)
{
    // eventual return
    unsigned long ret = -1;
    
    // ackermann's function has only three clauses
    if (0 == m)
    {
        // m = 0 is our limit clause, where this stops recursing
        ret = n + 1;
    }
    else if (0 == n)
    {
        // n = 0 is just a special recursive case.
        ret = ackermann((m - 1), 1);
    }
    else
    {
        // in every other case is just recursion
        ret = ackermann((m -1), ackermann(m, (n - 1)));
    }
    
    // end
    return ret;
}

int main()
{
    unsigned long m = 0;
    unsigned long n = 0;
    
    cout << "This calculates ackermann numbers! Be aware your" << endl <<
            "machine isn't going to be useful for much while this is" << endl <<
            "running! THIS CAN TAKE LONGER THAN YOU REALIZE!" << endl <<
            endl <<
            "Ackermann's function has two inputs. This program" << endl <<
            "calls them by their traditional names." << endl <<
            endl <<
            "Please insert an integer value 0 or greater for m" << endl <<
            "> ";
            
    cin >> m;
            
    cout << endl <<
            "Please insert an integer value 0 or greater for n" << endl <<
            "> ";
    
    cin >> n;
    
    cout << "Calculating, will not give updates as it goes." << endl;
    
    unsigned long answer = ackermann(m, n);
    
    cout << endl <<
            "Ackermann number A(" << m << ", " << n << ") is:" << endl <<
            answer << endl << endl;
            
     return 0;
}
{% endhighlight %}

The main reason this can't be rewritten into a loop nicely and neatly is at line 36.

{% highlight cpp %}
ret = ackermann((m -1), ackermann(m, (n - 1)))
{% endhighlight %}

That call would require a structure that simply doesn't exist; your loop would have to be able to create a loop like itself capable of creating itself to rewrite it. The problem is self-similar, but cannot be expressed as a loop.

<a name="l11-last-word"></a>The Last Word
=========================================

You can just directly download the files from this lesson if you'd like to play with them some.

{% highlight bash %}
# loop version of fibonacci
wget {{ site.url }}/cpp/l11/fibLoop.cpp

# recursive version of fibonacci
wget {{ site.url }}/cpp/l11/fibRecurse.cpp

# ackermann's function
wget {{ site.url }}/cpp/l11/ackermann.cpp
{% endhighlight %}

You are now ready to do [Problem 09: Ackermann, the Devil]({{ site.url }}/cpp/p09).

{% include infobox_head.html type="hacker" title="Chainsaws and Scissors, Branches and Twigs" %}

You may often hear me say "don't take a chainsaw to a twig". This is a reference to something that was drilled into my head early: *Don't take chainsaws to twigs. Don't take scissors to tree branches.*

What it means is to use the right tool for the job. Don't use something just because it's fancy or makes you look smarter. Don't use something that's insufficient, either.

Remember that "right tool" in programming means many things - is it readable? Is it sane? Is it acceptably efficient? (This applies to our toolkits too. Sometimes, like it or not, the correct answer to get the work done is to suck it up and use things that you frankly hate and don't want to support.)

Most the losses for readability in code are for the sake of program efficiency. This course assumes that you aren't on limited platforms (Arduino, for example) and don't have to worry about RAM or CPU time. There are times that the very things you've been told not to do would make sense. They are not a part of this course, and they are not in what I would call "normal" circumstances.

In other words, this course assumes that you are in a general set of circumstances where general rules can be given and serve you well. I try hard to distinguish "highly sane, general rules" from "hard and fast rules" in this writing, and I hope I succeed well at that.

Half the battle in this entire process is knowing your problem itself well. If you don't know if you have a "branch" or a "twig" in front of you, it's going to be very, very hard to decide on the proper tool. And relatively unusual platforms (like Arduino) can best be likened to a "sapling", where "twig" and "branch" often start to lose meaning as terms to think in.

Hackers don't just start by understanding the problems in front of them and how new they really might be - they start by knowing the tools at their disposal extremely well, inside and out, so that they can decide on which one to use as fast as they know the problem at hand.

{% include infobox_tail.html %}

&nbsp;

{% include infobox_head.html type="hacker" title="Hackers are Not Crackers!" %}

As this is the first time this topic has come up, it may be a good time to read on the differences between hackers and crackers, as well as some of the general hacker mindset notes. Also worth noting is how different people with some degree of experience think about the proper ways to learn code and culture from the ground up. (Actually, the guy who wrote catb is a bit of a legend in the culture, and I'm just... morose.)

[http://www.catb.org/~esr/faqs/hacker-howto.html](http://www.catb.org/~esr/faqs/hacker-howto.html)

{% include quote_head.html source="catb's How to be a Hacker" %}
There is another group of people who loudly call themselves hackers, but aren't. These are people (mainly adolescent males) who get a kick out of breaking into computers and phreaking the phone system. Real hackers call these people ‘crackers’ and want nothing to do with them. Real hackers mostly think crackers are lazy, irresponsible, and not very bright, and object that being able to break security doesn't make you a hacker any more than being able to hotwire cars makes you an automotive engineer. Unfortunately, many journalists and writers have been fooled into using the word ‘hacker’ to describe crackers; this irritates real hackers no end.
{% include quote_tail.html %}

As a rule, if it's on the news, they've mistakenly said "hacker" when they should say "cracker". As a rule, if someone says they're a "hacker", they either carry a lot of weight in the larger community and should be easy to look up (and determine the ethics of and whether they've misused that term)... or they aren't worth your time and are talking nonsense.

I would generally advise you to *never* call yourself a hacker, but to let other people make that determination by talking to you. There's this (unfortunate) tendency for all sorts of bad people to use the term (crackers, scriptkiddies, etc) and so it's better to let people just decide on it than to say it yourself.

{% include infobox_tail.html %}