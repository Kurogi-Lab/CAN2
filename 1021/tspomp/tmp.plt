set terminal tgif; set output "/home/kuro/data/12voicedata_ueki_all_m/mmt-ichi8-R1.obj";
set key font "Arial,30"
set xtics (0,1000,2000,3000,4000,5000); set ytics (-20000,-10000,0,10000,20000);
plot [-100:4000][-20000:20000] "/home/kuro/data/12voicedata_ueki_all_m/mmt-ichi8-R1.dat" using 0:1 w l
