#$Id$

Import('baseEnv')
Import('listFiles')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

hoopsLib = libEnv.StaticLibrary('hoops', listFiles(['src/*.cxx']))

progEnv.Tool('hoopsLib')
test_sourceBin = progEnv.Program('test_source', 'src/test/hoops_lim_test.cxx')
test_hoops = progEnv.Program('test_hoops', 'src/test/hoops_lim_test.cxx')
progEnv.Tool('registerObjects', package = 'hoops', libraries = [hoopsLib], testApps = [test_sourceBin, test_hoops], includes = listFiles(['hoops/*.h']),
             pfiles = listFiles(['pfiles/*.par']))
