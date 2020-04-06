#!/usr/bin/env python

import os
import re
import shutil

from waflib.extras import autowaf

APPNAME = 'verb-lv2'   # Package name for waf dist
VERSION = '0.0.1'      # Package version for waf dist
top     = '.'          # Source directory
out     = 'build'      # Build directory

def options(opt):
  opt.load('compiler_cxx')
  opt.load('lv2')

def configure(conf):
  conf.load('compiler_cxx', cache=True)
  conf.load('lv2', cache=True)
  conf.load('autowaf', cache=True)
  autowaf.set_c_lang(conf, 'c99')
  conf.check_pkg('lv2 >= 1.2.0', uselib_store='LV2')
  conf.run_env.append_unique('LV2_PATH', [conf.build_path('lv2')])
  autowaf.display_summary(conf, {'LV2 bundle directory': conf.env.LV2DIR})

def build(bld):
  bundle = 'verb.lv2'

  for i in bld.path.ant_glob('verb.lv2/[A-Za-z]*.ttl'):
    bld(features     = 'subst',
        is_copy      = True,
        source       = i,
        target       = 'lv2/verb.lv2/%s' % i.name,
        install_path = '${LV2DIR}/verb.lv2')

  # Build manifest by substitution
  bld(features     = 'subst',
      source       = 'verb.lv2/manifest.ttl.in',
      target       = 'lv2/verb.lv2/manifest.ttl',
      LIB_EXT      = bld.env.LV2_LIB_EXT,
      install_path = '${LV2DIR}/verb.lv2')

  plugins = [
    'averb'
  ]

  for p in plugins:
    # Build plugin library
    obj = bld(features     = 'cxx cxxshlib lv2lib',
              source       = ['src/%s.cpp' % p],
              includes     = ['.', './src'],
              name         = p,
              target       = os.path.join('lv2', bundle, p),
              install_path = '${LV2DIR}/' + bundle,
              uselib       = ['LV2'],
              defines      = ['PLUGIN_CLASS=%s' % p,
                              'URI_PREFIX="https://github.com/afofo/verb#"',
                              'PLUGIN_URI_SUFFIX="%s"' % p,
                              'PLUGIN_HEADER="src/%s.h"' % p])

    # Install data file
    bld.install_files('${LV2DIR}/' + bundle, os.path.join(bundle, p + '.ttl'))
