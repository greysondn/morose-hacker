---
layout: page
title: C++ Problem 07 - Cipher
permalink: /cpp/p07
---

Va gur jbeqf bs [gur zragbe](http://phrack.org/issues/7/3.html): "Lbh znl fgbc guvf vaqvivqhny,
ohg lbh pna'g fgbc hf nyy... nsgre nyy, jr'er nyy nyvxr."

<a name="p07-cipher"></a>Problem 07:Cipher
==========================================

This problem assumes you understand up to Lesson 8 (Arrays) of the C++ series.

Create a program that will take a lowercase string and output the same string again as lowercase letters encoded using the ROT13 cipher (or any other valid substitution cipher). There are two pieces of data that may help you do this:

First, `string` has a property, `length`. which tells you how many bytes make up the string. You can read it by calling `stringIdentifier.length()` in your code. (If you're in the recommended place in the lessons, we'll cover this strange dot notation later on.)

Second, you can read entire lines of input from the user at once. This is part of `iostream`. It's called, unsurprisingly, getline.

{% highlight cpp linenos %}
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::getline;

#include <string>
using std::string;

int main ()
{
    string name;

    cout << "Please, enter your full name." << endl;
    cout << "> ";
    getline(cin,name);
    cout << "Hello, " << name << "!" << endl;

  return 0;
}
{% endhighlight %}

More can be found on [the page this example was lifted from](http://www.cplusplus.com/reference/string/string/getline/).

<a name="p07-assumptions"></a>Assumptions
-----------------------------------------
You are allowed to assume the following.

* The user will only input a single line, consisting of lowercase letters and spaces, terminated with a standard line feed (or whatever the `enter` key provides on their system).

* The user will only use the characters from a through z in their statement

* The user will not use any punctuation

* The user only needs to input one line when they run the program