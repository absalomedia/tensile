/**
 * Tensile
 * PHP bindings to Tensorflow
 *
 * https://github.com/absalomedia/tensile
 * Copyright (c) 2017 Lawrence Meckan <http://absalom.biz>
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
#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include <../includes/tensorflow/c/c_api.h>

zend_class_entry *tensile_ce;
zend_class_entry *tensile_exception_ce;

zend_class_entry *tensile_get_exception_base();

#define TENSILE_NS "Tensile"

static PHP_MINFO_FUNCTION(tensile);
static PHP_MINIT_FUNCTION(tensile);
static PHP_FUNCTION(debug);

extern zend_module_entry tensile_module_entry;

#endif
