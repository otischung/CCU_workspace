all: osm sr4bm
	
osm: ./tb_lab9_hw_unsigned_osm.v ./lab9_optimized_serial_multiplier.v
	mkdir -p ./bin
	iverilog -o ./bin/osm tb_lab9_hw_unsigned_osm.v
	vvp ./bin/osm | cat > osm_log.txt
	cat osm_log.txt
	gtkwave lab9_hw_unsigned_osm.vcd &

sr4bm: ./tb_lab9_hw_unsigned_sr4bm.v ./lab9_serial_radix-4_booth_multiplier.v
	mkdir -p ./bin
	iverilog -o ./bin/sr4bm tb_lab9_hw_unsigned_sr4bm.v
	vvp ./bin/sr4bm | cat > sr4bm_log.txt
	cat sr4bm_log.txt
	gtkwave lab9_hw_unsigned_sr4bm.vcd &

clean:
	rm -f ./bin/* osm_log.txt sr4bm_log.txt lab9_hw_unsigned.vcd lab9_hw_unsigned_osm.vcd lab9_hw_unsigned_sr4bm.vcd
