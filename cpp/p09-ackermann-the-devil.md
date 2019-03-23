---
layout: page
title: C++ Problem 09 - Ackermann, the Devil
permalink: /cpp/p09
---

Laplace had his demon, but Ackermann might just be the devil; this is the first problem where real world time is of more importance than anything else and failure is a valid option.

<a name="p09-ackermann"></a>Problem 09: Ackermann, the Devil
=========================================================

This problem assumes you understand up to Lesson 11 (Recursion) of the C++ series.

Find as many calculation times as you can for different Ackermann numbers, and their values. You have seven days from the start of this task. I will start the timer as soon as I finish giving it to you. There will be followup conversation on this matter, which requires you to have tried this honestly to make any sense at all.

Four things may help you with this.

...

The first is the GNU time program, available under linux as `time`. It's as easy as running something like normal and just putting `time` in front of it; the number you'll want from that is the one labelled `real` in its output.  

...

The second is that you may wish to have a wrapper of some sort so that your input doesn't take time in the execution. You can do that via:

{% highlight bash %}
time printf 'X\nY\n' | ./ackermann
{% endhighlight %}

Replace X with the first input that you'd normally give `ackermann` when it asks you and Y with the second input that you'd normally give `ackermann` when it asks you.

(You can recall a previous command in the linux terminal by pressing up on your keyboard. You can also edit it.)

...

The third is that forceful termination of a foreground process in the linux terminal may be done with `ctrl+c` on a native keyboard. This seems to work spottily in Windows. I don't know but expect there will be some support in OSX as well.

...

The fourth is just a reminder that an Ackermann number is for two inputs, `m` and `n`. If you have a table of values, it should be for two inputs and one output, and a real time.

{% highlight text %}
A(0, 0) =  1, took 0m0.112s
A(0, 1) =  2, took 0m0.138s
A(1, 0) =  2, took 0m0.108s
A(1, 1) =  3, took 0m0.114s
A(2, 2) =  7, took 0m0.145s
A(3, 3) = 61, took 0m0.422s
{% endhighlight %}

Odds are very low your time will match mine, lest you think part of the work was just done for you.

<a name="p09-assumptions"></a>Assumptions
-----------------------------------------
* You are allowed to assume that if the calculation segfaults it's impossible to calculate that Ackermann number.

* You are encouraged to let some of these just run, possibly for multiple days. It is safe to assume that some of these take a very long time to calculate if your machine is even capable of calculating them.

* I can tell you that for all values m from 0 to 3 and all values n from 0 to 3, you can calculate these in practically no time. I can also tell you that ackermann(4, 4) is extremely time expensive and may be the last one you'll have time to do if you build your way up to there. And that's if you don't segfault. And I'm not guaranteeing it's doable before the deadline.

* I can tell you there are faster ways to calculate Ackermann numbers. I don't want to discourage you from exploration, but it's going to be better if you just fight with this within the deadline.

{% include infobox_head.html type="info" title="About the Segfault" %}
I can explain the segfault to you, which I imagine you'd appreciate right about now.

Each recursive call in Ackermann (or anything, really) requires that all the values for the parent call be kept in memory, as well as the address to them. What happens is that eventually this structure - known as the *call stack* - grows beyond the boundaries of memory and simply cannot be held anymore. The program literally cannot hold a call stack of the size necessary to calculate Ackermann at that point.

A very common benchmark for machine call stack depth (if it's something you need) is a variant of Ackermann which prints the maximum call stack depth reached as it's reached.

Segfaults all happen in different ways, but all of them have to do with memory segmentation and a detected violation. (Literally, "segmentation fault".) More comprehensive articles have been written elsewhere, but sometimes they're inexplicable, to the extent that in-joke I sometimes hear goes "the only thing more frustrating than segfaults and null pointer exceptions is the blue shell in Mario Kart". (A reference to [XKCD #290](https://xkcd.com/290/).)
{% include infobox_tail.html %}