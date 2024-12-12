# Arguments:
# ~~~~~~~~~~
# Leave all arguments except FPGA part on default value
# 
# hw_base_platform       -device family: Mercury, Mars
# module_name            -module name within family: KX1, AX3, ZX3, ...
# fpga_part              -FPGA part - see below the options for Mercury XU8
#    xczu4cg-fbvb900-1-e
#    xczu5ev-fbvb900-1-i
#    xczu7ev-fbvb900-2-i
# part_specific_text     -specifc text to be added to the directory naming (if needed)
# hw_platforms           -base board platform name PE1, PM3, EB1, STA

set hw_base_platform       Mercury
set module_name            XU8
set fpga_part              xczu5ev-fbvb900-1-i
set part_specific_text     _
set hw_platforms           PE1
