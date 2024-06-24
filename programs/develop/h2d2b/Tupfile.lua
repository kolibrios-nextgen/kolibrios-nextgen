if tup.getconfig("NO_FASM") ~= "" then return end
HELPERDIR = (tup.getconfig("HELPERDIR") == "") and "../.." or tup.getconfig("HELPERDIR")
tup.include(HELPERDIR .. "/use_fasm.lua")

add_include(HELPERDIR)
add_include(HELPERDIR .. "/develop/libraries/box_lib/trunk")
tup.rule("echo lang fix " .. ((tup.getconfig("LANG") == "") and "en" or tup.getconfig("LANG")) .. " > lang.inc", {"lang.inc"})
tup.rule({"h2d2b.asm", extra_inputs = {"lang.inc"}}, "fasm %f %o " .. tup.getconfig("KPACK_CMD"), "h2d2b")
