---
layout: page
title: C++ 07 - Loops
permalink: /cpp/l07
---

Does it ever feel like groundhog day - you just keep repeating yourself? Let's help the computer get that same feeling, shall we?

<a name="l07-loops"></a>Lesson 07: Loops
=================

There are three basic loop structures in C++. They are `while`, `do...while`, and `for`.

It's best to wrap your head around them in that order.

<a name="l07-while"></a>While
-----------------------------

A *while* loop takes the form

{% highlight cpp linenos %}
while(condition)
{
    // code to keep repeating
    // until condition is false
}
{% endhighlight %}

{% include photoplasty.html img="/res/cpp/l07/uml-while.png" caption="UML flowchart of a while loop" %}

When running, it will do the following:

* Check to make sure `true == condition`
  * If `true`...
    * Run the code inside the loop
    * Return to start
  * If `false`...
    * don't run the loop, just move forwards in code

It's important to note that *this means that you cannot necessarily guarantee that a while loop will run*. That is, it may run zero or more times.

<a name="l07-dowhile"></a>Do...While
-------------------------------------
A *do...while* loop takes the form

{% highlight cpp linenos %}
do
{
    // code to keep repeating
    // until condition is false
} while(condition);
{% endhighlight %}

{% include photoplasty.html img="/res/cpp/l07/uml-dowhile.png" caption="UML flowchart of a do...while loop" %}

When running it will do the following:

* Run the code inside the loop
* Check to make sure `true==condition`
  * if `true`...
    * Return to start
  * if `false`...
    * Move forwards in code

You may be looking at this thinking I've only swapped things around. That's *mostly* true. The chief distinction between *while* and *do...while* is that *do...while* is guaranteed to run *at least once*. That is, it may run one or more times.

<a name="l07-for"></a>For
-------------------------
A *for* loop takes the form

{% highlight cpp linenos %}
for (initializer; condition; step)
{
    // code to keep repeating
    // until condition is false
}
{% endhighlight %}

{% include photoplasty.html img="/res/cpp/l07/uml-for.png" caption="UML flowchart of a for loop" %}

When running, it does the following.

* perform *initializer*
  * check `true==condition`
    * if `true`...
      * run the code inside the loop
      * perform *step*
      * return to check step
    * if `false`
      * don't run the code, just move forwards in the program

It's important to notice that *for loops, like while loops, may never run the code inside of them*. However, unlike *while* loops, *for* loops will always run the *initializer* step.

<a name="l07-typical"></a>Typical Uses
--------------------------------------
The creator of C++ has a quote he tries to drill into people's heads. It's this:

{% include quote_head.html source="Bjarne Strousop" %}
Two or more, use a for!
{% include quote_tail.html %}

What he means is this: Due to the extreme optimization of *for* loops in the C++ compiler (and the clearer syntax for such tasks), if you - without a doubt - can give a countable number of iterations of your loop and it is `>=` 2... you need to be using a *for* loop.

With this being said, obviously you'd rather hear when to use each one.

The most common use for a while loop is a main program loop.

{% comment %}
Tested:
g++ (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0 (via WSL)
{% endcomment %}
{% highlight cpp linenos %}
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

int main()
{
    string userInput = "";
    bool   keepRunning = true;

    while (keepRunning)
    {
        // we could put basically any valid program body here
        // as long as we need it to loop
        cout << endl;
        cout << "Input 'end' to end this program" << endl;
        cout << "> ";
    
        cin >> userInput;

        // the point is, eventually we'd be ready to stop.
        if ("end" == userInput)
        {
            keepRunning = false;
        }
    }
    
    return 0;
}
{% endhighlight %}

The most common use for a *do...while* loop is to validate user input without setting a dummy value first. (Frankly... most people will just use a *while* loop with a dummy value, because of course we do.)

{% comment %}
Tested:
g++ (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0 (via WSL)
{% endcomment %}
{% highlight cpp linenos %}
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

int main()
{
    // notice we don't give it a default value.
    int userInput;

    // we won't do anything with it until we ask user
    // what to put into it.
    do
    {
        cout << endl;
        cout << "Please input a number between 1 and 100." << endl;
        cout << "> ";
        cin >> userInput;
    } while ((userInput < 1) || (userInput > 100));

    // we now know user input is between 1 and 100
    // for sure.

    // again, most people use a while loop.
    // you'll find out if you want to do an error
    // message then a while loop can make more sense

    return 0;
}
{% endhighlight %}

I really don't think I've ever seen someone use a `do...while` outside a classroom in a decade of writing code.

A `for` loop shows up when we know (or can obtain) a number of iterations for our code, typically.

{% comment %}
Tested:
g++ (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0 (via WSL)
{% endcomment %}
{% highlight cpp linenos %}
#include <iostream>
using std::cout;
using std::endl;

int main()
{
    cout << "I'm going to count from 1 to 10!" << endl;

    for (int i = 1; i <= 10; i++)
    {
        cout << i << endl;
    }

    return 0;
}
{% endhighlight %}

{% include infobox_head.html type="info" title="Increment and Decrement" %}

This is probably your first time seeing the increment operator - the `++` after `i` in the *step* portion of that *for* loop.

All it does is make the value before it one larger.

You could, equivalently, write `i = i + 1;` instead in the above example.

There is also a decrement function. It does about what you'd expect.

`i--` is the same as `i = i - 1;`

The most common place to see both of these operators is in a *for* loop's *step*.

{% include infobox_tail.html %}
<br />
{% include infobox_head.html type="caution" title="Don't Abuse For Loops, Signed Everyone Competent" %}

Technically, you could just rewrite a *while* as a *for* loop.

{% highlight cpp linenos %}
    for (; condition;)
    {
        // while body
    }
{% endhighlight %}

You could probably get by with some arbitrary code instead of what you're supposed to do.

{% highlight cpp linenos %}
int i = 1;
int j = 1;
for (int k = 20; k > i;i = i + j)
{
    // no body necessary
    // (productive examples exist)
}
{% endhighlight %}

Allow me to summarize what to do with these two pieces of information:

***JUST DON'T.***

Writing code like this is unclear and messy. Nobody with their head screwed on straight likes it. It is not how these things are meant to be used.

To put it another way... misusing *for* loops in C++ is like speaking in the backwards construction Yoda uses in English: *technically and syntactically correct, but irritating and hard to interpret for normal, sane human beings*.

***"Like Yoda speaking English misusing a for loop is. Do it you must not."***
{% include infobox_tail.html %}

<a name="l07-end"></a>Last Word
-------------------------------
You are now ready to do Problem #06: High or Low.

<a name="l07-todo"></a>Document TODO
------------------------------------
* Write and link problem #06.