# -*- python -*-
# $Id: SConscript,v 1.7 2008/11/21 22:30:38 glastrm Exp $
# Authors: James Peachey <peachey@lheamail.gsfc.nasa.gov>
# Version: hoops-01-01-01
Import('baseEnv')
Import('listFiles')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('hoopsLib', depsOnly = 1)
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
