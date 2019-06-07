set_property IOSTANDARD LVCMOS33 [get_ports {input_data[7]}]
set_property IOSTANDARD LVCMOS33 [get_ports {input_data[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {input_data[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {input_data[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {input_data[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {input_data[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {input_data[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {input_data[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {number_of_testing[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {number_of_testing[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {number_of_testing[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {number_of_testing[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {result[7]}]
set_property IOSTANDARD LVCMOS33 [get_ports {result[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {result[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {result[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {result[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {result[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {result[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {result[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports busy]
set_property IOSTANDARD LVCMOS33 [get_ports clk]
set_property IOSTANDARD LVCMOS33 [get_ports get_lsfr_base_from_data]
set_property IOSTANDARD LVCMOS33 [get_ports rst]
set_property IOSTANDARD LVCMOS33 [get_ports sqrt3_button_status]
set_property IOSTANDARD LVCMOS33 [get_ports testing_button_status]

set_property PACKAGE_PIN J15 [get_ports {input_data[0]}]
set_property PACKAGE_PIN L16 [get_ports {input_data[1]}]
set_property PACKAGE_PIN M13 [get_ports {input_data[2]}]
set_property PACKAGE_PIN R15 [get_ports {input_data[3]}]
set_property PACKAGE_PIN R17 [get_ports {input_data[4]}]
set_property PACKAGE_PIN T18 [get_ports {input_data[5]}]
set_property PACKAGE_PIN U18 [get_ports {input_data[6]}]
set_property PACKAGE_PIN R13 [get_ports {input_data[7]}]

set_property PACKAGE_PIN H17 [get_ports {result[0]}]
set_property PACKAGE_PIN K15 [get_ports {result[1]}]
set_property PACKAGE_PIN J13 [get_ports {result[2]}]
set_property PACKAGE_PIN N14 [get_ports {result[3]}]
set_property PACKAGE_PIN R18 [get_ports {result[4]}]
set_property PACKAGE_PIN V17 [get_ports {result[5]}]
set_property PACKAGE_PIN U17 [get_ports {result[6]}]
set_property PACKAGE_PIN U16 [get_ports {result[7]}]

set_property PACKAGE_PIN V16 [get_ports {number_of_testing[0]}]
set_property PACKAGE_PIN T15 [get_ports {number_of_testing[1]}]
set_property PACKAGE_PIN U14 [get_ports {number_of_testing[2]}]
set_property PACKAGE_PIN T16 [get_ports {number_of_testing[3]}]
set_property PACKAGE_PIN V15 [get_ports {number_of_testing[4]}]

set_property PACKAGE_PIN P17 [get_ports sqrt3_button_status]
set_property PACKAGE_PIN M17 [get_ports testing_button_status]
set_property PACKAGE_PIN T8 [get_ports get_lsfr_base_from_data]
set_property PACKAGE_PIN P18 [get_ports rst]
set_property PACKAGE_PIN N16 [get_ports busy]


set_property PACKAGE_PIN E3 [get_ports clk_c]
create_clock -add -name clk_c -period 10.00 -waveform {0.000 5.000} [get_ports clk_c];
























