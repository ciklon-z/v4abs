SYSTEMC_HOME=/home/chiahsun/tools/systemc/systemc-2.3.0
SYSTEMC_INCLUDE=$SYSTEMC_HOME/include
SYSTEMC_LIB=$SYSTEMC_HOME/lib-linux64

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SYSTEMC_LIB; $@
