/**
 * Tensile
 * PHP bindings to Tensorflow
 *
 * https://github.com/absalomedia/tensile
 * Copyright (c)2017 Lawrence Meckan <http://absalom.biz>
 *
 *
 */

#ifndef PHP_TENSILE_H
#define PHP_TENSILE_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define TENSILE_VERSION "0.0.1-dev"
#define TENSILE_FLAVOR "Tonewood"

#include <php.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#include <Zend/zend_exceptions.h>

#include <sass.h>

zend_class_entry *tensile_ce;
zend_class_entry *tensile_exception_ce;

zend_class_entry *tensile_get_exception_base();

PHP_METHOD(Tensile, __construct);
PHP_METHOD(Tensile, compile);
PHP_METHOD(Tensile, compileFile);
PHP_METHOD(Tensile, getGPU);
PHP_METHOD(Tensile, setGPU);
PHP_METHOD(Tensile, getCuda);
PHP_METHOD(Tensile, setCuda);


#endif
