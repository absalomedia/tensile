# Tensile

The `tensile` extension for PHP gives you an object-oriented system for utilising Google's Tensorflow Machine Learning (http://tensorflow.org) from within your PHP applications. Still not in fully working state & experimental builds.


![Tensorflow 1.8.0](https://img.shields.io/badge/tensorflow-1.8.0-blue.svg) [![Build Status](https://travis-ci.org/absalomedia/tensile.svg?branch=master)](https://travis-ci.org/absalomedia/tensile) [![Patreon](https://img.shields.io/badge/patreon-donate-green.svg)](https://www.patreon.com/bePatron?u=14641360)

# Concept

The concept of this extension is to expose Tensorflow into PHP directly so you can run rules, training & the Tensorflow engine natively via PHP code. The coding structure replicates my work having SASS compile on the fly as a PHP extension.

# Steps
- [x] Build a base test image to test this build process (Travis/Docker)
- [x] Build a shared library from Tensorflow that can then be wrapped into a PHP / Zend extension.
- [ ] Refactor header classes from SASSPHP to deal with Tensorflow functions, variables & classes. 
- [ ] Refactor C/C++ code to allow PHP classes to talk directly / manage Tensorflow once it's wrapped in shared library
- [ ] Build tests
- [ ] Gnomes
- [ ] Profit
