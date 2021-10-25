#
#CC	= gcc
#CC = gcc -Wno-unused-result -g -O2 -DLINUX -lm -lgsl -lgslcblas #for Linux
ifeq ($(CC),icc)
#ifdef INTEL_LICENSE_FILE
#CC = icc -g -O2 -DLINUX -lgsl -lgslcblas #for Linux
CC=icc 
CFLAGS= -g -O2 -DLINUX -I/usr/local/gsl-1.1/include
LDLIBS= -L/usr/local/gsl-1.1/lib -lgsl -lgslcblas #for Linux
CXX	= icpc #for g++ after source /opt/intel/bin/compilervars.sh ia32
LM	=
#CO = -g
#LDFLAGS	= 
else
CC=gcc 
CFLAGS=-g -Wno-unused-result -O2 -DLINUX -I/usr/local/gsl-1.1/include
LDLIBS= -lm -L/usr/local/gsl-1.1/lib -lgsl -lgslcblas #for Linux
#
CFLAGS=-g -Wno-unused-result -O2 -DLINUX 
LDLIBS= -lm -lgsl -lgslcblas #for Linux
CXX	= g++
#LM	= -lm
#CO 	= -lm -g
#LDFLAGS	= -lm
#after put source /opt/intel/bin/compilervars.sh ia32 in ~/.bashrc
endif
#CC = gcc -Wall -g -DLINUX -lm -lgsl -lgslcblas #for Linux
#CC = $(CC) -g -O2 -DLINUX -lm -lgsl -lgslcblas #for Linux
#LDFLAGS	= -lm
#LDFLAGS	= -g -lm -lgsl -lgslcblas
#CC = $(CC) -O2 -DWIN #for Windows
##########
TARGETS = crane1sub crane2sub emulate_crane1 emulate_crane2 crane linear1sub emulate_linear1 crane3sub emulate_crane3 crane4sub emulate_crane4 
TARGETS = emulate_crane4
#TARGETS = emulate_rca emulate_crane crane1sub crane2sub emulate_crane1 emulate_crane2
#TARGETS = kuwa_emulate 
#all: $(TARGETS)
all: lib $(TARGETS)

#../../can2m.tmp: 
#	mkdir -p ../../can2m.tmp

#emulate_rca: apc_rca.c emulate_rca.c myrandom.c calcAinvb.c
#	$(CC) emulate_rca.c -o emulate_rca $(CO)
#	$(CC) -DEMULATE emulate_rca.c -o emulate_rca $(CO)

#emulate_crane: apc_crane.c emulate_crane.c crane1sub.c crane2sub.c calcAinvb.c
#	$(CC) emulate_crane.c -o emulate_crane $(CO)
#	$(CC) -DEMULATE emulate_crane.c -o emulate_crane $(CO)

emulate_crane1: apc_crane.c emulate_crane.c crane1sub.c crane2sub.c calcAinvb.c
	$(CC) $(CFLAGS) -DCRANESUB=1 emulate_crane.c -o emulate_crane1 $(LDLIBS)
#	$(CC) -DCRANESUB=1 emulate_crane.c -o emulate_crane1 
#	$(CC) -DCRANESUB=1 emulate_crane.c -o emulate_crane1 $(CO)

emulate_crane2: apc_crane.c emulate_crane.c crane1sub.c crane2sub.c calcAinvb.c
	$(CC) $(CFLAGS) -DCRANESUB=2 emulate_crane.c -o emulate_crane2 $(LDLIBS)
#	$(CC) -DCRANESUB=2 emulate_crane.c -o emulate_crane2 $(CO)

emulate_crane3: apc_crane.c emulate_crane.c crane3sub.c calcAinvb.c
	$(CC) $(CFLAGS) -DCRANESUB=3 emulate_crane.c -o emulate_crane3 $(LDLIBS)
#	$(CC) -DCRANESUB=2 emulate_crane.c -o emulate_crane2 $(CO)

emulate_crane4: apc_crane.c emulate_crane.c crane4sub.c calcAinvb.c
	$(CC) $(CFLAGS) -DCRANESUB=4 emulate_crane.c -o emulate_crane4 $(LDLIBS)
#	$(CC) -DCRANESUB=2 emulate_crane.c -o emulate_crane2 $(CO)

emulate_linear1: apc_linear.c emulate_linear.c linear1sub.c calcAinvb.c
	$(CC) $(CFLAGS) -DCRANESUB=1 emulate_linear.c -o emulate_linear1 $(LDLIBS)
###kuwa_emulate: kuwa_apc.c myrandom.c kuwa_emulate.c
###	$(CC) -DEMULATE kuwa_emulate.c -o kuwa_emulate $(CO)
####	$(CC) -DEMULATE kuwa_emulate.c bpmpd.a -o kuwa_emulate $(CO)
###
####kuwa_emulatecc: kuwa_apc.c random.c kuwa_emulate.c
####	$(CC) -DEMULATE -E kuwa_emulate.c >kuwa_emulate.ccc
all-clean: lib-clean clean data-clean
	rm --force -rf tmp/* result/* result-ensrs/* *.dat
#	rm --force -rf tmp/* result/* result-ensrs2ge/* *.dat

lib-clean:
	cd ./can2l;make all-clean; cd ..

lib:
	cd ./can2l;make; cd ..

clean:
	rm --force *.o *~ $(TARGETS) 

data-clean: 
	rm --force -rf *.eps tmp/* *.dat *.plt *.obj *.net y_data/* y_matrix_data/* result/* net_file/* predict/* result-ensrs/*; 
#	rm --force -rf *.eps tmp/* *.dat *.plt *.obj *.net y_data/* y_matrix_data/* result/* net_file/* predict/* result-ensrs2ge/*; 
	cd ./can2l;make data-clean; cd ..

# can2b/result can2b/result-ensrs2ge
