# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "/home/nelis/MPLABProjects/pdice-03/out/pdice-03/default.cmf"
  "/home/nelis/MPLABProjects/pdice-03/out/pdice-03/default.hex"
  "/home/nelis/MPLABProjects/pdice-03/out/pdice-03/default.hxl"
  "/home/nelis/MPLABProjects/pdice-03/out/pdice-03/default.mum"
  "/home/nelis/MPLABProjects/pdice-03/out/pdice-03/default.o"
  "/home/nelis/MPLABProjects/pdice-03/out/pdice-03/default.sdb"
  "/home/nelis/MPLABProjects/pdice-03/out/pdice-03/default.sym"
  )
endif()
