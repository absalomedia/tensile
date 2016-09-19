# Tensile
Tensorflow as a PHP/Zend extension (experimental), using PHP5/PHP7. Still not in fully working state.

[![Build Status](https://travis-ci.org/absalomedia/tensile.svg?branch=master)](https://travis-ci.org/absalomedia/tensile)

# Concept

The concept of this extension is to expose Tensorflow into PHP directly so you can run rules, training & the Tensorflow engine natively via PHP code. The coding structure replicates my work having SASS compile on the fly as a PHP extension.

# Steps
- [x] Build a base test image to test this build process (Travis/Docker)
- [x] Build a shared library from Tensorflow that can then be wrapped into a PHP / Zend extension.
- [x] Refactor header classes from SASSPHP to deal with Tensorflow functions, variables & classes. 
- [ ] Refactor C/C++ code to allow PHP classes to talk directly / manage Tensorflow once it's wrapped in shared library
- [ ] Build tests
- [ ] Gnomes
- [ ] Profit
