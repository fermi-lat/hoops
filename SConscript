# -*- python -*-
# $Id: SConscript,v 1.13 2010/02/22 20:49:10 jrb Exp $
# Authors: James Peachey <peachey@lheamail.gsfc.nasa.gov>
# Version: hoops-01-01-06
Import('baseEnv')
Import('listFiles')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

hoopsLib = libEnv.StaticLibrary('hoops', listFiles(['src/*.cxx']))

progEnv.Tool('hoopsLib')
test_sourceBin = progEnv.Program('test_source', 'src/test/hoops_lim_test.cxx')
test_hoops = progEnv.Program('test_hoops', 'src/test/hoops_lim_test.cxx')

#progEnv.Tool('registerObjects', package = 'hoops', libraries = [hoopsLib], testApps = [test_sourceBin, test_hoops], includes = listFiles(['hoops/*.h']),
#             pfiles = listFiles(['pfiles/*.par']), data = listFiles(['data/*'], recursive = True))

progEnv.Tool('registerTargets', package = 'hoops',
             staticLibraryCxts = [[hoopsLib, libEnv]],
             testAppCxts = [[test_sourceBin, progEnv], [test_hoops, progEnv]],
             includes = listFiles(['hoops/*.h']),
             pfiles = listFiles(['pfiles/*.par']),
             data = listFiles(['data/*'], recursive = True))
