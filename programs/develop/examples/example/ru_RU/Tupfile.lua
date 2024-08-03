if tup.getconfig("NO_FASM") ~= "" then return end
HELPERDIR = (tup.getconfig("HELPERDIR") == "") and "../../../../" or tup.getconfig("HELPERDIR")
tup.include(HELPERDIR .. "/use_fasm.lua")

tup.rule("example.asm", "iconv -f UTF-8 -t CP866 %f > %o", "example-cp866.asm")
tup.rule("example-cp866.asm", FASM .. " %f %o " .. tup.getconfig("KPACK_CMD"), "%B")
