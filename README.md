### Learn Cinder

Personal notes and examples for getting started with [libcinder](https://libcinder.org/).

- [GitBook](https://mottosso.gitbooks.io/cinder/content/)

<br>
<br>
<br>

### Goals

With this project, I aim to..

1. Simplify [existing documentation].
1. Update and store guides and examples scattered across the interwebs.
1. Provide description and examples for classes and functions.
1. Conform coding style with the [CppCoreGuidelines].
1. Provide [permalinks] to pages and parts of pages to simplify sharing.

[permalinks]: https://en.wikipedia.org/wiki/Permalink
[CppCoreGuidelines]: https://github.com/isocpp/CppCoreGuidelines
[existing documentation]: https://libcinder.org/docs/branch/master/

<br>
<br>
<br>

### Motivation

I find that learning a new framework is a daunting task. So I've decided to approach it in a "divide-and-conquer" kind of fashion; where I inspect the most prominent components piece by piece and document what I find and learn in the way that makes the most sense to me.

Having had a few years of experience with the Qt framework, I've learnt that I am unlikely (and unwilling) to learn most things by heart and prefer remembering where to find things instead. Luckily, the Qt documentation resonates well with me and finding what I'm looking for is typically a matter of seconds.

I'd like the same to be true for Cinder, but unfortunately [the current documentation](https://libcinder.org/docs/branch/master/) does lack in a few of those areas.

- No descriptions
- No examples
- No timestamp
- Slow

No examples, as in the functions and classes are mostly undocumented. No description, no motivation for its existence and worst of all nothing to demonstrate how to actually use it.

A timestamp is important, because some, if not most parts seem out of date and most often does not work with the current release.

And, unexpectedly, visiting any page freezes my browser for about 2-3 seconds, and it's important to me that looking up information on a particular piece of code is as seamless as possible.

With this project, I aim to rectify these things for my current and future self.

<br>
<br>
<br>

### Markdown versus Doxygen

The [original documentation][docs] is generated with [Doxygen](http://www.stack.nl/~dimitri/doxygen/); a documentation generator from C++ sources.

With it, human consumable documentation is coupled with source code in an effort to both remove the added step of writing and maintaining a separate set of documentation and to aid in keeping both up-to-date.

[Markdown] on the other hand favours readability and the hand-crafting of text. It does not make a good fit for automated generation.

However, Cinder has a large user base, most of which are hungry to improve and push the boundaries of the framework. Holding them back today is the barrier-to-entry when it comes to understanding and using an automated documentation generator.

I think that if documentation were made more easily editable, we would see more contributions and a more up to date and lively documentation.

[docs]: https://libcinder.org/docs/branch/master/namespacecinder.html

[Markdown]: https://daringfireball.net/projects/markdown/
