---
layout: page
title: C++ 06: Random Numbers
permalink: /cpp/l06
---

This newfangled technology makes no sense to me.

<a name="l06-random-numbers"></a>Lesson 06: Random Numbers
=======

This isn't something I understand well, but it is the compliant way of doing it in C++ 2011.

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
    // use system clock to generate seed
    // I don't understand this, but this is apparently the compliant way
    // to get unix time stamp now. Christ.
    unsigned rngSeed = std::chrono::system_clock::now().time_since_epoch().count();
    
    // seed new style RNG just by creating a generator
    default_random_engine generator(rngSeed);

    // then we need to declare the distribution we'll be using
    // note it's a constructor with two arguments here
    uniform_int_distribution<int> distribution(1, 100);

    // let's roll it 20 times
    for (int i = 0; i < 20; i++)
    {
        // handing distribution the generator gives us a number
        // with the type and in the range we told distribution to have
        cout << distribution(generator) << endl;
    }

    return 0;
}
{% endhighlight %}

<a name="l06-todo"></a>Document TODO
------------------------------------
* Research this and understand it well enough to teach more than the basics.
* Actually write a proper lesson here instead of just dumping code.